
#ifndef MELODY_H
#define MELODY_H

#include "pitches.h"

// declare melody count
int const numTunes = 3;

// "Jingle Bells" melody
int jingleBells[] 			= { N_E5, N_E5, N_E5, N_E5, N_E5, N_E5, N_E5, N_G5, N_C5, N_D5, N_E5,
								N_F5, N_F5, N_F5, N_F5, N_F5, N_E5, N_E5, N_E5, N_E5, N_D5, N_D5, N_E5, N_D5, N_G5,
								N_E5, N_E5, N_E5, N_E5, N_E5, N_E5, N_E5, N_G5, N_C5, N_D5, N_E5,
								N_F5, N_F5, N_F5, N_F5, N_F5, N_E5, N_E5, N_E5, N_G5, N_G5, N_F5, N_D5, N_C5 };
int jingleBells_durations[] 	= { 4, 4, 8, 4, 4, 8, 4, 4, 4, 4, 16,
								4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 8, 8,
								4, 4, 8, 4, 4, 8, 4, 4, 4, 4, 16,
								4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 16 };
int jingleBells_tempo 		= 60;

// "The first noel" melody
int firstNoel[] 			= { N_E4, N_D4, N_C4, N_D4, N_E4, N_F4, N_G4, N_A4, N_B4, N_C5, N_B4, N_A4,
								N_G4, N_A4, N_B4, N_C5, N_B4, N_A4, N_G4, N_A4, N_B4, N_C5, N_G4, N_F4,
								N_E4, N_E4, N_D4, N_C4, N_D4, N_E4, N_F4, N_G4, N_A4, N_B4, N_C5, N_B4, N_A4,
								N_G4, N_A4, N_B4, N_C5, N_B4, N_A4, N_G4, N_A4, N_B4, N_C5, N_G4, N_F4,
								N_E4, N_E4, N_D4, N_C4, N_D4, N_E4, N_F4, N_G4, N_C5, N_B4, N_A4, N_A4,
								N_G4, N_C5, N_B4, N_A4, N_G4, N_A4, N_B4, N_C5, N_G4, N_F4, N_E4 };
int firstNoel_durations[] 	= { 2, 2, 6, 2, 2, 2, 8, 2, 2, 4, 4, 4,
								8, 2, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4,
								8, 2, 2, 6, 2, 2, 2, 8, 2, 2, 4, 4, 4,
								8, 2, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4,                             
								8, 2, 2, 6, 2, 2, 2, 8, 2, 2, 8, 4,
								12, 4, 4, 4, 4, 4, 4, 4, 4, 4, 8 };
int firstNoel_tempo 		= 60;

// "What child is this" melody
int whatChild[] 			= { N_E4, N_G4, N_A4, N_B4, N_C5, N_B4, N_A4, N_FS4, N_D4, N_E4, N_FS4, N_G4, N_E4, N_E4, N_DS4, N_E4, N_FS4, N_B3, N_REST,  N_E4,
								N_G4, N_A4, N_B4, N_C4, N_B4, N_A4, N_FS4, N_D4, N_E4, N_FS4, N_G4, N_FS4, N_E4, N_DS4, N_CS4, N_D4, N_E4, N_E4, N_REST,
								N_D5, N_D5, N_C5, N_B4, N_A4, N_FS4, N_D4, N_E4, N_FS4, N_G4, N_E4, N_E4, N_DS4, N_E4, N_FS4, N_DS4, N_B3, N_REST, 
								N_D5, N_D5, N_C5, N_B4, N_A4, N_FS4, N_D4, N_E4, N_FS4, N_G4, N_FS4, N_E4, N_DS4, N_CS4, N_D4, N_E4, N_E4 };
int whatChild_durations[] 	= { 2, 4, 2, 3, 1, 2, 4, 2, 3, 1, 2, 4, 2, 3, 1, 2, 6, 2, 2, 2,
								4, 2, 3, 1, 2, 4, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 6, 4, 2,
								6, 3, 1, 2, 4, 2, 3, 1, 2, 4, 2, 3, 1, 2, 4, 2, 4, 2,
								6, 3, 1, 2, 4, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 6, 4 }; 
int whatChild_tempo 		= 100;

// Declare melody structure
typedef struct {
   int *melody;
   int *durations;
   int tempo;
} tune;

// Debug info
#define DEBUG 		true

class Melody
{
public:
	Melody( int _pin ) {
		pin = _pin;
		// initialize speaker pin
    	pinMode(pin, OUTPUT);

    	tunes[0].melody = jingleBells;
    	tunes[0].durations = jingleBells_durations;
    	tunes[0].tempo = jingleBells_tempo;

    	tunes[1].melody = firstNoel;
    	tunes[1].durations = firstNoel_durations;
    	tunes[1].tempo = firstNoel_tempo;

    	tunes[2].melody = whatChild;
    	tunes[2].durations = whatChild_durations;
    	tunes[2].tempo = whatChild_tempo;
	};

	void play( void ) {
		play(0);
	};

	void play( int tuneNum ) {
		if(tuneNum < 0 || tuneNum == 0 || tuneNum >= numTunes)
			tuneNum = random(numTunes);
		else
			tuneNum--;

		int numNotes = sizeof(tunes[tuneNum].melody)/sizeof(int);
  		int tempo = tunes[tuneNum].tempo;
  		for (int thisNote = 0; thisNote < numNotes; thisNote++) {

		    int freq = tunes[tuneNum].melody[thisNote]*2;
		    int noteDuration = tempo*tunes[tuneNum].durations[thisNote];

		    if (freq > 0) {
				tone(pin, freq, noteDuration); 
			}

			delay(noteDuration);

			// to distinguish the notes, set a minimum time between them.
    		// the note's duration + 30% seems to work well:
    		int pauseBetweenNotes = noteDuration * 0.30;    
    		delay(pauseBetweenNotes);    
    
    		noTone(pin);
    	}
	};

private:
	int pin;
	tune tunes[numTunes];
};

#endif // __MELODY_H__
