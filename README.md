# RetroWatch
 <p align="center">
 <img src="https://raw.githubusercontent.com/RafaelRiber/RetroWatch/master/V1/Hardware/OSHPark%20Renders/front.png" width="400"/>
 <em>Front</em>
 <p align="center">
 <b>OSHPark renders</b>
 </p>
 
## Short description
A retro watch, based around the HP QDSP-6064 Bubble display, used in 70s HP calculators like the [HP-35](https://en.wikipedia.org/wiki/HP-35). The display is controlled by an Atmel ATMega328P-AU MCU with Arduino code, and the time is kept by a Maxim DS3231 Real-Time Clock module, that stays connected to the LiPo battery at all times, keeping time even when the microcontroller and display are not powered.
The code is open source, licensed under the MIT License, and the harware is fully open-source.

###Featured on:
[Hackaday.com blog post by Elliot Williams](http://hackaday.com/2016/06/25/easy-bubble-watch-oozes-retro-charm/)

[Hackaday.io project page](https://hackaday.io/project/12402-retrowatch)
  
## Hardware
###PCB
The board design was made in Eagle, has been tested and works. A 500 mAh [LiPo Battery from Adafruit](https://adafru.it/1578) fits perfectly under the board. It can be freely modified. It can also directly be ordered on the OSHPark website: 
<p align="center"><a href="https://oshpark.com/shared_projects/3zNSaolF"><img src="https://oshpark.com/assets/badge-5b7ec47045b78aef6eb9d83b3bac6b1920de805e9a0c227658eac6e19a045b9c.png" alt="Order from OSH Park"></img></a></p>

(DISCLAIMER: I am in no way affiliated with Atmel. I just put the Atmel logo on the PCB to show the circuit uses an Atmel chip, which I really like !)

###Bill Of Materials
You can find the BOM [here](https://github.com/RafaelRiber/RetroWatch/blob/master/BOM.md).
  
##Software
The software was written in Arduino code, is licensed under MIT License, and can be uploaded on the microcontroller via ISP.
Be sure to set the desired time in the code prior to uploading, to set the time registers on the RTC.

Functions of the code include:
* Hours, minutes and seconds
* Day and month
* Stopwatch
* Temperature reading from the real-time-clock's built-in thermometer (accurate to about 3°C)
 
To be able to upload the code on the watch, an Arduno IDE board file for an "ATMega328 on a breadboard" running at 8 MHz with the internal crystal, is needed. You can find it here: https://www.arduino.cc/en/Tutorial/ArduinoToBreadboard under "Minimal Circuit (Eliminating the External Clock)"
###Required Libraries
1. [Chrono library by thomasfredericks](https://github.com/thomasfredericks/Chrono)
2. [Pushbutton library from Pololu](http://pololu.github.io/pushbutton-arduino/)
3. [RTCLib by Adafruit Industries](https://github.com/adafruit/RTClib)
4. [SevSeg by SparkFun](https://github.com/sparkfun/SevSeg)

###Planned Sofware Functions
1. Menu structure for mode selection
2. Year
3. Time set on the watch
