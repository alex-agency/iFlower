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

// Declare DS1307 digital pin
#define DS1307PIN  2
// Declare state map keys
#define TIME2000  "time2000"

// Declare state map
struct comparator {
  bool operator()(const char* &str1, const char* &str2) {
    return strcmp(str1, str2) == 0;
  }
};
SimpleMap<const char*, int, 8, comparator> states;

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

  // initialize I2C for RTC
  pinMode(DS1307PIN, INPUT);
  digitalWrite(DS1307PIN, HIGH);
  // Shift NV-RAM address 0x08  
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

    led_blink(LED_OFF, false);
  }
  
  // update network
  mesh.update();
  
  // is new payload message available?
  while( mesh.available() ) {
    Payload payload;
    mesh.read(payload);
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
}

/****************************************************************************/

void set_time(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute) {
  RTC.setRAM(54, (uint8_t *)0xffff, sizeof(uint16_t));
  RTC.getRAM(54, (uint8_t *)0xffff, sizeof(uint16_t));
  RTC.stopClock();

  RTC.fillByYMD(year, month, day);
  RTC.fillByHMS(hour, minute, 0);
  
  RTC.setTime();
  RTC.setRAM(54, (uint8_t *)0xaa55, sizeof(uint16_t));
  RTC.startClock();
}
