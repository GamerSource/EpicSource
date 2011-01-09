#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

#ifndef HAVE_TYPES
#include "ES_types.h"
#define HAVE_TYPES 1
#endif
#ifndef HAVE_BODIES
#include "ES_bodies.h"
#define HAVE_BODIES 1
#endif
int esInitGL(int screen_w,int screen_h);
