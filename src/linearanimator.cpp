#include "linearanimator.h"
#include "reader.h"
#include "document.h"
#include "filestream.h"
#include <iostream>

LinearAnimator::LinearAnimator(vector<SimpleAnimEntry> entries)
{
    this->_entries = entries;
}

LinearAnimator::~LinearAnimator()
{
    //dtor
}

using namespace rapidjson;

struct AnimLoader {
	typedef char Ch;

    string currentFieldName = "";
    int numberArrayIndex = 0;
    bool nextReadFieldName = true;

    vector<SimpleAnimEntry> entries;
    SimpleAnimEntry current;

	void Null() { assert(false&& "invalid null in json file"); }
	void Bool(bool) { assert(false&& "invalid bool in json file"); }
	void Int(int n) { Num(n); }
	void Uint(unsigned n) { Num(n); }
	void Int64(int64_t n) { Num(n); }
	void Uint64(uint64_t n) { Num(n); }
	void Double(double n ) { Num(n); }

	void Num(double n)
	{
        if (currentFieldName == "pos")
        {
            current.pos[numberArrayIndex++] = n;
        }
        else if (currentFieldName == "rot")
        {
            current.rot[numberArrayIndex++] = n;
        }
        else if (currentFieldName == "scale")
        {
            current.scale[numberArrayIndex++] = n;
        }
        else if (currentFieldName == "time")
        {
            current.time = n;
        }
        else
        {
            assert(false&& "invalid number in json file");
        }
        nextReadFieldName = true;
	}

	void String(const Ch* str, int len, bool alloc)
	{
	    if (nextReadFieldName)
        {
            currentFieldName = string(str, len);
            nextReadFieldName = false;
        }
        else
        {
            assert(false&& "invalid string in json file");
        }
	}
	void StartObject()
	{
	    if (currentFieldName == "")
        {
            current.pos = {{0,0,0}};
            current.rot = {{0,0,0}};
            current.scale = {{1,1,1}};
            current.time = 0;
        }
        else
        {
            assert(false&& "invalid object in json file");
        }
	}
	void EndObject(int s)
	{
	    nextReadFieldName = true;
	    entries.push_back(current);
	}
	void StartArray() {
	    if (currentFieldName == "")
	    {
        }
        else if (currentFieldName =="pos" || currentFieldName =="rot" || currentFieldName == "scale")
        {
            numberArrayIndex = 0;
        }
        else
        {
            assert(false&& "invalid array in json file");
        }
	 }
	void EndArray(int s) { nextReadFieldName = true;}
};

unique_ptr<vector<SimpleAnimEntry>> loadAnimEntries(const char* filename)
{
    AnimLoader handler;
    FILE* file = fopen(filename, "r");
    if (file == nullptr)
        return unique_ptr<vector<SimpleAnimEntry>>();

	FileStream inputStream(file);

    Reader reader;

	if (!reader.Parse<0>(inputStream, handler))
    {
        std::cerr << "Error: failed to open anim file: " << filename << std::endl;
        exit(0);
        return nullptr;
    }
    fclose(file);

    return make_unique<vector<SimpleAnimEntry>>(handler.entries);
}


