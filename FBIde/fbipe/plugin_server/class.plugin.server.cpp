#include <wx/wx.h>
#include <wx/dynarray.h>
#include <wx/filename.h>

// Plugin server
#include "inc/class.plugin.server.h"

classPluginServer::~classPluginServer() {
    UnLoadAllPlugins();
    delete m_PluginData;
    return;
}



const int classPluginServer::GetPluginId ( wxFileName objFile ) {
    
    for ( int i = 0; i < GetPluginCount(); i++ )
        if ( m_arrPlugins.Item( i )->m_objFileName == objFile )
            return m_arrPlugins.Item( i )->m_ID;
    return 0;
}



classPlugin * classPluginServer::GetPlugin ( const int pluginID ) {
    
    for ( int i = 0; i < GetPluginCount(); i++ )
        if ( m_arrPlugins.Item( i )->m_ID == pluginID )
            return m_arrPlugins.Item( i )->m_objPlugin;
    return NULL;
}



void classPluginServer::UnloadPlugin ( const int pluginID ) {
    
    int pluginIndex = GetPluginIndex( pluginID );
    
    if( pluginID != -1 ) {
        m_arrPlugins.Item( pluginIndex )->m_objPlugin->OnExit();
        delete m_arrPlugins.Item( pluginIndex );
        m_arrPlugins.RemoveAt( pluginIndex );
    }
}



void classPluginServer::UnLoadAllPlugins () {
    
    while ( GetPluginCount() ) {
        m_arrPlugins.Item( 0 )->m_objPlugin->OnExit();
        delete m_arrPlugins.Item( 0 );
        m_arrPlugins.RemoveAt( 0 );
    }

}



const int classPluginServer::LoadPlugin ( wxFileName objFile ) { 
    
    objFile.Normalize();
    
    if( !objFile.IsOk() ) {
        SetError( ID_Error::PLUGIN_INVALID_FILE_NAME );
        return 0;
    }
    if( !objFile.FileExists() ) {
        SetError( ID_Error::PLUGIN_FILE_NOT_FOUND );
        return 0;
    }
    if( GetPluginId( objFile ) ) {
        SetError( ID_Error::PLUGIN_ALREADY_LOADED );
        return 0;
    }
    
    wxDynamicLibrary * objDll = new wxDynamicLibrary( objFile.GetFullPath() );
    if( !objDll->IsLoaded() ) {
        delete objDll;
        SetError( ID_Error::PLUGIN_UNKNOWN_LOAD_ERROR );
        return 0;
    } 
    
    if ( !objDll->HasSymbol( "GetPlugin" ) ) {
        objDll->Unload();
        delete objDll;
        SetError( ID_Error::PLUGIN_INVALID_FILE_TYPE );
        return 0;
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
        return 0;
    }
    
    objPlugin->SetPluginData( m_intPluginID, m_PluginData );
    
    if( !objPlugin->OnInit() ) {
        objDll->Unload();
        delete objDll;
        delete objPlugin;
        SetError( ID_Error::PLUGIN_INIT_ERROR );
        return 0;
    }
    
    m_arrPlugins.Add( new classPluginList ( m_intPluginID, objDll, objPlugin, objFile ) );
    
    return m_intPluginID++;
    
}
