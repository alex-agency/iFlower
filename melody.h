
#ifndef MELODY_H
#define MELODY_H

#include "pitches.h"

// Debug info
#define DEBUG 		true

// declare melody count
uint8_t const numMelodies = 5;

class Melody
{
public:
  Melody( uint8_t _pin ) {
    pin = _pin;
    // initialize speaker pin
    pinMode(pin, OUTPUT);
  };

  void beep( uint8_t _beepCount ) {
    if( _beepCount < 0 )
	  return;
	// set beep count
	beepCount = _beepCount;
  };

  void play( void ) {
	// play random
	play(0);
  };

  void play( uint8_t _melodyNum ) {
    // prevent new play if previous not ended
    if( noteIndex < numNotes ) 
	  return;
	// check number
	if(_melodyNum < 0 || _melodyNum == 0 || _melodyNum > numMelodies)
      melodyNum = random(2, numMelodies);
	else
	  melodyNum = _melodyNum;
	// compile chosen melody
	compileMelody();
	// reset index
	noteIndex = 0;
	notePause = 0;
	time = 0;
  };

  void update( void ) {
	if( beepCount > 0 && noteIndex >= numNotes ) {
	  // play beep melody
	  play(1);
	  beepCount--;
	}
	// skip if it last note or pause between notes
	if( noteIndex >= numNotes || (millis() - time) < notePause )
	  return;
	// play current note
	playNote();
	// change note cursor
	noteIndex++;
	time = millis();	
  };

private:
  uint8_t pin;
  uint8_t beepCount;
  uint8_t melodyNum;
  uint16_t *melody;
  uint8_t *duration;
  uint8_t tempo;	
  uint8_t numNotes;
  uint8_t noteIndex;
  uint16_t notePause;
  unsigned long time;

