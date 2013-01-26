OBJS=main.o
PROG=hider.prog
CXXFLAGS=-Wall -Wextra `pkg-config --cflags hider gtkmm-3.0`
LDFLAGS=`pkg-config --libs hider gtkmm-3.0`
CC=g++

all : $(PROG)

$(PROG) : $(OBJS)
	$(CC) $(CXXFLAGS) -o $@	$^ $(LDFLAGS)

%.o : %.cpp
	$(CC) $(CXXFLAGS) -c -o $@	$<

clean :
	@touch $(PROG) $(OBJS)
	@rm -v $(PROG) $(OBJS)

rec : clean all

.PHONY: all clean rec
