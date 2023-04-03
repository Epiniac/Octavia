# Makefile

CC = gcc -g
CPPFLAGS = -MMD
CFLAGS = -Wall -Wextra `pkg-config --cflags sdl2 SDL2_image SDL2_ttf`
LDFLAGS =
LDLIBS = `pkg-config --libs sdl2 SDL2_image SDL2_ttf`

SRC = main.c create_image.c postprocess.c
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}

main: ${OBJ}

-include ${DEP}

.PHONY: clean

clean:
	${RM} ${OBJ}
	${RM} ${DEP}
	${RM} main

# END
