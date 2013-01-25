#include "client/gui.h"
#include "client/input.h"
#include "client/diagnosticswindow.h"

#include <tnl.h>

Gui* Gui::mInstance = NULL;

void Gui::init(irr::gui::IGUIEnvironment* guiEnvironment)
{
    // don't initialize twice
    if(mGuiEnvironment) {
        return;
    }

    mGuiEnvironment = guiEnvironment;
    mDiagnosticsWindow = new DiagnosticsWindow(mGuiEnvironment);

    Input::get()->addListener(this);
}

bool Gui::handle(const irr::SEvent& event)
{
    // window shortcuts
    if (event.EventType == irr::EET_KEY_INPUT_EVENT && event.KeyInput.PressedDown) {
        switch (event.KeyInput.Key) {
            case irr::KEY_F12:
                mDiagnosticsWindow->toggle();
            break;
        }
        return true;
    }

    // Ignore other non-GUI events
    if (!event.EventType == irr::EET_GUI_EVENT) {
        return false;
    }

    switch (event.GUIEvent.EventType) {
        default:
        break;
    }
}

void Gui::draw()
{
   if(TNL::Platform::getRealMilliseconds() - mLastUpdate > UPDATE_INTERVAL) {
        mDiagnosticsWindow->update();
        mLastUpdate = TNL::Platform::getRealMilliseconds();
   }
   mGuiEnvironment->drawAll();
}

Gui* Gui::get()
{
    return mInstance = mInstance ? mInstance : new Gui();
}

Gui::Gui()
{
    mDiagnosticsWindow = NULL;
    mGuiEnvironment = NULL;
}

Gui::~Gui()
{
    mInstance = NULL;
}
