#include <Servo.h>
#include "monkey_island_notes.h"
// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 8, 7, 6, 5);


// Serial communication
const unsigned int BAUD_RATE = 9600;
boolean input_available = false;
String input = "";

// Servo
Servo servo1;

// Piezo
const int piezoPin = 10;
unsigned int note;

// 74HC595
//Pin connected to ST_CP of 74HC595
const int latchPin = 4;
//Pin connected to SH_CP of 74HC595
const int clockPin = 3;
////Pin connected to DS of 74HC595
const int dataPin = 2;
const int ledpos[] = {0, 1, 2, 4, 8, 16, 32, 64, 128};

// lcd row 1 & 2
String row1;
String row2;

void setup() 
{
  // Start serial communication
  Serial.begin(BAUD_RATE);
  Serial.println("Power On");
  
  // Set seed for random number generator
  randomSeed(analogRead(0));
  
  // Attach servo to pin 9
  servo1.attach(9);
  
  pinMode(piezoPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  row1 = " Monkey Island";
  row2 = "Insult-Generator";        
  printLcd(" Monkey Island",row2);
}

void loop()
{
    if (input_available) 
    {
      Serial.print("Receive: ");
      Serial.println(input);

      if (input == "monkey_song")
      {
        row1 = "Currently,I play";
        row2 = "the Monkey Song";        
        printLcd(row1,row2);
        play_monkey_song();
        row1 = "Finished!! Ready";
        row2 = "for new querys";        
        printLcd(row1,row2);
      }
      else if(input == "beep")
      {
        Serial.println("Beep");
        tone(piezoPin,1000,500);
      }
      else if(input.startsWith("servo:"))
      {
        int value = input.substring(6).toInt();
        Serial.print("Set servo to:");
        Serial.println(value);
        servo1.write(value);
      }
      else if(input.startsWith("leds:"))
      {
        int value = input.substring(5).toInt();
        Serial.print("Set leds to:");
        Serial.println(value);
        digitalWrite(latchPin, LOW);
        shiftOut(dataPin, clockPin, MSBFIRST, value);
        digitalWrite(latchPin, HIGH);
      }
      
      // Reset input
      input = "";
      input_available = false;      
    }
    
    delay(1000);
}

// End string with ;
void serialEvent()
{
    while (Serial.available())
    {
      const char c = Serial.read();

      if (c == ';')
        // input is finished for readout
        input_available = true;
      else
        // Add character to input
        input += c;
    }
}

void play_monkey_song() 
{
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < numberOfNotes; thisNote++)
  {
    note = pgm_read_word_near(melody + thisNote);
    
    if (note > 0)
    {
      tone(piezoPin, note);
      
      // Update Leds
      digitalWrite(latchPin, LOW);
      
      if (note > 900)
        shiftOut(dataPin, clockPin, MSBFIRST, 128);
      else if (note > 800)
        shiftOut(dataPin, clockPin, MSBFIRST, 64);
      else if (note > 700)
        shiftOut(dataPin, clockPin, MSBFIRST, 32);
      else if (note > 600)
        shiftOut(dataPin, clockPin, MSBFIRST, 16);
      else if (note > 500)
        shiftOut(dataPin, clockPin, MSBFIRST, 8);
      else if (note > 400)
        shiftOut(dataPin, clockPin, MSBFIRST, 4);
      else if (note > 300)
        shiftOut(dataPin, clockPin, MSBFIRST, 2);
      else if (note > 200)
        shiftOut(dataPin, clockPin, MSBFIRST, 1);
      else 
        shiftOut(dataPin, clockPin, MSBFIRST, 0);

      digitalWrite(latchPin, HIGH);            
    } 
    else
      noTone(piezoPin);
    
    delay(pgm_read_word_near(noteDurations + thisNote));
  }
  noTone(piezoPin);
  // Reset Leds
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 255);
  digitalWrite(latchPin, HIGH);
}

void printLcd(String row1, String row2)
{
  lcd.clear();
  lcd.setCursor(0, 0);       
  lcd.print(row1);
  lcd.setCursor(0, 1);
  lcd.print(row2);
}
  /*if (Serial.available() > 0) // Don't read unless
  {
    incomingByte = Serial.read();
    Serial.println(incomingByte,DEC);
  }
  
  if (incomingByte == 49)
  {
    Serial.println("Shaker On");
    bshake = true;
  }
  else if (incomingByte == 50)
  {
    Serial.println("Shaker Off");
    bshake = false;
  }
  else if (incomingByte == 51)
  {
    Serial.println("Summer On");
    tone(summerPin,1000,500);
  }
  else if (incomingByte == 52)
  {
    Serial.println("Summer Off");
    digitalWrite(summerPin,LOW);
  }
  else if (incomingByte == 53)
  {
    Serial.println("play melody");
    //playMelody();
  }
  else
  {
    Serial.println("Off");
    bshake = false;
    digitalWrite(summerPin,LOW); 
    delay(250);   
  }
  
  if (bshake)
  {
    shake(200);
  }
  
  tone(summerPin, random(5000), 500);
  delay(1000);
  noTone(summerPin);
  
  
  int tmp = 0;
  for (int numberToDisplay = 0; numberToDisplay < 9; numberToDisplay++) 
  {
    tmp = tmp + ledpos[numberToDisplay];
    
    digitalWrite(latchPin, LOW);
    // shift out the bits:
    shiftOut(dataPin, clockPin, MSBFIRST, tmp);
    Serial.println(pow(2,numberToDisplay), DEC);

    //take the latch pin high so the LEDs will light up:
    digitalWrite(latchPin, HIGH);
    // pause before next value:
    delay(50);
  }
  /*for (int numberToDisplay = 0; numberToDisplay < 256; numberToDisplay++) 
  {
    // take the latchPin low so 
    // the LEDs don't change while you're sending in bits:
    digitalWrite(latchPin, LOW);
    // shift out the bits:
    shiftOut(dataPin, clockPin, MSBFIRST, numberToDisplay);  

    //take the latch pin high so the LEDs will light up:
    digitalWrite(latchPin, HIGH);
    // pause before next value:
    delay(50);
  }*/
  
  //playMelody();
  /*shake(200);
  for (int numberToDisplay = 0; numberToDisplay < 9; numberToDisplay++) 
  {
    tmp = tmp - ledpos[numberToDisplay];
    
    digitalWrite(latchPin, LOW);
    // shift out the bits:
    shiftOut(dataPin, clockPin, MSBFIRST, tmp);
    Serial.println(pow(2,numberToDisplay), DEC);

    //take the latch pin high so the LEDs will light up:
    digitalWrite(latchPin, HIGH);
    // pause before next value:
    delay(50);
  }*/
//}

/*void shake(int d)
{
  servo1.write(10);
  delay(d);
  servo1.write(170);
  delay(d);
  servo1.write(90);
}

void playMelody()
{
  for (int thisNote = 0; thisNote < 27; thisNote++) 
  {
    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations2[thisNote];
    tone(summerPin, melody2[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(summerPin);
  }
  delay(500);
  
  for (int thisNote = 0; thisNote < 8; thisNote++) 
  {
    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(summerPin, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(summerPin);
  }
  delay(500);
}*/
