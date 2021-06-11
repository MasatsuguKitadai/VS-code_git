/*
PROGRAM NAME: log_temperature_SD_display
AUTHER      : Masatsugu Kitadai
DATE        : 2021/4/30
*/

#include <max6675.h>
#include <Wire.h>
#include <SD.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiAvrI2c.h"
#include <DS3232RTC.h>

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
char filename[20] = "datalog.txt";

// LCD display
#define I2C_ADDRESS 0x3C
SSD1306AsciiAvrI2c oled;

void setup() {
  Serial.begin(9600);
  // use Arduino pins 
  pinMode(vccPin, OUTPUT); digitalWrite(vccPin, HIGH);
  pinMode(gndPin, OUTPUT); digitalWrite(gndPin, LOW);

  // wait for MAX chip to stabilize
  delay(500);

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

  // setup SD card
  Serial.print("Initializing SD card...");
   pinMode(SS, OUTPUT);
 if (!SD.begin(chipSelect))
 {
    Serial.print("Card failed, or not present");
    oled.print("Card failed");
    // 失敗、何もしない
    while(1);
  }
  Serial.println(F("ok."));

  start_hour = hour();
  start_minute = minute();
  start_second = second();
}

void loop() 
{ 
  // Serial
  // write date
  Serial.print(hour());
  Serial.print(':');
  Serial.print(minute());
  Serial.print(':');
  Serial.print(second());
  Serial.println();
  
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
  datafile = SD.open(filename, FILE_WRITE); // 干渉箇所
  
  datafile.print(hour());
  datafile.print(':');
  datafile.print(minute());
  datafile.print(':');
  datafile.print(second());
  datafile.print("\t");
    
  datafile.print(thermocouple.readCelsius());
  
  #if ARDUINO >= 100
  datafile.write((byte)0);
  #else
  datafile.print(0, BYTE);
  #endif
  datafile.print("\t");
  datafile.print("C");
  datafile.println(); 
  
  datafile.close();

 // LCD display
  
  oled.clear();

  oled.print(hour());
  oled.print(" : ");
  oled.print(minute());
  oled.print(" : ");
  oled.print(second());
  oled.println();
    
  oled.print(thermocouple.readCelsius());
  
  #if ARDUINO >= 100
  oled.write((byte)0);
  #else
  oled.print(0, BYTE);
  #endif
  oled.print(" C");
  oled.println();
  
  // determining the interval
  delay(10000);
}
