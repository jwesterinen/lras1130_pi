/*
 * The Game of Life
 * 
 * This is John Conway's classic cellular automaton program for the Matrix.
 * It is based on Lucky Resistor's LRAS1130 library which must be installed.
 * This file is ostensibly an Arduino sketch, but it can be build for and run
 * on an RPi using the lras1130_pi project on github:
 *  https://github.com/jwesterinen/lras1130_pi.
 * It is included in the applications in that project.
 * 
 * The Rules
 *
 *   For a space that is 'populated':
 *     Each cell with one or no neighbors dies, as if by solitude. 
 *     Each cell with four or more neighbors dies, as if by overpopulation. 
 *     Each cell with two or three neighbors survives. 
 *   For a space that is 'empty' or 'unpopulated'
 *     Each cell with three neighbors becomes populated. 
 */

#include "LRAS1130.h"

using namespace lr;

struct LifeFrame : public AS1130Picture24x5
{
    // default constructor
    LifeFrame()
    {}
    
    // explicit data seed constructor
    LifeFrame(const uint8_t* data) : AS1130Picture24x5(data)
    {}

    // copy constructor
    LifeFrame(const LifeFrame& other)
    {
        memcpy((uint8_t*)getData(), other.getData(), 15);
    }

    // seed the frame
    void Seed(int seedQty)
    {
        for (int x = 0; x < getWidth(); x++)
            for (int y = 0; y < getHeight(); y++)
                setPixel(x, y, false);
        for (int n = 0; n < seedQty; n++)
            setPixel(random(getWidth()), random(getHeight()), true);
    }

    // equivalence operator
    bool operator==(LifeFrame& other)
    {
        for (int x = 0; x < getWidth(); x++)
            for (int y = 0; y < getHeight(); y++)
                if (getPixel(x, y) != other.getPixel(x, y))
                    return false;

        return true;
    }

    // return the number of active cells in the surrounding 8
    int NeighborQty(uint8_t x, uint8_t y)
    {
        int qty = 0;
 
        if (x != 0 && y != 0)
            if(getPixel(x-1, y-1))
                qty++;
        if (y != 0)
            if(getPixel(x, y-1))
                qty++;
        if (x != getWidth()-1 && y != 0)
            if(getPixel(x+1, y-1))
                qty++;
        if (x != 0)
            if(getPixel(x-1, y))
                qty++;
        if (x != getWidth()-1)
            if(getPixel(x+1, y))
                qty++;
        if (x != 0 && y != getHeight()-1)
            if(getPixel(x-1, y+1))
                qty++;
        if (y != getHeight()-1)
            if(getPixel(x, y+1))
                qty++;
        if (x != getWidth()-1 && y != getHeight()-1)
            if(getPixel(x+1, y+1))
                qty++;

        return qty;
    }
};

// modify the current frame based on the rules of the game --return true if the
// frames are still changing but not oscillating
bool GetNextFrame(LifeFrame& curFrame)
{
    static LifeFrame lastFrame;
    LifeFrame nextFrame = curFrame;
    bool hasChanged = false, isStable = false;

    // perform changes based on the rules
    for (int x = 0; x < LifeFrame::getWidth(); x++)
    {
        for (int y = 0; y < LifeFrame::getHeight(); y++)
        {
            int neighborQty = curFrame.NeighborQty(x, y);
            if (curFrame.getPixel(x, y))
            {
                if (neighborQty != 2 && neighborQty != 3)
                {
                    // Each cell with one or no neighbors dies, as if by solitude. 
                    // Each cell with four or more neighbors dies, as if by overpopulation. 
                    nextFrame.setPixel(x, y, false);
                    hasChanged = true;
                }
            }
            else
            {
                if (neighborQty == 3)
                {
                    // Each cell with three neighbors becomes populated. 
                    nextFrame.setPixel(x, y, true);
                    hasChanged = true;
                }
            }
        }
    }

    // check to see if the frames are oscillating between two states
    if (lastFrame == nextFrame)
    {
        isStable = true;
    }

    // remember the current frame for a stability check at the next frame
    lastFrame = curFrame;

    // return the next frame
    curFrame = nextFrame;

    // return false if there is no change or if the life frame is stable
    return hasChanged && !isStable;
}

AS1130 ledDriver;

void setup() {
  Wire.begin();
  Serial.begin(115200);
    
  // give the device a chance to initialize
  delay(100); 
  
  // Check if the chip is addressable.
  if (!ledDriver.isChipConnected()) {
    Serial.println(F("Communication problem with chip."));
    Serial.flush();
    return;
  }

  // init and start the device
  ledDriver.setRamConfiguration(AS1130::RamConfiguration1);
  ledDriver.setOnOffFrameAllOff(0);
  ledDriver.setBlinkAndPwmSetAll(0);
  ledDriver.setCurrentSource(AS1130::Current30mA);
  ledDriver.setScanLimit(AS1130::ScanLimitFull);
  ledDriver.startPicture(0);
  ledDriver.startChip();
}

//#define SEED_WITH_EXPLICIT_DATA
const uint8_t seedData[] = {
  0b00000000, 0b00000000, 0b00000000,
  0b00000000, 0b00000000, 0b00000000,
  0b00111000, 0b00000000, 0b00000000,
  0b00000000, 0b00000000, 0b00000000,
  0b00000000, 0b00000000, 0b00000000};


// display the current frame then get the next -- if there are no changes
// or the state is stable reseed the frame and start again
void loop() 
{
#ifdef SEED_WITH_EXPLICIT_DATA
    static LifeFrame frame(seedData);
#else
    static LifeFrame frame;
#endif

    ledDriver.setOnOffFrame(0, frame);
    delay(150);
    if (!GetNextFrame(frame))
    {
        frame.Seed(50);
    }
}

