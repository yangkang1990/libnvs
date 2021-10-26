#ifndef _FIR_DEF_H_
#define _FIR_DEF_H_

#include "cmsis_q_types.h"

#define Q15_SCALE  32567
#define Q14_SCALE  16384


/**
* @brief Instance structure for the Q15 FIR filter.
*/

typedef struct
{
    uint16_t    numTaps;            /**< number of filter coefficients in the filter. */
    uint16_t    index;              /**< index to pState[index]=x[0]. */
    q15_t       *pState;            /**< points to the state variable vector. The vector is of length numTaps. */
    q15_t       *pCoeffs;           /**< points to the coefficient array. The vector is of length numTaps.*/
} fir_q15_t;

/**
* @brief Instance structure for the Q15 delay block.
*/

typedef struct
{
    uint16_t    numTaps;            /**< number of delay taps */
    uint16_t    index;              /**< index to pState[index]=x[0]. */
    q15_t       *pState;            /**< points to the state variable array. Z^-N has a N taps */
} delay_q15_t;

/**
* @brief 2 phase, up by 2 sampler module.
*
* @details
* 2-phase fir filter (aka poly-phase, for two-phase up-by-2-sampler)
* for symetric filter: numCoeffs=2*numTaps-1
* for asymetric filter: numCoeffs=2*numTaps
* for symetric filter group delay is integer number
*/
typedef struct
{
    uint16_t    numTaps;            /**< vector size(pState) != vector size(pCoeffs)  */
    uint16_t    numCoeffs;          /**< vector size(pCoeffs) != vector size(pState)  */
    uint16_t    index;              /**< index to pState[index]=x[0]. */
    q15_t       *pState;            /**< points to the state variable vector. The vector is of length numTaps. */
    q15_t       *pCoeffs;           /**< points to the coefficient array. The vector is of length numTaps.*/
} p2fir_q15_t;

#endif

