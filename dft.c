#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "wavfile.h"
#include "fft.h"

#define PI 3.14159265358979323846

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        exit(1);
    }
   
    char *filename = argv[1];
    int num_samples;
    short *samples = read_wav(filename, &num_samples);
    if (samples == NULL) {
        printf("Error: Failed to read input file.\n");
        exit(1);
    }
   
    // Apply the DFT to the input samples
    int num_freqs = num_samples / 2 + 1;
    double *real = (double *)malloc(num_freqs * sizeof(double));
    double *imag = (double *)malloc(num_freqs * sizeof(double));
    dft(samples, num_samples, real, imag);
   
    // Compute the magnitude spectrum
    double *mag = (double *)malloc(num_freqs * sizeof(double));
    for (int i = 0; i < num_freqs; i++) {
        mag[i] = sqrt(real[i]*real[i] + imag[i]*imag[i]);
    }
   
    // Print the magnitude spectrum
    printf("Frequency (Hz)\tMagnitude\n");
    for (int i = 0; i < num_freqs; i++) {
        double freq = i * 44100.0 / num_samples;
        printf("%f\t%f\n", freq, mag[i]);
    }
   
    free(samples);
    free(real);
    free(imag);
    free(mag);
   
    return 0;
}
