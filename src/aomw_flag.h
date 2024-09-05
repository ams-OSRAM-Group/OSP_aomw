// aomw_flag.h - uses topo to paint flags spread out over an entire OSP string
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
#ifndef _AOMW_FLAG_H_
#define _AOMW_FLAG_H_


#include <aoresult.h>   // aoresult_t


// Painter use topo to draw the flag over the entire chain
aoresult_t aomw_flag_painter_dutch();    // RED WHT BLU // ~France, Luxembourg
aoresult_t aomw_flag_painter_columbia(); // YEL BLU RED // ~ Ecuador, Venezuela
aoresult_t aomw_flag_painter_japan();    // WHT RED WHT
aoresult_t aomw_flag_painter_mali();     // GRN YEL RED // ~ Benin, Cameroon, Ghana, Senegal
aoresult_t aomw_flag_painter_italy();    // GRN WHT RED
aoresult_t aomw_flag_painter_europe();   // BLU YEL BLU YEL BLUE
aoresult_t aomw_flag_painter_usa();      // BLU WHT BLU RED WHT
aoresult_t aomw_flag_painter_china();    // RED YEL RED YEL RED


// Painter are also available via index (must be kept in sync with aomw_flag_painters[])
#define AOMW_FLAG_PIX_DUTCH     0
#define AOMW_FLAG_PIX_COLUMBIA  1
#define AOMW_FLAG_PIX_JAPAN     2
#define AOMW_FLAG_PIX_MALI      3
#define AOMW_FLAG_PIX_ITALY     4
#define AOMW_FLAG_PIX_EUROPE    5
#define AOMW_FLAG_PIX_USA       6
#define AOMW_FLAG_PIX_CHINA     7


typedef aoresult_t (*aocmd_flag_painter_t)( );
int                  aomw_flag_count();
const char *         aomw_flag_name(int pix);
aocmd_flag_painter_t aomw_flag_painter(int pix);


#endif




