# This is a generic make file for an lras1130_pi application.
#
# There is no default project name, and the default directory for the LRAS1130
# project is ../LRAS1130.  These can be changed by either editing the make file
# or by setting these variables on the make command line, as follows:
#     make [clean] [TARGET=<project name>] [LRAS1130_DIR=<relative path>]
#
# Note that this make file will work for both LRAS1130 project examples OR
# lras1130_pi applications.  The source files can be either .ino (Arduino
# sketch) or .cpp files.

TARGET =
LRAS1130_DIR = ../../../LRAS1130
LRAS1130_PI_DIR = ../../../lras1130_pi

INCLUDE_DIRS = -I../.. -I$(LRAS1130_DIR) -I$(LRAS1130_PI_DIR)
CPPFLAGS = $(INCLUDE_DIRS) -O0 -g -Wall -std=c++11 -c

LIB_DIRS = -L$(LRAS1130_PI_DIR)
LIBS = -llras1130_pi -lwiringPi
LDFLAGS = $(LIB_DIRS) $(LIBS)

OBJECTS = $(TARGET).o

.PHONY: all
all: $(TARGET)

$(TARGET) : $(OBJECTS)
	g++ -o $@ $< $(LDFLAGS)

%.cpp: %.ino
	cp $< $@

.PHONY: clean
clean:
	rm -f $(TARGET) *.o 


