#include "input.h"

Input *Input::mInstance = NULL;

Input::Input()
{
    mInstance = this;
}

Input::~Input()
{
    //dtor
}

const vec2 Input::getDelta()
{
    return mCurrentMousePos - mLastMousePos;
}

bool Input::OnEvent(const irr::SEvent &event)
{
    if(event.EventType == irr::EET_MOUSE_INPUT_EVENT) {
        mLastMousePos = mCurrentMousePos;
        mCurrentMousePos = vec2(event.MouseInput.X, event.MouseInput.Y);
    }

    std::set<ListenerInterface*>::iterator i;

    for(i = mListeners.begin(); i != mListeners.end(); i++)
    {
        if((*i)->handle(event))
        {
            // if handle(event) returns true then the listener has consumed the event.
            break;
        }
    }
}

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

void Input::addListener(ListenerInterface *listener)
{
    mListeners.insert(listener);
}

Input *Input::get()
{
    return mInstance ? mInstance : new Input();
}

