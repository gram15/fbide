#ifndef _CLASS_PLUGIN_DATA_H_
#define _CLASS_PLUGIN_DATA_H_

    class classPluginData {
        private:
            wxApp                   * m_ParentApp;
            wxFrame                 * m_parentFrame;
        
        public :
            classPluginData( wxApp * app, wxFrame * frame );
             wxFrame * GetFrame() const { return m_parentFrame; }
             wxApp * GetApp() const { return m_ParentApp; }
    };
    
#endif
