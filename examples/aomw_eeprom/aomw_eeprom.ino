// aomw_eeprom.ino - demonstrates reading writing eeprom
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
#include <aospi.h>
#include <aoosp.h>
#include <aomw.h>


/*
DESCRIPTION
This demo initializes an OSP chain, powers the I2C bridge in a SAID
and checks whether there is an EEPROM. If so, reads and prints the
entire EEPROM contents, then modifies one row and then restores that.
It finalizes by doing a compare of the current EEPROM content with
the values read at the start.

HARDWARE
The demo runs on the OSP32 board. It has a built-in EEPROM.
In Arduino select board "ESP32S3 Dev Module".

OUTPUT
Welcome to aomw_eeprom.ino
version: result 0.1.10 spi 0.2.8 osp 0.2.3 mw 0.2.2
spi: init
osp: init
mw: init
demo: init

Read original content
00: 00 0E 49 0E 92 0E DB 0E 24 0F 6D 0F B6 0F FF 0F
10: F6 13 ED 13 E4 13 DB 13 D2 13 C9 13 C0 13 FE 25
20: FD 25 FC 25 FB 25 FA 25 F9 25 F8 25 BE 37 7D 37 <<<
30: 3C 37 FB 36 BA 36 79 36 38 36 BF 49 7F 49 3F 49
40: FF 48 BF 48 7F 48 3F 48 B7 5B 6F 5B 27 5B DF 5A
50: 97 5A 4F 5A 07 5A F7 6D EF 6D E7 6D DF 6D D7 6D
60: CF 6D C7 6D B6 01 6D 01 24 01 DB 00 92 00 49 00
70: 00 00 80 13 40 13 00 13 C0 12 80 12 40 12 00 12
80: B0 25 68 25 20 25 D8 24 90 24 48 24 00 24 30 36
90: 28 36 20 36 18 36 10 36 08 36 00 36 36 48 2D 48
a0: 24 48 1B 48 12 48 09 48 00 48 06 5A 05 5A 04 5A
b0: 03 5A 02 5A 01 5A 00 5A 86 6D 45 6D 04 6D C3 6C
c0: 82 6C 41 6C 00 6C B6 7F 6D 7F 24 7F DB 7E 92 7E
d0: 49 7E 00 7E 00 70 C0 A5 00 0E C0 93 00 0E C0 81
e0: 00 70 FF FF FF FF FF FF FF FF FF FF FF FF FF FF
f0: FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF

Overwrite row 20 with 00..0F
00: 00 0E 49 0E 92 0E DB 0E 24 0F 6D 0F B6 0F FF 0F
10: F6 13 ED 13 E4 13 DB 13 D2 13 C9 13 C0 13 FE 25
20: 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F <<<
30: 3C 37 FB 36 BA 36 79 36 38 36 BF 49 7F 49 3F 49
40: FF 48 BF 48 7F 48 3F 48 B7 5B 6F 5B 27 5B DF 5A
50: 97 5A 4F 5A 07 5A F7 6D EF 6D E7 6D DF 6D D7 6D
60: CF 6D C7 6D B6 01 6D 01 24 01 DB 00 92 00 49 00
70: 00 00 80 13 40 13 00 13 C0 12 80 12 40 12 00 12
80: B0 25 68 25 20 25 D8 24 90 24 48 24 00 24 30 36
90: 28 36 20 36 18 36 10 36 08 36 00 36 36 48 2D 48
a0: 24 48 1B 48 12 48 09 48 00 48 06 5A 05 5A 04 5A
b0: 03 5A 02 5A 01 5A 00 5A 86 6D 45 6D 04 6D C3 6C
c0: 82 6C 41 6C 00 6C B6 7F 6D 7F 24 7F DB 7E 92 7E
d0: 49 7E 00 7E 00 70 C0 A5 00 0E C0 93 00 0E C0 81
e0: 00 70 FF FF FF FF FF FF FF FF FF FF FF FF FF FF
f0: FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF

Restore row 20
00: 00 0E 49 0E 92 0E DB 0E 24 0F 6D 0F B6 0F FF 0F
10: F6 13 ED 13 E4 13 DB 13 D2 13 C9 13 C0 13 FE 25
20: FD 25 FC 25 FB 25 FA 25 F9 25 F8 25 BE 37 7D 37 <<<
30: 3C 37 FB 36 BA 36 79 36 38 36 BF 49 7F 49 3F 49
40: FF 48 BF 48 7F 48 3F 48 B7 5B 6F 5B 27 5B DF 5A
50: 97 5A 4F 5A 07 5A F7 6D EF 6D E7 6D DF 6D D7 6D
60: CF 6D C7 6D B6 01 6D 01 24 01 DB 00 92 00 49 00
70: 00 00 80 13 40 13 00 13 C0 12 80 12 40 12 00 12
80: B0 25 68 25 20 25 D8 24 90 24 48 24 00 24 30 36
90: 28 36 20 36 18 36 10 36 08 36 00 36 36 48 2D 48
a0: 24 48 1B 48 12 48 09 48 00 48 06 5A 05 5A 04 5A
b0: 03 5A 02 5A 01 5A 00 5A 86 6D 45 6D 04 6D C3 6C
c0: 82 6C 41 6C 00 6C B6 7F 6D 7F 24 7F DB 7E 92 7E
d0: 49 7E 00 7E 00 70 C0 A5 00 0E C0 93 00 0E C0 81
e0: 00 70 FF FF FF FF FF FF FF FF FF FF FF FF FF FF
f0: FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF
Successfully restored
*/


