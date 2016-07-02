//The MIT License (MIT)
//
//Copyright (c) 2016 Rafael Riber
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.

//Include required libraries
#include <Chrono.h>
#include <LightChrono.h>
#include <RTClib.h>
#include <Wire.h>
#include <SevSeg.h>
#include <Pushbutton.h>
#include <EEPROM.h>
#include <avr/wdt.h>

//Define constants
#define BUTTON1 14
#define BUTTON2 15
#define BUTTON3                     16
#define DS3231_I2C_ADDR             0x68
#define DS3231_TEMPERATURE_MSB      0x11
#define DS3231_TEMPERATURE_LSB      0x12

//Init objects
Pushbutton button1(BUTTON1);
Pushbutton button2(BUTTON2);
Pushbutton button3(BUTTON3);
SevSeg sevSeg;
RTC_DS3231 rtc;

Chrono myChrono(Chrono::SECONDS);

//Declare vars
byte temp_msb;
byte temp_lsb;
unsigned long timer;
unsigned int seconds;
unsigned int minutes;
unsigned int hours;
unsigned int months;
unsigned int days;
unsigned int year;
unsigned int doy;
unsigned int dow;
unsigned int woy;
unsigned int time_show;
unsigned long display_time;
unsigned long display_date;
unsigned long temp;
unsigned long deciSecond;
int count = 1;
int addr = 0;
int menu;
int mode;
int watch;
int brightness;
int date;

//Software reset function
void softwareReset(uint8_t prescaller) {
  wdt_enable(prescaller);
  while(1) {}
}

//Get seconds from RTC
unsigned int get_seconds()
{
  DateTime now = rtc.now();
  seconds = now.second();
  return seconds;
}

//Get minutes from RTC
unsigned int get_minutes()
{
  DateTime now = rtc.now();
  minutes = now.minute();
  return minutes;
}

//Get hours from RTC
unsigned int get_hours()
{
  DateTime now = rtc.now();
  hours = now.hour();
  return hours;
}

//Get days from RTC
unsigned int get_days()
{
  DateTime now = rtc.now();
  days = now.day();

  return days;
}

//Get months from RTC
unsigned int get_months()
{
  DateTime now = rtc.now();
  months = now.month();
  return months;
}

unsigned int get_year()
{
  DateTime now = rtc.now();
  year = now.year();
  return year;
}

unsigned int get_doy()
{
  DateTime now = rtc.now();
  doy = now.dayOfYear();
  return doy;
}

unsigned int get_dow()
{
  DateTime now = rtc.now();
  dow = now.dayOfTheWeek();
  return dow;
}

//Show hours and minutes on display
void show_hm()
{
  get_seconds();
  get_minutes();
  get_hours();

  display_time = (hours * 100) + minutes;

  char tempString[10];
  sprintf(tempString, "%04d", display_time);
  sevSeg.DisplayString(tempString, 2);
}

//Show minutes and seconds on display
void show_ms()
{
  get_seconds();
  get_minutes();
  get_hours();

  display_time = (minutes * 100) + seconds;

  char tempString[10];
  sprintf(tempString, "%04d", display_time);
  sevSeg.DisplayString(tempString, 2);
}

//Show date on display
//Show date on display
void show_date()
{
  char tempString[5];
  switch(date)
  {
    case 0:
      get_days();
      get_months();
      display_date = (days * 100) + months;
      sprintf(tempString, "%04d", display_date);
      sevSeg.DisplayString(tempString, 2);
      break;
    case 1:
      get_year();
      sprintf(tempString, "%4d", year);
      sevSeg.DisplayString(tempString, 0);
      break;
    case 2:
      get_doy();
      sprintf(tempString, "%4d", doy);
      sevSeg.DisplayString(tempString, 0);
      break;
    case 3:
      get_dow();
      sprintf(tempString, "%4d", dow);
      sevSeg.DisplayString(tempString, 0);
      break;
    case 4:
      get_doy();
      woy = doy / 7;
      sprintf(tempString, "%4d", woy);
      sevSeg.DisplayString(tempString, 0);
  }
  if (button2.getSingleDebouncedPress())
  {
    date = date - 1;
  }
  if (button3.getSingleDebouncedPress())
  {
    date++;
   }
   if (date < 0)
   {
    date = 4;
   }
   if (date > 4)
   {
    date = 0;
   }
}

//Get temperature from RTC
byte DS3231_get_MSB(){
 Wire.beginTransmission(DS3231_I2C_ADDR);
 Wire.write(DS3231_TEMPERATURE_MSB);
 Wire.endTransmission();

 Wire.requestFrom(DS3231_I2C_ADDR, 1);
 temp_msb = Wire.read();
}
byte DS3231_get_LSB(){

 Wire.beginTransmission(DS3231_I2C_ADDR);
 Wire.write(DS3231_TEMPERATURE_LSB);
 Wire.endTransmission();

 Wire.requestFrom(DS3231_I2C_ADDR, 1);
 temp_lsb = Wire.read() >> 6;
}

//Show temperature on display
void show_temp()
{
  char tempString[10];
  temp_msb = DS3231_get_MSB();
  temp_lsb = DS3231_get_LSB();
  
   switch(temp_lsb)
   {
     case 0:
       temp = (temp_msb*100);
       break;
     case 1 :
       temp = (temp_msb*100) + 25;
       break;
     case 2:
       temp = (temp_msb*100) + 50;
       break;
     case 3:
       temp = (temp_msb*100) + 75;
       break;
   }
  sprintf(tempString, "%04d", temp);
  sevSeg.DisplayString(tempString, 2);
}

