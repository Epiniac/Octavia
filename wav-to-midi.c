#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "wavfile.h"
#include "midi.h"

#define MIN_NOTE_DURATION 100 // minimum note duration in ms
#define MAX_NOTE_DURATION 2000 // maximum note duration in ms

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("Usage: %s input.wav output.mid\n", argv[0]);
        return 1;
    }

    // Open the input file
    FILE* input_file = fopen(argv[1], "rb");
    if (!input_file) {
        printf("Error: could not open input file %s\n", argv[1]);
        return 1;
    }

    // Read the WAV header
    WAVHeader* wav_header = read_wav(input_file);
    if (!wav_header) {
        printf("Error: invalid WAV file %s\n", argv[1]);
        fclose(input_file);
        return 1;
    }

    // Check that the WAV file has one channel
    if (wav_header->channels != 1) {
        printf("Error: WAV file %s has %d channels (must have 1)\n", argv[1], wav_header->channels);
        fclose(input_file);
        free(wav_header);
        return 1;
    }

    // Calculate the number of samples
    int num_samples = wav_header->subchunk2_size / sizeof(short);

    // Allocate memory for the audio data
    short* audio_data = (short*)malloc(num_samples * sizeof(short));
    if (!audio_data) {
        printf("Error: out of memory\n");
        fclose(input_file);
        free(wav_header);
        return 1;
    }

    // Read the audio data
    fread(audio_data, sizeof(short), num_samples, input_file);

    // Close the input file
    fclose(input_file);

    // Create the output MIDI file
    FILE* output_file = fopen(argv[2], "wb");
    if (!output_file) {
        printf("Error: could not create output file %s\n", argv[2]);
        free(audio_data);
        free(wav_header);
        return 1;
    }

    // Write the MIDI header
    MIDIHeader midi_header;
    midi_header.format = 1;
    midi_header.num_tracks = 1;
    midi_header.ticks_per_quarter_note = 480;
    write_midi_header(output_file, &midi_header);

    // Find the maximum amplitude
    short max_amplitude = 0;
    for (int i = 0; i < num_samples; i++) {
        short amplitude = abs(audio_data[i]);
        if (amplitude > max_amplitude) {
            max_amplitude = amplitude;
        }
    }

    // Convert the audio data to MIDI notes
    int sample_rate = wav_header->sample_rate;
    int num_notes = 0;
    for (int i = 0; i < num_samples; i++) {
        // Calculate the frequency of the audio sample
        double frequency = midi_note_frequency(audio_data[i], max_amplitude, sample_rate);

        // Check if the frequency is within the range of a MIDI note
        int midi_note_number = midi_frequency_to_note_number(frequency);
        if (midi_note_number < 0) {
            continue;
        }

        // Determine the duration of the note
        int note_start;
        // Check if this is the start of a new note
        if (i == 0 || midi_note_number != midi_frequency_to_note_number(midi_note_frequency(audio_data[i - 1], max_amplitude, sample_rate))) {
            note_start = i;
        }

        // Check if this is the end of a note
        if (i == num_samples - 1 || midi_note_number != midi_frequency_to_note_number(midi_note_frequency(audio_data[i + 1], max_amplitude, sample_rate))) {
            int note_end = i;
            int note_duration = (note_end - note_start) * 1000 / sample_rate;
            if (note_duration >= MIN_NOTE_DURATION && note_duration <= MAX_NOTE_DURATION) {
                int note_velocity = midi_note_velocity(audio_data, note_start, note_end, max_amplitude);
                MIDIEvent note_on_event = {
                    .delta_time = 0,
                    .status = 0x90,
                    .data = {midi_note_number, note_velocity},
                    .length = 2
                };
                MIDIEvent note_off_event = {
                    .delta_time = note_duration * midi_header.ticks_per_quarter_note / 1000,
                    .status = 0x80,
                    .data = {midi_note_number, 0},
                    .length = 2
                };
                write_midi_event(output_file, &note_on_event);
                write_midi_event(output_file, &note_off_event);
                num_notes++;
            }
        }
    }

    // Close the output file
    fclose(output_file);

    // Free the memory
    free(audio_data);
    free(wav_header);

    printf("Converted %d notes from %s to %s\n", num_notes, argv[1], argv[2]);

    return 0;
}
