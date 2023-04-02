#ifndef WAVFILE_H
#define WAVFILE_H

typedef struct {
    char riff[4];
    int overall_size;
    char wave[4];
    char fmt_chunk_marker[4];
    int fmt_chunk_size;
    short format_type;
    short channels;
    int sample_rate;
    int byte_rate;
    short block_align;
    short bits_per_sample;
    char data_chunk_header[4];
    int data_size;
    int subchunk2_size;
} WAVHeader;

WAVHeader* read_wav(FILE *filename);
int write_wav(FILE *filename, WAVHeader *header, double *data, int data_size);

#endif /* WAVFILE_H */
