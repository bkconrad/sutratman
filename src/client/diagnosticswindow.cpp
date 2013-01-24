#include "diagnosticswindow.h"

DiagnosticsWindow::DiagnosticsWindow(irr::gui::IGUIEnvironment *guiEnv)
    : GuiWindowInterface(guiEnv, L"Diagnostics")
{
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

}

