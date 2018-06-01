C=gcc
CXX=g++
RM=rm -f
CPPFLAGS= -std=c++11
LDFLAGS=
LDLIBS= -lm

SRCS=main.cpp szkola.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: szkola_bin
debug: CPPFLAGS+=-g
debug: LDFLAGS+=-g
debug: szkola_bin

szkola_bin: $(OBJS)
	$(CXX) $(LDFLAGS)  $(OBJS) -o szkola_bin  $(LDLIBS) 

main.o: main.cpp szkola.h lista.h interfejs.cpp

szkola.o: szkola.cpp szkola.h

lista.o: lista.h

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) szkola_bin
