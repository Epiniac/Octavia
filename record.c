#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <Mmsystem.h>

#define ALIAS "random_str"

int main(int argc,char *argv[])
{
	printf("|-------------------|\n" \
	       "|Tiny audio recorder|\n" \
		   "|By @systheron      |\n" \
		   "|-------------------|\n");
	char mci_command[100];
	char ReturnString[300];
	int mci_error;

	sprintf(mci_command, "open new type waveaudio alias %s", ALIAS);
	mci_error = mciSendString(mci_command, ReturnString, sizeof(ReturnString), NULL);

	// set the time format
	sprintf(mci_command,"set %s time format ms", ALIAS);    // just set time format
	mci_error = mciSendString(mci_command, ReturnString, sizeof(ReturnString), NULL);

	// start recording
	sprintf(mci_command, "record %s notify", ALIAS);
	mci_error = mciSendString(mci_command, ReturnString, sizeof(ReturnString), NULL);

	printf("Now on air, press a key too stop...\n");
	getch();

	//stop recording
	sprintf(mci_command,"stop %s", ALIAS);
	mci_error = mciSendString(mci_command, ReturnString, sizeof(ReturnString), NULL);

	// save the file
	sprintf(mci_command, "save %s %s", ALIAS, "random.wav");
	mci_error = mciSendString(mci_command, ReturnString, sizeof(ReturnString), NULL);

	// close the device
	sprintf(mci_command,"close %s", ALIAS);
	mci_error = mciSendString(mci_command, ReturnString, sizeof(ReturnString), NULL);
	printf("Recording stopped. Congrat, your file is save as: random.wav. \n");
	getch();
	return 0;
}

