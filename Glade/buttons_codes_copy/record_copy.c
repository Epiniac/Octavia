#include <stdlib.h>
#define RECORD "arecord --format=cd file.wav"

void arreterEnregistrement()
{
	system("pkill arecord");
}

void rec()
{
	//puts(RECORD);
	system(RECORD);
}


