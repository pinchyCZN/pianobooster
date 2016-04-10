
#include <stdio.h>
#include <string.h>

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
int get_data(FILE *f,char *out,int out_size,int len)
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
int get_vlq(FILE *f,int *len)
{
	unsigned char buf[4];
	int result=0,count=0,tmp;
	do{
		buf[0]=0;
		if(0==fread(buf,1,1,f))
			if(0==count)
				return 0;
		count++;
		tmp=buf[0];
		result<<=7;
		result=tmp&0x7F;
		if(tmp&0x80){
			;
		}else{
			break;
		}
	}while(count<4);
	if(len!=0)
		*len=result;
	return count;
}
int decode_header(FILE *f,int len)
{
	int i,val,pos;
	char buf[8];
	char *list[]={"format","tracks","division"};
	pos=ftell(f);
	for(i=0;i<sizeof(list)/sizeof(char*);i++){
		get_data(f,buf,sizeof(buf),2);
		val=get_int16(buf);
		printf("%s=%i\n",list[i],val);
	}
	fseek(f,pos,SEEK_SET);
	return 0;
}
int decode_midi_event(FILE *f,int event)
{
	unsigned char buf[4]={0};
	switch(event&0xF0){
	case 0x80:
	case 0x90:
	case 0xA0:
	case 0xB0:
	case 0xE0:
		{
			int d1,d2;
			get_data(f,buf,sizeof(buf),2);
			d1=buf[0];
			d2=buf[1];
			printf("midi %02X %02X %02X\n",event,d1,d2);
		}
		break;
	case 0xC0:
	case 0xD0:
		{
			int d1;
			get_data(f,buf,sizeof(buf),1);
			d1=buf[0];
			printf("midi %02X %02X\n",event,d1);
		}
		break;
	}
}
int decode_track(FILE *f,int tlen)
{
	int index;
	unsigned char buf[8];
	for(index=0;index<tlen; ){
		int delta=0;
		int event=0;
		int count;
		count=get_vlq(f,&delta);
		if(0==count)
			break;
		index+=count;
		buf[0]=0;
		if(0==fread(buf,1,1,f))
			break;
		index++;
		event=buf[0];
		switch(event){
		case 0xF0:
		case 0xF7:
			//sysex events
			{
				int len=0;
				count=get_vlq(f,&len);
				if(count)
					fseek(f,len,SEEK_CUR);
				index+=count+len;
				printf("sysex event %02X\n",event);
			}
			break;
		case 0xFF:
			{
				int type,len=0;
				get_data(f,buf,sizeof(buf),1);
				index++;
				type=buf[0];
				count=get_vlq(f,&len);
				if(count)
					fseek(f,len,SEEK_CUR);
				index+=count+len;
				printf("meta event %02X len=%i\n",type,len);
				if(type==0x2F)
					printf("end of track\n");
			}
			break;
		default: //midi event
			{
				printf("delta = %i ",delta);
				decode_midi_event(f,event);
				index+=2;
			}
			break;
		}
	}
	return index;
}

int parse_midi_file(char *fname)
{
	FILE *f;
	set_screen_buffer_size(80,9000);
	f=fopen(fname,"rb");
	if(f){
		while(1){
			char name[8],buf[8];
			int len,pos;
			if(0==get_data(f,name,sizeof(name),4))
				break;
			name[sizeof(name)-1]=0;
			if(0==get_data(f,buf,sizeof(buf),4))
				break;
			len=get_int32(buf);
			pos=ftell(f);

			if(0==strcmp("MThd",name)){
				printf("header len=%i\n",len);
				decode_header(f,len);
			}else if(0==strcmp("MTrk",name)){
				printf("track len=%i\n",len);
				decode_track(f,len);
			}
			fseek(f,pos+len,SEEK_SET);

		}
		fclose(f);
	}
	return 0;
}