#include <Arduino.h>
#include <Wire.h>
#include <Omron_D6FPH.h>

Omron_D6FPH mySensor;

void setup() {

//  差圧計 (DFP-) セットアップ
    Serial.begin(115200);
    Wire.begin();
    mySensor.begin(MODEL_0025AD1); // 型番指定 0025AD1

//    ロードセル セットアップ
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
} 

void loop() {

    float pressure = mySensor.getPressure();
    if(isnan(pressure)){
    Serial.println("Error: Could not read pressure data");
    }else{
//        Serial.print("Differential Pressure: ");
//        Serial.println(pressure);
    }

//　流速の計算

    float c = 1;
    float rho = 1.29; // [kg/m3] | 標準状態：温度 0 度，圧力1気圧 | url:https://www.jsme.or.jp/jsme-medwiki/09:1012584

    float v = 0;
    float p = pressure;

    v = c * sqrt(2 * p / rho) * 3600 / 1000;

    Serial.print(v, 2);
    Serial.println(" [km/h]");

//    float temperature = mySensor.getTemperature();
//    if(isnan(temperature)){
//    Serial.println("Error: Could not read temperature data");
//    }else{
//        Serial.print("Temperature C: ");
//        Serial.println(temperature);
//    }
//    Serial.println(temperature);
  delay(100);
}
