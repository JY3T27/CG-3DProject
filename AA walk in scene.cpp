/*
void display() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    gluLookAt(0.0, 0.0, 30.0,  // camera position
        0.0, 7.0, 0.0,   // camera direction
        0.0, 1.0, 0.0);

    glEnable(GL_DEPTH_TEST);    // Enable depth testing
    glPushMatrix();
    glTranslatef(0, 0, cord_z);
    drawFace();
    drawBody();

    glPushMatrix();
    glTranslatef(0, 1, 0.0);
    glRotatef(180, 1.0f, 0.0f, 0.0f);
    glRotatef(angle, 1.0f, 0.0f, 0.0f);
    drawHand();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 1, 0.0);
    glRotatef(180, 1.0f, 0.0f, 0.0f);
    glRotatef(-angle, 1.0f, 0.0f, 0.0f);
    drawHand_right();
    glPopMatrix();

    glPushMatrix();
    glRotatef(-angle, 1.0f, 0.0f, 0.0f);
    drawLeg_left();
    glPopMatrix();

    glPushMatrix();
    glRotatef(angle, 1.0f, 0.0f, 0.0f);
    drawLeg_right();
    glPopMatrix();

    glPopMatrix();

    background();

    glFlush();
    glutSwapBuffers();
}

void idle() {

    DWORD start = GetTickCount64();
    while (GetTickCount64() - start < 1000 / FPS);

    if (angle >= -90.0 && rotate1 == false)
    {
        angle -= 5;
        if (angle == -90.0)
        {
            rotate1 = true;
        }
    }
    if (rotate1 == true)
    {
        angle += 5;
        if (angle == 90.0)
        {
            rotate1 = false;
        }
    }

    cord_z += 0.1;
    glutPostRedisplay();

}
*/


#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <gl/gL.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include <math.h>
#include "stb_image.h"

#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 800
#define FPS	30
#define PI 3.141592653

GLuint textureID[20];
int width, height, channels;
float angle = 0.0;
float rotationDirection = 1.0f;
bool rotate1 = false; // false = increase
int scale = 2;
float cord_z = 0.0;

void loadTexRepeats()
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void loadTexture() {
    //flip image vertically
    stbi_set_flip_vertically_on_load(true);

    //textureID 1
    unsigned char* image = stbi_load("D:/Desktop/cg images/front_face.jpg", &width, &height, &channels, 3);
    glGenTextures(1, &textureID[1]);
    glBindTexture(GL_TEXTURE_2D, textureID[1]);
    loadTexRepeats();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    stbi_image_free(image);

    //textureID 2
    unsigned char* imageBack1 = stbi_load("D:/Desktop/cg images/back_face.jpg", &width, &height, &channels, 3);
    glGenTextures(1, &textureID[2]);
    glBindTexture(GL_TEXTURE_2D, textureID[2]);
    loadTexRepeats();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageBack1);
    stbi_image_free(imageBack1);

    //textureID 3
    unsigned char* imageBack2 = stbi_load("D:/Desktop/cg images/right_face.jpg", &width, &height, &channels, 3);
    glGenTextures(1, &textureID[3]);
    glBindTexture(GL_TEXTURE_2D, textureID[3]);
    loadTexRepeats();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageBack2);
    stbi_image_free(imageBack2);

    //textureID 4
    unsigned char* imageBack3 = stbi_load("D:/Desktop/cg images/left_face.jpg", &width, &height, &channels, 3);
    glGenTextures(1, &textureID[4]);
    glBindTexture(GL_TEXTURE_2D, textureID[4]);
    loadTexRepeats();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageBack3);
    stbi_image_free(imageBack3);

    //textureID 5
    unsigned char* imageBack4 = stbi_load("D:/Desktop/cg images/top_face.jpg", &width, &height, &channels, 3);
    glGenTextures(1, &textureID[5]);
    glBindTexture(GL_TEXTURE_2D, textureID[5]);
    loadTexRepeats();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageBack4);
    stbi_image_free(imageBack4);

    //textureID 6
    unsigned char* imageBack5 = stbi_load("D:/Desktop/cg images/bottom_face.jpg", &width, &height, &channels, 3);
    glGenTextures(1, &textureID[6]);
    glBindTexture(GL_TEXTURE_2D, textureID[6]);
    loadTexRepeats();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageBack5);
    stbi_image_free(imageBack5);

    unsigned char* imageBack6 = stbi_load("D:/Desktop/cg images/front_body.jpg", &width, &height, &channels, 3);
    glGenTextures(1, &textureID[7]);
    glBindTexture(GL_TEXTURE_2D, textureID[7]);
    loadTexRepeats();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageBack6);
    stbi_image_free(imageBack6);

    unsigned char* imageBack7 = stbi_load("D:/Desktop/cg images/back_body.jpg", &width, &height, &channels, 3);
    glGenTextures(1, &textureID[8]);
    glBindTexture(GL_TEXTURE_2D, textureID[8]);
    loadTexRepeats();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageBack7);
    stbi_image_free(imageBack7);

    unsigned char* imageBack8 = stbi_load("D:/Desktop/cg images/hand.jpg", &width, &height, &channels, 3);
    glGenTextures(1, &textureID[9]);
    glBindTexture(GL_TEXTURE_2D, textureID[9]);
    loadTexRepeats();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageBack8);
    stbi_image_free(imageBack8);

    stbi_set_flip_vertically_on_load(false);

    unsigned char* imageBack9 = stbi_load("D:/Desktop/cg images/tt.jpg", &width, &height, &channels, 3);
    glGenTextures(1, &textureID[10]);
    glBindTexture(GL_TEXTURE_2D, textureID[10]);
    loadTexRepeats();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageBack9);
    stbi_image_free(imageBack9);

}

