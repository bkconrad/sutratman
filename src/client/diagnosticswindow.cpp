#include "diagnosticswindow.h"
using std::wstring;
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
    string dump = Diagnostics::get()->dump();
    wstring output;
    output.assign(dump.begin(), dump.end());
    mGuiEnv->addStaticText(output.c_str(),
                           irr::core::rect<irr::s32>(5, 20, 200, 300),
                           true, true, mWindow);
}

