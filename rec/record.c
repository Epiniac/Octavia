#include <stdlib.h>
#define RECORD "arecord --format=cd file.mp3"
int main()
{
	//puts(RECORD);
	system(RECORD);
	return 0;
}
