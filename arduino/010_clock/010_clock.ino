/*
PROGRAM NAME: clock
AUTHER      : Masatsugu Kitadai
DATE        : 2021/4/30
*/

#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiAvrI2c.h"
#include <DS3232RTC.h>

// LCD display
#define I2C_ADDRESS 0x3C
SSD1306AsciiAvrI2c oled;

void setup(){
  Serial.begin(9600);
  
  // setup time log 
  Wire.begin();
  Serial.begin(9600);
  setSyncProvider(RTC.get);   // the function to get the time from the RTC
  if(timeStatus() != timeSet)
    Serial.println("Unable to sync with the RTC");
  else
    Serial.println("RTC has set the system time");

  // setup LCD display
  
  oled.begin(&Adafruit128x32, I2C_ADDRESS);
  oled.setFont(TimesNewRoman16);

  uint32_t m = micros();

  oled.clear();
}

void loop() 
{ 
  // Serial
  // write date
  Serial.print(year());
  Serial.print('/');
  Serial.print(month());
  Serial.print('/');
  Serial.print(day());
  Serial.print('\t');
  Serial.print(hour());
  Serial.print(':');
  Serial.print(minute());
  Serial.print(':');
  Serial.print(second());
  Serial.println();

 // LCD display
  
  oled.clear();
  oled.print(year());
  oled.print(" / ");
  oled.print(month());
  oled.print(" / ");
  oled.print(day());
  oled.println();
  oled.print(hour());
  oled.print(" : ");
  oled.print(minute());
  oled.print(" : ");
  oled.print(second());
  
  // determining the interval
  delay(1000);
}
