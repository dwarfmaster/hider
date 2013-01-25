OBJS=main.o options.o picture.o hider.o unhider.o
PROG=hider.prog
CXXFLAGS=-Wall -Wextra --std=c++11 -g
LDFLAGS=-lboost_filesystem -lboost_program_options -lboost_system
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

