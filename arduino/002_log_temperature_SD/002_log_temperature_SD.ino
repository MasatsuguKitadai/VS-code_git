/*
PROGRAM NAME: log_temperature_SD
AUTHER      : Masatsugu Kitadai
DATE        : 2021/4/30
*/

#include <max6675.h>
#include <Wire.h>
#include <SD.h>
#include "RTClib.h"
RTC_DS1307 RTC;

// Thermcouple
int thermoDO = 4;
int thermoCS = 5;
int thermoCLK = 6;

// MAX6675
MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);
int vccPin = 3;
int gndPin = 2;

// SD card
const int chipSelect = 10;
char filename[20] = "datalog.dat";

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
  if (! RTC.isrunning())
  {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }

  // setup SD card
  Serial.print("Initializing SD card...");
   pinMode(SS, OUTPUT);
 if (!SD.begin(chipSelect))
 {
    Serial.print("Card failed, or not present");
    // 失敗、何もしない
    while(1);
  }
  Serial.println(F("ok."));
}

void loop() 
{  
  // Serial
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

  // SDcard
  File datafile;
  datafile = SD.open(filename, FILE_WRITE);

  datafile.print(now.year(), DEC);
  datafile.print('/');
  datafile.print(now.month(), DEC);
  datafile.print('/');
  datafile.print(now.day(), DEC);
  datafile.print(' ');
  datafile.print(now.hour(), DEC);
  datafile.print(':');
  datafile.print(now.minute(), DEC);
  datafile.print(':');
  datafile.print(now.second(), DEC);
  datafile.print(" \t");
    
  datafile.print(thermocouple.readCelsius());
  
  #if ARDUINO >= 100
  datafile.write((byte)0);
  #else
  datafile.print(0, BYTE);
  #endif
  datafile.print(" C ");
  datafile.println(); 
  
  datafile.close();
  
  // determining the interval
  delay(3000);
}
