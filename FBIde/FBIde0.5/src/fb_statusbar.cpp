/////////////////////////////////////////////////////////////////////////////
// Name:        fb_statusbar.cpp
// Purpose:     
// Author:      VonGodric
// Modified by: 
// Created:     08/03/05 14:23:04
// RCS-ID:      
// Copyright:   
// Licence:     GPL
/////////////////////////////////////////////////////////////////////////////


#include "inc/wxall.h"
#include "inc/fb_frame.h"
#include "inc/fb_statusbar.h"

FB_StatusBar::FB_StatusBar( FB_Frame * parent ) :
    m_Parent( parent ), m_StatusBar( NULL ) {  }

FB_StatusBar::~FB_StatusBar() {
    DestroyStatusBar();
}


void FB_StatusBar::Show( bool status ) {
    if( status ) CreateStatusBar();
    else DestroyStatusBar();
}


void FB_StatusBar::CreateStatusBar() {
    if( m_StatusBar != NULL ) return;
    m_StatusBar = new wxStatusBar( m_Parent, wxID_ANY );
    
    int arrWidths[] = { 65, 100, -1 };
    
    m_StatusBar->SetFieldsCount( 3, arrWidths );
    
    m_Parent->SetStatusBar( m_StatusBar );
    m_Parent->SetStatusBarPane( 2 );
}


void FB_StatusBar::DestroyStatusBar() {
    if( m_StatusBar == NULL ) return;
    delete m_StatusBar;
    m_StatusBar = NULL;
    m_Parent->SetStatusBar( NULL );
}


void FB_StatusBar::SetStatusText( const wxString& text, int i ) {
    if( m_StatusBar == NULL ) return;
    m_StatusBar->SetStatusText( text, i );
}
