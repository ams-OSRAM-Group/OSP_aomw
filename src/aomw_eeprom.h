// aomw_eeprom.h - driver for an I2C EEPROM (AT24C02C) connected to a SAID
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
#ifndef _AOMW_EEPROM_H_
#define _AOMW_EEPROM_H_


#include <stdint.h>     // uint8_t, uint16_t
#include <aoresult.h>   // aoresult_t


// I2C address of the EEPROM on the OSP32 board
#define AOMW_EEPROM_DADDR7_OSP32      0x54
// I2C address of the EEPROM on the SAIDbasic board
#define AOMW_EEPROM_DADDR7_SAIDBASIC  0x50
// I2C address of the EEPROM on the I2C EEPROM stick
#define AOMW_EEPROM_DADDR7_STICK      0x51


// Checks if an EEPROM with the 7-bit device address `daddr7` is connected to (the I2C bridge of) OSP node with address `addr`.
aoresult_t aomw_eeprom_present(uint16_t addr, uint8_t daddr7 );
// Reads `count` bytes into buffer `buf` from an EEPROM with the 7-bit I2C device address `daddr7` connected to (the I2C bridge of) the OSP node with address `addr`. The EEPROM will be read from (register) address `raddr` and further.
aoresult_t aomw_eeprom_read   (uint16_t addr, uint8_t daddr7, uint8_t raddr,       uint8_t *buf, int count );
// Writes `count` bytes from buffer `buf` to an EEPROM with the 7-bit I2C device address `daddr7` connected to (the I2C bridge of) the OSP node with address `addr`. The EEPROM will be written at (register) address `raddr` and further.
aoresult_t aomw_eeprom_write  (uint16_t addr, uint8_t daddr7, uint8_t raddr, const uint8_t *buf, int count );
// Reads `count` bytes from an EEPROM with the 7-bit I2C device address `daddr7` connected to (the I2C bridge of) the OSP node with address `addr` and compares them to `buf`. The EEPROM will be read from (register) address `raddr` and further.
aoresult_t aomw_eeprom_compare(uint16_t addr, uint8_t daddr7, uint8_t raddr, const uint8_t *buf, int count );


#endif




