CC=gcc
CPPFLAGS= -MMD
CFLAGS= 
LDFLAGS=
LDLIBS=

SRC= record.c
DEP= ${SRC:.c=.d}	
PRG= ${SRC:.c=}

all: ${PRG}

-include ${DEP}

clean:
	rm -f *.o
	rm -f ${DEP}
	rm -f ${PRG}

