#include "sceneloader.h"
#include "objloader.h"
#include "reader.h"
#include "document.h"
#include "filestream.h"
#include <fstream>
#include <cassert>
#include <stack>
#include <cstdio>
#include <iostream>
#include "linearanimator.h"
#include "constanimator.h"

using namespace rapidjson;

struct SceneData
{
    string objectName = "<no_name>";
    string currentFieldName = "";
    int numberArrayIndex = 0;
    int objectArrayIndex = 0;

    bool nextReadFieldName = true;
    bool readingObject = true;

    array<GLdouble, 3> pos {{0,0,0}};
    array<GLdouble, 3> rot {{0,0,0}};
    array<GLdouble, 3> scale {{1,1,1}};

    vector<SceneObject*> subobjects;
    vector<string> models;
    string animationFile = "";
};

struct SceneHandler {
	typedef char Ch;

    stack<SceneData*> objs;
    SceneObject* loadedObject = nullptr;

	void Null() { assert(false&& "invalid null in json file"); }
	void Bool(bool) { assert(false&& "invalid bool in json file"); }
	void Int(int n) { Num(n); }
	void Uint(unsigned n) { Num(n); }
	void Int64(int64_t n) { Num(n); }
	void Uint64(uint64_t n) { Num(n); }
	void Double(double n ) { Num(n); }

	void Num(double n)
	{
	    if (!objs.top()->readingObject)
	    {
            if (objs.top()->currentFieldName == "pos")
            {
                objs.top()->pos[objs.top()->numberArrayIndex++] = n;
            }
            else if (objs.top()->currentFieldName == "rot")
            {
                objs.top()->rot[objs.top()->numberArrayIndex++] = n;
            }
            else if (objs.top()->currentFieldName == "scale")
            {
                objs.top()->scale[objs.top()->numberArrayIndex++] = n;
            }
            else
            {
                assert(false&& "invalid number in json file");
            }
	    }
	    else
        {
            assert(false && "invalid number in json file");
        }
        objs.top()->nextReadFieldName = objs.top()->readingObject;
	}

	void String(const Ch* str, int len, bool alloc)
	{
	    if (objs.top()->readingObject && objs.top()->nextReadFieldName)
        {
            objs.top()->currentFieldName = string(str, len);
            objs.top()->nextReadFieldName = false;
        }
        else if(objs.top()->readingObject && objs.top()->currentFieldName == "name")
        {
            objs.top()->objectName = string(str, len);
            objs.top()->nextReadFieldName = true;
        }
        else if(objs.top()->readingObject && objs.top()->currentFieldName == "animation")
        {
            objs.top()->animationFile = string(str, len);
            objs.top()->nextReadFieldName = true;
        }
        else if(!objs.top()->readingObject && objs.top()->currentFieldName == "models")
        {
            objs.top()->models.push_back(string(str, len));
        }
        else
        {
            assert(false&& "invalid string in json file");
        }
	}
	void StartObject()
	{
	    if (objs.empty() || (objs.top()->currentFieldName == "objs" && !objs.top()->readingObject))
        {
            objs.push(new SceneData());
        }
        else
        {
            assert(false&& "invalid object in json file");
        }
	}
	void EndObject(int s)
	{
	    // object and it's children are all ready
	    // can now build sceneobject
        SceneData* data = objs.top();
        objs.pop();
        vector<shared_ptr<Drawable>> models;
        for (auto& m: data->models)
        {
            for(auto d: loadObjFile(m.c_str()))
            {
                models.push_back(d);
            }
        }

        vector<shared_ptr<SceneObject>> subObjs;
        for (auto s: data->subobjects)
        {
            shared_ptr<SceneObject> sp{s};
            subObjs.push_back(sp);
        }

        ScenePos pos = ScenePos(data->pos[0], data->pos[1],data->pos[2], data->rot[0], data->rot[1], data->rot[2]);
        unique_ptr<Animator> animator;

        if (data->animationFile == "")
        {
            ObjectDesc desc;
            desc.pos = pos;
            desc.scale = data->scale;
            animator = make_unique<ConstAnimator>(desc);
        }
        else
        {
            animator = make_unique<LinearAnimator>(loadAnimEntries(data->animationFile.c_str()));
        }

        SceneObject* sceneObj = new SceneObject(data->objectName,
                                                pos, data->scale,
                                                models, subObjs);

        if (objs.empty())
        {
            loadedObject = sceneObj;
        }
        else
        {
            objs.top()->subobjects.push_back(sceneObj);
            objs.top()->nextReadFieldName = objs.top()->readingObject;
        }
        delete data;
	}
	void StartArray() {
	    if (!objs.top()->readingObject)
        {
            assert(false&& "invalid nested array in json file");
        }
        objs.top()->readingObject = false;
	    if (objs.top()->currentFieldName == "objs")
	    {
        }
        else if (objs.top()->currentFieldName =="pos" || objs.top()->currentFieldName =="rot" || objs.top()->currentFieldName == "scale" || objs.top()->currentFieldName == "models")
        {
            objs.top()->numberArrayIndex = 0;
        }
        else
        {
            assert(false&& "invalid array in json file");
        }
	 }
	void EndArray(int s) { objs.top()->readingObject = true; objs.top()->nextReadFieldName = true;}
};

SceneObject* loadScene(const char* filename)
{
    SceneHandler handler;
    FILE* file = fopen(filename, "r");
    if (file == nullptr)
        return nullptr;

	FileStream inputStream(file);

    Reader reader;

	if (!reader.Parse<0>(inputStream, handler) || handler.loadedObject == nullptr)
    {
        cerr << "Error: failed to open scene file: " << filename << endl;
        exit(0);
        return nullptr;
    }
    fclose(file);

    return handler.loadedObject;
}



