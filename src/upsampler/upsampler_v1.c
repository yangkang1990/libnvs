
#include <stddef.h>

#include "upsampler_v1.h"
#include "fir_def.h"

#ifdef POLY_PHASE_UPSAMPLER
#include "P2_UP_2_Eq2_60dB.h"
#include "P2_UP_2_LA_N_17.h"
#else
#include "UP_2_Eq1_60dB.h"
#include "UP_2_LA_N_9.h"
#endif

#define GAIN_Q3_13                  ((q15_t)(2.0f * 8192)) // fixpoint_val*2^13 format [F3.13] - [-4.000..+3.999]
#define MAX_Q15                     ((q31_t) 0x00007FFF)
#define MIN_Q15                     ((q31_t) 0xFFFF8000)

#ifdef POLY_PHASE_UPSAMPLER
#define DELAY_TAPS_N      (P2FIR_UP_SAMPLER_COEFF_N-1)/2 - (P2FIR_UP_INTERPOLATOR_COEFF_N-1)/2
#else
#define DELAY_TAPS_N      (FIR_UP_SAMPLER_TAPS_N-1)/2 - (FIR_UP_INTERPOLATOR_TAPS_N-1)/2
#endif

static q15_t xdelay[DELAY_TAPS_N] = { 0 };

static delay_q15_t  delay =
{
    .numTaps = DELAY_TAPS_N,
    .index = 0,
    .pState = xdelay
};

 
static q31_t SSAT(q31_t x, q31_t max_y, q31_t min_y)
{

    if(x > max_y)
    {
      x = max_y;
    }
    else if(x < min_y)
    {
      x = min_y;
    }
    
    return (x);
}
 
static q15_t q15_sat_q24(q31_t x)
{
    return (q15_t)(SSAT(x, 0x00FFFFFF, 0xFF000000) >> 9); // [8.24] (- SAT +0.99999/-1.0 ) -> [1.15]
}  

void vector_gain_q15(q15_t *p_samples_q15, int buffer_size)
{
    int i;
    q15_t gain = GAIN_Q3_13; // [F3.13]

    for (i=0; i<buffer_size; i++)
    {
      // result is [F1.15] i.e. ([F3.15] = [F1.15]x[F3.13]) saturated to [F1.15])
      *p_samples_q15 = (q15_t) SSAT((((q31_t) (*p_samples_q15) * (gain)) >> 13), MAX_Q15, MIN_Q15);
      p_samples_q15++;
    }
}

static void delay_q15_init(delay_q15_t *pDelay)
{
    uint32_t i;

    for (i = 0; i < pDelay->numTaps; i++)
    {
        pDelay->pState[i] = 0;
    }
    pDelay->index = 0;
}

/*
// Delay - this is a modification of original CMSIS-DSP implementation
*/
static void delay_q15(delay_q15_t *pDelay, q15_t *pSrc, q15_t *pDst)
{
    q15_t x;

    x = *pSrc;  // pSrc might be equal with pSrc 
    *pDst = pDelay->pState[pDelay->index];
    pDelay->pState[pDelay->index] = x;
    pDelay->index++;
    if (pDelay->index == pDelay->numTaps)
    {
        pDelay->index = 0;
    }
}

static void vector_delay_q15(delay_q15_t *pDelay, q15_t *pSrc, q15_t *pDst, uint32_t blockSize)
{
    uint32_t  i;

    if (pSrc == pDst)
    {
        for (i = 0; i<blockSize; i++)
        {
            delay_q15(pDelay, pSrc, pSrc);
            pSrc++;
        }
    }
    else
    {
        for (i = 0; i<blockSize; i++)
        {
            delay_q15(pDelay, pSrc++, pDst++);
        }
    }
}


#ifndef POLY_PHASE_UPSAMPLER
// standard FIR implementation
/*
// Upsample
*/
static void up2_q15( q15_t *pSrc, q15_t *pDst, uint32_t blockSize)
{
  uint32_t  i;
  
    for (i=0; i < blockSize; i++)
    {
      *pDst++ = *pSrc++;  // y[i]=x[i]
      *pDst++ = 0;        // y[i+1]=0
    }  
}

static void fir_q15_init(fir_q15_t *pFir)
{
    uint32_t i;

    for (i = 0; i < pFir->numTaps; i++)
    {
        pFir->pState[i] = 0;
    }
    pFir->index = 0;

}

