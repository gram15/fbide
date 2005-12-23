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

#include "inc/wxall.h"
#include "inc/fb_browser.h"

FB_Browser::FB_Browser( wxWindow * parent ) :
    wxNotebook( parent, wxID_ANY, 
                wxDefaultPosition, wxDefaultSize, 
                wxNB_TOP | wxCLIP_CHILDREN | wxNO_BORDER )
{

    m_Project = new wxTreeCtrl( this, wxID_ANY );
    m_SFTree = new wxTreeCtrl( this, wxID_ANY );

    wxImageList* imageList = new wxImageList(16, 16, true, 2);
    {
        wxBitmap bitmap(wxBITMAP(bmp_opnproj));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        imageList->Add(bitmap);
    }
    {
        wxBitmap bitmap(wxBITMAP(bmp_newsrc));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        imageList->Add(bitmap);
    }
    m_Project->AssignImageList( imageList );
        
    this->AddPage(m_Project, _("Project"), true, 0);
    this->AddPage(m_SFTree, _("Sub/Function"), false, 1);
    size = 0;
    
}
