
#ifndef MELODY_H
#define MELODY_H

#include "pitches.h"

// Debug info
#define DEBUG 		true

// declare melody count
uint8_t const numMelodies = 3;

// R2D2
uint16_t beep1[] = { N_A7, N_G7, N_E7, N_C7, N_D7, N_B7, N_F7, N_C8,
                     N_A7, N_G7, N_E7, N_C7, N_D7, N_B7, N_F7, N_C8,};
uint8_t beep1_durations[] = { 2, 2, 2, 2, 2, 2, 2, 2,
                               2, 2, 2, 2, 2, 2, 2, 2 };
uint8_t beep1_tempo = 40;

uint16_t beep2[] = { 343, 422 };
uint16_t beep2_durations[] = { 4, 3 };
uint16_t beep2_tempo = 111;

uint16_t beep3[] = { 500 };
uint16_t beep3_durations[] = { 5 };
uint16_t beep3_tempo = 100;

// "Jingle Bells" melody	      	
/*uint16_t jingleBells[] 			= { N_E5, N_E5, N_E5, N_E5, N_E5, N_E5, N_E5, N_G5, N_C5, N_D5, N_E5,
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

	void beep( uint8_t _beepCount ) {
		if( _beepCount < 0 )
			return;
		// set beep count
		beepCount = _beepCount;
		// reset index
		noteIndex = 0;
		notePause = 0;
		time = 0;
	};

	void play( void ) {
		// play random
		play(0);
	};

	void play( uint8_t _melodyNum ) {
		if( noteIndex < numNotes ) 
			return;

		if(_melodyNum < 0 || _melodyNum == 0 || _melodyNum > numMelodies)
			melodyNum = random(2, numMelodies);
		else
			melodyNum = _melodyNum;

		switch( melodyNum ) {
			case 1:
				numNotes = sizeof(beep1)/sizeof(int);
				//numNotes = sizeof(jingleBells)/sizeof(int);
			break;
			case 2:
				numNotes = sizeof(beep2)/sizeof(int);
			//	numNotes = sizeof(firstNoel)/sizeof(int);
			break;
			case 3:
				numNotes = sizeof(beep3)/sizeof(int);
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
		if( beepCount > 0 && noteIndex == 0 ) {
			// play beep melody
			play(1);
			beepCount--;
		}

		if( noteIndex >= numNotes || (millis() - time) < notePause )
			return;

		switch( melodyNum ) {
			case 1:
			//	notePause = playNote(noteIndex, beep1, beep1_durations, beep1_tempo);
			//	notePause = playNote(noteIndex, jingleBells, jingleBells_durations, jingleBells_tempo);
			break;
			case 2:
				notePause = playNote(noteIndex, beep2, beep2_durations, beep2_tempo);
			//	notePause = playNote(noteIndex, firstNoel, firstNoel_durations, firstNoel_tempo);
			break;
			case 3:
				notePause = playNote(noteIndex, beep3, beep3_durations, beep3_tempo);
			//	notePause = playNote(noteIndex, whatChild, whatChild_durations, whatChild_tempo);
			break;
		}

		noteIndex++;
		time = millis();	
	};

private:
	uint8_t pin;
	uint8_t beepCount;
	uint8_t melodyNum;
	uint16_t *melody;
	uint8_t *duration;	
    uint16_t numNotes;
	uint16_t noteIndex;
	uint16_t notePause;
	unsigned long time;

	void compileMelody() {
		switch( melodyNum ) {
			case 1:
				uint16_t jingleBells[]  	= { N_E5, N_E5, N_E5, N_E5, N_E5, N_E5, N_E5, N_G5, 
												N_C5, N_D5, N_E5, N_F5, N_F5, N_F5, N_F5, N_F5, 
												N_E5, N_E5, N_E5, N_E5, N_D5, N_D5, N_E5, N_D5, 
												N_G5, N_E5, N_E5, N_E5, N_E5, N_E5, N_E5, N_E5, 
												N_G5, N_C5, N_D5, N_E5, N_F5, N_F5, N_F5, N_F5, 
												N_F5, N_E5, N_E5, N_E5, N_G5, N_G5, N_F5, N_D5, 
												N_C5 };
				melody = jingleBells;

				uint8_t jingleBells_dur[] 	= { 4, 	  4,    8,    4,    4,    8,    4,    4, 
												4,    4,   16,    4,    4,    4,    4,    4, 
												4,    4,    4,    4,    4,    4,    4,    8, 
												8,    4,    4,    8,    4,    4,    8,    4, 
												4,    4,    4,   16,    4,    4,    4,    4, 
												4,    4,    4,    4,    4,    4,    4,    4, 
												16 };
				duration = jingleBells_dur;
			break;
		}

	};

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
