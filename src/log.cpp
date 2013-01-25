#include "log.h"

#include <cstdio>
#include <string>

using namespace std;

namespace Log
{
void p(const char *format, ...)
{
    string s(format);
    s += "\n";
    va_list argptr;
    va_start(argptr, format);
    vfprintf(stdout, s.c_str(), argptr);
    va_end(argptr);
}
}
