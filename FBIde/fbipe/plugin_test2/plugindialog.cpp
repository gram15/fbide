/////////////////////////////////////////////////////////////////////////////
// Name:        plugindialog.cpp
// Purpose:     
// Author:      
// Modified by: 
// Created:     01/02/2006 15:20:10
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma implementation "plugindialog.h"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

////@begin includes
////@end includes

#include "plugindialog.h"

////@begin XPM images
////@end XPM images

/*!
 * Plugindialog type definition
 */

IMPLEMENT_DYNAMIC_CLASS( Plugindialog, wxDialog )

/*!
 * Plugindialog event table definition
 */

BEGIN_EVENT_TABLE( Plugindialog, wxDialog )

////@begin Plugindialog event table entries
////@end Plugindialog event table entries

END_EVENT_TABLE()

/*!
 * Plugindialog constructors
 */

Plugindialog::Plugindialog( )
{
}

Plugindialog::Plugindialog( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Create(parent, id, caption, pos, size, style);
}

/*!
 * Plugindialog creator
 */

bool Plugindialog::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin Plugindialog member initialisation
////@end Plugindialog member initialisation

////@begin Plugindialog creation
    SetExtraStyle(GetExtraStyle()|wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    GetSizer()->Fit(this);
    GetSizer()->SetSizeHints(this);
    Centre();
////@end Plugindialog creation
    return true;
}

/*!
 * Control creation for Plugindialog
 */

void Plugindialog::CreateControls()
{    
////@begin Plugindialog content construction
    Plugindialog* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    wxStaticBox* itemStaticBoxSizer3Static = new wxStaticBox(itemDialog1, wxID_ANY, _("Info"));
    wxStaticBoxSizer* itemStaticBoxSizer3 = new wxStaticBoxSizer(itemStaticBoxSizer3Static, wxHORIZONTAL);
    itemBoxSizer2->Add(itemStaticBoxSizer3, 0, wxGROW|wxALL, 5);

    wxStaticText* itemStaticText4 = new wxStaticText( itemDialog1, wxID_STATIC, _("This dialog is created by a plugin."), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticBoxSizer3->Add(itemStaticText4, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);

    wxTextCtrl* itemTextCtrl5 = new wxTextCtrl( itemDialog1, ID_TEXTCTRL, _T(""), wxDefaultPosition, wxSize(200, 100), wxTE_MULTILINE );
    itemBoxSizer2->Add(itemTextCtrl5, 1, wxGROW|wxALL, 5);

////@end Plugindialog content construction
}

/*!
 * Should we show tooltips?
 */

bool Plugindialog::ShowToolTips()
{
    return true;
}

/*!
 * Get bitmap resources
 */

wxBitmap Plugindialog::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin Plugindialog bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end Plugindialog bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon Plugindialog::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin Plugindialog icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end Plugindialog icon retrieval
}
