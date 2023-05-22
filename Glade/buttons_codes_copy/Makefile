# Variables
CC = gcc
CFLAGS = -Wall -Wextra `pkg-config --cflags gtk+-3.0 sdl2 SDL2_image SDL2_ttf`
LDFLAGS = `pkg-config --libs gtk+-3.0 sdl2 SDL2_image SDL2_ttf`
LDLIBS = -lm -lsndfile -lfftw3 -lfftw3f `pkg-config --libs sdl2 SDL2_image SDL2_ttf` -export-dynamic
SOURCES = main.c Editor/conv.c Editor/create_image.c Editor/postprocess.c V2/detect.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = mon_programme

# Règles
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) $(LDLIBS) -o $@

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(EXECUTABLE) $(OBJECTS)

# Inclusion des dépendances générées par le compilateur
-include $(OBJECTS:.o=.d)
