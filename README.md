# RetroWatch
<p align="center">
  <img src="https://raw.githubusercontent.com/RafaelRiber/RetroWatch/master/Hardware/OSHPark%20Renders/front.png" width="400"/>
  <em>Front</em>
</p>  
<p align="center">
  <img src="https://raw.githubusercontent.com/RafaelRiber/RetroWatch/master/Hardware/OSHPark%20Renders/back.png" width="400"/>
  <em>Back</em>
</p>
<p align="center">
<b>OSHPark renders</b>
</p>

## Short description
A retro watch, based around the HP QDSP-6064 Bubble display, used in 70s HP calculators like the HP-35. The display is controlled by an Atmel ATMega328P-AU MCU with Arduino code, and the time is kept by a Maxim DS3231 Real-Time Clock module, that stays connected to the LiPo battery at all times, keeping time even when the microcontroller and display are not powered.
The code is open source, licensed under the MIT License, and the harware is fully open-source.

## Hardware
The board design was made in Eagle, and can be freely modified. It can also directly be ordered on OSHPark: 
<p align="center"><a href="https://oshpark.com/shared_projects/3zNSaolF"><img src="https://oshpark.com/assets/badge-5b7ec47045b78aef6eb9d83b3bac6b1920de805e9a0c227658eac6e19a045b9c.png" alt="Order from OSH Park"></img></a></p>

##Software
The software was written in Arduino code, is licensed under MIT License, and can be uploaded on the microcontroller via ISP.
Be sure to set the desired time in the code prior to uploading, to set the time registers on the RTC.