void drawBody() {
    // Define the cuboid's vertices
    GLfloat vertices[8][3] = {
        {-0.5, -1.0, -0.25},
        {0.5, -1.0, -0.25},
        {0.5, 1.0, -0.25},
        {-0.5, 1.0, -0.25},
        {-0.5, -1.0, 0.25},
        {0.5, -1.0, 0.25},
        {0.5, 1.0, 0.25},
        {-0.5, 1.0, 0.25}
    };

    // Define the cuboid's normals
    GLfloat normals[6][3] = {
        {0.0, 0.0, -1.0}, // Back face
        {1.0, 0.0, 0.0},  // Right face
        {0.0, 0.0, 1.0},  // Front face
        {-1.0, 0.0, 0.0}, // Left face
        {0.0, -1.0, 0.0}, // Bottom face
        {0.0, 1.0, 0.0}   // Top face
    };

    // Define the cuboid's textureID coordinates
    GLfloat texCoords[4][2] = {
        {0.0, 0.0},
        {1.0, 0.0},
        {1.0, 1.0},
        {0.0, 1.0}
    };

    glPushMatrix();
    glTranslatef(0.0f, 1, 0.0f);

    // Enable textureID mapping
    glEnable(GL_TEXTURE_2D);

    // Draw the back face with textureID coordinates
    glBindTexture(GL_TEXTURE_2D, textureID[8]);
    glBegin(GL_QUADS);
    glNormal3fv(normals[0]);
    glTexCoord2fv(texCoords[0]);
    glVertex3fv(vertices[0]);
    glTexCoord2fv(texCoords[1]);
    glVertex3fv(vertices[1]);
    glTexCoord2fv(texCoords[2]);
    glVertex3fv(vertices[2]);
    glTexCoord2fv(texCoords[3]);
    glVertex3fv(vertices[3]);
    glEnd();


    // Draw the front face with textureID coordinates
    glBindTexture(GL_TEXTURE_2D, textureID[7]);
    glBegin(GL_QUADS);
    glNormal3fv(normals[2]);
    glTexCoord2fv(texCoords[0]);
    glVertex3fv(vertices[5]);
    glTexCoord2fv(texCoords[1]);
    glVertex3fv(vertices[4]);
    glTexCoord2fv(texCoords[2]);
    glVertex3fv(vertices[7]);
    glTexCoord2fv(texCoords[3]);
    glVertex3fv(vertices[6]);
    glEnd();

    glDisable(GL_TEXTURE_2D);

    // Draw the right face with textureID coordinates

    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, textureID[9]);

    glBegin(GL_QUADS);
    glNormal3fv(normals[1]);
    glTexCoord2fv(texCoords[0]);
    glVertex3fv(vertices[1]);
    glTexCoord2fv(texCoords[1]);
    glVertex3fv(vertices[5]);
    glTexCoord2fv(texCoords[2]);
    glVertex3fv(vertices[6]);
    glTexCoord2fv(texCoords[3]);
    glVertex3fv(vertices[2]);
    glEnd();

    // Draw the left face with textureID coordinates
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, textureID[9]);

    glBegin(GL_QUADS);
    glNormal3fv(normals[3]);
    glTexCoord2fv(texCoords[0]);
    glVertex3fv(vertices[4]);
    glTexCoord2fv(texCoords[1]);
    glVertex3fv(vertices[0]);
    glTexCoord2fv(texCoords[2]);
    glVertex3fv(vertices[3]);
    glTexCoord2fv(texCoords[3]);
    glVertex3fv(vertices[7]);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3fv(normals[4]);
    glTexCoord2fv(texCoords[0]);
    glVertex3fv(vertices[1]);
    glTexCoord2fv(texCoords[1]);
    glVertex3fv(vertices[0]);
    glTexCoord2fv(texCoords[2]);
    glVertex3fv(vertices[4]);
    glTexCoord2fv(texCoords[3]);
    glVertex3fv(vertices[5]);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3fv(normals[5]);
    glTexCoord2fv(texCoords[0]);
    glVertex3fv(vertices[3]);
    glTexCoord2fv(texCoords[1]);
    glVertex3fv(vertices[2]);
    glTexCoord2fv(texCoords[2]);
    glVertex3fv(vertices[6]);
    glTexCoord2fv(texCoords[3]);
    glVertex3fv(vertices[7]);
    glEnd();

    // Disable textureID mapping

    glPopMatrix();
}

