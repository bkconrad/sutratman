#ifndef INPUT_H_
#define INPUT_H_

#include "client/listenerinterface.h"

#include <glm/glm.hpp>
#include <irrlicht.h>
#include <tnl.h>

#include <set>

using namespace TNL;
using namespace glm;

class Input : public irr::IEventReceiver
{
public:
    static Input *get();
    Input();
    virtual ~Input();

    void addListener(ListenerInterface *listener);
    const vec2 getDelta();
    void removeListener(ListenerInterface *listener);

    // overrides
    bool OnEvent(const irr::SEvent &event);

private:
    vec2 mLastMousePos;
    vec2 mCurrentMousePos;
    std::set<ListenerInterface*> mListeners;
    static Input *mInstance;
};

#endif /* INPUT_H_ */
