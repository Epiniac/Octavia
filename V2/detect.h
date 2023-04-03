#ifndef DETECT_H
#define DETECT_H

typedef struct wave_header
{
    char chunk_id[4];
    uint32_t chunk_size;
    char format[4];
    char subchunk1_id[4];
    uint32_t subchunk1_size;
    uint16_t audio_format;
    uint16_t num_channels;
    uint32_t sample_rate;
    uint32_t byte_rate;
    uint16_t block_align;
    uint16_t bits_per_sample;
    char subchunk2_id[4];
    uint32_t subchunk2_size;
}wave_header;

void fft(double* samples, int length, double* spectrum);

void ToSpectrum2(char* wave_file);

void ToSpectrum(char* wave_file);

double TakeFrequency(char* wave_file);

void ToArray(char* wave_file);

int return_n(char *p);

#endif
