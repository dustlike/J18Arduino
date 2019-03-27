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

#pragma once

#include <stdint.h>
#include "sam.h"



/* Definitions and types for pins */
typedef enum _EAnalogChannel
{
  No_ADC_Channel=-1,
  ADC_Channel0=0,
  ADC_Channel1=1,
  ADC_Channel2=2,
  ADC_Channel3=3,
  ADC_Channel4=4,
  ADC_Channel5=5,
  ADC_Channel6=6,
  ADC_Channel7=7,
  ADC_Channel8=8,
  ADC_Channel9=9,
  ADC_Channel10=10,
  ADC_Channel11=11,
  ADC_Channel12=12,
  ADC_Channel13=13,
  ADC_Channel14=14,
  ADC_Channel15=15,
  ADC_Channel16=16,
  ADC_Channel17=17,
  ADC_Channel18=18,
  ADC_Channel19=19,
  DAC_Channel0,
} EAnalogChannel ;

extern const EAnalogChannel AdcChannelMapping[64];



/* Generic Clock Multiplexer IDs */
#define GCM_DFLL48M_REF           (0x00U)
#define GCM_FDPLL96M_INPUT        (0x01U)
#define GCM_FDPLL96M_32K          (0x02U)
#define GCM_WDT                   (0x03U)
#define GCM_RTC                   (0x04U)
#define GCM_EIC                   (0x05U)
#define GCM_USB                   (0x06U)
#define GCM_EVSYS_CHANNEL_0       (0x07U)
#define GCM_EVSYS_CHANNEL_1       (0x08U)
#define GCM_EVSYS_CHANNEL_2       (0x09U)
#define GCM_EVSYS_CHANNEL_3       (0x0AU)
#define GCM_EVSYS_CHANNEL_4       (0x0BU)
#define GCM_EVSYS_CHANNEL_5       (0x0CU)
#define GCM_EVSYS_CHANNEL_6       (0x0DU)
#define GCM_EVSYS_CHANNEL_7       (0x0EU)
#define GCM_EVSYS_CHANNEL_8       (0x0FU)
#define GCM_EVSYS_CHANNEL_9       (0x10U)
#define GCM_EVSYS_CHANNEL_10      (0x11U)
#define GCM_EVSYS_CHANNEL_11      (0x12U)
#define GCM_SERCOMx_SLOW          (0x13U)
#define GCM_SERCOM0_CORE          (0x14U)
#define GCM_SERCOM1_CORE          (0x15U)
#define GCM_SERCOM2_CORE          (0x16U)
#define GCM_SERCOM3_CORE          (0x17U)
#define GCM_SERCOM4_CORE          (0x18U)
#define GCM_SERCOM5_CORE          (0x19U)
#define GCM_TCC0_TCC1             (0x1AU)
#define GCM_TCC2_TC3              (0x1BU)
#define GCM_TC4_TC5               (0x1CU)
#define GCM_TC6_TC7               (0x1DU)
#define GCM_ADC                   (0x1EU)
#define GCM_AC_DIG                (0x1FU)
#define GCM_AC_ANA                (0x20U)
#define GCM_DAC                   (0x21U)
#define GCM_PTC                   (0x22U)
#define GCM_I2S_0                 (0x23U)
#define GCM_I2S_1                 (0x24U)
