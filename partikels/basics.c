/*
*
* Particle Engine Basics
* from Ep!c Source Game Engine
*
*/

#include "../basics.h"


int rot_h = 0;

int main()
{
	srand(time(NULL));
	int i,j,k;
	int quit=0,pause=0,screen_w=1200,screen_h=990,frames=125,frame_ms;
	unsigned int lifetime = 5000,drawn_frames=0;
	float rot_per_frame = 0.3f;
	double alpha=10;	
	Uint32 now,nxt_time,frame_avg_helper;
	SDL_Event event;
	Ergb cube_colors[6] = {{0.0f,0.0f,0.0f},{1.0f,1.0f,1.0f},{1.0f,0.0f,0.0f},{0.0f,1.0f,1.0f},{0.0f,0.0f,1.0f},{1.0f,0.0f,1.0f}};
	Epos3  cube ={600.0f,495.0f,-80.0f, 250.0f,250.0f,250.0f, 1.0f,0.0f,1.0f, 0.0f};
	Eparticle particle[PARTICLES];

	
	for(i=0; i < PARTICLES; i++)
	{
		esResetParticle(&particle[i],1);
	}
	printf("# © 2010 GamerSource\n# http://gamer-source.org/ep!c\n");
	printf("\n>> Press spacebar do start/stop cube roation\n>> Click right mouse button to speed up cube rotation\n>> Click left mouse button to speed down cube rotation\n>> Press return (OK) to reset particles\n>> Press p to pause everything\n>> Press escape to exit\n\nTrying to get %d fps stable...\n",frames);
	frame_ms=(int)1000/((frames>5&&frames<1000)?frames:29);
	atexit(SDL_Quit);
	if( SDL_SetVideoMode( screen_w, screen_h, 32, SDL_OPENGL | SDL_HWPALETTE | SDL_GL_DOUBLEBUFFER ) == NULL )
	{
		printf("Can't set video mode: %s\n", SDL_GetError());
		exit(1);
	}
	if(esInitGL(screen_w,screen_h)!=1)
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
					if(event.key.keysym.sym==SDLK_RETURN) 
					{
							for(i=0; i < PARTICLES; i++)
							{
								esResetParticle(&particle[i],PARTICLESIZE);
							}
					}
					if(event.key.keysym.sym==SDLK_p)
						pause = (pause)?0:1;
					if(event.key.keysym.sym==SDLK_d)
						esDebugParticle(*particle);
				break;
				case SDL_MOUSEBUTTONDOWN:
					if( event.button.button == SDL_BUTTON_RIGHT )
						rot_per_frame += 0.05f;
					if( event.button.button == SDL_BUTTON_LEFT )
						rot_per_frame -= 0.05f;
				break;        
			}			
		}
		if(pause)
		{
			now = SDL_GetTicks();
			SDL_Delay((nxt_time<=now)?0:nxt_time-now);
			nxt_time += frame_ms;
			continue;
		}		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		
		esDemoBg(900,600,alpha);
		
		for(i=0; i < PARTICLES; i++)
		{
			esDrawParticle(particle[i],2);
			esMvParticle(&particle[i]);
			esControlParticle(&particle[i]);
		}
		
		esDrawCube(cube, cube_colors);		
		cube.deg = (rot_h==1)?cube.deg+rot_per_frame:cube.deg;
		
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
// Particle Functions
void esControlParticle(Eparticle *prtcl)
{
	prtcl->life -= prtcl->fade;
	if(prtcl->life<=0.0f)
		esResetParticle(prtcl,1);
	return;
}
// Reset Paricles to zero or a random value
void esResetParticle(Eparticle *prtcl,int rnd_flag)
{
	prtcl->vel.x = (rnd_flag)?(-400+(rand()%801))/1000.0f:0.0f;
	prtcl->vel.y = (rnd_flag)?(-1500+(rand()%1501))/1500.0f:0.0f;
	prtcl->vel.z = (rnd_flag)?(-30+(rand()%61))/1000.0f:0.0f;
	prtcl->pos.x = (rnd_flag)?(float)(550+rand()%101):0.0f;
	prtcl->pos.y = 350.0f; // (rnd_flag)?(float)(rand()%990):0.0f;
	prtcl->pos.z = (rnd_flag)?(float)(rand()%50):0.0f;
	prtcl->gravity.x = 0.0f; //(rnd_flag)?(-50+(rand()%101))/10000.0f:0.0f;
	prtcl->gravity.y = 0.0009f ;//(rnd_flag)?(-50+(rand()%101))/10000.0f:0.0f;
	prtcl->gravity.z = 0.0f; //(rnd_flag)?(-50+(rand()%101))/10000.0f:0.0f;
	prtcl->rot.x = (rnd_flag)?(-50+(rand()%101))/100.0f:0.0f;
	prtcl->rot.y = (rnd_flag)?(-50+(rand()%101))/100.0f:0.0f;
	prtcl->rot.z = (rnd_flag)?(-50+(rand()%101))/100.0f:0.0f;
	prtcl->deg = //(rnd_flag)?(-50+(rand()%110))/10:0.0f;;
	prtcl->type = 1;
	prtcl->life = (rnd_flag)?(0.1f+(rand()%101))/1000.0f:0.0f;
	prtcl->fade = 0.0003f;//+(rnd_flag)?((rand()%11))/1000.0f:0.0f;
	prtcl->color.r = (rnd_flag)?(-100+(rand()%200))/100.0f:0.0f;
	prtcl->color.g = (rnd_flag)?(-100+(rand()%200))/100.0f:0.0f;
	prtcl->color.b = (rnd_flag)?(-100+(rand()%200))/100.0f:0.0f;
	prtcl->color.a = 1.0f;
	return;
}
// Switche the type of a particle and draws it
void esDrawParticle(Eparticle prtcl,float a)
{
	switch(prtcl.type)
	{
	#ifdef DEBUG
		case 0:
		{
			printf("\nEP!C DEBUG: Virtual Particle won't become real...\n");
		break;
		}
	#endif
		case 1: // Draw a Square for each Particle
		{
			esDrawSquare((Epos3){prtcl.pos.x,prtcl.pos.y,prtcl.pos.z, a,a,a, prtcl.rot.x,prtcl.rot.y,prtcl.rot.z, prtcl.deg,},prtcl.color);//28;134;238
			break;
		}
		case 2: // Draw a Cube for each Particle
		{
			esDrawCube((Epos3){prtcl.pos.x,prtcl.pos.y,prtcl.pos.z, a,a,a, prtcl.rot.x,prtcl.rot.y,prtcl.rot.z, prtcl.deg,},(Ergb[6]){(Ergb){0.5f,0.5f,0.5f},(Ergb){0.6f,0.6f,0.6f},(Ergb){0.7f,0.7f,0.7f},(Ergb){0.5f,0.5f,0.5f},(Ergb){0.6f,0.6f,0.6f},(Ergb){0.7f,0.7f,0.7f}});
			break;
		}
	}
	return;
}
// Moves the particle 
void esMvParticle(Eparticle *prtcl)
{
	if(prtcl->pos.x+prtcl->vel.x<2.0f||prtcl->pos.x+prtcl->vel.x>1198.0f)
	{
		prtcl->vel.x = -prtcl->vel.x;		
	}
	else
	{
		prtcl->pos.x += prtcl->vel.x;
		prtcl->vel.x += prtcl->gravity.x;
	}
	if(prtcl->pos.y+prtcl->vel.y<=2.0f||prtcl->pos.y+prtcl->vel.y>988.0f)
	{
		prtcl->vel.y = -prtcl->vel.y*0.3f;
		if(prtcl->pos.y+prtcl->vel.y<=2.0f)prtcl->vel.x = -prtcl->vel.x;
		if(prtcl->vel.y>=0.0f&&prtcl->pos.y+prtcl->vel.y>988.0f) prtcl->vel.x = 0.0f;	
	}
	else
	{
		prtcl->pos.y += prtcl->vel.y;
		prtcl->vel.y += prtcl->gravity.y;
	}
	if(prtcl->pos.z+prtcl->vel.z<-100.0f||prtcl->pos.z+prtcl->vel.z>999.0f)
	{
		prtcl->vel.z = 0.0f;		
	}
	else
	{
		prtcl->pos.z += prtcl->vel.z;
		prtcl->vel.z += prtcl->gravity.z;
	}
	return;
}

