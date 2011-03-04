/*
*
* 	Compile all Objectfiles (ES.c;primitives/ES_bodies.c; and this file demos/particle_demos.c) like this:
*	gcc -c example.c -o o1.o
* 	
*	then make a binary:
*	gcc o1.o o2.o o3.o -o demo.bin -lGL  `sdl-config --cflags --libs`
*	(note: o1, o2, o3 must be the three objectfiles)
*	
*/

#include "../ES.h"

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
								esResetParticle(&particle[i],1);
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
		//esDemoBg(900,600,alpha);
		esDemoBg(800,500,alpha);
		for(i=0; i < PARTICLES; i++)
		{
			esDrawParticle(particle[i],PARTICLESIZE);
			esControlParticle(&particle[i]);
			esMvParticle(&particle[i]);			
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
