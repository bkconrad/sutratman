#ifndef INPUT_H_
#define INPUT_H_

#include "client/listenerinterface.h"

#include <irrlicht.h>
#include <tnl.h>

#include <set>

using namespace TNL;
using irr::core::vector2df;

class Input : public irr::IEventReceiver
{
public:
    static Input *get();
    Input();
    virtual ~Input();

    void addListener(ListenerInterface *listener);
    const vector2df getDelta();
    void removeListener(ListenerInterface *listener);

    // overrides
    bool OnEvent(const irr::SEvent &event);

private:
    vector2df mLastMousePos;
    vector2df mCurrentMousePos;
    std::set<ListenerInterface*> mListeners;
    static Input *mInstance;
};

#endif /* INPUT_H_ */
