// aomw_flag.cpp - uses topo to paint flags spread out over an entire OSP string
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
#include <Arduino.h>    // uint16_t
#include <aomw_topo.h>  // aomw_topo_settriplet
#include <aomw_flag.h>  // own


// Paints a flag with three bands, using topo
static aoresult_t aomw_flag_3bands(const aomw_topo_rgb_t*band1,const aomw_topo_rgb_t*band2,const aomw_topo_rgb_t*band3) {
  // determine number of triplets we have
  int numtot  = aomw_topo_numtriplets(); // total number of triplets in chain
  int nummcu1 = aomw_topo_node_numtriplets(1); // number of triplets on MCU board at the start of the chain
  int nummcu3 = aomw_topo_loop()? aomw_topo_node_numtriplets(aomw_topo_numnodes()) : 0; // number of triplets on MCU board at the end of the chain
  int numpcb  = numtot-nummcu1-nummcu3; // number of triplets on the pcb(s), ie not on the MCU board
  int numflag = numpcb>=3 ? numpcb : numtot; // if there is enough triplets on the pcb, use only pcb for flag else use all triplets in chain

  // divide triplets over 3 bands
  int div = numflag / 3; // number of triplets for each band
  int mod = numflag % 3; // triplets left over

  // If one triplet is left over, put it in the middle band; if two are left over put it on both side bands
  int num1 = div + (mod==2?1:0); // number of colors for left side band
  int num2 = div + (mod==1?1:0); // number of colors for middle band
  int num3 = div + (mod==2?1:0); // number of colors for right side band

  // if we ignored the triplets on the MCU, add them again
  if( numpcb>=3 ) { num1+=nummcu1; num3+=nummcu3; }

  // generate all three bands
  aoresult_t result;
  uint16_t tix=0;
  for( int i=0; i<num1; i++,tix++ ) {
    result= aomw_topo_settriplet(tix, band1 );
    if( result!=aoresult_ok ) return result;
  }
  for( int i=0; i<num2; i++,tix++ ) {
    result= aomw_topo_settriplet(tix, band2 );
    if( result!=aoresult_ok ) return result;
  }
  for( int i=0; i<num3; i++,tix++ ) {
    result= aomw_topo_settriplet(tix, band3 );
    if( result!=aoresult_ok ) return result;
  }

  return aoresult_ok;
}


/*!
    @brief  Paints a red-white-blue flag on the OSP chain (using topo).
    @return aoresult_ok           If painting was successful
            other error code      if there is a (communications) error
    @note   The OSP chain must be initialized (eg with aomw_topo_build()).
    @note   The Netherlands, France, and Luxembourg uses these colors.
*/
aoresult_t aomw_flag_painter_dutch() {
  return aomw_flag_3bands( &aomw_topo_red, &aomw_topo_white, &aomw_topo_blue );
}


/*!
    @brief  Paints a yellow-blue-red flag on the OSP chain (using topo).
    @return aoresult_ok           If painting was successful
            other error code      if there is a (communications) error
    @note   The OSP chain must be initialized (eg with aomw_topo_build()).
    @note   Columbia, Ecuador, and Venezuela uses these colors.
*/
aoresult_t aomw_flag_painter_columbia() {
  return aomw_flag_3bands( &aomw_topo_yellow, &aomw_topo_blue, &aomw_topo_red );
}


/*!
    @brief  Paints a white-red-white flag on the OSP chain (using topo).
    @return aoresult_ok           If painting was successful
            other error code      if there is a (communications) error
    @note   The OSP chain must be initialized (eg with aomw_topo_build()).
    @note   Abstraction of the flag from Japan.
*/
aoresult_t aomw_flag_painter_japan() {
  return aomw_flag_3bands( &aomw_topo_white, &aomw_topo_red, &aomw_topo_white );
}


/*!
    @brief  Paints a green-yellow-red flag on the OSP chain (using topo).
    @return aoresult_ok           If painting was successful
            other error code      if there is a (communications) error
    @note   The OSP chain must be initialized (eg with aomw_topo_build()).
    @note   Mali, Benin, Cameroon, Ghana, and Senegal uses the colors.
*/
aoresult_t aomw_flag_painter_mali() {
  return aomw_flag_3bands( &aomw_topo_green, &aomw_topo_yellow, &aomw_topo_red );
}


/*!
    @brief  Paints a green-white-red flag on the OSP chain (using topo).
    @return aoresult_ok           If painting was successful
            other error code      if there is a (communications) error
    @note   The OSP chain must be initialized (eg with aomw_topo_build()).
    @note   Italy uses the colors.
*/
aoresult_t aomw_flag_painter_italy() {
  return aomw_flag_3bands( &aomw_topo_green, &aomw_topo_white, &aomw_topo_red );
}


