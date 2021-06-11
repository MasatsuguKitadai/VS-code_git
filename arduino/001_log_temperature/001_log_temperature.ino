/*
PROGRAM NAME: 001_log_temperature
AUTHER      : Masatsugu Kitadai
DATE        : 2021/4/30
*/

#include <max6675.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include "RTClib.h"
RTC_DS1307 RTC;

int thermoDO = 4;
int thermoCS = 5;
int thermoCLK = 6;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);
int vccPin = 3;
int gndPin = 2;

void setup() {
  Serial.begin(9600);
  // use Arduino pins 
  pinMode(vccPin, OUTPUT); digitalWrite(vccPin, HIGH);
  pinMode(gndPin, OUTPUT); digitalWrite(gndPin, LOW);

  // wait for MAX chip to stabilize
  delay(500);

  // setup time log
   Wire.begin();
    RTC.begin();
  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
}

void loop() {

  // write date
  DateTime now = RTC.now(); 
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(' ');
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.print(" \t");
  
  // write temperature
  Serial.print(thermocouple.readCelsius());
#if ARDUINO >= 100
  Serial.write((byte)0);
#else
  Serial.print(0, BYTE);
#endif
  Serial.print(" C ");
  Serial.println(); 

  // determining the interval
  delay(2000);
}
