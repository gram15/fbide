/////////////////////////////////////////////////////////////////////////////
// Name:        fb_browser.cpp
// Purpose:     
// Author:      VonGodric
// Modified by: 
// Created:     08/03/05 14:23:04
// RCS-ID:      
// Copyright:   
// Licence:     GPL
/////////////////////////////////////////////////////////////////////////////

#include "wx/wx.h"
#include "inc/fb_browser.h"

FB_Browser::FB_Browser( wxWindow * parent ) :
    wxNotebook( parent, wxID_ANY, 
                wxDefaultPosition, wxDefaultSize, 
                wxNB_TOP | wxCLIP_CHILDREN | wxNO_BORDER )
{
    
        Project = new wxTreeCtrl( this, wxID_ANY );
        SFTree = new wxTreeCtrl( this, wxID_ANY );
        
        this->AddPage(Project, _("Project"), true, 0);
        this->AddPage(SFTree, _("Sub/Function"), false, 1);
        size = 0;
    
}
