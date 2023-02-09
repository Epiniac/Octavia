#include <al.h>
#include <alc.h>

ALCdevice* Device;
ALCdevice* CaptureDevice;

bool InitCapture()
{
	// On commence par vérifier que la capture audio est supportée
	if (alcIsExtensionPresent(Device, "ALC_EXT_CAPTURE") == AL_FALSE)
		return 0;
	
	

}
