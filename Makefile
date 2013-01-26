OBJS=picture.o hider.o unhider.o
PROG=hider.so
CXXFLAGS=-Wall -Wextra --std=c++11 -g -fPIC
LDFLAGS=-lboost_filesystem -lboost_program_options -lboost_system -shared
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

