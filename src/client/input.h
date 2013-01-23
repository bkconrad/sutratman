#ifndef INPUT_H
#define INPUT_H

#include "client/listenerinterface.h"

#include <irrlicht.h>
#include <tnl.h>

#include <set>

using namespace TNL;

class Input : public irr::IEventReceiver
{
   public:
      static Input* get();
      Input();
      virtual ~Input();

      void addListener(ListenerInterface* listener);
      void removeListener(ListenerInterface* listener);

      // overrides
      bool OnEvent(const irr::SEvent& event);
   protected:
   private:
      std::set<ListenerInterface*> mListeners;
      static Input* mInstance;
};

#endif // INPUT_H
