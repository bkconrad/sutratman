#include "client/guiwindowinterface.h"

#include <string>

using std::wstring;

unsigned int GuiWindowInterface::WindowIdCount = 0;

GuiWindowInterface::~GuiWindowInterface()
{
    if (mWindow) {
        mWindow->remove();
    }
}

GuiWindowInterface::GuiWindowInterface(irr::gui::IGUIEnvironment *guiEnv, const wchar_t *title)
    : mGuiEnv(guiEnv)
{
    mWindow = mGuiEnv->addWindow(irr::core::rect<irr::s32>(0,0,200,200),
                                false,
                                title,
                                guiEnv->getRootGUIElement(),
                                WindowIdCount++);
}

void GuiWindowInterface::show()
{
    mWindow->setVisible(true);
}

void GuiWindowInterface::hide()
{
    mWindow->setVisible(false);
}

void GuiWindowInterface::toggle()
{
    mWindow->setVisible(!mWindow->isVisible());
}

