#ifndef GUI_H_
#define GUI_H_

#include "client/guiwindowinterface.h"
#include "client/listenerinterface.h"

#include <irrlicht.h>

class Gui : ListenerInterface
{
public:
    static const int UPDATE_INTERVAL = 200;

    static Gui *get();

    virtual ~Gui();
    void draw();
    bool handle(const irr::SEvent &event);
    void init(irr::gui::IGUIEnvironment *guiEnvironment);

private:
    static Gui *mInstance;

    Gui();

    GuiWindowInterface *mDiagnosticsWindow;
    irr::gui::IGUIEnvironment *mGuiEnvironment;
    unsigned int mLastUpdate;
};

#endif /* GUI_H_ */
