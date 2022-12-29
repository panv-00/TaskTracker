CPP=g++
PKGS=
CFLAGS=-Wall -O3 -g
LIBS=
VPATH=../src

OBJECTS=     \
	TtString.o \
	TtTime.o   \
	TtDate.o   \
	TtIO.o     \

DEPLIST= \
	TtInclude.h \

default: $(OBJECTS)
	$(CPP) -o ../TaskTracker ../src/TaskTracker.cpp \
		$(OBJECTS) \
		$(CFLAGS) \
		$(LIBS)

%.o: %.cpp %.h $(DEPLIST)
	$(CPP) -c $< -o $*.o $(CFLAGS)