void esDebugParticle(Eparticle prtcl)
{
	printf("\n############*- DEBUG PENGUIN -*############\n");
	printf("> Position:\n\tx: %f\n\ty: %f\n\tz: %f\n",prtcl.pos.x,prtcl.pos.y,prtcl.pos.z);
	printf("> Velocity:\n\tx: %f\n\ty: %f\n\tz: %f\n",prtcl.vel.x,prtcl.vel.y,prtcl.vel.z);
	printf("> Gravity:\n\tx: %f\n\ty: %f\n\tz: %f\n",prtcl.gravity.x,prtcl.gravity.y,prtcl.gravity.z);
	printf("> Rotation:\n\tx: %f\n\ty: %f\n\tz: %f\n\tDegree: %f\n",prtcl.rot.x,prtcl.rot.y,prtcl.rot.z,prtcl.deg);
	printf("-------\n> Color:\n\tr: %f\n\tg: %f\n\tb: %f\n\ta: %f\n",prtcl.color.r,prtcl.color.g,prtcl.color.b,prtcl.color.a);
	printf("-------\n> Type: %d\nLife:\n\t-time: %f\n\t-fade: %f",prtcl.type,prtcl.life,prtcl.fade);
	printf("\n############+- DEBUG PENGUIN -+############\n");
	return;
}

