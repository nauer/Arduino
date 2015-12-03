const int A = A0;
const int B = A1;
const int C = A2;

void setup()
{
  Serial.begin(9600);
  pinMode(A, INPUT);
  pinMode(B, INPUT);
  pinMode(C, INPUT);
}

void loop()
{
  Serial.print(analogRead(A));
  Serial.print("-");
  Serial.print(analogRead(B));
  Serial.print("-");
  Serial.println(analogRead(C));
  delay(2000);  
}
