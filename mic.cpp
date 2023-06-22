const float MICROPHONE_HEIGHT = 0.2f;
const float MICROPHONE_RADIUS = 0.4f;

void drawMicrophone() {
	// Draw the microphone base (a cylinder)
	glColor3f(0.5f, 0.5f, 0.5f);
	GLUquadricObj* base = gluNewQuadric();
	gluCylinder(base, MICROPHONE_RADIUS * 0.8, MICROPHONE_RADIUS * 0.8, MICROPHONE_HEIGHT * 0.3, 16, 1);

	// Draw the microphone body (a cone)
	glTranslatef(0.0f, 0.0f, MICROPHONE_HEIGHT * 0.2);
	glColor3f(0.8f, 0.8f, 0.8f);
	GLUquadricObj* body = gluNewQuadric();
	gluCylinder(body, MICROPHONE_RADIUS * 0.7, 0.0, MICROPHONE_HEIGHT * 0.8, 16, 1);

	// Draw the microphone top (a sphere)
	glTranslatef(0.0f, 0.0f, MICROPHONE_HEIGHT * 0.8);
	glColor3f(0.7f, 0.7f, 0.7f);
	glutSolidSphere(MICROPHONE_RADIUS * 0.7, 16, 16);
}
