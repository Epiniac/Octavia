# Variables
CC = gcc
CFLAGS = -Wall -Wextra `pkg-config --cflags gtk+-3.0 sdl2 SDL2_image SDL2_ttf gstreamer-1.0`
LDFLAGS = `pkg-config --libs gtk+-3.0 sdl2 SDL2_image SDL2_ttf gstreamer-1.0`
LDLIBS = -lm -lsndfile -lfftw3 -lfftw3f `pkg-config --libs sdl2 SDL2_image SDL2_ttf gstreamer-1.0` -export-dynamic
SOURCES = main.c buttons_codes_copy/Editor/conv.c buttons_codes_copy/Editor/postprocess.c buttons_codes_copy/download.c buttons_codes_copy/new.c buttons_codes_copy/quit.c buttons_codes_copy/delete.c buttons_codes_copy/convert.c ../V2/detect.c buttons_codes_copy/record.c 
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
