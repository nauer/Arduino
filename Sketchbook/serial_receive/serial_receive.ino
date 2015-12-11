//serial_receive.ino
const int led = 13;

void setup() 
{
  Serial.begin(9600);  
  pinMode(led, OUTPUT);
}

void loop() 
{
  if (Serial.available()) 
  {
    delay(100);

    while(Serial.available()) 
    {
      int val = Serial.parseInt();
      
      if (val == 1)
        digitalWrite(led, HIGH);
      else
        digitalWrite(led, LOW);
    }
  }
}
