const int ledPin = 13;
const int statPin = 6;
volatile bool statusLed = false;
bool status1 = false;

void setup() 
{ 
  pinMode(2, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  pinMode(statPin, OUTPUT);
  attachInterrupt(0, buttonPressed, FALLING);
} 

void loop()
{
  if (status1)
  {
    digitalWrite(statPin, LOW);
    status1 = false;
  }
  else
  {
    digitalWrite(statPin, HIGH);
    status1 = true;    
  }
  delay(500);

}

void buttonPressed()
{
  if (statusLed)
  {
    digitalWrite(ledPin,LOW);
    statusLed=false;
  }
  else
  {
    digitalWrite(ledPin,HIGH);
    statusLed=true;
  }
}
