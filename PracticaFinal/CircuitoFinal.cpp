//PR�CTICA 8 de Introducci�n a los sistemas gr�ficos interactivos (Texturas)
//Laura Ruiz Mu�oz
#define PROYECTO "Circuito"

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
static float velocity = 0, grad = 0;
static float pos_x = 0, pos_z = 0, look_x = 0, look_z = 1;
static int N = 10, M = 10;
static enum { SOLIDO, ALAMBRICO } modo;
static enum { DESACTIVAR, ACTIVAR } luces;
static enum { SECO, HUMEDO }  niebla;
static enum { ON, OFF } efectos;
static enum { NOCHE,DIA} textura;
GLuint tex0, tex1, tex2, tex3, tex4, tex5, tex6, tex7,tex8,tex9,tex10,tex11;
static float coef[16];

using namespace std;

void init()
{
	glShadeModel(GL_SMOOTH);
	glNormal3f(0, 1, 0);


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

	glGenTextures(1, &tex3);
	glBindTexture(GL_TEXTURE_2D, tex3);
	loadImageFile("musepancarta.jpg");
	glEnable(GL_TEXTURE_2D);

	glGenTextures(1, &tex4);
	glBindTexture(GL_TEXTURE_2D, tex4);
	loadImageFile("supernaturabanner.jpg");
	glEnable(GL_TEXTURE_2D);

	glGenTextures(1, &tex5);
	glBindTexture(GL_TEXTURE_2D, tex5);
	loadImageFile("starwars.jpg");
	glEnable(GL_TEXTURE_2D);

	glGenTextures(1, &tex6);
	glBindTexture(GL_TEXTURE_2D, tex6);
	loadImageFile("fantasy.jpg");
	glEnable(GL_TEXTURE_2D);

	glGenTextures(1, &tex7);
	glBindTexture(GL_TEXTURE_2D, tex7);
	loadImageFile("mario.png");
	glEnable(GL_TEXTURE_2D);

	glGenTextures(1, &tex8);
	glBindTexture(GL_TEXTURE_2D, tex8);
	loadImageFile("rojo.jpg");
	glEnable(GL_TEXTURE_2D);

	glGenTextures(1, &tex9);
	glBindTexture(GL_TEXTURE_2D, tex9);
	loadImageFile("verde.jpg");
	glEnable(GL_TEXTURE_2D);

	glGenTextures(1, &tex10);
	glBindTexture(GL_TEXTURE_2D, tex10);
	loadImageFile("nubes.jpg");
	glEnable(GL_TEXTURE_2D);

	glGenTextures(1, &tex11);
	glBindTexture(GL_TEXTURE_2D, tex11);
	loadImageFile("cielo6.jpg");
	glEnable(GL_TEXTURE_2D);

	glGetFloatv(GL_MODELVIEW_MATRIX, coef);

	GLfloat Al0[] = { 0.05,0.05,0.05,1.0 };
	GLfloat Dl0[] = { 0.05,0.05,0.05,1.0 };
	GLfloat Sl0[] = { 0.0,0.0,0.0,1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, Al0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Dl0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, Sl0);


	GLfloat Al1[] = { 0.5,0.5,0.5,1.0 };
	GLfloat Dl1[] = { 1.0,1.0,1.0,1.0 };
	GLfloat Sl1[] = { 0.3,0.3,0.3,1.0 };
	glLightfv(GL_LIGHT1, GL_AMBIENT, Al1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Dl1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, Sl1);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 25);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 20);


	GLfloat Al2[] = { 0.0,0.0,0.0,1.0 };
	GLfloat Dl2[] = { 0.5,0.5,0.2,1.0 };
	GLfloat Sl2[] = { 0.0,0.0,0.0,1.0 };
	GLfloat dir_central_aux[] = { 0.0, -1, 7 };
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, dir_central_aux);
	glLightfv(GL_LIGHT2, GL_AMBIENT, Al2);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, Dl2);
	glLightfv(GL_LIGHT2, GL_SPECULAR, Sl2);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 30);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 10);


	GLfloat dir_central2[] = { -2.0,-1.0,0.0 };
	glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, dir_central2);
	glLightfv(GL_LIGHT3, GL_AMBIENT, Al2);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, Dl2);
	glLightfv(GL_LIGHT3, GL_SPECULAR, Sl2);
	glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 30);
	glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 10);
	glEnable(GL_LIGHT3);

	glLightfv(GL_LIGHT4, GL_AMBIENT, Al2);
	glLightfv(GL_LIGHT4, GL_DIFFUSE, Dl2);
	glLightfv(GL_LIGHT4, GL_SPECULAR, Sl2);
	glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, 30);
	glLightf(GL_LIGHT4, GL_SPOT_EXPONENT, 10);
	glEnable(GL_LIGHT4);

	glLightfv(GL_LIGHT5, GL_AMBIENT, Al2);
	glLightfv(GL_LIGHT5, GL_DIFFUSE, Dl2);
	glLightfv(GL_LIGHT5, GL_SPECULAR, Sl2);
	glLightf(GL_LIGHT5, GL_SPOT_CUTOFF, 30);
	glLightf(GL_LIGHT5, GL_SPOT_EXPONENT, 10);
	glEnable(GL_LIGHT5);

	glEnable(GL_DEPTH_TEST);


}

