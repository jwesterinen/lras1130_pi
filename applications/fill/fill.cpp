#include "LRAS1130.h"

using namespace lr;

struct Position
{
    uint8_t X;
    uint8_t Y;

    Position(uint8_t x = 0, uint8_t y = 0) : X(x), Y(y)
    {}
    bool operator!=(const Position& rhs)
    {
        return (X != rhs.X && Y != rhs.Y);
    }
};

struct Picture : public AS1130Picture24x5
{
  Picture()
  {}

  bool Set(const Position& pos, bool state)
  {
    if (getPixel(pos.X, pos.Y) != state)
    {
      // if not set to the given do so and return true
      setPixel(pos.X, pos.Y, state);
      return true;
    }

    // return false if the bit was already set to the given state
    return false;
  }

  // if all bits are set to the given state return true
  bool IsFull(bool state)
  {
    for (int x = 0; x < Picture::getWidth(); x++)
      for (int y = 0; y < Picture::getHeight(); y++)
        if (getPixel(x, y) != state)
          return false;
    return true;
  }
};

AS1130 ledDriver;
bool isRandom;

void setup() {
  Wire.begin();
  Serial.begin(115200);
    
    // check for arguments
    isRandom = (g_argc > 1) ? true : false;
        
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

void GetNewPosition(Position &pos)
{
  const uint8_t direction = random(4);

  if (isRandom)
  {
    pos.X = random(24);
    pos.Y = random(5);
  }
  else
  {
    switch (direction) 
    {
      case 0:
        if (pos.X < Picture::getWidth()-1) 
        {
          ++pos.X;
        }
        break;
      case 1:
        if (pos.Y < Picture::getHeight()-1) 
        {
          ++pos.Y;
        }
        break;
      case 2:
        if (pos.X > 0) 
        {
          --pos.X;
        }
        break;
      case 3:
        if (pos.Y > 0) 
        {
          --pos.Y;
        }
        break;
    }
  }
}

void loop() 
{
  static Position pos;
  static Picture picture;
  static bool state = true;

  if (!picture.IsFull(state))
  {
    if (picture.Set(pos, state))
    {
      ledDriver.setOnOffFrame(0, picture);
      delay(50);
    }
    GetNewPosition(pos);
  }
  else
  {
    state = !state;
  }
}


