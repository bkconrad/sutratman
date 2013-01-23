#ifndef LISTENERINTERFACE_H
#define LISTENERINTERFACE_H

#include <irrlicht.h>

/**
Interface for in-game listeners. Once subscribed a listener will
receive events (in turn by the order it was subscribed). A listener can also
choose to consume or pass on events
*/
class ListenerInterface
{
   public:
      virtual bool handle(const irr::SEvent& event) = 0;
};

#endif // LISTENERINTERFACE_H
