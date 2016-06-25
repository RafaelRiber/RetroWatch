# RetroWatch
 <p align="center">
 <img src="https://raw.githubusercontent.com/RafaelRiber/RetroWatch/master/V1/Hardware/OSHPark%20Renders/front.png" width="400"/>
 <em>Front</em>
 </p>  
 <p align="center">
 <img src="https://raw.githubusercontent.com/RafaelRiber/RetroWatch/master/V1/Hardware/OSHPark%20Renders/back.png" width="400"/>
  <em>Back</em>
 </p>
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
The board design was made in Eagle, has been tested and works. It can be freely modified. It can also directly be ordered on the OSHPark website: 
<p align="center"><a href="https://oshpark.com/shared_projects/3zNSaolF"><img src="https://oshpark.com/assets/badge-5b7ec47045b78aef6eb9d83b3bac6b1920de805e9a0c227658eac6e19a045b9c.png" alt="Order from OSH Park"></img></a></p>

###Bill of Materials:
<p>
<table>
<tr><td><b>Part</b></td><td><b>Value</b></td><td><b>Device</b></td><td><b>Package</b></td><td><b>Description</b></td><td><b></b></td></tr>
<tr><td>C1</td><td>0.1 uF</td><td>C-USC0805</td><td>C0805</td><td>CAPACITOR, American symbol</td><td></td></tr>
<tr><td>C2</td><td>0.1 uF</td><td>C-USC0805</td><td>C0805</td><td>CAPACITOR, American symbol</td><td></td></tr>
<tr><td>C3</td><td>1 uF</td><td>C-USC0805</td><td>C0805</td><td>CAPACITOR, American symbol</td><td></td></tr>
<tr><td>CN1</td><td>JST-PH</td><td>JST_2PIN-SMT-RA</td><td>JST-PH-2-SMT-RA</td><td>JST 2-Pin Connectors of various flavors</td><td></td></tr>
<tr><td>DISP1</td><td>HP QDSP 6064</td><td>7-SEGMENT-4DIGIT-COUNTER-HP-BUBBLE</td><td>DIL12</td><td></td><td></td></tr>
<tr><td>R1</td><td>10k</td><td>R-US_R0805</td><td>R0805</td><td>RESISTOR, American symbol</td><td></td></tr>
<tr><td>R2</td><td>10k</td><td>R-US_R0805</td><td>R0805</td><td>RESISTOR, American symbol</td><td></td></tr>
<tr><td>R3</td><td>220R</td><td>R-US_R0805</td><td>R0805</td><td>RESISTOR, American symbol</td><td></td></tr>
<tr><td>R4</td><td>220R</td><td>R-US_R0805</td><td>R0805</td><td>RESISTOR, American symbol</td><td></td></tr>
<tr><td>R5</td><td>220R</td><td>R-US_R0805</td><td>R0805</td><td>RESISTOR, American symbol</td><td></td></tr>
<tr><td>R6</td><td>220R</td><td>R-US_R0805</td><td>R0805</td><td>RESISTOR, American symbol</td><td></td></tr>
<tr><td>RTC1</td><td>DS3231M</td><td>DS3231M</td><td>SOIC8</td><td>DS3231M Real Time Clock.  Accuracy +/-5ppm.  Battery Backup.  2.3V to 5.5V.</td><td></td></tr>
<tr><td>S1</td><td>SKQGAFE010</td><td>SWITCH-MOMENTARY-2SMD</td><td>TACTILE-SWITCH-SMD</td><td>Various NO switches- pushbuttons, reed, etc</td><td></td></tr>
<tr><td>S2</td><td>SKQGAFE010</td><td>SWITCH-MOMENTARY-2SMD</td><td>TACTILE-SWITCH-SMD</td><td>Various NO switches- pushbuttons, reed, etc</td><td></td></tr>
<tr><td>S3</td><td>SKQGAFE010</td><td>SWITCH-MOMENTARY-2SMD</td><td>TACTILE-SWITCH-SMD</td><td>Various NO switches- pushbuttons, reed, etc</td><td></td></tr>
<tr><td>S4</td><td>SS SMD402</td><td>SWITCH-SPDTSMD2</td><td>SWITCH-SPDT-SMD</td><td>SPDT Switch</td><td></td></tr>
<tr><td>U1</td><td>ATMEGA328P-AU</td><td>ATMEGA328P-AU</td><td>TQFP32</td><td>8-bit Microcontroller with In-System Programmable Flash</td><td></td></tr>
</table>

  
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
