#include <stdio.h>
#include <string.h>
#include <err.h>
#include <stdlib.h>

#include <math.h>
//#include <fftw.h>

#define N 1024
#define Fs 10000

int fourier(void)
{
  double signal[N];
  for(int i=0i<N;i++)
    {
      signal[i] = sin(2.0*M_PI*1000*i/Fs) + 0.5*sin(2.0*M_PI*2000*i/Fs);
    }
  fftw_complex* out =fftw_malloc(sizeof(fftw_complex)*N);
  fftw_plan plan = fftw_plan_dft_r2c_1d(N,signal,out,FFTW_ESTIMATE);
  fftw_execute(plan);
  for(int i =0; i<N/2+1,i++)
    {
      double freq = i*Fs/N;
      double mag = sqrt(out[i][0]*out[i][0]+out[i][1]*out[i][1]);
      printf(%lf,%lf,freq,mag);
    }

  fftw_destro_plan(plan);
  fftw_free(out);

  return 0;
}



void ToArray(char *fichier_wave)
{
   FILE *file = fopen(fichier_wave,"rb");
   if (file == NULL)
     {
       errx(1,"Can't open file! \n");
     }
   fseek(file,0,SEEK_END);
   int size = ftell(file);
   fseek(file,0,SEEK_SET);
   char *data = malloc(sizeof(char)*size);
   if (data == NULL)
     {
       errx(1,"Data is NULL ! \n");
     }
   fread(data,size,1,file);
   fclose(file);
   for (size_t i = 0; i<size-1; i++)
     {
       printf("%d \n",data[i]);
     }
   //printf("%s\n",data);
}



int main (int argc, char **argv)
{
  if (argc != 2)
    {
      errx(1,"You must put 2 arguments !\n");
    }
  else
    {
      ToArray(argv[1]);
      return 0;
    }
}
