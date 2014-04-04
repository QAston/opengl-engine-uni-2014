#include <cstdlib>
#include <GL/glut.h>
#include <AL/alut.h>
#include <random>
#include <chrono>
#include <iostream>

using namespace std;

void keyboard(unsigned char key, int x, int y);
void display(void);
void reshape (int w, int h);
void specialInput(int key, int x, int y);
static void playFile(const char *filename);

const float deltaPosX = 0.1;
const float deltaPosY = 0.1;

float posX = 0;
float posY = 0;

GLint cubeVerticles[] = {0, 0, 0,
                          1, 0, 0,
                          1, 1, 0,
                          0, 1, 0,
                          0, 0, 1,
                          1, 0, 1,
                          1, 1, 1,
                          0, 1, 1};

GLfloat cubeColors[24];

GLubyte frontIndices[] = {4, 5, 6, 7};
GLubyte rightIndices[] = {1, 2, 6, 5};
GLubyte bottomIndices[] = {0, 1, 5, 4};
GLubyte backIndices[] = {0, 3, 2, 1};
GLubyte leftIndices[] = {0, 4, 7, 3};
GLubyte topIndices[] = {2, 3, 7, 6};

int main(int argc, char** argv)
{
  glutInitWindowSize(800, 600);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInit(&argc, argv);
  alutInit(&argc, argv);
  /*int mainWindow = */glutCreateWindow("RW3");
  glutKeyboardFunc(&keyboard);
  glutSpecialFunc(&specialInput);
  glutDisplayFunc(&display);
  glutReshapeFunc(&reshape);
  glEnable(GL_DEPTH_TEST);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClearDepth(1.0f);
  // init colors
    std::mt19937 generator;
    generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_real_distribution<float> distribution(0.0, 1.0);
    for(int i = 0; i < 24; ++i)
    {
        cubeColors[i] = distribution(generator);
    }
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
      playFile("alert.wav");
      break;
    default:
        return;
  }
  glutPostRedisplay();
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

  glEnableClientState (GL_COLOR_ARRAY);
  glEnableClientState (GL_VERTEX_ARRAY);
  glColorPointer (3, GL_FLOAT, 0, cubeColors);
  glVertexPointer (3, GL_INT, 0, cubeVerticles);
   glPolygonMode(GL_FRONT, GL_FILL);
   glPolygonMode(GL_BACK, GL_LINE);
   glFrontFace(GL_CCW);

   glLoadIdentity ();
   glTranslatef(posX, posY, -3.0);

    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, frontIndices);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, rightIndices);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, bottomIndices);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, backIndices);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, leftIndices);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, topIndices);

  glutSwapBuffers();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(90.0, w/(float)h, 1.0, 20.0);
   glMatrixMode (GL_MODELVIEW);
}

static void playFile (const char *fileName)
{
  ALuint buffer;
  ALuint source;
  ALenum error;
  ALint status;

  /* Create an AL buffer from the given sound file. */
  buffer = alutCreateBufferFromFile (fileName);
  if (buffer == AL_NONE)
  {
      error = alutGetError ();
      cerr <<  "Error loading file: " << alutGetErrorString(error) << endl;
      alutExit ();
      exit (EXIT_FAILURE);
  }

  /* Generate a single source, attach the buffer to it and start playing. */
  alGenSources (1, &source);
  alSourcei (source, AL_BUFFER, buffer);
  alSourcePlay (source);

  /* Normally nothing should go wrong above, but one never knows... */
  error = alGetError ();
  if (error != ALUT_ERROR_NO_ERROR)
  {
      cerr << alGetString(error) << endl;
      alutExit ();
      exit (EXIT_FAILURE);
  }

  /* Check every 0.1 seconds if the sound is still playing. */
  do
  {
      alutSleep (0.1f);
      alGetSourcei (source, AL_SOURCE_STATE, &status);
  }
  while (status == AL_PLAYING);
}