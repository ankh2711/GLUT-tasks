#include <GL/glut.h>
#include <cstdio>   
#include <cmath>   

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

bool initGL()
{
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(0.53f, 0.81f, 0.92f, 1.f); 

    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        printf("Error initializing OpenGL! %s\n");
        return false;
    }
    return true;
}

void drawCircle(float x, float y, float radius, int segments)
{
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); 
    for (int i = 0; i <= segments; i++)
    {
        float angle = 2.0f * 3.14159f * i / segments;
        glVertex2f(x + cos(angle) * radius, y + sin(angle) * radius);
    }
    glEnd();
}

void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3)
{
    glBegin(GL_TRIANGLES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glEnd();
}

void drawPetal(float x, float y, float angle)
{
    float petalLength = 75.0f;
    float petalWidth = 40.0f; 

    // Рисуем верхнюю часть лепестка
    glBegin(GL_TRIANGLES);
    glVertex2f(x, y);
    glVertex2f(x + petalLength * cos(angle), y + petalLength * sin(angle));
    glVertex2f(x + petalWidth * cos(angle + M_PI / 6), y + petalWidth * sin(angle + M_PI / 6));
    glEnd();

    // Рисуем нижнюю часть лепестка
    glBegin(GL_TRIANGLES);
    glVertex2f(x, y);
    glVertex2f(x + petalLength * cos(angle), y + petalLength * sin(angle));
    glVertex2f(x + petalWidth * cos(angle - M_PI / 6), y + petalWidth * sin(angle - M_PI / 6));
    glEnd();
}

void drawFlower(float x, float y)
{
    glColor3f(1.0f, 0.0f, 0.0f);
    for (int i = 0; i < 5; i++) {
        float angle = i * 2.0f * M_PI / 5; 
        drawPetal(x, y, angle);
    }

    // Рисуем центр цветка
    glColor3f(1.0f, 1.0f, 0.0f); 
    drawCircle(x, y, 20.0f, 30);
}
void drawFish(float x, float y, float radius)
{
    glBegin(GL_POLYGON);
    glColor3f(1.f, 1.f, 1.f);
    for (int i = 0; i < 5; i++)
    {
        float angle = i * 4.0f * 3.14159f / 5.0f; 
        glVertex2f(x + cos(angle) * radius, y + sin(angle) * radius);
    }
    glEnd();

    // Рисуем глаз
    float eyeOffsetX = radius * 0.4f;
    float eyeOffsetY = radius * 0.3f;
    float eyeRadius = radius * 0.1f;

    glColor3f(0.f, 0.f, 0.f); 
    glBegin(GL_POLYGON); 
    for (int i = 0; i < 20; i++)
    {
        float angle = 2.0f * 3.14159f * i / 20;
        glVertex2f(x + eyeOffsetX + cos(angle) * eyeRadius, y - eyeOffsetY + sin(angle) * eyeRadius);
    }
    glEnd();
}

void render()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Рисуем голову (круг)
    glPushMatrix();
    glTranslatef(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.3f, 0.f); 
    glColor3f(1.f, 0.8f, 0.6f);
    float radius = 30.0f;
    int numSegments = 100;
    glBegin(GL_POLYGON);
    for (int i = 0; i < numSegments; i++)
    {
        float angle = 2.0f * 3.14159f * i / numSegments;
        glVertex2f(cos(angle) * radius, sin(angle) * radius);
    }
    glEnd();
    glPopMatrix();

    // Рисуем шею (прямоугольник)
    glPushMatrix();
    glTranslatef(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.05f, 0.f);
    glColor3f(1.f, 0.8f, 0.6f); 
    glBegin(GL_QUADS);
        glVertex2f(-10.f, -10.f);
        glVertex2f(10.f, -10.f);
        glVertex2f(10.f, 10.f);
        glVertex2f(-10.f, 10.f);
    glEnd();
    glPopMatrix();

    // Рисуем тело (прямоугольник)
    glPushMatrix();
    glTranslatef(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 1.7f, 0.f); 
    glColor3f(0.f, 0.f, 1.f);  
    glBegin(GL_QUADS);
        glVertex2f(-20.f, -50.f);
        glVertex2f(20.f, -50.f);
        glVertex2f(20.f, 50.f);
        glVertex2f(-20.f, 50.f);
    glEnd();
    glPopMatrix();

    // Рисуем левую руку
    glPushMatrix();
    glTranslatef(SCREEN_WIDTH / 2.f - 30.f, SCREEN_HEIGHT / 1.7f, 0.f); 
    glRotatef(30.f, 0.f, 0.f, 1.f); 
    glColor3f(1.f, 0.8f, 0.6f);
    glBegin(GL_QUADS);
        glVertex2f(-10.f, -20.f);
        glVertex2f(10.f, -20.f);
        glVertex2f(10.f, 20.f);
        glVertex2f(-10.f, 20.f);
    glEnd();
    glPopMatrix();

    // Рисуем правую руку
    glPushMatrix();
    glTranslatef(SCREEN_WIDTH / 2.f + 30.f, SCREEN_HEIGHT / 1.7f, 0.f); 
    glRotatef(-30.f, 0.f, 0.f, 1.f); 
    glColor3f(1.f, 0.8f, 0.6f);
    glBegin(GL_QUADS);
        glVertex2f(-10.f, -20.f);
        glVertex2f(10.f, -20.f);
        glVertex2f(10.f, 20.f);
        glVertex2f(-10.f, 20.f);
    glEnd();
    glPopMatrix();

    // Рисуем левую ногу
    glPushMatrix();
    glTranslatef(SCREEN_WIDTH / 2.f - 10.f, SCREEN_HEIGHT / 1.5f, 0.f); 
    glRotatef(20.f, 0.f, 0.f, 1.f); 
    glColor3f(1.f, 0.f, 0.f); 
    glBegin(GL_QUADS);
        glVertex2f(-10.f, 0.f);
        glVertex2f(10.f, 0.f);
        glVertex2f(10.f, 50.f);
        glVertex2f(-10.f, 50.f);
    glEnd();
    glPopMatrix();

    // Рисуем правую ногу
    glPushMatrix();
    glTranslatef(SCREEN_WIDTH / 2.f + 10.f, SCREEN_HEIGHT / 1.5f, 0.f); 
    glRotatef(-20.f, 0.f, 0.f, 1.f); 
    glColor3f(1.f, 0.f, 0.f);
    glBegin(GL_QUADS);
        glVertex2f(-10.f, 0.f);
        glVertex2f(10.f, 0.f);
        glVertex2f(10.f, 50.f);
        glVertex2f(-10.f, 50.f);
    glEnd();
    glPopMatrix();

    // Рисуем ствол дерева (прямоугольник)
    glPushMatrix();
    glTranslatef(SCREEN_WIDTH / 4.f, SCREEN_HEIGHT / 1.7f, 0.f); 
    glColor3f(0.55f, 0.27f, 0.07f); 
    glBegin(GL_QUADS);
        glVertex2f(-10.f, -40.f);
        glVertex2f(10.f, -40.f);
        glVertex2f(10.f, 40.f);
        glVertex2f(-10.f, 40.f);
    glEnd();
    glPopMatrix();

    // Рисуем листву дерева (многоугольник)
    glPushMatrix();
    glTranslatef(SCREEN_WIDTH / 4.f, SCREEN_HEIGHT / 2.1f, 0.f); 
    glColor3f(0.f, 0.5f, 0.f); 
    glBegin(GL_POLYGON);
    int treeSegments = 8;
    float foliageRadius = 50.f;
    for (int i = 0; i < treeSegments; i++)
    {
        float angle = 2.0f * 3.14159f * i / treeSegments;
        glVertex2f(cos(angle) * foliageRadius, sin(angle) * foliageRadius);
    }
    glEnd();
    glPopMatrix();

    // Рисуем рыбы
    drawFish(100.f, 100.f, 20.f); 
    drawFish(200.f, 80.f, 20.f);   
    drawFish(300.f, 120.f, 20.f); 

    drawFlower(SCREEN_WIDTH / 1.3f, SCREEN_HEIGHT / 2.0f);
    
    glutSwapBuffers();
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutCreateWindow("2D Figure with Tree and Larger Stars");
    if (!initGL())
    {
        printf("Unable to initialize graphics library!\n");
        return 1;
    }
    glutDisplayFunc(render);
    glutMainLoop();
    return 0;
}
