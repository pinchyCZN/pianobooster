#include <windows.h>
#include <conio.h>
#include <stdio.h>

typedef struct{
	char name[MAXPNAMELEN];
	int id;
}MIDI_DEVICE;

MIDI_DEVICE *midi_dev_in=0;
MIDI_DEVICE *midi_dev_out=0;
int midi_dev_in_cnt=0;
int midi_dev_out_cnt=0;
HMIDIOUT	hmo=0;
HMIDIIN		hmi=0;

int set_screen_buffer_size(int x,int y)
{
	HANDLE hcon;
	COORD size;
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	size.X=x;
	size.Y=y;
	SetConsoleScreenBufferSize(hcon,size);
	return TRUE;
}

int list_midi_in()
{
	int i,count;
	midi_dev_in_cnt=count=midiInGetNumDevs();
	if(midi_dev_in!=0)
		free(midi_dev_in);
	midi_dev_in=0;
	if(count==0)
		return count;
	midi_dev_in=calloc(count,sizeof(MIDI_DEVICE));
	for(i=0;i<count;i++){
		MIDIINCAPS caps={0};
		if(MMSYSERR_NOERROR==midiInGetDevCaps(i,&caps,sizeof(caps))){
			if(midi_dev_in!=0){
				strncpy(midi_dev_in[i].name,caps.szPname,sizeof(midi_dev_in[i].name));
				midi_dev_in[i].name[sizeof(midi_dev_in[i].name)-1]=0;
				midi_dev_in[i].id=i;
			}
			printf("%s\n",caps.szPname);
		}
	}
	return count;
}
int list_midi_out()
{
	int i,count;
	midi_dev_out_cnt=count=midiOutGetNumDevs();
	if(midi_dev_out!=0)
		free(midi_dev_out);
	midi_dev_out=0;
	if(count==0)
		return count;
	midi_dev_out=calloc(count,sizeof(MIDI_DEVICE));
	for(i=0;i<count;i++){
		MIDIOUTCAPS caps={0};
		if(MMSYSERR_NOERROR==midiOutGetDevCaps(i,&caps,sizeof(caps))){
			if(midi_dev_out!=0){
				strncpy(midi_dev_out[i].name,caps.szPname,sizeof(midi_dev_out[i].name));
				midi_dev_out[i].name[sizeof(midi_dev_out[i].name)-1]=0;
				midi_dev_out[i].id=i;
			}
			printf("%s\n",caps.szPname);
		}
	}
	return count;
}

int test_midi()
{
	if(midi_dev_out_cnt>1){
		hmo=0;
		midiOutOpen(&hmo,midi_dev_out[1].id,NULL,0,CALLBACK_NULL);
		if(hmo!=0){
			DWORD msg;
			char *p=&msg;
			p[0]=0x90;
			p[1]=0x3c;
			p[2]=0x40;
			midiOutShortMsg(hmo,msg);
			Sleep(1000);
			p[0]=0x80;
			p[1]=0x3c;
			p[2]=0x40;
			midiOutShortMsg(hmo,msg);
		}
	}
}
int main(int argc,char **argv)
{
	char *fname;
//	list_midi_in();
//	list_midi_out();
//	test_midi();
	fname="E:\\music\\Mp3\\MusicStudy\\keyboard\\Scarlatti_Sonate_K.517.mid";
	//fname="C:\\temp\\PMLP336239-Scarlatti_Sonate_K.517.mid";
	midi_file_test(fname);
	printf("done\n");
	getch();
}