/*
// Fir - this is a modification of original CMSIS-DSP implementation
// Circular buffering for x[n]
// Acculation is done in 8.24 format
*/
static void fir_q15( fir_q15_t *pFir,  q15_t *pSrc, q15_t *pDst)
{
  q15_t *pState = pFir->pState;                   /* State pointer */
  q15_t *pb = pFir->pCoeffs;                      /* Coefficient pointer x[0]*/
  q15_t x;                                        /* x[n-i] */
  q31_t acc;                                      /* acc = sum(x[n-i]*c[i] */
  uint32_t tapIndex;                              /* Loop counters */
  int32_t  i; 
  
    /* update state x[0] = pState[index]*/
    tapIndex = pFir->index;
    pState[tapIndex] = *pSrc;
    /* update index, wrap on vector boundary */    
    pFir->index++;
    if (pFir->index == pFir->numTaps) 
    {
      pFir->index = 0;
    }
    /* Reset accumulator and tap */    
    i = 0;    
    acc = 0;
    /* Perform the multiply-accumulates for all taps */
    for (i=0; i < pFir->numTaps; i++)
    {
      x = pState[tapIndex];
      acc += (((q31_t)(x) * (*pb++)) >> 6); // acc +=x[n-i]*b[i] << Q[1.15]*Q[1.15]=Q[2.30])>>6 =>Q[8.24] >>       
      // update to previous tap
      if (tapIndex==0) 
        tapIndex = pFir->numTaps - 1;
      else 
        tapIndex--;      
    } 
    /* The accumulation result is in 8.24 format. Convert to 1.15         
     ** Then store the output in the destination buffer. */
    *pDst = q15_sat_q24(acc);

}

static void vector_fir_q15(fir_q15_t *pFir,  q15_t *pSrc,  q15_t *pDst,  uint32_t blockSize)
{
  uint32_t  i;
  
    if (pSrc == pDst)
    {
      for (i=0; i<blockSize; i++)
      {         
          fir_q15(pFir, pSrc, pSrc);
          pSrc++;
      }      
    }      
    else
    {
      for (i=0; i<blockSize; i++)
      {
          fir_q15(pFir, pSrc++, pDst++);
      }
    }
}


int32_t up2_sampler(q15_t *p_x, uint32_t in_size, q15_t *p_y1, q15_t *p_y2, uint32_t out_size)
{  
    int32_t err_code;

    if ((p_x == NULL) || (p_y1 == NULL) || (p_y2 == NULL))
    {
        return -1; // NULL pointers
    }

    if ((in_size == 0) || (out_size < 2*in_size))
    {
        return -2; // bad size
    }

    err_code = 2 * in_size;
    up2_q15(p_x, p_y1, in_size);
    vector_fir_q15(&FIR_UP_SAMPLER, p_y1, p_y1, 2*in_size);
    vector_gain_q15(p_y1, 2*in_size);
  
    up2_q15(p_x, p_y2, in_size);
    vector_fir_q15(&FIR_UP_INTERPOLATOR, p_y2, p_y2, 2*in_size);
    vector_delay_q15(&delay, p_y2, p_y2, 2*in_size);
    vector_gain_q15(p_y2, 2*in_size);

    return err_code;  
}

void up2_sampler_init(void)
{
    fir_q15_init(&FIR_UP_SAMPLER);
    fir_q15_init(&FIR_UP_INTERPOLATOR);
    delay_q15_init(&delay);
}

#else
// 2 phase FIR implementation

