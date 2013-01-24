#include "diagnostics.h"

Diagnostics *Diagnostics::mInstance = NULL;

Diagnostics::Diagnostics()
{
    //ctor
    mMap["test"] = "hi";
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

const string Diagnostics::print(const string& field)
{
    return mMap[field];
}

/** @brief get a reference to the map
  */
const map<string, string>& Diagnostics::getMap()
{
    return (const map<string, string>&) mMap;
}