void moverVehiculo()
{
	static int horaAnterior = glutGet(GLUT_ELAPSED_TIME);
	int horaActual = glutGet(GLUT_ELAPSED_TIME);
	float tiempoTranscurrido = horaActual - horaAnterior;
	pos_x += velocity * (tiempoTranscurrido / 1000.0)*sin(grad*PI / 180.0);
	pos_z += velocity * (tiempoTranscurrido / 1000.0)*cos(grad*PI / 180.0);
	look_z = pos_z + cos(grad*PI / 180.0);
	look_x = pos_x + sin(grad*PI / 180.0);
	horaAnterior = horaActual;
}

void display()

{


	glClear(GL_ACCUM_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glMultMatrixf(coef);
	glGetFloatv(GL_MODELVIEW_MATRIX, coef);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glEnable(GL_TEXTURE_2D);




	GLfloat posicion[] = { 0,10,0,0 };
	glLightfv(GL_LIGHT0, GL_POSITION, posicion);
	GLfloat posicion1[] = { 0,0.7, 0, 1.0 };
	glLightfv(GL_LIGHT1, GL_POSITION, posicion1);
	GLfloat dir_central[] = { 0,-0.5,-0.7 };
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, dir_central);

	//NIEBLA
	if (niebla == HUMEDO && luces == ACTIVAR && textura == NOCHE) {
		GLfloat color_niebla[3] = { 0.545, 0.271, 0.075 };
		glEnable(GL_FOG);
		glFogfv(GL_FOG_COLOR, color_niebla);
		glFogf(GL_FOG_DENSITY, 0.3);
	}
	else if (niebla == SECO) {
		glDisable(GL_FOG);
	}
	else if (niebla == HUMEDO && luces == DESACTIVAR && textura == NOCHE) {
		GLfloat color_niebla2[3] = { 0.627, 0.322, 0.176 };
		glEnable(GL_FOG);
		glFogfv(GL_FOG_COLOR, color_niebla2);
		glFogf(GL_FOG_DENSITY, 0.3);
	} else if (niebla == HUMEDO && luces == ACTIVAR && textura == DIA){
		GLfloat color_niebla3[3] = { 0.502, 0.502, 0.502 };
		glEnable(GL_FOG);
		glFogfv(GL_FOG_COLOR, color_niebla3);
		glFogf(GL_FOG_DENSITY, 0.3);
	}
	else if (niebla == HUMEDO && luces == DESACTIVAR && textura == DIA) {
		GLfloat color_niebla4[3] = { 0.753, 0.753, 0.753 };
		glEnable(GL_FOG);
		glFogfv(GL_FOG_COLOR, color_niebla4);
		glFogf(GL_FOG_DENSITY, 0.3);
	}

	//MENSAJE PARA LAURA DEL FUTURO: TOCA ESTO Y TE REVIENTO
	if (luces == ACTIVAR) {
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT1);
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	moverVehiculo();
	if (efectos == ON) {
		gluLookAt(0, 0, 0, 0, 0, -1, 0, 1, 0);

		

		glBindTexture(GL_TEXTURE_2D, tex7);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		// c. Forma de combinar y repetir
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPEAT);

		glPushMatrix();
		glBegin(GL_POLYGON);
		glTranslatef(-0.5, -5, 0);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(-0.5, -0.82, -2.0);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(1, -0.82, -2.0);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(1, 0.5, -2.0);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(-0.5, 0.5, -2.0);
		
		
		
		glEnd();
		glPopMatrix();

		glPushMatrix();
		if (velocity > 3) {
			glBindTexture(GL_TEXTURE_2D, tex8);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			// c. Forma de combinar y repetir
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPEAT);

		}
		else {
			glBindTexture(GL_TEXTURE_2D, tex9);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			// c. Forma de combinar y repetir
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPEAT);

		}
		glBegin(GL_POLYGON);

		glTranslatef(-0.5, -5, 0);
		glVertex3f(1.2, (velocity / 3) - 0.82, -2.0);
		glVertex3f(1.5, (velocity / 3) - 0.82, -2.0);
		glVertex3f(1.5, -0.82, -2.0);
		glVertex3f(1.2, -0.82, -2.0);
		glEnd();
		glPopMatrix();


	}


	//glClear(GL_DEPTH_BUFFER_BIT);

	//gluLookAt(0, 200, 0, 0, 0, 0, 0, 0, -1);
	gluLookAt(pos_x, 1, pos_z, look_x, 1, look_z, 0, 1, 0);
	//glClear(GL_DEPTH_BUFFER_BIT);
	ejes();

	if (luces == ACTIVAR) {

		glEnable(GL_LIGHT0);

		GLfloat posicion2[] = { 0.0,3.0,7.0, 1.0 };
		glLightfv(GL_LIGHT2, GL_POSITION, posicion2);

		GLfloat posicion3[] = { -2.0,4.0,0.0, 1.0 };
		glLightfv(GL_LIGHT3, GL_POSITION, posicion3);

		GLfloat posicion4[] = { 0.0,4.0,17.0, 1.0 };
		glLightfv(GL_LIGHT4, GL_POSITION, posicion4);
		GLfloat dir_central3[] = { 0.0,-1.0,17.0 };
		glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, dir_central3);

		GLfloat posicion5[] = { 2,4.0,17.0, 1.0 };
		glLightfv(GL_LIGHT5, GL_POSITION, posicion5);
		GLfloat dir_central4[] = { 2,-1.0,17.0 };
		glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, dir_central4);

		glEnable(GL_LIGHT2);
		glEnable(GL_LIGHT3);
		glEnable(GL_LIGHT4);
		glEnable(GL_LIGHT5);
	}
	if (luces == DESACTIVAR) {
		glDisable(GL_LIGHTING);
	}

	if (modo == SOLIDO) {
		glEnable(GL_TEXTURE_2D);
		if (luces == ACTIVAR) {
			//Circuito arcoiris s�lido
			if (textura == DIA) {
				glBindTexture(GL_TEXTURE_2D, tex10);
			}
			else if (textura == NOCHE) {
				glBindTexture(GL_TEXTURE_2D, tex0);
			}
			// b. Filtros
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			// c. Forma de combinar y repetir
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

			GLfloat planoS[] = { -2,0,0,0 };
			GLfloat planoT[] = { -2,0,20,0 };
			glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
			glTexGenfv(GL_S, GL_OBJECT_PLANE, planoS);
			glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
			glTexGenfv(GL_T, GL_OBJECT_PLANE, planoT);

			GLfloat Sm[] = { 0.3,0.3,0.3,1.0 };
			GLfloat Dm[] = { 0.8,0.8,0.8,1.0 };
			GLfloat s = 3.0;
			glMaterialfv(GL_FRONT, GL_SPECULAR, Sm);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, Dm);
			glMaterialf(GL_FRONT, GL_SHININESS, s);
		}
		else if (luces == DESACTIVAR) {
			if (textura == DIA) {
				glBindTexture(GL_TEXTURE_2D, tex10);
			}
			else if (textura == NOCHE) {
				glBindTexture(GL_TEXTURE_2D, tex0);
			}
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
		}

		glShadeModel(GL_SMOOTH);
		glCallList(circuito);
		glPolygonMode(GL_FRONT, GL_FILL);

		if (luces == ACTIVAR) {
			//Fondo paisaje s�lido
			if (textura == DIA) {
				glBindTexture(GL_TEXTURE_2D, tex11);
			}
			else if (textura == NOCHE) {
				glBindTexture(GL_TEXTURE_2D, tex6);
			}
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			// c. Forma de combinar y repetir
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		}
		else if (luces == DESACTIVAR) {
			//Fondo paisaje s�lido
			if (textura == DIA) {
				glBindTexture(GL_TEXTURE_2D, tex11);
			}
			else if (textura == NOCHE) {
				glBindTexture(GL_TEXTURE_2D, tex6);
			}
			//glBindTexture(GL_TEXTURE_2D, tex6);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			// c. Forma de combinar y repetir
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPEAT);
		}

		glBegin(GL_QUAD_STRIP);
		float alfa = 2 * PI / 10.0;
		for (int i = 0; i <= 10; i++) {
			float ex = 75 * sin(i*alfa);
			float ez = 75 * cos(i*alfa);
			glTexCoord2f(i*alfa / (2.0*PI), 0);
			glVertex3f(ex, -75, ez);
			glTexCoord2f(i*alfa / (2.0*PI), 1);
			glVertex3f(ex, 75, ez);
		}
		glEnd();

		//Postes de pancarta Dio
		//(1)
		glPushMatrix();
		glColor3f(0.663, 0.663, 0.663);
		glTranslatef(-2.0, 1.75, 10);
		glScalef(0.1, 3.5, 0.1);
		glutSolidCube(1.0);
		glPopMatrix();

		//(2)
		glPushMatrix();
		glColor3f(0.663, 0.663, 0.663);
		glTranslatef(2.0, 1.75, 10);
		glScalef(0.1, 3.5, 0.1);
		glutSolidCube(1.0);
		glPopMatrix();

		//Postes de Pancarta Muse s�lidos
		//(1)
		glPushMatrix();
		glColor3f(0.663, 0.663, 0.663);
		glTranslatef(-5.0, 1.75, 38);
		glScalef(0.1, 3.5, 0.1);
		glutSolidCube(1.0);
		glPopMatrix();

		//(2)
		glPushMatrix();
		glColor3f(0.663, 0.663, 0.663);
		glTranslatef(-5.0, 1.75, 43);
		glScalef(0.1, 3.5, 0.1);
		glutSolidCube(1.0);
		glPopMatrix();

		//Postes de pancarta SPN s�lidos
		//(1)
		glPushMatrix();
		glColor3f(0.663, 0.663, 0.663);
		glTranslatef(-14.0, 1.75, 10);
		glScalef(0.1, 3.5, 0.1);
		glutSolidCube(1.0);
		glPopMatrix();

		//(2)
		glPushMatrix();
		glColor3f(0.663, 0.663, 0.663);
		glTranslatef(-18.0, 1.75, 10);
		glScalef(0.1, 3.5, 0.1);
		glutSolidCube(1.0);
		glPopMatrix();

		//Postes de pancarta Star Wars s�lidos
		//(1)
		glPushMatrix();
		glColor3f(0.663, 0.663, 0.663);
		glTranslatef(-7.0, 1.75, -38);
		glScalef(0.1, 3.5, 0.1);
		glutSolidCube(1.0);
		glPopMatrix();

		//(2)
		glPushMatrix();
		glColor3f(0.663, 0.663, 0.663);
		glTranslatef(-7.0, 1.75, -43);
		glScalef(0.1, 3.5, 0.1);
		glutSolidCube(1.0);
		glPopMatrix();

		if (luces == ACTIVAR) {
			//Pancarta de Dio s�lida
			glBindTexture(GL_TEXTURE_2D, tex2);
			// b. Filtros
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			// c. Forma de combinar y repetir
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		}
		else if (luces == DESACTIVAR) {
			//Pancarta de Dio s�lida
			glBindTexture(GL_TEXTURE_2D, tex2);
			// b. Filtros
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			// c. Forma de combinar y repetir
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPEAT);
		}

		glPushMatrix();
		glColor3f(0.0, 0.0, 0.0);
		glTranslatef(2.0, 2.0, 10);
		glScalef(4.0, 4.0, 1.0);
		glRotatef(180, 0, 1, 0);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(0.0, 0.0, 0);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(0.0, 0.56, 0);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(1.0, 0.56, 0);
		glTexCoord2f(1.0, 0);
		glVertex3f(1.0, 0, 0);
		glEnd();
		glPopMatrix();

		if (luces == ACTIVAR) {
			//Pancarta de Muse s�lida
			glBindTexture(GL_TEXTURE_2D, tex3);
			// b. Filtros
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			// c. Forma de combinar y repetir
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		}
		else if (luces == DESACTIVAR) {
			//Pancarta de Muse s�lida
			glBindTexture(GL_TEXTURE_2D, tex3);
			// b. Filtros
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			// c. Forma de combinar y repetir
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPEAT);
		}

		glPushMatrix();
		glColor3f(0.0, 0.0, 0.0);
		glTranslatef(-5.0, 2.75, 43);
		glRotatef(90, 0, 1, 0);
		glScalef(5.0, 5.0, 1.0);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(0.0, 0.0, 0);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(0.0, 0.5, 0);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(1.0, 0.5, 0);
		glTexCoord2f(1.0, 0);
		glVertex3f(1.0, 0, 0);
		glEnd();
		glPopMatrix();

		if (luces == ACTIVAR) {
			//Pancarta de SPN s�lida
			glBindTexture(GL_TEXTURE_2D, tex4);
			// b. Filtros
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			// c. Forma de combinar y repetir
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		}
		else if (luces == DESACTIVAR) {
			//Pancarta de SPN s�lida
			glBindTexture(GL_TEXTURE_2D, tex4);
			// b. Filtros
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			// c. Forma de combinar y repetir
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPEAT);
		}

		glPushMatrix();
		glColor3f(0.0, 0.0, 0.0);
		glTranslatef(-18.0, 2.5, 10);
		glScalef(4.0, 4.0, 1.0);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(0.0, 0.0, 0);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(0.0, 0.37, 0);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(1.0, 0.37, 0);
		glTexCoord2f(1.0, 0);
		glVertex3f(1.0, 0, 0);
		glEnd();
		glPopMatrix();

		if (luces == ACTIVAR) {
			//Pancarta de Star Wars s�lida
			glBindTexture(GL_TEXTURE_2D, tex5);
			// b. Filtros
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			// c. Forma de combinar y repetir
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		}
		else if (luces == DESACTIVAR) {
			//Pancarta de Star Wars s�lida
			glBindTexture(GL_TEXTURE_2D, tex5);
			// b. Filtros
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			// c. Forma de combinar y repetir
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPEAT);
		}

		glPushMatrix();
		glColor3f(0.0, 0.0, 0.0);
		glTranslatef(-7.0, 2.0, -43);
		glRotatef(-90, 0, 1, 0);
		glScalef(5.05, 5.05, 1.0);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(0.0, 0.0, 0);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(0.0, 0.375, 0);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(1.0, 0.375, 0);
		glTexCoord2f(1.0, 0);
		glVertex3f(1.0, 0, 0);
		glEnd();
		glPopMatrix();

		glDisable(GL_TEXTURE_2D);

	}
	else if (modo == ALAMBRICO) {
		glDisable(GL_LIGHTING);
		glDisable(GL_FOG);
		//Postes de pancarta Dio al�mbricos
		//(1)
		glPushMatrix();
		glColor3f(0.0, 0.0, 0.0);
		glTranslatef(-2.0, 1.75, 10);
		glScalef(0.1, 3.5, 0.1);
		glutWireCube(1.0);
		glPopMatrix();

		//(2)
		glPushMatrix();
		glColor3f(0.0, 0.0, 0.0);
		glTranslatef(2.0, 1.75, 10);
		glScalef(0.1, 3.5, 0.1);
		glutWireCube(1.0);
		glPopMatrix();

		//Postes de pancarta Muse al�mbricos
		//(1)
		glPushMatrix();
		glColor3f(0.0, 0.0, 0.0);
		glTranslatef(-5.0, 1.75, 38);
		glScalef(0.1, 3.5, 0.1);
		glutWireCube(1.0);
		glPopMatrix();

		//(2)
		glPushMatrix();
		glColor3f(0.0, 0.0, 0.0);
		glTranslatef(-5.0, 1.75, 43);
		glScalef(0.1, 3.5, 0.1);
		glutWireCube(1.0);
		glPopMatrix();

		//Postes de pancarta SPN al�mbricos
		//(1)
		glPushMatrix();
		glColor3f(0.0, 0.0, 0.0);
		glTranslatef(-14.0, 1.75, 10);
		glScalef(0.1, 3.5, 0.1);
		glutWireCube(1.0);
		glPopMatrix();

		//(2)
		glPushMatrix();
		glColor3f(0.0, 0.0, 0.0);
		glTranslatef(-18.0, 1.75, 10);
		glScalef(0.1, 3.5, 0.1);
		glutWireCube(1.0);
		glPopMatrix();

		//Postes de pancarta Star Wars al�mbricos 
		//(1)
		glPushMatrix();
		glColor3f(0.0, 0.0, 0.0);
		glTranslatef(-7.0, 1.75, -38);
		glScalef(0.1, 3.5, 0.1);
		glutWireCube(1.0);
		glPopMatrix();

		//(2)
		glPushMatrix();
		glColor3f(0.0, 0.0, 0.0);
		glTranslatef(-7.0, 1.75, -43);
		glScalef(0.1, 3.5, 0.1);
		glutWireCube(1.0);
		glPopMatrix();

		//Pancarta de Dio al�mbrica
		glPushMatrix();
		glColor3f(0.0, 0.0, 0.0);
		glTranslatef(2.0, 2.0, 10);
		glScalef(4.0, 4.0, 1.0);
		glRotatef(180, 0, 1, 0);
		glBegin(GL_LINE_LOOP);
		glVertex3f(0.0, 0.0, 0);
		glVertex3f(0.0, 0.56, 0);
		glVertex3f(1.0, 0.56, 0);
		glVertex3f(1.0, 0, 0);
		glEnd();
		glPopMatrix();

		//Pancarta de Muse al�mbrica
		glPushMatrix();
		glColor3f(0.0, 0.0, 0.0);
		glTranslatef(-5.0, 2.75, 43);
		glRotatef(90, 0, 1, 0);
		glScalef(5.0, 5.0, 1.0);
		glBegin(GL_LINE_LOOP);
		glVertex3f(0.0, 0.0, 0);
		glVertex3f(0.0, 0.5, 0);
		glVertex3f(1.0, 0.5, 0);
		glVertex3f(1.0, 0, 0);
		glEnd();
		glPopMatrix();

		//Pancarta de SPN al�mbrica
		glPushMatrix();
		glColor3f(0.0, 0.0, 0.0);
		glTranslatef(-18.0, 2.5, 10);
		glScalef(4.0, 4.0, 1.0);
		glBegin(GL_LINE_LOOP);
		glVertex3f(0.0, 0.0, 0);
		glVertex3f(0.0, 0.37, 0);
		glVertex3f(1.0, 0.37, 0);
		glVertex3f(1.0, 0, 0);
		glEnd();
		glPopMatrix();

		//Pancarta de Star Wars al�mbrica
		glPushMatrix();
		glColor3f(0.0, 0.0, 0.0);
		glTranslatef(-7.0, 2.0, -43);
		glRotatef(-90, 0, 1, 0);
		glScalef(5.05, 5.05, 1.0);
		glBegin(GL_LINE_LOOP);
		glVertex3f(0.0, 0.0, 0);
		glVertex3f(0.0, 0.375, 0);
		glVertex3f(1.0, 0.375, 0);
		glVertex3f(1.0, 0, 0);

		glEnd();
		glPopMatrix();

		//Cilindro para textura al�mbrico
		glBegin(GL_QUAD_STRIP);
		float alfa = 2 * PI / 10.0;
		for (int i = 0; i <= 10; i++) {
			float ex = 75 * sin(i*alfa);
			float ez = 75 * cos(i*alfa);
			glTexCoord2f(i*alfa / (2.0*PI), 0);
			glVertex3f(ex, -75, ez);
			glTexCoord2f(i*alfa / (2.0*PI), 1);
			glVertex3f(ex, 75, ez);
		}
		glEnd();

		//Circuito al�mbrico
		glColor3f(0.0, 0.0, 0.0);
		glPolygonMode(GL_FRONT, GL_LINE);
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
	gluPerspective(45, razon, 1, 4000);
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
	cuentakms << "Interfaz de conducci�n. SPEED " << velocity << " m/s";
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
		break;
	case 'S': modo = SOLIDO;
		break;
	case 's': modo = ALAMBRICO;
		break;
	case 'L': luces = ACTIVAR;
		break;
	case 'l': luces = DESACTIVAR;
		break;
	case 'N': niebla = SECO;
		break;
	case 'n': niebla = HUMEDO;
		break;
	case 'C': efectos = ON;
		break;
	case 'c': efectos = OFF;
		break;
	case 't': textura = DIA;
		break;
	case 'T': textura = NOCHE;
		break;
	}
	glutPostRedisplay();
}

