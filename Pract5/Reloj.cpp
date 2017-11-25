//PRÁCTICA 5 DE SISTEMAS GRÁFICOS INTERACTIVOS
//Laura Ruiz Muñoz
#define PROYECTO "Reloj analogico"

#include <iostream>
#include <cmath>
#include <GL\freeglut.h>
#include <ctime>


static float beta = 0;
static float hour, min, sec, tiempo_transcurrido, min_1;

using namespace std;
static GLuint DODECAGONO;
static GLuint punto;
static GLuint estrella;

void init()
{
	DODECAGONO = glGenLists(1);
	glNewList(DODECAGONO, GL_COMPILE);

	glPolygonMode(GL_FRONT, GL_FILL);
	glBegin(GL_POLYGON);
	
	for (int i = 0; i<100; i++) {
		float x = (float)cos(i * 2 * 3.141592654 / 100);
		float y = (float)sin(i * 2 * 3.141592654 / 100);
		glVertex3f(0.95*x, 0.95*y, 0);
		glColor3f(0.0, 0.0, 0.1);
	}
	glEnd();

	glEndList();

	punto = glGenLists(2);
	glNewList(punto, GL_COMPILE);
	glPolygonMode(GL_FRONT, GL_LINE);
	glLineWidth(2.0);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	for (int i = 0; i<12; i++) {
		glVertex3f(0.98*cos(i * 2 * 3.1415926 / 12), 0.98*sin(i * 2 * 3.1415926 / 12), 0.0);
	}
	glEnd();

	glPolygonMode(GL_FRONT, GL_POINT);
	glPointSize(10.0);

	glBegin(GL_POLYGON);
	for (int i = 1; i<13; i++) {
		if (i != 12) {
			glColor3f(0.0, 0.0, 1.0);
			glVertex3f(0.97*cos(i * 2 * 3.1415926 / 12), 0.97*sin(i * 2 * 3.1415926 / 12), 0.0);
		}
		else {
			glColor3f(0.0, 1.0, 1.0);
			glVertex3f(0.97*cos(i * 2 * 3.1415926 / 12), 0.97*sin(i * 2 * 3.1415926 / 12), 0.0);
		}
	}
	glEnd();

	glEndList();

	estrella = glGenLists(3);
	glNewList(estrella, GL_COMPILE);
	glPolygonMode(GL_FRONT, GL_FILL);
	glBegin(GL_POLYGON);
	
	glVertex3f(0.25*cos(0 * 2 * 3.1415926 / 6), 0.25*sin(0 * 2 * 3.1415926 / 6), 0.0);
	
	glVertex3f(0.25*cos(2 * 2 * 3.1415926 / 6), 0.25*sin(2 * 2 * 3.1415926 / 6), 0.0);
	
	glVertex3f(0.25*cos(4 * 2 * 3.1415926 / 6), 0.25*sin(4 * 2 * 3.1415926 / 6), 0.0);
	glEnd();

	glBegin(GL_POLYGON);

	glVertex3f(0.25*cos(1 * 2 * 3.1415926 / 6), 0.25*sin(1 * 2 * 3.1415926 / 6), 0.0);

	glVertex3f(0.25*cos(3 * 2 * 3.1415926 / 6), 0.25*sin(3 * 2 * 3.1415926 / 6), 0.0);
	
	glVertex3f(0.25*cos(5 * 2 * 3.1415926 / 6), 0.25*sin(5 * 2 * 3.1415926 / 6), 0.0);

	glEnd();
	glEndList();


}

void display()

