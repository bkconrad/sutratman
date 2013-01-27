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

/**
 * @brief set a diagnostic to value
 */
void Diagnostics::set(const string& field, const string& value)
{
    mMap[field] = value;
}

/**
 * @brief set a diagnostic field to a string representation of v
 */
void Diagnostics::set(const string& field, const vector3df& v)
{
    char buffer[BUFFER_SIZE];
    sprintf(buffer, "%0.2f, %0.2f, %0.2f", v.X, v.Y, v.Z);
    mMap[field] = buffer;
}

/**
 * @brief Get the contents of a single diagnostic
 */
const string Diagnostics::print(const string& field)
{
    return mMap[field];
}

/** @brief Return a std::string of all key/value pairs
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



