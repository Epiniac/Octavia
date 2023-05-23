#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define BUFFER_SIZE 1024

typedef struct {
    int sample_rate;
    int bit_depth;
    int num_channels;
    int num_samples;
    int *data;
} WaveFile;

// Function to read wave file
WaveFile *read_wave_file(char *filename) {
    FILE *fp;
    WaveFile *wave_file;

    fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("Error: Failed to open wave file %s\n", filename);
        return NULL;
    }

    wave_file = (WaveFile *)malloc(sizeof(WaveFile));
    if (wave_file == NULL) {
        printf("Error: Failed to allocate memory for wave file\n");
        return NULL;
    }

    char chunk_id[4];
    int chunk_size;
    char format[4];
    char subchunk1_id[4];
    int subchunk1_size;
    short audio_format;
    short num_channels;
    int sample_rate;
    int byte_rate;
    short block_align;
    short bit_depth;
    char subchunk2_id[4];
    int subchunk2_size;

    fread(chunk_id, sizeof(char), 4, fp);
    fread(&chunk_size, sizeof(int), 1, fp);
    fread(format, sizeof(char), 4, fp);
    fread(subchunk1_id, sizeof(char), 4, fp);
    fread(&subchunk1_size, sizeof(int), 1, fp);
    fread(&audio_format, sizeof(short), 1, fp);
    fread(&num_channels, sizeof(short), 1, fp);
    fread(&sample_rate, sizeof(int), 1, fp);
    fread(&byte_rate, sizeof(int), 1, fp);
    fread(&block_align, sizeof(short), 1, fp);
    fread(&bit_depth, sizeof(short), 1, fp);
    fread(subchunk2_id, sizeof(char), 4, fp);
    fread(&subchunk2_size, sizeof(int), 1, fp);

    wave_file->sample_rate = sample_rate;
    wave_file->bit_depth = bit_depth;
    wave_file->num_channels = num_channels;
    wave_file->num_samples = subchunk2_size / (bit_depth / 8);
    wave_file->data = (int *)malloc(wave_file->num_samples * sizeof(int));

    int i, j;
    char buffer[BUFFER_SIZE];
    for (i = 0; i < wave_file->num_samples; i++) {
        fread(buffer, sizeof(char), bit_depth / 8, fp);
        int value = 0;
        for (j = bit_depth / 8 - 1; j >= 0; j--) {
            value = (value << 8) + (unsigned char)buffer[j];
        }
        wave_file->data[i] = value;
    }

    fclose(fp);
    return wave_file;
}

// Function to free wave file
void free_wave_file(WaveFile *wave_file) {
    free(wave_file->data);
    free(wave_file);
}

// Function to perform FFT
void fft(double *input, double *output, int num_samples) {
    if (num_samples == 1) {
        output[0] = input[0];
        return;
    }
    double I[num_samples];
    double *even_input = (double *)malloc(num_samples / 2 * sizeof(double));
    double *odd_input = (double *)malloc(num_samples / 2 * sizeof(double));
    double *even_output = (double *)malloc(num_samples / 2 * sizeof(double));
    double *odd_output = (double *)malloc(num_samples / 2 * sizeof(double));

    int i;
    for (i = 0; i < num_samples / 2; i++) {
        even_input[i] = input[2 * i];
        odd_input[i] = input[2 * i + 1];
    }

    fft(even_input, even_output, num_samples / 2);
    fft(odd_input, odd_output, num_samples / 2);

    for (i = 0; i < num_samples / 2; i++) {
        double angle = -2 * M_PI * i / num_samples;
        double complex_factor = cos(angle) + sin(angle) * I[i];
        output[i] = even_output[i] + complex_factor * odd_output[i];
        output[num_samples - i] = even_output[i] - complex_factor * odd_output[i];
    }

    //free(even_input);
    //free(odd_input);
    //free(even_output);
    //free(odd_output);
}

// Function to detect notes
void detect_notes(WaveFile *wave_file) {
    int i, j;
    int num_samples = wave_file->num_samples;
    int sample_rate = wave_file->sample_rate;
    int bit_depth = wave_file->bit_depth;
    int num_channels = wave_file->num_channels;

    int num_notes = 0;
    int *notes = (int *)malloc(num_samples * sizeof(int));

    // Perform FFT on each channel
    for (i = 0; i < num_channels; i++) {
        double *input = (double *)malloc(num_samples * sizeof(double));
        double *output = (double *)malloc(num_samples * sizeof(double));
        double max_frequency = 0;
        int max_index = 0;

        // Normalize samples to [-1, 1]
        for (j = 0; j < num_samples; j++) {
            input[j] = wave_file->data[j * num_channels + i] / pow(2, bit_depth - 1);
        }
	
        // Perform FFT
        fft(input, output, num_samples);

        // Find the frequency with maximum amplitude
        for (j = 0; j < num_samples / 2; j++) {
            double frequency = (double)j * sample_rate / num_samples;
            double amplitude = sqrt(output[j] * output[j] + output[num_samples - j] * output[num_samples - j]);
            if (amplitude > max_frequency) {
                max_frequency = amplitude;
                max_index = j;
            }
        }

        // Add note to the array if frequency is above a certain threshold
        if (max_frequency > 0.1) {
            notes[num_notes++] = max_index;
        }

	free(input);
	free(output);
    }

    	
    // Print detected notes
    printf("Detected notes: ");
    for (i = 0; i < num_notes; i++) {
        double frequency = (double)notes[i] * sample_rate / num_samples;
        printf("%0.2fHz ", frequency);
    }
    printf("\n");

    free(notes);
}

int main(int argc, char** argv)
{
    printf("Starting...\n");
    WaveFile *wave_file = read_wave_file(argv[1]);
    detect_notes(wave_file);
    free_wave_file(wave_file);
    printf("Done! \n");
    return 0;
}


