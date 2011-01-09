#include "../ES_bodies.h"

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

// Temporaly placed here
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
