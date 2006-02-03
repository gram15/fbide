
#ifndef _CLASS_PLUGIN_H_
#define _CLASS_PLUGIN_H_
 
    #include "inc/class.plugin.data.h"
    
    /**
     * This class is a base class for a plugin. All plugins are derived from 
     * this.
     */
     
    class classPlugin : public wxEvtHandler {
	    
		public:
            classPlugin( );
            
            // These are pure virtual methods that every
            // plugin must override
            virtual bool OnInit( ) = 0;
			virtual void OnExit( ) = 0;
			virtual void SendCommand( wxString strCmd ) = 0;
			
            
            virtual ~classPlugin();
			
			const classPluginData * GetData() const { return m_objPluginData; }
			const int GetId() const { return m_ID; }
            
            void SetPluginData( int ID, classPluginData * objPluginData ) { 
                m_ID = ID; 
                m_objPluginData = objPluginData; 
            }
            
        private:
            classPluginData * m_objPluginData;
            int               m_ID;
	};

   
#endif