void stopwatch()
{
  switch(count)
  {
    case 0:
      char tempString[10];
      if(myChrono.hasPassed(1))
      {
        deciSecond++;
        sprintf(tempString, "%04d", deciSecond);
        if(deciSecond < 10000)
        {
         sevSeg.DisplayString(tempString, 2);
        }
        if(deciSecond >= 10000)
        {
          sevSeg.DisplayString(tempString, 4);
        }
      }
      break;
    case 1:
      sprintf(tempString, "%04d", deciSecond);
      if(deciSecond < 10000)
      {
        sevSeg.DisplayString(tempString, 2);
      }
      if(deciSecond >= 10000)
      {
        sevSeg.DisplayString(tempString, 4);
      }
      break;
  }
  if (button3.getSingleDebouncedPress())
    {
      if (count <= 1)
      {
        count++;
      }
      if (count > 1)
      {
        count = 0;
      }
    }
    if (button2.getSingleDebouncedPress())
    {
      deciSecond = 0;
    }
}

void time()
{
  switch(time_show)
  {
    case 0:
      show_hm();
      break;
    case 1:
      show_ms();
      break;
  }
    if (button2.getSingleDebouncedPress())
  {
    time_show = time_show - 1;
  }
  if (button3.getSingleDebouncedPress())
  {
    time_show++;
   }
   if (time_show < 0)
   {
    time_show = 1;
   }
   if (time_show > 1)
   {
    time_show = 0;
   }
}

//Set brightness and save to EEPROM if different than before
void brightness_set()
{
  char tempString[5];
  sprintf(tempString, "%4d", brightness);
  sevSeg.DisplayString(tempString, 0);

  if (button2.getSingleDebouncedPress())
  {
    brightness = brightness - 1;
  }
  if (button3.getSingleDebouncedPress())
  {
    brightness = brightness + 1;
  }
  if (brightness > 10)
  {
    brightness = 10;
  }
  if (brightness < 0)
  {
    brightness = 0;
  }
  if (button1.getSingleDebouncedPress())
    {
      //Save brightness to EEPROM
      if(brightness != EEPROM.read(0))
      {
        EEPROM.write(0, brightness);
      }
      mode = 7;
      watch = 1;
    }
}

void menu_select()
{
  switch(menu)
  {
    case 0:
      sevSeg.DisplayString("Hour", 0);
      if (button1.getSingleDebouncedPress())
      {
        mode = 0;
        watch = 0;
      }
      break;
    case 1:
      sevSeg.DisplayString("Date", 0);
      if (button1.getSingleDebouncedPress())
      {
        mode = 1;
        watch = 0;
      }
      break;
    case 2:
      sevSeg.DisplayString("Chro", 0);
      if (button1.getSingleDebouncedPress())
      {
        mode = 2;
        watch = 0;
      }
      break;
    case 3:
      sevSeg.DisplayString("Heat", 0);
      if (button1.getSingleDebouncedPress())
      {
        mode = 3;
        watch = 0;
      }
      break;
    case 4:
      sevSeg.DisplayString("Brtx", 0);
      if (button1.getSingleDebouncedPress())
      {
        mode = 4;
        watch = 0;
      }
      break;
    case 5:
      sevSeg.DisplayString("Rstx", 0);
      if (button1.getSingleDebouncedPress())
      {
        mode = 5;
        watch = 0;
      }
      break;
  }
  
  if (button2.getSingleDebouncedPress())
  {
    menu = menu - 1;
  }
  if (button3.getSingleDebouncedPress())
  {
    menu++;
   }
   if (menu < 0)
   {
    menu = 0;
   }
   if (menu > 5)
   {
    menu = 5;
   }
}

void modes()
{
  switch(mode)
  {
    case 0:
      time();
      break;
    case 1:
      show_date();
      break;
    case 2:
      stopwatch();
      break;
    case 3:
      show_temp();
      break;
    case 4:
      brightness_set();
      break;
    case 5:
      softwareReset(WDTO_15MS);
      break;
   }
     if (mode < 0)
   {
    mode = 0;
   }
   if (mode > 5)
   {
    mode = 5;
   }
     if (button1.getSingleDebouncedPress())
     {
       watch++;
       if (watch > 1)
       {
         watch = 0;
       }
   }
}


//Initial setup
void setup()
{
  delay(10);
  rtc.begin();
  timer = millis();

  //Set time if RTC lost power
  if (rtc.lostPower())
  {
    // following line sets the RTC to the date & time this sketch was compiled
    //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time:
    rtc.adjust(DateTime(2016, 6, 27, 19, 15, 0));
  }
  //Init display vars
  int displayType = COMMON_CATHODE;

  int digit1 = 8;
  int digit2 = 5;
  int digit3 = 11;
  int digit4 = 13;

  int segA = 7;
  int segB = 6;
  int segC = 10;
  int segD = 3;
  int segE = 9;
  int segF = 4;
  int segG = 2;
  int segDP = 12;

  int numberOfDigits = 4;

  sevSeg.Begin(displayType, numberOfDigits, digit1, digit2, digit3, digit4, segA, segB, segC, segD, segE, segF, segG, segDP);

  brightness = EEPROM.read(0);
}

//Main loop
void loop()
{ 
  sevSeg.SetBrightness(brightness * 10);
  switch(watch)
  {
    case 0:
      modes();
      break;
    case 1:
      menu_select();
      break;
  }
}
