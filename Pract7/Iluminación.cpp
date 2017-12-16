//PRÁCTICA 6 
//Laura Ruiz Muñoz
#define PROYECTO "Estrella de David"

#include <iostream>
#include <cmath>
#include <gl\freeglut.h>
#include <Utilidades.h>
#include <cmath>
#include <stdlib.h>
#include <sstream> 


static GLuint circuito;
GLfloat v0[3] = { 2,0,0 }, v1[3] = { -2,0,0 }, v2[3] = { -2,0,20 }, v3[3] = { 2,0,17 }, v4[3] = { 6,0,22 }, v5[3] = { 2,0,25 }, v7[3] = { 2,0,35 }, v6[3] = { 6,0,37 };
GLfloat v8[3] = { 0,0,43 }, v9[3] = { -1,0,38 }, v10[3] = { -14,0,38 }, v11[3] = { -18,0,43 }, v12[3] = { -18,0,0 }, v13[3] = { -14,0,0 }, v14[3] = { -14,0,-20 }, v15[3] = { -18,0,-17 };
GLfloat v16[3] = { -22,0,-22 }, v17[3] = { -18,0,-25 }, v18[3] = { -18,0,-35 }, v19[3] = { -22,0,-37 }, v20[3] = { -16,0,-43 }, v21[3] = { -15,0,-38 }, v22[3] = { -2,0,-38 }, v23[3] = { 2,0,-43 };
GLfloat v24[3] = { 2,0,-21 }, v25[3] = { -2,0,-19 }, v26[3] = { 0,0,-16 }, v27[3] = { 4,0,-18 }, v28[3] = { 4,0,-9 }, v29[3] = { 0,0,-11 }, v30[3] = { -2,0,-7 }, v31[3] = { 2,0,-5 };
static float velocity = 0, grad = 0;
static float pos_x = 0, pos_z = 0, look_x = 0, look_z = 1;
static int N = 10, M = 10;
static enum { ALAMBRICO, SOLIDO, DOUBLE } modo;
static float coef[16];

using namespace std;

void init()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	circuito = glGenLists(42);
	glNewList(circuito, GL_COMPILE);

	quad(v0, v1, v2, v3, 30, 30);
	quad(v3, v2, v5, v4, 30, 30);
	quad(v4, v5, v7, v6, 30, 30);
	quad(v6, v7, v9, v8, 30, 30);
	quad(v8, v9, v10, v11, 30, 30);
	quad(v11, v10, v13, v12, 30, 30);
	quad(v12, v13, v14, v15, 30, 30);
	quad(v15, v14, v17, v16, 30, 30);
	quad(v16, v17, v18, v19, 30, 30);
	quad(v19, v18, v21, v20, 30, 30);
	quad(v20, v21, v22, v23, 30, 30);
	quad(v23, v22, v25, v24, 30, 30);
	quad(v24, v25, v26, v27, 30, 30);
	quad(v27, v26, v29, v28, 30, 30);
	quad(v28, v29, v30, v31, 30, 30);
	quad(v31, v30, v1, v0, 30, 30);
	glEndList();

	glGetFloatv(GL_MODELVIEW_MATRIX, coef);

	GLfloat Al0[] = { 0.05,0.05,0.05,1.0 };
	GLfloat Dl0[] = { 0.05,0.05,0.05,1.0 };
	GLfloat Sl0[] = { 0.0,0.0,0.0,1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, Al0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Dl0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, Sl0);
	glEnable(GL_LIGHT0);

	GLfloat Al1[] = { 0.2,0.2,0.2,1.0 };
	GLfloat Dl1[] = { 1.0,1.0,1.0,1.0 };
	GLfloat Sl1[] = { 0.3,0.3,0.3,1.0 };
	glLightfv(GL_LIGHT1, GL_AMBIENT, Al1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Dl1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, Sl1);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 25);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 20);
	glEnable(GL_LIGHT1);

	GLfloat Al2[] = { 0.0,0.0,0.0,1.0 };
	GLfloat Dl2[] = { 0.5,0.5,0.2,1.0 };
	GLfloat Sl2[] = { 0.0,0.0,0.0,1.0 };
	glLightfv(GL_LIGHT2, GL_AMBIENT, Al2);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, Dl2);
	glLightfv(GL_LIGHT2, GL_SPECULAR, Sl2);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 45);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 10);
	glEnable(GL_LIGHT2);

	glLightfv(GL_LIGHT3, GL_AMBIENT, Al2);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, Dl2);
	glLightfv(GL_LIGHT3, GL_SPECULAR, Sl2);
	glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 45);
	glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 10);
	glEnable(GL_LIGHT3);

	glLightfv(GL_LIGHT4, GL_AMBIENT, Al2);
	glLightfv(GL_LIGHT4, GL_DIFFUSE, Dl2);
	glLightfv(GL_LIGHT4, GL_SPECULAR, Sl2);
	glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, 45);
	glLightf(GL_LIGHT4, GL_SPOT_EXPONENT, 10);
	glEnable(GL_LIGHT4);

	glLightfv(GL_LIGHT5, GL_AMBIENT, Al2);
	glLightfv(GL_LIGHT5, GL_DIFFUSE, Dl2);
	glLightfv(GL_LIGHT5, GL_SPECULAR, Sl2);
	glLightf(GL_LIGHT5, GL_SPOT_CUTOFF, 45);
	glLightf(GL_LIGHT5, GL_SPOT_EXPONENT, 10);
	glEnable(GL_LIGHT5);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

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

