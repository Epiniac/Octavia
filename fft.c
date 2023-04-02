#include <math.h>
#include "fft.h"

// Private function prototypes
static void swap(double *a, double *b);
static int reverse_bits(int x, int num_bits);

void fft(double *real, double *imag, int n) {
    // Bit-reverse the input
    for (int i = 0; i < n; i++) {
        int j = reverse_bits(i, log2(n));
        if (j > i) {
            swap(&real[i], &real[j]);
            swap(&imag[i], &imag[j]);
        }
    }

    // Perform the FFT
    for (int size = 2; size <= n; size *= 2) {
        int half_size = size / 2;
        double angle = 2 * M_PI / size;
        double w_real = cos(angle);
        double w_imag = sin(angle);
        for (int i = 0; i < n; i += size) {
            double w_curr_real = 1.0;
            double w_curr_imag = 0.0;
            for (int j = i; j < i + half_size; j++) {
                double temp_real = w_curr_real * real[j + half_size] - w_curr_imag * imag[j + half_size];
                double temp_imag = w_curr_real * imag[j + half_size] + w_curr_imag * real[j + half_size];
                real[j + half_size] = real[j] - temp_real;
                imag[j + half_size] = imag[j] - temp_imag;
                real[j] += temp_real;
                imag[j] += temp_imag;
                double w_next_real = w_curr_real * w_real - w_curr_imag * w_imag;
                double w_next_imag = w_curr_real * w_imag + w_curr_imag * w_real;
                w_curr_real = w_next_real;
                w_curr_imag = w_next_imag;
            }
        }
    }
}

static void swap(double *a, double *b) {
    double temp = *a;
    *a = *b;
    *b = temp;
}

static int reverse_bits(int x, int num_bits) {
    int result = 0;
    for (int i = 0; i < num_bits; i++) {
        result <<= 1;
        result |= (x & 1);
        x >>= 1;
    }
    return result;
}
