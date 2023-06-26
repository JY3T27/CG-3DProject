#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <gl/glu.h>
#include <GL/gl.h> 
#include <cmath>
#include "stb_image.h"

#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900
#define FPS	30
#define PI 3.141592653

const char* file_front_face = "C:/Users/HP/Desktop/cg images/front_face.jpg"; //"D:/Desktop/cg images/front_face.jpg";
const char* file_back_face = "C:/Users/HP/Desktop/cg images/back_face.jpg";  //"D:/Desktop/cg images/back_face.jpg";
const char* file_right_face = "C:/Users/HP/Desktop/cg images/right_face.jpg"; //"D:/Desktop/cg images/right_face.jpg";
const char* file_left_face = "C:/Users/HP/Desktop/cg images/left_face.jpg"; //"D:/Desktop/cg images/left_face.jpg";
const char* file_top_face = "C:/Users/HP/Desktop/cg images/top_face.jpg"; //"D:/Desktop/cg images/top_face.jpg";
const char* file_bottom_face = "C:/Users/HP/Desktop/cg images/bottom_face.jpg";  //"D:/Desktop/cg images/bottom_face.jpg";
const char* file_front_body = "C:/Users/HP/Desktop/cg images/front_body.jpg";  //"D:/Desktop/cg images/front_body.jpg";
const char* file_back_body = "C:/Users/HP/Desktop/cg images/back_body.jpg";  //"D:/Desktop/cg images/back_body.jpg";
const char* file_background = "C:/Users/HP/Desktop/cg images/tt.jpg";  //"D:/Desktop/cg images/tt.jpg";
const char* file_hand = "C:/Users/HP/Desktop/cg images/hand.jpg";  //"D:/Desktop/cg images/hand.jpg";

const float scale = 2.0f;
const float walkSpeed = 4.0f;
const float flySpeed = 0.1f;
const float rotateSpeed = 2.5f;
const float cheerSpeed = 5.0f;

GLuint textureID[20];
int width, height, channels;
float cameraX = 1.9f;
float cameraY = 0.5f;
float cameraZ = 1.9f;
float targetX = 0.0f;
float targetY = 0.8f;
float targetZ = 0.0f;

int timer1 = 0;
int cheerCount = 0;
float chinAngle = 100.0f;
float chinPosX = -11.2f;
float chinPosY = 5.5f;
float walkAngleL, walkAngleR;
float cheerL = 0.0f;
float cheerR = 0.0f;

bool walking = false;
bool rotate1 = true;
bool cheering = false;
bool rotate2 = true; 
bool rotate3 = true;

void display();
void reshape(int width, int height);
void init();
void setupMaterial();
void loadTexRepeats();
void loadTexture();
void idle();
void camera();

void stage();
void background();
void chinesePP();

void cube();
void drawCylinder(float radius, float height);
void drawLine3D(float startX, float startY, float startZ, float endX, float endY, float endZ);
void groupLines();
void groupCylinder();

void drawBody();
void drawFace();
void drawHand();
void drawHand_right();
void drawLeg_left();
void drawLeg_right();

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutCreateWindow("Solid Cube");
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    init();    // Set up lighting
    setupMaterial();    // Set up material properties
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    loadTexture();
    glutIdleFunc(idle);

    glutMainLoop();
    return 0;
}

void display()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    camera();  //camera function 

    chinesePP();
    background();
    stage();

    glFlush();
    glutSwapBuffers();
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)width / (double)height, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void init()
{
    GLfloat light_position[] = { 0.2f, 0.0f, 1.0f, 0.0f };  // Position of the light source
    GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };   // Diffuse color of the light
    GLfloat material_diffuse[] = { 0.7f, 0.7f, 0.7f, 1.0f }; // Diffuse color of the material

    //glClearColor(0.0f, 0.0f, 0.0f, 0.0f);     // Clear color to black
    glEnable(GL_COLOR_MATERIAL); // cheat!!!!
    glEnable(GL_DEPTH_TEST);                  // Enable depth testing
    glEnable(GL_LIGHTING);                    // Enable lighting
    glEnable(GL_LIGHT0);                      // Enable light source 0

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);    // Set light position
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);      // Set light diffuse color

    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse); // Set material diffuse color
}

