#include <windows.h>
#include <stdio.h>
#include <string.h>

typedef struct{
	int time;
	int type;
	int data;
	int data2;
}MIDI_EVENT;

typedef struct{
	int event_count;
	MIDI_EVENT *events;
}MIDI_TRACK;

typedef struct{
	char fname[MAX_PATH];
	int format;
	int track_count;
	int division;
	MIDI_TRACK *tracks;
}MIDI_FILE;

int get_int32(unsigned char *buf)
{
	int i;
	i=(buf[0]<<24)|(buf[1]<<16)|(buf[2]<<8)|buf[3];
	return i;
}
int get_int16(unsigned char *buf)
{
	int i;
	i=(buf[0]<<8)|buf[1];
	return i;
}
int get_fdata(FILE *f,char *out,int out_size,int len)
{
	int result=0;
	if(out!=0 && out_size>0){
		memset(out,0,out_size);
		if(len>out_size)
			len=out_size;
		result=fread(out,1,len,f);
	}
	return result;
}
int get_vlq(unsigned char *data,int dlen,int *val)
{
	int result=0,count=0,tmp;
	do{
		if(count>=dlen)
			break;
		tmp=data[count++];
		result<<=7;
		result=tmp&0x7F;
		if(tmp&0x80){
			;
		}else{
			break;
		}
	}while(count<4);
	if(val!=0)
		*val=result;
	return count;
}
int decode_header(unsigned char *data,int len,MIDI_FILE *mf)
{
	int i;
	unsigned char *p;
	int offset=0;
	char *list[]={"format","tracks","division"};
	p=data;
	for(i=0;i<sizeof(list)/sizeof(char*);i++){
		int val;
		if(offset>=(len-1))
			break;
		val=get_int16(p);
		switch(i){
		case 0:	mf->format=val; break;
		case 1: mf->track_count=val; break;
		case 2: mf->division=val; break;
		}
		p+=2;
		offset+=2;
		printf("%s=%i\n",list[i],val);
	}
	return 0;
}
int decode_midi_event(unsigned char *data,int dlen,int event)
{
	int result=0;
	switch(event&0xF0){
	case 0x80:
	case 0x90:
	case 0xA0:
	case 0xB0:
	case 0xE0:
		{
			if(dlen>=2){
				int d1,d2;
				d1=data[0];
				d2=data[1];
				printf("midi %02X %02X %02X\n",event,d1,d2);
			}
			result=2;
		}
		break;
	case 0xC0:
	case 0xD0:
		{
			if(dlen>=1){
				int d1;
				d1=data[0];
				printf("midi %02X %02X\n",event,d1);
			}
			result=1;
		}
		break;
	}
	return result;
}
int count_track_events(unsigned char *data,int tlen,int *event_count)
{
	unsigned char *p;
	int index;
	p=data;
	for(index=0;index<tlen; ){
		int delta=0;
		int event=0;
		int count;
		count=get_vlq(p,tlen-index,&delta);
		if(0==count)
			break;
		p+=count;
		index+=count;
		if(index>=tlen)
			break;
		event=p[0];
		p++;
		index++;
		if(index>=tlen)
			break;
		switch(event){
		case 0xF0:
		case 0xF7:
			//sysex events
			{
				int len=0;
				count=get_vlq(p,tlen-index,&len);
				index+=count+len;
				p+=count+len;
				printf("sysex event %02X\n",event);
			}
			break;
		case 0xFF:
			{
				int type,len=0;
				type=p[0];
				p++;
				index++;
				if(index>=tlen)
					break;
				count=get_vlq(p,tlen-index,&len);
				p+=count+len;
				index+=count+len;
				printf("meta event %02X len=%i\n",type,len);
				if(type==0x2F)
					printf("end of track\n");
			}
			break;
		default: //midi event
			{
				printf("delta = %i ",delta);
				count=decode_midi_event(p,tlen-index,event);
				p+=count;
				index+=count;
			}
			break;
		}
		if(event_count!=0)
			(*event_count)++;
	}
	return index;
}
int read_track_events(unsigned char *data,int tlen,MIDI_TRACK *mt)
{
	unsigned char *p;
	int index;
	int time=0;
	int event_counter=0;
	p=data;
	for(index=0;index<tlen; ){
		MIDI_EVENT *midi_event;
		int delta=0;
		int event=0;
		int count;
		count=get_vlq(p,tlen-index,&delta);
		time+=delta;
		if(0==count)
			break;
		p+=count;
		index+=count;
		if(index>=tlen)
			break;
		event=p[0];
		p++;
		index++;
		if(index>=tlen)
			break;
		if(event_counter>=mt->event_count)
			break;
		midi_event=&mt->events[event_counter];
		midi_event->type=event;
		midi_event->time=time;
		switch(event){
		case 0xF0:
		case 0xF7:
			//sysex events
			{
				int len=0;
				count=get_vlq(p,tlen-index,&len);
				index+=count+len;
				p+=count+len;
				midi_event->data=len;
			}
			break;
		case 0xFF:
			{
				int type,len=0;
				type=p[0];
				p++;
				index++;
				if(index>=tlen)
					break;
				count=get_vlq(p,tlen-index,&len);
				p+=count+len;
				index+=count+len;
				midi_event->data=type;
				midi_event->data2=len;
			}
			break;
		default: //midi event
			{
				int t=event&0xF0;
				int count=2;
				if(0xC0==t || 0xD0==t){
					count=1;
					midi_event->data=p[0];
				}else{
					if(index<(tlen-1)){
						midi_event->data=p[0];
						midi_event->data2=p[1];
					}
				}
				p+=count;
				index+=count;
			}
			break;
		}
		event_counter++;
	}
	return event_counter;
}