/*!
    @brief  Paints a blue-yellow1-blue-yellow1-blue flag on the OSP
            chain (using topo).
    @return aoresult_ok           If painting was successful
            other error code      if there is a (communications) error
    @note   The OSP chain must be initialized (eg with aomw_topo_build()).
    @note   Abstraction of the flag from European Union.
*/
aoresult_t aomw_flag_painter_europe() {
  int numtot  = aomw_topo_numtriplets(); // total number of triplets in chain
  int numstart= aomw_topo_node_numtriplets(1); // number of triplets on the start of the chain that must be blue
  int numend  = aomw_topo_loop()? aomw_topo_node_numtriplets(aomw_topo_numnodes()) : 0; // number of triplets on the end of the chain that must be blue
  int numpcb  = numtot-numstart-numend; // number of triplets on the PCB
  int numstars= numpcb<5 ? 0 : 2 ; //number of yellow stars
  int numblue = numpcb-numstars; // number of triplets on the pcb(s) that we want to be blue

  // there are three blue bands
  int div = numblue / 3; // number of triplets for each band
  int mod = numblue % 3; // triplets left over

  // If one triplet is left over, put it in the middle band; if two are left over put it on both side bands
  int num1 = div + (mod==2?1:0); // number of blues before first star
  int num2 = numstars/2; // yellow star
  int num3 = div + (mod==1?1:0); // number of blues between the two stars
  int num4 = numstars/2; // yellow star
  int num5 = div + (mod==2?1:0); // number of blues after the star

  num1+= numstart;
  num5+= numend;

  // generate three blue bands with two yellow stars
  aoresult_t result;
  uint16_t tix=0;
  for( int i=0; i<num1; i++,tix++ ) {
    result= aomw_topo_settriplet(tix, &aomw_topo_blue );
    if( result!=aoresult_ok ) return result;
  }
  for( int i=0; i<num2; i++,tix++ ) {
    result= aomw_topo_settriplet(tix, &aomw_topo_yellow );
    if( result!=aoresult_ok ) return result;
  }
  for( int i=0; i<num3; i++,tix++ ) {
    result= aomw_topo_settriplet(tix, &aomw_topo_blue );
    if( result!=aoresult_ok ) return result;
  }
  for( int i=0; i<num4; i++,tix++ ) {
    result= aomw_topo_settriplet(tix, &aomw_topo_yellow );
    if( result!=aoresult_ok ) return result;
  }
  for( int i=0; i<num5; i++,tix++ ) {
    result= aomw_topo_settriplet(tix, &aomw_topo_blue );
    if( result!=aoresult_ok ) return result;
  }

  return aoresult_ok;
}


/*!
    @brief  Paints a blue1-(white1-blue1)*-red-(white-red)* flag on the OSP
            chain (using topo).
    @return aoresult_ok           If painting was successful
            other error code      if there is a (communications) error
    @note   The OSP chain must be initialized (eg with aomw_topo_build()).
    @note   Abstraction of the flag from the USA.
*/
aoresult_t aomw_flag_painter_usa() {
  // determine number of triplets we have
  int numtot    = aomw_topo_numtriplets(); // total number of triplets in chain
  int nummain   = numtot-2-aomw_topo_node_numtriplets(1); // we have 1 blue to start then several white-blue and then several red-white pairs, and finally one red. The outer two are removed here.
  int numpairs  = nummain/2;
  int numcorner = numpairs/3; // the blue-white part

  aoresult_t result;
  uint16_t tixnum=aomw_topo_numtriplets();
  uint16_t tix=0;
  // First blue
  int mcu=0;
  while( mcu<aomw_topo_node_numtriplets(1)+1 && tix<tixnum ) {
    result= aomw_topo_settriplet(tix, &aomw_topo_blue );
    if( result!=aoresult_ok ) return result;
    tix++;
    mcu++;
  }
  // white/blue pairs
  int pairs=0;
  while( pairs<numcorner && tix<tixnum ) {
    result= aomw_topo_settriplet(tix, &aomw_topo_white );
    if( result!=aoresult_ok ) return result;
    tix++;
    if( tix<tixnum ) {
      result= aomw_topo_settriplet(tix, &aomw_topo_blue );
      if( result!=aoresult_ok ) return result;
      tix++;
    }
    pairs++;
  }
  // first red
  if( tix<tixnum ) {
    result= aomw_topo_settriplet(tix, &aomw_topo_red );
    if( result!=aoresult_ok ) return result;
    tix++;
  }
  // white/red pairs
  while( tix<tixnum ) {
    result= aomw_topo_settriplet(tix, &aomw_topo_white );
    if( result!=aoresult_ok ) return result;
    tix++;
    if( tix<tixnum ) {
      result= aomw_topo_settriplet(tix, &aomw_topo_red );
      if( result!=aoresult_ok ) return result;
      tix++;
    }
  }
  return aoresult_ok;
}


