#
# Makefile: Build and clean the program
# Copyright (C) 2011  Matt Miller
#
# Based on example from:
# http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/

#IDIR =../include
CC=gcc
#CFLAGS=-I$(IDIR)
CFLAGS=-Wall -g

ODIR=obj
#LDIR =../lib

#LIBS=-lm
LIBS=

DIR=c_oo
NAME=$(DIR)

#_DEPS = hellomake.h
#DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))
DEPS = base1.h common.h base1_friend.h base2.h base2_friend.h \
       derived1.h derived1_friend.h derived2.h

_OBJ = base1.o test_$(NAME).o base2.o common.o derived1.o derived2.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

test_$(NAME): $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean tar doc

clean:
	rm -f test_$(NAME) $(ODIR)/*.o *~ core 

doc:
	doxygen
	cd doc/latex; pdflatex refman.tex

tar:
	tar -czvhf $(NAME).tar.gz ../$(NAME) --exclude *.swp --exclude *.o \
        --exclude test_$(NAME) --exclude $(NAME).tar.gz
