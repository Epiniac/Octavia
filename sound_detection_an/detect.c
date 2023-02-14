#include <stdio.h>
#include <string.h>
#include <err.h>
#include <stdlib.h>


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
