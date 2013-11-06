
#ifndef SOIL_H
#define SOIL_H

#define OFF				-1
#define EXTRA_DRY		1
#define DRY 			2
#define PARTLY_DRY		3
#define PARTLY_WET		4
#define WET 			5
#define EXTRA_WET		6

const int sensitivity = 50;

class Soil
{
public:
	Soil( int _sensor_pin ) {
		sensor_pin = _sensor_pin;
		// initialize
		pinMode(sensor_pin, INPUT_PULLUP);
	};

	int read() {
		int value, sensor = 0;
		// get maximum value
  		for(int i = 0; i < sensitivity; i++) {
  			sensor = analogRead(sensor_pin);
    		if(sensor != 0 && sensor > value) {
      			value = sensor;
    		}
    		delay(50);
  		}

  		if( value < 10 )
  			return OFF;
  		else
  			if( value < 100 )
  				return DRY;
  			else
  				if( value < 200 )
  					return PARTLY_DRY;
  				else
  					if( value < 300 )
  						return PARTLY_WET;
  					else
  						if( value < 400 )
  							return WET;
  						else
  							if( value < 512 )
  								return EXTRA_WET;
  		return OFF;
	};

private:
	int sensor_pin;
};

#endif // __SOIL_H__
