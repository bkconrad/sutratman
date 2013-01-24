#ifndef INPUT_H
#define INPUT_H

#include "client/listenerinterface.h"

#include <irrlicht.h>
#include <tnl.h>
#include <glm/glm.hpp>

#include <set>

using namespace TNL;
using namespace glm;

class Input : public irr::IEventReceiver
{
   public:
      static Input* get();
      Input();
      virtual ~Input();

      void addListener(ListenerInterface* listener);
      void removeListener(ListenerInterface* listener);
      const vec2 getDelta();

      // overrides
      bool OnEvent(const irr::SEvent& event);
   protected:
   private:
      vec2 mLastMousePos;
      vec2 mCurrentMousePos;
      std::set<ListenerInterface*> mListeners;
      static Input* mInstance;
};

#endif // INPUT_H
