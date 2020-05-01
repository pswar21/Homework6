#
# UTD CS3377 CDK
# Priyanshu Swar
# pxs170020@utdallas.edu
# NETID: 170020
# Date: 4/29/2020
# Section : 3377.502 2020 Spring 
# This is a Makefile for the matrix. 

CXX = g++
CXXFLAGS =
CPPFLAGS = -Wall -g -I/scratch/perkins/include
LDFLAGS = -L/scratch/perkins/lib
LDLIBS = -lcdk -lcurses

# Executable Name
EXECFILE = cdkexample

# Auto include all .cc files
SOURCES := $(wildcard *.cc)
OBJS = $(SOURCES:.cc=.o)

# Rely on implicit rules for compilation

all: $(EXECFILE)

clean:
	rm -f $(OBJS) $(EXECFILE) *~ \#*


$(EXECFILE): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS) $(LDLIBS)

