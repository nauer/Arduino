#include <Servo.h>
#include <TimerOne.h> // Pin9 and Pin10 are not available
#include <LiquidCrystal.h>

#include "monkey_island_notes.h"

// LCD
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

void setup() 
{
  // LCD
  lcd.begin(16, 2);
  
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
  
  //Timer1.initialize(100000); // set a timer of length 100000 microseconds (or 0.1 sec - or 10Hz => the led will blink 5 times, 5 cycles of on-and-off, per second)
  //Timer1.attachInterrupt(play); // attach the service routine here
}

void loop()
{
    if (input_available) 
    {
      Serial.print("Receive: ");
      Serial.println(input);

      if (input == "monkey_song")
      {
        
        Serial.println("The Monkey Island Song");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("The Monkey Island");
        lcd.setCursor(0, 1);    
        lcd.print("Song");
        play_monkey_song();
      }
      else if(input == "beep")
      {
        Serial.println("Beep");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Beep!!!");
        tone(piezoPin,1000,500);
      }
      else if(input.startsWith("servo:"))
      {
        int value = input.substring(6).toInt();
        Serial.print("Set servo to:");
        Serial.println(value);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Set servo to:");
        lcd.setCursor(0, 1);
        lcd.print(value);
        
        servo1.write(value);
      }
      else if(input.startsWith("leds:"))
      {
        int value = input.substring(5).toInt();
        lcd.setCursor(0, 0);
        Serial.print("Set leds to:");
        Serial.println(value);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Set leds to:");
        lcd.setCursor(0, 1);
        lcd.print(value);
        
        digitalWrite(latchPin, LOW);
        shiftOut(dataPin, clockPin, MSBFIRST, value);
        digitalWrite(latchPin, HIGH);
      }
      else
      {
        lcd.clear();
        lcd.setCursor(0, 0);        
        lcd.print(input);
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