void main(int argc, char** argv)
{
	FreeImage_Initialise();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH | GLUT_ACCUM);
	glutInitWindowSize(600, 400);
	glutCreateWindow("Interfaz de conducci�n. SPEED 0 m/s");
	std::cout << "Version: OpenGL " << glGetString(GL_VERSION) << endl;
	std::cout << "Controles: " << endl;
	std::cout << "Boton s: Circuito modo alambrico" << endl;
	std::cout << "Boton S: Circuito con texturas"  << endl;
	std::cout << "Boton L: Iluminacion activada"  << endl;
	std::cout << "Boton l: Iluminacion desactivada"  << endl;
	std::cout << "Boton n: Niebla habilitada" << endl;
	std::cout << "Boton N: Niebla deshabilitada"  << endl;
	std::cout << "Boton C: Elementos solidarios con la camara activados" << endl;
	std::cout << "Boton c: Elementos solidarios con la camara desactivados"  << endl;
	std::cout << " "  << endl;
	std::cout << "Especial: "  << endl;
	std::cout << "Boton t: Circuito con texturas de dia " << endl;
	std::cout << "Boton T: Circuito con texturas de noche " << endl;
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(onSpecialKey);
	glutKeyboardFunc(onKey);
	glutIdleFunc(idle);
	glutMainLoop();
	FreeImage_DeInitialise();
}