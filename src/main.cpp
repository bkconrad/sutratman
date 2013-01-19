#ifndef SUT_DEDICATED
   #include "client/client.h"
#endif

#include "server.h"

#include <iostream>

using namespace TNL;
using namespace std;

int main (int argc, char** argv) {
   bool isClient = argc > 1 && !strcmp(argv[1], "-client");

   if (isClient) {
#ifndef SUT_DEDICATED
      Client c;
      c.init();
      c.go();
#endif
   } else {
#ifdef SUT_DEDICATED
      cout << "Starting dedicated server!" << endl;
#else
      cout << "Starting hybrid server!" << endl;
#endif
      Server s;
      s.go();
   }
   return 0;
}
