﻿/*--------------------------------------------------------------------*-

  system_mode_1769_003-0_c13a.c (Released 2015-02)

  --------------------------------------------------------------------
  
  This module controls the system mode.

  See "ERES(1769)" book, Chapter 7 (details below).

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

// Project header
#include "../main/main.h"

// System (self) tests
#include "../system_tests/system_test_mcu_temperature_1769_003-0_c13a.h"

// Task headers (Bertrik Sikken USB library)
#include "../bertrik_sikken/lpcusb.h"

// Remaining task headers
#include "../tasks/heartbeat_1769_003-0_c02a.h"
#include "../tasks/menu_1769_003-0_c13a.h"
#include "../tasks/spi_7_seg_display_1769_003-0_c13a.h"
#include "../tasks/switch_ea-sw3_1769_003-0_c13a.h"
#include "../tasks/watchdog_1769_003-0_c02a.h"


// ------ Public variable definitions ------------------------------

// In many designs, System_mode_G will be used in other modules.
// - we therefore make this variable public.
eSystem_mode System_mode_G;

// ------ Private function declarations ----------------------------

void SYSTEM_Identify_Required_Mode(void);
void SYSTEM_Configure_Required_Mode(void);

/*--------------------------------------------------------------------*-

  SYSTEM_Init()

  Wrapper for system startup functions.

-*--------------------------------------------------------------------*/
void SYSTEM_Init(void)
   {
   SYSTEM_Identify_Required_Mode();
   SYSTEM_Configure_Required_Mode();
   }

/*--------------------------------------------------------------------*-

  SYSTEM_Identify_Required_Mode()

  Try to work out the cause of the system reset.
  Set the system mode accordingly.

-*--------------------------------------------------------------------*/
void SYSTEM_Identify_Required_Mode(void)
   {
   // If "1", reset was caused by WDT
   uint32_t WDT_flag = (LPC_SC->RSID >> 2) & 1;

   if (WDT_flag == 1)
      {
      // Cleared only by software or POR
      // Clear flag (or other resets may be interpreted as WDT)
      LPC_SC->RSID &= ~(0x04);

      // Set system mode (Fail Silent)
      System_mode_G = FAIL_SILENT;
      }
   else
      {
      // Here we treat all other forms of reset in the same way
      // Set system mode (Normal)
      System_mode_G = NORMAL;
      }
   }

/*--------------------------------------------------------------------*-

  SYSTEM_Configure_Required_Mode()

  Configure the system in the required mode.  

-*--------------------------------------------------------------------*/
void SYSTEM_Configure_Required_Mode(void)
   {
   switch (System_mode_G)
      {
      default:          // Default to "FAIL_SILENT"
      case FAIL_SILENT:
         {
         // Reset caused by WDT
         // Trigger "fail silent" behaviour
         SYSTEM_Perform_Safe_Shutdown();

         break;
         }

      case NORMAL:
         {
         // Set up WDT (timeout in *microseconds*) 
         WATCHDOG_Init(1100);

         // Set up scheduler for 1 ms ticks (tick interval in *ms*)
         SCH_Init(1);

         // Prepare for periodic system temperature check
         SYS_CHECK_MCU_TEMP_Init();

         // Prepare for the tasks
         SWITCH_SW3_Init();
         SPI_7_SEG_DISPLAY_Init();
         USB_SERIAL_Init();
         MENU_Init();
         HEARTBEAT_Init();

         // Add tasks to schedule.
         // Parameters are:
         // 1. Task name
         // 2. Initial delay / offset (in Ticks)
         // 3. Task period (in Ticks): Must be > 0
         // 4. Task WCET (in microseconds)
         // 5. Task BCET (in microseconds)

         // Add watchdog task first
         SCH_Add_Task(WATCHDOG_Update, 0, 1, 10, 0);

         // Main tasks
         SCH_Add_Task(SWITCH_SW3_Update, 5, 10, 20, 0);
         SCH_Add_Task(USB_SERIAL_Update, 0, 1, 50, 0);
         SCH_Add_Task(MENU_Update, 0, 10, 10, 0);
         SCH_Add_Task(SPI_7_SEG_DISPLAY_Update, 10, 1000, 20, 0);

         // Periodic system temperature check
         SCH_Add_Task(SYS_CHECK_MCU_TEMP_Update, 0, 1, 20, 0);

         // Heartbeat task
         SCH_Add_Task(HEARTBEAT_Update, 0, 1000, 20, 0);

         // Feed the watchdog
         WATCHDOG_Update();

         break;
         }
      }
   }

/*--------------------------------------------------------------------*-

  SYSTEM_Perform_Safe_Shutdown()

  Attempt to move the system into a safe state.

  Note: Does not return and may (if watchdog is operational) result
  in a processor reset, after which the function may be called again.

  [The rationale for this behaviour is that - after the reset - 
   the system MAY be in a better position to enter a safe state.
   To avoid the possible reset, adapt the code and feed the WDT
   in the loop.]

-*--------------------------------------------------------------------*/
void SYSTEM_Perform_Safe_Shutdown(void)
   {
   // Used for simple fault reporting.
   uint32_t Delay, j;

   // Here we simply "fail silent" with rudimentary fault reporting.
   // OTHER BEHAVIOUR IS LIKELY TO BE REQUIRED IN YOUR DESIGN

   // *************************************
   // NOTE: This function should NOT return
   // *************************************

   HEARTBEAT_Init();

   while(1)
      {
      // Flicker Heartbeat LED to indicate fault
      for (Delay = 0; Delay < 200000; Delay++) j *= 3;
      HEARTBEAT_Update();
      }
   }

/*--------------------------------------------------------------------*-
  ------ END OF FILE -------------------------------------------------
-*--------------------------------------------------------------------*/
