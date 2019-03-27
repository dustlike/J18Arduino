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



void pinMode( uint32_t ulPin, uint32_t ulMode )
{
	uint32_t grp = ulPin >> 5;
	
	if (grp >= PORT_GROUPS) return;
	
	uint32_t pin = ulPin & 0x1F;
	
	if (ulMode >= 0x10)
	{
		//workaround for Errata 12368
		if (ulPin == PIN_PA24 || ulPin == PIN_PA25)
		{
			//PULL won't be disabled automatically when PA24 and PA25 is configured as alternative function
			PORT->Group[0].PINCFG[pin].bit.INEN = 0;
		}
		
		if (ulPin & 1)	//pin is odd number
		{
			PORT->Group[grp].PMUX[pin >> 1].bit.PMUXO = ulMode & 15;
		}
		else
		{
			PORT->Group[grp].PMUX[pin >> 1].bit.PMUXE = ulMode & 15;
		}
		
		PORT->Group[grp].PINCFG[pin].bit.PMUXEN = 1;
	}
	else
	{
		uint32_t mask = 1 << pin;
		
		switch(ulMode)
		{
			case OUTPUT:
			PORT->Group[grp].PINCFG[pin].reg = 0;
			PORT->Group[grp].DIRSET.reg = mask;
			break;
			
			case INPUT:
			PORT->Group[grp].PINCFG[pin].reg = PORT_PINCFG_INEN;
			PORT->Group[grp].DIRCLR.reg = mask;
			break;
			
			case INPUT_PULLUP:
			PORT->Group[grp].PINCFG[pin].reg = PORT_PINCFG_INEN | PORT_PINCFG_PULLEN;
			PORT->Group[grp].DIRCLR.reg = mask;
			PORT->Group[grp].OUTSET.reg = mask;
			break;
			
			case INPUT_PULLDOWN:
			PORT->Group[grp].PINCFG[pin].reg = PORT_PINCFG_INEN | PORT_PINCFG_PULLEN;
			PORT->Group[grp].DIRCLR.reg = mask;
			PORT->Group[grp].OUTCLR.reg = mask;
			break;
			
			case DISABLE:
			PORT->Group[grp].PINCFG[pin].reg = 0;
			PORT->Group[grp].DIRCLR.reg = mask;
			break;
			
			case DISABLE_PULLUP:
			PORT->Group[grp].PINCFG[pin].reg = PORT_PINCFG_PULLEN;
			PORT->Group[grp].DIRCLR.reg = mask;
			PORT->Group[grp].OUTSET.reg = mask;
			break;
			
			case DISABLE_PULLDN:
			PORT->Group[grp].PINCFG[pin].reg = PORT_PINCFG_PULLEN;
			PORT->Group[grp].DIRCLR.reg = mask;
			PORT->Group[grp].OUTCLR.reg = mask;
			break;
		}
	}
}



void digitalWrite( uint32_t ulPin, uint32_t ulVal )
{
	uint32_t grp = ulPin >> 5;
	
	if (grp >= PORT_GROUPS) return;
	
	uint32_t pin = ulPin & 0x1F;
	
	if (ulVal == LOW)
	{
		PORT->Group[grp].OUTCLR.reg = 1 << pin;
	}
	else
	{
		PORT->Group[grp].OUTSET.reg = 1 << pin;
	}
}



int digitalRead( uint32_t ulPin )
{
	uint32_t grp = ulPin >> 5;
	
	if (grp >= PORT_GROUPS) return LOW;
	
	uint32_t pin = ulPin & 0x1F;
	
	return PORT->Group[grp].IN.reg & (1 << pin)? HIGH : LOW;
}



void pinSet(uint32_t pinNum)
{
	uint32_t grp = pinNum >> 5;
	
	if (grp >= PORT_GROUPS) return;
	
	uint32_t pin = pinNum & 0x1F;
	
	PORT->Group[grp].OUTSET.reg = 1 << pin;
}



void pinClr(uint32_t pinNum)
{
	uint32_t grp = pinNum >> 5;
	
	if (grp >= PORT_GROUPS) return;
	
	uint32_t pin = pinNum & 0x1F;
	
	PORT->Group[grp].OUTCLR.reg = 1 << pin;
}



void pinToggle(uint32_t pinNum)
{
	uint32_t grp = pinNum >> 5;
	
	if (grp >= PORT_GROUPS) return;
	
	uint32_t pin = pinNum & 0x1F;
	
	PORT->Group[grp].OUTTGL.reg = 1 << pin;
}
