#include "../ES_particle.h"

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
	prtcl->vel.x = (rnd_flag)?(-1000+(rand()%2001))/1000.0f:0.0f;
	prtcl->vel.y = (rnd_flag)?(-1000+(rand()%2001))/1000.0f:0.0f;
	prtcl->vel.z = (rnd_flag)?(-30+(rand()%61))/1000.0f:0.0f;
	prtcl->pos.x = 300.0f;//(rnd_flag)?(float)(595+rand()%11):0.0f;
	prtcl->pos.y = 250.0f; // (rnd_flag)?(float)(rand()%990):0.0f;
	prtcl->pos.z = (rnd_flag)?(float)(rand()%50):0.0f;
	prtcl->gravity.x = 0.0f; //(rnd_flag)?(-50+(rand()%101))/10000.0f:0.0f;
	prtcl->gravity.y = 0.004f ;//(rnd_flag)?(-50+(rand()%101))/10000.0f:0.0f;
	prtcl->gravity.z = 0.0f; //(rnd_flag)?(-50+(rand()%101))/10000.0f:0.0f;
	prtcl->rot.x = (rnd_flag)?(-50+(rand()%101))/100.0f:0.0f;
	prtcl->rot.y = (rnd_flag)?(-50+(rand()%101))/100.0f:0.0f;
	prtcl->rot.z = (rnd_flag)?(-50+(rand()%101))/100.0f:0.0f;
	prtcl->deg = 0.0f;//(rnd_flag)?(-500+(rand()%101))/10:0.0f;;
	prtcl->type = 1;
	prtcl->life = (rnd_flag)?(0.1f+(rand()%101))/1000.0f:0.0f;
	prtcl->fade = 0.0000f;//+(rnd_flag)?((rand()%11))/1000.0f:0.0f;
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

