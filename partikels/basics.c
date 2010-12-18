/*
*
* Particle Engine Basics
* from Ep!c Source Game Engine
*
*/
#include <stdlib.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

#define PARTICLES 10
#define FRAME_H 10

typedef struct _pos
{
	GLfloat x,y,z;
} Epos;

typedef	 struct _Ergba
{
	float r,g,b,a;
} Ergba;

typedef	 struct _Ergb
{
	float r,g,b;
} Ergb;

typedef struct _prtkl 
{
	Epos vel,pos;
	Ergba color;
	int type;
	float life,fade;
} Eparticle;
// Prototypes
void esCreateParticle(Eparticle prtcl);
void esAssociateParticle(Eparticle prtcl,float a);
void esMvParticle(Eparticle prtcl);
void esDemoBg(float w, float h, double alpha);
void esDrawCube(Epos pos, Epos size, Ergb color[]);

float angel = 45.0f;
int rot_h = 0;

int main()
{
	int i,j,k;
	int quit=0,screen_w=1200,screen_h=990,frames=120,frame_ms;
	unsigned int lifetime = 5000,drawn_frames=0;
	double alpha=10;	
	Uint32 now,nxt_time,frame_avg_helper;
	SDL_Event event;
	Ergb cube_colors[6] = {{0.0f,0.0f,0.0f},{1.0f,1.0f,1.0f},{1.0f,0.0f,0.0f},{0.0f,1.0f,1.0f},{0.0f,0.0f,1.0f},{1.0f,0.0f,1.0f}},cube_cols[6] = {{1.0f,1.0f,0.0f},{1.0f,0.0f,1.0f},{0.8f,0.3f,0.3f},{0.8f,1.0f,0.0f},{0.5f,0.0f,1.0f},{0.8f,1.0f,1.0f}};
	Epos cube_pos = {200.0f,300.0f,0.0f}, cube_size = {100.0f,100.0f,100.0f},cube_size_2 = {500.0f,250.0f,100.0f};
	Eparticle particle[10];

	
	for(i=0; i < 10; i++)
	{
		particle[i].type=-1;
	}
	printf("Press Spacebar do Start/Stop roation\nPress Escape to exit\n");
	//scanf("%lf",&alpha);
	frame_ms=1000/((frames>5&&frames<1000)?frames:29);
	atexit(SDL_Quit);
	if( SDL_SetVideoMode( screen_w, screen_h, 32, SDL_OPENGL | SDL_HWPALETTE | SDL_GL_DOUBLEBUFFER ) == NULL )
	{
		printf("Can't set video mode: %s\n", SDL_GetError());
		exit(1);
	}
	// OpenGl Zeugs
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
		printf("Can't set OpenGL\n");
		exit(1);    
	}
	SDL_WM_SetCaption("ES - Particle System Basics","EP!C SOURCE - Partikel System Basics");
	frame_avg_helper = SDL_GetTicks()+5000;
	nxt_time = SDL_GetTicks()+frame_ms;
	while(quit==0)
	{
		while (SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT:
					quit = 1;
				break;
				case SDL_KEYDOWN:
					if(event.key.keysym.sym==SDLK_ESCAPE) quit=1;
					if(event.key.keysym.sym==SDLK_SPACE) 
					{
						rot_h = (rot_h==1)?0:1;//printf("SPACE BAR down\n");
					}
				break;
				case SDL_MOUSEBUTTONDOWN:
					if( event.button.button == SDL_BUTTON_RIGHT )
					printf("Right Mouse Btn down\n");
				break;        
			}			
		}		
		glClear( GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);		
		esDemoBg(900,600,alpha);
		
		
		for(i=0;i<14;i++)
		{
			esDrawCube((Epos){1.0f+(float)i*(float)cube_size.x+5,275.0f,25.0f}, cube_size, cube_cols);
		}
		for(i=0;i<14;i++)
		{
			esDrawCube((Epos){1.0f+(float)i*(float)cube_size.x+5,100.0f,25.0f}, cube_size, cube_cols);
		}
		for(i=0;i<14;i++)
		{
			esDrawCube((Epos){1.0f+(float)i*(float)cube_size.x+5,450.0f,25.0f}, cube_size, cube_cols);
		}
		for(i=0;i<14;i++)
		{
			esDrawCube((Epos){1.0f+(float)i*(float)cube_size.x+5,625.0f,25.0f}, cube_size, cube_cols);
		}
		for(i=0;i<14;i++)
		{
			esDrawCube((Epos){1.0f+(float)i*(float)cube_size.x+5,800.0f,25.0f}, cube_size, cube_cols);
		}
		esDrawCube((Epos){600.0f,495.0f,0.0f}, cube_size_2, cube_colors);
		
		angel = (rot_h==1)?angel+0.3f:angel;
		SDL_GL_SwapBuffers();
		drawn_frames++;
		now = SDL_GetTicks();
		if(frame_avg_helper<now)
		{
			printf("%d Frames after %.3f Seconds => fps: %.3f\n",drawn_frames,(now-frame_avg_helper+5000)/1000.0f,drawn_frames/((now-frame_avg_helper+5000)/1000.0f));
			frame_avg_helper = now+5000;
			drawn_frames=0;
		}	
		now = SDL_GetTicks();
		SDL_Delay((nxt_time<=now)?0:nxt_time-now);
		nxt_time += frame_ms;
	}
		
	SDL_Quit();
	return 0;
}

