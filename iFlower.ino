// Import libraries
#include <SPI.h>
#include "printf.h"
//#include "nRF24L01.h"
//#include "RF24.h"
//#include "Mesh.h"
#include "dht11.h"
#include "SimpleMap.h"
#include "timer.h"
#include <Wire.h>
#include "DS1307new.h"
#include "led.h"
#include "soil.h"
#include "melody.h"

// Debug info
#define DEBUG   true

// Declare SPI bus pins
//#define CE_PIN  9
//#define CS_PIN  10
// Set up nRF24L01 radio
//RF24 radio(CE_PIN, CS_PIN);
// Set up network
//Mesh mesh(radio);
// Declare radio channel 0-127
//const uint8_t channel = 76;
// Declare unique node id
//const uint16_t node_id = 222;
// Declare base id, base always has 00 id
//const uint16_t base_id = 00;

// Declare DHT11 sensor digital pin
#define DHT11PIN  3
// Declare state map keys
#define HUMIDITY  "humidity"
#define TEMPERATURE  "temperature"

// Set up LED digital pins
Led led(5, 6); // (green, red) 

// Declare state map keys
#define CDN  "CDN" // days after 2000-01-01
#define TIME  "TIME" // seconds after 00:00:00

// Set up SOIL sensors analog pins
Soil soil_1(A0);
Soil soil_2(A1);
Soil soil_3(A2);
Soil soil_4(A3);
// Declare state map keys
#define SOIL1  "soil1"
#define SOIL2  "soil2"
#define SOIL3  "soil3"
#define SOIL4  "soil4"

// Set up Speaker digital pin
Melody melody(4);
// Declare interval for play melody
const uint16_t alarm_interval = 1800; // seconds
uint32_t last_time_alarm;

// Declare state map
struct comparator {
  bool operator()(const char* &str1, const char* &str2) {
    return strcmp(str1, str2) == 0;
  }
};
SimpleMap<const char*, int, 9, comparator> states;

// Declare delay manager in ms
timer_t timer(15000);

//
// Setup
//
void setup()
{
  // Configure console
  Serial.begin(57600);
  printf_begin();

  // initialize radio
  //radio.begin();
  // initialize network
  //mesh.begin(channel, node_id);

  // Shift NV-RAM address 0x08 for RTC
  RTC.setRAM(0, (uint8_t *)0x0000, sizeof(uint16_t));
}

//
// Loop
//
void loop()
{  
  if( timer ) {    
    // read sensors
    read_DHT11();
    read_soil();
    read_time();

    // check values
    check();
  }

  // update led
  led.update();
  
  // update melody
  melody.update();

  // send values to base
  /*if( mesh.ready() && timer ) {      
    // send DHT11 sensor values
    Payload payload1(HUMIDITY, states[HUMIDITY]);
    mesh.send(payload1, base_id);
    Payload payload2(TEMPERATURE, states[TEMPERATURE]);
    mesh.send(payload2, base_id);

    // send time value
    Payload payload3(TIME2000, states[TIME2000]);
    mesh.send(payload3, base_id);

    // send Soil sensors values
    if(states[SOIL1] != -1) {
      Payload payload4(SOIL1, states[SOIL1]);
      mesh.send(payload4, base_id);
    }
    if(states[SOIL2] != -1) {    
      Payload payload5(SOIL2, states[SOIL2]);
      mesh.send(payload5, base_id);
    }
    if(states[SOIL3] != -1) {    
      Payload payload6(SOIL3, states[SOIL3]);
      mesh.send(payload6, base_id);
    }
    if(states[SOIL4] != -1) {    
      Payload payload7(SOIL4, states[SOIL4]);
      mesh.send(payload7, base_id);
    }
  }*/
  
  // update network
  //mesh.update();
  
  // read message if available
  /*while( mesh.available() ) {
    Payload payload;
    mesh.read(payload);
    
    // set new time
    if(payload.key == TIME2000) {
      set_time(payload.value);
    }
  }*/
}

/****************************************************************************/

bool read_DHT11() {
  dht11 DHT11;
  int state = DHT11.read(DHT11PIN);
  switch (state) {
    case DHTLIB_OK:
      states[HUMIDITY] = DHT11.humidity;
      states[TEMPERATURE] = DHT11.temperature;

      if(DEBUG) printf_P(PSTR("DHT11: Info: Sensor values: humidity: %d, temperature: %d.\n\r"), 
                  states[HUMIDITY], states[TEMPERATURE]);
      return true;
    case DHTLIB_ERROR_CHECKSUM:
      printf_P(PSTR("DHT11: Error: Checksum test failed!: The data may be incorrect!\n\r"));
      return false;
    case DHTLIB_ERROR_TIMEOUT: 
      printf_P(PSTR("DHT11: Error: Timeout occured!: Communication failed!\n\r"));
      return false;
    default: 
      printf_P(PSTR("DHT11: Error: Unknown error!\n\r"));
      return false;
  }
}

