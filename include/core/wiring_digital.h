/*
  Copyright (c) 2014 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef _WIRING_DIGITAL_
#define _WIRING_DIGITAL_

#ifdef __cplusplus
 extern "C" {
#endif

#include "WVariant.h"

/**
 * \brief Configures the specified pin to behave either as an input or an output. See the description of digital pins for details.
 *
 * \param ulPin The number of the pin whose mode you wish to set
 * \param ulMode Can be INPUT, OUTPUT, INPUT_PULLUP or INPUT_PULLDOWN
 */
extern void pinMode( uint32_t dwPin, uint32_t dwMode ) ;

/**
 * \brief Write a HIGH or a LOW value to a digital pin.
 *
 * If the pin has been configured as an OUTPUT with pinMode(), its voltage will be set to the
 * corresponding value: 5V (or 3.3V on 3.3V boards) for HIGH, 0V (ground) for LOW.
 *
 * \param dwPin the pin number
 * \param dwVal HIGH or LOW
 */
extern void digitalWrite( uint32_t dwPin, uint32_t dwVal ) ;

/**
 * \brief Reads the value from a specified digital pin, either HIGH or LOW.
 *
 * \param ulPin The number of the digital pin you want to read (int)
 *
 * \return HIGH or LOW
 */
extern int digitalRead( uint32_t ulPin ) ;

/**
 * \brief Change the level of specified digital pin to HIGH.
 *
 * \param pinNum The number of the digital pin you want to change
 */
void pinSet(uint32_t pinNum);

/**
 * \brief Change the level of specified digital pin to LOW.
 *
 * \param pinNum The number of the digital pin you want to change
 */
void pinClr(uint32_t pinNum);

/**
 * \brief Toggle the level of specified digital pin.
 *
 * \param pinNum The number of the digital pin you want to toggle
 */
void pinToggle(uint32_t pinNum);


#ifdef __cplusplus
}


class PinTuple
{
public:
	PinTuple(uint32_t pin_number, uint32_t mux) { value = pin_number | (mux << PIN_NUMBER_WIDTH); }
	
	//convert to Pin Number.
	operator uint32_t() { return value & ((1 << PIN_NUMBER_WIDTH) - 1); }
	
	//get Peripheral Multiplexer
	uint32_t iomux() { return value >> PIN_NUMBER_WIDTH; }
	
private:
	enum { PIN_NUMBER_WIDTH = 8 };
	uint32_t value;
};


#endif

#endif /* _WIRING_DIGITAL_ */
