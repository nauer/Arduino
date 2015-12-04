// servo.ino
#include <Servo.h>  

Servo servo;
const byte servo_pin = 8;

void setup() 
  servo.attach(servo_pin);

void loop() 
{ 
  servo.write(10);
  delay(3000);
  servo.write(90);
  delay(3000);
  servo.write(180);
  delay(3000);
}
