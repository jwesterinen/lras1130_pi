TARGET = windchime

INCLUDE_DIRS = -I../../.. -I../.. -I../../lras1130_pi
CPPFLAGS = $(INCLUDE_DIRS) -O0 -g -Wall -std=c++11 -c

LIB_DIRS = -L../.. -L../../lras1130_pi
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