void setupMaterial()
{
    // Set material properties
    GLfloat matAmbient[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat matDiffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat matSpecular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat matShininess[] = { 50.0 };

    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
}

void loadTexRepeats()
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void loadTexture()
{
    //flip image vertically
    stbi_set_flip_vertically_on_load(true);

    //textureID 1
    unsigned char* image = stbi_load(file_front_face, &width, &height, &channels, 3);
    glGenTextures(1, &textureID[1]);
    glBindTexture(GL_TEXTURE_2D, textureID[1]);
    loadTexRepeats();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    stbi_image_free(image);

    //textureID 2
    unsigned char* imageBack1 = stbi_load(file_back_face, &width, &height, &channels, 3);
    glGenTextures(1, &textureID[2]);
    glBindTexture(GL_TEXTURE_2D, textureID[2]);
    loadTexRepeats();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageBack1);
    stbi_image_free(imageBack1);

    //textureID 3
    unsigned char* imageBack2 = stbi_load(file_right_face, &width, &height, &channels, 3);
    glGenTextures(1, &textureID[3]);
    glBindTexture(GL_TEXTURE_2D, textureID[3]);
    loadTexRepeats();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageBack2);
    stbi_image_free(imageBack2);

    //textureID 4
    unsigned char* imageBack3 = stbi_load(file_left_face, &width, &height, &channels, 3);
    glGenTextures(1, &textureID[4]);
    glBindTexture(GL_TEXTURE_2D, textureID[4]);
    loadTexRepeats();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageBack3);
    stbi_image_free(imageBack3);

    //textureID 5
    unsigned char* imageBack4 = stbi_load(file_top_face, &width, &height, &channels, 3);
    glGenTextures(1, &textureID[5]);
    glBindTexture(GL_TEXTURE_2D, textureID[5]);
    loadTexRepeats();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageBack4);
    stbi_image_free(imageBack4);

    //textureID 6
    unsigned char* imageBack5 = stbi_load(file_bottom_face, &width, &height, &channels, 3);
    glGenTextures(1, &textureID[6]);
    glBindTexture(GL_TEXTURE_2D, textureID[6]);
    loadTexRepeats();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageBack5);
    stbi_image_free(imageBack5);

    unsigned char* imageBack6 = stbi_load(file_front_body, &width, &height, &channels, 3);
    glGenTextures(1, &textureID[7]);
    glBindTexture(GL_TEXTURE_2D, textureID[7]);
    loadTexRepeats();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageBack6);
    stbi_image_free(imageBack6);

    unsigned char* imageBack7 = stbi_load(file_back_body, &width, &height, &channels, 3);
    glGenTextures(1, &textureID[8]);
    glBindTexture(GL_TEXTURE_2D, textureID[8]);
    loadTexRepeats();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageBack7);
    stbi_image_free(imageBack7);

    unsigned char* imageBack8 = stbi_load(file_background, &width, &height, &channels, 3);
    glGenTextures(1, &textureID[9]);
    glBindTexture(GL_TEXTURE_2D, textureID[9]);
    loadTexRepeats();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageBack8);
    stbi_image_free(imageBack8);

    unsigned char* imageBack9 = stbi_load(file_hand, &width, &height, &channels, 3);
    glGenTextures(1, &textureID[10]);
    glBindTexture(GL_TEXTURE_2D, textureID[10]);
    loadTexRepeats();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageBack9);
    stbi_image_free(imageBack9);
}

void idle()
{
    DWORD start = GetTickCount64();
    while (GetTickCount64() - start < 1000 / FPS);

    if (chinPosX < -1.2f && chinPosY > 0.5)
    {
       chinPosX += 2 * flySpeed;
       chinPosY -= flySpeed;
       walking = true;
    }
    else
    {
       walking = false;
       cheering = true;
    }

    if (walking == true)
    {
        if (rotate1 == true)
        {
            walkAngleL += walkSpeed;
            walkAngleR -= walkSpeed;
            if (walkAngleL >= 50.0)
            {
                rotate1 = false;
            }
        }
        else
        {
            walkAngleL -= walkSpeed;
            walkAngleR += walkSpeed;
            if (walkAngleL <= -50.0)
            {
                rotate1 = true;
            }
        }
    }
    else
    {
        walkAngleL = 0.0f;
        walkAngleR = 0.0f;
    }

    if (cheerCount >= 3)
    {
        cheering = false;
    }
    
    if (cheering == true)
    {
        if (rotate2 == true)
        {
            chinAngle -= rotateSpeed;
            if (chinAngle <= 0.0f)
            {
                cheerCount += 1;
                rotate2 = false;
            }
        }
        else
        {
            chinAngle += rotateSpeed;
            if (chinAngle >= 100.0f)
            {
                cheerCount += 1;
                rotate2 = true;
            }
        }

        if (rotate3 == true)
        {
            cheerL += cheerSpeed;
            cheerR -= cheerSpeed;
            if (cheerL >= 120.0f)
            {
                rotate3 = false;
            }
        }
        else
        {
            cheerL -= cheerSpeed;
            cheerR += cheerSpeed;
            if (cheerL <= 0.0f)
            {
                rotate3 = true;
            }
        }
    }
    else
    {
        chinAngle = 100.0f;
        cheerL = 0.0f;
        cheerR = 0.0f;
    }

    


    glutPostRedisplay();
}

