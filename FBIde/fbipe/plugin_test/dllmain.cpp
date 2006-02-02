
#include <wx/wx.h>

// include main plugin class.
#include "inc/class.plugin.h"

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
        caption << "Plugin ID:" << GetData()->GetId();
        wxMessageBox( "Hello from a plugin!", caption );
        return true;
    }
    
    // this get's called before exit ( sent by the parent )
    void OnExit( ) {
        return;
    }
    
    
    // Just testing. 
    void SendCommand( wxString strCmd ) {
        wxString caption;
        caption << "Plugin ID:" << GetData()->GetId();
        wxMessageBox( "Message receaved: " + strCmd, caption );
    }
    
    
    // Destructor
    ~plugin_test() {
        wxString caption;
        caption << "Plugin ID:" << GetData()->GetId();
        wxMessageBox( "Plugin Destructor", caption );
        return;
    }

};


// IMplement our plugin. This macro is needed!
IMPLEMENT_PLUGIN(plugin_test)
