#ifndef MAIN_H
#define MAIN_H

class PluginApp : public wxApp {
    public:
    virtual bool OnInit();
};

enum PluginID {
    ID_PLUGIN_SEND_COMMAND = wxID_HIGHEST,
    ID_PLUGIN_CLOSE,
};

class classPluginList;

class classPlugin;
class classPluginServer;

class PluginFrame : public wxFrame {
    public:
        PluginFrame(const wxString& title);
        void OnQuit(wxCommandEvent& event);
    
    private:
        
        void OnLoadButton( wxCommandEvent& event );
        void OnPluginListRight( wxListEvent & event );
        void OnClosePlugin( wxCommandEvent & event );
        void OnSendCommand( wxCommandEvent & event );
        
        classPluginList   * m_objPluginList;
        classPluginServer * m_objPluginServer;
        int                 m_intListIndex;
        
        DECLARE_EVENT_TABLE()
};

#endif
