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

struct Bitmap
{
  bool bitmap[24][5];

  Bitmap()
  {
    Clear();
  }

  void Clear()
  {
    for (int x = 0; x < 24; x++)
      for (int y = 0; y < 5; y++)
        bitmap[x][y] = false;
  }

  // attempt to set the bit in the map
  bool Set(uint8_t x, uint8_t y)
  {
    if (!bitmap[x][y])
    {
      // if not set do so and return true
      bitmap[x][y] = true;
      return true;
    }

    // return false if the bit was already set
    return false;
  }

  // if all bits are set return true
  bool IsFull()
  {
    for (int x = 0; x < 24; x++)
      for (int y = 0; y < 5; y++)
        if (!bitmap[x][y])
          return false;
    return true;
  }
};

AS1130 ledDriver;
typedef AS1130Picture24x5 Picture;
Picture picture;

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

void GetNewPosition(Position &pos)
{
  const uint8_t direction = random(4);
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

void loop() 
{
  static Position pos;
  static Bitmap bitmap;

  if (!bitmap.IsFull())
  {
    if (bitmap.Set(pos.X, pos.Y))
    {
      picture.setPixel(pos.X, pos.Y, true);
      ledDriver.setOnOffFrame(0, picture);
      delay(50);
    }
    GetNewPosition(pos);
  }
  else
  {
    for (int x = 0; x < 24; x++)
      for (int y = 0; y < 5; y++)
        picture.setPixel(x, y, false);
    ledDriver.setOnOffFrame(0, picture);
    bitmap.Clear();
  }
}


