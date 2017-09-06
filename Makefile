TARGET = liblras1130_pi.a

INCLUDES = -I.
CPPFLAGS = $(INCLUDES) -O0 -g -Wall -std=c++11
LFLAGS = -shared

HEADERS = Arduino.h Wire.h serialPi.h utils.h LRAS1130.h LRAS1130Picture12x11.h LRAS1130Picture24x5.h
OBJECTS = main.o wirePi.o serialPi.o ../LRAS1130.o ../LRAS1130Picture12x11.o ../LRAS1130Picture24x5.o 

.PHONY: all
all: $(TARGET)

$(TARGET) : $(OBJECTS)
#	g++ $(LFLAGS) -o $@ $(OBJECTS) $(LIBS)
	ar rcs $@ $(OBJECTS)

%.o: %.cpp $(HEADERS)
	g++ $(CPPFLAGS) -o $@ $<

%.o: ../%.cpp $(HEADERS)
	g++ $(CPPFLAGS) -o $@ $<

.PHONY: clean
clean:
	rm -f $(TARGET) *.o ../*.o

