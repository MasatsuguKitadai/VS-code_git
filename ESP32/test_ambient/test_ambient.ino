#include <WiFi.h>
#include <Wire.h>
#include "Ambient.h"
WiFiClient client;
Ambient ambient;

unsigned long delayTime;
float temp;
float pressure;
float humid;

const char* ssid       = "kit_formula";
const char* password   = "password";

unsigned int channelId = 42567;
const char* writeKey = "a840d034f2594fea";

int i = 0;

void setup() {
  Serial.begin(115200);

//  wifiへの接続
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);  //  Wi-Fi APに接続
    while (WiFi.status() != WL_CONNECTED) {  //  Wi-Fi AP接続待ち
        delay(100);
    }

  Serial.print("WiFi connected\r\nIP address: ");
  Serial.println(WiFi.localIP());
  ambient.begin(channelId, writeKey, &client); // チャネルIDとライトキーを指定してAmbientの初期化
};

void loop() { 

if (i > 19) {
  i = i - 10;
} else {
  i = i + 1;
}

// 送信データの設定
  ambient.set(1, i); // データ1にセット
  ambient.send(); // データをAmbientに送信

// データの送信
  Serial.print("send ");
  Serial.println(i);

  delay(10000);
}
