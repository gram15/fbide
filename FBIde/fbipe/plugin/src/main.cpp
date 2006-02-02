
#include "wx/wx.h"
#include <wx/textctrl.h>
#include <wx/listctrl.h>
#include <wx/filename.h>

// Plugin SDK
#include "inc/class.plugin.h"

// Plugin Server
#include "inc/class.plugin.server.h"

// Local test stuff
#include "inc/class.pluginlist.h"
#include "inc/main.h"


BEGIN_EVENT_TABLE(PluginFrame, wxFrame)
    EVT_MENU(wxID_EXIT,  PluginFrame::OnQuit)
    EVT_MENU(ID_PLUGIN_CLOSE, PluginFrame::OnClosePlugin)
    EVT_MENU(ID_PLUGIN_SEND_COMMAND, PluginFrame::OnSendCommand)
    EVT_BUTTON( ID_Button_Input, PluginFrame::OnLoadButton)
    EVT_LIST_ITEM_RIGHT_CLICK( ID_PluginList, PluginFrame::OnPluginListRight )
END_EVENT_TABLE()

IMPLEMENT_APP(PluginApp)
DECLARE_APP(PluginApp) 


bool PluginApp::OnInit() {
    PluginFrame *frame = new PluginFrame(_T("Plugin test sandbox"));
    frame->Show(true);
    return true;
}




PluginFrame::PluginFrame(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title) {

    // Create menus
    wxMenu *fileMenu = new wxMenu;
    fileMenu->Append(wxID_EXIT, _T("E&xit\tAlt-X"), _T("Quit this program"));
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, _T("&File"));
    SetMenuBar(menuBar);
    
    m_objPluginList = new classPluginList( this ); 
    
    m_objPluginServer = new classPluginServer( dynamic_cast<wxApp *>(&::wxGetApp()), 
                                               dynamic_cast<wxFrame *>( this ) );

    
}




void PluginFrame::OnQuit(wxCommandEvent& WXUNUSED(event)) {
    
    /*wxDynamicLibrary * dll = m_arrDlls.Item( m_intListIndex );
    classPlugin * plugin = m_arrPlugins.Item( m_intListIndex );
    
    while( m_arrPlugins.GetCount() ) {
        plugin = m_arrPlugins.Item( 0 );
        plugin->OnExit();
        delete plugin;
        m_arrPlugins.RemoveAt( 0 );
        
        dll = m_arrDlls.Item( 0 );
        dll->Unload();
        delete dll;
        m_arrDlls.RemoveAt( 0 );
    }*/
    
    delete m_objPluginList;
    delete m_objPluginServer;
    Close(true);
}



void PluginFrame::OnPluginListRight( wxListEvent & event ) {
    m_intListIndex = event.GetIndex();
    wxMenu popup("");
    popup.Append( ID_PLUGIN_SEND_COMMAND, "Send Command" );
    popup.Append( ID_PLUGIN_CLOSE, "Close plugin" );
    PopupMenu( &popup );
}


void PluginFrame::OnClosePlugin( wxCommandEvent & event ) {
    /*wxListCtrl * objList = m_objPluginList->GetListCtrl();
    wxDynamicLibrary * dll = m_arrDlls.Item( m_intListIndex );
    classPlugin * plugin = m_arrPlugins.Item( m_intListIndex );
    
    plugin->OnExit();
    delete plugin;
    dll->Unload();
    delete dll;
    m_arrDlls.RemoveAt( m_intListIndex );
    m_arrPlugins.RemoveAt( m_intListIndex );
    objList->DeleteItem( m_intListIndex );*/
    return;
}


void PluginFrame::OnSendCommand( wxCommandEvent & event ) {
    /*classPlugin * plugin = m_arrPlugins.Item( m_intListIndex );
    wxTextEntryDialog dialog(this, "Enter command to send" );
    if ( dialog.ShowModal() == wxID_OK ) {
       // plugin->SendCommand( dialog.GetValue() );
    }*/
}


void PluginFrame::OnLoadButton(wxCommandEvent& WXUNUSED(event)) {
    
    wxTextCtrl * objInput = m_objPluginList->GetTextCtrl();
    wxListCtrl * objList = m_objPluginList->GetListCtrl();
    
    wxFileName objInputFile( objInput->GetValue() );
    
    int result = m_objPluginServer->LoadPlugin( objInputFile );
    
    if( result == -1 ) {
        wxString strError;
        switch( m_objPluginServer->GetError() ) {
            case ID_Error::PLUGIN_FILE_NOT_FOUND :
                strError = "File not found!";
                break;
            case ID_Error::PLUGIN_INVALID_FILE_NAME :
                strError = "Invalid file name";
                break;
            case ID_Error::PLUGIN_INVALID_FILE_TYPE :
                strError = "Invalid plugin file";
                break;
            case ID_Error::PLUGIN_INVALID_FILE_VERSION :
                strError = "Invalid version information";
                break;
            case ID_Error::PLUGIN_UNKNOWN_LOAD_ERROR :
                strError = "Unknown loader error!";
                break;
            case ID_Error::PLUGIN_ALREADY_LOADED :
                strError = "Plugin is already loaded";
                break;
            case ID_Error::PLUGIN_INIT_ERROR :
                strError = "There was an error with initalising the plugin!";
                break;
            default :
                strError = "UnKnown error";
                break;
        }
        wxMessageBox( strError );
        return;
    }
                   
    int intItemCount = objList->GetItemCount();
    objList->InsertItem( intItemCount, objInputFile.GetFullPath(), 0 );
    wxString strID;
    strID << result;
    objList->SetItem( intItemCount, 1, strID );

}