// Non Particle Functions
void esDrawCube(Epos3 data, Ergb color[])
{
	int i=0;
	glLoadIdentity();
	glTranslatef(data.pos.x, data.pos.y, data.pos.z);	
	glRotatef(data.deg,data.rot.x,data.rot.y,data.rot.z);
    glBegin(GL_QUADS);
		// Top
		glColor3f( color[i].r, color[i].g, color[i].b);
		glVertex3f(-data.size.x/2.0f, -data.size.y/2.0f, -data.size.z/2.0f);	// A done
		glVertex3f(-data.size.x/2.0f, -data.size.y/2.0f, data.size.z/2.0f); 	// E done
		glVertex3f(data.size.x/2.0f, -data.size.y/2.0f, data.size.z/2.0f);  	// F done
		glVertex3f(data.size.x/2.0f, -data.size.y/2.0f, -data.size.z/2.0f);  	// B done
		i++;
		// Bottom
		glColor3f( color[i].r, color[i].g, color[i].b);
		glVertex3f(-data.size.x/2.0f, data.size.y/2.0f, -data.size.z/2.0f);  	// D done
		glVertex3f(-data.size.x/2.0f, data.size.y/2.0f, data.size.z/2.0f);  	// H done       
		glVertex3f(data.size.x/2.0f, data.size.y/2.0f, data.size.z/2.0f);  		// G done
		glVertex3f(data.size.x/2.0f, data.size.y/2.0f, -data.size.z/2.0f);  	// C done
		i++; 
		/// Front
		glColor3f( color[i].r, color[i].g, color[i].b); 
		glVertex3f(-data.size.x/2.0f, -data.size.y/2.0f, -data.size.z/2.0f); 	// A
		glVertex3f(data.size.x/2.0f, -data.size.y/2.0f, -data.size.z/2.0f);  	// B
		glVertex3f(data.size.x/2.0f, data.size.y/2.0f, -data.size.z/2.0f);  	// C
		glVertex3f(-data.size.x/2.0f, data.size.y/2.0f, -data.size.z/2.0f);  	// D
		i++;
		// Back
		glColor3f( color[i].r, color[i].g, color[i].b);
		glVertex3f(data.size.x/2.0f, -data.size.y/2.0f, data.size.z/2.0f);  	// F
		glVertex3f(-data.size.x/2.0f, -data.size.y/2.0f, data.size.z/2.0f); 	// E
		glVertex3f(-data.size.x/2.0f, data.size.y/2.0f, data.size.z/2.0f);  	// H
		glVertex3f(data.size.x/2.0f, data.size.y/2.0f, data.size.z/2.0f);  		// G
		i++;        
		// Left
		glColor3f( color[i].r, color[i].g, color[i].b);
		glVertex3f(-data.size.x/2.0f, -data.size.y/2.0f, data.size.z/2.0f); 	// E
		glVertex3f(-data.size.x/2.0f, -data.size.y/2.0f, -data.size.z/2.0f); 	// A
		glVertex3f(-data.size.x/2.0f, data.size.y/2.0f, -data.size.z/2.0f);  	// D
		glVertex3f(-data.size.x/2.0f, data.size.y/2.0f, data.size.z/2.0f);  	// H 
		// Right
		i++;
		glColor3f( color[i].r, color[i].g, color[i].b);
		glVertex3f(data.size.x/2.0f, -data.size.y/2.0f, -data.size.z/2.0f);  	// B
		glVertex3f(data.size.x/2.0f, -data.size.y/2.0f, data.size.z/2.0f);  	// F
		glVertex3f(data.size.x/2.0f, data.size.y/2.0f, data.size.z/2.0f);  		// G
		glVertex3f(data.size.x/2.0f, data.size.y/2.0f, -data.size.z/2.0f);  	// C
    glEnd();
	glLoadIdentity();
	return;
}
void esDrawSquare(Epos3 data, Ergba color)
{
	glLoadIdentity();
	glTranslatef(data.pos.x, data.pos.y, data.pos.z);
	glRotatef(data.deg,data.rot.x,data.rot.y,data.rot.z);
	glColor4f( color.r, color.g, color.b, color.a);
    glBegin( GL_QUADS );		
		glVertex3f(-data.size.x/2.0f, -data.size.y/2.0f, 0.0f);
		glVertex3f(data.size.x/2.0f, -data.size.y/2.0f, 0.0f);
		glVertex3f(data.size.x/2.0f, data.size.y/2.0f, 0.0f);
		glVertex3f(-data.size.x/2.0f,data.size.y/2.0f, 0.0f);		
    glEnd();
	glLoadIdentity();
	return;
}
void esDemoBg(float w, float h, double alpha)
{	
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

int esInitGL(int screen_w,int screen_h)
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
