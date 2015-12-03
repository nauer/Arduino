// ir_receive.ino
#include <IRremote.h>

int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  Serial.begin(9600);
  pinMode (13, OUTPUT);
  irrecv.enableIRIn();
}

void loop()
{
  if (irrecv.decode(&results)) 
  {
    Serial.println(results.value, HEX);
    Serial.println(results.decode_type, DEC);
    irrecv.resume();
  }
}