void drawFace() {

    // Define the cube's vertices
    GLfloat vertices[8][3] = {
        {-0.5, -0.5, -0.5},
        {0.5, -0.5, -0.5},
        {0.5, 0.5, -0.5},
        {-0.5, 0.5, -0.5},
        {-0.5, -0.5, 0.5},
        {0.5, -0.5, 0.5},
        {0.5, 0.5, 0.5},
        {-0.5, 0.5, 0.5}
    };

    // Define the cube's normal vectors
    GLfloat normals[6][3] = {
        {0.0, 0.0, -1.0}, // Front face
        {0.0, 0.0, 1.0},  // Back face
        {1.0, 0.0, 0.0},  // Right face
        {-1.0, 0.0, 0.0}, // Left face
        {0.0, 1.0, 0.0},  // Top face
        {0.0, -1.0, 0.0}  // Bottom face
    };

    // Define the textureID coordinates for each face
    GLfloat texCoords[6][4][2] = {
        // Front face
        {{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}},
        // Back face
        {{1.0, 0.0}, {0.0, 0.0}, {0.0, 1.0}, {1.0, 1.0}},
        // Right face
        {{1.0, 0.0}, {0.0, 0.0}, {0.0, 1.0}, {1.0, 1.0}},
        // Left face
        {{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}},
        // Top face
        {{0.0, 1.0}, {0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}},
        // Bottom face
        {{0.0, 0.0}, {0.0, 1.0}, {1.0, 1.0}, {1.0, 0.0}}
    };

    glPushMatrix();
    glTranslatef(0.0f, 2, 0.0f);

    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, textureID[1]);  // Front face textureID
    glBegin(GL_QUADS);

    glNormal3fv(normals[1]);
    glTexCoord2fv(texCoords[1][0]);
    glVertex3fv(vertices[5]);
    glTexCoord2fv(texCoords[1][1]);
    glVertex3fv(vertices[4]);
    glTexCoord2fv(texCoords[1][2]);
    glVertex3fv(vertices[7]);
    glTexCoord2fv(texCoords[1][3]);
    glVertex3fv(vertices[6]);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, textureID[2]);  // Back face textureID
    // Draw the front face with textureID coordinates and normal vectors
    glBegin(GL_QUADS);

    glNormal3fv(normals[0]);
    glTexCoord2fv(texCoords[0][0]);
    glVertex3fv(vertices[0]);
    glTexCoord2fv(texCoords[0][1]);
    glVertex3fv(vertices[1]);
    glTexCoord2fv(texCoords[0][2]);
    glVertex3fv(vertices[2]);
    glTexCoord2fv(texCoords[0][3]);
    glVertex3fv(vertices[3]);
    glEnd();


    // Draw the right face with textureID coordinates and normal vectors
    glBindTexture(GL_TEXTURE_2D, textureID[3]);
    glBegin(GL_QUADS);

    glNormal3fv(normals[2]);
    glTexCoord2fv(texCoords[2][0]);
    glVertex3fv(vertices[1]);
    glTexCoord2fv(texCoords[2][1]);
    glVertex3fv(vertices[5]);
    glTexCoord2fv(texCoords[2][2]);
    glVertex3fv(vertices[6]);
    glTexCoord2fv(texCoords[2][3]);
    glVertex3fv(vertices[2]);
    glEnd();

    // Draw the left face with textureID coordinates and normal vectors
    glBindTexture(GL_TEXTURE_2D, textureID[4]);
    glBegin(GL_QUADS);
    glNormal3fv(normals[3]);
    glTexCoord2fv(texCoords[3][0]);
    glVertex3fv(vertices[4]);
    glTexCoord2fv(texCoords[3][1]);
    glVertex3fv(vertices[0]);
    glTexCoord2fv(texCoords[3][2]);
    glVertex3fv(vertices[3]);
    glTexCoord2fv(texCoords[3][3]);
    glVertex3fv(vertices[7]);
    glEnd();

    // Draw the top face with textureID coordinates and normal vectors
    glBindTexture(GL_TEXTURE_2D, textureID[5]);
    glBegin(GL_QUADS);
    glNormal3fv(normals[4]);
    glTexCoord2fv(texCoords[4][0]);
    glVertex3fv(vertices[3]);
    glTexCoord2fv(texCoords[4][1]);
    glVertex3fv(vertices[2]);
    glTexCoord2fv(texCoords[4][2]);
    glVertex3fv(vertices[6]);
    glTexCoord2fv(texCoords[4][3]);
    glVertex3fv(vertices[7]);
    glEnd();

    // Draw the bottom face with textureID coordinates and normal vectors
    glBindTexture(GL_TEXTURE_2D, textureID[6]);

    glBegin(GL_QUADS);
    glNormal3fv(normals[5]);
    glTexCoord2fv(texCoords[5][0]);
    glVertex3fv(vertices[0]);
    glTexCoord2fv(texCoords[5][1]);
    glVertex3fv(vertices[4]);
    glTexCoord2fv(texCoords[5][2]);
    glVertex3fv(vertices[5]);
    glTexCoord2fv(texCoords[5][3]);
    glVertex3fv(vertices[1]);
    glEnd();

    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}

