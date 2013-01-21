#ifndef INPUT_H
#define INPUT_H

#include <irrlicht.h>
#include <tnl.h>

using namespace TNL;

class Input : irr::IEventReceiver
{
   public:
      Input();
      virtual ~Input();

      bool isKeyDown(irr::EKEY_CODE key) const;
      void addHandler(bool (*func)(const irr::SEvent&));
      void removeHandler(bool (*func)(const irr::SEvent&));

      // overrides
      virtual bool OnEvent(const irr::SEvent& event);
   protected:
   private:
      Vector<bool (*)(const irr::SEvent&)> mHandlers;
      bool mKeyStates[irr::KEY_KEY_CODES_COUNT];
};

#endif // INPUT_H
