LRAS1130_PI

This project allows applications that are written for the Boldport Club's "Matrix"
board controlled by Arduino using Lucky Resistor's awesome LRAS1130 API, to be 
run on a board that is controlled by a Raspberry Pi, with absolute NO modification 
to the original LRAS1130 project or applications.  LRAS1130_PI provides an Arduino-like 
framework that works along with the original LRAS1130 project. The current 
version provides "Wire" and "Serial" libraries (based on the fantastic "wiringPi"
library) that run on the Pi.  You will need both the wiringPi library and Lucky
Resistor's LRAS1130 API project.

Procedure:

 1.  Install the wiringPi library.  You can get it and instructions on how to 
     install it at wiringpi.com.

 2.  Clone Lucky Resistor's LRAS1130 project:
       git clone https://github.com/LuckyResistor/LRAS1130

 3.  Clone the lras1130_pi project:
       git clone https://github.com/jwesterinen/lras1130_pi

 4.  Build the lras1130_pi library:
       cd lras1130_pi
       make

 5.  Build and run any of the example applications, e.g. MovingPixel:
       cd ../LRAS1130/examples/MovingPixel
       cp ../../../lras1130_pi/applications/build .
       ./build
       ./MovingPixel

 6.  Create an application of you own using the Lucky Resistor API:
       cd applications
       <create a directory and source file (must be the same name)>
       cd <new directory>
       cp ../build .
       ./build
       ./<application name>