void drawHand() {
    // Define the cube's vertices
    GLfloat vertices[8][3] = {
        {-0.2, -1.0, -0.2},
        {0.2, -1.0, -0.2},
        {0.2, 1.0, -0.2},
        {-0.2, 1.0, -0.2},
        {-0.2, -1.0, 0.2},
        {0.2, -1.0, 0.2},
        {0.2, 1.0, 0.2},
        {-0.2, 1.0, 0.2}
    };

    // Define the cube's normal vectors
    GLfloat normals[6][3] = {
        {0.0, 0.0, -1.0}, // Front face
        {0.0, 0.0, 1.0},  // Back face
        {1.0, 0.0, 0.0},  // Right face
        {-1.0, 0.0, 0.0}, // Left face
        {0.0, 1.0, 0.0},  // Top face
        {0.0, -1.0, 0.0}  // Bottom face
    };

    // Define the textureID coordinates for each face
    GLfloat texCoords[6][4][2] = {
        // Front face
        {{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}},
        // Back face
        {{1.0, 0.0}, {0.0, 0.0}, {0.0, 1.0}, {1.0, 1.0}},
        // Right face
        {{1.0, 0.0}, {0.0, 0.0}, {0.0, 1.0}, {1.0, 1.0}},
        // Left face
        {{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}},
        // Top face
        {{0.0, 1.0}, {0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}},
        // Bottom face
        {{0.0, 0.0}, {0.0, 1.0}, {1.0, 1.0}, {1.0, 0.0}}
    };

    glPushMatrix();
    glTranslatef(0.7, 0.5, 0);

    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, textureID[9]);  // Front face textureID
    glBegin(GL_QUADS);
    glBegin(GL_QUADS);
    glColor3f(0.55, 0.0, 0.0);
    glNormal3fv(normals[1]);
    glTexCoord2fv(texCoords[1][0]);
    glVertex3fv(vertices[5]);
    glTexCoord2fv(texCoords[1][1]);
    glVertex3fv(vertices[4]);
    glTexCoord2fv(texCoords[1][2]);
    glVertex3fv(vertices[7]);
    glTexCoord2fv(texCoords[1][3]);
    glVertex3fv(vertices[6]);
    glEnd();

    // Draw the front face with textureID coordinates and normal vectors
    glBegin(GL_QUADS);

    glNormal3fv(normals[0]);
    glTexCoord2fv(texCoords[0][0]);
    glVertex3fv(vertices[0]);
    glTexCoord2fv(texCoords[0][1]);
    glVertex3fv(vertices[1]);
    glTexCoord2fv(texCoords[0][2]);
    glVertex3fv(vertices[2]);
    glTexCoord2fv(texCoords[0][3]);
    glVertex3fv(vertices[3]);
    glEnd();


    // Draw the right face with textureID coordinates and normal vectors
    glBegin(GL_QUADS);

    glNormal3fv(normals[2]);
    glTexCoord2fv(texCoords[2][0]);
    glVertex3fv(vertices[1]);
    glTexCoord2fv(texCoords[2][1]);
    glVertex3fv(vertices[5]);
    glTexCoord2fv(texCoords[2][2]);
    glVertex3fv(vertices[6]);
    glTexCoord2fv(texCoords[2][3]);
    glVertex3fv(vertices[2]);
    glEnd();

    // Draw the left face with textureID coordinates and normal vectors
    glBegin(GL_QUADS);
    glNormal3fv(normals[3]);
    glTexCoord2fv(texCoords[3][0]);
    glVertex3fv(vertices[4]);
    glTexCoord2fv(texCoords[3][1]);
    glVertex3fv(vertices[0]);
    glTexCoord2fv(texCoords[3][2]);
    glVertex3fv(vertices[3]);
    glTexCoord2fv(texCoords[3][3]);
    glVertex3fv(vertices[7]);
    glEnd();

    // Draw the top face with textureID coordinates and normal vectors
    glBegin(GL_QUADS);
    glNormal3fv(normals[4]);
    glTexCoord2fv(texCoords[4][0]);
    glVertex3fv(vertices[3]);
    glTexCoord2fv(texCoords[4][1]);
    glVertex3fv(vertices[2]);
    glTexCoord2fv(texCoords[4][2]);
    glVertex3fv(vertices[6]);
    glTexCoord2fv(texCoords[4][3]);
    glVertex3fv(vertices[7]);
    glEnd();

    // Draw the bottom face with textureID coordinates and normal vectors

    glBegin(GL_QUADS);
    glNormal3fv(normals[5]);
    glTexCoord2fv(texCoords[5][0]);
    glVertex3fv(vertices[0]);
    glTexCoord2fv(texCoords[5][1]);
    glVertex3fv(vertices[4]);
    glTexCoord2fv(texCoords[5][2]);
    glVertex3fv(vertices[5]);
    glTexCoord2fv(texCoords[5][3]);
    glVertex3fv(vertices[1]);
    glEnd();

    glDisable(GL_TEXTURE_2D);

    glPopMatrix();

}

