#include <wx/wx.h>
#include "inc/class.plugin.h"

classPlugin::classPlugin( ) {
    return;
}


classPlugin::~classPlugin() {
    delete m_objPluginData;
    return;
}


bool classPlugin::OnInit(  ) {
    return false;
}


void classPlugin::OnExit() {
    return;
}


void classPlugin::SendCommand( wxString strCmd ) {
    return;
}
