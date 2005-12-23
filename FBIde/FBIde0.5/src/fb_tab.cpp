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


#include "wxall.h"
#include "inc/fb_tab.h"

FB_Tab::FB_Tab( wxWindow * parent ) 
{
    Parent = ( FB_Frame* ) parent;
    tab = NULL;
    Show( false );
    tabcount = 0;
    tabvis = 0;
}

FB_Tab::~FB_Tab() 
{
    if ( tab ) delete tab;
}

void FB_Tab::Create( wxWindow* parent )
{
    tab = new wxMyNotebook( parent, wxID_ANY, 
        wxDefaultPosition, wxDefaultSize, 
        wxNO_FULL_REPAINT_ON_RESIZE|wxCLIP_CHILDREN|wxBC_DEFAULT );
}

void FB_Tab::AddPage()
{
    if ( tabcount == 0 ) Show( true );
    else if( tabcount >= 10 ) 
    {
        wxMessageBox( "Too many tabs!" );
        return;
    }
    tabcount++;
    wxString tabname("tab nr");
    tabname << tabcount;
    tab->AddPage( new wxTextCtrl( tab, wxID_ANY, "",
            wxDefaultPosition, wxDefaultSize,
            wxTE_MULTILINE  ), tabname );
    tab->Refresh();
    
}


void FB_Tab::Show( bool status ) {
    
    if(!status) {
        wxWindow * old = Parent->Code_area;
        if ( tab ) if ( old!=tab ) return;
        Parent->Code_area = new wxPanel( Parent->VSplitter, wxID_ANY );
        Parent->Code_area->SetBackgroundColour(wxSystemSettings::GetColour( wxSYS_COLOUR_APPWORKSPACE ));
        if ( old ) {
            Parent->VSplitter->ReplaceWindow( old, Parent->Code_area );
            delete old;
            tab = 0;
        }
    }
    else
    {
        if ( tab ) return;
        Create( Parent->VSplitter );
        Parent->VSplitter->ReplaceWindow( Parent->Code_area, tab );
        delete Parent->Code_area;
        Parent->Code_area = tab;
    }
}


void FB_Tab::ClosePage( int idx  )
{
    if ( !tab ) return;
    if ( idx == -1 ) idx = tab->GetSelection();
    tab->DeletePage( idx );
    tabcount--;
    if ( tabcount == 0 ) Show( false );
    
    return;
}


void FB_Tab::ClosePages( int idx[] )
{
    if ( !tab ) return;
    return;
}


void FB_Tab::CloseAll()
{
    if ( !tab ) return;
}