void camera()
{
    gluLookAt(cameraX, cameraY, cameraZ,    // camera position
        targetX, targetY, targetZ,  // target position
        0.0, 1.0, 0.0);             // up vector
}


void stage()
{
    glPushMatrix();
    glTranslatef(0.0, -0.5, 0.0);
    cube();
    groupCylinder();
    groupLines();
    glPopMatrix();
}

void background()
{
    glPushMatrix();
    glTranslatef(0.0f, 2, 0.0f);
    glColor3ub(255, 255, 255);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID[9]);  // Front face textureID
    glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0, 1.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-7.0, -5.0, 1.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(3.0, -5.0, -5.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(3.0, 3.0, -5.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(-7.0, 3.0, 1.0);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}

void chinesePP()
{
    glPushMatrix();
    glTranslated(chinPosX, chinPosY, 1.0);
    glScaled(0.3, 0.3, 0.3);
    glTranslated(-chinPosX, -chinPosY, -1.0);
    glRotated(chinAngle, 0.0, 1.0, 0.0);
    

    drawFace();
    drawBody();

    //Left Hand 
    glPushMatrix();
    glTranslated(0.65, 1.31, 0.0);
    glRotatef(walkAngleL, 1.0f, 0.0f, 0.0f); //movement x direction  
    glRotated(cheerL, 0.0, 0.0, 1.0);        //movement z direction  120
    glTranslated(-0.65, -1.31, 0.0);
    drawHand();
    glPopMatrix();

    //Right Hand 
    glPushMatrix();
    glTranslated(-0.63, 1.31, 0.0);
    glRotatef(walkAngleR, 1.0f, 0.0f, 0.0f); //movement x direction  
    glRotated(cheerR, 0.0, 0.0, 1.0);          //movement z direction  120
    glTranslated(0.63, -1.31, 0.0);
    drawHand_right();
    glPopMatrix();

    //Left Leg
    glPushMatrix();
    glTranslated(-0.63, 0.0, 0.0);
    glRotatef(walkAngleR, 1.0f, 0.0f, 0.0f); //movement x direction  
    glTranslated(0.63, 0.0, 0.0);
    drawLeg_left();
    glPopMatrix();

    //Right Leg
    glPushMatrix();
    glTranslated(0.65, 0.0, 0.0);
    glRotatef(walkAngleL, 1.0f, 0.0f, 0.0f); //movement x direction  
    glTranslated(-0.65, 0.0, 0.0);
    drawLeg_right();
    glPopMatrix();

    glPopMatrix();
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

void drawBody()
{
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

    glDisable(GL_TEXTURE_2D);
    // Disable textureID mapping

    //glColor3ub(185, 0, 0);
    // Draw the right face with textureID coordinates
    glBegin(GL_QUADS);
    glColor3f(1.0, 0.0, 0.0); // Red color
    //glNormal3fv(normals[1]);
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
    glBegin(GL_QUADS);
    glColor3f(1.0, 0.0, 0.0); // Red color
    //glNormal3fv(normals[3]);
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
    glColor3f(1.0, 0.0, 0.0); // Red color
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
    glColor3f(1.0, 0.0, 0.0); // Red color
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

    glPopMatrix();
}

void drawFace()
{
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

    // Draw the front face with textureID coordinates and normal vectors
    glBindTexture(GL_TEXTURE_2D, textureID[2]);  // Back face textureID
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

void drawHand()
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
    glTranslatef(0.7, 0.7, 0);
    glScaled(1.0, 0.8, 1.0);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID[10]);
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
    glTranslatef(-0.7, 0.7, 0);
    glScaled(1.0, 0.8, 1.0);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID[10]);
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

    glDisable(GL_TEXTURE_2D);

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
    glTranslatef(0.25, -0.6, 0);
    glScaled(1.0, 0.8, 1.0);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID[10]);
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

    glDisable(GL_TEXTURE_2D);

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
    glTranslatef(-0.25, -0.6, 0);
    glScaled(1.0, 0.8, 1.0);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID[10]);
    glBegin(GL_QUADS);
    //glColor3f(0.1, 0.1, 0.1);
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
