#include "tnl.h"
#include "tnlNetConnection.h"
#include "tnlEventConnection.h"
#include "tnlNetInterface.h"
#include "tnlRPC.h"

#ifndef SUT_DEDICATED
   #include <irrlicht.h>
   using namespace irr;
   using namespace core;
   using namespace scene;
   using namespace video;
   using namespace io;
   using namespace gui;
#endif

#include <iostream>

using namespace TNL;
using namespace std;

class SimpleEventConnection : public EventConnection {
   typedef EventConnection Parent;
   public:
      TNL_DECLARE_NETCONNECTION(SimpleEventConnection);
};

TNL_IMPLEMENT_NETCONNECTION(SimpleEventConnection, NetClassGroupGame, true);

int main (int argc, char** argv) {
   if (argc < 3) {
      cout << "Usage: " << argv[0] << " -[client|server] <address>" << endl;
      exit(1);
   }
   bool isClient = !strcmp(argv[1], "-client");
   Address cmdAddress(argv[2]);
   RefPtr<NetInterface> interface;

   if (isClient) {
#ifndef SUT_DEDICATED
      Address bindAddress(IPProtocol, Address::Any, 0);
      interface = new NetInterface(bindAddress);
      SimpleEventConnection *newConnection = new SimpleEventConnection;
      newConnection->connect(interface, cmdAddress);
      IrrlichtDevice *device =
         createDevice( video::EDT_SOFTWARE, dimension2d<u32>(640, 480), 16,
               false, false, false, 0);
#endif
   } else {
      interface = new NetInterface(cmdAddress);
      interface->setAllowsConnections(true);
#ifdef SUT_DEDICATED
      cout << "Starting dedicated server!" << endl;
#else
      cout << "Starting hybrid server!" << endl;
#endif
   }
   while(true) {
      interface->checkIncomingPackets();
      interface->processConnections();
      Platform::sleep(100);
   }
   return 0;
}
