#include "input.h"

Input *Input::mInstance = NULL;

Input *Input::get()
{
    return mInstance ? mInstance : new Input();
}

Input::Input()
{
    mInstance = this;
}

Input::~Input()
{
    //dtor
}

/**
 * @brief return the last mouse pointer change
 */
const vector2df Input::getDelta()
{
    return mCurrentMousePos - mLastMousePos;
}

bool Input::OnEvent(const irr::SEvent &event)
{
    if(event.EventType == irr::EET_MOUSE_INPUT_EVENT)
    {
        mLastMousePos = mCurrentMousePos;
        mCurrentMousePos = vector2df(event.MouseInput.X, event.MouseInput.Y);
    }

    std::set<ListenerInterface*>::iterator i;

    for(i = mListeners.begin(); i != mListeners.end(); i++)
    {
        if((*i)->handle(event))
        {
            // when handle(event) returns true the listener consumes
            break;
        }
    }
}

/**
 * @brief unsubscribe a listener
 */
void Input::removeListener(ListenerInterface *listener)
{
    std::set<ListenerInterface*>::iterator i;

    for(i = mListeners.begin(); i != mListeners.end(); i++)
    {
        if(*i == listener)
        {
            mListeners.erase(i);
        }
    }
}

/**
 * @brief subscribe a listener to the event listener list
 */
void Input::addListener(ListenerInterface *listener)
{
    mListeners.insert(listener);
}
