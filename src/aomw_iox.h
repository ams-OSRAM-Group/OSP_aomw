// aomw_iox.h - driver for NXP PCA6408ABSHP IO expander connected to a SAID, assuming 4 LEDs and 4 buttons are connected
/*****************************************************************************
 * Copyright 2024 by ams OSRAM AG                                            *
 * All rights are reserved.                                                  *
 *                                                                           *
 * IMPORTANT - PLEASE READ CAREFULLY BEFORE COPYING, INSTALLING OR USING     *
 * THE SOFTWARE.                                                             *
 *                                                                           *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS       *
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT         *
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS         *
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT  *
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,     *
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT          *
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,     *
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY     *
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT       *
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE     *
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.      *
 *****************************************************************************/
#ifndef _AOMW_IOX_H_
#define _AOMW_IOX_H_


#include <stdint.h>     // uint8_t
#include <aoresult.h>   // aoresult_t


// === Signaling LED ========================================================


// Masks for aomw_iox_led_on/off/set to tell which LED to switch (can be or'ed)
#define AOMW_IOX_LED0    0x02
#define AOMW_IOX_LED1    0x08
#define AOMW_IOX_LED2    0x20
#define AOMW_IOX_LED3    0x80
#define AOMW_IOX_LED(n)  (1<<((n)*2+1)) // n=0..3
#define AOMW_IOX_LEDALL  (AOMW_IOX_LED0|AOMW_IOX_LED1|AOMW_IOX_LED2|AOMW_IOX_LED3)
#define AOMW_IOX_LEDNONE 0x00


// Turns on the signaling LEDs that have a bit set in `led`.
aoresult_t aomw_iox_led_on( uint8_t leds );
// Turns off the signaling LEDs that have a bit set in `led`.
aoresult_t aomw_iox_led_off( uint8_t leds );
// The bits set in `leds` indicate which signaling LEDs to turn on, the clear bits, which to turn off.
aoresult_t aomw_iox_led_set( uint8_t leds );


// === Button ===============================================================


// Masks for aomw_iox_but_wentdown to tell which buttons where pressed (can be or'ed)
#define AOMW_IOX_BUT0   0x01
#define AOMW_IOX_BUT1   0x04
#define AOMW_IOX_BUT2   0x10
#define AOMW_IOX_BUT3   0x40
#define AOMW_IOX_BUTALL (AOMW_IOX_BUT0|AOMW_IOX_BUT1|AOMW_IOX_BUT2|AOMW_IOX_BUT3)


// This function scans all buttons for their state (up, down) and records that in a global variable. It also maintains the previous state. Use functions aomw_iox_but_isup()/down(), and/or aomw_iox_but_wentup()/wentdown() to determine which buttons are respectively went up/down.
aoresult_t aomw_iox_but_scan( );
// Returns which of the buttons in `buts` were down (depressed) during the last aomw_iox_but_scan() call, but where up (released) during the call to aomw_iox_but_scan() before that; the button "went down".
uint8_t aomw_iox_but_wentdown( uint8_t buts );
// Returns which of the buttons in `buts` was down (depressed) during the last aomw_iox_but_scan() call.
uint8_t aomw_iox_but_isdown( uint8_t buts );
// Returns which of the buttons in `buts` were up (released) during the last aomw_iox_but_scan() call, but where down (depressed) during the call to aomw_iox_but_scan() before that; the button "went up".
uint8_t aomw_iox_but_wentup( uint8_t buts );
// Returns which of the buttons in `buts` was up (released) during the last aomw_iox_but_scan() call.
uint8_t aomw_iox_but_isup( uint8_t buts );


// === main =================================================================


// I2C address of the IO Expander
#define AOMW_IOX_DADDR7         0x20


// Tests if an IO expander (IOX) is connected to the I2C bus of OSP node (SAID) with address `addr`.
aoresult_t aomw_iox_present(uint16_t addr );
// Associates this software driver to the IO expander (IOX) connected to the I2C bus of OSP node (SAID) with address `addr`.
aoresult_t aomw_iox_init(uint16_t addr);


#endif




