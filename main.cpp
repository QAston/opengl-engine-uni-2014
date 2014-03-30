#include <stdlib.h>
#include <GL/glut.h>

void keyboard(unsigned char key, int x, int y);
void display(void);
void reshape (int w, int h);
void specialInput(int key, int x, int y);


int main(int argc, char** argv)
{
  glutInitWindowSize(800, 600);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInit(&argc, argv);
  /*int mainWindow = */glutCreateWindow("RW3");
  glutKeyboardFunc(&keyboard);
  glutSpecialFunc(&specialInput);
  glutDisplayFunc(&display);
  glEnable(GL_DEPTH_TEST);
  glutMainLoop();

  return EXIT_SUCCESS;
}

// checks ascii input
void keyboard(unsigned char key, int /*x*/, int /*y*/)
{
  switch (key)
  {
    case '\x1B':
      exit(EXIT_SUCCESS);
      break;
    case ' ':
      break;
  }
}

// checks raw keyboard input
void specialInput(int key, int /*x*/, int /*y*/)
{
  switch(key)
  {
    case GLUT_KEY_UP:
      break;
    case GLUT_KEY_DOWN:
      break;
    case GLUT_KEY_LEFT:
      break;
    case GLUT_KEY_RIGHT:
      break;
    default:
        return;
  }

  glutPostRedisplay();
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glBegin(GL_LINE_LOOP);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, 0.0f);
    glVertex3f( 0.5f, -0.5f, 0.0f);
    glVertex3f( 0.5f,  0.5f, 0.0f);
    glVertex3f(-0.5f,  0.5f, 0.0f);
  glEnd();
  glBegin(GL_LINE_LOOP);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, -1.0f);
    glVertex3f( 0.5f, -0.5f, -1.0f);
    glVertex3f( 0.5f,  0.5f, -1.0f);
    glVertex3f(-0.5f,  0.5f, -1.0f);
  glEnd();

  glutSwapBuffers();
}

void reshape (int w, int h)
{
   /*glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluOrtho2D (0.0, (GLdouble) w, 0.0, (GLdouble) h);*/
}