void drawHand_right()
{
    // Define the cube's vertices
    GLfloat vertices[8][3] = {
        {-0.2, -1.0, -0.2},
        {0.2, -1.0, -0.2},
        {0.2, 1.0, -0.2},
        {-0.2, 1.0, -0.2},
        {-0.2, -1.0, 0.2},
        {0.2, -1.0, 0.2},
        {0.2, 1.0, 0.2},
        {-0.2, 1.0, 0.2}
    };

    // Define the cube's normal vectors
    GLfloat normals[6][3] = {
        {0.0, 0.0, -1.0}, // Front face
        {0.0, 0.0, 1.0},  // Back face
        {1.0, 0.0, 0.0},  // Right face
        {-1.0, 0.0, 0.0}, // Left face
        {0.0, 1.0, 0.0},  // Top face
        {0.0, -1.0, 0.0}  // Bottom face
    };

    // Define the textureID coordinates for each face
    GLfloat texCoords[6][4][2] = {
        // Front face
        {{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}},
        // Back face
        {{1.0, 0.0}, {0.0, 0.0}, {0.0, 1.0}, {1.0, 1.0}},
        // Right face
        {{1.0, 0.0}, {0.0, 0.0}, {0.0, 1.0}, {1.0, 1.0}},
        // Left face
        {{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}},
        // Top face
        {{0.0, 1.0}, {0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}},
        // Bottom face
        {{0.0, 0.0}, {0.0, 1.0}, {1.0, 1.0}, {1.0, 0.0}}
    };

    glPushMatrix();
    glTranslatef(-0.7, 0.5, 0);
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, textureID[9]);
    glBegin(GL_QUADS);
    glColor3f(0.55, 0, 0);
    glNormal3fv(normals[1]);
    glTexCoord2fv(texCoords[1][0]);
    glVertex3fv(vertices[5]);
    glTexCoord2fv(texCoords[1][1]);
    glVertex3fv(vertices[4]);
    glTexCoord2fv(texCoords[1][2]);
    glVertex3fv(vertices[7]);
    glTexCoord2fv(texCoords[1][3]);
    glVertex3fv(vertices[6]);
    glEnd();

    // Draw the front face with textureID coordinates and normal vectors
    glBegin(GL_QUADS);

    glNormal3fv(normals[0]);
    glTexCoord2fv(texCoords[0][0]);
    glVertex3fv(vertices[0]);
    glTexCoord2fv(texCoords[0][1]);
    glVertex3fv(vertices[1]);
    glTexCoord2fv(texCoords[0][2]);
    glVertex3fv(vertices[2]);
    glTexCoord2fv(texCoords[0][3]);
    glVertex3fv(vertices[3]);
    glEnd();


    // Draw the right face with textureID coordinates and normal vectors
    glBegin(GL_QUADS);

    glNormal3fv(normals[2]);
    glTexCoord2fv(texCoords[2][0]);
    glVertex3fv(vertices[1]);
    glTexCoord2fv(texCoords[2][1]);
    glVertex3fv(vertices[5]);
    glTexCoord2fv(texCoords[2][2]);
    glVertex3fv(vertices[6]);
    glTexCoord2fv(texCoords[2][3]);
    glVertex3fv(vertices[2]);
    glEnd();

    // Draw the left face with textureID coordinates and normal vectors
    glBegin(GL_QUADS);
    glNormal3fv(normals[3]);
    glTexCoord2fv(texCoords[3][0]);
    glVertex3fv(vertices[4]);
    glTexCoord2fv(texCoords[3][1]);
    glVertex3fv(vertices[0]);
    glTexCoord2fv(texCoords[3][2]);
    glVertex3fv(vertices[3]);
    glTexCoord2fv(texCoords[3][3]);
    glVertex3fv(vertices[7]);
    glEnd();

    // Draw the top face with textureID coordinates and normal vectors
    glBegin(GL_QUADS);
    glNormal3fv(normals[4]);
    glTexCoord2fv(texCoords[4][0]);
    glVertex3fv(vertices[3]);
    glTexCoord2fv(texCoords[4][1]);
    glVertex3fv(vertices[2]);
    glTexCoord2fv(texCoords[4][2]);
    glVertex3fv(vertices[6]);
    glTexCoord2fv(texCoords[4][3]);
    glVertex3fv(vertices[7]);
    glEnd();

    // Draw the bottom face with textureID coordinates and normal vectors

    glBegin(GL_QUADS);
    glNormal3fv(normals[5]);
    glTexCoord2fv(texCoords[5][0]);
    glVertex3fv(vertices[0]);
    glTexCoord2fv(texCoords[5][1]);
    glVertex3fv(vertices[4]);
    glTexCoord2fv(texCoords[5][2]);
    glVertex3fv(vertices[5]);
    glTexCoord2fv(texCoords[5][3]);
    glVertex3fv(vertices[1]);
    glEnd();


    glPopMatrix();


}

void drawLeg_left()
{
    // Define the cube's vertices
    GLfloat vertices[8][3] = {
        {-0.2, -1.0, -0.2},
        {0.2, -1.0, -0.2},
        {0.2, 1.0, -0.2},
        {-0.2, 1.0, -0.2},
        {-0.2, -1.0, 0.2},
        {0.2, -1.0, 0.2},
        {0.2, 1.0, 0.2},
        {-0.2, 1.0, 0.2}
    };

    // Define the cube's normal vectors
    GLfloat normals[6][3] = {
        {0.0, 0.0, -1.0}, // Front face
        {0.0, 0.0, 1.0},  // Back face
        {1.0, 0.0, 0.0},  // Right face
        {-1.0, 0.0, 0.0}, // Left face
        {0.0, 1.0, 0.0},  // Top face
        {0.0, -1.0, 0.0}  // Bottom face
    };

    // Define the textureID coordinates for each face
    GLfloat texCoords[6][4][2] = {
        // Front face
        {{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}},
        // Back face
        {{1.0, 0.0}, {0.0, 0.0}, {0.0, 1.0}, {1.0, 1.0}},
        // Right face
        {{1.0, 0.0}, {0.0, 0.0}, {0.0, 1.0}, {1.0, 1.0}},
        // Left face
        {{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}},
        // Top face
        {{0.0, 1.0}, {0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}},
        // Bottom face
        {{0.0, 0.0}, {0.0, 1.0}, {1.0, 1.0}, {1.0, 0.0}}
    };

    glPushMatrix();
    glTranslatef(0.25, -0.9, 0);

    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, textureID[9]);

    glBegin(GL_QUADS);
    glColor3f(0.1, 0.1, 0.1);
    glNormal3fv(normals[1]);
    glTexCoord2fv(texCoords[1][0]);
    glVertex3fv(vertices[5]);
    glTexCoord2fv(texCoords[1][1]);
    glVertex3fv(vertices[4]);
    glTexCoord2fv(texCoords[1][2]);
    glVertex3fv(vertices[7]);
    glTexCoord2fv(texCoords[1][3]);
    glVertex3fv(vertices[6]);
    glEnd();

    // Draw the front face with textureID coordinates and normal vectors
    glBegin(GL_QUADS);

    glNormal3fv(normals[0]);
    glTexCoord2fv(texCoords[0][0]);
    glVertex3fv(vertices[0]);
    glTexCoord2fv(texCoords[0][1]);
    glVertex3fv(vertices[1]);
    glTexCoord2fv(texCoords[0][2]);
    glVertex3fv(vertices[2]);
    glTexCoord2fv(texCoords[0][3]);
    glVertex3fv(vertices[3]);
    glEnd();


    // Draw the right face with textureID coordinates and normal vectors
    glBegin(GL_QUADS);

    glNormal3fv(normals[2]);
    glTexCoord2fv(texCoords[2][0]);
    glVertex3fv(vertices[1]);
    glTexCoord2fv(texCoords[2][1]);
    glVertex3fv(vertices[5]);
    glTexCoord2fv(texCoords[2][2]);
    glVertex3fv(vertices[6]);
    glTexCoord2fv(texCoords[2][3]);
    glVertex3fv(vertices[2]);
    glEnd();

    // Draw the left face with textureID coordinates and normal vectors
    glBegin(GL_QUADS);
    glNormal3fv(normals[3]);
    glTexCoord2fv(texCoords[3][0]);
    glVertex3fv(vertices[4]);
    glTexCoord2fv(texCoords[3][1]);
    glVertex3fv(vertices[0]);
    glTexCoord2fv(texCoords[3][2]);
    glVertex3fv(vertices[3]);
    glTexCoord2fv(texCoords[3][3]);
    glVertex3fv(vertices[7]);
    glEnd();

    // Draw the top face with textureID coordinates and normal vectors
    glBegin(GL_QUADS);
    glNormal3fv(normals[4]);
    glTexCoord2fv(texCoords[4][0]);
    glVertex3fv(vertices[3]);
    glTexCoord2fv(texCoords[4][1]);
    glVertex3fv(vertices[2]);
    glTexCoord2fv(texCoords[4][2]);
    glVertex3fv(vertices[6]);
    glTexCoord2fv(texCoords[4][3]);
    glVertex3fv(vertices[7]);
    glEnd();

    // Draw the bottom face with textureID coordinates and normal vectors

    glBegin(GL_QUADS);
    glNormal3fv(normals[5]);
    glTexCoord2fv(texCoords[5][0]);
    glVertex3fv(vertices[0]);
    glTexCoord2fv(texCoords[5][1]);
    glVertex3fv(vertices[4]);
    glTexCoord2fv(texCoords[5][2]);
    glVertex3fv(vertices[5]);
    glTexCoord2fv(texCoords[5][3]);
    glVertex3fv(vertices[1]);
    glEnd();


    glPopMatrix();

}

