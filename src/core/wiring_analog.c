/*
  Copyright (c) 2014 Arduino LLC.  All right reserved.

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

#include "Arduino.h"
#include "wiring_private.h"



static int _readResolution = 10;
static int _ADCResolution = 10;
static int _writeResolution = 8;

// Wait for synchronization of registers between the clock domains
static __inline__ void syncADC() __attribute__((always_inline, unused));
static void syncADC() {
  while (ADC->STATUS.bit.SYNCBUSY == 1)
    ;
}

// Wait for synchronization of registers between the clock domains
static __inline__ void syncDAC() __attribute__((always_inline, unused));
static void syncDAC() {
  while (DAC->STATUS.bit.SYNCBUSY == 1)
    ;
}

// Wait for synchronization of registers between the clock domains
static __inline__ void syncTC_16(Tc* TCx) __attribute__((always_inline, unused));
static void syncTC_16(Tc* TCx) {
  while (TCx->COUNT16.STATUS.bit.SYNCBUSY);
}

// Wait for synchronization of registers between the clock domains
static __inline__ void syncTCC(Tcc* TCCx) __attribute__((always_inline, unused));
static void syncTCC(Tcc* TCCx) {
  while (TCCx->SYNCBUSY.reg & TCC_SYNCBUSY_MASK);
}



void analogReadResolution(int res)
{
	_readResolution = res;
	
	if (res > 10)
	{
		ADC->CTRLB.bit.RESSEL = ADC_CTRLB_RESSEL_12BIT_Val;
		_ADCResolution = 12;
	}
	else if (res > 8)
	{
		ADC->CTRLB.bit.RESSEL = ADC_CTRLB_RESSEL_10BIT_Val;
		_ADCResolution = 10;
	}
	else
	{
		ADC->CTRLB.bit.RESSEL = ADC_CTRLB_RESSEL_8BIT_Val;
		_ADCResolution = 8;
	}
	
	syncADC();
}



void analogWriteResolution(int res)
{
	_writeResolution = res;
}



static inline uint32_t mapResolution(uint32_t value, uint32_t from, uint32_t to)
{
	if (from == to) return value;
	if (from >= to) return value >> (from - to);
	return value << (to - from);
}



/*
 * Internal Reference is at 1.0v
 * External Reference should be between 1v and VDDANA-0.6v=2.7v
 *
 * Warning : On Arduino Zero board the input/output voltage for SAMD21G18 is 3.3 volts maximum
 */
void analogReference(eAnalogReference mode)
{
	syncADC();
	switch (mode)
	{
		case AR_INTERNAL:
		case AR_INTERNAL2V23:
		ADC->INPUTCTRL.bit.GAIN = ADC_INPUTCTRL_GAIN_1X_Val;      // Gain Factor Selection
		ADC->REFCTRL.bit.REFSEL = ADC_REFCTRL_REFSEL_INTVCC0_Val; // 1/1.48 VDDANA = 1/1.48* 3V3 = 2.2297
		break;

		case AR_EXTERNAL:
		ADC->INPUTCTRL.bit.GAIN = ADC_INPUTCTRL_GAIN_1X_Val;      // Gain Factor Selection
		ADC->REFCTRL.bit.REFSEL = ADC_REFCTRL_REFSEL_AREFA_Val;
		break;

		case AR_INTERNAL1V0:
		ADC->INPUTCTRL.bit.GAIN = ADC_INPUTCTRL_GAIN_1X_Val;      // Gain Factor Selection
		ADC->REFCTRL.bit.REFSEL = ADC_REFCTRL_REFSEL_INT1V_Val;   // 1.0V voltage reference
		break;

		case AR_INTERNAL1V65:
		ADC->INPUTCTRL.bit.GAIN = ADC_INPUTCTRL_GAIN_1X_Val;      // Gain Factor Selection
		ADC->REFCTRL.bit.REFSEL = ADC_REFCTRL_REFSEL_INTVCC1_Val; // 1/2 VDDANA = 0.5* 3V3 = 1.65V
		break;

		case AR_DEFAULT:
		default:
		ADC->INPUTCTRL.bit.GAIN = ADC_INPUTCTRL_GAIN_DIV2_Val;
		ADC->REFCTRL.bit.REFSEL = ADC_REFCTRL_REFSEL_INTVCC1_Val; // 1/2 VDDANA = 0.5* 3V3 = 1.65V
		break;
	}
}



uint32_t analogRead(uint32_t pin_number)
{
	if (pin_number >= sizeof(AdcChannelMapping) / sizeof(AdcChannelMapping[0])) return 65535;
	
	auto channel = AdcChannelMapping[pin_number];
	if (channel == No_ADC_Channel) return 65535;
	
	if (pin_number == PIN_DAC)		// Disable DAC, if analogWrite(PIN_DAC) used previously the DAC is enabled
	{
		syncDAC();
		DAC->CTRLA.bit.ENABLE = 0;	// Disable DAC
	}
	
	
	pinMode(pin_number, PIO_ANALOG);
	
	//select ADC channel
	syncADC();
	ADC->INPUTCTRL.bit.MUXPOS = (uint32_t)channel;
	
	//enable ADC
	syncADC();
	ADC->CTRLA.bit.ENABLE = 1;
	
	//start conversion
	while (ADC->STATUS.bit.SYNCBUSY);
	ADC->INTFLAG.reg = ADC_INTFLAG_RESRDY;	//ensure the ready flag is clear
	ADC->SWTRIG.reg = ADC_SWTRIG_START;
	
	//wait conversion...
	while (!ADC->INTFLAG.bit.RESRDY);
	
	uint16_t valueRead = ADC->RESULT.reg;
	
	//disable ADC
	ADC->CTRLA.bit.ENABLE = 0;
	syncADC();
	
	return mapResolution(valueRead, _ADCResolution, _readResolution);
}



// TODO: support PWM
void analogWrite(uint32_t pin, uint32_t value)
{
	if (pin != PIN_DAC) return;
	
	value = mapResolution(value, _writeResolution, 10);
	
	syncDAC();
	DAC->DATA.reg = value & 0x3FF;	// DAC on 10 bits.
	syncDAC();
	DAC->CTRLA.bit.ENABLE = 1;	// Enable DAC
	syncDAC();
	
	pinMode(pin, PIO_ANALOG);
}
