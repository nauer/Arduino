// pwm.ino
const int pin = 10; // also the SMD Led on the Arduino

void setup()
{
  // Set pin 13 to output mode
  pinMode(pin, OUTPUT);
  pinMode(A0, INPUT);
  
  analogWrite(pin,127);
  Serial.begin(9600);
}

void loop()
{
  Serial.println(analogRead(A0));
  delay(250);
}


