/////////////////////////////////////////////////////////////////////////////
// Name:        fb_doc.h
// Purpose:     
// Author:      VonGodric
// Modified by: 
// Created:     08/03/05 14:23:04
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _FB_DOC_H_
#define _FB_DOC_H_

enum fbDoc_Enums {
    fbDoc_UNKNOWN = -1,
    fbDoc_FBDoc,
    fbDoc_RC,
    fbDoc_HTML,
    fbDoc_TXT
};

class FB_Doc {
    public:
        wxFileName  m_File;
        bool        m_IsModified;
        bool        m_IsNewFile;
        int         m_FileType;
    
    FB_Doc( wxFileName File = "", int FileType = fbDoc_UNKNOWN );
    
    wxString GetFileName() const {
        return m_File.GetFullName();
    }
    
    wxString GetFullPath() const {
        return m_File.GetFullPath();
    }
    
    wxFileName GetFile() const {
        return  m_File;
    }
    
    void SetFile( wxFileName File, int FileType = fbDoc_UNKNOWN );
    
    int DetectFileType( wxFileName File );
    
    bool IsNewDoc() const {
        return m_IsNewFile;
    }
    
    int GetDocType(  ) const {
        return m_FileType;
    }
    
    bool IsModified( ) const { return m_IsModified; }
    void SetModified( bool state ) { m_IsModified = state; }
};

#endif
