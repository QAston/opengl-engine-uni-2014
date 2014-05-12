#include "loadedobject.h"
#include <iostream>
#include "objloader.h"

using namespace std;

LoadedObject::LoadedObject(
    const vector<array<double,3>> &vertici,
    const vector<array<int,4>> &faces,
    const vector<array<double,3>> &normals,
    tinyobj::material_t material,
    const vector<array<double,2>> &texCoords)
{
    vector<array<double,3>>::const_iterator it;
    vector<array<int,4>>::const_iterator fit;

    for (it=vertici.begin(); it != vertici.end(); it++)
    {
        _vertici.push_back((GLdouble)((*it)[0]));
        _vertici.push_back((GLdouble)((*it)[1]));
        _vertici.push_back((GLdouble)((*it)[2]));
    }

    for (fit=faces.begin(); fit != faces.end(); fit++)
    {
        array<GLubyte,4> tmp;
        tmp[0] = (GLubyte)(*fit)[0];
        tmp[1] = (GLubyte)(*fit)[1];
        tmp[2] = (GLubyte)(*fit)[2];
        tmp[3] = (GLubyte)(*fit)[3];
        _faces.push_back(tmp);
    }
    //TODO FIX THIS!!!!
    _normals = vector<array<GLdouble,3>>(_vertici.size(), {1.0, 0.0, 0.0});
    _colors = vector<GLfloat>(_vertici.size(), 0.5);
    _material = material;
    _texCoords = texCoords;

    if (_material.diffuse_texname != "")
    {
        _textureImage = loadPngImage(_material.diffuse_texname.c_str(), _texWidth, _texHeight);
        if (_textureImage == NULL)
            cerr << "Unable to load png file :" << _material.diffuse_texname << endl;
        else
            cout << "Image loaded. Width: " << _texWidth << " Height: " << _texHeight << endl;
    }

}

LoadedObject::~LoadedObject()
{
    //dtor
}

void LoadedObject::draw()
{
    glEnableClientState (GL_NORMAL_ARRAY);
    glNormalPointer (GL_DOUBLE, 0, _normals.data());

    glEnableClientState (GL_VERTEX_ARRAY);
    glVertexPointer (3, GL_DOUBLE, 0, _vertici.data());

    glEnableClientState (GL_TEXTURE_COORD_ARRAY);
    glTexCoordPointer (2, GL_DOUBLE, 0, _texCoords.data());
    //} else
    //glEnableClientState (GL_COLOR_ARRAY);
    //glColorPointer (3, GL_FLOAT, 0, _colors.data());
    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_LINE);
    glFrontFace(GL_CCW);

    //glLoadIdentity ();
    //glTranslatef(_posX, _posY, _posZ);
    //glRotatef(rotateX, 0,1,0);
    //glRotatef(rotateY, 1,0,0);

    glMaterialfv(GL_FRONT, GL_AMBIENT, _material.ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, _material.diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, _material.specular);
    glMaterialfv(GL_FRONT, GL_EMISSION, _material.emission);
    glMaterialf(GL_FRONT, GL_SHININESS, _material.shininess);


    glColor3fv(_material.diffuse);

    if(_textureImage != NULL)
    {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, 3, _texWidth,
                     _texHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,
                     _textureImage);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glEnable(GL_TEXTURE_2D);
        glShadeModel(GL_FLAT);
    }

    vector<array<GLubyte,4>>::iterator facesIterator;
    for (facesIterator = _faces.begin(); facesIterator != _faces.end(); facesIterator++)
    {
        glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, (*facesIterator).data());
    }

    //glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisable(GL_BLEND);
}
