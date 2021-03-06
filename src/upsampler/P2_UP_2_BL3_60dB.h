#ifndef _P2FIR_UPSAMPLE_H_ 
#define _P2FIR_UPSAMPLE_H_ 
#include "fir_def.h" 

#define P2FIR_UP_SAMPLER                      P2_UP_2_BL3_60dB_p2fir
#define P2FIR_UP_SAMPLER_TAPS_N          275
#define P2FIR_UP_SAMPLER_COEFF_N         549

static q15_t P2_UP_2_BL3_60dB_state[P2FIR_UP_SAMPLER_TAPS_N] = {0};
static q15_t P2_UP_2_BL3_60dB_coeff[P2FIR_UP_SAMPLER_COEFF_N] = {
    (q15_t)((1.59011824389e-35f)*Q15_SCALE),
    (q15_t)((1.37936361473e-08f)*Q15_SCALE),
    (q15_t)((6.51722049974e-22f)*Q15_SCALE),
    (q15_t)((-1.25106387805e-07f)*Q15_SCALE),
    (q15_t)((7.65855757576e-21f)*Q15_SCALE),
    (q15_t)((3.50367092403e-07f)*Q15_SCALE),
    (q15_t)((-1.19145374538e-20f)*Q15_SCALE),
    (q15_t)((-6.92649285226e-07f)*Q15_SCALE),
    (q15_t)((1.15722568446e-20f)*Q15_SCALE),
    (q15_t)((1.15537566321e-06f)*Q15_SCALE),
    (q15_t)((-2.8001520981e-21f)*Q15_SCALE),
    (q15_t)((-1.74232893178e-06f)*Q15_SCALE),
    (q15_t)((-1.83918644596e-20f)*Q15_SCALE),
    (q15_t)((2.45766234312e-06f)*Q15_SCALE),
    (q15_t)((-1.06676895337e-19f)*Q15_SCALE),
    (q15_t)((-3.30590991661e-06f)*Q15_SCALE),
    (q15_t)((1.0003906469e-19f)*Q15_SCALE),
    (q15_t)((4.29199633356e-06f)*Q15_SCALE),
    (q15_t)((-7.58413763352e-20f)*Q15_SCALE),
    (q15_t)((-5.42124649949e-06f)*Q15_SCALE),
    (q15_t)((2.95684601069e-20f)*Q15_SCALE),
    (q15_t)((6.69939476902e-06f)*Q15_SCALE),
    (q15_t)((4.35358928254e-20f)*Q15_SCALE),
    (q15_t)((-8.13259382943e-06f)*Q15_SCALE),
    (q15_t)((3.57948239434e-19f)*Q15_SCALE),
    (q15_t)((9.72742324094e-06f)*Q15_SCALE),
    (q15_t)((-3.11233520089e-19f)*Q15_SCALE),
    (q15_t)((-1.14908976331e-05f)*Q15_SCALE),
    (q15_t)((2.31541525659e-19f)*Q15_SCALE),
    (q15_t)((1.34304745586e-05f)*Q15_SCALE),
    (q15_t)((-1.1335936932e-19f)*Q15_SCALE),
    (q15_t)((-1.55540620075e-05f)*Q15_SCALE),
    (q15_t)((-4.91584333558e-20f)*Q15_SCALE),
    (q15_t)((1.78700255872e-05f)*Q15_SCALE),
    (q15_t)((-8.23659012981e-19f)*Q15_SCALE),
    (q15_t)((-2.03871953738e-05f)*Q15_SCALE),
    (q15_t)((7.02479506235e-19f)*Q15_SCALE),
    (q15_t)((2.31148724458e-05f)*Q15_SCALE),
    (q15_t)((-5.29424847243e-19f)*Q15_SCALE),
    (q15_t)((-2.60628351094e-05f)*Q15_SCALE),
    (q15_t)((2.97638626181e-19f)*Q15_SCALE),
    (q15_t)((2.92413448301e-05f)*Q15_SCALE),
    (q15_t)((1.67619797465e-22f)*Q15_SCALE),
    (q15_t)((-3.26611518857e-05f)*Q15_SCALE),
    (q15_t)((-3.71740664022e-19f)*Q15_SCALE),
    (q15_t)((3.63335007597e-05f)*Q15_SCALE),
    (q15_t)((-1.34997338414e-18f)*Q15_SCALE),
    (q15_t)((-4.02701352943e-05f)*Q15_SCALE),
    (q15_t)((1.03720230066e-18f)*Q15_SCALE),
    (q15_t)((4.44833036296e-05f)*Q15_SCALE),
    (q15_t)((-6.40484566956e-19f)*Q15_SCALE),
    (q15_t)((-4.89857629527e-05f)*Q15_SCALE),
    (q15_t)((1.5071054717e-19f)*Q15_SCALE),
    (q15_t)((5.37907840874e-05f)*Q15_SCALE),
    (q15_t)((4.41794612832e-19f)*Q15_SCALE),
    (q15_t)((-5.89121559578e-05f)*Q15_SCALE),
    (q15_t)((2.35402410115e-18f)*Q15_SCALE),
    (q15_t)((6.43641899607e-05f)*Q15_SCALE),
    (q15_t)((-1.84425614227e-18f)*Q15_SCALE),
    (q15_t)((-7.0161724288e-05f)*Q15_SCALE),
    (q15_t)((1.21913331218e-18f)*Q15_SCALE),
    (q15_t)((7.63201282404e-05f)*Q15_SCALE),
    (q15_t)((-4.67326997753e-19f)*Q15_SCALE),
    (q15_t)((-8.2855306582e-05f)*Q15_SCALE),
    (q15_t)((-4.23168334299e-19f)*Q15_SCALE),
    (q15_t)((8.97837039859e-05f)*Q15_SCALE),
    (q15_t)((1.46506419036e-18f)*Q15_SCALE),
    (q15_t)((-9.7122309627e-05f)*Q15_SCALE),
    (q15_t)((3.06658687771e-18f)*Q15_SCALE),
    (q15_t)((0.000104888661984f)*Q15_SCALE),
    (q15_t)((-2.13479150685e-18f)*Q15_SCALE),
    (q15_t)((-0.000113100853914f)*Q15_SCALE),
    (q15_t)((1.03479936556e-18f)*Q15_SCALE),
    (q15_t)((0.000121777538073f)*Q15_SCALE),
    (q15_t)((2.48145361175e-19f)*Q15_SCALE),
    (q15_t)((-0.000130937932761f)*Q15_SCALE),
    (q15_t)((-1.72962224788e-18f)*Q15_SCALE),
    (q15_t)((0.000140601828266f)*Q15_SCALE),
    (q15_t)((-4.85198090332e-18f)*Q15_SCALE),
    (q15_t)((-0.000150789593813f)*Q15_SCALE),
    (q15_t)((3.51769272121e-18f)*Q15_SCALE),
    (q15_t)((0.000161522185194f)*Q15_SCALE),
    (q15_t)((-1.96445867048e-18f)*Q15_SCALE),
    (q15_t)((-0.000172821153205f)*Q15_SCALE),
    (q15_t)((1.74333346968e-19f)*Q15_SCALE),
    (q15_t)((0.000184708652987f)*Q15_SCALE),
    (q15_t)((1.87157692816e-18f)*Q15_SCALE),
    (q15_t)((-0.000197207454397f)*Q15_SCALE),
    (q15_t)((7.38548091936e-18f)*Q15_SCALE),
    (q15_t)((0.000210340953549f)*Q15_SCALE),
    (q15_t)((-5.53246272119e-18f)*Q15_SCALE),
    (q15_t)((-0.000224133185652f)*Q15_SCALE),
    (q15_t)((3.3990959518e-18f)*Q15_SCALE),
    (q15_t)((0.00023860883932f)*Q15_SCALE),
    (q15_t)((-9.63777417463e-19f)*Q15_SCALE),
    (q15_t)((-0.000253793272488f)*Q15_SCALE),
    (q15_t)((-1.79617970274e-18f)*Q15_SCALE),
    (q15_t)((0.000269712530155f)*Q15_SCALE),
    (q15_t)((-1.08953894396e-17f)*Q15_SCALE),
    (q15_t)((-0.000286393364115f)*Q15_SCALE),
    (q15_t)((8.38399860959e-18f)*Q15_SCALE),
    (q15_t)((0.000303863254901f)*Q15_SCALE),
    (q15_t)((-5.51868140388e-18f)*Q15_SCALE),
    (q15_t)((-0.000322150436175f)*Q15_SCALE),
    (q15_t)((2.27366106665e-18f)*Q15_SCALE),
    (q15_t)((0.000341283921809f)*Q15_SCALE),
    (q15_t)((1.37807644905e-18f)*Q15_SCALE),
    (q15_t)((-0.000361293535926f)*Q15_SCALE),
    (q15_t)((-5.46482579085e-18f)*Q15_SCALE),
    (q15_t)((0.000382209946203f)*Q15_SCALE),
    (q15_t)((-1.23242804632e-17f)*Q15_SCALE),
    (q15_t)((-0.000404064700755f)*Q15_SCALE),
    (q15_t)((8.54692857756e-18f)*Q15_SCALE),
    (q15_t)((0.000426890268948f)*Q15_SCALE),
    (q15_t)((-4.29765820418e-18f)*Q15_SCALE),
    (q15_t)((-0.000450720086542f)*Q15_SCALE),
    (q15_t)((-4.55498590851e-19f)*Q15_SCALE),
    (q15_t)((0.000475588605563f)*Q15_SCALE),
    (q15_t)((-8.13584349516e-18f)*Q15_SCALE),
    (q15_t)((-0.000501531349387f)*Q15_SCALE),
    (q15_t)((3.02604097182e-18f)*Q15_SCALE),
    (q15_t)((0.000528584973535f)*Q15_SCALE),
    (q15_t)((-1.27593848401e-17f)*Q15_SCALE),
    (q15_t)((-0.00055678733274f)*Q15_SCALE),
    (q15_t)((7.27719815871e-18f)*Q15_SCALE),
    (q15_t)((0.000586177554903f)*Q15_SCALE),
    (q15_t)((-1.17659954317e-18f)*Q15_SCALE),
    (q15_t)((-0.000616796122619f)*Q15_SCALE),
    (q15_t)((1.23971376689e-17f)*Q15_SCALE),
    (q15_t)((0.000648684963022f)*Q15_SCALE),
    (q15_t)((-5.86446672966e-18f)*Q15_SCALE),
    (q15_t)((-0.000681887546796f)*Q15_SCALE),
    (q15_t)((-1.3724329261e-18f)*Q15_SCALE),
    (q15_t)((0.00071644899725f)*Q15_SCALE),
    (q15_t)((-1.15113913697e-17f)*Q15_SCALE),
    (q15_t)((-0.000752416210517f)*Q15_SCALE),
    (q15_t)((3.77535780142e-18f)*Q15_SCALE),
    (q15_t)((0.000789837987989f)*Q15_SCALE),
    (q15_t)((4.76042503448e-18f)*Q15_SCALE),
    (q15_t)((-0.000828765182296f)*Q15_SCALE),
    (q15_t)((9.97994597253e-18f)*Q15_SCALE),
    (q15_t)((0.000869250858221f)*Q15_SCALE),
    (q15_t)((-8.69600536166e-19f)*Q15_SCALE),
    (q15_t)((-0.000911350470178f)*Q15_SCALE),
    (q15_t)((1.73711089566e-17f)*Q15_SCALE),
    (q15_t)((0.000955122058018f)*Q15_SCALE),
    (q15_t)((-7.66234228415e-18f)*Q15_SCALE),
    (q15_t)((-0.00100062646319f)*Q15_SCALE),
    (q15_t)((-3.01389809235e-18f)*Q15_SCALE),
    (q15_t)((0.00104792756753f)*Q15_SCALE),
    (q15_t)((-1.57602505365e-17f)*Q15_SCALE),
    (q15_t)((-0.00109709255717f)*Q15_SCALE),
    (q15_t)((4.39685726306e-18f)*Q15_SCALE),
    (q15_t)((0.0011481922146f)*Q15_SCALE),
    (q15_t)((-2.53202498942e-17f)*Q15_SCALE),
    (q15_t)((-0.00120130124197f)*Q15_SCALE),
    (q15_t)((1.32420810887e-17f)*Q15_SCALE),
    (q15_t)((0.0012564986195f)*Q15_SCALE),
    (q15_t)((3.48274574233e-21f)*Q15_SCALE),
    (q15_t)((-0.00131386800314f)*Q15_SCALE),
    (q15_t)((2.36953298449e-17f)*Q15_SCALE),
    (q15_t)((0.00137349816638f)*Q15_SCALE),
    (q15_t)((-9.62965004313e-18f)*Q15_SCALE),
    (q15_t)((-0.00143548349167f)*Q15_SCALE),
    (q15_t)((-5.75628839712e-18f)*Q15_SCALE),
    (q15_t)((0.00149992451773f)*Q15_SCALE),
    (q15_t)((-2.10315168891e-17f)*Q15_SCALE),
    (q15_t)((-0.00156692855019f)*Q15_SCALE),
    (q15_t)((4.70451280724e-18f)*Q15_SCALE),
    (q15_t)((0.00163661034369f)*Q15_SCALE),
    (q15_t)((1.31172019519e-17f)*Q15_SCALE),
    (q15_t)((-0.00170909286535f)*Q15_SCALE),
    (q15_t)((1.71118348079e-17f)*Q15_SCALE),
    (q15_t)((0.00178450815052f)*Q15_SCALE),
    (q15_t)((1.79126038234e-18f)*Q15_SCALE),
    (q15_t)((-0.00186299826415f)*Q15_SCALE),
    (q15_t)((3.17089221107e-17f)*Q15_SCALE),
    (q15_t)((0.00194471638253f)*Q15_SCALE),
    (q15_t)((-1.16788482891e-17f)*Q15_SCALE),
    (q15_t)((-0.00202982801343f)*Q15_SCALE),
    (q15_t)((-1.01663539177e-17f)*Q15_SCALE),
    (q15_t)((0.00211851237513f)*Q15_SCALE),
    (q15_t)((-2.75696078221e-17f)*Q15_SCALE),
    (q15_t)((-0.00221096395875f)*Q15_SCALE),
    (q15_t)((4.42250532541e-18f)*Q15_SCALE),
    (q15_t)((0.00230739430274f)*Q15_SCALE),
    (q15_t)((-4.619851825e-17f)*Q15_SCALE),
    (q15_t)((-0.0024080340133f)*Q15_SCALE),
    (q15_t)((2.16936517897e-17f)*Q15_SCALE),
    (q15_t)((0.00251313507138f)*Q15_SCALE),
    (q15_t)((5.03753192744e-18f)*Q15_SCALE),
    (q15_t)((-0.00262297347435f)*Q15_SCALE),
    (q15_t)((4.20160724911e-17f)*Q15_SCALE),
    (q15_t)((0.00273785227002f)*Q15_SCALE),
    (q15_t)((-1.37022907805e-17f)*Q15_SCALE),
    (q15_t)((-0.00285810505258f)*Q15_SCALE),
    (q15_t)((2.43227416845e-17f)*Q15_SCALE),
    (q15_t)((0.00298410000404f)*Q15_SCALE),
    (q15_t)((-3.58574087564e-17f)*Q15_SCALE),
    (q15_t)((-0.00311624458314f)*Q15_SCALE),
    (q15_t)((3.11574803813e-18f)*Q15_SCALE),
    (q15_t)((0.00325499098558f)*Q15_SCALE),
    (q15_t)((-1.46673330175e-17f)*Q15_SCALE),
    (q15_t)((-0.00340084252746f)*Q15_SCALE),
    (q15_t)((2.72525424785e-17f)*Q15_SCALE),
    (q15_t)((0.00355436113935f)*Q15_SCALE),
    (q15_t)((1.06909338338e-17f)*Q15_SCALE),
    (q15_t)((-0.00371617620252f)*Q15_SCALE),
    (q15_t)((1.85645323051e-18f)*Q15_SCALE),
    (q15_t)((0.00388699501658f)*Q15_SCALE),
    (q15_t)((-1.55810141764e-17f)*Q15_SCALE),
    (q15_t)((-0.00406761526067f)*Q15_SCALE),
    (q15_t)((3.05856176552e-17f)*Q15_SCALE),
    (q15_t)((0.00425893990565f)*Q15_SCALE),
    (q15_t)((-4.69859988109e-17f)*Q15_SCALE),
    (q15_t)((-0.00446199515869f)*Q15_SCALE),
    (q15_t)((-6.19117577813e-21f)*Q15_SCALE),
    (q15_t)((0.00467795218476f)*Q15_SCALE),
    (q15_t)((-1.64284695479e-17f)*Q15_SCALE),
    (q15_t)((-0.0049081535664f)*Q15_SCALE),
    (q15_t)((3.44951507643e-17f)*Q15_SCALE),
    (q15_t)((0.005154145753f)*Q15_SCALE),
    (q15_t)((2.07194250284e-17f)*Q15_SCALE),
    (q15_t)((-0.00541771914366f)*Q15_SCALE),
    (q15_t)((-2.72945697189e-18f)*Q15_SCALE),
    (q15_t)((0.00570095798445f)*Q15_SCALE),
    (q15_t)((-1.71955267763e-17f)*Q15_SCALE),
    (q15_t)((-0.00600630300312f)*Q15_SCALE),
    (q15_t)((3.92868147513e-17f)*Q15_SCALE),
    (q15_t)((0.00633663074405f)*Q15_SCALE),
    (q15_t)((-6.38167584866e-17f)*Q15_SCALE),
    (q15_t)((-0.00669535504025f)*Q15_SCALE),
    (q15_t)((-6.75604331041e-18f)*Q15_SCALE),
    (q15_t)((0.00708655818136f)*Q15_SCALE),
    (q15_t)((-1.78690615209e-17f)*Q15_SCALE),
    (q15_t)((-0.00751516243728f)*Q15_SCALE),
    (q15_t)((4.5538298421e-17f)*Q15_SCALE),
    (q15_t)((0.00798715720712f)*Q15_SCALE),
    (q15_t)((-1.81670260624e-17f)*Q15_SCALE),
    (q15_t)((-0.00850990404311f)*Q15_SCALE),
    (q15_t)((-1.29335974563e-17f)*Q15_SCALE),
    (q15_t)((0.00909255258728f)*Q15_SCALE),
    (q15_t)((-1.84373318195e-17f)*Q15_SCALE),
    (q15_t)((-0.00974661751004f)*Q15_SCALE),
    (q15_t)((5.44614428226e-17f)*Q15_SCALE),
    (q15_t)((0.0104867941757f)*Q15_SCALE),
    (q15_t)((-1.86787767376e-17f)*Q15_SCALE),
    (q15_t)((-0.0113321368185f)*Q15_SCALE),
    (q15_t)((-2.31400977103e-17f)*Q15_SCALE),
    (q15_t)((0.0123078022358f)*Q15_SCALE),
    (q15_t)((-1.88902808252e-17f)*Q15_SCALE),
    (q15_t)((-0.0134477032242f)*Q15_SCALE),
    (q15_t)((6.90536551261e-17f)*Q15_SCALE),
    (q15_t)((0.0147986782553f)*Q15_SCALE),
    (q15_t)((-1.90708932363e-17f)*Q15_SCALE),
    (q15_t)((-0.0164272946195f)*Q15_SCALE),
    (q15_t)((1.91493547938e-17f)*Q15_SCALE),
    (q15_t)((0.0184314537746f)*Q15_SCALE),
    (q15_t)((-1.92197985244e-17f)*Q15_SCALE),
    (q15_t)((-0.0209612809589f)*Q15_SCALE),
    (q15_t)((1.92821445358e-17f)*Q15_SCALE),
    (q15_t)((0.0242592975046f)*Q15_SCALE),
    (q15_t)((-1.93363220204e-17f)*Q15_SCALE),
    (q15_t)((-0.0287444174731f)*Q15_SCALE),
    (q15_t)((1.93822693725e-17f)*Q15_SCALE),
    (q15_t)((0.0352079397742f)*Q15_SCALE),
    (q15_t)((-1.94199342903e-17f)*Q15_SCALE),
    (q15_t)((-0.0453455267414f)*Q15_SCALE),
    (q15_t)((1.94492738627e-17f)*Q15_SCALE),
    (q15_t)((0.063565931238f)*Q15_SCALE),
    (q15_t)((-1.94702546402e-17f)*Q15_SCALE),
    (q15_t)((-0.1060346321f)*Q15_SCALE),
    (q15_t)((1.94828526908e-17f)*Q15_SCALE),
    (q15_t)((0.318241094638f)*Q15_SCALE),
    (q15_t)((0.49991888709f)*Q15_SCALE),
    (q15_t)((0.318241094638f)*Q15_SCALE),
    (q15_t)((1.94828526908e-17f)*Q15_SCALE),
    (q15_t)((-0.1060346321f)*Q15_SCALE),
    (q15_t)((-1.94702546402e-17f)*Q15_SCALE),
    (q15_t)((0.063565931238f)*Q15_SCALE),
    (q15_t)((1.94492738627e-17f)*Q15_SCALE),
    (q15_t)((-0.0453455267414f)*Q15_SCALE),
    (q15_t)((-1.94199342903e-17f)*Q15_SCALE),
    (q15_t)((0.0352079397742f)*Q15_SCALE),
    (q15_t)((1.93822693725e-17f)*Q15_SCALE),
    (q15_t)((-0.0287444174731f)*Q15_SCALE),
    (q15_t)((-1.93363220204e-17f)*Q15_SCALE),
    (q15_t)((0.0242592975046f)*Q15_SCALE),
    (q15_t)((1.92821445358e-17f)*Q15_SCALE),
    (q15_t)((-0.0209612809589f)*Q15_SCALE),
    (q15_t)((-1.92197985244e-17f)*Q15_SCALE),
    (q15_t)((0.0184314537746f)*Q15_SCALE),
    (q15_t)((1.91493547938e-17f)*Q15_SCALE),
    (q15_t)((-0.0164272946195f)*Q15_SCALE),
    (q15_t)((-1.90708932363e-17f)*Q15_SCALE),
    (q15_t)((0.0147986782553f)*Q15_SCALE),
    (q15_t)((6.90536551261e-17f)*Q15_SCALE),
    (q15_t)((-0.0134477032242f)*Q15_SCALE),
    (q15_t)((-1.88902808252e-17f)*Q15_SCALE),
    (q15_t)((0.0123078022358f)*Q15_SCALE),
    (q15_t)((-2.31400977103e-17f)*Q15_SCALE),
    (q15_t)((-0.0113321368185f)*Q15_SCALE),
    (q15_t)((-1.86787767376e-17f)*Q15_SCALE),
    (q15_t)((0.0104867941757f)*Q15_SCALE),
    (q15_t)((5.44614428226e-17f)*Q15_SCALE),
    (q15_t)((-0.00974661751004f)*Q15_SCALE),
    (q15_t)((-1.84373318195e-17f)*Q15_SCALE),
    (q15_t)((0.00909255258728f)*Q15_SCALE),
    (q15_t)((-1.29335974563e-17f)*Q15_SCALE),
    (q15_t)((-0.00850990404311f)*Q15_SCALE),
    (q15_t)((-1.81670260624e-17f)*Q15_SCALE),
    (q15_t)((0.00798715720712f)*Q15_SCALE),
    (q15_t)((4.5538298421e-17f)*Q15_SCALE),
    (q15_t)((-0.00751516243728f)*Q15_SCALE),
    (q15_t)((-1.78690615209e-17f)*Q15_SCALE),
    (q15_t)((0.00708655818136f)*Q15_SCALE),
    (q15_t)((-6.75604331041e-18f)*Q15_SCALE),
    (q15_t)((-0.00669535504025f)*Q15_SCALE),
    (q15_t)((-6.38167584866e-17f)*Q15_SCALE),
    (q15_t)((0.00633663074405f)*Q15_SCALE),
    (q15_t)((3.92868147513e-17f)*Q15_SCALE),
    (q15_t)((-0.00600630300312f)*Q15_SCALE),
    (q15_t)((-1.71955267763e-17f)*Q15_SCALE),
    (q15_t)((0.00570095798445f)*Q15_SCALE),
    (q15_t)((-2.72945697189e-18f)*Q15_SCALE),
    (q15_t)((-0.00541771914366f)*Q15_SCALE),
    (q15_t)((2.07194250284e-17f)*Q15_SCALE),
    (q15_t)((0.005154145753f)*Q15_SCALE),
    (q15_t)((3.44951507643e-17f)*Q15_SCALE),
    (q15_t)((-0.0049081535664f)*Q15_SCALE),
    (q15_t)((-1.64284695479e-17f)*Q15_SCALE),
    (q15_t)((0.00467795218476f)*Q15_SCALE),
    (q15_t)((-6.19117577813e-21f)*Q15_SCALE),
    (q15_t)((-0.00446199515869f)*Q15_SCALE),
    (q15_t)((-4.69859988109e-17f)*Q15_SCALE),
    (q15_t)((0.00425893990565f)*Q15_SCALE),
    (q15_t)((3.05856176552e-17f)*Q15_SCALE),
    (q15_t)((-0.00406761526067f)*Q15_SCALE),
    (q15_t)((-1.55810141764e-17f)*Q15_SCALE),
    (q15_t)((0.00388699501658f)*Q15_SCALE),
    (q15_t)((1.85645323051e-18f)*Q15_SCALE),
    (q15_t)((-0.00371617620252f)*Q15_SCALE),
    (q15_t)((1.06909338338e-17f)*Q15_SCALE),
    (q15_t)((0.00355436113935f)*Q15_SCALE),
    (q15_t)((2.72525424785e-17f)*Q15_SCALE),
    (q15_t)((-0.00340084252746f)*Q15_SCALE),
    (q15_t)((-1.46673330175e-17f)*Q15_SCALE),
    (q15_t)((0.00325499098558f)*Q15_SCALE),
    (q15_t)((3.11574803813e-18f)*Q15_SCALE),
    (q15_t)((-0.00311624458314f)*Q15_SCALE),
    (q15_t)((-3.58574087564e-17f)*Q15_SCALE),
    (q15_t)((0.00298410000404f)*Q15_SCALE),
    (q15_t)((2.43227416845e-17f)*Q15_SCALE),
    (q15_t)((-0.00285810505258f)*Q15_SCALE),
    (q15_t)((-1.37022907805e-17f)*Q15_SCALE),
    (q15_t)((0.00273785227002f)*Q15_SCALE),
    (q15_t)((4.20160724911e-17f)*Q15_SCALE),
    (q15_t)((-0.00262297347435f)*Q15_SCALE),
    (q15_t)((5.03753192744e-18f)*Q15_SCALE),
    (q15_t)((0.00251313507138f)*Q15_SCALE),
    (q15_t)((2.16936517897e-17f)*Q15_SCALE),
    (q15_t)((-0.0024080340133f)*Q15_SCALE),
    (q15_t)((-4.619851825e-17f)*Q15_SCALE),
    (q15_t)((0.00230739430274f)*Q15_SCALE),
    (q15_t)((4.42250532541e-18f)*Q15_SCALE),
    (q15_t)((-0.00221096395875f)*Q15_SCALE),
    (q15_t)((-2.75696078221e-17f)*Q15_SCALE),
    (q15_t)((0.00211851237513f)*Q15_SCALE),
    (q15_t)((-1.01663539177e-17f)*Q15_SCALE),
    (q15_t)((-0.00202982801343f)*Q15_SCALE),
    (q15_t)((-1.16788482891e-17f)*Q15_SCALE),
    (q15_t)((0.00194471638253f)*Q15_SCALE),
    (q15_t)((3.17089221107e-17f)*Q15_SCALE),
    (q15_t)((-0.00186299826415f)*Q15_SCALE),
    (q15_t)((1.79126038234e-18f)*Q15_SCALE),
    (q15_t)((0.00178450815052f)*Q15_SCALE),
    (q15_t)((1.71118348079e-17f)*Q15_SCALE),
    (q15_t)((-0.00170909286535f)*Q15_SCALE),
    (q15_t)((1.31172019519e-17f)*Q15_SCALE),
    (q15_t)((0.00163661034369f)*Q15_SCALE),
    (q15_t)((4.70451280724e-18f)*Q15_SCALE),
    (q15_t)((-0.00156692855019f)*Q15_SCALE),
    (q15_t)((-2.10315168891e-17f)*Q15_SCALE),
    (q15_t)((0.00149992451773f)*Q15_SCALE),
    (q15_t)((-5.75628839712e-18f)*Q15_SCALE),
    (q15_t)((-0.00143548349167f)*Q15_SCALE),
    (q15_t)((-9.62965004313e-18f)*Q15_SCALE),
    (q15_t)((0.00137349816638f)*Q15_SCALE),
    (q15_t)((2.36953298449e-17f)*Q15_SCALE),
    (q15_t)((-0.00131386800314f)*Q15_SCALE),
    (q15_t)((3.48274574233e-21f)*Q15_SCALE),
    (q15_t)((0.0012564986195f)*Q15_SCALE),
    (q15_t)((1.32420810887e-17f)*Q15_SCALE),
    (q15_t)((-0.00120130124197f)*Q15_SCALE),
    (q15_t)((-2.53202498942e-17f)*Q15_SCALE),
    (q15_t)((0.0011481922146f)*Q15_SCALE),
    (q15_t)((4.39685726306e-18f)*Q15_SCALE),
    (q15_t)((-0.00109709255717f)*Q15_SCALE),
    (q15_t)((-1.57602505365e-17f)*Q15_SCALE),
    (q15_t)((0.00104792756753f)*Q15_SCALE),
    (q15_t)((-3.01389809235e-18f)*Q15_SCALE),
    (q15_t)((-0.00100062646319f)*Q15_SCALE),
    (q15_t)((-7.66234228415e-18f)*Q15_SCALE),
    (q15_t)((0.000955122058018f)*Q15_SCALE),
    (q15_t)((1.73711089566e-17f)*Q15_SCALE),
    (q15_t)((-0.000911350470178f)*Q15_SCALE),
    (q15_t)((-8.69600536166e-19f)*Q15_SCALE),
    (q15_t)((0.000869250858221f)*Q15_SCALE),
    (q15_t)((9.97994597253e-18f)*Q15_SCALE),
    (q15_t)((-0.000828765182296f)*Q15_SCALE),
    (q15_t)((4.76042503448e-18f)*Q15_SCALE),
    (q15_t)((0.000789837987989f)*Q15_SCALE),
    (q15_t)((3.77535780142e-18f)*Q15_SCALE),
    (q15_t)((-0.000752416210517f)*Q15_SCALE),
    (q15_t)((-1.15113913697e-17f)*Q15_SCALE),
    (q15_t)((0.00071644899725f)*Q15_SCALE),
    (q15_t)((-1.3724329261e-18f)*Q15_SCALE),
    (q15_t)((-0.000681887546796f)*Q15_SCALE),
    (q15_t)((-5.86446672966e-18f)*Q15_SCALE),
    (q15_t)((0.000648684963022f)*Q15_SCALE),
    (q15_t)((1.23971376689e-17f)*Q15_SCALE),
    (q15_t)((-0.000616796122619f)*Q15_SCALE),
    (q15_t)((-1.17659954317e-18f)*Q15_SCALE),
    (q15_t)((0.000586177554903f)*Q15_SCALE),
    (q15_t)((7.27719815871e-18f)*Q15_SCALE),
    (q15_t)((-0.00055678733274f)*Q15_SCALE),
    (q15_t)((-1.27593848401e-17f)*Q15_SCALE),
    (q15_t)((0.000528584973535f)*Q15_SCALE),
    (q15_t)((3.02604097182e-18f)*Q15_SCALE),
    (q15_t)((-0.000501531349387f)*Q15_SCALE),
    (q15_t)((-8.13584349516e-18f)*Q15_SCALE),
    (q15_t)((0.000475588605563f)*Q15_SCALE),
    (q15_t)((-4.55498590851e-19f)*Q15_SCALE),
    (q15_t)((-0.000450720086542f)*Q15_SCALE),
    (q15_t)((-4.29765820418e-18f)*Q15_SCALE),
    (q15_t)((0.000426890268948f)*Q15_SCALE),
    (q15_t)((8.54692857756e-18f)*Q15_SCALE),
    (q15_t)((-0.000404064700755f)*Q15_SCALE),
    (q15_t)((-1.23242804632e-17f)*Q15_SCALE),
    (q15_t)((0.000382209946203f)*Q15_SCALE),
    (q15_t)((-5.46482579085e-18f)*Q15_SCALE),
    (q15_t)((-0.000361293535926f)*Q15_SCALE),
    (q15_t)((1.37807644905e-18f)*Q15_SCALE),
    (q15_t)((0.000341283921809f)*Q15_SCALE),
    (q15_t)((2.27366106665e-18f)*Q15_SCALE),
    (q15_t)((-0.000322150436175f)*Q15_SCALE),
    (q15_t)((-5.51868140388e-18f)*Q15_SCALE),
    (q15_t)((0.000303863254901f)*Q15_SCALE),
    (q15_t)((8.38399860959e-18f)*Q15_SCALE),
    (q15_t)((-0.000286393364115f)*Q15_SCALE),
    (q15_t)((-1.08953894396e-17f)*Q15_SCALE),
    (q15_t)((0.000269712530155f)*Q15_SCALE),
    (q15_t)((-1.79617970274e-18f)*Q15_SCALE),
    (q15_t)((-0.000253793272488f)*Q15_SCALE),
    (q15_t)((-9.63777417463e-19f)*Q15_SCALE),
    (q15_t)((0.00023860883932f)*Q15_SCALE),
    (q15_t)((3.3990959518e-18f)*Q15_SCALE),
    (q15_t)((-0.000224133185652f)*Q15_SCALE),
    (q15_t)((-5.53246272119e-18f)*Q15_SCALE),
    (q15_t)((0.000210340953549f)*Q15_SCALE),
    (q15_t)((7.38548091936e-18f)*Q15_SCALE),
    (q15_t)((-0.000197207454397f)*Q15_SCALE),
    (q15_t)((1.87157692816e-18f)*Q15_SCALE),
    (q15_t)((0.000184708652987f)*Q15_SCALE),
    (q15_t)((1.74333346968e-19f)*Q15_SCALE),
    (q15_t)((-0.000172821153205f)*Q15_SCALE),
    (q15_t)((-1.96445867048e-18f)*Q15_SCALE),
    (q15_t)((0.000161522185194f)*Q15_SCALE),
    (q15_t)((3.51769272121e-18f)*Q15_SCALE),
    (q15_t)((-0.000150789593813f)*Q15_SCALE),
    (q15_t)((-4.85198090332e-18f)*Q15_SCALE),
    (q15_t)((0.000140601828266f)*Q15_SCALE),
    (q15_t)((-1.72962224788e-18f)*Q15_SCALE),
    (q15_t)((-0.000130937932761f)*Q15_SCALE),
    (q15_t)((2.48145361175e-19f)*Q15_SCALE),
    (q15_t)((0.000121777538073f)*Q15_SCALE),
    (q15_t)((1.03479936556e-18f)*Q15_SCALE),
    (q15_t)((-0.000113100853914f)*Q15_SCALE),
    (q15_t)((-2.13479150685e-18f)*Q15_SCALE),
    (q15_t)((0.000104888661984f)*Q15_SCALE),
    (q15_t)((3.06658687771e-18f)*Q15_SCALE),
    (q15_t)((-9.7122309627e-05f)*Q15_SCALE),
    (q15_t)((1.46506419036e-18f)*Q15_SCALE),
    (q15_t)((8.97837039859e-05f)*Q15_SCALE),
    (q15_t)((-4.23168334299e-19f)*Q15_SCALE),
    (q15_t)((-8.2855306582e-05f)*Q15_SCALE),
    (q15_t)((-4.67326997753e-19f)*Q15_SCALE),
    (q15_t)((7.63201282404e-05f)*Q15_SCALE),
    (q15_t)((1.21913331218e-18f)*Q15_SCALE),
    (q15_t)((-7.0161724288e-05f)*Q15_SCALE),
    (q15_t)((-1.84425614227e-18f)*Q15_SCALE),
    (q15_t)((6.43641899607e-05f)*Q15_SCALE),
    (q15_t)((2.35402410115e-18f)*Q15_SCALE),
    (q15_t)((-5.89121559578e-05f)*Q15_SCALE),
    (q15_t)((4.41794612832e-19f)*Q15_SCALE),
    (q15_t)((5.37907840874e-05f)*Q15_SCALE),
    (q15_t)((1.5071054717e-19f)*Q15_SCALE),
    (q15_t)((-4.89857629527e-05f)*Q15_SCALE),
    (q15_t)((-6.40484566956e-19f)*Q15_SCALE),
    (q15_t)((4.44833036296e-05f)*Q15_SCALE),
    (q15_t)((1.03720230066e-18f)*Q15_SCALE),
    (q15_t)((-4.02701352943e-05f)*Q15_SCALE),
    (q15_t)((-1.34997338414e-18f)*Q15_SCALE),
    (q15_t)((3.63335007597e-05f)*Q15_SCALE),
    (q15_t)((-3.71740664022e-19f)*Q15_SCALE),
    (q15_t)((-3.26611518857e-05f)*Q15_SCALE),
    (q15_t)((1.67619797465e-22f)*Q15_SCALE),
    (q15_t)((2.92413448301e-05f)*Q15_SCALE),
    (q15_t)((2.97638626181e-19f)*Q15_SCALE),
    (q15_t)((-2.60628351094e-05f)*Q15_SCALE),
    (q15_t)((-5.29424847243e-19f)*Q15_SCALE),
    (q15_t)((2.31148724458e-05f)*Q15_SCALE),
    (q15_t)((7.02479506235e-19f)*Q15_SCALE),
    (q15_t)((-2.03871953738e-05f)*Q15_SCALE),
    (q15_t)((-8.23659012981e-19f)*Q15_SCALE),
    (q15_t)((1.78700255872e-05f)*Q15_SCALE),
    (q15_t)((-4.91584333558e-20f)*Q15_SCALE),
    (q15_t)((-1.55540620075e-05f)*Q15_SCALE),
    (q15_t)((-1.1335936932e-19f)*Q15_SCALE),
    (q15_t)((1.34304745586e-05f)*Q15_SCALE),
    (q15_t)((2.31541525659e-19f)*Q15_SCALE),
    (q15_t)((-1.14908976331e-05f)*Q15_SCALE),
    (q15_t)((-3.11233520089e-19f)*Q15_SCALE),
    (q15_t)((9.72742324094e-06f)*Q15_SCALE),
    (q15_t)((3.57948239434e-19f)*Q15_SCALE),
    (q15_t)((-8.13259382943e-06f)*Q15_SCALE),
    (q15_t)((4.35358928254e-20f)*Q15_SCALE),
    (q15_t)((6.69939476902e-06f)*Q15_SCALE),
    (q15_t)((2.95684601069e-20f)*Q15_SCALE),
    (q15_t)((-5.42124649949e-06f)*Q15_SCALE),
    (q15_t)((-7.58413763352e-20f)*Q15_SCALE),
    (q15_t)((4.29199633356e-06f)*Q15_SCALE),
    (q15_t)((1.0003906469e-19f)*Q15_SCALE),
    (q15_t)((-3.30590991661e-06f)*Q15_SCALE),
    (q15_t)((-1.06676895337e-19f)*Q15_SCALE),
    (q15_t)((2.45766234312e-06f)*Q15_SCALE),
    (q15_t)((-1.83918644596e-20f)*Q15_SCALE),
    (q15_t)((-1.74232893178e-06f)*Q15_SCALE),
    (q15_t)((-2.8001520981e-21f)*Q15_SCALE),
    (q15_t)((1.15537566321e-06f)*Q15_SCALE),
    (q15_t)((1.15722568446e-20f)*Q15_SCALE),
    (q15_t)((-6.92649285226e-07f)*Q15_SCALE),
    (q15_t)((-1.19145374538e-20f)*Q15_SCALE),
    (q15_t)((3.50367092403e-07f)*Q15_SCALE),
    (q15_t)((7.65855757576e-21f)*Q15_SCALE),
    (q15_t)((-1.25106387805e-07f)*Q15_SCALE),
    (q15_t)((6.51722049974e-22f)*Q15_SCALE),
    (q15_t)((1.37936361473e-08f)*Q15_SCALE),
    (q15_t)((1.59011824389e-35f)*Q15_SCALE),
};

static p2fir_q15_t P2_UP_2_BL3_60dB_p2fir = {
.numTaps = P2FIR_UP_SAMPLER_TAPS_N,
.numCoeffs = P2FIR_UP_SAMPLER_COEFF_N,
.index = 0,
.pState = P2_UP_2_BL3_60dB_state,
.pCoeffs = P2_UP_2_BL3_60dB_coeff
};
#endif  //_P2FIR_UPSAMPLE_H 
