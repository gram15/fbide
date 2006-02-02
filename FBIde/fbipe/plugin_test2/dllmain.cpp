
#include <wx/wx.h>

#include "inc/class.plugin.h"
#include "plugindialog.h"

DECLARE_PLUGIN()

class plugin_test : public classPlugin {
    
    private:
        Plugindialog    * m_Dialog;
    
    public:
    
    // constructor
    plugin_test() {
        return;
    }
    
    
    // this function is like "main" in C, but returns true | false
    // on success ot failure
    bool OnInit(  ) {
        wxString caption;
        caption << "Plugin ID:" << GetData()->GetId();
        m_Dialog = new Plugindialog( NULL, wxID_ANY, caption );
        m_Dialog->Show( true );
        return true;
    }
    
    
    // This function gets called before closing of the plugin
    void OnExit( ) {
        m_Dialog->EndModal( 0 );
        delete m_Dialog;
        return;
    }
    
    
    // testing stuff...
    void SendCommand( wxString strCmd ) {
        wxString caption;
        caption << "Plugin ID:" << GetData()->GetId();
        wxMessageBox( "Message receaved: " + strCmd, caption );
    }
    
    
    // plugin destructor
    ~plugin_test() {
        return;
    }

};

IMPLEMENT_PLUGIN(plugin_test)
