#include <stdlib.h>
#include <GL/glut.h>

void keyboard(unsigned char key, int x, int y);
void display(void);
void reshape (int w, int h);
void specialInput(int key, int x, int y);

const float deltaPosX = 0.1;
const float deltaPosY = 0.1;

float posX = 0;
float posY = 0;

int main(int argc, char** argv)
{
  glutInitWindowSize(800, 600);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInit(&argc, argv);
  /*int mainWindow = */glutCreateWindow("RW3");
  glutKeyboardFunc(&keyboard);
  glutSpecialFunc(&specialInput);
  glutDisplayFunc(&display);
  glutReshapeFunc(&reshape);
  glEnable(GL_DEPTH_TEST);
  glShadeModel (GL_);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClearDepth(1.0f);
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
        posY += deltaPosY;
      break;
    case GLUT_KEY_DOWN:
        posY -= deltaPosY;
      break;
    case GLUT_KEY_LEFT:
        posX -= deltaPosX;
      break;
    case GLUT_KEY_RIGHT:
        posX += deltaPosX;
      break;
    default:
        return;
  }

  glutPostRedisplay();
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glColor3f (1.0, 1.0, 1.0);
   glLoadIdentity ();             /* clear the matrix */
           /* viewing transformation  */
   //gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
   glTranslatef(posX, posY, -5.0);
   glutWireCube (1.0);

  glutSwapBuffers();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(60.0, 1.0, 1.0, 20.0);
   glMatrixMode (GL_MODELVIEW);
}