/****************************************************************************/

void read_time() {
  RTC.getRAM(54, (uint8_t *)0xaa55, sizeof(uint16_t));
  RTC.getTime();
  states[CDN] = RTC.cdn;
  states[TIME] = RTC.hour*60*60+RTC.minute*60+RTC.second;

  if(DEBUG) printf_P(PSTR("RTC: Info: CDN: %d -> %d-%d-%d, TIME: %d -> %d:%d:%d.\n\r"), 
              states[CDN], RTC.year, RTC.month, RTC.day, 
              states[TIME], RTC.hour, RTC.minute, RTC.second);
}

/****************************************************************************/

void set_time(int _cdn, int _time) {
  RTC.setRAM(54, (uint8_t *)0xffff, sizeof(uint16_t));
  RTC.getRAM(54, (uint8_t *)0xffff, sizeof(uint16_t));
  RTC.stopClock();
  
  if(_cdn > 0) {
    RTC.fillByCDN(_cdn);
    printf_P(PSTR("RTC: Warning: set new CDN: %d.\n\r"), _cdn);  	
  }

  if(_time > 0) {
    uint8_t seconds = _time % 60;
    _time /= 60;
    uint8_t minutes = _time % 60;
    _time /= 60;
    uint8_t hours = _time % 24;
    RTC.fillByHMS(hours, minutes, seconds);
    printf_P(PSTR("RTC: Warning: set new time: %d:%d:%d.\n\r"), 
      hours, minutes, seconds );
  }

  RTC.setTime();
  RTC.setRAM(54, (uint8_t *)0xaa55, sizeof(uint16_t));
  RTC.startClock();
}

/****************************************************************************/

void read_soil() {
  states[SOIL1] = soil_1.read();
  states[SOIL2] = soil_2.read();
  states[SOIL3] = soil_3.read();
  states[SOIL4] = soil_4.read();

  if(DEBUG) printf_P(PSTR("SOIL: Info: Soil1: %s, Soil2: %s, Soil3: %s, Soil4: %s.\n\r"), 
              convert_soil(states[SOIL1]), convert_soil(states[SOIL2]), 
              convert_soil(states[SOIL3]), convert_soil(states[SOIL4]));
}

/****************************************************************************/

char* convert_soil(int state) {
	switch( state ) {
		case EXTRA_DRY:
			return "EXTRA DRY";
		break;
		case DRY:
			return "DRY";
		break;
		case PARTLY_DRY:
			return "PARTLY DRY";
		break;
		case PARTLY_WET:
			return "PARTLY WET";
		break;
		case WET:
			return "WET";
		break;
		case EXTRA_WET:
			return "EXTRA WET";
	}
	return "OFF";
}

/****************************************************************************/

void check() {
  led.set_blink(LED_GREEN, 1);

  check_soil(1, states[SOIL1]);
  check_soil(2, states[SOIL2]);
  check_soil(3, states[SOIL3]);
  check_soil(4, states[SOIL4]);

  if( states[TEMPERATURE] < 13 || states[TEMPERATURE] > 28 ) {
    alarm(0);
    printf_P(PSTR("CHECK: WARNING: Temperature: %d!\n\r"), states[TEMPERATURE]); 
  }

  if( states[HUMIDITY] < 35 && states[TEMPERATURE] > 25 ) {
    led.set(LED_RED);
    printf_P(PSTR("CHECK: WARNING: Humidity too low: %d!\n\r"), states[HUMIDITY]);
  }
}

/****************************************************************************/

void check_soil(int sensor, int state) {
  if( state != OFF && state <= DRY ) {
    alarm(sensor);
    printf_P(PSTR("CHECK: WARNING: Soil with sensor #%d need water! Its state: %s.\n\r"), 
      sensor, convert_soil(state));
  }
}

/****************************************************************************/

void alarm(int mode) {
  led.set_blink(LED_RED, mode);
  melody.beep(mode);	  	
  
  // sleeping time
  if( RTC.dow == 0 || RTC.dow == 6 || RTC.hour < 11 || RTC.hour > 19 ) {
    return;
  }

  int duration = states[TIME] - last_time_alarm;
  // do alarm each time interval
  if( duration > alarm_interval ) {
    last_time_alarm = states[TIME];
    if(DEBUG) printf_P(PSTR("CHECK: Info: Play alarm every %d sec.\n\r"), duration);
    
    melody.play();
  }
}

/****************************************************************************/
