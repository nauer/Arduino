// hello_world.ino
const int pin = 13; // also the SMD Led on the Arduino

void setup()
{
  // Set pin 13 in output mode
  pinMode(pin, OUTPUT);
}

void loop()
{
  digitalWrite(pin, HIGH);  // turn the LED on
  delay(1000);              // wait for a second
  digitalWrite(pin, LOW);   // turn the LED off
  delay(250);               // wait for 250 milli seconds
}