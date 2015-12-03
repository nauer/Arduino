// TMP36.ino
void setup()
{
  pinMode(A0, INPUT);
  Serial.begin(9600);
}

void loop()
{
  Serial.print(analogRead(A0));
  Serial.print("\tTemp: ");
  // 0-410 : 0-2 V -50-150°C TWP36-Output
  Serial.print(map(analogRead(A0),0,410,-50,150));
  Serial.println(" C");  
  delay(250);
}


