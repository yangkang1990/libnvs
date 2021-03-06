#ifndef _P2_FIR_UP_INTERPOLATOR_H_ 
#define _P2_FIR_UP_INTERPOLATOR_H_ 
#include "fir_def.h" 

#define P2FIR_UP_INTERPOLATOR                      P2_UP_2_WR3_p2fir
#define P2FIR_UP_INTERPOLATOR_TAPS_N          38
#define P2FIR_UP_INTERPOLATOR_COEFF_N         75

static q15_t P2_UP_2_WR3_state[P2FIR_UP_INTERPOLATOR_TAPS_N] = {0};
static q15_t P2_UP_2_WR3_coeff[P2FIR_UP_INTERPOLATOR_COEFF_N] = {
    (q15_t)((0.00789551459582f)*Q15_SCALE),
    (q15_t)((-1.4340096177e-08f)*Q15_SCALE),
    (q15_t)((-0.00834668685844f)*Q15_SCALE),
    (q15_t)((1.43400961838e-08f)*Q15_SCALE),
    (q15_t)((0.00885254666804f)*Q15_SCALE),
    (q15_t)((-1.43400961914e-08f)*Q15_SCALE),
    (q15_t)((-0.00942367871114f)*Q15_SCALE),
    (q15_t)((1.43400962001e-08f)*Q15_SCALE),
    (q15_t)((0.0100735875878f)*Q15_SCALE),
    (q15_t)((-1.43400962099e-08f)*Q15_SCALE),
    (q15_t)((-0.0108197792609f)*Q15_SCALE),
    (q15_t)((1.43400962213e-08f)*Q15_SCALE),
    (q15_t)((0.0116853616018f)*Q15_SCALE),
    (q15_t)((-1.43400962347e-08f)*Q15_SCALE),
    (q15_t)((-0.012701480002f)*Q15_SCALE),
    (q15_t)((1.4340096156e-08f)*Q15_SCALE),
    (q15_t)((0.0139111447641f)*Q15_SCALE),
    (q15_t)((-1.43400961655e-08f)*Q15_SCALE),
    (q15_t)((-0.0153754757919f)*Q15_SCALE),
    (q15_t)((1.4340096177e-08f)*Q15_SCALE),
    (q15_t)((0.0171843552968f)*Q15_SCALE),
    (q15_t)((-1.43400961914e-08f)*Q15_SCALE),
    (q15_t)((-0.0194756026697f)*Q15_SCALE),
    (q15_t)((1.43400962099e-08f)*Q15_SCALE),
    (q15_t)((0.0224718492343f)*Q15_SCALE),
    (q15_t)((-1.43400962347e-08f)*Q15_SCALE),
    (q15_t)((-0.0265576400042f)*Q15_SCALE),
    (q15_t)((1.43400961655e-08f)*Q15_SCALE),
    (q15_t)((0.0324593377829f)*Q15_SCALE),
    (q15_t)((-1.43400961914e-08f)*Q15_SCALE),
    (q15_t)((-0.0417334342923f)*Q15_SCALE),
    (q15_t)((1.43400962347e-08f)*Q15_SCALE),
    (q15_t)((0.0584268080092f)*Q15_SCALE),
    (q15_t)((-1.43400961914e-08f)*Q15_SCALE),
    (q15_t)((-0.0973780133486f)*Q15_SCALE),
    (q15_t)((1.43400961914e-08f)*Q15_SCALE),
    (q15_t)((0.292134040046f)*Q15_SCALE),
    (q15_t)((0.458883062696f)*Q15_SCALE),
    (q15_t)((0.292134040046f)*Q15_SCALE),
    (q15_t)((1.43400961914e-08f)*Q15_SCALE),
    (q15_t)((-0.0973780133486f)*Q15_SCALE),
    (q15_t)((-1.43400961914e-08f)*Q15_SCALE),
    (q15_t)((0.0584268080092f)*Q15_SCALE),
    (q15_t)((1.43400962347e-08f)*Q15_SCALE),
    (q15_t)((-0.0417334342923f)*Q15_SCALE),
    (q15_t)((-1.43400961914e-08f)*Q15_SCALE),
    (q15_t)((0.0324593377829f)*Q15_SCALE),
    (q15_t)((1.43400961655e-08f)*Q15_SCALE),
    (q15_t)((-0.0265576400042f)*Q15_SCALE),
    (q15_t)((-1.43400962347e-08f)*Q15_SCALE),
    (q15_t)((0.0224718492343f)*Q15_SCALE),
    (q15_t)((1.43400962099e-08f)*Q15_SCALE),
    (q15_t)((-0.0194756026697f)*Q15_SCALE),
    (q15_t)((-1.43400961914e-08f)*Q15_SCALE),
    (q15_t)((0.0171843552968f)*Q15_SCALE),
    (q15_t)((1.4340096177e-08f)*Q15_SCALE),
    (q15_t)((-0.0153754757919f)*Q15_SCALE),
    (q15_t)((-1.43400961655e-08f)*Q15_SCALE),
    (q15_t)((0.0139111447641f)*Q15_SCALE),
    (q15_t)((1.4340096156e-08f)*Q15_SCALE),
    (q15_t)((-0.012701480002f)*Q15_SCALE),
    (q15_t)((-1.43400962347e-08f)*Q15_SCALE),
    (q15_t)((0.0116853616018f)*Q15_SCALE),
    (q15_t)((1.43400962213e-08f)*Q15_SCALE),
    (q15_t)((-0.0108197792609f)*Q15_SCALE),
    (q15_t)((-1.43400962099e-08f)*Q15_SCALE),
    (q15_t)((0.0100735875878f)*Q15_SCALE),
    (q15_t)((1.43400962001e-08f)*Q15_SCALE),
    (q15_t)((-0.00942367871114f)*Q15_SCALE),
    (q15_t)((-1.43400961914e-08f)*Q15_SCALE),
    (q15_t)((0.00885254666804f)*Q15_SCALE),
    (q15_t)((1.43400961838e-08f)*Q15_SCALE),
    (q15_t)((-0.00834668685844f)*Q15_SCALE),
    (q15_t)((-1.4340096177e-08f)*Q15_SCALE),
    (q15_t)((0.00789551459582f)*Q15_SCALE),
};

static p2fir_q15_t P2_UP_2_WR3_p2fir = {
.numTaps = P2FIR_UP_INTERPOLATOR_TAPS_N,
.numCoeffs = P2FIR_UP_INTERPOLATOR_COEFF_N,
.index = 0,
.pState = P2_UP_2_WR3_state,
.pCoeffs = P2_UP_2_WR3_coeff
};
#endif  //_P2_FIR_UP_INTERPOLATOR_H_ 
