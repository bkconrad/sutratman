#ifndef DIAGNOSTICS_H_
#define DIAGNOSTICS_H_

#include <irrlicht.h>

#include <iostream>
#include <map>
#include <sstream>
#include <string>

#define DIAG(name, expression) \
    Diagnostics::get()->set(#name, expression)

using irr::core::vector3df;

using std::map;
using std::ostream;
using std::ostringstream;
using std::string;
using std::wstring;

class Diagnostics
{
    public:
        static Diagnostics *get();
        const string dump();
        const string print(const string& field);
        void set(const string& field, const string& value);
        void set(const string& field, const vector3df& value);

    protected:
    private:
        static const int BUFFER_SIZE = 1024;
        static Diagnostics* mInstance;
        map<string, string> mMap;
        Diagnostics();
        virtual ~Diagnostics();
};

#endif /* DIAGNOSTICS_H_ */
