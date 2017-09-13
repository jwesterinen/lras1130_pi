//
// Lucky Resistor's AS1130 Library
// ---------------------------------------------------------------------------
// (c)2017 by Lucky Resistor. See LICENSE for details.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>
//
#include "LRAS1130.h"

/// @example MovingPixel.ino
/// This is an example how to scroll multiple frames.

using namespace lr;
AS1130 ledDriver;


typedef AS1130Picture24x5 Picture;
struct Pos
{
  Pos(uint8_t x = -1, uint8_t y = -1) : positionX(x), positionY(y)
  {}
  bool operator!=(const Pos& other)
  {
    return (positionX != other.positionX && positionY != other.positionY);
  }
  uint8_t positionX;
  uint8_t positionY;
};
struct CurState
{
  Pos head;
  Pos tail[4];
};
Picture picture;
CurState frame;

void setup() {
    
  // Wait until the chip is ready.
  delay(100); 
  Serial.println(F("Initialize chip"));
  
  // Check if the chip is addressable.
  if (!ledDriver.isChipConnected()) {
    Serial.println(F("Communication problem with chip."));
    Serial.flush();
    return;
  }

  // init the first pixel to be at (0,0)
  frame.head = Pos(0,0);

  // Set-up everything.
  ledDriver.setRamConfiguration(AS1130::RamConfiguration1);
  ledDriver.setOnOffFrameAllOff(0);
  ledDriver.setBlinkAndPwmSetAll(0);
  ledDriver.setCurrentSource(AS1130::Current30mA);
  ledDriver.setScanLimit(AS1130::ScanLimitFull);
  ledDriver.setMovieEndFrame(AS1130::MovieEndWithFirstFrame);
  ledDriver.setMovieFrameCount(4);
  ledDriver.setFrameDelayMs(100);
  ledDriver.setMovieLoopCount(AS1130::MovieLoop6);
  ledDriver.setScrollingEnabled(true);
  ledDriver.startPicture(0);
  
  // Enable the chip
  ledDriver.startChip();
}


void loop() 
{
  Pos nextPos;
  int i;

  picture.setPixel(frame.head.positionX, frame.head.positionY, true);
  for (i = 0; i < 4; i++)
  {
    if (frame.tail[i] != Pos(-1,-1))
    {
      picture.setPixel(frame.tail[i].positionX, frame.tail[i].positionY, true);
    }
  }
  ledDriver.setOnOffFrame(0, picture);
  delay(50);
  picture.setPixel(frame.head.positionX, frame.head.positionY, false);
  for (i = 0; i < 4; i++)
  {
    if (frame.tail[i] != Pos(-1,-1))
    {
      picture.setPixel(frame.tail[i].positionX, frame.tail[i].positionY, false);
    }
  }
  const uint8_t direction = random(4);
  switch (direction) {
  case 0:
    nextPos = frame.head;
    if (frame.head.positionX < Picture::getWidth()-1) 
    {
      nextPos.positionX++;
      //if (nextPos != frame.tail[0])
      {
        //++positionX;
        break;
      }
    }
  case 1:
    nextPos = frame.head;
    if (frame.head.positionY < Picture::getHeight()-1) 
    {
      nextPos.positionY++;
      //if (nextPos != frame.tail[0])
      {
        //++positionY;
        break;
      }
    }
  case 2:
    nextPos = frame.head;
    if (frame.head.positionX > 0) 
    {
      nextPos.positionX--;
      //if (nextPos != frame.tail[0])
      {
        //--positionX;
        break;
      }
    }
  case 3:
    nextPos = frame.head;
    if (frame.head.positionY > 0)
    {
      nextPos.positionY--;
      //if (nextPos != frame.tail[0])
      {
        //--positionY;
        break;
      }
    }
  }
  frame.tail[3] = frame.tail[2];
  frame.tail[2] = frame.tail[1];
  frame.tail[1] = frame.tail[0];
  frame.tail[0] = frame.head;
  frame.head = nextPos;
}


