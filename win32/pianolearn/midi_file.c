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
				//printf("midi %02X %02X %02X\n",event,d1,d2);
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
				//printf("midi %02X %02X\n",event,d1);
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
				//printf("sysex event %02X\n",event);
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
				//printf("meta event %02X len=%i\n",type,len);
				//if(type==0x2F)
				//	printf("end of track\n");
			}
			break;
		default: //midi event
			{
				//printf("delta = %i ",delta);
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
char current_fname[MAX_PATH]={0};
int set_current_fname(char *fname)
{
	strncpy(current_fname,fname,sizeof(current_fname));
	current_fname[sizeof(current_fname)-1]=0;
	return 0;
}

int play_midi_event(HMIDIOUT hmo,MIDI_EVENT *me)
{
	DWORD msg=0;
	char *p=&msg;
	if(hmo==0)
		return 0;
	p[0]=me->type;
	p[1]=me->data; //note
	p[2]=me->data2; //velo
	return midiOutShortMsg(hmo,msg);
}
int clear_all_notes(HMIDIOUT hmo)
{
	int i;
	if(hmo==0)
		return 0;
	for(i=0x24;i<=0x60;i++){
		DWORD msg=0;
		char *p=&msg;
		p[0]=0x80;
		p[1]=i; //note
		p[2]=0; //velo
		midiOutShortMsg(hmo,msg);
	}
	return 0;
}
int seek_next_note(MIDI_TRACK *mt,int *index)
{
	int i=*index;
	if(i>=mt->event_count)
		i=0;
	for( ;i<mt->event_count;i++){
		MIDI_EVENT *me=&mt->events[i];
		int event,velo;
		event=me->type&0xF0;
		velo=me->data2;
		if(event==0x90){
			if(velo!=0){
				*index=i;
				return TRUE;
			}
		}
	}
	return FALSE;
}
MIDI_EVENT current_events[16]={0};
int ce_count=0;

int play_current_notes(HMIDIOUT hmo,MIDI_EVENT *mlist,int count)
{
	int i;
	for(i=0;i<count;i++){
		play_midi_event(hmo,&mlist[i]);
	}
	return count;
}
int gather_notes(MIDI_TRACK *mt,int *index,MIDI_EVENT *mlist,int list_size,int *total)
{
	int count=0;
	int time=0;
	int i=*index;
	if(i>=mt->event_count)
		return FALSE;
	for( ;i<mt->event_count;i++){
		MIDI_EVENT *me=&mt->events[i];
		int event,velo;
		event=me->type&0xF0;
		velo=me->data2;
		if(event==0x90){
			if(velo!=0){
				if(count>=list_size)
					break;
				if(time==0)
					time=me->time;
				if(me->time > time)
					break;
				mlist[count]=*me;
				mlist[count].data2=1;
				count++;
			}
		}
	}
	*index=i;
	*total=count;
	return count;
}
int check_note_ranges(MIDI_EVENT *mlist,int count)
{
	int i,result=0;
	for(i=0;i<count;i++){
		int note=mlist[i].data;
		if(note<0x24 || note>0x60){
			mlist[i].data2=0;
			result++;
		}
	}
	return count-result;
}
int check_key_press(HMIDIOUT hmo,MIDI_EVENT *mlist,int list_count)
{
	int i,played=0;
	int result=FALSE;
	extern unsigned char in_keys[];
	for(i=0;i<list_count;i++){
		int key=mlist[i].data&0xFF;
		if(mlist[i].data2==0)
			played++;
		else{
			if(in_keys[key]!=0){
				mlist[i].data2=0;
				play_midi_event(hmo,&mlist[i]);
				played++;
			}
		}
	}
	if(played>=list_count)
		result=TRUE;
	return result;
}
int fforward_track(MIDI_TRACK *mt,int *index)
{
	int i,time=0;
	for(i=*index;i<mt->event_count;i++){
		MIDI_EVENT *me=&mt->events[i];
		int event,velo;
		event=me->type&0xF0;
		velo=me->data2;
		if(event==0x90 && velo!=0){
			int delta;
			if(time==0)
				time=me->time;
			delta=me->time-time;
			if(delta>500){
				*index=i;
				break;
			}
		}
	}
	return 0;
}
int check_commands(MIDI_TRACK *mt,int *index,int *state)
{
	extern unsigned char in_keys[];
	extern unsigned char trig_keys[];
	int result=FALSE;
	int t1,t2,c0,c1,c2,c3;
	int clear_trig=FALSE;
	t1=in_keys[0x24];
	t2=in_keys[0x26];
	c0=trig_keys[0x5D];
	c1=trig_keys[0x5E];
	c2=trig_keys[0x5F];
	c3=trig_keys[0x60];
	if(t1 && t2){
		if((*state)==1){
			if(c0 || c1 || c2 || c3){
				clear_trig=TRUE;
				*state=0;
				result=TRUE;
			}
		}
		if(result)
			goto EXIT;
		if(c0){
			clear_trig=TRUE;
			*state=0;
			*index=0;
			result=TRUE;
		}
		if(c2){
			int i,time,target;
			clear_trig=TRUE;
			i=(*index)-1;
			if(i<=0){
				*index=0;
				result=TRUE;
				goto EXIT;
			}
			time=mt->events[i].time;
			target=0;
			printf("begin=%i\n",i);
			for( ;i>0;i--){
				MIDI_EVENT *me=&mt->events[i];
				if(me->time<time){
					int event=me->type&0xF0;
					if(event==0x90){
						int velo=me->data2;
						if(velo!=0){
							int delta=time-me->time;
							if(delta>500)
								break;
						}
					}
				}
			}
			result=TRUE;
			*index=i;
			printf("end=%i\n",i);
		}
		else if(c3){
			clear_trig=TRUE;
			fforward_track(mt,index);
			result=TRUE;
		}
		else if(c1){
			clear_trig=TRUE;
			if((*state)==0){
				*state=1;
				result=TRUE;
			}
		}

	}
EXIT:
	if(clear_trig){
		trig_keys[0x5D]=0;
		trig_keys[0x5E]=0;
		trig_keys[0x5F]=0;
		trig_keys[0x60]=0;
	}
	return result;
}
int current_instrument=6;
int set_current_instrument(int i)
{
	return current_instrument=i;
}
int change_program(HMIDIOUT hmo,int instr)
{
	if(hmo!=0){
		MIDI_EVENT me={0};
		me.type=0xC0;
		me.data=instr;
		play_midi_event(hmo,&me);
	}
	return TRUE;
}
int play_track(HMIDIOUT hmo,MIDI_TRACK *mt,int index,int *state)
{
	change_program(hmo,current_instrument);
	while(1){
		DWORD time=0,delta;
		int i;
		if(index>=mt->event_count)
			index=0;
		for(  ;index<mt->event_count;index++){
			MIDI_EVENT *me=&mt->events[index];
			int event,velo;
			event=me->type&0xF0;
			velo=me->data2;
			if(event==0x90 || event==0x80){
				if(time==0)
					time=me->time;
				delta=me->time-time;
				if(delta!=0){
					if(delta>1000)
						delta=1000;
					Sleep(delta);
				}
				time=me->time;
				play_midi_event(hmo,me);
			}
			check_commands(mt,&index,state);
			if((*state)==0)
				break;
		}
		if((*state)==0)
			break;

	}
	*state=0;
	clear_all_notes(hmo);
	return TRUE;
}
DWORD WINAPI play_midi_thread(void *arg)
{
	HMIDIOUT	hmo=arg;
	MIDI_FILE mf={0};
	extern HANDLE thread_event;
	int index=0;
	printf("thread\n");

	strncpy(mf.fname,current_fname,sizeof(mf.fname));
	mf.fname[sizeof(mf.fname)-1]=0;
	parse_midi_file(&mf);
	clear_all_notes(hmo);

	while(1){
		if(hmo!=0){
			if(mf.track_count==2){
				MIDI_TRACK *mt;
				mt=&mf.tracks[1];
				while(1){
					static int state=0;
					if(index>=mt->event_count)
						index=0;
					if(state==1)
						play_track(hmo,mt,index,&state);
					if(seek_next_note(mt,&index)){
						int next_index=index;
						ce_count=0;
						gather_notes(mt,&index,current_events,sizeof(current_events)/sizeof(MIDI_EVENT),&ce_count);
						if(check_note_ranges(current_events,ce_count)>0){
							printf("time=%i\n",current_events[0].time);
							play_current_notes(hmo,current_events,ce_count);
							while(1){
								WaitForSingleObject(thread_event,INFINITE);
								if(check_key_press(hmo,current_events,ce_count))
									break;
								if(check_commands(mt,&index,&state)){
									clear_all_notes(hmo);
									break;
								}
							}
						}else
							Sleep(100);
					}else
						Sleep(100);
				}
			}
		}
	}
}