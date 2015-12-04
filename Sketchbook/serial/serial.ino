// TMP36.ino
boolean isMessage = false;
boolean trig = false;
byte input = 0;
const byte led = 13;


void setup()
{
  pinMode(A0, INPUT);
  Serial.begin(9600);
}

void loop()
{
  if (isMessage)
  {
    switch (input)
    {
      case 1: // Start reading
        trig = true;
        break;
      default: // Stop everything
        trig = false;      
        break;
    }
    isMessage = false;
  }
  
  if (trig)
  {
    digitalWrite(led, HIGH);
    Serial.print(map(analogRead(A0),0,410,-50,150));
  }
  else
    digitalWrite(led, LOW);
    
  delay(1000);
}

void serialEvent()
{
  // is something in the buffer
  while (Serial.available())
  {
    // get the new byte:
    //input = Serial.read(); Convert to character
    input = Serial.parseInt();
    isMessage = true;
  }
}
