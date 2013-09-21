// Import libraries
#include <SPI.h>
#include "printf.h"
#include "nRF24L01.h"
#include "RF24.h"
#include "Mesh.h"
#include "dht11.h"
#include "SimpleMap.h"
#include "timer.h"
#include <Wire.h>
#include "DS1307new.h"

// Declare SPI bus pins
#define CE_PIN  9
#define CS_PIN  10
// Set up nRF24L01 radio
RF24 radio(CE_PIN, CS_PIN);
// Set up network
Mesh mesh(radio);
// Declare radio channel 0-127
const uint8_t channel = 76;
// Declare unique node id
const uint16_t node_id = 1002;
// Declare base id, base always has 00 id
const uint16_t base_id = 00;

// Declare DHT11 sensor digital pin
#define DHT11PIN  3
// Declare state map keys
#define HUMIDITY  "humidity"
#define TEMPERATURE  "temperature"

// Declare LED digital pins
#define LEDREDPIN  6
#define LEDGREENPIN  5
// Declare state map keys
#define LED_RED  "red_led"
#define LED_GREEN  "green_led"
// Declare state value
#define LED_OFF  0

// Declare state map keys
#define TIME2000  "time2000"

// Declare soil sensors pins
#define SOIL1PIN  A0  
#define SOIL2PIN  A1
#define SOIL3PIN  A2
#define SOIL4PIN  A3
// Declare state map keys
#define SOIL1  "soil1"
#define SOIL2  "soil2"
#define SOIL3  "soil3"
#define SOIL4  "soil4"

// Declare state map
struct comparator {
  bool operator()(const char* &str1, const char* &str2) {
    return strcmp(str1, str2) == 0;
  }
};
SimpleMap<const char*, int, 9, comparator> states;

// Declare delay manager in ms
timer_t send_timer(60000);

// Debug info.
const bool DEBUG = true;

//
// Setup
//
void setup()
{
  // Configure console
  Serial.begin(57600);
  printf_begin();

  // initialize radio
  radio.begin();
  // initialize network
  mesh.begin(channel, node_id);

  // Shift NV-RAM address 0x08 for RTC
  RTC.setRAM(0, (uint8_t *)0x0000, sizeof(uint16_t));
}

//
// Loop
//
void loop()
{  
  if( mesh.ready() && send_timer ) {
    led_blink(LED_GREEN, false);
        
    // send DHT11 sensor values
    read_DHT11();
    Payload payload1(HUMIDITY, states[HUMIDITY]);
    mesh.send(payload1, base_id);
    Payload payload2(TEMPERATURE, states[TEMPERATURE]);
    mesh.send(payload2, base_id);

    // send time value
    read_time();
    Payload payload3(TIME2000, states[TIME2000]);
    mesh.send(payload3, base_id);

    // send Soil sensors values
    read_soil();
    if(states[SOIL1] > 0) {
      Payload payload4(SOIL1, states[SOIL1]);
      mesh.send(payload4, base_id);
    }
    if(states[SOIL2] > 0) {    
      Payload payload5(SOIL2, states[SOIL2]);
      mesh.send(payload5, base_id);
    }
    if(states[SOIL3] > 0) {    
      Payload payload6(SOIL3, states[SOIL3]);
      mesh.send(payload6, base_id);
    }
    if(states[SOIL4] > 0) {    
      Payload payload7(SOIL4, states[SOIL4]);
      mesh.send(payload7, base_id);
    }

    led_blink(LED_OFF, false);
  }
  
  // update network
  mesh.update();
  
  // is new payload message available?
  while( mesh.available() ) {
    Payload payload;
    mesh.read(payload);
    
    // set new time
    if(payload.key == TIME2000) {
      set_time(payload.value);
    }

  }
}

/****************************************************************************/

