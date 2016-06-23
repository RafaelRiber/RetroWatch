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
unsigned long display_time;
unsigned long display_date;
unsigned long temp;
long deciSecond;
int mode;
int count = 1;

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
void show_date()
{
  char tempString[10];
  get_days();
  get_months();

  display_date = (days * 100) + months;

  sprintf(tempString, "%04d", display_date);
  sevSeg.DisplayString(tempString, 2);
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
}

//Initial setup
void setup()
{
  delay(10);
  timer = millis();

  //Set time if RTC lost power
  if (rtc.lostPower())
  {
    // following line sets the RTC to the date & time this sketch was compiled
    //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time:
    rtc.adjust(DateTime(2016, 6, 21, 16, 3, 0));
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

  sevSeg.SetBrightness(100);

  for (int i = 0; i < 50; i++)
  {
    sevSeg.DisplayString("rexx", 0);
  }

  for (int i = 0; i < 50; i++)
  {
    sevSeg.DisplayString("xtro", 0);
  }

  for (int i = 0; i < 50; i++)
  {
    sevSeg.DisplayString("xISx", 0);
  }

  for (int i = 0; i < 50; i++)
  {
    sevSeg.DisplayString("COOL", 0);
  }

}

//Main loop
void loop()
{
  switch(mode){
    case 0:
      show_hm();
      if (button1.getSingleDebouncedPress())
      {
        for (int i = 0; i < 250; i++)
        {
          show_date();
        }
      }
      break;
    case 1:
      show_ms();
      if (button2.getSingleDebouncedPress())
      {
        for (int i = 0; i < 250; i++)
        {
          show_temp();
        }
      }
      break;
    case 2:
      stopwatch();
      break;
    default:
      show_hm();
      break;
  }
  
  if (millis() - timer >= 5)
  {
    if (button1.getSingleDebouncedPress())
    {
      deciSecond = 0;
      mode = 0;
      count = 1;
    }
    if (button2.getSingleDebouncedPress())
    {
      deciSecond = 0;
      mode = 1;
      count = 1;
    }
    if (button3.getSingleDebouncedPress())
    {
      mode = 2;
    }
  }
}
