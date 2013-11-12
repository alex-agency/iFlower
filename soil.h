
#ifndef SOIL_H
#define SOIL_H

#define OFF				-1
#define EXTRA_DRY		1
#define DRY 			2
#define PARTLY_DRY		3
#define PARTLY_WET		4
#define WET 			5
#define EXTRA_WET		6

const int sensitivity = 1;

class Soil
{
public:
	Soil( int _sensor_pin ) {
		sensor_pin = _sensor_pin;
		// initialize
		pinMode(sensor_pin, INPUT_PULLUP);
	};

	int read() {
  	        delay(100);
                int value = analogRead(sensor_pin);
    		
                printf("SOIL: Info: pin: %d, ", sensor_pin);
                printf(" value: %d.\n\r", value);

  		if( value > 1000 )
  			return OFF;
  		else
  			if( value < 200 )
  				return EXTRA_WET;
  			else
  				if( value < 350 )
  					return WET;
  				else
  					if( value < 500 )
  						return PARTLY_WET;
  					else
  						if( value < 650 )
  							return PARTLY_DRY;
  						else
  							if( value < 800 )
  								return DRY;
  		return OFF;
	};

private:
	int sensor_pin;
};

#endif // __SOIL_H__
