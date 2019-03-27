/*
 * SPI Master library for Arduino Zero.
 * Copyright (c) 2015 Arduino LLC
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */


#pragma once

#include "Stream.h"
#include "SERCOM.h"
#include "wiring_digital.h"
#include "RingBuffer.h"


class FourWire : public ISercomIRQ
{
public:
	FourWire(): sercom((SERCOM_SPI *)0xE01000000) {}
	
	// �j�wSERCOM����A�Y��LISercomIRQ�����Ӹj�w�F�P��SERCOM����A�N�ݭn�A�I�s����k.
	// �]�wIO�}��h�u�A�YIO�}��Q���@�L�δN�ݭn�A�I�s����k.
	void configIO(SERCOM *, PinTuple MISO, PinTuple SCLK, PinTuple MOSI);
	
	// SPI�����W�v, �줸����, CPHA�PCPOL�]�w, �����}����, SPI�}����.
	void begin(uint32_t, BitOrder, SercomSpiClockMode, SercomRXPad, SercomSpiTXPad);
	
	void end();
	uint8_t transfer(uint8_t data) { return sercom->transferDataSPI(data); }
	uint16_t transfer16(uint16_t data);
	void transfer(void *buf, size_t count);
	
	virtual void IRQHandler();
	
private:
	SERCOM_SPI *sercom;
};


extern FourWire SPI;