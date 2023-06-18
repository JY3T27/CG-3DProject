void gun() {
	glPushMatrix();
	glColor3ub(105, 105, 105);
	glScaled(8.7, 1.5, 1.7);
	glTranslated(0.0, 2.0, 0.0);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(128, 128, 128);
	glScaled(8.5, 1.5, 1.1);
	glTranslated(0.0, 1.7, 0.0);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(128, 128, 128);
	glScaled(2.0, 4.0, 1.0);
	glTranslated(1.5, 0.05, 0.0);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(90, 90, 90);
	glScaled(1.0, 1.0, 0.7);
	glTranslated(1.3, 1.2, 0.0);
	glutSolidCube(1.0);
	glPopMatrix();
}
