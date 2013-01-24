#ifndef GUIWINDOWINTERFACE_H
#define GUIWINDOWINTERFACE_H

#include <irrlicht.h>

/**
Interface for in-game windows (e.g. diagnostics, inventory, etc)
*/
class GuiWindowInterface
{
    public:
    GuiWindowInterface(irr::gui::IGUIEnvironment *guiEnv, const wchar_t *title);
    virtual ~GuiWindowInterface();
    void hide();
    void show();
    void toggle();

    /**
    make any changes necessary to put this window into a valid state
    */
    virtual void validate() = 0;
    /**
    return the window's contents to their initial state
    */
    virtual void initialize() = 0;
    /**
    perform any updates necessary on this window
    */
    virtual void update() = 0;

    protected:
    irr::gui::IGUIWindow *mWindow;
    irr::gui::IGUIEnvironment *mGuiEnv;

    private:
    static unsigned int WindowIdCount;
};

#endif // GUIWINDOWINTERFACE_H
