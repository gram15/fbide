/////////////////////////////////////////////////////////////////////////////
// Name:        fb_frame2.cpp
// Purpose:     
// Author:      VonGodric
// Modified by: 
// Created:     08/03/05 14:23:04
// RCS-ID:      
// Copyright:   
// Licence:     GPL
/////////////////////////////////////////////////////////////////////////////


#include "inc/wxall.h"

#include "inc/fb_console.h"
#include "inc/fb_browser.h"
#include "inc/fb_statusbar.h"
#include "inc/fb_config.h"
#include "inc/fb_frame.h"


void FB_Frame::CreatePanels()
{
    m_HSplitter = new wxSplitterWindow( 
        this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 
        wxSP_FULLSASH|wxNO_BORDER );
    m_HSplitter->SetSashGravity( 1.0 );
    m_HSplitter->SetMinimumPaneSize( 100 );
    
    m_VSplitter = new wxSplitterWindow( 
        m_HSplitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, 
        wxSP_FULLSASH|wxNO_BORDER );
    m_VSplitter->SetMinimumPaneSize( 130 );
    
    m_Console_area = new FB_Console( m_HSplitter );
    m_Browser_area = new FB_Browser( m_VSplitter );

    m_Code_areaTab = 0;
    m_Code_area = new wxPanel ( m_VSplitter, wxID_ANY, 
                      wxDefaultPosition, wxDefaultSize,
                      wxTAB_TRAVERSAL|wxSUNKEN_BORDER );
    m_Code_area->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_APPWORKSPACE ) );
           
    if ( m_Config->ShowProject ) {
        m_VSplitter->SplitVertically( m_Browser_area, m_Code_area, 150 );
        m_ViewProject->Check( true );
    } else {
        m_VSplitter->Initialize( m_Code_area );
    }
    
    if ( m_Config->ShowConsole ) {
        m_HSplitter->SplitHorizontally( m_VSplitter, m_Console_area, -100 );
        m_ViewConsole->Check( true );
    } else {
        m_HSplitter->Initialize( m_VSplitter );
    }
}


void FB_Frame::CreateStatusBar() {
    m_StatusBar->Show(  m_Config->ShowStatusBar );
    m_ViewStatusBar->Check(  m_Config->ShowStatusBar );
}


