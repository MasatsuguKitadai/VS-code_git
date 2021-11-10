#include <WiFi.h>
#include <Wire.h>
#include "Ambient.h"
WiFiClient client;
Ambient ambient;
//初期設定

//デザリングの設定
const char* ssid       = "Start";
const char* password   = "Password";

//Ambientの設定
unsigned int channelId = 43076;
const char* writeKey = "402951c596dbf815";

// millis の設定djsafal
unsigned long time_data = 0;
int milli_sec = 0;

//LEDの設定
#define LED_GREEN 12 // 送信確認
#define LED_BLUE 27 // Wifi接続確認

//超音波距離センサの設定
#define echoPin 33 // Echo Pin
#define trigPin 25 // Trigger Pin
 
double Duration = 0; //受信した間隔
double Distance = 0; //距離
 
void setup() {
Serial.begin( 115200 );
digitalWrite(LED_BLUE, LOW);
digitalWrite(LED_GREEN, LOW);


int i = 0;

//  wifiへの接続
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);  //  Wi-Fi APに接続
    while (WiFi.status() != WL_CONNECTED) {  //  Wi-Fi AP接続待ち
        delay(100);
        i = i + 1;
        if(i > 50)
        {
          ESP.restart(); // 再起動
        }
    }

  Serial.print("WiFi connected\r\nIP address: ");
  Serial.println(WiFi.localIP());
  digitalWrite(LED_BLUE, HIGH);
  
//  Ambient セットアップ
  ambient.begin(channelId, writeKey, &client); // チャネルIDとライトキーを指定してAmbientの初期化

  ambient.set(1, 1);
  ambient.send(); // データをAmbientに送信

//  超音波センサのセットアップ
pinMode( echoPin, INPUT );
pinMode( trigPin, OUTPUT );

//  LEDのセットアップ
pinMode(LED_GREEN, OUTPUT);
pinMode(LED_BLUE, OUTPUT);
}
 
void loop() {
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite( trigPin, HIGH ); //超音波を出力
  delayMicroseconds( 10 ); //
  digitalWrite( trigPin, LOW );
  
  
  Duration = pulseIn( echoPin, HIGH ); //センサからの入力
  if (Duration > 0) {
    Duration = Duration/2; //往復距離を半分にする
    Distance = Duration*340*100/1000000; // 音速を340m/sに設定

//    mills で時刻を取得
    time_data = millis();
    milli_sec = time_data;
    
    if (Distance < 200) // 反応距離の設定
    {
      Serial.print("[");
      Serial.print(milli_sec);
      Serial.print("]\t");
      Serial.println(Distance);
//      LED(緑)の点灯
      digitalWrite(LED_GREEN, HIGH);
      delay(10);
      digitalWrite(LED_GREEN, LOW);

//      送信データの設定
      ambient.set(2, milli_sec); // データ1にセット
      ambient.send(); // データをAmbientに送信

//      停止時刻
      delay(2990);
    }
  }
  delay(10);//取得間隔1秒
}
