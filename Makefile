OBJS=picture.o hider.o
PROG=hider.so
CXXFLAGS=-Wall -Wextra --std=c++11 -g -fPIC
LDFLAGS=-lboost_filesystem -lboost_program_options -lboost_system -shared
CC=g++

DEST=/home/luc/libs
INCSDIR=/home/luc/includes
PCDIR=/usr/lib/pkgconfig
PCFILE=hider.pc

all : $(PROG)

$(PROG) : $(OBJS)
	$(CC) $(CXXFLAGS)    -o $@	$^ $(LDFLAGS)

%.o : %.cpp
	$(CC) $(CXXFLAGS) -c -o $@	$<

clean :
	@touch $(PROG) $(OBJS)
	@rm -v $(PROG) $(OBJS)

rec : clean all

install : $(PROG)
	@cp -v $(PROG) $(DEST)
	@cp -v *.hpp $(INCSDIR)
	@sudo cp -v $(PCFILE) $(PCDIR)

uninstall :
	@touch $(DEST)/$(PROG) $(INCSDIR)
	@rm -v $(DEST)/$(PROG)
	@sudo rm -v $(PCDIR)/$(PCFILE)

reinstall : uninstall install

recinstall : uninstall rec install

.PHONY: all clean rec install uninstall reinstall recinstall

