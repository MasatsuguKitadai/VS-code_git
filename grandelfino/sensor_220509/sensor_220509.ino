/*
PROGRAM NAME: Aero_sesors
DATE        : 2022/5/09
*/

#include <Arduino.h>
#include <Wire.h>
#include <SD.h>
#include <Omron_D6FPH.h>
#include <DS3232RTC.h>

// D6FPH
Omron_D6FPH mySensor;

// Load-cell
int value0, value1, value2, value3;
double dv0, dv1, dv2, dv3;

// SD card
DS3232RTC RTC;
const int chipSelect = 10;
char filename[60];

void setup() {

    Serial.begin(115200);
    Wire.begin();

    // time log 
    RTC.begin();
    setSyncProvider(RTC.get);   // the function to get the time from the RTC
    if(timeStatus() != timeSet)
      Serial.println("Unable to sync with the RTC");
    else
      Serial.println("RTC has set the system time");

    //  D6FPH setup
    mySensor.begin(MODEL_0025AD1); // 型番指定 0025AD1

    //  Load-cell setup
    pinMode(A0, INPUT);
    pinMode(A1, INPUT);
    pinMode(A2, INPUT);
    pinMode(A3, INPUT);

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
  
    // SDcard
    File datafile;

    sprintf(filename, "%d-%d%-d%|d%:d:%d.csv", year(), month(), day(), hour(), minute(), second());
    datafile = SD.open(filename, FILE_WRITE);
    
    datafile.print("p");
    datafile.print(",");
    datafile.print("v");
    datafile.print(",");
    datafile.print("dv0");
    datafile.print(",");
    datafile.print("dv1");
    datafile.print(",");
    datafile.print("dv2");
    datafile.print(",");
    datafile.print("dv3");
    datafile.println();

    datafile.close();
} 

void loop() {

// 差圧センサ電圧読み取り
    float pressure = mySensor.getPressure();
    if(isnan(pressure)){
    Serial.println("Error: Could not read pressure data");
    }

//　流速の計算

    float c = 1;
    float rho = 1.29; // [kg/m3] | 標準状態：温度 0 度，圧力1気圧 | url:https://www.jsme.or.jp/jsme-medwiki/09:1012584

    float v = 0;
    float p = pressure;

    v = c * sqrt(2 * p / rho) * 3600 / 1000;

//    Serial.print(v, 2);
//    Serial.println(" [km/h]");

// ロードセル電圧読み取り

    value0 = analogRead(A0);
    value1 = analogRead(A1);
    value2 = analogRead(A2);
    value3 = analogRead(A3);
  
    dv0 = value0 *5.0 /1024;
    dv1 = value1 *5.0 /1024;
    dv2 = value2 *5.0 /1024;
    dv3 = value3 *5.0 /1024;

// SD 書き込み

    File datafile;
    datafile = SD.open(filename, FILE_WRITE);

    datafile.print(p);
    datafile.print(",");
    datafile.print(v,2);
    datafile.print(",");
    datafile.print(dv0);
    datafile.print(",");
    datafile.print(dv1);
    datafile.print(",");
    datafile.print(dv2);
    datafile.print(",");
    datafile.print(dv3);
    datafile.println();

    datafile.close();
    delay(100);
}
