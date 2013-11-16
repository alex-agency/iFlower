
#ifndef MELODY_H
#define MELODY_H

#include "pitches.h"

// Debug info
#define DEBUG 		true

// declare melody count
uint8_t const numMelodies = 2;

// "Jingle Bells" melody	      	
uint16_t jingleBells[] 				= { N_E5, N_E5, N_E5, N_E5, N_E5, N_E5, N_E5, N_G5, N_C5, N_D5, N_E5,
										N_F5, N_F5, N_F5, N_F5, N_F5, N_E5, N_E5, N_E5, N_E5, N_D5, N_D5, N_E5, N_D5, N_G5,
										N_E5, N_E5, N_E5, N_E5, N_E5, N_E5, N_E5, N_G5, N_C5, N_D5, N_E5,
										N_F5, N_F5, N_F5, N_F5, N_F5, N_E5, N_E5, N_E5, N_G5, N_G5, N_F5, N_D5, N_C5 };
uint16_t jingleBells_durations[] 	= { 4, 4, 8, 4, 4, 8, 4, 4, 4, 4, 16,
										4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 8, 8,
										4, 4, 8, 4, 4, 8, 4, 4, 4, 4, 16,
										4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 16 };
uint16_t jingleBells_tempo 			=	60;	

// "The first noel" melody
/*uint16_t firstNoel[] 				= { N_E4, N_D4, N_C4, N_D4, N_E4, N_F4, N_G4, N_A4, N_B4, N_C5, N_B4, N_A4,
										N_G4, N_A4, N_B4, N_C5, N_B4, N_A4, N_G4, N_A4, N_B4, N_C5, N_G4, N_F4,
										N_E4, N_E4, N_D4, N_C4, N_D4, N_E4, N_F4, N_G4, N_A4, N_B4, N_C5, N_B4, N_A4,
										N_G4, N_A4, N_B4, N_C5, N_B4, N_A4, N_G4, N_A4, N_B4, N_C5, N_G4, N_F4,
										N_E4, N_E4, N_D4, N_C4, N_D4, N_E4, N_F4, N_G4, N_C5, N_B4, N_A4, N_A4,
										N_G4, N_C5, N_B4, N_A4, N_G4, N_A4, N_B4, N_C5, N_G4, N_F4, N_E4 };
uint16_t firstNoel_durations[] 		= { 2, 2, 6, 2, 2, 2, 8, 2, 2, 4, 4, 4,
										8, 2, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4,
										8, 2, 2, 6, 2, 2, 2, 8, 2, 2, 4, 4, 4,
										8, 2, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4,                             
										8, 2, 2, 6, 2, 2, 2, 8, 2, 2, 8, 4,
										12, 4, 4, 4, 4, 4, 4, 4, 4, 4, 8 };
uint16_t firstNoel_tempo 			=	60;

// "What child is this" melody
uint16_t whatChild[] 				= { N_E4, N_G4, N_A4, N_B4, N_C5, N_B4, N_A4, N_FS4, N_D4, N_E4, N_FS4, N_G4, N_E4, N_E4, N_DS4, N_E4, N_FS4, N_B3, N_REST,  N_E4,
										N_G4, N_A4, N_B4, N_C4, N_B4, N_A4, N_FS4, N_D4, N_E4, N_FS4, N_G4, N_FS4, N_E4, N_DS4, N_CS4, N_D4, N_E4, N_E4, N_REST,
										N_D5, N_D5, N_C5, N_B4, N_A4, N_FS4, N_D4, N_E4, N_FS4, N_G4, N_E4, N_E4, N_DS4, N_E4, N_FS4, N_DS4, N_B3, N_REST, 
										N_D5, N_D5, N_C5, N_B4, N_A4, N_FS4, N_D4, N_E4, N_FS4, N_G4, N_FS4, N_E4, N_DS4, N_CS4, N_D4, N_E4, N_E4 };
uint16_t whatChild_durations[] 		= { 2, 4, 2, 3, 1, 2, 4, 2, 3, 1, 2, 4, 2, 3, 1, 2, 6, 2, 2, 2,
										4, 2, 3, 1, 2, 4, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 6, 4, 2,
										6, 3, 1, 2, 4, 2, 3, 1, 2, 4, 2, 3, 1, 2, 4, 2, 4, 2,
										6, 3, 1, 2, 4, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 6, 4 };
uint16_t whatChild_tempo 			=	100;*/

class Melody
{
public:
	Melody( uint8_t _pin ) {
		pin = _pin;
		// initialize speaker pin
    	pinMode(pin, OUTPUT);
	};

	void play( void ) {
		play(0);
	};

	void play( uint8_t _melodyNum ) {
		if( noteIndex < numNotes ) 
			return;

		if(_melodyNum < 0 || _melodyNum == 0 || _melodyNum > numMelodies)
			melodyNum = random(1, numMelodies);
		else
			melodyNum = _melodyNum;

		switch( melodyNum ) {
			case 1:
				numNotes = sizeof(jingleBells)/sizeof(int);
			break;
			case 2:
			//	numNotes = sizeof(firstNoel)/sizeof(int);
			break;
			case 3:
			//	numNotes = sizeof(whatChild)/sizeof(int);
			break;
		}

		if(DEBUG) printf_P(PSTR("Melody: Info: Play melody #%u with %u notes.\n\r"),
			melodyNum, numNotes);

		noteIndex = 0;
		notePause = 0;
		time = 0;
	};

	void update( void ) {
		
		if( noteIndex >= numNotes || (millis() - time) < notePause )
			return;

		switch( melodyNum ) {
			case 1:
				notePause = playNote(noteIndex, jingleBells, jingleBells_durations, jingleBells_tempo);
			break;
			case 2:
			//	notePause = playNote(noteIndex, firstNoel, firstNoel_durations, firstNoel_tempo);
			break;
			case 3:
			//	notePause = playNote(noteIndex, whatChild, whatChild_durations, whatChild_tempo);
			break;
		}

		noteIndex++;
		time = millis();	
	};

private:
	uint8_t pin;
	uint8_t melodyNum;	
    uint16_t numNotes;
	uint16_t noteIndex;
	uint16_t notePause;
	unsigned long time;

	uint16_t playNote( uint16_t _noteIndex, uint16_t* _melody, uint16_t* _durations, uint16_t _tempo ) {
		noTone(pin);
		
		uint16_t freq = _melody[_noteIndex] * 2;
		uint16_t noteDuration = _tempo * _durations[_noteIndex];

		if (freq > 0) {
			tone(pin, freq, noteDuration); 
		}

		// to distinguish the notes, set a minimum time between them.
		// the note's duration + 30% seems to work well:
		return noteDuration + (noteDuration * 0.30);
	};
};

#endif // __MELODY_H__
