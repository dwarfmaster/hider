OBJS=main.o
PROG=hider.prog
CXXFLAGS=-Wall -Wextra `sdl-config --cflags` `pkg-config --cflags SDL_image`
LDFLAGS=`sdl-config --libs` `pkg-config --libs SDL_image`
CC=g++

all : $(PROG)

$(PROG) : $(OBJS)
	$(CC) $(CXXFLAGS)    -o $@	$^ $(LDFLAGS)

%.o : %.cpp
	$(CC) $(CXXFLAGS) -c -o $@	$<

clean :
	@touch $(PROG) $(OBJS)
	@rm -v $(PROG) $(OBJS)

rec : clean all

.PHONY: all clean rec

