#include <Wire.h>

int16_t axRaw, ayRaw, azRaw, gxRaw, gyRaw, gzRaw, temperature;
        //a:acceleration  g:gyro(角加速度)
float acc_x,acc_y,acc_z;
float acc_angle_x,acc_angle_y,acc_angle_z;
float gyr_x,gyr_y,gyr_z;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  TWBR = 12;

  Wire.beginTransmission(0x68);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission();

  //Gyro初期設定.
  
  Wire.beginTransmission(0x68);
  Wire.write(0x1C);
  Wire.write(0x10);
  Wire.endTransmission();

  //加速度センサー初期設定
  Wire.beginTransmission(0x68);
  Wire.write(0x1B);
  Wire.write(0x08);
  Wire.endTransmission();

  //LPF設定
  Wire.beginTransmission(0x68);
  Wire.write(0x1A);
  Wire.write(0x05);
  Wire.endTransmission();
  
}


void loop() {
  Wire.beginTransmission(0x68);
  Wire.write(0x3B);
  Wire.endTransmission();
  Wire.requestFrom(0x68, 14);
  while (Wire.available() < 14);
  axRaw = Wire.read() << 8 | Wire.read();
  ayRaw = Wire.read() << 8 | Wire.read();
  azRaw = Wire.read() << 8 | Wire.read();
  temperature = Wire.read() << 8 | Wire.read();
  gxRaw = Wire.read() << 8 | Wire.read();
  gyRaw = Wire.read() << 8 | Wire.read();
  gzRaw = Wire.read() << 8 | Wire.read();

  // 取得した加速度値を分解能で割って加速度(G)に変換する
  acc_x = axRaw / 4096.0; //スケールファクタの設定(分解能？)
  acc_y = ayRaw / 4096.0; //FS_SEL_2 4096LSB/g (Least Significant Bit:量子化単位)
  acc_z = azRaw / 4096.0;

/*
  // 加速度からセンサ対地角を求める
  acc_angle_x = atan2(acc_y, acc_z) * 360 / (2.0*PI);
  acc_angle_y = atan2(acc_x, acc_z) * 360 / (2.0*PI);
  acc_angle_z = atan2(acc_x, acc_y) * 360 / (2.0*PI);
*/

  // 取得した角速度値を分解能で割って角速度(deg/s)に変換する
  gyr_x = gxRaw / 65.5; //スケールファクタの設定(分解能？)
  gyr_y = gyRaw / 65.5; //FS_SEL_1 65.5LSB/(deg/s)
  gyr_z = gzRaw / 65.5;

  Serial.print("A_x: "); Serial.print(acc_x); Serial.print('\t');
  Serial.print("A_y: "); Serial.print(acc_y); Serial.print('\t');
  Serial.print("A_z: "); Serial.print(acc_z); Serial.print('\t');
  Serial.print("G_x: "); Serial.print(gyr_x); Serial.print('\t');
  Serial.print("G_y: "); Serial.print(gyr_y); Serial.print('\t');
  Serial.print("G_z: "); Serial.print(gyr_z); Serial.print('\t');
  //Serial.print("ang_x:"); Serial.print(acc_angle_x); Serial.print(",");
  Serial.println();

  delay(100);
}
