typedef struct _pos
{
	float x,y,z;
} Epos;

typedef struct _pos3
{
	Epos pos;
	Epos size;
	Epos rot;
	float deg;
} Epos3;
typedef	 struct _Ergba
{
	float r,g,b,a;
} Ergba;

typedef	 struct _Ergb
{
	float r,g,b;
} Ergb;

// Type definition for Particles
typedef struct _prtkl 
{
	Epos vel,pos,gravity;
	Epos rot;
	float deg;
	Ergba color;
	int type;
	float life,fade;
} Eparticle;
