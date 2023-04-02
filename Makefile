CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
LDFLAGS = -lm

all: wav-to-midi

fft.o: fft.c fft.h
	$(CC) $(CFLAGS) -c fft.c

midi.o: midi.c midi.h
	$(CC) $(CFLAGS) -c midi.c

wav-to-midi.o: wav-to-midi.c wavfile.h fft.h midi.h
	$(CC) $(CFLAGS) -c wav-to-midi.c

wavfile.o: wavfile.c wavfile.h
	$(CC) $(CFLAGS) -c wavfile.c

wav-to-midi: wav-to-midi.o wavfile.o fft.o midi.o
	$(CC) $(LDFLAGS) -o wav-to-midi wav-to-midi.o wavfile.o fft.o midi.o

clean:
	rm -f wav-to-midi *.o
