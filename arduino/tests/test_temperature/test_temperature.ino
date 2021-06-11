// this example is public domain. enjoy!
// https://learn.adafruit.com/thermocouple/

#include <max6675.h>
#include <LiquidCrystal.h>
#include <Wire.h>

int thermoDO = 4;
int thermoCS = 5;
int thermoCLK = 6;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);
int vccPin = 3;
int gndPin = 2;

void setup() {
  Serial.begin(9600);
  // use Arduino pins 
  pinMode(vccPin, OUTPUT); digitalWrite(vccPin, HIGH);
  pinMode(gndPin, OUTPUT); digitalWrite(gndPin, LOW);

  // wait for MAX chip to stabilize
  delay(500);
}

void loop() {
  // basic readout test, just print the current temp

  Serial.print("MAX6675 test");
  
  // go to line #1
  Serial.print(thermocouple.readCelsius());
#if ARDUINO >= 100
  Serial.write((byte)0);
#else
  Serial.print(0, BYTE);
#endif
  Serial.print(" C ");
  Serial.print(thermocouple.readFahrenheit());
#if ARDUINO >= 100
  Serial.write((byte)0);
#else
  Serial.print(0, BYTE);
#endif
  Serial.print(" F");
  Serial.println(); 
  
  delay(5000);
}