void drawLeg_right()
{
    // Define the cube's vertices
    GLfloat vertices[8][3] = {
        {-0.2, -1.0, -0.2},
        {0.2, -1.0, -0.2},
        {0.2, 1.0, -0.2},
        {-0.2, 1.0, -0.2},
        {-0.2, -1.0, 0.2},
        {0.2, -1.0, 0.2},
        {0.2, 1.0, 0.2},
        {-0.2, 1.0, 0.2}
    };

    // Define the cube's normal vectors
    GLfloat normals[6][3] = {
        {0.0, 0.0, -1.0}, // Front face
        {0.0, 0.0, 1.0},  // Back face
        {1.0, 0.0, 0.0},  // Right face
        {-1.0, 0.0, 0.0}, // Left face
        {0.0, 1.0, 0.0},  // Top face
        {0.0, -1.0, 0.0}  // Bottom face
    };

    // Define the textureID coordinates for each face
    GLfloat texCoords[6][4][2] = {
        // Front face
        {{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}},
        // Back face
        {{1.0, 0.0}, {0.0, 0.0}, {0.0, 1.0}, {1.0, 1.0}},
        // Right face
        {{1.0, 0.0}, {0.0, 0.0}, {0.0, 1.0}, {1.0, 1.0}},
        // Left face
        {{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}},
        // Top face
        {{0.0, 1.0}, {0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}},
        // Bottom face
        {{0.0, 0.0}, {0.0, 1.0}, {1.0, 1.0}, {1.0, 0.0}}
    };

    glPushMatrix();
    glTranslatef(-0.25, -0.9, 0);

    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, textureID[9]);

    glBegin(GL_QUADS);
    glColor3f(0.1, 0.1, 0.1);
    glNormal3fv(normals[1]);
    glTexCoord2fv(texCoords[1][0]);
    glVertex3fv(vertices[5]);
    glTexCoord2fv(texCoords[1][1]);
    glVertex3fv(vertices[4]);
    glTexCoord2fv(texCoords[1][2]);
    glVertex3fv(vertices[7]);
    glTexCoord2fv(texCoords[1][3]);
    glVertex3fv(vertices[6]);
    glEnd();

    // Draw the front face with textureID coordinates and normal vectors
    glBegin(GL_QUADS);

    glNormal3fv(normals[0]);
    glTexCoord2fv(texCoords[0][0]);
    glVertex3fv(vertices[0]);
    glTexCoord2fv(texCoords[0][1]);
    glVertex3fv(vertices[1]);
    glTexCoord2fv(texCoords[0][2]);
    glVertex3fv(vertices[2]);
    glTexCoord2fv(texCoords[0][3]);
    glVertex3fv(vertices[3]);
    glEnd();


    // Draw the right face with textureID coordinates and normal vectors
    glBegin(GL_QUADS);

    glNormal3fv(normals[2]);
    glTexCoord2fv(texCoords[2][0]);
    glVertex3fv(vertices[1]);
    glTexCoord2fv(texCoords[2][1]);
    glVertex3fv(vertices[5]);
    glTexCoord2fv(texCoords[2][2]);
    glVertex3fv(vertices[6]);
    glTexCoord2fv(texCoords[2][3]);
    glVertex3fv(vertices[2]);
    glEnd();

    // Draw the left face with textureID coordinates and normal vectors
    glBegin(GL_QUADS);
    glNormal3fv(normals[3]);
    glTexCoord2fv(texCoords[3][0]);
    glVertex3fv(vertices[4]);
    glTexCoord2fv(texCoords[3][1]);
    glVertex3fv(vertices[0]);
    glTexCoord2fv(texCoords[3][2]);
    glVertex3fv(vertices[3]);
    glTexCoord2fv(texCoords[3][3]);
    glVertex3fv(vertices[7]);
    glEnd();

    // Draw the top face with textureID coordinates and normal vectors
    glBegin(GL_QUADS);
    glNormal3fv(normals[4]);
    glTexCoord2fv(texCoords[4][0]);
    glVertex3fv(vertices[3]);
    glTexCoord2fv(texCoords[4][1]);
    glVertex3fv(vertices[2]);
    glTexCoord2fv(texCoords[4][2]);
    glVertex3fv(vertices[6]);
    glTexCoord2fv(texCoords[4][3]);
    glVertex3fv(vertices[7]);
    glEnd();

    // Draw the bottom face with textureID coordinates and normal vectors

    glBegin(GL_QUADS);
    glNormal3fv(normals[5]);
    glTexCoord2fv(texCoords[5][0]);
    glVertex3fv(vertices[0]);
    glTexCoord2fv(texCoords[5][1]);
    glVertex3fv(vertices[4]);
    glTexCoord2fv(texCoords[5][2]);
    glVertex3fv(vertices[5]);
    glTexCoord2fv(texCoords[5][3]);
    glVertex3fv(vertices[1]);
    glEnd();


    glPopMatrix();

}

