#include "monkey_island_notes.h"

/* need special memory management because of big notes array size 
   see avr/pgmspace.h 
*/

void setup() 
{
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < numberOfNotes; thisNote++)
  {
    if (pgm_read_word_near(melody + thisNote) > 0)
    {
      tone(11, pgm_read_word_near(melody + thisNote));
    } 
    else noTone(11);
    delay(pgm_read_word_near(noteDurations + thisNote));
  }
  noTone(11);
}

void loop() 
{
  // no need to repeat the melody.
}



