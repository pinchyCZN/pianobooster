#include <windows.h>
#include <conio.h>
#include <stdio.h>

int list_midi_in()
{
	int i,count;
	count=midiInGetNumDevs();
	for(i=0;i<count;i++){
		MIDIINCAPS caps={0};
		if(MMSYSERR_NOERROR==midiInGetDevCaps(i,&caps,sizeof(caps)))
			printf("%s\n",caps.szPname);
	}
	return count;
}
int list_midi_out()
{
	int i,count;
	count=midiOutGetNumDevs();
	for(i=0;i<count;i++){
		MIDIOUTCAPS caps={0};
		if(MMSYSERR_NOERROR==midiOutGetDevCaps(i,&caps,sizeof(caps)))
			printf("%s\n",caps.szPname);
	}
	return count;
}

int main(int argc,char **argv)
{

	list_midi_in();
	list_midi_out();
	printf("done\n");
	getch();
}