void background()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID[10]);

    glTranslatef(5.0, -10, 0.0);
    glBegin(GL_QUADS);
    glColor3ub(255, 255, 255);

    glTexCoord2f(0.0f, 0.0f); glVertex3f(40.0, 40.0, -5.0);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-40.0, 40.0, -5.0);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-40.0, 2.0, -5.0);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(40.0, 2.0, -5.0);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void cube()
{
    // Draw the cuboid
    glBegin(GL_QUADS);
    // Front face
    glColor3f(1.0, 0.0, 0.0); // Red color
    glVertex3f(-1.0 * scale, -0.2 * scale, 1.0 * scale); // Adjusted y-coordinate
    glVertex3f(1.0 * scale, -0.2 * scale, 1.0 * scale); // Adjusted y-coordinate
    glVertex3f(1.0 * scale, 0.2 * scale, 1.0 * scale); // Adjusted y-coordinate
    glVertex3f(-1.0 * scale, 0.2 * scale, 1.0 * scale); // Adjusted y-coordinate
    glColor3f(1.0, 0.0, 0.0); // Red color
    glVertex3f(-1.0 * scale, -0.2 * scale, -1.0 * scale); // Adjusted y-coordinate
    glVertex3f(1.0 * scale, -0.2 * scale, -1.0 * scale); // Adjusted y-coordinate
    glVertex3f(1.0 * scale, 0.2 * scale, -1.0 * scale); // Adjusted y-coordinate
    glVertex3f(-1.0 * scale, 0.2 * scale, -1.0 * scale); // Adjusted y-coordinate
    // Right face
    glColor3f(0.0, 0.0, 1.0); // Blue color
    glVertex3f(1.0 * scale, -0.2 * scale, -1.0 * scale); // Adjusted y-coordinate
    glVertex3f(1.0 * scale, -0.2 * scale, 1.0 * scale); // Adjusted y-coordinate
    glVertex3f(1.0 * scale, 0.2 * scale, 1.0 * scale); // Adjusted y-coordinate
    glVertex3f(1.0 * scale, 0.2 * scale, -1.0 * scale); // Adjusted y-coordinate
    glColor3f(0.0, 0.0, 1.0); // Blue color
    glVertex3f(-1.0 * scale, -0.2 * scale, -1.0 * scale); // Adjusted y-coordinate
    glVertex3f(-1.0 * scale, -0.2 * scale, 1.0 * scale); // Adjusted y-coordinate
    glVertex3f(-1.0 * scale, 0.2 * scale, 1.0 * scale); // Adjusted y-coordinate
    glVertex3f(-1.0 * scale, 0.2 * scale, -1.0 * scale); // Adjusted y-coordinate
    // Top face
    glColor3ub(192, 192, 192); // Grey color
    glVertex3f(-1.0 * scale, 0.2 * scale, 1.0 * scale); // Adjusted y-coordinate
    glVertex3f(1.0 * scale, 0.2 * scale, 1.0 * scale); // Adjusted y-coordinate
    glVertex3f(1.0 * scale, 0.2 * scale, -1.0 * scale); // Adjusted y-coordinate
    glVertex3f(-1.0 * scale, 0.2 * scale, -1.0 * scale); // Adjusted y-coordinate
    // Bottom face
    glColor3f(1.0, 0.0, 1.0); // Magenta color
    glVertex3f(-1.0 * scale, -0.2 * scale, 1.0 * scale); // Adjusted y-coordinate
    glVertex3f(1.0 * scale, -0.2 * scale, 1.0 * scale); // Adjusted y-coordinate
    glVertex3f(1.0 * scale, -0.2 * scale, -1.0 * scale); // Adjusted y-coordinate
    glVertex3f(-1.0 * scale, -0.2 * scale, -1.0 * scale); // Adjusted y-coordinate
    glEnd();
}

