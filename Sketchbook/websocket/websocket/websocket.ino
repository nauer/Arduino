// websocket.ino
unsigned long i=0;

void setup()
{
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);  
  Serial.begin(19200);
}

void loop()
{
  Serial.print(i);
  Serial.print("#");
  Serial.print(analogRead(A0));
  Serial.print("#");  
  Serial.println(analogRead(A1));
  i++;
  delay(1000);
}


