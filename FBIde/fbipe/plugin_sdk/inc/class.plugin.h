
#ifndef _CLASS_PLUGIN_H_
#define _CLASS_PLUGIN_H_
 
#define PLUGIN_EXPORT __declspec (dllexport)

	
    class classPluginData {
        private:
            int       m_ID;
            wxApp   * m_ParentApp;
            wxFrame * m_parentFrame;
        
        public:
            classPluginData( int ID, wxApp * app, wxFrame * frame ) : 
                m_ID( ID ), m_ParentApp( app ),  m_parentFrame( frame )
            { }
            
            const wxFrame * GetFrame() const { return m_parentFrame; }
            const wxApp * GetApp() const { return m_ParentApp; }
            const int GetId() const { return m_ID; }
    };
        
    
    class classPlugin : public wxEvtHandler {
	    
		public:
            classPlugin( );
            virtual bool OnInit( );
			virtual void OnExit( );
			virtual void SendCommand( wxString strCmd );
			virtual ~classPlugin();
			
			const int GetErrorCode() const { return m_ErrorCode; }
			void SetErrorCode( int intError ) { m_ErrorCode = intError; }
			
			const classPluginData * GetData() const { return m_objPluginData; }
		
            void SetPluginData( classPluginData * objPluginData ) { m_objPluginData = objPluginData; }
            
            bool m_IsAttached;
            bool m_ErrorCode;
            classPluginData * m_objPluginData;
	};


    #define DECLARE_PLUGIN() \
        extern "C" \
        { \
            PLUGIN_EXPORT classPlugin* GetPlugin(); \
        }
        
    #define IMPLEMENT_PLUGIN(name) \
        classPlugin* GetPlugin() { return new name; }

    
#endif
