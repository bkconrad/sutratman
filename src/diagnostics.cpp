#include "diagnostics.h"

#include <cstdio>

Diagnostics *Diagnostics::mInstance = NULL;

Diagnostics::Diagnostics()
{
    //ctor
}

Diagnostics::~Diagnostics()
{
    //dtor
}

Diagnostics *Diagnostics::get() {
    return mInstance = mInstance ? mInstance : new Diagnostics;
}

void Diagnostics::set(const string& field, const string& value)
{
    mMap[field] = value;
}

void Diagnostics::set(const string& field, const vec3& v)
{
    char buffer[BUFFER_SIZE];
    sprintf(buffer, "%0.2f, %0.2f, %0.2f", v.x, v.y, v.z);
    mMap[field] = buffer;
}

const string Diagnostics::print(const string& field)
{
    return mMap[field];
}

/** @brief dump
  *
  * @todo: document this function
  */
const string Diagnostics::dump()
{
    map<string, string>::iterator i;
    string result = "";
    for (i = mMap.begin(); i != mMap.end(); i++) {
        result += (*i).first + ": " + (*i).second + "\n";
    }
    return result;
}



