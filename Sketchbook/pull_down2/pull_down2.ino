// pull_down2.ino
const int taster = A0;

void setup()
{
  Serial.begin(9600);
  pinMode(taster, INPUT);
}

void loop()
{
  // A0 - A5 can also be used as digital pins
  Serial.println(analogRead(taster));
  delay(500);  
}
