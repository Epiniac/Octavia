#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "midi.h"

MIDIFile *MIDI_open(const char *filename, int num_tracks) {
    MIDIFile *midi = (MIDIFile *) malloc(sizeof(MIDIFile));
    if (midi == NULL) {
        return NULL;
    }
    midi->file = fopen(filename, "wb");
    if (midi->file == NULL) {
        free(midi);
        return NULL;
    }
    midi->num_tracks = num_tracks;
    midi->tracks = (MIDITrack *) calloc(num_tracks, sizeof(MIDITrack));
    if (midi->tracks == NULL) {
        fclose(midi->file);
        free(midi);
        return NULL;
    }
    for (int i = 0; i < num_tracks; i++) {
        midi->tracks[i].delta_time = 0;
        midi->tracks[i].num_events = 0;
        midi->tracks[i].events = NULL;
    }
    return midi;
}

void MIDI_close(MIDIFile *midi) {
    if (midi != NULL) {
        if (midi->tracks != NULL) {
            for (int i = 0; i < midi->num_tracks; i++) {
                if (midi->tracks[i].events != NULL) {
                    free(midi->tracks[i].events);
                }
            }
            free(midi->tracks);
        }
        if (midi->file != NULL) {
            fclose(midi->file);
        }
        free(midi);
    }
}

void MIDI_set_tick_resolution(MIDIFile *midi, int ticks_per_second) {
    midi->ticks_per_second = ticks_per_second;
}

void MIDI_add_note(MIDIFile *midi, int track_number, int start_time, int end_time, int channel, int note_number, int velocity) {
    MIDITrack *track = &midi->tracks[track_number];
    int num_events = track->num_events;
    MIDIEvent *events = track->events;
    track->events = (MIDIEvent *) realloc(events, (num_events + 2) * sizeof(MIDIEvent));
    if (track->events == NULL) {
        track->events = events;
        return;
    }
    track->num_events += 2;
    track->events[num_events].delta_time = start_time - track->delta_time;
    track->events[num_events].status = MIDI_STATUS_NOTE_ON | channel;
    track->events[num_events].data1 = note_number;
    track->events[num_events].data2 = velocity;
    track->delta_time = start_time;
    track->events[num_events + 1].delta_time = end_time - start_time;
    track->events[num_events + 1].status = MIDI_STATUS_NOTE_OFF | channel;
    track->events[num_events + 1].data1 = note_number;
    track->events[num_events + 1].data2 = velocity;
    track->delta_time = end_time;
}

void MIDI_write_track_header(MIDIFile *midi, int track_number) {
    MIDITrack *track = &midi->tracks[track_number];
    fwrite("MTrk", 1, 4, midi->file);
    fwrite(&track->length, 1, 4, midi->file);
    fwrite(track->data, 1, track->length, midi->file);
}

void MIDI_write_header(MIDIFile *midi) {
    fwrite("MThd", 1, 4, midi->file);
    fwrite("\x00\x00\x00\x06", 1, 4, midi->file);
    fwrite("\x00\x01", 1, 2, midi->file);
    fwrite(&midi->num_tracks, 1, 2, midi->file);
    fwrite(&midi->ticks_per_second, 1, 2, midi->file);
}

void MIDI_write_track(MIDIFile *midi, int track_number) {
    MIDITrack *track = &midi->tracks[track_number];
    int num_events = track->num_events;
    MIDIEvent *events = track->events;
    track->length = 0;
    track->data = (char *) calloc(num_events * 4, sizeof(char));
    if (track->data == NULL) {
        return;
    }
    char *data = track->data;
    for (int i = 0; i < num_events; i++) {
        int delta_time = events[i].delta_time;
        if (delta_time > 0x0FFFFFFF) {
            delta_time = 0x0FFFFFFF;
        }
        if (delta_time >= 0x00000080) {
            *data++ = (delta_time >> 21) | 0x80;
        }
        if (delta_time >= 0x0000040) {
            *data++ = (delta_time >> 14) | 0x80;
        }
        if (delta_time >= 0x0000020) {
            *data++ = (delta_time >> 7) | 0x80;
        }
        *data++ = delta_time & 0x7F;
        *data++ = events[i].status;
        *data++ = events[i].data1;
        if ((events[i].status & 0xF0) != MIDI_STATUS_PROGRAM_CHANGE && (events[i].status & 0xF0) != MIDI_STATUS_CHANNEL_AFTER_TOUCH) {
            *data++ = events[i].data2;
        }
        track->length += 4;
    }
    MIDI_write_track_header(midi, track_number);
}

void MIDI_write(MIDIFile *midi) {
    MIDI_write_header(midi);
    for (int i = 0; i < midi->num_tracks; i++) {
        MIDI_write_track(midi, i);
    }
}
