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
	glClear(GL_COLOR_BUFFER_BIT);


	glCallList(ESTRELLA);


	glFlush();
}

void reshape(GLint w, GLint h)
{

}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutCreateWindow(PROYECTO);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	cout << PROYECTO << " en marcha " << endl;
	glutMainLoop();
}