void esDemoBg(float w, float h, double alpha)
{
	//double h;
	//h = d * sin(alpha);
	
	glLoadIdentity();
	glTranslatef( 10,900,50);
	glRotatef(alpha,0.5f, 0.0f, 1.0f);
	glBegin( GL_QUADS );
       	glColor4f( 0, 0, 0, 0);
        glVertex3f(0, 0, 0);
        glColor4f( 1, 1, 1, 0);
        glVertex3f(w, 0, 0);
        glColor4f( 0, 1, 0, 0);
        glVertex3f(w, -h, 0);
        glColor4f( 0, 0, 1, 0);
        glVertex3f(-w, -h, 0);  	
	glEnd();
	glLoadIdentity();
	return;
}

void esCreateParticle(Eparticle prtcl)
{
	
	return;
}
void esAassociateParticle(float a, int type)
{
	
	return;
}
void esMvParticle(Eparticle prtcl)
{
	return;
}
void esDrawCube(Epos pos, Epos size, Ergb color[])
{
	int i=0;
	glLoadIdentity();
	glTranslatef( pos.x, pos.y, pos.z);	
	glRotatef(angel,1.0f,0.5f,0.0f);	
	glColor3f( 0.5f, 0.5f, 1.0f);
    glBegin( GL_QUADS );
	    // Top
	    glColor3f( color[i].r, color[i].g, color[i].b);
        glVertex3f(-size.x/2.0f, -size.y/2.0f, -size.z/2.0f);	// A done
		glVertex3f(-size.x/2.0f, -size.y/2.0f, size.z/2.0f); 	// E done
        glVertex3f(size.x/2.0f, -size.y/2.0f, size.z/2.0f);  	// F done
        glVertex3f(size.x/2.0f, -size.y/2.0f, -size.z/2.0f);  	// B done
        i++;
        // Bottom
       	glColor3f( color[i].r, color[i].g, color[i].b);
        glVertex3f(-size.x/2.0f, size.y/2.0f, -size.z/2.0f);  	// D done
        glVertex3f(-size.x/2.0f, size.y/2.0f, size.z/2.0f);  	// H done       
        glVertex3f(size.x/2.0f, size.y/2.0f, size.z/2.0f);  	// G done
        glVertex3f(size.x/2.0f, size.y/2.0f, -size.z/2.0f);  	// C done
        i++; 
        /// Front
       	glColor3f( color[i].r, color[i].g, color[i].b); 
        glVertex3f(-size.x/2.0f, -size.y/2.0f, -size.z/2.0f); 	// A
        glVertex3f(size.x/2.0f, -size.y/2.0f, -size.z/2.0f);  	// B
        glVertex3f(size.x/2.0f, size.y/2.0f, -size.z/2.0f);  	// C
        glVertex3f(-size.x/2.0f, size.y/2.0f, -size.z/2.0f);  	// D
        i++;
        // Back
       	glColor3f( color[i].r, color[i].g, color[i].b);
        glVertex3f(size.x/2.0f, -size.y/2.0f, size.z/2.0f);  	// F
        glVertex3f(-size.x/2.0f, -size.y/2.0f, size.z/2.0f); 	// E
        glVertex3f(-size.x/2.0f, size.y/2.0f, size.z/2.0f);  	// H
        glVertex3f(size.x/2.0f, size.y/2.0f, size.z/2.0f);  	// G
        i++;        
        // Left
       	glColor3f( color[i].r, color[i].g, color[i].b);
        glVertex3f(-size.x/2.0f, -size.y/2.0f, size.z/2.0f); 	// E
        glVertex3f(-size.x/2.0f, -size.y/2.0f, -size.z/2.0f); 	// A
        glVertex3f(-size.x/2.0f, size.y/2.0f, -size.z/2.0f);  	// D
        glVertex3f(-size.x/2.0f, size.y/2.0f, size.z/2.0f);  	// H 
        // Right
        i++;
       	glColor3f( color[i].r, color[i].g, color[i].b);
        glVertex3f(size.x/2.0f, -size.y/2.0f, -size.z/2.0f);  	// B
        glVertex3f(size.x/2.0f, -size.y/2.0f, size.z/2.0f);  	// F
        glVertex3f(size.x/2.0f, size.y/2.0f, size.z/2.0f);  	// G
        glVertex3f(size.x/2.0f, size.y/2.0f, -size.z/2.0f);  	// C
        //*/
    glEnd();
	glLoadIdentity();
	return;
}
