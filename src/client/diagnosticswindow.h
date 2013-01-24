#ifndef DIAGNOSTICSWINDOW_H
#define DIAGNOSTICSWINDOW_H

#include "diagnostics.h"
#include "client/guiwindowinterface.h"

class DiagnosticsWindow : public GuiWindowInterface
{
    public:
        DiagnosticsWindow(irr::gui::IGUIEnvironment *guiEnv);
        // overrides
        virtual void validate();
        virtual void initialize();
        virtual void update();
    protected:
    private:
};

#endif // DIAGNOSTICSWINDOW_H