void display()

{
	glEnable(GL_DEPTH_TEST);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	

	GLfloat posicion[] = { 0,10,0,0 };
	glLightfv(GL_LIGHT0, GL_POSITION, posicion);

	GLfloat posicion1[] = { 0,0.7, 0, 1.0 };
	glLightfv(GL_LIGHT1, GL_POSITION, posicion1);
	GLfloat dir_central[] = { 0,-0.5,-0.7 };
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, dir_central);

	

	moverVehiculo();
	glMultMatrixf(coef);
	glGetFloatv(GL_MODELVIEW_MATRIX, coef);

	glLoadIdentity();
	gluLookAt(pos_x, 1, pos_z, look_x, 1, look_z, 0, 1, 0);
	glMultMatrixf(coef);
	
	ejes();

	GLfloat posicion2[] = { 2.0,4.0,0.0, 1.0 };
	glLightfv(GL_LIGHT2, GL_POSITION, posicion2);
	GLfloat dir_central1[] = { 2.0,-1.0,0.0 };
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, dir_central1);

	GLfloat posicion3[] = { -2.0,4.0,0.0, 1.0 };
	glLightfv(GL_LIGHT3, GL_POSITION, posicion3);
	GLfloat dir_central2[] = { -2.0,-1.0,0.0 };
	glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, dir_central2);

	GLfloat posicion4[] = { 0.0,4.0,17.0, 1.0 };
	glLightfv(GL_LIGHT4, GL_POSITION, posicion4);
	GLfloat dir_central3[] = { 0.0,-1.0,17.0 };
	glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, dir_central3);
	
	GLfloat posicion5[] = { 2,4.0,17.0, 1.0 };
	glLightfv(GL_LIGHT5, GL_POSITION, posicion5);
	GLfloat dir_central4[] = { 2,-1.0,17.0 };
	glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, dir_central4);



	if (modo == SOLIDO) {

		//glColor3f(0.545, 0.271, 0.075);
		GLfloat Sm[] = { 0.3,0.3,0.3,1.0 };
		GLfloat Dm[] = { 0.8,0.8,0.8,1.0 };
		GLfloat s = 3.0;
		glMaterialfv(GL_FRONT, GL_SPECULAR, Sm);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, Dm);
		glMaterialf(GL_FRONT, GL_SHININESS, s);
		glCallList(circuito);
		glPolygonMode(GL_FRONT, GL_FILL);

	}
	else if (modo == ALAMBRICO) {
		GLfloat Sm[] = { 0.3,0.3,0.3,1.0 };
		GLfloat Dm[] = { 0.8,0.8,0.8,1.0 };
		GLfloat s = 3.0;
		glMaterialfv(GL_FRONT, GL_SPECULAR, Sm);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, Dm);
		glMaterialf(GL_FRONT, GL_SHININESS, s);
		glColor3f(0.0, 0.0, 0.0);
		glCallList(circuito);
		glPolygonMode(GL_FRONT, GL_LINE);


	}
	else {
		GLfloat Sm[] = { 0.3,0.3,0.3,1.0 };
		GLfloat Dm[] = { 0.8,0.8,0.8,1.0 };
		GLfloat s = 3.0;
		glMaterialfv(GL_FRONT, GL_SPECULAR, Sm);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, Dm);
		glMaterialf(GL_FRONT, GL_SHININESS, s);
		glPolygonMode(GL_FRONT, GL_LINE);
		glColor3f(0.0, 0.0, 0.0);
		glCallList(circuito);
		glPolygonMode(GL_FRONT, GL_FILL);
		glColor3f(0.545, 0.271, 0.075);
		glCallList(circuito);
	}
	
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
	case 27: exit(0);
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
}