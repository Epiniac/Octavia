#include <stdio.h>
#include <stdlib.h>
#include "wavfile.h"

WAVHeader* read_wav(FILE* fp) {
    WAVHeader* header = (WAVHeader*)malloc(sizeof(WAVHeader));
    if (!header) {
        return NULL;
    }

    // Read the header
    fread(header, sizeof(WAVHeader), 1, fp);

    // Check that the header is valid
    if (header->chunk_id != 0x46464952 ||
        header->format != 0x45564157 ||
        header->subchunk1_id != 0x20746D66 ||
        header->audio_format != 1 ||
        header->subchunk1_size != 16 ||
        header->byte_rate != header->sample_rate * header->num_channels * (header->bits_per_sample / 8) ||
        header->block_align != header->num_channels * (header->bits_per_sample / 8) ||
        header->subchunk2_id != 0x61746164 ||
        header->subchunk2_size <= 0) {
        free(header);
        return NULL;
    }

    return header;
}

int write_wav(FILE* fp, const WAVHeader* header, const short* data) {
    if (!header || !data) {
        return -1;
    }

    // Write the header
    fwrite(header, sizeof(WAVHeader), 1, fp);

    // Write the audio data
    fwrite(data, sizeof(short), header->subchunk2_size / sizeof(short), fp);

    return 0;
}
