
/*
 Copyright (C) 2011 James Coliz, Jr. <maniacbug@ymail.com>
 
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

/**
 * @file sleep.cpp 
 *
 * Sleep helpers, definitions
 */

#include "RF24Network_config.h"

#include <avr/power.h>
#include <avr/sleep.h>
#include "sleep.h" 

sleep_c Sleep;

/******************************************************************/

void sleep_c::begin(wdt_prescalar_e prescalar_in,short cycles)
{
  sleep_cycles_remaining = cycles;
  sleep_cycles_per_transmission = cycles;

  uint8_t prescalar = min(9,(uint8_t)prescalar_in);
  uint8_t wdtcsr = prescalar & 7;
  if ( prescalar & 8 )
      wdtcsr |= _BV(WDP3);

  MCUSR &= ~_BV(WDRF);
  WDTCSR = _BV(WDCE) | _BV(WDE);
  WDTCSR = _BV(WDCE) | wdtcsr | _BV(WDIE);
}

/******************************************************************/

void sleep_c::go(void)
{
  while( sleep_cycles_remaining-- )
  {
    set_sleep_mode(SLEEP_MODE_PWR_DOWN); 

    power_adc_disable();
    power_spi_disable();
    power_twi_disable();
    power_usart0_disable();
    power_timer0_disable();
    power_timer1_disable();
    power_timer2_disable();

    // Unpower functions
    PRR = 0xFF;

    sleep_mode();
  }
  
  sleep_cycles_remaining = sleep_cycles_per_transmission;

  // Re-enable functions
  power_all_enable();

  power_adc_enable();
  power_spi_enable();
  power_twi_enable();
  power_usart0_enable();
  power_timer0_enable();
  power_timer1_enable();
  power_timer2_enable();
}

ISR(WDT_vect) {
}

// vim:ai:cin:sts=2 sw=2 ft=cpp