// The address of the SAID that has the I2C bridge
#define ADDR   0x001 // The OSP32 board has an built-in EEPROM attached to SAID 001
// The I2C address of EEPROM memory
#define DADDR7 AOMW_EEPROM_DADDR7_SAIDBASIC // todo: is AOMW_EEPROM_DADDR7_OSP32 on OSP32


// Lazy way of error handling
#define PRINT_ERROR() do { if( result!=aoresult_ok ) { Serial.printf("ERROR %s\n", aoresult_to_str(result) ); } } while(0)


void demo_init() {
  // (1) initialize the OSP chain
  aoresult_t result;
  result = aoosp_exec_resetinit(); PRINT_ERROR();

  // todo: remove for OSP32
  // (2patch) In case the SAID does not have the I2C_BRIDGE_EN, we could try to override this in RAM
  // result= aoosp_exec_i2cenable_set(ADDR,1); PRINT_ERROR();

  // (2) Check if SAID has I2C bridge
  int enable;
  result= aoosp_exec_i2cenable_get(ADDR, &enable); PRINT_ERROR();
  if( !enable ) result= aoresult_dev_noi2cbridge; PRINT_ERROR();

  // (3) power the I2C bridge in a SAID
  result= aoosp_exec_i2cpower(ADDR); PRINT_ERROR();

  // (4) check wether there is an EEPROM
  result= aomw_eeprom_present(ADDR,DADDR7); PRINT_ERROR();

  Serial.printf("demo: init\n");
}


void demo_dump(int row) {
  uint8_t buf[256];
  aoresult_t result= aomw_eeprom_read(ADDR, DADDR7, 0x00, buf, 256 ); PRINT_ERROR();
  for( int i=0; i<256; i+=16 ) Serial.printf("%02x: %s%s\n", i, aoosp_prt_bytes(&buf[i],16),i==row?" <<<":"");
}


#define ROWIX 0x20
#define ROWSZ 0x10
void demo_readwrite() {
  aoresult_t result;

  Serial.printf("\nRead original content\n");
  uint8_t buf1[ROWSZ];
  result= aomw_eeprom_read(ADDR, DADDR7, ROWIX, buf1, ROWSZ ); PRINT_ERROR();
  // Show original contents
  demo_dump(ROWIX);

  Serial.printf("\nOverwrite row %02x with 00..0F\n",ROWIX);
  uint8_t buf2[ROWSZ] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F};
  result= aomw_eeprom_write(ADDR, DADDR7, ROWIX, buf2, ROWSZ ); PRINT_ERROR();
  demo_dump(ROWIX);

  Serial.printf("\nRestore row %02x\n",ROWIX);
  result= aomw_eeprom_write(ADDR, DADDR7, ROWIX, buf1, ROWSZ ); PRINT_ERROR();
  // Show restored contents
  demo_dump(ROWIX);

  // Compare original with current (prints aoresult_comparefail when not equal)
  result= aomw_eeprom_compare(ADDR, DADDR7, ROWIX, buf1, ROWSZ ); PRINT_ERROR();
  if(result==aoresult_ok) Serial.printf("Successfully restored\n");

}


void setup() {
  Serial.begin(115200);
  Serial.printf("\n\nWelcome to aomw_eeprom.ino\n");
  Serial.printf("version: result %s spi %s osp %s mw %s\n", AORESULT_VERSION, AOSPI_VERSION, AOOSP_VERSION, AOMW_VERSION );

  aospi_init();
  aoosp_init();
  aomw_init();
  demo_init();

  demo_readwrite();
}


void loop() {
  delay(5000);
}

