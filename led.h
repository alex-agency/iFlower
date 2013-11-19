
#ifndef LED_H
#define LED_H

#define LED_OFF		0
#define LED_RED		1
#define LED_GREEN	2

const int blink_delay_start = 3000; //ms
const int blink_delay_on = 800; 	//ms
const int blink_delay_off = 400; 	//ms

// Debug info
#define DEBUG 		true

class Led
{
public:
	Led( int _pin_green, int _pin_red ) {
		pin_green = _pin_green;
		pin_red = _pin_red;
		// initialize led pins
    	pinMode(_pin_green, OUTPUT);
    	pinMode(_pin_red, OUTPUT);
	};

	void set_blink( int _state, int _blink_count ) {
		previous_state = state;
		state = _state;
		blink_count = _blink_count;
		time = 0;
		if(DEBUG) printf_P(PSTR("LED: Info: state: %d, blink count: %d.\n\r"),
        	_state, _blink_count);
	};

	void set( int _state ) {
		set_blink(_state, -1);
	};

	void update( void ) {
		// return if nothing update
		if( previous_state == state && blink_count == 0 ) 
			return;

		if( blink_count == -1 ) {
			// reset time
			time = 0;
		}

		// blinking if need
		if( blink_count >= 0 ) {

			if( time == 0 ) {
				time = millis();
				// do off
				write(LED_OFF);
				if(DEBUG) printf_P(PSTR("LED: Info: Blinking Start delay...\n\r"));
				return;
			} 

			unsigned long delay = millis() - time;

			if( blink_count == 0 && delay > blink_delay_start ) {
				blink_count = -1;
				if(DEBUG) printf_P(PSTR("LED: Info: Blinking ON delay...\n\r"));
				return;
			}	

			if( previous_state == LED_OFF && delay < blink_delay_start ) {
				// wait 'off' delay
				return;
			} 

			if( blink_count == 0 ) {
				blink_count = -1;
				if(DEBUG) printf_P(PSTR("LED: Info: Blinking ended.\n\r"));
				return;
			}

			if( previous_state == LED_OFF && delay >= blink_delay_start ) {
				// enable led
				write(state);
				time = millis();
				if(DEBUG) printf_P(PSTR("LED: Info: Blinking ON delay...\n\r"));
				return;
			}

			if ( previous_state != LED_OFF && delay >= blink_delay_on ) {
				// do off
				write(LED_OFF);
				// shift time for short off
				time = millis() - (blink_delay_start - blink_delay_off);
				blink_count --;
				if(DEBUG) printf_P(PSTR("LED: Info: Blinking OFF delay, %d blinks left.\n\r"),
					blink_count);
				return;
			} 
			else {
				// wait 'on' delay
				return;
			}
		}
		
		// change led
		write(state);
	};

private:
	int pin_green;
	int pin_red;
	int state;
	int previous_state;
	int blink_count;
	unsigned long time;

	void write( int state ) {
		if(DEBUG) printf_P(PSTR("LED: Info: "));

		if( state == LED_RED ) {
			// enable red led
	    	digitalWrite(pin_red, HIGH);
	    	digitalWrite(pin_green, LOW);

	    	if(DEBUG) printf_P(PSTR("enabled RED led, "));
		} else
			if( state == LED_GREEN ) {
				// enable green led
		    	digitalWrite(pin_green, HIGH);
		    	digitalWrite(pin_red, LOW);

		    	if(DEBUG) printf_P(PSTR("enabled GREEN led, "));
			} else
				if( state == LED_OFF ) {
					// disable led
					digitalWrite(pin_green, LOW);
		    		digitalWrite(pin_red, LOW);

		    		if(DEBUG) printf_P(PSTR("led disabled, "));
				}
		// save previous state
		previous_state = state;
		if(DEBUG) printf_P(PSTR("new state: %d, previous state: %d.\n\r"),
			state, previous_state);
	}; 
};

#endif // __LED_H__
