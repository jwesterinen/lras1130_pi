TARGET = liblras1130_pi.a
LRAS1130_DIR=../LRAS1130

INCLUDES = -I.
CPPFLAGS = $(INCLUDES) -O0 -g -Wall -std=c++11

HEADERS = Arduino.h Wire.h serialPi.h utils.h $(LRAS1130_DIR)/LRAS1130.h $(LRAS1130_DIR)/LRAS1130Picture12x11.h $(LRAS1130_DIR)/LRAS1130Picture24x5.h
OBJECTS = main.o wirePi.o serialPi.o $(LRAS1130_DIR)/LRAS1130.o $(LRAS1130_DIR)/LRAS1130Picture12x11.o $(LRAS1130_DIR)/LRAS1130Picture24x5.o 

.PHONY: all
all: $(TARGET)

$(TARGET) : $(OBJECTS)
	ar rcs $@ $(OBJECTS)

%.o: %.cpp $(HEADERS)
	g++ $(CPPFLAGS) -o $@ $<

%.o: ../%.cpp $(HEADERS)
	g++ $(CPPFLAGS) -o $@ $<

.PHONY: clean
clean:
	rm -f $(TARGET) *.o $(LRAS1130_DIR)/*.o

