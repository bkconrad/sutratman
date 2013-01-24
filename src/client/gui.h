#ifndef GUI_H
#define GUI_H

#include "client/listenerinterface.h"
#include "client/guiwindowinterface.h"

#include <irrlicht.h>

class Gui : ListenerInterface
{
    public:
        static Gui* get();
        void init(irr::gui::IGUIEnvironment* guiEnvironment);
        void draw();
        bool handle(const irr::SEvent& event);
        virtual ~Gui();
    protected:
    private:
        static Gui* mInstance;
        Gui();

        irr::gui::IGUIEnvironment *mGuiEnvironment;
        GuiWindowInterface *mDiagnosticsWindow;
};

#endif // GUI_H
