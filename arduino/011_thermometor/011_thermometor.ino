/*
PROGRAM NAME: log_temperature_SD_display
AUTHER      : Masatsugu Kitadai
DATE        : 2021/6/22
*/

#include <Wire.h>
#include <SD.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiAvrI2c.h"
#include <DS3232RTC.h>

/***********************************************************/

// LCD display
#define I2C_ADDRESS 0x3c
SSD1306AsciiAvrI2c oled;

// SD card
const int chipSelect = 10;
char filename[20] = "tmp_log.dat";

// number
int i = 0;

/***********************************************************/

void setup() {
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
  datafile = SD.open(filename, FILE_WRITE);
  datafile.print("start");
  datafile.print('\t');
  datafile.print(year());
  datafile.print("/");
  datafile.print(month());
  datafile.print("/");
  datafile.println(day());
  datafile.close();
}

/***********************************************************/
void loop() { 

    i = i + 1;

    // KP-AM2320
    float humidity = 0.00;
    float temperature = 0.00;

    Wire.beginTransmission(0x5c);
    Wire.write(0x03);
    Wire.write(0x00);
    Wire.write(0x04);
    Wire.endTransmission();  
    delay(1000); // ここにないといけないみたい

    int ans = Wire.requestFrom(0x5c,6);
    while(Wire.available() !=0){   
      int H1,H2,T1,T2 = 0;
      for(int i = 1; i <  ans+1; i++){     
        int c = Wire.read();        
        switch (i){    
          case 5:
          T1 = c;
          break;
          case 6:
          T2 = c; 
          break;
          case 3:
          H1 = c; 
          break;
          case 4: 
          H2 = c;  
          break;
          default:
          break;
        }       
    }      

    humidity = (H1*256 + H2)/10.0; 
    temperature = (T1*256 + T2)/10.0; 
    Serial.print("  Temperature=");
    Serial.print(temperature);
    Serial.print("’C  Humidity=");
    Serial.print(humidity);
    Serial.println("%   ");

    // LCD display
    oled.clear();
    oled.print(month());
    oled.print(" / ");
    oled.print(day());
    oled.print("          ");
    oled.print(hour());
    oled.print(" : ");
    oled.print(minute());
    oled.println();
    
    oled.print(temperature);
    oled.print(" (C)");
    oled.print("   ");
    oled.print(humidity);
    oled.print(" (%)");

    #if ARDUINO >= 100
    oled.write((byte)0);
    #else
    oled.print(0, BYTE);
    #endif
    oled.println();
    
    // SDcard
    File datafile;
    datafile = SD.open(filename, FILE_WRITE); // 干渉箇所

    datafile.print(hour());
    datafile.print(":");
    datafile.print(minute());
    datafile.print('\t');
    
    datafile.print(temperature);
    datafile.print('\t');
    datafile.print(humidity);
    datafile.println();
  
    datafile.close();
    }
}