void drawCylinder(float radius, float height)
{
    const int numSegments = 30;
    const float segmentAngle = 2.0 * PI / numSegments;

    glBegin(GL_QUAD_STRIP);
    glColor3f(0.5, 0.5, 0.5);
    for (int i = 0; i <= numSegments; ++i)
    {
        float angle = segmentAngle * i;
        float x = radius * cos(angle);
        float z = radius * sin(angle);

        glVertex3f(x, height / 2.0, z);
        glVertex3f(x, -height / 2.0, z);
    }
    glEnd();
}

void drawLine3D(float startX, float startY, float startZ, float endX, float endY, float endZ)
{
    glBegin(GL_LINES);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(startX, startY, startZ);
    glVertex3f(endX, endY, endZ);
    glEnd();
}

void groupLines()
{
    drawLine3D(1.0 * scale, 1.0, 1.0 * scale, 1.0 * scale, 1.0, -1.0 * scale);
    drawLine3D(1.0 * scale, 1.0, 1.0 * scale, -1.0 * scale, 1.0, 1.0 * scale);
    drawLine3D(-1.0 * scale, 1.0, 1.0 * scale, -1.0 * scale, 1.0, -1.0 * scale);
    drawLine3D(1.0 * scale, 1.0, -1.0 * scale, -1.0 * scale, 1.0, -1.0 * scale);

    drawLine3D(1.0 * scale, 0.8, 1.0 * scale, 1.0 * scale, 0.8, -1.0 * scale);
    drawLine3D(1.0 * scale, 0.8, 1.0 * scale, -1.0 * scale, 0.8, 1.0 * scale);
    drawLine3D(-1.0 * scale, 0.8, 1.0 * scale, -1.0 * scale, 0.8, -1.0 * scale);
    drawLine3D(1.0 * scale, 0.8, -1.0 * scale, -1.0 * scale, 0.8, -1.0 * scale);

    drawLine3D(1.0 * scale, 1.2, 1.0 * scale, 1.0 * scale, 1.2, -1.0 * scale);
    drawLine3D(1.0 * scale, 1.2, 1.0 * scale, -1.0 * scale, 1.2, 1.0 * scale);
    drawLine3D(-1.0 * scale, 1.2, 1.0 * scale, -1.0 * scale, 1.2, -1.0 * scale);
    drawLine3D(1.0 * scale, 1.2, -1.0 * scale, -1.0 * scale, 1.2, -1.0 * scale);
}

void groupCylinder()
{
    glPushMatrix();
    glTranslatef(1.0 * scale, 1.0, 1.0 * scale);
    drawCylinder(0.03, 1.2);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.0 * scale, 1.0, -1.0 * scale);
    drawCylinder(0.03, 1.2);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.0 * scale, 1.0, -1.0 * scale);
    drawCylinder(0.03, 1.2);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.0 * scale, 1.0, 1.0 * scale);
    drawCylinder(0.03, 1.2);
    glPopMatrix();
}

void stage()
{
    glPushMatrix();
    //glTranslatef(0.5, 0, -10.0);
    cube();
    groupCylinder();
    groupLines();
    glPopMatrix();
}

void display() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    gluLookAt(0.0, 0.0, 30.0,  // camera position 
        0.0, 7.0, 0.0,   // camera direction 
        0.0, 1.0, 0.0);

    glEnable(GL_DEPTH_TEST);    // Enable depth testing
    glPushMatrix();
    glTranslatef(0, 0, cord_z);
    drawFace();
    drawBody();

    glPushMatrix();
    glTranslatef(0, 1, 0.0);
    glRotatef(180, 1.0f, 0.0f, 0.0f);
    glRotatef(angle, 1.0f, 0.0f, 0.0f);
    drawHand();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 1, 0.0);
    glRotatef(180, 1.0f, 0.0f, 0.0f);
    glRotatef(-angle, 1.0f, 0.0f, 0.0f);
    drawHand_right();
    glPopMatrix();

    glPushMatrix();
    glRotatef(-angle, 1.0f, 0.0f, 0.0f);
    drawLeg_left();
    glPopMatrix();

    glPushMatrix();
    glRotatef(angle, 1.0f, 0.0f, 0.0f);
    drawLeg_right();
    glPopMatrix();
    
    glPopMatrix();

    background();

    glFlush();
    glutSwapBuffers();
}

void idle() {
    
    DWORD start = GetTickCount64();
    while (GetTickCount64() - start < 1000 / FPS);
    
    if (angle >= -90.0 && rotate1 == false)
    {
        angle -= 5;
        if (angle == -90.0)
        {
            rotate1 = true;
        }
    }
    if (rotate1 == true)
    {
        angle += 5;
        if (angle == 90.0)
        {
            rotate1 = false;
        }
    }
    
    cord_z += 0.1;
    glutPostRedisplay();

}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)width / (double)height, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void init() {

    glEnable(GL_LIGHTING); // Enable lighting calculations
    glEnable(GL_LIGHT0);   // Enable light source 0

    GLfloat ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };  //illumination
    GLfloat diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };  //uniform
    GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; //reflection
    GLfloat position[] = { -0.6f, 0.0f, 0.8f, 0.0f }; 

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);     // Set ambient light properties
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);     // Set diffuse light properties
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);   // Set specular light properties
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    
}

void setupMaterial() {
    // Set material properties
    GLfloat matAmbient[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat matDiffuse[] = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat matSpecular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat matShininess[] = { 50.0 };

    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutCreateWindow("Solid Cube");
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    init();    // Set up lighting
    setupMaterial();    // Set up material properties
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutReshapeFunc(reshape);

    loadTexture();

    glutMainLoop();
    return 0;
}
