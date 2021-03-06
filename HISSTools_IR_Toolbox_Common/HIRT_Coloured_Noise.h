
#ifndef __HIRT_COLOURED_NOISE__
#define __HIRT_COLOURED_NOISE__

#include <AH_Math.h>
#include <AH_Types.h>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////// Mode Enum ////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


typedef enum {

    NOISE_MODE_WHITE = 0,
    NOISE_MODE_BROWN = 1,
    NOISE_MODE_PINK = 2,

} t_noise_mode;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////// Noise and XORShift Structures  ////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


typedef struct _xorshift
{
    AH_UInt32 w;
    AH_UInt32 x;
    AH_UInt32 y;
    AH_UInt32 z;

} t_xorshift;


typedef struct noise_params
{
    double prev_output;
    double alpha;

    double alpha0;
    double alpha1;
    double alpha2;
    double alpha3;
    double alpha4;

    double b0;
    double b1;
    double b2;
    double b3;
    double b4;
    double b5;
    double b6;

    double amp;
    double sample_rate;

    double fade_in;
    double fade_out;
    double RT;

    t_noise_mode mode;
    t_xorshift gen;
    AH_UIntPtr T;

} t_noise_params;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////// Get Length  //////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


static __inline AH_UIntPtr coloured_noise_get_length (t_noise_params *x)
{
    return x->T;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////// Function Prototypes ///////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void coloured_noise_params(t_noise_params *x, t_noise_mode mode, double fade_in, double fade_out, double length, double sample_rate, double amp);
void coloured_noise_reset(t_noise_params *x);

void coloured_noise_gen_float(t_noise_params *x, float *out, AH_UIntPtr startN, AH_UIntPtr N);
void coloured_noise_gen_double(t_noise_params *x, double *out, AH_UIntPtr startN, AH_UIntPtr N);

void coloured_noise_gen_block(t_noise_params *x, void *out, AH_UIntPtr startN, AH_UIntPtr N, AH_Boolean double_precision);
void coloured_noise_gen(t_noise_params *x, void *out, AH_Boolean double_precision);

void coloured_noise_measure(t_noise_params *x, AH_UIntPtr N, double *max_out_pink, double *max_out_brown);


#endif    /* __HIRT_COLOURED_NOISE__ */