/*
// 2 phase fir - 1 input sample gives 2 output samples
// Circular buffering for x[n]
// Acculation is done in 8.24 format
*/
void p2fir_q15(
    p2fir_q15_t *pP2Fir,
    q15_t *pSrc,
    q15_t *pDst
    )
{
    q15_t *pState = pP2Fir->pState;                    /* State pointer */
    q15_t *pb;                                         /* Coefficient pointer b[0]*/
    q15_t x;                                           /* x[n-i] */
    q31_t acc;                                         /* acc = sum(x[n-i]*c[i] */
    uint32_t tapIndex, zeroIndex;
    int32_t  i;

    /* update state x[0] = pState[index]*/

    zeroIndex = pP2Fir->index;
    pState[zeroIndex] = *pSrc;
    /* update index, wrap on vector boundary */
    pP2Fir->index++;
    if (pP2Fir->index == pP2Fir->numTaps)
    {
        pP2Fir->index = 0;
    }

    /* Reset accumulator and tapIndex for phase 0*/
    i = 0;
    acc = 0;
    tapIndex = zeroIndex;
    /* *pb = b[0] */
    pb = pP2Fir->pCoeffs;
    /* Perform the multiply-accumulates even-phase */
    for (i = 0; i < pP2Fir->numTaps; i++)
    {
        x = pState[tapIndex];
        acc += (((q31_t)(x)* (*pb)) >> 6); // acc +=x[n-i]*b[i] << Q[1.15]*Q[1.15]=Q[2.30])>>6 =>Q[8.24] >>       
        // even coefficients for phase 0
        pb = pb + 2;
        // update to previous tap
        if (tapIndex == 0)
            tapIndex = pP2Fir->numTaps - 1;
        else
            tapIndex--;
    }
    /* The accumulation result is in 8.24 format. Convert to 1.15
    ** Then store the output in the destination buffer as phase 0 sample */
    *(pDst) = q15_sat_q24(acc);

    /* Reset accumulator and tapIndex for phase 1 */
    i = 0;
    acc = 0;
    tapIndex = zeroIndex;
    /* *pb = b[1] */
    pb = pP2Fir->pCoeffs;
    pb++;
    /* Perform the multiply-accumulates odd-phase */
    for (i = 0; i < pP2Fir->numTaps - 1; i++)
    {
        x = pState[tapIndex];
        acc += (((q31_t)(x)* (*pb)) >> 6); // acc +=x[n-i]*b[i] << Q[1.15]*Q[1.15]=Q[2.30])>>6 =>Q[8.24] >>       
        // even coefficients for phase 0
        pb = pb + 2;
        // update to previous tap
        if (tapIndex == 0)
            tapIndex = pP2Fir->numTaps - 1;
        else
            tapIndex--;
    }
    // for asymetric filter one more accumulation for last even coefficient
    if ((pP2Fir->numCoeffs & 0x0001) == 0)
    {
        x = pState[tapIndex];
        acc += (((q31_t)(x)* (*pb)) >> 6); // acc +=x[n-i]*b[i] << Q[1.15]*Q[1.15]=Q[2.30])>>6 =>Q[8.24] >>             
    }
    /* The accumulation result is in 8.24 format. Convert to 1.15
    ** Then store the output in the destination buffer as phase 1 sample */
    *(++pDst) = q15_sat_q24(acc);

}

void vector_p2fir_q15(
    p2fir_q15_t *pP2Fir,
    q15_t *pSrc,
    q15_t *pDst,
    uint32_t blockSize)
{
    uint32_t  i;

    for (i = 0; i<blockSize; i++)
    {
        p2fir_q15(pP2Fir, pSrc, pDst);
        pSrc++;
        pDst += 2;
    }
}

static void p2fir_q15_init(p2fir_q15_t *pP2Fir)
{
    uint32_t i;

    for (i = 0; i < pP2Fir->numTaps; i++)
    {
        pP2Fir->pState[i] = 0;
    }
    pP2Fir->index = 0;

}

int32_t up2_sampler(q15_t *p_x, uint32_t in_size, q15_t *p_y1, q15_t *p_y2, uint32_t out_size)
{
    int32_t err_code;

    if ((p_x == NULL) || (p_y1 == NULL) || (p_y2 == NULL))
    {
        return -1; // NULL pointers
    }

    if ((in_size == 0) || (out_size < 2 * in_size))
    {
        return -2; // bad size
    }

    err_code = 2 * in_size;
    vector_p2fir_q15(&P2FIR_UP_SAMPLER, p_x, p_y1, in_size);
    vector_gain_q15(p_y1, 2*in_size);

    vector_p2fir_q15(&P2FIR_UP_INTERPOLATOR, p_x, p_y2, in_size);
    vector_delay_q15(&delay, p_y2, p_y2, 2*in_size);
    vector_gain_q15(p_y2, 2 * in_size);

    return err_code;
}

void up2_sampler_init(void)
{
    p2fir_q15_init(&P2FIR_UP_SAMPLER);
    p2fir_q15_init(&P2FIR_UP_INTERPOLATOR);
    delay_q15_init(&delay);
}

#endif
