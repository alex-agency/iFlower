
#ifndef MELODY_H
#define MELODY_H

#include "pitches.h"

// declare melody count
uint8_t const numTunes = 3;

// "Jingle Bells" melody
uint16_t jingleBells[] 			= { N_E5, N_E5, N_E5, N_E5, N_E5, N_E5, N_E5, N_G5, N_C5, N_D5, N_E5,
								N_F5, N_F5, N_F5, N_F5, N_F5, N_E5, N_E5, N_E5, N_E5, N_D5, N_D5, N_E5, N_D5, N_G5,
								N_E5, N_E5, N_E5, N_E5, N_E5, N_E5, N_E5, N_G5, N_C5, N_D5, N_E5,
								N_F5, N_F5, N_F5, N_F5, N_F5, N_E5, N_E5, N_E5, N_G5, N_G5, N_F5, N_D5, N_C5 };
uint16_t jingleBells_durations[] 	= { 4, 4, 8, 4, 4, 8, 4, 4, 4, 4, 16,
								4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 8, 8,
								4, 4, 8, 4, 4, 8, 4, 4, 4, 4, 16,
								4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 16 };

// "The first noel" melody
uint16_t firstNoel[] 			= { N_E4, N_D4, N_C4, N_D4, N_E4, N_F4, N_G4, N_A4, N_B4, N_C5, N_B4, N_A4,
								N_G4, N_A4, N_B4, N_C5, N_B4, N_A4, N_G4, N_A4, N_B4, N_C5, N_G4, N_F4,
								N_E4, N_E4, N_D4, N_C4, N_D4, N_E4, N_F4, N_G4, N_A4, N_B4, N_C5, N_B4, N_A4,
								N_G4, N_A4, N_B4, N_C5, N_B4, N_A4, N_G4, N_A4, N_B4, N_C5, N_G4, N_F4,
								N_E4, N_E4, N_D4, N_C4, N_D4, N_E4, N_F4, N_G4, N_C5, N_B4, N_A4, N_A4,
								N_G4, N_C5, N_B4, N_A4, N_G4, N_A4, N_B4, N_C5, N_G4, N_F4, N_E4 };
uint16_t firstNoel_durations[] 	= { 2, 2, 6, 2, 2, 2, 8, 2, 2, 4, 4, 4,
								8, 2, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4,
								8, 2, 2, 6, 2, 2, 2, 8, 2, 2, 4, 4, 4,
								8, 2, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4,                             
								8, 2, 2, 6, 2, 2, 2, 8, 2, 2, 8, 4,
								12, 4, 4, 4, 4, 4, 4, 4, 4, 4, 8 };

// "What child is this" melody
uint16_t whatChild[] 			= { N_E4, N_G4, N_A4, N_B4, N_C5, N_B4, N_A4, N_FS4, N_D4, N_E4, N_FS4, N_G4, N_E4, N_E4, N_DS4, N_E4, N_FS4, N_B3, N_REST,  N_E4,
								N_G4, N_A4, N_B4, N_C4, N_B4, N_A4, N_FS4, N_D4, N_E4, N_FS4, N_G4, N_FS4, N_E4, N_DS4, N_CS4, N_D4, N_E4, N_E4, N_REST,
								N_D5, N_D5, N_C5, N_B4, N_A4, N_FS4, N_D4, N_E4, N_FS4, N_G4, N_E4, N_E4, N_DS4, N_E4, N_FS4, N_DS4, N_B3, N_REST, 
								N_D5, N_D5, N_C5, N_B4, N_A4, N_FS4, N_D4, N_E4, N_FS4, N_G4, N_FS4, N_E4, N_DS4, N_CS4, N_D4, N_E4, N_E4 };
uint16_t whatChild_durations[] 	= { 2, 4, 2, 3, 1, 2, 4, 2, 3, 1, 2, 4, 2, 3, 1, 2, 6, 2, 2, 2,
								4, 2, 3, 1, 2, 4, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 6, 4, 2,
								6, 3, 1, 2, 4, 2, 3, 1, 2, 4, 2, 3, 1, 2, 4, 2, 4, 2,
								6, 3, 1, 2, 4, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 6, 4 }; 

// Declare melody structure
typedef struct {
   uint16_t *melody;
   uint16_t *durations;
   uint16_t tempo;
   uint16_t numNotes;
} tune;

// Debug info
#define DEBUG 		true

class Melody
{
public:
	Melody( uint8_t _pin ) {
		pin = _pin;
		// initialize speaker pin
    	pinMode(pin, OUTPUT);

    	tunes[0].melody = jingleBells;
    	tunes[0].durations = jingleBells_durations;
    	tunes[0].tempo = 60;
        tunes[0].numNotes = sizeof(jingleBells)/sizeof(int);

    	tunes[1].melody = firstNoel;
    	tunes[1].durations = firstNoel_durations;
    	tunes[1].tempo = 60;
        tunes[1].numNotes = sizeof(firstNoel)/sizeof(int);

    	tunes[2].melody = whatChild;
    	tunes[2].durations = whatChild_durations;
    	tunes[2].tempo = 100;
        tunes[2].numNotes = sizeof(whatChild)/sizeof(int);
	};

	void play( void ) {
		play(0);
	};

	void play( uint8_t _tuneNum ) {
		if( thisNote < tunes[tuneNum].numNotes ) 
			return;

		if(_tuneNum < 0 || _tuneNum == 0 || _tuneNum > numTunes)
			tuneNum = random(numTunes);
		else
			tuneNum = _tuneNum - 1;

		thisNote = 0;
		pauseBetweenNotes = 0;
		time = 0;
	};

	void update( void ) {
		
		if( thisNote >= tunes[tuneNum].numNotes ||
		 	(millis() - time) < pauseBetweenNotes ) {
			return;
		}

		noTone(pin);

		uint16_t freq = tunes[tuneNum].melody[thisNote]*2;
		uint16_t noteDuration = tunes[tuneNum].tempo*tunes[tuneNum].durations[thisNote];

		if (freq > 0) {
			tone(pin, freq, noteDuration); 
		}

		// to distinguish the notes, set a minimum time between them.
		// the note's duration + 30% seems to work well:
		pauseBetweenNotes = noteDuration + (noteDuration * 0.30); 

		thisNote++;
		time = millis();	
	};

private:
	uint8_t pin;
	tune tunes[numTunes];
	uint8_t tuneNum;
	uint16_t thisNote;
	uint16_t pauseBetweenNotes;
	unsigned long time;
};

#endif // __MELODY_H__
