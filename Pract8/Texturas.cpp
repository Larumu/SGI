//PRÁCTICA 8 de Introducción a los sistemas gráficos interactivos (Texturas)
//Laura Ruiz Muñoz
#define PROYECTO "Estrella de David"

#include <iostream>
#include <cmath>
#include <GL\freeglut.h>
#include <Utilidades.h> 
#include <cmath>
#include <stdlib.h>
#include <sstream> 
#include <freeimage/FreeImage.h>

static GLuint circuito, pancartadio, estrella;
GLfloat v0[3] = { 2,0,0 }, v1[3] = { -2,0,0 }, v2[3] = { -2,0,20 }, v3[3] = { 2,0,17 }, v4[3] = { 6,0,22 }, v5[3] = { 2,0,25 }, v7[3] = { 2,0,35 }, v6[3] = { 6,0,37 };
GLfloat v8[3] = { 0,0,43 }, v9[3] = { -1,0,38 }, v10[3] = { -14,0,38 }, v11[3] = { -18,0,43 }, v12[3] = { -18,0,0 }, v13[3] = { -14,0,0 }, v14[3] = { -14,0,-20 }, v15[3] = { -18,0,-17 };
GLfloat v16[3] = { -22,0,-22 }, v17[3] = { -18,0,-25 }, v18[3] = { -18,0,-35 }, v19[3] = { -22,0,-37 }, v20[3] = { -16,0,-43 }, v21[3] = { -15,0,-38 }, v22[3] = { -2,0,-38 }, v23[3] = { 2,0,-43 };
GLfloat v24[3] = { 2,0,-21 }, v25[3] = { -2,0,-19 }, v26[3] = { 0,0,-16 }, v27[3] = { 4,0,-18 }, v28[3] = { 4,0,-9 }, v29[3] = { 0,0,-11 }, v30[3] = { -2,0,-7 }, v31[3] = { 2,0,-5 };
//GLfloat v31[3]={-18, 0,50}, v32[3]={}
static float velocity = 0, grad = 0;
static float pos_x = 0, pos_z = 0, look_x = 0, look_z = 1;
static int N = 10, M = 10;
static enum { ALAMBRICO, SOLIDO, DOUBLE } modo;
GLuint tex0;
GLuint tex1, tex2;

using namespace std;



void init()
{


	circuito = glGenLists(42);
	glNewList(circuito, GL_COMPILE);

	quad(v0, v1, v2, v3, 3, 10);
	quad(v3, v2, v5, v4, 3, 10);
	quad(v4, v5, v7, v6, 3, 10);
	quad(v6, v7, v9, v8, 3, 10);
	quad(v8, v9, v10, v11, 3, 10);
	quad(v11, v10, v13, v12, 3, 10);
	quad(v12, v13, v14, v15, 3, 10);
	quad(v15, v14, v17, v16, 3, 10);
	quad(v16, v17, v18, v19, 3, 10);
	quad(v19, v18, v21, v20, 3, 10);
	quad(v20, v21, v22, v23, 3, 10);
	quad(v23, v22, v25, v24, 3, 10);
	quad(v24, v25, v26, v27, 3, 10);
	quad(v27, v26, v29, v28, 3, 10);
	quad(v28, v29, v30, v31, 3, 10);
	quad(v31, v30, v1, v0, 3, 10);
	//glColor3f(0.804, 0.522, 0.247);
	glEndList();


	glGenTextures(1, &tex0);
	glBindTexture(GL_TEXTURE_2D, tex0);
	loadImageFile("arcoiris.jpg");
	glEnable(GL_TEXTURE_2D);

	glGenTextures(1, &tex1);
	glBindTexture(GL_TEXTURE_2D, tex1);
	loadImageFile("gris.jpg");
	glEnable(GL_TEXTURE_2D);

	glGenTextures(1, &tex2);
	glBindTexture(GL_TEXTURE_2D, tex2);
	loadImageFile("konodioda.jpg");
	glEnable(GL_TEXTURE_2D);

}

void loadTexture() 
	{
	
	glGenTextures(1, &tex0);
	glBindTexture(GL_TEXTURE_2D, tex0);
	loadImageFile("arcoiris.jpg");
	glEnable(GL_TEXTURE_2D);
	
}

void display()

