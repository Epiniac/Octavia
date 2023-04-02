CC = gcc
CFLAGS = -lm
TARGET = main

all: $(TARGET)

$(TARGET): main_program.c
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f $(TARGET) *.o
