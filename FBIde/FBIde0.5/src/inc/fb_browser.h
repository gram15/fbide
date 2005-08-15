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

#ifndef _FB_BROWSER_H_
#define _FB_BROWSER_H_

#include "wx/notebook.h"
#include "wx/treectrl.h"

class FB_Browser : public wxNotebook {
    private:
        wxTreeCtrl * Project;
        wxTreeCtrl * SFTree;
        int size;
    
    public:
        FB_Browser( wxWindow * parent );
        void SetSize( int s )  { size = s; }
        int  GetSize(  ) const { return (size == 0) ? -350 : size; }
};

#endif
