#include "loadedobject.h"
#include <iostream>

using namespace std;

LoadedObject::LoadedObject(vector<array<double,3>> vertizzi, vector<array<int,4>> faces)
{
    vector<array<double,3>>::iterator it;
    vector<array<int,4>>::iterator fit;

    for (it=vertizzi.begin(); it != vertizzi.end(); it++)
    {
        this->vertici.push_back((*it)[0]);
        this->vertici.push_back((*it)[1]);
        this->vertici.push_back((*it)[2]);
    }
    for (fit=faces.begin(); fit != faces.end(); fit++)
    {
        array<GLubyte,4> tmp;
        tmp[0] = (GLubyte)(*it)[0];
        tmp[1] = (GLubyte)(*it)[1];
        tmp[2] = (GLubyte)(*it)[2];
        tmp[3] = (GLubyte)(*it)[3];
        this->faces.push_back(tmp);
    }
}

LoadedObject::~LoadedObject()
{
    //dtor
}

void LoadedObject::draw()
{
    glEnableClientState (GL_VERTEX_ARRAY);
    glVertexPointer (3, GL_INT, 0, &vertici);
    /*if(texturing)
    {
        glEnableClientState (GL_TEXTURE_COORD_ARRAY);
        glTexCoordPointer (2, GL_FLOAT, 0, texturePoints);
    } else */
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
        glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, &*facesIterator);
    }

    glDisableClientState (GL_COLOR_ARRAY);
    glDisableClientState (GL_VERTEX_ARRAY);
}
