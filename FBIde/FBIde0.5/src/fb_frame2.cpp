/////////////////////////////////////////////////////////////////////////////
// Name:        fb_frame.cpp
// Purpose:     
// Author:      VonGodric
// Modified by: 
// Created:     08/03/05 14:23:04
// RCS-ID:      
// Copyright:   
// Licence:     GPL
/////////////////////////////////////////////////////////////////////////////


#include "wx/wx.h"

#include "inc/fb_console.h"
#include "inc/fb_browser.h"
#include "inc/fb_statusbar.h"
#include "inc/fb_tab.h"
#include "inc/fb_frame.h"


void FB_Frame::CreatePanels()
{

    HSplitter = new wxSplitterWindow( 
        this, 10, wxDefaultPosition, wxDefaultSize, 
        wxSP_FULLSASH|wxNO_BORDER );
    HSplitter->SetSashGravity( 1.0 );
    HSplitter->SetMinimumPaneSize( 100 );
    
    VSplitter = new wxSplitterWindow( 
        HSplitter, 100, wxDefaultPosition, wxDefaultSize, 
        wxSP_FULLSASH|wxNO_BORDER );
    VSplitter->SetMinimumPaneSize( 100 );
    
    Console_area = new FB_Console( HSplitter );
    Browser_area = new FB_Browser( VSplitter );
    fbtab = new FB_Tab( this );
    //Code_area = new wxPanel( VSplitter, 14, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
    //Code_area->SetBackgroundColour(wxSystemSettings::GetColour( wxSYS_COLOUR_APPWORKSPACE ));
           
    if ( FBIde_Config.ShowProject ) {
        VSplitter->SplitVertically( Browser_area, Code_area, 150 );
        ViewProject->Check( true );
    } else {
        VSplitter->Initialize( Code_area );
    }
    
    if ( FBIde_Config.ShowConsole ) {
        HSplitter->SplitHorizontally( VSplitter, Console_area, -100 );
        ViewConsole->Check( true );
    } else {
        HSplitter->Initialize( VSplitter );
    }

}


void FB_Frame::CreateStatusBar() {
    
    StatusBar = new FB_StatusBar( this );
    
    if ( FBIde_Config.ShowStatusBar ) 
    {
        SetStatusBar( StatusBar );
        ViewStatusBar->Check( true );
    } 
    else 
    {
        StatusBar->Hide();
        SetStatusBar( NULL );
    }
    
}


