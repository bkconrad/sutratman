#ifndef DIAGNOSTICSWINDOW_H
#define DIAGNOSTICSWINDOW_H

#include "client/guiwindowinterface.h"

class DiagnosticsWindow : public GuiWindowInterface
{
    public:
        DiagnosticsWindow(irr::gui::IGUIEnvironment *guiEnv);
        // overrides
        void validate();
        void initialize();
        void update();
    protected:
    private:
};

#endif // DIAGNOSTICSWINDOW_H
