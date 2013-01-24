#ifndef DIAGNOSTICS_H
#define DIAGNOSTICS_H

#include <string>
#include <map>

using std::string;
using std::map;

class Diagnostics
{
    public:
        static Diagnostics *get();
        const string print(const string& field);
        void set(const string& field, const string& value);
        const map<string, string>& getMap();

    protected:
    private:
        static Diagnostics* mInstance;
        map<string, string> mMap;
        Diagnostics();
        virtual ~Diagnostics();
};

#endif // DIAGNOSTICS_H
