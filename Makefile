#Author: Matthew Josephson
#Description: Makefile develops a set of rules to determine how to compile
#Oct 4, 2023

# Some settings for the Makefile.
#
# In particular, you might need to adjust WT_BASE to wherever Wt was installed. /usr/local is the default.

CXX=g++
WT_BASE=/usr/local
CXXFLAGS=--std=c++14 -I$(WT_BASE)/include 
LDFLAGS=-L$(WT_BASE)/lib -Wl,-rpath,$(WT_BASE)/lib -lwthttp -lwt



DEPS = wordle.h
OBJS = main.o wordle.o

# Define your source files and target here:
SRC = main.cpp wordle.cpp
TARGET = asn1

# How do we build objects?

%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# How do we build the executable?

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# How do we clean up after ourselves?

clean:
	rm -f $(TARGET) $(OBJS)

