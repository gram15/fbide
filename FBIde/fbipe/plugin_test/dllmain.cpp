
#include <wx/wx.h>

// include plugin sdk. This include will also include
// all base headers and declares data needed for plugins.
#include "inc/fbipe_sdk.h"


// Declare our plugin. This Macro is needed!
DECLARE_PLUGIN()


// Our plugin class
class plugin_test : public classPlugin {
    public:
    // constructor    
    plugin_test() {
        return;
    }
    
    // If return false then it means failed loading.
    bool OnInit(  ) {
        wxString caption;
        caption << "Plugin ID:" << GetId();
        wxMessageBox( "Hello from a plugin!", caption );
        return true;
    }
    
    // this get's called before exit ( sent by the parent )
    void OnExit( ) {
        return;
    }
    
    
    // Just testing. 
    void SendCommand( wxString strCmd ) {
        wxFrame * frame = GetData()->GetFrame();
        frame->SetTitle( strCmd );
        return;
    }
    
    
    // Destructor
    ~plugin_test() {
        wxString caption;
        caption << "Plugin ID:" << GetId();
        wxMessageBox( "Plugin Destructor", caption );
        return;
    }

};


// IMplement our plugin. This macro is needed!
IMPLEMENT_PLUGIN(plugin_test)
