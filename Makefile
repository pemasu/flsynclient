PROG = flsynclient
SOURCES =  UImain.c main.c
LIBS = `fltk-config --ldflags`

CFLAGS = -O2
#comando compilatore e linker (gcc o g++)
CC = g++

OBJSS  = $(SOURCES:.cpp=.o)
OBJS = $(OBJSS:.c=.o)

all: depend $(PROG)

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(CFLAGS) $(OBJS) $(LIBS)
	
.PHONY: clean depend install .depend
	
clean: 
	rm -f $(PROG) $(OBJS) .depend

depend:
	$(CC) -MM $(SOURCES) >.depend
	
install:
	cp ./$(PROG) /usr/bin/
	cp ./flsynclient.xpm /usr/share/pixmaps/
	cp ./flsynclient.png /usr/share/pixmaps/

ifeq ($wildcard .depend, .depend)
include .depend
endif
