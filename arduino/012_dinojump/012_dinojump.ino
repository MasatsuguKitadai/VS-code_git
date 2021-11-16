SD #include <Servo.h>
 
Servo myservo;
int value = 0;
int i = 0;
int j = 0;

void setup() {
  Serial.begin(9800);
  myservo.attach(9);
  myservo.write(0);
}

void loop() {
  value = analogRead(0);
  if (value > 734 ){
    Serial.println(value);
    i = i + 2;
    j = 280 - i;
    delay(j);
    myservo.write(16);
    delay(300);             
    myservo.write(0);
    delay(100);
  }
  delay(50);
}
  
