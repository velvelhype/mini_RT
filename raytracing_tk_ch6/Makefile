CC=gcc
CFLAGS=-std=c89 -Wall -Wextra -g
LD=gcc
LDFLAGS=-lm
HEADERS=vector_utils.h raytracing.h
OBJS=main.o vector_utils.o raytracing.o

ifeq ($(OS),Windows_NT)
EXESUF=.exe
else
EXESUF=
endif

all :

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

scene%.ppm : scene%$(EXESUF)
	./$< > $@

main.o : main.c $(HEADERS)
vector_utils.o : vector_utils.c vector_utils.h 

scene_setting1.o : scene_setting1.c $(HEADERS)

scene1$(EXESUF) : scene_setting1.o $(OBJS)
	$(LD) $(LDFLAGS) $^ -o $@

.PHONEY : all clean hoge

hoge:
	echo $(OS)

clean :
	rm -f *~ *.o *.ppm scene?$(EXESUF)
