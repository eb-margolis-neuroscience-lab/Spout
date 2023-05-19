# Firmware installation  
 1. If you don't already have it, install the [Arduino IDE](https://www.arduino.cc/en/software) which will upload the compiled code to the device. Then follow the [instructions](https://learn.adafruit.com/adafruit-esp32-feather-v2/arduino-ide-setup) on the Adafruit website to install the required libraries for the Huzzah32. 
 2. The real time clock (RTC) will hold the date and time so that data can be aligned with time of day. Follow [these instructions](https://learn.adafruit.com/adafruit-pcf8523-real-time-clock/rtc-with-arduino), except the wiring part, to set the RTC. 
 3. To set the RTC, connect the Spout device to the computer with a microUSB and flash [RTC_PCF8523](https://github.com/eb-margolis-neuroscience-lab/Spout/blob/main/arduino%20code/pcf8523.ino) onto it. The clock will be set based on the time and date on the computer. To check that the clock is set and functioning open the Arduino IDE serial monitor with the device still connected to the computer. If the coin battery gets disconnected at any time, the RTC has to be flashed onto the device again. 
4. Use the Arduino IDE to flash [SpoutCollect](https://github.com/eb-margolis-neuroscience-lab/Spout/blob/main/arduino%20code/SpoutCollectMay2023.ino) onto the device. 
5. Disconnect the device from the computer and insert a micro SD card. 
6. The device is ready to use once the battery is inserted. Click [here](https://github.com/eb-margolis-neuroscience-lab/Spout/blob/main/Spout_Construction_Guide/Spout_Construction_Guide_README.md) to return to the contruction guide. 

## Helpful tutorials for Arduino IDE and C++: 

1. [Arduino IDE basics](https://docs.arduino.cc/software/ide-v1/tutorials/arduino-ide-v1-basics)

2. [Arduino IDE intro tutorial](https://docs.arduino.cc/learn/starting-guide/the-arduino-software-ide) -- This tutorial allows you to learn how to navigate Arduino IDE by creating your own blink program. This is not a needed step for using Spout, it is just a helpful resource for people that are new to Arduino and programming. 

3. [Introduction to C++ on Arduino](https://www.digikey.com/en/maker/blogs/2020/the-basics-of-c-on-an-arduino-part-1-variables)
