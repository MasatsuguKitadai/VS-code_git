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

/***********************************************************/

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

// setting
int i = 0;
int s = 0;
int t = 0;
int k = 0;

/***********************************************************/

void setup() {
  Serial.begin(9600);

  // setup MAX6675
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
  // SDcard
  File datafile;
  datafile = SD.open(filename, FILE_WRITE); // 干渉箇所
  datafile.print("(start) ");
  datafile.print(year());
  datafile.print("/");
  datafile.print(month());
  datafile.print("/");
  datafile.print(day());
  datafile.print(" ");
  datafile.print(hour());
  datafile.print(":");
  datafile.print(minute());
  datafile.print(":");
  datafile.print(second());
  datafile.println();
  datafile.close();
}

/***********************************************************/

void loop() 
{ 
  i = i + 1;
  s = s + 1;
  t = s / 60;

  if (i < 60)
  {
    // Serial
    Serial.print(hour());
    Serial.print(":");
    Serial.print(minute());
    Serial.print(":");
    Serial.print(second());
    Serial.print("\t");
    Serial.print(s);
    Serial.println();

    // LCD display
    oled.clear();
/*
    oled.print(month());
    oled.print(" / ");
    oled.print(day());
    oled.print(" ");
    oled.print(hour());
    oled.print(" : ");
    oled.print(minute());
    oled.print(" : ");
    oled.print(second());
    oled.println();
*/
    oled.print(t);
    oled.print(" min");
    oled.print(" / ");
    oled.print(i);
    oled.print(" sec");
    oled.println();
    
    oled.print(thermocouple.readCelsius());
  
    #if ARDUINO >= 100
    oled.write((byte)0);
    #else
    oled.print(0, BYTE);
    #endif
    oled.print(" C");
    oled.println();
  }
  
  else
  {
    i = 0;

    Serial.print(hour());
    Serial.print(":");
    Serial.print(minute());
    Serial.print(":");
    Serial.print(second());
    Serial.print("\t");
    Serial.print(s);
    Serial.println();
    
    // LCD display
    oled.clear();
  /*  
    oled.print(month());
    oled.print(" / ");
    oled.print(day());
    oled.print(" ");
    oled.print(hour());
    oled.print(" : ");
    oled.print(minute());
    oled.print(" : ");
    oled.print(second());
    oled.println();
*/
    oled.print(t);
    oled.print(" min");
    oled.print(" / ");
    oled.print(i);
    oled.print(" sec");
    oled.println();
    
    oled.print(thermocouple.readCelsius());
  
    #if ARDUINO >= 100
    oled.write((byte)0);
    #else
    oled.print(0, BYTE);
    #endif
    oled.print(" C");
    oled.println();
    
    // SDcard
    File datafile;
    
    datafile = SD.open(filename, FILE_WRITE);
    datafile.print(k);
    datafile.print("\t");
    datafile.print(thermocouple.readCelsius());
    datafile.println();
  
    datafile.close();
    
    k = k + 1;
  }
   
   // determining the interval
  delay(970);
}
