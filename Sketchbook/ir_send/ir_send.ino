// ir_send.ino
#include <IRremote.h>

IRsend irsend;

void setup()
{}

void loop()
{
  for (int i=0; i<3; i++)
  {
    irsend.sendSony(0xa90, 12);
    delay(140);
  }
  delay(2000);
}
