// ping.ino
const int TRIG = 8;
const int ECHO = 9;
unsigned long length; // use long

const float microseconds_per_cm = 29.155;

void setup()
{
  Serial.begin(9600);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT); 
}

void loop()
{
  // start measurement
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(5);
  digitalWrite(TRIG, LOW);
  
  // get the echo
  // count time until ECHO pin is HIGH
  length = pulseIn(ECHO, HIGH);
  Serial.print("Distance to nearest object:");
  Serial.println(microseconds_to_cm(length));
  delay(500);  
}

const float microseconds_to_cm(const unsigned long microseconds)
{
  // 343m/s -> 29.155 microseconds/cm / 2 
  // echo takes 2 times the same distance
  return max(0, microseconds / microseconds_per_cm / 2);
}


