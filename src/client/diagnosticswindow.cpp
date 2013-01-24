#include "diagnosticswindow.h"

DiagnosticsWindow::DiagnosticsWindow(irr::gui::IGUIEnvironment *guiEnv)
    : GuiWindowInterface(guiEnv, L"Diagnostics")
{
    initialize();
}

void DiagnosticsWindow::initialize()
{
    mWindow->setDraggable(true);
}

void DiagnosticsWindow::validate()
{

}

void DiagnosticsWindow::update()
{
    irr::core::list<irr::gui::IGUIElement*> children = mWindow->getChildren();
    irr::core::list<irr::gui::IGUIElement*>::Iterator i;
    for(i = children.begin(); i != children.end(); i++) {
        (*i)->remove();
    }
    mGuiEnv->addStaticText(L"Test",
                           irr::core::rect<irr::s32>(0, 0, 100, 10),
                           true, true, mWindow);
}

