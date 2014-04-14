#include "cube.h"
#include <random>
#include <chrono>

Cube::Cube(float x, float y, float z, float rX, float rY)
{
    this->rotateX = rX;
    this->rotateY = rY;
    this->_posX = x;
    this->_posY = y;
    this->_posZ = z;


  // init colors
    std::mt19937 generator;
    generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_real_distribution<float> distribution(0.0, 1.0);
    for(int i = 0; i < 24; ++i)
    {
        cubeColors[i] = distribution(generator);
    }
}

Cube::~Cube()
{
    //dtor
}

void Cube::draw()
{
    glEnableClientState (GL_VERTEX_ARRAY);
    glVertexPointer (3, GL_INT, 0, cubeVerticles);
    /*if(texturing)
    {
        glEnableClientState (GL_TEXTURE_COORD_ARRAY);
        glTexCoordPointer (2, GL_FLOAT, 0, texturePoints);
    } else */{
        glEnableClientState (GL_COLOR_ARRAY);
        glColorPointer (3, GL_FLOAT, 0, cubeColors);
    }
    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_LINE);
    glFrontFace(GL_CCW);

    glLoadIdentity ();
    glTranslatef(_posX, _posY, _posZ);
    glRotatef(rotateX, 0,1,0);
    glRotatef(rotateY, 1,0,0);

    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, frontIndices);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, rightIndices);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, bottomIndices);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, backIndices);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, leftIndices);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, topIndices);

    glDisableClientState (GL_COLOR_ARRAY);
    glDisableClientState (GL_VERTEX_ARRAY);
}
