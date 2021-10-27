#include <WiFi.h>
#include <Wire.h>
#include "Ambient.h"
WiFiClient client;
Ambient ambient;
//初期設定

//デザリングの設定
const char* ssid       = "finish";
const char* password   = "password";

//Ambientの設定
unsigned int channelId = 42567;
const char* writeKey = "1f9d0e2d5891b768";

// millis の設定
unsigned long time_data = 0;
int milli_sec = 0;

#define echoPin 16 // Echo Pin
#define trigPin 17 // Trigger Pin
 
double Duration = 0; //受信した間隔
double Distance = 0; //距離
 
void setup() {
Serial.begin( 115200 );//Arduino Unoは9600,ESPで試す場合はは115200

//  超音波センサの設定
pinMode( echoPin, INPUT );
pinMode( trigPin, OUTPUT );

//  wifiへの接続
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);  //  Wi-Fi APに接続
    while (WiFi.status() != WL_CONNECTED) {  //  Wi-Fi AP接続待ち
        delay(100);
    }

  Serial.print("WiFi connected\r\nIP address: ");
  Serial.println(WiFi.localIP());
  ambient.begin(channelId, writeKey, &client); // チャネルIDとライトキーを指定してAmbientの初期化

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
    
    if (Distance < 100)
    {
      Serial.print("[");
      Serial.print(milli_sec);
      Serial.print("]\t");
      Serial.println(Distance);

      // 送信データの設定
      ambient.set(2, milli_sec); // データ2にセット
      ambient.send(); // データをAmbientに送信
      
      delay(10000);
    }
  }
  delay(10);//取得間隔0.01秒
}
