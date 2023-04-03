#include <stdlib.h>
#define RECORD "arecord --format=cd file.wav"
int main()
{
	//puts(RECORD);
	system(RECORD);
	return 0;
}
