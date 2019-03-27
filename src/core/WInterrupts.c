/*
  Copyright (c) 2015 Arduino LLC.  All right reserved.

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

#include <string.h>


static voidFuncPtr callbacksInt[16];


/* Configure I/O interrupt sources */
static void __initialize()
{
	memset(callbacksInt, 0, sizeof(callbacksInt));

	NVIC_DisableIRQ(EIC_IRQn);
	NVIC_ClearPendingIRQ(EIC_IRQn);
	NVIC_SetPriority(EIC_IRQn, 0);
	NVIC_EnableIRQ(EIC_IRQn);

	// Enable GCLK for IEC (External Interrupt Controller)
	GCLK->CLKCTRL.reg = (uint16_t) (GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN_GCLK0 | GCLK_CLKCTRL_ID(GCM_EIC));

	// Enable EIC
	EIC->CTRL.bit.ENABLE = 1;
	while (EIC->STATUS.bit.SYNCBUSY);
}


/*
 * \brief Specifies a named Interrupt Service Routine (ISR) to call when an interrupt occurs.
 *        Replaces any previous function that was attached to the interrupt.
 */
void attachInterrupt(uint32_t pin_number, voidFuncPtr callback, uint32_t mode)
{
	static bool enabled = false;
	
	if (!enabled)
	{
		__initialize();
		enabled = true;
	}
	
	//NMI
	if (pin_number == PIN_PA08) return;

	uint32_t in = pin_number & 15;
	uint32_t cfg = in >> 3;
	uint32_t pos = (in << 2) & 31;

	// Enable wakeup capability on pin in case being used during sleep
	EIC->WAKEUP.reg |= (1 << in);

	// Assign pin to EIC
	pinPeripheral(pin_number, PIO_EXTINT);

	// Assign callback to interrupt
	callbacksInt[in] = callback;
	
	switch (mode)
	{
	case LOW:
		EIC->CONFIG[cfg].reg |= EIC_CONFIG_SENSE0_LOW_Val << pos;
		break;

	case HIGH:
		EIC->CONFIG[cfg].reg |= EIC_CONFIG_SENSE0_HIGH_Val << pos;
		break;

	case CHANGE:
		EIC->CONFIG[cfg].reg |= EIC_CONFIG_SENSE0_BOTH_Val << pos;
		break;

	case FALLING:
		EIC->CONFIG[cfg].reg |= EIC_CONFIG_SENSE0_FALL_Val << pos;
		break;

	case RISING:
		EIC->CONFIG[cfg].reg |= EIC_CONFIG_SENSE0_RISE_Val << pos;
		break;
	}

	// Enable the interrupt
	EIC->INTENSET.reg = EIC_INTENSET_EXTINT(1 << in);
}


/*
 * \brief Turns off the given interrupt.
 */
void detachInterrupt(uint32_t pin_number)
{
	//NMI
	if (pin_number == PIN_PA08) return;
	
	uint32_t in = pin_number & 15;
	uint32_t cfg = in >> 3;
	uint32_t pos = (in << 2) & 31;
	
	// Disable the interrupt
	EIC->INTENCLR.reg = EIC_INTENCLR_EXTINT(1 << in);
	
	//According to Microchip SAMD21 Datasheet 21.8.8 Interrupt Flag Status and Clear,
	//  This flag is set when EXTINTx pin matches the external interrupt sense configuration
	//So we need SENSEx setting to NONE.
	EIC->CONFIG[cfg].reg &= ~(7ul << pos);
	
	// Disable wakeup capability on pin during sleep
	EIC->WAKEUP.reg &= ~(1 << in);
	
	// Clear callback
	callbacksInt[in] = 0;
}



/*
 * External Interrupt Controller NVIC Interrupt Handler
 */
void EIC_Handler(void)
{
	uint32_t mask = 0;
	
	for (uint32_t i = 0; i < sizeof(callbacksInt)/sizeof(voidFuncPtr); i++)
	{
		if (EIC->INTFLAG.reg & mask)
		{
			if (callbacksInt[i]) callbacksInt[i]();
			EIC->INTFLAG.reg = mask;	//clear interrupt
		}
		
		mask <<= 1;
	}
}
