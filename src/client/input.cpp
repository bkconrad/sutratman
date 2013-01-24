#include "input.h"

Input* Input::mInstance = NULL;

Input::Input()
{
   mInstance = this;
}

Input::~Input()
{
   //dtor
}

/** @brief getDelta
  *
  * @todo: document this function
  */
const vec2 Input::getDelta()
{
   return mCurrentMousePos - mLastMousePos;
}

/** @brief OnEvent
  *
  * @todo: document this function
  */
bool Input::OnEvent(const irr::SEvent& event)
{
   mLastMousePos = mCurrentMousePos;
   mCurrentMousePos = vec2(event.MouseInput.X, event.MouseInput.Y);

   std::set<ListenerInterface*>::iterator i;
   for (i = mListeners.begin(); i != mListeners.end(); i++) {
      (*i)->handle(event);
   }
}

void Input::removeListener(ListenerInterface* listener)
{
   std::set<ListenerInterface*>::iterator i;
   for (i = mListeners.begin(); i != mListeners.end(); i++) {
      if (*i == listener) {
         mListeners.erase(i);
      }
   }
}

void Input::addListener(ListenerInterface* listener)
{
   mListeners.insert(listener);
}



/** @brief get
  *
  * @todo: document this function
  */
Input* Input::get()
{
   return mInstance ? mInstance : new Input();
}