void led_blink(const char* led, bool blink) {
  // blinking
  if(blink && states[led]) {
    led = LED_OFF;
  }
  // clear all states
  states[LED_RED] = false;
  states[LED_GREEN] = false;

  if(strcmp(led, LED_RED) == 0) {
    // initialize led pins
    pinMode(LEDREDPIN, OUTPUT);
    // enable red led
    digitalWrite(LEDREDPIN, HIGH);
    digitalWrite(LEDGREENPIN, LOW);
    // save state
    states[LED_RED] = true;
  } 
  else if(strcmp(led, LED_GREEN) == 0) {
    // initialize led pins
    pinMode(LEDGREENPIN, OUTPUT);
    // enable green led
    digitalWrite(LEDGREENPIN, HIGH);
    digitalWrite(LEDREDPIN, LOW);
    // save state
    states[LED_GREEN] = true;
  } 
  else {
    // disable leds
    digitalWrite(LEDREDPIN, LOW);
    digitalWrite(LEDGREENPIN, LOW);
  }
}

/****************************************************************************/

bool read_DHT11() {
  dht11 DHT11;
  int state = DHT11.read(DHT11PIN);
  switch (state) {
    case DHTLIB_OK:
      states[HUMIDITY] = DHT11.humidity;
      states[TEMPERATURE] = DHT11.temperature;

      if(DEBUG) printf("DHT11: Info: Sensor values: humidity: %d, temperature: %d.\n\r", 
                  states[HUMIDITY], states[TEMPERATURE]);
      return true;
    case DHTLIB_ERROR_CHECKSUM:
      printf("DHT11: Error: Checksum test failed!: The data may be incorrect!\n\r");
      return false;
    case DHTLIB_ERROR_TIMEOUT: 
      printf("DHT11: Error: Timeout occured!: Communication failed!\n\r");
      return false;
    default: 
      printf("DHT11: Error: Unknown error!\n\r");
      return false;
  }
}

/****************************************************************************/

void read_time() {
  RTC.getRAM(54, (uint8_t *)0xaa55, sizeof(uint16_t));
  RTC.getTime();
  states[TIME2000] = RTC.time2000; // seconds after 2000-01-01 00:00

  if(DEBUG) printf("RTC: Info: time2000: %d.\n\r", states[TIME2000]);
}

/****************************************************************************/

void set_time(uint32_t time2000) {
  RTC.setRAM(54, (uint8_t *)0xffff, sizeof(uint16_t));
  RTC.getRAM(54, (uint8_t *)0xffff, sizeof(uint16_t));
  RTC.stopClock();

  RTC.fillByTime2000(time2000);
  
  RTC.setTime();
  RTC.setRAM(54, (uint8_t *)0xaa55, sizeof(uint16_t));
  RTC.startClock();
}

/****************************************************************************/

void read_soil() {
  const int sensitivity = 100;
  uint16_t sensor1, sensor2, sensor3, sensor4 = 0;
  uint16_t value1, value2, value3, value4 = 0;

  // initialize sensors
  pinMode(SOIL1PIN, INPUT_PULLUP);
  pinMode(SOIL2PIN, INPUT_PULLUP);
  pinMode(SOIL3PIN, INPUT_PULLUP);
  pinMode(SOIL4PIN, INPUT_PULLUP);

  // get maximum value
  for(int i = 0; i < sensitivity; i++) {
    // read first sensor
    sensor1 = analogRead(SOIL1PIN);
    if(sensor1 != 0 && sensor1 > value1) {
      value1 = sensor1;
    }
    // read second sensor
    sensor2 = analogRead(SOIL2PIN);
    if(sensor2 != 0 && sensor2 > value2) {
      value2 = sensor2;
    }
    // read third sensor
    sensor3 = analogRead(SOIL3PIN);
    if(sensor3 != 0 && sensor3 > value3) {
      value3 = sensor3;
    }
    // read forth sensor
    sensor4 = analogRead(SOIL4PIN);
    if(sensor4 != 0 && sensor4 > value4) {
      value4 = sensor4;
    }
    delay(50);
  }

  states[SOIL1] = value1;
  states[SOIL2] = value2;
  states[SOIL3] = value3;
  states[SOIL4] = value4;

  if(DEBUG) printf("SOIL: Info: Sensor1: %d, Sensor2: %d, Sensor3: %d, Sensor4: %d.\n\r", 
    value1, value2, value3, value4);
}

