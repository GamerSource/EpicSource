#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>


#include "ES_types.h"
#ifndef HAVE_BODIES
#include "ES_bodies.h"
#define HAVE_BODIES 1
#endif
int esInitGL(int screen_w,int screen_h);
