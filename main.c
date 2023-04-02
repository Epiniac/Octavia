#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wavfile.h"
#include "midi.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s input.wav output.mid\n", argv[0]);
        return 1;
    }

    // Convert the WAV file to MIDI
    if (wav_to_midi(argv[1], argv[2]) != 0) {
        fprintf(stderr, "Error: Failed to convert %s to %s\n", argv[1], argv[2]);
        return 1;
    }

    return 0;
}
