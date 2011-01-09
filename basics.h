#include "ES.h"

#define DEBUG 1
#define PARTICLES 5000
#define FRAME_H 10
#define PARTICLESIZE 1



// Prototypes
void esResetParticle(Eparticle *prtcl,int rnd_flag);
void esDrawParticle(Eparticle prtcl,float a);
void esMvParticle(Eparticle *prtcl);
void esControlParticle(Eparticle *prtcl);
void esDebugParticle(Eparticle prtcl);
