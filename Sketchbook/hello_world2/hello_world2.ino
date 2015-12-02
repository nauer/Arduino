// hello_world2.ino
const int pin = 13; // also the SMD Led on the Arduino
boolean isMessage = false;
byte input = 0;

void setup()
{
  // Set pin 13 to output mode
  pinMode(pin, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  if (isMessage)
  {
    switch (input)
    {
      case 1: // Turn led on
        digitalWrite(pin, HIGH);
        break; // Do not forget!!
      case 2: // Turn led off 
        digitalWrite(pin, LOW);
        break;
      default:
        digitalWrite(pin, HIGH);
        delay(500);
        digitalWrite(pin, LOW);
        delay(500);
        break;
    }
    isMessage = false;
    Serial.print("Receive: ");
    Serial.println(input);
  }
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
