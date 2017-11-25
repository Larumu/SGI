//PRÁCTICA 2 DE SISTEMAS GRÁFICOS INTERACTIVOS
//Laura Ruiz Muñoz
#define PROYECTO "Estrella de David"

#include <iostream>
#include <cmath>
#include <GL\freeglut.h>

using namespace std;
static GLuint ESTRELLA;

void init()
{
	ESTRELLA = glGenLists(1);
	glNewList(ESTRELLA, GL_COMPILE);
	//Triangulo max arriba
	glColor3f(0.0, 0.0, 0.3);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(0.0, 1.0, 0.0);
	glVertex3f(-0.865, -0.5, 0.0);
	glVertex3f(0.865, -0.5, 0.0);
	glEnd();
	//Triangulo max abajo
	glColor3f(0.0, 0.0, 0.3);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(0.0, -1.0, 0.0);
	glVertex3f(0.865, 0.5, 0.0);
	glVertex3f(-0.865, 0.5, 0.0);
	glEnd();
	//Triangulo min arriba
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(0.0, 0.7, 0.0);
	glVertex3f(-0.605, -0.35, 0.0);
	glVertex3f(0.605, -0.35, 0.0);
	glEnd();
	//Triangulo min abajo
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(0.0, -0.7, 0.0);
	glVertex3f(0.605, 0.35, 0.0);
	glVertex3f(-0.605, 0.35, 0.0);
	glEnd();
	//hexagono max
	glColor3f(0.0, 0.0, 0.3);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(-0.575, 0.0, 0.0);//3
	glVertex3f(-0.3, -0.5, 0.0);//2
	glVertex3f(-0.3, 0.5, 0.0);//4
	glVertex3f(0.3, -0.5, 0.0);//1
	glVertex3f(0.3, 0.5, 0.0);//5
	glVertex3f(0.575, 0.0, 0.0);//6
	glEnd();
	//hexagono min
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(-0.4025, 0.0, 0.0);//3	
	glVertex3f(-0.21, -0.35, 0.0);//2
	glVertex3f(-0.21, 0.35, 0.0);//4
	glVertex3f(0.21, -0.35, 0.0);//1
	glVertex3f(0.21, 0.35, 0.0);//5
	glVertex3f(0.4025, 0.0, 0.0);//6
	glEnd();

	glEndList();

}

void display()

{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(1, 1.5, 2, 0, 0, 0, 0, 1, 0);
	glTranslatef(-0.15, 0, 0);

	glRotatef(10, 0, 1, 0);
	glCallList(ESTRELLA);
	
	glPushMatrix();
	glRotatef(-30, 0, 1, 0);
	//glTranslatef(-0.15, 0, 0);
	glCallList(ESTRELLA);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-60, 0, 1, 0);
	glCallList(ESTRELLA);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-90, 0, 1, 0);
	glCallList(ESTRELLA);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-120, 0, 1, 0);
	glCallList(ESTRELLA);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-150, 0, 1, 0);
	glCallList(ESTRELLA);
	glPopMatrix();

	glColor3f(0.0, 0.0, 0.3);
	glutWireSphere(1.0,12,12);

	


	glFlush();
}

void reshape(GLint w, GLint h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float razon = (float) w / h;
	gluPerspective(45, razon, 1, 10);
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutCreateWindow(PROYECTO);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	cout << PROYECTO << " en marcha " << endl;
	glutMainLoop();
}