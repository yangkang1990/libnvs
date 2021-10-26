#ifndef _P2_FIR_UP_INTERPOLATOR_H_ 
#define _P2_FIR_UP_INTERPOLATOR_H_ 
#include "fir_def.h" 

#define P2FIR_UP_INTERPOLATOR                      P2_UP_2_LA_N_9_p2fir
#define P2FIR_UP_INTERPOLATOR_TAPS_N          5
#define P2FIR_UP_INTERPOLATOR_COEFF_N         9

static q15_t P2_UP_2_LA_N_9_state[P2FIR_UP_INTERPOLATOR_TAPS_N] = {0};
static q15_t P2_UP_2_LA_N_9_coeff[P2FIR_UP_INTERPOLATOR_COEFF_N] = {
    (q15_t)((-0.0f)*Q15_SCALE),
    (q15_t)((-0.03184f)*Q15_SCALE),
    (q15_t)((0.0f)*Q15_SCALE),
    (q15_t)((0.28658f)*Q15_SCALE),
    (q15_t)((0.5f)*Q15_SCALE),
    (q15_t)((0.28658f)*Q15_SCALE),
    (q15_t)((0.0f)*Q15_SCALE),
    (q15_t)((-0.03184f)*Q15_SCALE),
    (q15_t)((-0.0f)*Q15_SCALE),
};

static p2fir_q15_t P2_UP_2_LA_N_9_p2fir = {
.numTaps = P2FIR_UP_INTERPOLATOR_TAPS_N,
.numCoeffs = P2FIR_UP_INTERPOLATOR_COEFF_N,
.index = 0,
.pState = P2_UP_2_LA_N_9_state,
.pCoeffs = P2_UP_2_LA_N_9_coeff
};
#endif  //_P2_FIR_UP_INTERPOLATOR_H_ 
