#ifndef _P2FIR_UPSAMPLE_H 
#define _P2FIR_UPSAMPLE_H 
#include "fir_def.h" 

#define P2FIR_UP_SAMPLER                      P2_UP_2_Eq1_60dB_p2fir
#define P2FIR_UP_SAMPLER_TAPS_N          51
#define P2FIR_UP_SAMPLER_COEFF_N         101

static q15_t P2_UP_2_Eq1_60dB_state[P2FIR_UP_SAMPLER_TAPS_N] = {0};
static q15_t P2_UP_2_Eq1_60dB_coeff[P2FIR_UP_SAMPLER_COEFF_N] = {
    (q15_t)((-0.00346438252234f)*Q15_SCALE),
    (q15_t)((-0.00706987193789f)*Q15_SCALE),
    (q15_t)((-0.00419070565293f)*Q15_SCALE),
    (q15_t)((0.00609796707018f)*Q15_SCALE),
    (q15_t)((0.0131447124003f)*Q15_SCALE),
    (q15_t)((0.00849408092996f)*Q15_SCALE),
    (q15_t)((-0.000138320912758f)*Q15_SCALE),
    (q15_t)((-2.48309324332e-05f)*Q15_SCALE),
    (q15_t)((0.00598508704831f)*Q15_SCALE),
    (q15_t)((0.00515694782892f)*Q15_SCALE),
    (q15_t)((-0.00185298414448f)*Q15_SCALE),
    (q15_t)((-0.0022848560277f)*Q15_SCALE),
    (q15_t)((0.00430556756852f)*Q15_SCALE),
    (q15_t)((0.00453332315933f)*Q15_SCALE),
    (q15_t)((-0.00297773451781f)*Q15_SCALE),
    (q15_t)((-0.00389438710337f)*Q15_SCALE),
    (q15_t)((0.0040470967646f)*Q15_SCALE),
    (q15_t)((0.00521064724992f)*Q15_SCALE),
    (q15_t)((-0.00370693573127f)*Q15_SCALE),
    (q15_t)((-0.00554320510296f)*Q15_SCALE),
    (q15_t)((0.00421916974487f)*Q15_SCALE),
    (q15_t)((0.00665040669163f)*Q15_SCALE),
    (q15_t)((-0.00422234601184f)*Q15_SCALE),
    (q15_t)((-0.00749127987616f)*Q15_SCALE),
    (q15_t)((0.00453932477853f)*Q15_SCALE),
    (q15_t)((0.00873653327023f)*Q15_SCALE),
    (q15_t)((-0.00466180572865f)*Q15_SCALE),
    (q15_t)((-0.010029608634f)*Q15_SCALE),
    (q15_t)((0.00488061459074f)*Q15_SCALE),
    (q15_t)((0.0116326361768f)*Q15_SCALE),
    (q15_t)((-0.0050333635526f)*Q15_SCALE),
    (q15_t)((-0.0134936358977f)*Q15_SCALE),
    (q15_t)((0.00520375058541f)*Q15_SCALE),
    (q15_t)((0.0157762933019f)*Q15_SCALE),
    (q15_t)((-0.00533083683024f)*Q15_SCALE),
    (q15_t)((-0.0185701220328f)*Q15_SCALE),
    (q15_t)((0.00547062852283f)*Q15_SCALE),
    (q15_t)((0.0221684246588f)*Q15_SCALE),
    (q15_t)((-0.00557626750073f)*Q15_SCALE),
    (q15_t)((-0.0269496459262f)*Q15_SCALE),
    (q15_t)((0.00567984940967f)*Q15_SCALE),
    (q15_t)((0.0337317189242f)*Q15_SCALE),
    (q15_t)((-0.00575694721448f)*Q15_SCALE),
    (q15_t)((-0.0441890067955f)*Q15_SCALE),
    (q15_t)((0.00582355877892f)*Q15_SCALE),
    (q15_t)((0.0627431456746f)*Q15_SCALE),
    (q15_t)((-0.00586698773044f)*Q15_SCALE),
    (q15_t)((-0.105551352473f)*Q15_SCALE),
    (q15_t)((0.00589161976166f)*Q15_SCALE),
    (q15_t)((0.318123715252f)*Q15_SCALE),
    (q15_t)((0.494096653611f)*Q15_SCALE),
    (q15_t)((0.318123715252f)*Q15_SCALE),
    (q15_t)((0.00589161976166f)*Q15_SCALE),
    (q15_t)((-0.105551352473f)*Q15_SCALE),
    (q15_t)((-0.00586698773044f)*Q15_SCALE),
    (q15_t)((0.0627431456746f)*Q15_SCALE),
    (q15_t)((0.00582355877892f)*Q15_SCALE),
    (q15_t)((-0.0441890067955f)*Q15_SCALE),
    (q15_t)((-0.00575694721448f)*Q15_SCALE),
    (q15_t)((0.0337317189242f)*Q15_SCALE),
    (q15_t)((0.00567984940967f)*Q15_SCALE),
    (q15_t)((-0.0269496459262f)*Q15_SCALE),
    (q15_t)((-0.00557626750073f)*Q15_SCALE),
    (q15_t)((0.0221684246588f)*Q15_SCALE),
    (q15_t)((0.00547062852283f)*Q15_SCALE),
    (q15_t)((-0.0185701220328f)*Q15_SCALE),
    (q15_t)((-0.00533083683024f)*Q15_SCALE),
    (q15_t)((0.0157762933019f)*Q15_SCALE),
    (q15_t)((0.00520375058541f)*Q15_SCALE),
    (q15_t)((-0.0134936358977f)*Q15_SCALE),
    (q15_t)((-0.0050333635526f)*Q15_SCALE),
    (q15_t)((0.0116326361768f)*Q15_SCALE),
    (q15_t)((0.00488061459074f)*Q15_SCALE),
    (q15_t)((-0.010029608634f)*Q15_SCALE),
    (q15_t)((-0.00466180572865f)*Q15_SCALE),
    (q15_t)((0.00873653327023f)*Q15_SCALE),
    (q15_t)((0.00453932477853f)*Q15_SCALE),
    (q15_t)((-0.00749127987616f)*Q15_SCALE),
    (q15_t)((-0.00422234601184f)*Q15_SCALE),
    (q15_t)((0.00665040669163f)*Q15_SCALE),
    (q15_t)((0.00421916974487f)*Q15_SCALE),
    (q15_t)((-0.00554320510296f)*Q15_SCALE),
    (q15_t)((-0.00370693573127f)*Q15_SCALE),
    (q15_t)((0.00521064724992f)*Q15_SCALE),
    (q15_t)((0.0040470967646f)*Q15_SCALE),
    (q15_t)((-0.00389438710337f)*Q15_SCALE),
    (q15_t)((-0.00297773451781f)*Q15_SCALE),
    (q15_t)((0.00453332315933f)*Q15_SCALE),
    (q15_t)((0.00430556756852f)*Q15_SCALE),
    (q15_t)((-0.0022848560277f)*Q15_SCALE),
    (q15_t)((-0.00185298414448f)*Q15_SCALE),
    (q15_t)((0.00515694782892f)*Q15_SCALE),
    (q15_t)((0.00598508704831f)*Q15_SCALE),
    (q15_t)((-2.48309324332e-05f)*Q15_SCALE),
    (q15_t)((-0.000138320912758f)*Q15_SCALE),
    (q15_t)((0.00849408092996f)*Q15_SCALE),
    (q15_t)((0.0131447124003f)*Q15_SCALE),
    (q15_t)((0.00609796707018f)*Q15_SCALE),
    (q15_t)((-0.00419070565293f)*Q15_SCALE),
    (q15_t)((-0.00706987193789f)*Q15_SCALE),
    (q15_t)((-0.00346438252234f)*Q15_SCALE),
};

static p2fir_q15_t P2_UP_2_Eq1_60dB_p2fir = {
.numTaps = P2FIR_UP_SAMPLER_TAPS_N,
.numCoeffs = P2FIR_UP_SAMPLER_COEFF_N,
.index = 0,
.pState = P2_UP_2_Eq1_60dB_state,
.pCoeffs = P2_UP_2_Eq1_60dB_coeff
};
#endif  //_P2FIR_UPSAMPLE_H 