{
	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0, 0, 2.5, 0, 0, 0, 0, 1, 0);



	
	glPushMatrix();
	glRotated(90, 0, 0, 1);
	if(beta <1800)
	{
		glColor3f(0.0, 1.0, 1.0);
	}
	else
	{
		glColor3f(0.000, 0.749, 1.000);
	}
	glCallList(DODECAGONO);
	glPopMatrix();

	glPushMatrix();
	glRotated((90-sec), 0, 0, 1);
	glCallList(punto);
	glPopMatrix();

	glPushMatrix();
	glRotated(-90, 1, 0, 0);
    if (beta <= 1800) {
		glRotated(beta / 10, 1, 0, 0);
	}
	else { glRotated(-beta / 10, 1, 0, 0); }
	
	glScaled(0.95, 0.95,0.95);
	glCallList(punto);
	glPopMatrix();
	
	//Gira cada minuto
	glPushMatrix();
	if //(tiempo_transcurrido % 5.0==0)//
		(beta <1800)
	{
		glColor3f(0.0, 1.0, 1.0);
	}
	else
	{
		glColor3f(0.000, 0.749, 1.000);
	}
	glRotated(-min_1, 0, 0, 1);
	glTranslated(0.0, 0.0, 0.1);
	glCallList(estrella);
	glPopMatrix();

	for (int i = 0; i<12; i++) {
		glPushMatrix();
		glLineWidth(1.0);
		glColor3f(0.0, 1.0, 1.0);
		glTranslatef(0.9*cos(i * 2 * 3.141592 / 12), 0.9*sin(i * 2 * 3.141592 / 12), 0);
		glutWireSphere(0.025, 50, 50);
		glPopMatrix();
	}


	glPushMatrix();
	glRotatef(min, 0, 0, -1);
	glRotatef(90, 0, 0, 1);
	glTranslatef(0.9 / 2, 0, 0);
	glScalef(0.9, 0.04, 0.04);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glRotatef(hour, 0, 0, -1);
	glRotatef(90, 0, 0, 1);
	glTranslatef(0.6 / 2, 0, 0);
	glScalef(0.6, 0.04, 0.04);
	glutSolidCube(1);
	glPopMatrix();


	glFlush();
	
	glDisable(GL_DEPTH_TEST);
	glutSwapBuffers();

}

void reshape(GLint w, GLint h) {
	static const float razon = 1.0;
	float razonAD = (float)w / h;
	float wp, hp;
	if (razonAD<razon) {
		wp = float(w);
		hp = wp / razon;
		glViewport(0, int(h / 2.0 - hp / 2.0), w, int(hp));
	}
	else {
		hp = float(h);
		wp = hp*razon;
		glViewport(int(w / 2.0 - wp / 2.0), 0, int(wp), h);
	}
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, razon, 1, 10);
}

void onTimer(int i) {
	if (i == 1) {
		sec = sec + 6;
		if (sec >= 360)
			sec = 0;
		min = min + 0.1;
		if (min >= 360)
			min = 0;
		hour = hour + 360 / (12 * 60 * 60);
		if (hour >= 360)
			hour = 0;
		glutTimerFunc(1000, onTimer, 1);
	}
	glutPostRedisplay();
}

void onTimer_1(int j) {
	if (j == 2)
	{
		min_1 = min_1 + 6;
		if (min_1 >= 360)
			min_1 = 0;
	}
	glutTimerFunc(60000, onTimer_1, 2);
}

void Hora() {
#pragma warning(disable : 4996)
	time_t rawtime;
	struct tm*timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	char h1 = (asctime(timeinfo))[11];
	char h2 = (asctime(timeinfo))[12];
	char m1 = (asctime(timeinfo))[14];
	char m2 = (asctime(timeinfo))[15];
	char s1 = (asctime(timeinfo))[17];
	char s2 = (asctime(timeinfo))[18];
	int hn = (h1 - '0') * 10 + (h2 - '0');
	int mn = (m1 - '0') * 10 + (m2 - '0');
	int sn = (s1 - '0') * 10 + (s2 - '0');
	sec = sn * 6;
	min = mn * 6;
	hour = (hn % 12) * 30 + (min / 12);
}


void onIdle()
{
	static const float omega = 1;
	static int antes = glutGet(GLUT_ELAPSED_TIME);
	int ahora =	glutGet(GLUT_ELAPSED_TIME);
	
	tiempo_transcurrido = (ahora	- antes) /1000.0f;
	if (beta >= 3600)
	{
		beta = 0;
	}
	beta += 1 * 360 * tiempo_transcurrido;
	antes = ahora;
	glutPostRedisplay();	
}


void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutCreateWindow(PROYECTO);
	
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(onIdle);
	glutTimerFunc(1000, onTimer, 1);
	glutTimerFunc(60000, onTimer_1, 2);
	cout << PROYECTO << " en marcha " << endl;
	init();
	Hora();
	glutMainLoop();
}