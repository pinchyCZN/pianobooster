
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
		result=fread(out,len,1,f);
	}
	return result;
}
int decode_header(FILE *f)
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
int decode_track(FILE *f)
{

}
int parse_midi_file(char *fname)
{
	FILE *f;
	f=fopen(fname,"rb");
	if(f){
		while(1){
			char name[8],buf[8];
			int len;
			if(0==get_data(f,name,sizeof(name),4))
				break;
			name[sizeof(name)-1]=0;
			get_data(f,buf,sizeof(buf),4);
			len=get_int32(buf);

			if(0==strcmp("MThd",name)){
				printf("header\n");
				decode_header(f);
			}else if(0==strcmp("MTrk",name)){
				printf("track\n");
			}
			printf("len=%i\n",len);
			fseek(f,len,SEEK_CUR);

		}
		fclose(f);
	}
	return 0;
}