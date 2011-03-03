#include "ES.h"

int esInitGL(int screen_w,int screen_h/*, int depth*/)
{
	glClearColor(0.8, 0.8, 0.8, 0 );
    glClearDepth( 1.0f );
    glEnable( GL_DEPTH_TEST );
    glDepthFunc( GL_LEQUAL );
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
    glHint( GL_POINT_SMOOTH_HINT, GL_NICEST );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho( 0, screen_w, screen_h, 0, -1000, 500 );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	if( glGetError() != GL_NO_ERROR )
	{		
		return 0;   
	}
	return 1;
}
