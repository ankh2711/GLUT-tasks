#include <GL/glut.h>
#include <cmath>

// Функция для отрисовки каркасной сферы
void myWireSphere(GLfloat radius, int slices, int stacks) {
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    glutWireSphere(radius, slices, stacks);
    glPopMatrix();
}

// Функция для отрисовки кольца
void myRing(GLfloat innerRadius, GLfloat outerRadius, int slices) {
    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i <= slices; i++) {
        float angle = (2.0f * M_PI * i) / slices;
        float x = cos(angle);
        float y = sin(angle);

        // Внешняя часть кольца
        glVertex3f(x * outerRadius, 0, y * outerRadius);
        // Внутренняя часть кольца
        glVertex3f(x * innerRadius, 0, y * innerRadius);
    }
    glEnd();
}

// Инициализация времени модели
static int year = 0, day = 0;

// Функция отрисовки
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();

    // Солнце
    glColor3f(1.0, 1.0, 0.0);
    myWireSphere(1.0, 15, 15); 

    // Меркурий
    glPushMatrix();
    glRotatef((GLfloat)year, 0.0, 1.0, 0.0);
    glTranslatef(1.5, 0.0, 0.0); 
    glRotatef((GLfloat)day, 0.0, 1.0, 0.0);
    glColor3f(0.5, 0.5, 0.5);
    myWireSphere(0.1, 15, 15); 
    glPopMatrix();

    // Венера
    glPushMatrix();
    glRotatef((GLfloat)year + 30, 0.0, 1.0, 0.0);
    glTranslatef(2.0, 0.0, 0.0); 
    glRotatef((GLfloat)day, 0.0, 1.0, 0.0);
    glColor3f(1.0, 0.5, 0.0); 
    myWireSphere(0.2, 15, 15); 
    glPopMatrix();

    // Земля
    glPushMatrix();
    glRotatef((GLfloat)year + 60, 0.0, 1.0, 0.0);
    glTranslatef(3.0, 0.0, 0.0); 
    glRotatef((GLfloat)day, 0.0, 1.0, 0.0);
    glColor3f(0.0, 0.5, 1.0); 
    myWireSphere(0.3, 15, 15); 
    glPopMatrix();

    // Марс
    glPushMatrix();
    glRotatef((GLfloat)year + 90, 0.0, 1.0, 0.0);
    glTranslatef(4.0, 0.0, 0.0); 
    glRotatef((GLfloat)day, 0.0, 1.0, 0.0);
    glColor3f(1.0, 0.0, 0.0);
    myWireSphere(0.2, 15, 15); 
    glPopMatrix();

    // Юпитер
    glPushMatrix();
    glRotatef((GLfloat)year + 120, 0.0, 1.0, 0.0);
    glTranslatef(5.0, 0.0, 0.0); 
    glRotatef((GLfloat)day, 0.0, 1.0, 0.0);
    glColor3f(1.0, 0.7, 0.5);
    myWireSphere(0.5, 15, 15); 
    glPopMatrix();

    // Сатурн
    glPushMatrix();
    glRotatef((GLfloat)year + 150, 0.0, 1.0, 0.0);
    glTranslatef(6.0, 0.0, 0.0);
    glRotatef((GLfloat)day, 0.0, 1.0, 0.0);
    glColor3f(1.0, 1.0, 0.5); 
    myWireSphere(0.5, 15, 15); 

    glColor3f(1.0, 1.0, 0.8); 
    myRing(0.55, 0.75, 30);
    glPopMatrix();

    // Уран
    glPushMatrix();
    glRotatef((GLfloat)year + 210, 0.0, 1.0, 0.0);
    glTranslatef(7.0, 0.0, 0.0); 
    glRotatef((GLfloat)day, 0.0, 1.0, 0.0);
    glColor3f(0.5, 1.0, 1.0);
    myWireSphere(0.4, 15, 15); 

    glColor3f(0.5, 0.7, 0.9); 
    myRing(0.45, 0.65, 30); 
    glPopMatrix();

    // Нептун
    glPushMatrix();
    glRotatef((GLfloat)year + 240, 0.0, 1.0, 0.0);
    glTranslatef(8.0, 0.0, 0.0); 
    glRotatef((GLfloat)day, 0.0, 1.0, 0.0);
    glColor3f(0.0, 0.0, 1.0); 
    myWireSphere(0.4, 15, 15); 
    glPopMatrix();

    glPopMatrix();
    glFlush();
    glutSwapBuffers();
}

static GLfloat u = 0.0; 
static GLfloat du = 0.05;

void timer(int v) {
    u += du;
    day = (day + 1) % 360;
    year = (year + 1) % 360;

    // Перемещение камеры
    GLfloat cometX = 8 * cos(u) + 5;
    GLfloat cometY = 3 * sin(u) + 1;
    GLfloat cometZ = 5 * sin(u / 2.0);

    glLoadIdentity();
    gluLookAt(cometX, cometY, cometZ, 0, 0, 0, 0, 1, 0);
    glutPostRedisplay();
    glutTimerFunc(1000 / 30, timer, v); 
}

// Обработка изменения размера окна
void reshape(GLint w, GLint h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 40.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Solar System");
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(1000 / 30, timer, 0);
    glutMainLoop();
    return 0;
}
