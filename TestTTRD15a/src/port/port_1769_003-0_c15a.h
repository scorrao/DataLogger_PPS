﻿/*--------------------------------------------------------------------*-
  
   port_1769_003-0_c15a.h (Released 2015-02)

  ------------------------------------------------------------------

   This is the "Port Header" file: 
   it documents usage of port pins in the project.

-*--------------------------------------------------------------------*/
/*--------------------------------------------------------------------*-

  This code is copyright (c) 2014-2015 SafeTTy Systems Ltd.

  This code forms part of a Time-Triggered Reference Design (TTRD)
  that is documented in the following book: 

  Pont, M.J. (2014) 
  "The Engineering of Reliable Embedded Systems: LPC1769 edition", 
  Published by SafeTTy Systems Ltd. ISBN: 978-0-9930355-0-0.

  Both the TTRDs and the above book ("the ERES book") describe 
  patented* technology and are subject to copyright and other 
  restrictions.

  This code may be used without charge: [i] by universities and 
  colleges in courses for which a degree up to and including MSc 
  level (or equivalent) is awarded; [ii] for non-commercial projects 
  carried out by individuals and hobbyists.

  Where this code has been provided to you as part of a training 
  course delivered by SafeTTy Systems Ltd, you may use it for 
  evaluation purposes for a period of up to 12 months from the 
  end date of this course, subject to the condition that no 
  products (of any kind) based either on this code, or on the 
  patented technology described in the ERES book, are released.

  Any and all other use of this code and / or the patented 
  technology described in the ERES book requires purchase of a 
  ReliabiliTTy Technology Licence:
  http://www.safetty.net/products/reliabilitty

  Please contact SafeTTy Systems Ltd if you require clarification
  of these licensing arrangements:
  http://www.safetty.net/contact

  MoniTTor is a registered trademark of SafeTTy Systems Ltd.
  PredicTTor is a registered trademark of SafeTTy Systems Ltd.
  ReliabiliTTy is a registered trademark of SafeTTy Systems Ltd.
  WarranTTor is a registered trademark of SafeTTy Systems Ltd.

  * Patents applied for.

-*--------------------------------------------------------------------*/

#ifndef _PORT_H
#define _PORT_H 1

// Project header
#include "../main/main.h"

// Heartbeat LED
// Connected to "LED2" on LPC1769 board
// Port 0, Pin 22
#define HEARTBEAT_PORT (0)
#define HEARTBEAT_PIN (0b10000000000000000000000)

// Connected to "LED3 (Red)" on EA Baseboard board
// Port 2, Pin 0
#define LED3_RED_PORT (2)
#define LED3_RED_PIN (0b1)

// Connected to "LED3 (Green)" on EA Baseboard board
// Port 2, Pin 1
#define LED3_GREEN_PORT (2)
#define LED3_GREEN_PIN (0b10)

// Connected to "LED3 (Blue)" on EA Baseboard board
// Port 0, Pin 26
#define LED3_BLUE_PORT (0)
#define LED3_BLUE_PIN (0b100000000000000000000000000)

// 7-segment display is controlled with "SPI" link
// Uses SSP1 plus a pin for chip select
#define SSP_CHANNEL LPC_SSP1

#define LED_DISPLAY_PORT_CS (2)
#define LED_DISPLAY_PIN_CS (0b100)

// "Start switch" input
// Connected to "SW3" on LPC1769 Baseboard
// Port 0, Pin 4
#define START_SWITCH_PORT (0)
#define START_SWITCH_PIN (0b10000)

// Connection to MAX6576 on EA Baseboard
// We assume that we are connected to Port 0, Pin 2
// NOTE:
// This only works for me when my board is
// *apparently* set to Pin 1.5 [via J25] ... (MJP)
#define TEMP_SENSOR_PORT (0)
#define TEMP_SENSOR_PIN (0b100)

// WDT jumper
// Add jumper wire on baseboard to control WDT
// WDT is enabled *only* if jumper is in place.
// (Jumper is read at init phase only)
// Port 2, Pin 3
// Labelled PIO2_3 on EA Baseboard
#define WDT_JUMPER_PORT (2)
#define WDT_JUMPER_PIN (0b1000)

// WDT will only be enabled if jumper is inserted
// (connecting the jumper pin to ground)
#define WDT_JUMPER_INSERTED (0)

// Jumper used to clear fault codes
// Add jumper wire on baseboard to control
// clearing of fault codes during a power-on reset
// (Jumper is read at init phase only)
// Port 2, Pin 5
// Labelled PIO2_5 on EA Baseboard
// (next to WDT jumper if default values used)
#define CFC_JUMPER_PORT (2)
#define CFC_JUMPER_PIN (0b100000)

// Fault codes will only be cleared if
// the SR jumper is inserted
// (connecting the jumper pin to ground)
// *AND* a power-on reset is performed
#define CFC_JUMPER_INSERTED (0)

#endif

/*--------------------------------------------------------------------*-
  ------ END OF FILE -------------------------------------------------
-*--------------------------------------------------------------------*/
