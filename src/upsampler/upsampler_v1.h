#ifndef _UP_SAMPLER_H 
#define _UP_SAMPLER_H

#define POLY_PHASE_UPSAMPLER

#include "cmsis_q_types.h"

/**@brief up by 2 sampler module.
*
* @details 
*          two up sampled by 2 vectors are produced: 
*          p_y1 is upsampled by long FIR filter, 
*          p_y2 is upsampled by short FIR filter
*          delay in second path compensates differences in group delay
* @param[in]        p_x         pointer to vector of input samples in Q1.15.
* @param[in]        in_size     input samples vector size.
* @param[int,out]   p_y1        pointer to vector of output samples in Q1.15.
* @param[int,out]   p_y2        pointer to vector of output samples in Q1.15.
* @param[in]        out_size    p_y1, p_y2 vector size  
*
* @return                       number of samples in p_y1,p_y2 (normally 2*in_size) or error code
*/
int32_t up2_sampler(q15_t *p_x, uint32_t in_size, q15_t *p_y1, q15_t *p_y2, uint32_t out_size);

/**@brief up by 2 sampler module init - reset state vectors and indexes
*/
void up2_sampler_init(void);
#endif 
