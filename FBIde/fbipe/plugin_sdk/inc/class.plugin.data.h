#ifndef _CLASS_PLUGIN_DATA_H_
#define _CLASS_PLUGIN_DATA_H_

    class classPluginData {
        private:
            wxApp   * m_ParentApp;
            wxFrame * m_parentFrame;
        
        public:
            classPluginData( wxApp * app, wxFrame * frame ) : 
                m_ParentApp( app ),  m_parentFrame( frame )
            { }
            
            const wxFrame * GetFrame() const { return m_parentFrame; }
            const wxApp * GetApp() const { return m_ParentApp; }
    };
    
#endif
