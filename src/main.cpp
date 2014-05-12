#include <cstdlib>
#include <GL/glut.h>
#include <AL/alut.h>
#include <random>
#include <chrono>
#include <iostream>
#include <png.h>
#include <cstring>
#include <vector>

#include <memory>
#include "cube.h"
#include "fpscamera.h"
#include "inputmanagerglut.h"
#include "objloader.h"
#include "loadedobject.h"
#include "displaymanagerglut.h"
#include "unique.h"
#include "soundsourceglut.h"
#include "scenepos.h"
#include "sceneloader.h"

using namespace std;

void reshape (int w, int h);
bool loadPngImage(char *name, int &outWidth, int &outHeight,
                  bool &outHasAlpha, GLubyte **outData);
ALuint loadAudioFile(const char *fileName);
void initTexture(void);

bool texturing = false;
GLubyte *textureImage;

int main(int argc, char** argv)
{
    // wire up the entire system
  glutInit(&argc, argv);
  alutInit(&argc, argv);

  glutInitWindowSize(800, 600);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

  /*int mainWindow = */glutCreateWindow("RW5");
  if (argc > 1)
  {
      texturing = true;
      initTexture();
  }
      glutWarpPointer(400, 300);
      glutReshapeFunc(&reshape);

  ALuint alert = loadAudioFile("alert.wav");

  unique_ptr<SoundSource> cubeSound = make_unique<SoundSourceGLUT>(alert);
  vector<shared_ptr<Drawable>> objects = loadObjFile("objFiles/redcubeobj.obj");
  ScenePos posCube1 = ScenePos(3, 0, -3, 0, 0);
  objects.push_back(make_shared<Cube>(posCube1));
  objects.push_back(make_shared<Cube>(ScenePos(0, 0, -3, 0, 0)));
  cubeSound->setPosition(posCube1);

  shared_ptr<Cube::Input> cubeSoundInput = make_shared<Cube::Input>(nullptr, cubeSound.get());

  shared_ptr<FPSCamera> camera = make_shared<FPSCamera>(0, 0, 10, 0, 0);
  InputManager* inputManager = InputManagerGLUT::get();
  DisplayManager* displayManager = DisplayManagerGLUT::get();
  displayManager->init(camera);
  shared_ptr<FPSCamera::Input> cameraInput = make_shared<FPSCamera::Input>(camera);
  inputManager->registerObject(cameraInput);
  inputManager->registerObject(cubeSoundInput);
  for(shared_ptr<Drawable> obj: objects)
  {
        displayManager->registerObject(obj);
  }
  glutMainLoop();
  alutExit();
  return EXIT_SUCCESS;
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(90.0, w/(float)h, 1.0, 20.0);
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
      cerr <<  "Error loading file: " << alutGetErrorString(error) << endl;
      alutExit ();
      exit (EXIT_FAILURE);
  }
  return audioBuffer;
}

// Function loading texture from png file, uses libpng.
bool loadPngImage(char *name, int &outWidth, int &outHeight, GLubyte **outData) {
    png_structp png_ptr;
    png_infop info_ptr;
    unsigned int sig_read = 0;
    int color_type, interlace_type;
    FILE *fp;

    if ((fp = fopen(name, "rb")) == NULL)
        return false;

    /* Create and initialize the png_struct
     * with the desired error handler
     * functions.  If you want to use the
     * default stderr and longjump method,
     * you can supply NULL for the last
     * three parameters.  We also supply the
     * the compiler header file version, so
     * that we know if the application
     * was compiled with a compatible version
     * of the library.  REQUIRED
     */
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
                                     NULL, NULL, NULL);

    if (png_ptr == NULL) {
        fclose(fp);
        return false;
    }

    /* Allocate/initialize the memory
     * for image information.  REQUIRED. */
    info_ptr = png_create_info_struct(png_ptr);
    if (info_ptr == NULL) {
        fclose(fp);
        png_destroy_read_struct(&png_ptr, NULL, NULL);
        return false;
    }

    /* Set error handling if you are
     * using the setjmp/longjmp method
     * (this is the normal method of
     * doing things with libpng).
     * REQUIRED unless you  set up
     * your own error handlers in
     * the png_create_read_struct()
     * earlier.
     */
    if (setjmp(png_jmpbuf(png_ptr))) {
        /* Free all of the memory associated
         * with the png_ptr and info_ptr */
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        fclose(fp);
        /* If we get here, we had a
         * problem reading the file */
        return false;
    }

    /* Set up the output control if
     * you are using standard C streams */
    png_init_io(png_ptr, fp);

    /* If we have already
     * read some of the signature */
    png_set_sig_bytes(png_ptr, sig_read);

    /*
     * If you have enough memory to read
     * in the entire image at once, and
     * you need to specify only
     * transforms that can be controlled
     * with one of the PNG_TRANSFORM_*
     * bits (this presently excludes
     * dithering, filling, setting
     * background, and doing gamma
     * adjustment), then you can read the
     * entire image (including pixels)
     * into the info structure with this
     * call
     *
     * PNG_TRANSFORM_STRIP_16 |
     * PNG_TRANSFORM_PACKING  forces 8 bit
     * PNG_TRANSFORM_EXPAND forces to
     *  expand a palette into RGB
     */
    png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, NULL);

    png_uint_32 width, height;
    int bit_depth;
    png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type,
                 &interlace_type, NULL, NULL);
    outWidth = width;
    outHeight = height;

    unsigned int row_bytes = png_get_rowbytes(png_ptr, info_ptr);
    *outData = (unsigned char*) malloc(row_bytes * outHeight);

    png_bytepp row_pointers = png_get_rows(png_ptr, info_ptr);

    for (int i = 0; i < outHeight; i++) {
        // note that png is ordered top to
        // bottom, but OpenGL expect it bottom to top
        // so the order or swapped
        memcpy(*outData+(row_bytes * (outHeight-1-i)), row_pointers[i], row_bytes);
    }

    /* Clean up after the read,
     * and free any memory allocated */
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);

    /* Close the file */
    fclose(fp);

    /* That's it */
    return true;
}

// Loads texture and makes openGL use it.
void initTexture(void) {

    // The following two lines enable semi transparent
    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    int width, height;
    char filename[] = "logo.png";
    bool success = loadPngImage(filename, width, height, &textureImage);
    if (!success) {
        cerr << "Unable to load png file" << endl;
        return;
    }
    cout << "Image loaded " << width << " " << height << std::endl;
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, width,
                 height, 0, GL_RGB, GL_UNSIGNED_BYTE,
                 textureImage);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_FLAT);
}