/*!
    @brief  Paints a red-yellow2-red-yellow1-red flag on the OSP
            chain (using topo).
    @return aoresult_ok           If painting was successful
            other error code      if there is a (communications) error
    @note   The OSP chain must be initialized (eg with aomw_topo_build()).
    @note   Abstraction of the flag from China.
*/
aoresult_t aomw_flag_painter_china() {
  int numtot  = aomw_topo_numtriplets(); // total number of triplets in chain
  int numstart= aomw_topo_node_numtriplets(1); // number of triplets on the start of the chain that must be red
  int numend  = aomw_topo_loop()? aomw_topo_node_numtriplets(aomw_topo_numnodes()) : 0; // number of triplets on the end of the chain that must be red
  int numpcb  = numtot-numstart-numend; // number of triplets on the PCB
  int numstars= numpcb<7 ? 0 : 3 ; //number of yellow stars
  int numred  = numpcb-numstars; // number of triplets on the pcb(s) that we want to be red

  // If one triplet is left over, put it in the middle band; if two are left over put it on both side bands
  int num1 = numred>1 ? 1 : 0; // number of reds before first star
  int num2 = (numstars+1)/2; // yellow star
  int num3 = numred>2 ? 1 : 0; // number of reds between the two stars
  int num4 = numstars/2; // yellow star
  int num5 = numred-num1-num3; // number of reds after the star

  num1+= numstart;
  num5+= numend;

  // generate three red bands with two yellow stars
  aoresult_t result;
  uint16_t tix=0;
  for( int i=0; i<num1; i++,tix++ ) {
    result= aomw_topo_settriplet(tix, &aomw_topo_red );
    if( result!=aoresult_ok ) return result;
  }
  for( int i=0; i<num2; i++,tix++ ) {
    result= aomw_topo_settriplet(tix, &aomw_topo_yellow );
    if( result!=aoresult_ok ) return result;
  }
  for( int i=0; i<num3; i++,tix++ ) {
    result= aomw_topo_settriplet(tix, &aomw_topo_red );
    if( result!=aoresult_ok ) return result;
  }
  for( int i=0; i<num4; i++,tix++ ) {
    result= aomw_topo_settriplet(tix, &aomw_topo_yellow );
    if( result!=aoresult_ok ) return result;
  }
  for( int i=0; i<num5; i++,tix++ ) {
    result= aomw_topo_settriplet(tix, &aomw_topo_red );
    if( result!=aoresult_ok ) return result;
  }

  return aoresult_ok;
}


// === Access by index/name ==================================================
// Painters can be called with the above functions, but they are also
// available via index (aomw_flag_pix_xxx) or via name (aomw_flag_name())


// Coupling a name to a painter
typedef struct aomw_flag_painter_s {
  const char *         name;
  aocmd_flag_painter_t painter;
} aomw_flag_painter_t;


// Database of painters - must be kept in sync with AOMW_FLAG_PIX_XXX
static aomw_flag_painter_t aomw_flag_painters[] = {
  { "dutch",     aomw_flag_painter_dutch    },
  { "columbia",  aomw_flag_painter_columbia },
  { "japan",     aomw_flag_painter_japan    },
  { "mali",      aomw_flag_painter_mali     },
  { "italy",     aomw_flag_painter_italy    },
  { "europe",    aomw_flag_painter_europe   },
  { "usa",       aomw_flag_painter_usa      },
  { "china",     aomw_flag_painter_china    },
};


// Number of painters
#define AOMW_FLAG_PAINTERS_COUNT ( sizeof(aomw_flag_painters)/sizeof(aomw_flag_painters[0]) )


/*!
    @brief  Returns the number of flag (painters).
    @return Number of flag (painters).
    @note   Used for indexing in aomw_flag_name() and aomw_flag_painter().
*/
int aomw_flag_count() {
  return AOMW_FLAG_PAINTERS_COUNT;
}


/*!
    @brief  Returns the name of flag `pix`.
    @param  pix
            The painter index [0..aomw_flag_count)
    @return Name (eg 'dutch'). 
*/
const char * aomw_flag_name(int pix) {
  AORESULT_ASSERT( 0<=pix && pix<AOMW_FLAG_PAINTERS_COUNT );
  return aomw_flag_painters[pix].name;
}


/*!
    @brief  Returns the painter of flag `pix`.
    @param  pix
            The painter index [0..aomw_flag_count)
    @return Painter (eg aomw_flag_painter_dutch()). 
*/
aocmd_flag_painter_t aomw_flag_painter(int pix) {
  AORESULT_ASSERT( 0<=pix && pix<AOMW_FLAG_PAINTERS_COUNT );
  return aomw_flag_painters[pix].painter;
}

