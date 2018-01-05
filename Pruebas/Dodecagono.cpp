
#include <Utilidades.h>
#include <iostream>
#include <sstream> 
#define N 5
#define M 5

static float posx = 0, posz = 0, vistax = 0, vistaz = -1, velocidad = 0, alfa = 32;
static GLuint tex[5];
static enum { ALAMBRICO, SOLIDO, } modo;
static bool NIEBLA, LUZ, TEXTURAS;
GLfloat niebla[3] = { 0.15, 0.1, 0.03 };
static int anuncio;
void init()
{
	printf(" Presione tecla ESC para salir \n");
	printf(" Flecha izquierda/derecha: giro del vehículo \n");
	printf(" Flecha arriba / abajo: aumento / disminución de la velocidad \n");
	printf(" S / s : Activa / desactiva un modelo simple en alámbrico de la práctica 6 sin luces ni texturas \n");
	printf(" L / l : Cambia entre modo diurno / nocturno \n");
	printf(" N / n : Cambia el estado de la niebla(on / off) \n");
	printf(" T / t: Activa o desactiva las texturas \n");
	printf("\n\n POR DEFECTO SOLIDO, SIN NIEBLA, NOCTURNO, SIN TEXTURAS \n");
	modo = SOLIDO;
	TEXTURAS = false;
	LUZ = true;
	GLfloat DF_L0[] = { 0.05, 0.05, 0.05, 1.0 };
	GLfloat SP_L0[] = { 0.0, 0.0, 0.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, DF_L0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DF_L0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, SP_L0);


	GLfloat DF_MAT[] = { 0.8, 0.8, 0.8 };
	GLfloat SP_MAT[] = { 0.3, 0.3, 0.3 };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, DF_MAT);
	glMaterialfv(GL_FRONT, GL_SPECULAR, SP_MAT);
	glMaterialf(GL_FRONT, GL_SHININESS, 3);

	GLfloat DF_L1[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat AM_L1[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat SP_L1[] = { 0.3, 0.3, 0.3, 1.0 };

	glLightfv(GL_LIGHT1, GL_AMBIENT, AM_L1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, DF_L1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, SP_L1);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 25.0);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 20.0);

	GLfloat DF_F[] = { 0.5, 0.5, 0.2, 1.0 };
	GLfloat AM_F[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat SP_F[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat dir_central[] = { 0.0, -1, 0 };
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, dir_central);
	glLightfv(GL_LIGHT2, GL_AMBIENT, AM_F);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, DF_F);
	glLightfv(GL_LIGHT2, GL_SPECULAR, SP_F);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 45.0);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 10.0);

	glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, dir_central);
	glLightfv(GL_LIGHT3, GL_AMBIENT, AM_F);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, DF_F);
	glLightfv(GL_LIGHT3, GL_SPECULAR, SP_F);
	glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 45.0);
	glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 10.0);
	glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, dir_central);
	glLightfv(GL_LIGHT4, GL_AMBIENT, AM_F);
	glLightfv(GL_LIGHT4, GL_DIFFUSE, DF_F);
	glLightfv(GL_LIGHT4, GL_SPECULAR, SP_F);
	glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, 45.0);
	glLightf(GL_LIGHT4, GL_SPOT_EXPONENT, 10.0);
	glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, dir_central);
	glLightfv(GL_LIGHT5, GL_AMBIENT, AM_F);
	glLightfv(GL_LIGHT5, GL_DIFFUSE, DF_F);
	glLightfv(GL_LIGHT5, GL_SPECULAR, SP_F);
	glLightf(GL_LIGHT5, GL_SPOT_CUTOFF, 45.0);
	glLightf(GL_LIGHT5, GL_SPOT_EXPONENT, 10.0);

	glEnable(GL_NORMALIZE);
	glGenTextures(5, tex);
	glBindTexture(GL_TEXTURE_2D, tex[0]);
	loadImageFile("77.jpg");

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);


	glBindTexture(GL_TEXTURE_2D, tex[1]);
	loadImageFile("carretera.jpg");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, tex[2]);
	loadImageFile("anuncio2.jpg");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, tex[3]);
	loadImageFile("blanco.jpg");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, tex[4]);
	loadImageFile("peligro.jpg");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);


}


