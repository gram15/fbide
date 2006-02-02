
#include <wx/wx.h>
#include <wx/dynlib.h>
#include <wx/dynarray.h>
#include <wx/filename.h>

// Plugin SDK
#include "inc/class.plugin.h"

// Plugin server
#include "inc/class.plugin.server.h"

classPluginServer::~classPluginServer () {
    return;
}



int classPluginServer::GetPluginId ( wxFileName objFile ) {
    return 0;
}



int classPluginServer::LoadPlugin ( wxFileName objFile ) { 
    
    objFile.Normalize();
    
    if( !objFile.IsOk() ) {
        SetError( ID_Error::PLUGIN_INVALID_FILE_NAME );
        return -1;
    }
    if( !objFile.FileExists() ) {
        SetError( ID_Error::PLUGIN_FILE_NOT_FOUND );
        return -1;
    }
    
    wxDynamicLibrary * objDll = new wxDynamicLibrary( objFile.GetFullPath() );
    if( !objDll->IsLoaded() ) {
        delete objDll;
        SetError( ID_Error::PLUGIN_UNKNOWN_LOAD_ERROR );
        return -1;
    } 
    
    if ( !objDll->HasSymbol( "GetPlugin" ) ) {
        objDll->Unload();
        delete objDll;
        SetError( ID_Error::PLUGIN_INVALID_FILE_TYPE );
        return -1;
    }
    
    typedef classPlugin*(*GetPluginProc)(void);
    GetPluginProc fnProc;
    fnProc = (GetPluginProc)objDll->GetSymbol( "GetPlugin" );
    
    classPlugin * objPlugin = 0;
    objPlugin = fnProc();
    
    if( objPlugin == 0 ) {
        objDll->Unload();
        delete objDll;
        SetError( ID_Error::PLUGIN_UNKNOWN_LOAD_ERROR );
        return -1;
    }
    
    classPluginData * objPluginData = new classPluginData ( m_intPluginID, 
                                                            m_ParentApp, 
                                                            m_ParentFrame );
    objPlugin->SetPluginData( objPluginData );
    
    if( !objPlugin->OnInit() ) {
        objDll->Unload();
        delete objDll;
        delete objPlugin;
        SetError( ID_Error::PLUGIN_INIT_ERROR );
        return -1;
    }
    
    m_arrPlugins.Add( new classPluginList ( m_intPluginID, objDll, objPlugin, objFile ) );
    
    int intReturn =  m_intPluginID;
    
    m_intPluginID++;
    
    return intReturn;
    
}
