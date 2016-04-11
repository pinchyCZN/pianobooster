#include <windows.h>
#include <conio.h>
#include <stdio.h>

typedef struct{
	char name[MAXPNAMELEN];
	int id;
}MIDI_DEVICE;

typedef struct{
	int count;
	MIDI_DEVICE *devices;
}MIDI_DEV_LIST;

MIDI_DEV_LIST mdev_out;
MIDI_DEV_LIST mdev_in;

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

int list_midi(MIDI_DEV_LIST *mdev_list,
			  UINT ( __stdcall * get_num_devs)(void),
			  MMRESULT (__stdcall * get_dev_caps)(UINT,void *,UINT),
			  void *caps,int caps_size,int name_offset)
{
	int i,count;
	mdev_list->count=count=get_num_devs();
	if(0!=mdev_list->devices)
		free(mdev_list->devices);
	mdev_list->devices=0;
	if(count==0)
		return count;
	mdev_list->devices=calloc(count,sizeof(MIDI_DEVICE));
	for(i=0;i<count;i++){
		if(MMSYSERR_NOERROR==get_dev_caps(i,caps,caps_size)){
			char *name=(char*)caps+name_offset;
			if(mdev_list->devices!=0){
				MIDI_DEVICE *md=&mdev_list->devices[i];
				strncpy(md->name,name,sizeof(md->name));
				md->name[sizeof(md->name)-1]=0;
				md->id=i;
			}
			printf("%s\n",name);
		}
	}
	if(0==mdev_in.devices)
		count=0;
	return count;
}

int test_midi(int index)
{
	if(mdev_out.count>1){
		hmo=0;
		midiOutOpen(&hmo,mdev_out.devices[index].id,NULL,0,CALLBACK_NULL);
		if(hmo!=0){
			DWORD msg;
			char *p=&msg;
			p[0]=0x90;
			p[1]=0x3c;
			p[2]=0x01;
			midiOutShortMsg(hmo,msg);
//			Sleep(1000);
			p[0]=0x80;
			p[1]=0x3c;
			p[2]=0x40;
			midiOutShortMsg(hmo,msg);
		}
	}
}
int find_keyboard(MIDI_DEV_LIST *list)
{
	int i;
	for(i=0;i<list->count;i++){
		char n1[MAXPNAMELEN];
		strncpy(n1,list->devices[i].name,sizeof(n1));
		n1[sizeof(n1)-1]=0;
		strlwr(n1);
		if(strstr(n1,"keyboard"))
			return i;
	}
	return -1;
}
void CALLBACK in_event(HMIDIIN hMidiIn,UINT wMsg,DWORD dwInstance,DWORD dwParam1,DWORD dwParam2)
{
	printf("dfsdf\n");
}
int main(int argc,char **argv)
{
	char *fname;
	MIDIOUTCAPS ocaps;
	MIDIINCAPS icaps;
	int offset;
	int index_out,index_in;
	offset=(char*)&ocaps.szPname-(char*)&ocaps;
	list_midi(&mdev_out,midiOutGetNumDevs,midiOutGetDevCaps,&ocaps,sizeof(ocaps),offset);
	offset=(char*)&icaps.szPname-(char*)&icaps;
	list_midi(&mdev_in,midiInGetNumDevs,midiInGetDevCaps,&icaps,sizeof(icaps),offset);
	index_out=find_keyboard(&mdev_out);
	if(index_out>=0){
		index_in=find_keyboard(&mdev_in);
		if(index_in>=0){
			//midiOutOpen(&hmo,mdev_out.devices[index].id,NULL,0,CALLBACK_NULL);
			midiInOpen(&hmi,mdev_in.devices[index_in].id,in_event,0,MIDI_IO_STATUS|CALLBACK_FUNCTION);
		}
	}
	fname="E:\\music\\Mp3\\MusicStudy\\keyboard\\Scarlatti_Sonate_K.517.mid";
	//fname="C:\\temp\\PMLP336239-Scarlatti_Sonate_K.517.mid";
	//midi_file_test(fname);
	printf("done\n");
	while(1){
		Sleep(100);
	}
	getch();
}