#ifndef INPUT_H
#define INPUT_H

#include "client/listenerinterface.h"
#include "vec2.h"

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
      const Vec2 getDelta();

      // overrides
      bool OnEvent(const irr::SEvent& event);
   protected:
   private:
      Vec2 mLastMousePos;
      Vec2 mCurrentMousePos;
      std::set<ListenerInterface*> mListeners;
      static Input* mInstance;
};

#endif // INPUT_H
