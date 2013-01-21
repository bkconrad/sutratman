#include "input.h"

Input::Input()
{
   //ctor
}

Input::~Input()
{
   //dtor
}
/** @brief OnEvent
  *
  * @todo: document this function
  */
bool Input::OnEvent(const irr::SEvent& event)
{
   if (!event.EventType == irr::EET_KEY_INPUT_EVENT)
      return false;

   mKeyStates[event.KeyInput.Key] = event.KeyInput.PressedDown;
}

/** @brief removeHandler
  *
  * @todo: document this function
  */
void Input::removeHandler(bool (*func)(const irr::SEvent&))
{
   for(int i = 0; i < mHandlers.size(); i++) {
      if (mHandlers[i] == func) {
         mHandlers.erase(i);
      }
   }
}

/** @brief addHandler
  *
  * @todo: document this function
  */
void Input::addHandler(bool (*func)(const irr::SEvent&))
{
   mHandlers.push_back(func);
}

/** @brief isKeyDown
  *
  * @todo: document this function
  */
bool Input::isKeyDown(irr::EKEY_CODE key) const
{
   return mKeyStates[key];
}

