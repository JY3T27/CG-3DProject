#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <gl/gL.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include <math.h>

#define PI 3.141592653

#define SCREEN_WIDTH	500
#define SCREEN_HEIGHT	500
#define FPS	30

float angle = 0.0;

void square() {
	glBegin(GL_QUADS);
	glVertex3f(1.0, 1.0, 0.0);
	glVertex3f(-1.0, 1.0, 0.0);
	glVertex3f(-1.0, -1.0, 0.0);
	glVertex3f(1.0, -1.0, 0.0);
	glEnd();
}

void rectangle() {
	glBegin(GL_QUADS);
	glVertex3f(1.0, 1.0, 0.0);
	glVertex3f(-1.0, 1.0, 0.0);
	glVertex3f(-1.0, -1.0, 0.0);
	glVertex3f(1.0, -1.0, 0.0);
	glEnd();
}

void cube() {
	glNormal3f(0, 0, 1);

	glPushMatrix();
	glColor3d(1.0, 0.0, 0.0);
	glTranslated(0.0, 0.0, 1.0);
	square();
	glPopMatrix();

	glPushMatrix();
	glColor3d(0.0, 1.0, 0.0);
	glRotated(90.0, 0.0, 1.0, 0.0);
	glTranslated(0.0, 0.0, 1.0);
	square();
	glPopMatrix();

	glPushMatrix();
	glColor3d(1.0, 1.0, 0.0);
	glRotated(180.0, 0.0, 1.0, 0.0);
	glTranslated(0.0, 0.0, 1.0);
	square();
	glPopMatrix();

	glPushMatrix();
	glColor3d(0.0, 1.0, 1.0);
	glRotated(270.0, 0.0, 1.0, 0.0);
	glTranslated(0.0, 0.0, 1.0);
	square();
	glPopMatrix();

	glPushMatrix();
	glColor3d(1.0, 0.0, 1.0);
	glRotated(-90.0, 1.0, 0.0, 0.0);
	glTranslated(0.0, 0.0, 1.0);
	square();
	glPopMatrix();

	glPushMatrix();
	glColor3d(1.0, 1.0, 1.0);
	glRotated(90.0, 1.0, 0.0, 0.0);
	glTranslated(0.0, 0.0, 1.0);
	square();
	glPopMatrix();

}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//head
	glPushMatrix();
	glColor3f(0.95f, 0.75f, 0.6f);
	glScaled(0.2, 0.2, 0.2);
	glTranslated(0.0, 9.0, 0.0);
	glutSolidSphere(5.0, 25.0, 25.0);
	glPopMatrix();

	//body
	glPushMatrix();
	glColor3f(0.9f, 0.9f, 0.5f);
	glScaled(0.8, 1.0, 0.5);
	glTranslated(0.0, -0.5, 0.0);
	glutSolidCube(3.0);
	glPopMatrix();

	//left hand
	glPushMatrix();
	glColor3f(0.95f, 0.75f, 0.6f);
	glScaled(0.5, 1.0, 0.3); // scaling size
	glTranslated(3.0, -0.5, 0.0); //positioning
	glutSolidCube(2.0); //size
	glPopMatrix();

	//left fist
	glPushMatrix();
	glColor3f(0.95f, 0.75f, 0.6f);
	glScaled(0.1, 0.1, 0.1);
	glTranslated(15.0, -18, 0.0);
	glutSolidSphere(3.0, 25.0, 25.0);
	glPopMatrix();

	//right hand
	glPushMatrix();
	glColor3f(0.95f, 0.75f, 0.6f);
	glScaled(0.5, 1.0, 0.3); 
	glTranslated(-3.0, -0.5, 0.0); 
	glutSolidCube(2.0);
	glPopMatrix();

	//right fist
	glPushMatrix();
	glColor3f(0.95f, 0.75f, 0.6f);
	glScaled(0.1, 0.1, 0.1);
	glTranslated(-16.0, -18, 0.0);
	glutSolidSphere(3.0, 25.0, 25.0);
	glPopMatrix();

	//left leg
	glPushMatrix();
	glColor3f(0.95f, 0.75f, 0.6f);
	glScaled(0.4, 1.2, 0.3); 
	glTranslated(-1.0, -2.5, 0.0); 
	glutSolidCube(2.0);
	glPopMatrix();

	//right leg
	glPushMatrix();
	glColor3f(0.95f, 0.75f, 0.6f);
	glScaled(0.4, 1.2, 0.3);
	glTranslated(1.0, -2.5, 0.0);
	glutSolidCube(2.0);
	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

void idle() {
	DWORD start = GetTickCount64();
	while (GetTickCount64() - start < 1000 / FPS);

	angle += 0.1;
	if (angle > 360.0) angle = 0.0;

	glutPostRedisplay();

}

void initGL() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glPointSize(10.0);
	glLineWidth(5.0);

	// camera setup
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-10, 10, -10, 10, 0.5, 1000.0);
	gluPerspective(45.0, 1.0, 0.0001, 1000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(5.0, 5.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	// lights
	glEnable(GL_COLOR_MATERIAL); // cheat!!!!
	glEnable(GL_LIGHTING);
	GLfloat dir[] = { 0.2, 0.0, 1.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, dir);
	glEnable(GL_LIGHT0);

	// depth buffer
	glEnable(GL_DEPTH_TEST);
}

int main(int argc, char** argv) {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInit(&argc, argv);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow("Test");
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	initGL();

	glutMainLoop();

}