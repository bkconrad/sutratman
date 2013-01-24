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
        /** @brief return true to consume the event (stop other listeners from getting it after this one) */
      virtual bool handle(const irr::SEvent& event) = 0;
};

#endif // LISTENERINTERFACE_H
