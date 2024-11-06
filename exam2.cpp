#include <GL/glut.h>

static int rightShoulderAngle = 0, rightElbowAngle = 0;
static int leftShoulderAngle = 0, leftElbowAngle = 0;
static int leftLegAngle = 0, rightLegAngle = 0;
static int robotRotationAngle = 0;

void Cube(GLdouble width, GLdouble height, GLdouble depth) {
    glPushMatrix();
    glScalef(width, height, depth);
    glutWireCube(1.0);
    glPopMatrix();
}

void Cone(GLdouble base, GLdouble height, GLint slices, GLint stacks) {
    glPushMatrix();
    glTranslatef(0.0f, height / 2, 0.0f); 
    glutWireCone(base, height, slices, stacks);
    glPopMatrix();
}

void special(int key, int, int) {
  switch (key) {
    case GLUT_KEY_LEFT:
      if (rightElbowAngle < 90) rightElbowAngle += 5;
      break;
    case GLUT_KEY_RIGHT:
      if (rightElbowAngle > -90) rightElbowAngle -= 5;
      break;
    case GLUT_KEY_UP:
      if (rightShoulderAngle < 90) rightShoulderAngle += 5;
      break;
    case GLUT_KEY_DOWN:
      if (rightShoulderAngle > -90) rightShoulderAngle -= 5;
      break;
    case GLUT_KEY_PAGE_UP:
      if (leftShoulderAngle < 90) leftShoulderAngle -= 5;
      break;
    case GLUT_KEY_PAGE_DOWN:
      if (leftShoulderAngle > -90) leftShoulderAngle += 5;
      break;
    case GLUT_KEY_HOME:
      if (leftElbowAngle < 90) leftElbowAngle -= 5;
      break;
    case GLUT_KEY_END:
      if (leftElbowAngle > -90) leftElbowAngle += 5;
      break;
    default:
      return;
  }
  glutPostRedisplay();
}

void keyboard(unsigned char key, int, int) {
    switch (key) {
        case 'a':
            if (leftLegAngle < 45) leftLegAngle += 5;
            break;
        case 's': 
            if (leftLegAngle > -45) leftLegAngle -= 5;
            break;
        case 'w':  
            if (rightLegAngle < 45) rightLegAngle += 5;
            break;
        case 'd': 
            if (rightLegAngle > -45) rightLegAngle -= 5;
            break;
        case 'q':  
            robotRotationAngle += 5;
            break;
        case 'e': 
            robotRotationAngle -= 5;
            break;
        default:
            return;
    }
    glutPostRedisplay();
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();

  glRotatef((GLfloat)robotRotationAngle, 0.0, 1.0, 0.0);

  glColor3f(0.5, 0.5, 0.5);
  Cube(1.0, 2.0, 0.5);

  // Правая рука 
  glPushMatrix();
  glTranslatef(0.5, 1.0, 0.0);
  glRotatef((GLfloat)rightShoulderAngle, 0.0, 0.0, 1.0);
  glTranslatef(0.8, 0.0, 0.0); 
  glColor3f(0.0, 0.0, 1.0);
  Cube(1.6, 0.3, 0.5);

  glTranslatef(0.8, 0.0, 0.0);
  glRotatef((GLfloat)rightElbowAngle, 0.0, 0.0, 1.0);
  glTranslatef(0.5, 0.0, 0.0);
  glColor3f(0.0, 1.0, 0.0);
  Cube(1.0, 0.3, 0.5);
  glPopMatrix();

  // Левая рука
  glPushMatrix();
  glTranslatef(-0.5, 1.0, 0.0);
  glRotatef((GLfloat)leftShoulderAngle, 0.0, 0.0, 1.0);
  glTranslatef(-0.8, 0.0, 0.0);
  glColor3f(0.0, 0.0, 1.0);
  Cube(1.6, 0.3, 0.5);

  glTranslatef(-0.8, 0.0, 0.0);
  glRotatef((GLfloat)leftElbowAngle, 0.0, 0.0, 1.0);
  glTranslatef(-0.5, 0.0, 0.0);
  glColor3f(0.0, 1.0, 0.0);
  Cube(1.0, 0.3, 0.5);
  glPopMatrix();

  // Голова
  glPushMatrix();
  glTranslatef(0.0, 2.0, 0.0);
  glColor3f(1.0, 0.8, 0.6);
  glutWireSphere(0.5, 10, 10);
  glPopMatrix();

  // Левая нога
  glPushMatrix();
  glTranslatef(-0.3, -1.5, 0.0);
  glRotatef((GLfloat)leftLegAngle, 1.0, 0.0, 0.0);
  glColor3f(0.6, 0.3, 0.0);
  Cube(0.3, 1.0, 0.3);
  glPopMatrix();

  // Правая нога
  glPushMatrix();
  glTranslatef(0.3, -1.5, 0.0);
  glRotatef((GLfloat)rightLegAngle, 1.0, 0.0, 0.0);
  glColor3f(0.6, 0.3, 0.0);
  Cube(0.3, 1.0, 0.3);
  glPopMatrix();

  // Куб
  glPushMatrix();
  glTranslatef(2.0, -1.5, 0.0); 
  glColor3f(0.8, 0.2, 0.2);
  Cube(1.0, 1.0, 1.0); 
  glPopMatrix();

  // Конус
  glPushMatrix();
  glTranslatef(2.0, -1.0, 0.0); 
  glRotatef(270, 1.0, 0.0, 0.0); 
  glColor3f(0.2, 0.8, 0.2); 
  Cone(0.5, 1.0, 10, 10);
  glPopMatrix();

  glPopMatrix();
  glFlush();
  glutSwapBuffers();
}

void reshape(GLint w, GLint h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(65.0, GLfloat(w)/GLfloat(h), 1.0, 20.0);
}

void init() {
  glShadeModel(GL_FLAT);
  glEnable(GL_DEPTH_TEST);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(1, 2, 8, 0, 0, 0, 0, 1, 0);
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(80, 80);
  glutInitWindowSize(800, 600);
  glutCreateWindow("3D Robot with Dual Arms");
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutSpecialFunc(special);
  glutKeyboardFunc(keyboard);
  init();
  glutMainLoop();
}
