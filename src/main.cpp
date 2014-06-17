#include <cstdlib>
#include <GL/glut.h>
#include <AL/alut.h>
#include <random>
#include <chrono>
#include <iostream>
#include <cstring>
#include <vector>

#include <memory>
#include "cube.h"
#include "fpscamera.h"
#include "inputmanagerglut.h"
#include "displaymanagerglut.h"
#include "unique.h"
#include "soundsourceglut.h"
#include "scenepos.h"
#include "sceneloader.h"
#include "objectmanagerglut.h"
#include "mover.h"
#include "aabbcollisionmgr.h"
#include "worldobject.h"

using namespace std;

void reshape (int w, int h);

ALuint loadAudioFile(const char *fileName);
bool texturing = false;

int main(int argc, char** argv)
{
    // wire up the entire system
  glutInit(&argc, argv);
  alutInit(&argc, argv);

  glutInitWindowSize(800, 600);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

  /*int mainWindow = */glutCreateWindow("RW5");

      glutWarpPointer(400, 300);
      glutReshapeFunc(&reshape);

  ALuint alert = loadAudioFile("alert.wav");

  unique_ptr<SoundSource> cubeSound = make_unique<SoundSourceGLUT>(alert);
  shared_ptr<SceneObject> scene{ loadScene("objFiles/szczala.json")};
  shared_ptr<SceneObject> object2{ loadScene("objFiles/arrows.json")};

  shared_ptr<Cube::Input> cubeSoundInput = make_shared<Cube::Input>(nullptr, cubeSound.get());

  shared_ptr<FPSCamera> camera = make_shared<FPSCamera>(10, 0, 0, 0, 90);
  InputManager* inputManager = InputManagerGLUT::get();
  DisplayManager* displayManager = DisplayManagerGLUT::get();
  ObjectManager* objectManager = ObjectManagerGLUT::get();
  displayManager->init(camera);
  shared_ptr<FPSCamera::Input> cameraInput = make_shared<FPSCamera::Input>(camera);

  inputManager->registerObject(cameraInput);
  inputManager->registerObject(cubeSoundInput);

  objectManager->registerObject(scene);

  shared_ptr<WorldObject> wobj1 = make_shared<WorldObject>(object2);
  ScenePos pos1 = ScenePos(0, 0, 0, -90, 0, 90);
  pos2.moveForward(3);
  wobj1->moveTo(pos1);

  shared_ptr<WorldObject> wobj2 = make_shared<WorldObject>(scene);
  ScenePos pos2 = ScenePos(0, 0, 0, -90, 0, 90);

  wobj2->moveTo(pos2);

  shared_ptr<Mover> collidingMover1 = make_shared<Mover>(wobj1.get(), 'w', 's', 'a', 'd');

  shared_ptr<Mover> collidingMover2 = make_shared<Mover>(wobj2.get(), 'i', 'k', 'j', 'l');

  inputManager->registerObject(collidingMover1);
  inputManager->registerObject(collidingMover2);

  AABBCollisionMgr* collisionMgr = AABBCollisionMgr::get();

  collisionMgr->registerObject(wobj1);
  collisionMgr->registerObject(wobj2);
  displayManager->registerObject(wobj1);
  displayManager->registerObject(wobj2);
  glutMainLoop();
  alutExit();

  return EXIT_SUCCESS;
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(90.0, w/(float)h, 0.1, 100.0);
   glMatrixMode (GL_MODELVIEW);
}

ALuint loadAudioFile(const char *fileName)
{
  ALenum error;

  /* Create an AL buffer from the given sound file. */
  ALuint audioBuffer = alutCreateBufferFromFile (fileName);
  if (audioBuffer == AL_NONE)
  {
      error = alutGetError ();
      cerr <<  "Error loading audio file " << fileName << ": " <<
        alutGetErrorString(error) << endl;
      alutExit ();
      exit (EXIT_FAILURE);
  }
  return audioBuffer;
}
