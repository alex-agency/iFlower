
#ifndef LED_H
#define LED_H

#define OFF			0
#define RED			1
#define GREEN		2

const int blink_delay_start = 3000; //ms
const int blink_delay_on = 800; 	//ms
const int blink_delay_off = 400; 	//ms

class led
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
	};

	void set( int _state ) {
		set_blink(_state, 0);
	};

	void update( void ) {
		// return if nothing update
		if( previous_state == state && blink_count == 0 ) 
			return;
		// blinking if need
		if( blink_count > 0 ) {

			if( time == 0 ) {
				time = millis();
				// do off
				write(OFF);
				return;
			} 

			unsigned long delay = millis() - time;

			if( delay < blink_delay_start ) {
				// do off
				write(OFF);
				return;
			}

			if ( delay < )

			time = millis();
		}
		// change led
		write(state);
	};

private:
	int pin_green;
	int pin_red;
	int state = OFF;
	int previous_state = OFF;
	int blink_count = 0;
	unsigned long time = 0;

	void write( int state ) {
		if( state == RED ) {
			// enable red led
	    	digitalWrite(pin_red, HIGH);
	    	digitalWrite(pin_green, LOW);
		} else
			if( state == GREEN ) {
				// enable green led
		    	digitalWrite(pin_green, HIGH);
		    	digitalWrite(pin_red, LOW);
			} else
				if( state == OFF ) {
					// disable led
					digitalWrite(pin_green, LOW);
		    		digitalWrite(pin_red, LOW);
				}
	}; 
};

#endif // __LED_H__