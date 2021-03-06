
#ifndef SOIL_H
#define SOIL_H

#define OFF          -1
#define EXTRA_DRY     1
#define DRY           2
#define PARTLY_DRY    3
#define PARTLY_WET    4
#define WET           5
#define EXTRA_WET     6

// Debug info
#define DEBUG         false

class Soil
{
public:
	Soil( int _sensor_pin ) {
		sensor_pin = _sensor_pin;
	};

	int read() {
    // initialize
    pinMode(sensor_pin, INPUT_PULLUP);
    delay(10); // short delay before read analog
    int value = analogRead(sensor_pin);

    if(DEBUG) printf_P(PSTR("SOIL: Info: pin: %d, value: %d, "),
      sensor_pin, value);

		if( value < 300 ) {
      if(DEBUG) printf_P(PSTR("state: EXTRA WET.\n\r"));
				return EXTRA_WET;
    }
  		else 
  			if( value < 400 ) {
        if(DEBUG) printf_P(PSTR("state: WET.\n\r"));
  				return WET;
      }
  			else
  				if( value < 500 ) {
  					if(DEBUG) printf_P(PSTR("state: PARTLY WET.\n\r"));
          return PARTLY_WET;
        }
  				else
  					if( value < 600 ) {
  						if(DEBUG) printf_P(PSTR("state: PARTLY DRY.\n\r"));
            return PARTLY_DRY;
          }
  					else
  						if( value < 900 ) {
  							if(DEBUG) printf_P(PSTR("state: DRY.\n\r"));
              return DRY;
            }
      
    if(DEBUG) printf_P(PSTR("state: OFF.\n\r"));
    return OFF;
	};

private:
	int sensor_pin;
};

#endif // __SOIL_H__
