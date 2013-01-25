#ifndef DIAGNOSTICS_H
#define DIAGNOSTICS_H

#include <glm/glm.hpp>

#include <string>
#include <sstream>
#include <iostream>
#include <map>

#define DIAG(name, expression) \
    Diagnostics::get()->set(#name, expression)

using std::string;
using std::wstring;
using std::map;
using std::ostringstream;
using std::ostream;
using namespace glm;

class Diagnostics
{
    public:
        static Diagnostics *get();
        const string print(const string& field);
        const string dump();
        void set(const string& field, const string& value);
        void set(const string& field, const vec3& value);

    protected:
    private:
        static const int BUFFER_SIZE = 1024;
        static Diagnostics* mInstance;
        map<string, string> mMap;
        Diagnostics();
        virtual ~Diagnostics();
};

#endif // DIAGNOSTICS_H
