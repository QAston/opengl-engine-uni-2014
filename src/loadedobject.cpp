#include "loadedobject.h"
#include <iostream>

using namespace std;

LoadedObject::LoadedObject(const vector<array<double,3>> &vertizzi, const vector<array<int,4>> &facess)
{
    vector<array<double,3>>::const_iterator it;
    vector<array<int,4>>::const_iterator fit;

    for (it=vertizzi.begin(); it != vertizzi.end(); it++)
    {
        this->vertici.push_back((GLdouble)((*it)[0]));
        this->vertici.push_back((GLdouble)((*it)[1]));
        this->vertici.push_back((GLdouble)((*it)[2]));
    }
    for (fit=facess.begin(); fit != facess.end(); fit++)
    {
        array<GLubyte,4> tmp;
        tmp[0] = (GLubyte)(*fit)[0];
        tmp[1] = (GLubyte)(*fit)[1];
        tmp[2] = (GLubyte)(*fit)[2];
        tmp[3] = (GLubyte)(*fit)[3];
        this->faces.push_back(tmp);
    }
}

LoadedObject::~LoadedObject()
{
    //dtor
}

void LoadedObject::draw()
{
    GLfloat cubeColors[24] = { 0.5, 0.5, 0.5,
    0.5, 0.5, 0.5,
    0.5, 0.5, 0.5,
    0.5, 0.5, 0.5,
    0.5, 0.5, 0.5,
    0.5, 0.5, 0.5,
    0.5, 0.5, 0.5,
    0.5, 0.5, 0.5
    };

    glEnableClientState (GL_VERTEX_ARRAY);
    glVertexPointer (3, GL_DOUBLE, 0, vertici.data());

    /*if(texturing)
    {
        glEnableClientState (GL_TEXTURE_COORD_ARRAY);
        glTexCoordPointer (2, GL_FLOAT, 0, texturePoints);
    } else */
    glEnableClientState (GL_COLOR_ARRAY);
    glColorPointer (3, GL_FLOAT, 0, cubeColors);
    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_LINE);
    glFrontFace(GL_CCW);

    //glLoadIdentity ();
    //glTranslatef(_posX, _posY, _posZ);
    //glRotatef(rotateX, 0,1,0);
    //glRotatef(rotateY, 1,0,0);

    vector<array<GLubyte,4>>::iterator facesIterator;
    for (facesIterator = this->faces.begin(); facesIterator != faces.end(); facesIterator++)
    {
        glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, (*facesIterator).data());
    }

    glDisableClientState (GL_COLOR_ARRAY);
    glDisableClientState (GL_VERTEX_ARRAY);
}
