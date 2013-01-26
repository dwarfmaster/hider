OBJS=main.o options.o
PROG=hider.prog
CXXFLAGS=-Wall -Wextra `pkg-config --cflags hider`
LDFLAGS=`pkg-config --libs hider` -lboost_program_options
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