void reshape(GLint w, GLint h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float razon = (float)w / h;
	gluPerspective(120, razon, 0.0001, 40);
}

void circuito()
{
	glPushMatrix();

	glBindTexture(GL_TEXTURE_2D, tex[0]);
	glBegin(GL_QUAD_STRIP);
	float alfa = 2 * PI / 10.0;
	for (int i = 0; i <= 20; i++) {
		float ex = posx + 35 * sin(i*alfa);
		float ez = posz + 35 * cos(i*alfa);
		glTexCoord2f(i*alfa / (2.0*PI), 0);
		glVertex3f(ex, -75, ez);
		glTexCoord2f(i*alfa / (2.0*PI), 1);
		glVertex3f(ex, 75, ez);

	}
	glEnd();
	float startz = 10 + (int)posz - (int)posz % 10;
	float x = 5 * sin((posz)* PI / 25);
	float tx = ((PI / 5) * cos((posz)* PI / 25));
	float v0[3] = { x - 2,0,startz + tx * 2 };
	float v1[3] = { x + 2,0,startz - tx * 2 };

	for (int i = 1; i <= 50; i++) {
		x = 5 * sin((startz - i) * PI / 25);
		tx = ((PI / 5) * cos((startz - i) * PI / 25));

		float v3[3] = { x - 2,0,startz - i + tx * 2 };
		float v2[3] = { x + 2,0,startz - i - tx * 2 };
		glBindTexture(GL_TEXTURE_2D, tex[1]);
		quad(v0, v1, v2, v3, N, M);

		if (((int)startz - i) % 20 == 0) {
			float a0[3] = { x - 2.5,4,startz - i };
			float a1[3] = { x + 2.5,4,startz - i };
			float a3[3] = { x - 2.5,8,startz - i };
			float a2[3] = { x + 2.5,8,startz - i };
			glBindTexture(GL_TEXTURE_2D, tex[2]);
			quad(a0, a1, a2, a3, N, M);
			float b0[3] = { x - 0.1,0,startz - i };
			float b1[3] = { x + 0.1,0,startz - i };
			float b3[3] = { x - 0.1,4,startz - i };
			float b2[3] = { x + 0.1,4,startz - i };
			glBindTexture(GL_TEXTURE_2D, tex[3]);
			quad(b0, b1, b2, b3, N, M);
		}
		if (((int)startz - i) % 10 == 0) {
			float a0[3] = { x - 2.5,4,startz - i };
			float a1[3] = { x + 2.5,4,startz - i };
			float a3[3] = { x - 2.5,8,startz - i };
			float a2[3] = { x + 2.5,8,startz - i };
			glBindTexture(GL_TEXTURE_2D, tex[4]);
			quad(a0, a1, a2, a3, N, M);
			float b0[3] = { x - 0.1,0,startz - i };
			float b1[3] = { x + 0.1,0,startz - i };
			float b3[3] = { x - 0.1,4,startz - i };
			float b2[3] = { x + 0.1,4,startz - i };
			glBindTexture(GL_TEXTURE_2D, tex[3]);
			quad(b0, b1, b2, b3, N, M);
		}
		v0[0] = v3[0];
		v0[2] = v3[2];
		v1[0] = v2[0];
		v1[2] = v2[2];
	}
	glPopMatrix();
}

void farolas() {
	float x;
	float startz = 10 + (int)posz - (int)posz % 10;
	int luz = 0;
	for (int i = 0; i<4; i++) {
		x = 5 * sin((startz - 10 * i) * PI / 25);
		GLfloat POS[] = { x, 4, startz - 10 * i, 1.0 };
		switch (luz) {
		case 0:
			glLightfv(GL_LIGHT2, GL_POSITION, POS);
			glEnable(GL_LIGHT2);
			break;
		case 1:
			glLightfv(GL_LIGHT3, GL_POSITION, POS);
			glEnable(GL_LIGHT3);
			break;
		case 2:
			glLightfv(GL_LIGHT4, GL_POSITION, POS);
			glEnable(GL_LIGHT4);
			break;
		case 3:
			glLightfv(GL_LIGHT5, GL_POSITION, POS);
			glEnable(GL_LIGHT5);
			break;
		}
		luz++;

	}
}

