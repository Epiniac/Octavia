CC = gcc
CFLAGS = -lm -lsndfile -lfftw3 -lfftw3f
TARGET = main

all: $(TARGET)

$(TARGET): detect.c
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f $(TARGET) *.o
