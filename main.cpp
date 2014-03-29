#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>

void keyboard(unsigned char key, int x, int y);
void display(void);

/* Function handling arrow keys */
void specialInput(int key, int x, int y);


int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutCreateWindow("GLUT Test");
  glutKeyboardFunc(&keyboard);
  glutSpecialFunc(&specialInput);
  glutDisplayFunc(&display);
  glutMainLoop();

  return EXIT_SUCCESS;
}


void keyboard(unsigned char key, int /*x*/, int /*y*/)
{
  switch (key)
  {
    case '\x1B':
      exit(EXIT_SUCCESS);
      break;
  }
}


void specialInput(int key, int x, int y)
{
  switch(key)
  {
    case GLUT_KEY_UP:
			//do something here
      break;
    case GLUT_KEY_DOWN:
      exit(EXIT_SUCCESS);
      break;
    case GLUT_KEY_LEFT:
      break;
    case GLUT_KEY_RIGHT:
      break;
  }
			
  glutPostRedisplay();
} 

void display()
{
  glClear(GL_COLOR_BUFFER_BIT);


    glColor3f(1.0f, 0.0f, 0.0f);
  glBegin(GL_POLYGON);
    glVertex3f(-0.5f, -0.5f, 0.0f);
    glVertex3f( 0.5f, -0.5f, 0.0f);
    glVertex3f( 0.5f,  0.5f, 0.0f);
    glVertex3f(-0.5f,  0.5f, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, 1.0f);
    glVertex3f( 0.5f, -0.5f, 1.0f);
    glVertex3f( 0.5f,  0.5f, 1.0f);
    glVertex3f(-0.5f,  0.5f, 1.0f);
  glEnd();

  glFlush();
}
