#include <cstdlib>
#include <GL/glut.h>
#include <AL/alut.h>
#include <random>
#include <chrono>
#include <iostream>
#include <png.h>
// cstring potrzebny dla memcpy w funkcji loadPngImage
#include <cstring>

using namespace std;

void keyboard(unsigned char key, int x, int y);
void display(void);
void reshape (int w, int h);
void specialInput(int key, int x, int y);
static void playFile(const char *filename);
bool loadPngImage(char *name, int &outWidth, int &outHeight,
                  bool &outHasAlpha, GLubyte **outData);
void loadAudioFile(const char *fileName);
void initTexture(void);
void mousePassive(int x, int y);
void mouseMotion(int x, int y);

const float deltaPosX = 0.1;
const float deltaPosY = 0.1;

float posX = 0;
float posY = 0;
float posZ = -3;

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

ALuint alsource;
ALuint audioBuffer;

ALfloat listenerOrientation[6] = {0,0,-1, 0, 1, 0};

bool texturing = false;
GLubyte *textureImage;
GLfloat texturePoints[] = {0.25, 0.66,
                           0.50, 0.66,
                           0.50, 0.33,
                           0.25, 0.33,
                           0, 0,
                          1, 0,
                          1, 1,
                          0, 1};

float rotateX = 0;
float rotateY = 0;
 
int mouseX;
int mouseY;
                           
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
  glutMotionFunc(mouseMotion);
  glutPassiveMotionFunc(mousePassive);
  glEnable(GL_DEPTH_TEST);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClearDepth(1.0f);
  if (argc > 1) 
  {
      texturing = true;
      initTexture();
  }
  
  alListener3f(AL_POSITION, 0.0, 0.0, 0.0);
  alListenerfv(AL_ORIENTATION, listenerOrientation);

  // init colors
    std::mt19937 generator;
    generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_real_distribution<float> distribution(0.0, 1.0);
    for(int i = 0; i < 24; ++i)
    {
        cubeColors[i] = distribution(generator);
    }
  loadAudioFile("alert.wav");
  glutMainLoop();
  alutExit();
  return EXIT_SUCCESS;
}

// checks ascii input
void keyboard(unsigned char key, int /*x*/, int /*y*/)
{
  switch (key)
  {
    case '\x1B':
	  alutExit();
      exit(EXIT_SUCCESS);
      break;
    case ' ':
      alSource3f(alsource, AL_POSITION, posX, posY, posZ);
      alSourcePlay (alsource);
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

    glEnableClientState (GL_VERTEX_ARRAY);
    glVertexPointer (3, GL_INT, 0, cubeVerticles);
    if(texturing)
    {
        
        glEnableClientState (GL_TEXTURE_COORD_ARRAY);
        glTexCoordPointer (2, GL_FLOAT, 0, texturePoints);
    } else {
        glEnableClientState (GL_COLOR_ARRAY);
        glColorPointer (3, GL_FLOAT, 0, cubeColors);
    }
    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_LINE);
    glFrontFace(GL_CCW);

    glLoadIdentity ();
    glTranslatef(posX, posY, posZ);
    glRotatef(rotateX, 0,1,0);
    glRotatef(rotateY, 1,0,0);

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

void loadAudioFile(const char *fileName)
{
  //ALuint source;
  ALenum error;
  ALint status;

  /* Create an AL buffer from the given sound file. */
  audioBuffer = alutCreateBufferFromFile (fileName);
  if (audioBuffer == AL_NONE)
  {
      error = alutGetError ();
      cerr <<  "Error loading file: " << alutGetErrorString(error) << endl;
      alutExit ();
      exit (EXIT_FAILURE);
  }

  /* Generate a single source, attach the buffer to it and start playing. */
  alGenSources (1, &alsource);
  alSourcei (alsource, AL_BUFFER, audioBuffer);
  alSourcei (alsource, AL_SOURCE_RELATIVE, AL_TRUE);
}

// Function loading texture from png file, uses libpng. 
bool loadPngImage(char *name, int &outWidth, int &outHeight, bool &outHasAlpha, GLubyte **outData) {
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
    bool hasAlpha;
    char filename[] = "logo.png";
    bool success = loadPngImage(filename, width, height, hasAlpha, &textureImage);
    if (!success) {
        cerr << "Unable to load png file" << endl;
        return;
    }
    cout << "Image loaded " << width << " " << height << " alpha " << hasAlpha << std::endl;
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, hasAlpha ? 4 : 3, width,
                 height, 0, hasAlpha ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE,
                 textureImage);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_FLAT);
}

void mousePassive(int x, int y)
{
    mouseX = x;
    mouseY = y;
}
 
void mouseMotion(int x, int y)
{
    const float SPEED = 2;
 
    rotateX += (mouseX-x)/SPEED;
    rotateY += (mouseY-y)/SPEED;
    mousePassive(x, y);
    glutPostRedisplay();
}