#ifndef DIAGNOSTICSWINDOW_H_
#define DIAGNOSTICSWINDOW_H_

#include "client/guiwindowinterface.h"
#include "diagnostics.h"

class DiagnosticsWindow : public GuiWindowInterface
{
    public:
        DiagnosticsWindow(irr::gui::IGUIEnvironment *guiEnv);

        // overrides
        virtual void initialize();
        virtual void update();
        virtual void validate();
};

#endif /* DIAGNOSTICSWINDOW_H_ */
