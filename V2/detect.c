#include <stdio.h>
#include <string.h>
#include <err.h>
#include <stdlib.h>

#include <sndfile.h>
#include <math.h>
#include <fftw3.h>
#include <unistd.h> 

#define BUFFER_LEN 4096


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


void fft(double* samples, int length, double* spectrum)
{
    for (int i = 0; i < length; i++)
    {
        double real = 0.0;
        double imag = 0.0;
        for (int j = 0; j < length; j++)
        {
            real += samples[j] * cos(2 * M_PI * i * j / length);
            imag -= samples[j] * sin(2 * M_PI * i * j / length);
        }
        spectrum[i] = real * real + imag * imag;
    }
}


void ToSpectrum2(char *wave_file)
{
    FILE* wavefile;
    FILE* outfile;
    wave_header header;
    uint16_t* data;
    double* samples;
    double* spectrum;

    wavefile = fopen(wave_file, "rb");

    fread(&header, sizeof(wave_header), 1, wavefile);

    data = (uint16_t*)malloc(header.subchunk2_size);
    fread(data, header.subchunk2_size, 1, wavefile);
    samples = (double*)malloc(header.subchunk2_size);
    for (int i = 0; i < header.subchunk2_size / 2; i++)
    {
        samples[i] = ((double)(int16_t)data[i]) / 32767.0;
        printf("EST LA\n");
    }
    spectrum = (double *)malloc(header.subchunk2_size/2*sizeof(double));
    
    fft(samples, header.subchunk2_size / 2, spectrum);
    outfile = fopen("new.csv", "w");
    
    for (int i=0; i<header.subchunk2_size/4;i++)
    {
        fprintf(outfile, "%f,", spectrum[i]);
    }
    
    fclose(wavefile);
    fclose(outfile);
    free(data);
    free(samples);
    free(spectrum);
}


void ToSpectrum(char *fichier_wave)
{
    SF_INFO sfinfo;
    SNDFILE* infile = sf_open("audio_file.wav", SFM_READ, &sfinfo);
    
    float* buf = malloc(sfinfo.frames * sizeof(float));
    long numFrames = sf_readf_float(infile, buf, sfinfo.frames);

    int N = sfinfo.frames;
    double* in, * out;
    fftw_plan p;
    in = (double*)fftw_malloc(sizeof(double) * N);
    out = (double*)fftw_malloc(sizeof(double) * N);
    for (int i = 0; i < N; i++) 
    {
        in[i] = buf[i];
        printf("ouioui baguette\n");
    }
    p = fftw_plan_r2r_1d(N, in, out, FFTW_R2HC, FFTW_MEASURE);
    fftw_execute(p);

    double freq, mag;
    int K = N / 2 + 1;
    for (int i = 0; i < K; i++) 
    {
        freq = (double)i / N * sfinfo.samplerate;
        mag = sqrt(out[i] * out[i] + out[N - i - 1] * out[N - i - 1]);
        printf("%.2f Hz %.2f\n", freq, mag);
    }

    fftw_destroy_plan(p);
    fftw_free(in);
    fftw_free(out);
    sf_close(infile);
    free(buf);
}


double TakeFrequency(char* wavefile)
{
    SF_INFO sfinfo;
    SNDFILE* infile = sf_open(wavefile, SFM_READ, &sfinfo);
    if (!infile)
    {
        errx(EXIT_FAILURE, "Error for oppening infile.");
    }

    double buffer[BUFFER_LEN];

    int frames;
    double frequency = 0.0;
    while ((frames = sf_read_double(infile,buffer,BUFFER_LEN))>0)
    {
        fftw_complex* fft_output = fftw_alloc_complex(BUFFER_LEN / 2 + 1);
        fftw_plan plan = fftw_plan_dft_r2c_1d(BUFFER_LEN, buffer, fft_output, FFTW_ESTIMATE);
        fftw_execute(plan);

        double max_magnitude = 0.0;
        int max_index = 0;
        for (int i =0; i<BUFFER_LEN/2+1;i++)
        {
            double magnitude = sqrt(fft_output[i][0] * fft_output[i][0] + fft_output[i][1] * fft_output[i][1]);
            if (magnitude > max_magnitude)
            {
                max_magnitude = magnitude;
                max_index = i;
            }
        }
        frequency += max_index * sfinfo.samplerate / BUFFER_LEN;
        fftw_free(fft_output);
        fftw_destroy_plan(plan);
    }

    frequency /= sfinfo.frames / BUFFER_LEN;
    sf_close(infile);
    printf("Your frequency is: %.2f Hz\n", frequency);
    return frequency; 
}


void ToArray(char *fichier_wave)
{
   FILE *file = fopen(fichier_wave,"rb");
   if (file == NULL)
     {
       errx(1,"Error: Can't open file! \n");
     }
   fseek(file,0,SEEK_END);
   int size = ftell(file);
   fseek(file,0,SEEK_SET);
   char *data = malloc(sizeof(char)*size);
   if (data == NULL)
     {
       errx(1,"Error: malloc(data) \n");
     }
   fread(data,size,1,file);
   fclose(file);

   double max = 0;
   for (size_t i = 0; i<size-1; i++)
     {
       if (max < data[i])
           max = data[i];
       //printf("%d \n",data[i]);
     }
   printf("%f\n",max);
}


int main (int argc, char **argv)
{
  if (argc != 2)
    {
      errx(1,"You must put 2 arguments !\n");
    }
  else
    {
      double frequency, ratio;
      char* notes[] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};

      printf("Detection starting... \n");
      sleep(1);
      frequency = TakeFrequency(argv[1]);

      double a = 440;
      ratio = pow(2.0, 1.0/12.0);
      double a_ratio = frequency/a;
      int n = 12 * log(a_ratio) / log(ratio);
      if (n<0)
      {
      	n += 12;
      }
      n = n % 12;
      printf("The note is %s\n", notes[n]);
      printf("Done! \n");

      return 0;
    }
}
