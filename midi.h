#ifndef MIDI_H
#define MIDI_H

#include <stdio.h>

typedef struct MIDIFile {
    FILE *file;
    int tick_resolution;
    int current_time;
} MIDIFile;

typedef struct{
    char chunkt_type[4];
    int chunk_size;
    int num_tracks;
    int division;
    int format;
    int ticks_per_quarter_note;
}MIDIHeader;

void MIDI_init(MIDIFile *midi);
void MIDI_cleanup(MIDIFile *midi);
void MIDI_set_tick_resolution(MIDIFile *midi, int ticks_per_quarter_note);
void MIDI_add_note(MIDIFile *midi, int channel, int start_time, int end_time,
                   int note_number, int velocity, double duration);
void MIDI_add_program_change(MIDIFile *midi, int channel, int program_number);
void MIDI_write(MIDIFile *midi, char *filename);

#endif
