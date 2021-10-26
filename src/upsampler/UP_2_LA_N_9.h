#ifndef _FIR_UP_INTERPOLATOR_H_ 
#define _FIR_UP_INTERPOLATOR_H_ 
#include "fir_def.h" 

#define FIR_UP_INTERPOLATOR                      UP_2_LA_N_9_fir
#define FIR_UP_INTERPOLATOR_TAPS_N          9

static q15_t UP_2_LA_N_9_state[FIR_UP_INTERPOLATOR_TAPS_N] = {0};
static q15_t UP_2_LA_N_9_taps[FIR_UP_INTERPOLATOR_TAPS_N] = {
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

static fir_q15_t UP_2_LA_N_9_fir = {
.numTaps = FIR_UP_INTERPOLATOR_TAPS_N,
.index = 0,
.pState = UP_2_LA_N_9_state,
.pCoeffs = UP_2_LA_N_9_taps
};
#endif  //_FIR_UP_INTERPOLATOR_H_ 
