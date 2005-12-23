/////////////////////////////////////////////////////////////////////////////
// Name:        fb_doc.cpp
// Purpose:     
// Author:      VonGodric
// Modified by: 
// Created:     08/14/05 17:16:30
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#include "inc/wxall.h"
#include "inc/fb_doc.h"

FB_Doc::FB_Doc( wxFileName File, int FileType ) : m_File(File),  m_IsModified(false) {

    if( m_File.IsOk() && m_File.FileExists() ) {
        m_IsNewFile = false;
    } else {
        m_IsNewFile = true;
        m_File = "UnTitled";
    }
    
    if ( m_IsNewFile && FileType == fbDoc_UNKNOWN ) {
        m_FileType = fbDoc_FBDoc;
    } else {
        m_FileType = DetectFileType( m_File );
    }
}



void FB_Doc::SetFile( wxFileName File, int FileType ) {
    m_File = File;
    m_IsNewFile = false;
    m_FileType = DetectFileType( m_File );
}


int FB_Doc::DetectFileType( wxFileName File ) {
    wxString ext = File.GetExt();
    ext = ext.Lower();
    if ( ext == "bas" || ext == "bi" ) {
        return fbDoc_FBDoc;
    } else if ( ext == "html" || ext == "htm" ) {
        return fbDoc_HTML;
    } else if ( ext == "rc" ) {
        return fbDoc_RC;
    } else if ( ext == "txt" ) {
        return fbDoc_TXT;
    } else {
        return fbDoc_UNKNOWN;
    }    
}
