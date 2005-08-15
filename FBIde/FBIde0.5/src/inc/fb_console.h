/////////////////////////////////////////////////////////////////////////////
// Name:        fb_frame.h
// Purpose:     
// Author:      VonGodric
// Modified by: 
// Created:     08/03/05 14:23:04
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _FB_CONSOLE_H_
#define _FB_CONSOLE_H_

#include "wx/notebook.h"
#include "wx/listctrl.h"

enum consoleID {
    conID_CompileTab = 200,
    conID_DebugTab,
    conID_SearchTab
};

class FB_Console : public wxNotebook {
    private:
        wxListCtrl * Compiler;
        wxListCtrl * SearchResult;
        wxPanel * Debug;
        int size;
        
    public:
        FB_Console( wxWindow * parent );
        void CreateCompilerTab(  );
        void CreateSearchTab(  );
        void CreateDebugTab(  );
        void SetSize( int s )  { size = s; }
        int  GetSize(  ) const { return (size == 0) ? -100 : size; }
};


#endif