void display()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0, 1.0, 1.0, 0.5);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	GLfloat dir_central[] = { 0.0, -0.5, -0.7 };
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, dir_central);
	gluLookAt(posx, 1, posz, vistax, 1, vistaz, 0, 1, 0);
	GLfloat POS_L0[] = { 0.0, 10, 0.0, 0 };
	glLightfv(GL_LIGHT0, GL_POSITION, POS_L0);
	GLfloat POS_L1[] = { posx, 0.7, posz, 1.0 };
	glLightfv(GL_LIGHT1, GL_POSITION, POS_L1);


	if (LUZ) {
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		glEnable(GL_LIGHTING);
		farolas();
	}
	if (!LUZ) {
		glDisable(GL_LIGHTING);
	}
	if (TEXTURAS) {
		glEnable(GL_TEXTURE_2D);
		circuito();
		farolas();
	}
	if (!TEXTURAS) {
		glDisable(GL_TEXTURE_2D);
		circuito();
		farolas();
	}
	if (NIEBLA) {
		glEnable(GL_FOG);
		glFogfv(GL_FOG_COLOR, niebla);
		glFogf(GL_FOG_DENSITY, 0.2);
	}
	if (!NIEBLA) {
		glDisable(GL_FOG);
	}
	if (modo == SOLIDO) {
		glEnable(GL_TEXTURE_2D);
		glPolygonMode(GL_FRONT, GL_FILL);
		circuito();
		farolas();
	}
	else if (modo == ALAMBRICO) {
		glDisable(GL_TEXTURE_2D);
		glPolygonMode(GL_FRONT, GL_LINE);
		circuito();
		farolas();
	}
	glutSwapBuffers();

}

void mover() {
	static int hora_anterior = glutGet(GLUT_ELAPSED_TIME);
	int hora_actual = glutGet(GLUT_ELAPSED_TIME);
	float tiempo_transcurrido = hora_actual - hora_anterior;
	posx -= velocidad * (tiempo_transcurrido / 1000.0) * sin(alfa * PI / 180.0);
	posz -= velocidad * (tiempo_transcurrido / 1000.0) * cos(alfa * PI / 180.0);
	vistaz = posz - cos(alfa * PI / 180.0);
	vistax = posx - sin(alfa * PI / 180.0);
	hora_anterior = hora_actual;
}

void onSpecialKey(int tecla, int x, int y)
{

	switch (tecla) {
	case GLUT_KEY_LEFT:
		alfa += 0.5;
		break;
	case GLUT_KEY_RIGHT:
		alfa -= 0.5;
		break;
	case GLUT_KEY_UP:
		velocidad += 0.1;
		break;
	case GLUT_KEY_DOWN:
		velocidad = max(0, velocidad - 0.1);
		break;
	}
	stringstream titulo;
	titulo << "Videojuego. SPEED " << velocidad << " m/s";
	glutSetWindowTitle(titulo.str().c_str());
	mover();
	glutPostRedisplay();
}
void onKey(unsigned char tecla, int x, int y) {
	switch (tecla) {
	case 27: exit(0);
	case 'S': modo = SOLIDO;
		break;
	case 's': modo = ALAMBRICO;
		break;
	case 'N': NIEBLA = true;
		break;
	case 'n': NIEBLA = false;
		break;
	case 'L': LUZ = true;
		break;
	case 'l': LUZ = false;
		break;
	case 'T': TEXTURAS = true;
		break;
	case 't': TEXTURAS = false;
		break;
	}
	glutPostRedisplay();
}

void idle() {
	mover();
	glutPostRedisplay();
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(650, 168);
	glutInitWindowSize(500, 500);
	glutCreateWindow("videojuego. SPEED 0 m/s");

	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(onSpecialKey);
	glutIdleFunc(idle);
	glutKeyboardFunc(onKey);


	glutMainLoop();
	FreeImage_DeInitialise();

}glClear(GL_DEPTH_BUFFER_BIT);
gluLookAt(0, 0, 0, 0, 0, 1, 0, 1, 0);

glPushMatrix();

glBegin(GL_POLYGON);
glVertex3f(1.0, 0.0, 5.0);
glVertex3f(1.5, 0.0, 5.0);
glVertex3f(1.5, 2.0, 5.0);
glVertex3f(1.0, 2.0, 5.0);
glEnd();
glPopMatrix();