  void compileMelody( void ) {
	// short beep 
	if( melodyNum == 1 ) {
	  uint16_t beep[]  				= { 343, 422 };
	  melody 						= beep;

	  uint8_t beep_dur[] 			= { 4, 	  3 };
	  duration 						= beep_dur;

	  tempo 						= 111;
	  numNotes 						= sizeof(beep)/sizeof(int);
	}
	// "Jingle Bells" melody
    else if( melodyNum == 2 ) { 
	  uint16_t jingleBells[]  		= { N_E5, N_E5, N_E5, N_E5, N_E5, N_E5, N_E5, N_G5, 
						    			N_C5, N_D5, N_E5, N_F5, N_F5, N_F5, N_F5, N_F5, 
						    			N_E5, N_E5, N_E5, N_E5, N_D5, N_D5, N_E5, N_D5, 
										N_G5, N_E5, N_E5, N_E5, N_E5, N_E5, N_E5, N_E5, 
										N_G5, N_C5, N_D5, N_E5, N_F5, N_F5, N_F5, N_F5, 
										N_F5, N_E5, N_E5, N_E5, N_G5, N_G5, N_F5, N_D5, 
										N_C5 };
	  melody 						= jingleBells;

	  uint8_t jingleBells_dur[] 	= { 4, 	  4,    8,    4,    4,    8,    4,    4, 
										4,    4,   16,    4,    4,    4,    4,    4, 
										4,    4,    4,    4,    4,    4,    4,    8, 
										8,    4,    4,    8,    4,    4,    8,    4, 
										4,    4,    4,   16,    4,    4,    4,    4, 
										4,    4,    4,    4,    4,    4,    4,    4, 
										16 };
	  duration 						= jingleBells_dur;

	  tempo 						= 60;
	  numNotes 						= sizeof(jingleBells)/sizeof(int);
	}
    // "The first noel" melody
    else if( melodyNum == 3 ) {  
	  uint16_t firstNoel[] 			= { N_E4, N_D4, N_C4, N_D4, N_E4, N_F4, N_G4, N_A4, 
										N_B4, N_C5, N_B4, N_A4, N_G4, N_A4, N_B4, N_C5, 
										N_B4, N_A4, N_G4, N_A4, N_B4, N_C5, N_G4, N_F4,
										N_E4, N_E4, N_D4, N_C4, N_D4, N_E4, N_F4, N_G4, 
										N_A4, N_B4, N_C5, N_B4, N_A4, N_G4, N_A4, N_B4, 
										N_C5, N_B4, N_A4, N_G4, N_A4, N_B4, N_C5, N_G4, 
										N_F4, N_E4, N_E4, N_D4, N_C4, N_D4, N_E4, N_F4, 
										N_G4, N_C5, N_B4, N_A4, N_A4, N_G4, N_C5, N_B4, 
										N_A4, N_G4, N_A4, N_B4, N_C5, N_G4, N_F4, N_E4 };
	  melody 						= firstNoel;

	  uint8_t firstNoel_dur[] 		= { 2, 	  2,    6,    2,    2,    2,    8,    2, 
										2,    4,    4,    4,    8,    2,    2,    4, 
										4,    4,    4,    4,    4,    4,    4,    4,
										8,    2,    2,    6,    2,    2,    2,    8, 
										2,    2,    4,    4,    4,    8,    2,    2, 
										4,    4,    4,    4,    4,    4,    4,    4, 
										4,    8,    2,    2,    6,    2,    2,    2, 
										8,    2,    2,    8,    4,   12,    4,    4,
										4,    4,    4,    4,    4,    4,    4,    8 };
	  duration 						= firstNoel_dur;

	  tempo 						= 60;
	  numNotes 						= sizeof(firstNoel)/sizeof(int);
	}
	// "What child is this" melody
    else if( melodyNum == 4 ) {
	  uint16_t whatChild[] 			= { N_E4, N_G4, N_A4, N_B4, N_C5, N_B4, N_A4, N_FS4, 
										N_D4, N_E4, N_FS4, N_G4, N_E4, N_E4, N_DS4, N_E4, 
										N_FS4, N_B3, N_REST, N_E4, N_G4, N_A4, N_B4, N_C4, 
										N_B4, N_A4, N_FS4, N_D4, N_E4, N_FS4, N_G4, N_FS4, 
										N_E4, N_DS4, N_CS4, N_D4, N_E4, N_E4, N_REST, N_D5, 
										N_D5, N_C5, N_B4, N_A4, N_FS4, N_D4, N_E4, N_FS4, 
										N_G4, N_E4, N_E4, N_DS4, N_E4, N_FS4, N_DS4, N_B3, 
										N_REST, N_D5, N_D5, N_C5, N_B4, N_A4, N_FS4, N_D4, 
										N_E4, N_FS4, N_G4, N_FS4, N_E4, N_DS4, N_CS4, N_D4, 
										N_E4, N_E4 };
	  melody 						= whatChild;

	  uint8_t whatChild_dur[] 		= { 2,    4,    2,    3,    1,    2,    4,    2, 
			   							3,    1,    2,    4,    2,    3,    1,    2, 
			   							6,    2,    2,    2,    4,    2,    3,    1, 
			   							2,    4,    2,    3,    1,    2,    3,    1, 
			   							2,    3,    1,    2,    6,    4,    2,    6,
			   							3,    1,    2,    4,    2,    3,    1,    2, 
			   							4,    2,    3,    1,    2,    4,    2,    4, 
			   							2,    6,    3,    1,    2,    4,    2,    3, 
			   							1,    2,    3,    1,    2,    3,    1,    2, 
			   							6,    4 };
	  duration 						= whatChild_dur;

	  tempo 						= 100;
	  numNotes 						= sizeof(whatChild)/sizeof(int);
	}
	// "R2D2" melody
    else if( melodyNum == 5 ) {
	  uint16_t r2d2[] 				= { N_A7, N_G7, N_E7, N_C7, N_D7, N_B7, N_F7, N_C8,
                     					N_A7, N_G7, N_E7, N_C7, N_D7, N_B7, N_F7, N_C8,};
	  melody 						= r2d2;

	  uint8_t r2d2_dur[] 			= { 2,    2,    2,    2,    2,    2,    2,    2,
                               			2,    2,    2,    2,    2,    2,    2,    2 };
	  duration 						= r2d2_dur;

	  tempo 						= 40;
	  numNotes 						= sizeof(r2d2)/sizeof(int);
	}
  };

  void playNote( void ) {
	noTone(pin);
		
	uint16_t freq = melody[noteIndex] * 2;
	uint16_t noteDuration = tempo * duration[noteIndex];

	if (freq > 0) {
	  tone(pin, freq, noteDuration); 
	}
	// to distinguish the notes, set a minimum time between them.
	// the note's duration + 30% seems to work well:
	notePause = noteDuration + (noteDuration * 0.30);
  };
};

#endif // __MELODY_H__