int parse_midi_file(MIDI_FILE *mfile)
{
	FILE *f;
	set_screen_buffer_size(80,9000);
	f=fopen(mfile->fname,"rb");
	if(f){
		int track_index=0;
		while(1){
			char *data;
			char name[8],buf[8];
			int len,pos;
			if(0==get_fdata(f,name,sizeof(name),4))
				break;
			name[sizeof(name)-1]=0;
			if(0==get_fdata(f,buf,sizeof(buf),4))
				break;
			len=get_int32(buf);
			pos=ftell(f);
			data=calloc(1,len);
			if(data!=0){
				fread(data,1,len,f);
				if(0==strcmp("MThd",name)){
					printf("header len=%i\n",len);
					decode_header(data,len,mfile);
					if(mfile->track_count!=0){
						mfile->tracks=calloc(mfile->track_count,sizeof(MIDI_TRACK));
					}
				}else if(0==strcmp("MTrk",name)){
					int event_count=0;
					printf("track len=%i\n",len);
					count_track_events(data,len,&event_count);
					if(event_count!=0){
						if(track_index<mfile->track_count
							&& mfile->tracks!=0){
							MIDI_TRACK *trk=&mfile->tracks[track_index];
							trk->event_count=event_count;
							trk->events=calloc(event_count,sizeof(MIDI_EVENT));
							if(trk->events!=0)
								read_track_events(data,len,trk);
						}
					}
					track_index++;
				}
				free(data);
			}
			fseek(f,pos+len,SEEK_SET);

		}
		fclose(f);
	}
	return 0;
}

int dump_midi_struct(MIDI_FILE *mf)
{
	int i;
	for(i=0;i<mf->track_count;i++){
		MIDI_TRACK *mt;
		int j;
		mt=&mf->tracks[i];
		for(j=0;j<mt->event_count;j++){
			MIDI_EVENT *me;
			me=&mt->events[j];
			printf("me:%06i %02X %02X %02X\n",me->time,me->type,me->data,me->data2);
		}
	}
}
int midi_file_test(char *fname)
{
	MIDI_FILE mf={0};
	strncpy(mf.fname,fname,sizeof(mf.fname));
	mf.fname[sizeof(mf.fname)-1]=0;
	parse_midi_file(&mf);
	dump_midi_struct(&mf);
}