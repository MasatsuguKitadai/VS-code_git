#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <SD.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiAvrI2c.h"
#include <DS3232RTC.h>

/***********************************************************/

// GPS

static const int RXPin = 8, TXPin = 9;
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

// SD
const int chipSelect = 10;
char filename[20] = "GPSlog.csv";

// LCD display
#define I2C_ADDRESS 0x3C
SSD1306AsciiAvrI2c oled;

/***********************************************************/

void setup()
{
  // setup LCD display
  
  oled.begin(&Adafruit128x32, I2C_ADDRESS);
  oled.setFont(TimesNewRoman16);

  uint32_t m = micros();
  
  // setup GPS
  Serial.begin(9600);
  ss.begin(GPSBaud);

  // setup SD card
  Serial.print("Initializing SD card...");
  oled.println("Initializing SD card...");
   pinMode(SS, OUTPUT);
  if (!SD.begin(chipSelect))
 {
    Serial.print("Card failed, or not present");
    oled.println("Card failed");
    // 失敗、何もしない
    while(1);
  }
  Serial.println(F("ok."));
  oled.println(F("ok."));
  
  File datafile;
  datafile = SD.open(filename, FILE_WRITE);
  datafile.print("latitude,");
  datafile.print("longitude");
  datafile.close();
}

/***********************************************************/


void loop()
{    
  printInt(gps.satellites.value(), gps.satellites.isValid(), 5);
  oled.print("lat :");
  printFloat(gps.location.lat(), gps.location.isValid(), 11, 6);
  oled.print("long :");
  printFloat(gps.location.lng(), gps.location.isValid(), 12, 6);
  Serial.println(); 

  File datafile;
  datafile = SD.open(filename, FILE_WRITE);
  datafile.println();
  datafile.close(); 
  smartDelay(1000);
 
  oled.clear();

  if (millis() > 5000 && gps.charsProcessed() < 10)
    Serial.println(F("No GPS data received: check wiring"));

  
}

// This custom version of delay() ensures that the gps object
// is being "fed".

/***********************************************************/

static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}

/***********************************************************/

static void printFloat(float val, bool valid, int len, int prec)
{
  if (!valid)
  {
    while (len-- > 1)
      Serial.print('*');
    Serial.print(' ');
  }
  else
  {
    File datafile;
    datafile = SD.open(filename, FILE_WRITE);
    
    Serial.print(val, prec);
    
    datafile.print(val, prec);
    
    oled.print(val,prec);
    oled.println();
    
    int vi = abs((int)val);
    int flen = prec + (val < 0.0 ? 2 : 1); // . and -
    flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
    for (int i=flen; i<len; ++i)
      Serial.print(' ');
      datafile.print(',');
      datafile.print('\t');
    datafile.close(); 
  }
  smartDelay(0);
}

/***********************************************************/

static void printInt(unsigned long val, bool valid, int len)
{
  char sz[32] = "*****************";
  if (valid)
    sprintf(sz, "%ld", val);
  sz[len] = 0;
  for (int i=strlen(sz); i<len; ++i)
    sz[i] = ' ';
  if (len > 0) 
    sz[len-1] = ' ';
  Serial.print(sz);
  smartDelay(0);
}

/***********************************************************/
