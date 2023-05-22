# Makefile

CC = gcc 
CPPFLAGS = -MMD
CFLAGS = -Wall -Wextra
LDFLAGS =
LDLIBS = -lm -lsndfile -lfftw3 -lfftw3f `pkg-config --libs sdl2 SDL2_image SDL2_ttf` -export-dynamic 

SRC = main.c create_image.c postprocess.c ../../V2/detect.c
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}

main: ${OBJ}

-include DEP

.PHONY: clean

clean:
	${RM} ${OBJ}
	${RM} ${DEP}
	${RM} main

# END