{
	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(pos_x, 1, pos_z, look_x, 1, look_z, 0, 1, 0);

	ejes();

	glBindTexture(GL_TEXTURE_2D, tex1);
	// b. Filtros
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	// c. Forma de combinar y repetir
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	GLfloat planoS1[] = { 0,0,0,0 };
	GLfloat planoT1[] = { -0.1,3,0,0 };
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGenfv(GL_S, GL_OBJECT_PLANE, planoS1);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGenfv(GL_T, GL_OBJECT_PLANE, planoT1);

	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(-2.0, 1.75, 10);
	glScalef(0.1, 3.5, 0.1);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(2.0, 1.75, 10);
	glScalef(0.1, 3.5, 0.1);
	glutSolidCube(1.0);
	glPopMatrix();


	glBindTexture(GL_TEXTURE_2D, tex2);
	// b. Filtros
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// c. Forma de combinar y repetir
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);


	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(-2.0, 2.0, 10);
	glScalef(4.0, 4.0, 1.0);
	//glutSolidCube(1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.0, 0.0, 0);
	glTexCoord2f(1.0, 0);
	glVertex3f(1.0, 0, 0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(1.0, 0.56, 0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0, 0.56, 0);
	glEnd();
	glPopMatrix();


	glBindTexture(GL_TEXTURE_2D, tex0);
	// b. Filtros
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	// c. Forma de combinar y repetir
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	GLfloat planoS[] = { -2,0,0,0 };
	GLfloat planoT[] = { -2,0,20,0 };
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGenfv(GL_S, GL_OBJECT_PLANE, planoS);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGenfv(GL_T, GL_OBJECT_PLANE, planoT);

	glPushMatrix();
	if (modo == SOLIDO) {
		glCallList(circuito);
		glPolygonMode(GL_FRONT, GL_FILL);
	}
	else if (modo == ALAMBRICO) {
		glCallList(circuito);
		glPolygonMode(GL_FRONT, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT, GL_LINE);
		glColor3f(0.0, 0.0, 0.0);
		glCallList(circuito);
		glPolygonMode(GL_FRONT, GL_FILL);
		glCallList(circuito);
	}
	glPopMatrix();

	


	glFlush();
	glutSwapBuffers();
}

void reshape(GLint w, GLint h)
{
	glViewport(0, 0, w, h);
	float razon = (float)w / h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, razon, 1, 30);
}

void moverVehiculo()
{
	static int horaAnterior = glutGet(GLUT_ELAPSED_TIME);
	int horaActual = glutGet(GLUT_ELAPSED_TIME);
	float tiempoTranscurrido = horaActual - horaAnterior;
	pos_x += velocity*(tiempoTranscurrido / 1000.0)*sin(grad*PI / 180.0);
	pos_z += velocity*(tiempoTranscurrido / 1000.0)*cos(grad*PI / 180.0);
	look_z = pos_z + cos(grad*PI / 180.0);
	look_x = pos_x + sin(grad*PI / 180.0);
	horaAnterior = horaActual;
}

void onSpecialKey(int key, int x, int y)
{
	stringstream cuentakms;
	switch (key)
	{
	case GLUT_KEY_UP: velocity += 0.2;
		break;
	case GLUT_KEY_LEFT: grad += 0.5;
		break;
	case GLUT_KEY_DOWN: velocity = max(0, velocity - 0.2);
		break;
	case GLUT_KEY_RIGHT: grad -= 0.5;
		break;

	}
	cuentakms << "Interfaz de conducción. SPEED " << velocity << " m/s";
	glutSetWindowTitle(cuentakms.str().c_str());
	moverVehiculo();
	glutPostRedisplay();
}
void idle()
{
	moverVehiculo();
	glutPostRedisplay();
}

void onKey(unsigned char tecla, int x, int y) {
	switch (tecla) {
	case 27:
		exit(0);
		break;
	case 's': modo = SOLIDO;
		break;
	case 'i': modo = ALAMBRICO;
		break;
	case 'o': modo = DOUBLE;
		break;
	}
	glutPostRedisplay();
}

void main(int argc, char** argv)
{
	FreeImage_Initialise();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 400);
	glutCreateWindow("Interfaz de conducción. SPEED 0 m/s");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(onSpecialKey);
	glutKeyboardFunc(onKey);
	glutIdleFunc(idle);
	glutMainLoop();
	FreeImage_DeInitialise();
}