#ifndef _FIR_UP_INTERPOLATOR_H_ 
#define _FIR_UP_INTERPOLATOR_H_ 
#include "fir_def.h" 

#define FIR_UP_INTERPOLATOR                      UP_2_LA_N_13_fir
#define FIR_UP_INTERPOLATOR_TAPS_N          13

static q15_t UP_2_LA_N_13_state[FIR_UP_INTERPOLATOR_TAPS_N] = {0};
static q15_t UP_2_LA_N_13_taps[FIR_UP_INTERPOLATOR_TAPS_N] = {
    (q15_t)((0.0f)*Q15_SCALE),
    (q15_t)((0.01216f)*Q15_SCALE),
    (q15_t)((-0.0f)*Q15_SCALE),
    (q15_t)((-0.06755f)*Q15_SCALE),
    (q15_t)((0.0f)*Q15_SCALE),
    (q15_t)((0.30396f)*Q15_SCALE),
    (q15_t)((0.5f)*Q15_SCALE),
    (q15_t)((0.30396f)*Q15_SCALE),
    (q15_t)((0.0f)*Q15_SCALE),
    (q15_t)((-0.06755f)*Q15_SCALE),
    (q15_t)((-0.0f)*Q15_SCALE),
    (q15_t)((0.01216f)*Q15_SCALE),
    (q15_t)((0.0f)*Q15_SCALE),
};

static fir_q15_t UP_2_LA_N_13_fir = {
.numTaps = FIR_UP_INTERPOLATOR_TAPS_N,
.index = 0,
.pState = UP_2_LA_N_13_state,
.pCoeffs = UP_2_LA_N_13_taps
};
#endif  //_FIR_UP_INTERPOLATOR_H_ 
