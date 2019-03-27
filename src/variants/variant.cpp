/*
  Copyright (c) 2014-2015 Arduino LLC.  All right reserved.

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



const EAnalogChannel AdcChannelMapping[] =
{
	//PA00
	No_ADC_Channel,
	No_ADC_Channel,
	ADC_Channel0,
	ADC_Channel1,
	ADC_Channel4,
	ADC_Channel5,
	ADC_Channel6,
	ADC_Channel7,
	
	//PA08
	ADC_Channel16,
	ADC_Channel17,
	ADC_Channel18,
	ADC_Channel19,
	No_ADC_Channel,
	No_ADC_Channel,
	No_ADC_Channel,
	No_ADC_Channel,
	
	//PA16
	No_ADC_Channel,
	No_ADC_Channel,
	No_ADC_Channel,
	No_ADC_Channel,
	No_ADC_Channel,
	No_ADC_Channel,
	No_ADC_Channel,
	No_ADC_Channel,
	
	//PA24
	No_ADC_Channel,
	No_ADC_Channel,
	No_ADC_Channel,
	No_ADC_Channel,
	No_ADC_Channel,
	No_ADC_Channel,
	No_ADC_Channel,
	No_ADC_Channel,
	
	//PB00
	ADC_Channel8,
	ADC_Channel9,
	ADC_Channel10,
	ADC_Channel11,
	ADC_Channel12,
	ADC_Channel13,
	ADC_Channel14,
	ADC_Channel15,
	
	//PB08
	ADC_Channel2,
	ADC_Channel3,
	No_ADC_Channel,
	No_ADC_Channel,
	No_ADC_Channel,
	No_ADC_Channel,
	No_ADC_Channel,
	No_ADC_Channel,
	
	//PB16
	No_ADC_Channel,
	No_ADC_Channel,
	No_ADC_Channel,
	No_ADC_Channel,
	No_ADC_Channel,
	No_ADC_Channel,
	No_ADC_Channel,
	No_ADC_Channel,
	
	//PB24
	No_ADC_Channel,
	No_ADC_Channel,
	No_ADC_Channel,
	No_ADC_Channel,
	No_ADC_Channel,
	No_ADC_Channel,
	No_ADC_Channel,
	No_ADC_Channel,
};



SERCOM sercom0 = SERCOM(SERCOM0, SERCOM0_IRQn, GCM_SERCOM0_CORE);
void SERCOM0_Handler()
{
	sercom0.handleIRQ();
}


SERCOM sercom1 = SERCOM(SERCOM1, SERCOM1_IRQn, GCM_SERCOM1_CORE);
void SERCOM1_Handler()
{
	sercom1.handleIRQ();
}


SERCOM sercom2 = SERCOM(SERCOM2, SERCOM2_IRQn, GCM_SERCOM2_CORE);
void SERCOM2_Handler()
{
	sercom2.handleIRQ();
}


SERCOM sercom3 = SERCOM(SERCOM3, SERCOM3_IRQn, GCM_SERCOM3_CORE);
void SERCOM3_Handler()
{
	sercom3.handleIRQ();
}


SERCOM sercom4 = SERCOM(SERCOM4, SERCOM4_IRQn, GCM_SERCOM4_CORE);
void SERCOM4_Handler()
{
	sercom4.handleIRQ();
}


SERCOM sercom5 = SERCOM(SERCOM5, SERCOM5_IRQn, GCM_SERCOM5_CORE);
void SERCOM5_Handler()
{
	sercom5.handleIRQ();
}
