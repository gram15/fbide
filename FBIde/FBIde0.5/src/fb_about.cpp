/////////////////////////////////////////////////////////////////////////////
// Name:        fb_about.cpp
// Purpose:     
// Author:      VonGodric
// Modified by: 
// Created:     08/14/05 17:16:30
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#include "inc/wxall.h"

#include "inc/fb_about.h"
#include "../FBIde_private.h"

IMPLEMENT_DYNAMIC_CLASS( FB_About, wxDialog )

BEGIN_EVENT_TABLE( FB_About, wxDialog )
    EVT_CLOSE(              FB_About::OnCloseWindow )
    EVT_BUTTON( wxID_OK,    FB_About::OnOkClick )
END_EVENT_TABLE()

FB_About::FB_About( ) {  }
FB_About::FB_About( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Create(parent, id, caption, pos, size, style);
}


bool FB_About::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    SetExtraStyle(GetExtraStyle()|wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    GetSizer()->Fit(this);
    GetSizer()->SetSizeHints(this);
    Centre();
    return TRUE;
}


void FB_About::CreateControls()
{    
    FB_About* itemDialog1 = this;
    wxString temp;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    wxBitmap itemStaticBitmap3Bitmap(itemDialog1->GetBitmapResource(wxT("ide/fbide.bmp")));
    wxStaticBitmap* itemStaticBitmap3 = new wxStaticBitmap( itemDialog1, wxID_STATIC, itemStaticBitmap3Bitmap, wxDefaultPosition, wxSize(300, 75), 0 );
    itemBoxSizer2->Add(itemStaticBitmap3, 0, wxALIGN_CENTER_HORIZONTAL, 5);

    wxStaticBox* itemStaticBoxSizer4Static = new wxStaticBox(itemDialog1, wxID_ANY, _("FBIde information"));
    wxStaticBoxSizer* itemStaticBoxSizer4 = new wxStaticBoxSizer(itemStaticBoxSizer4Static, wxVERTICAL);
    itemBoxSizer2->Add(itemStaticBoxSizer4, 0, wxGROW|wxLEFT|wxRIGHT|wxBOTTOM, 5);

    temp = ""; 
    temp << "Version:    " << VER_MAJOR << "." << VER_MINOR << "." << VER_RELEASE;
    wxStaticText* itemStaticText5 = new wxStaticText( itemDialog1, wxID_STATIC, temp, wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText5->SetFont(wxFont(10, wxSWISS, wxNORMAL, 0, FALSE, _T("Courier New")));
    itemStaticBoxSizer4->Add(itemStaticText5, 0, wxALIGN_LEFT|wxLEFT|wxRIGHT|wxADJUST_MINSIZE, 5);

    temp = ""; 
    temp << "Build:      " << VER_BUILD;
    wxStaticText* itemStaticText6 = new wxStaticText( itemDialog1, wxID_STATIC, temp, wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText6->SetFont(wxFont(10, wxSWISS, wxNORMAL, 0, FALSE, _T("Courier New")));
    itemStaticBoxSizer4->Add(itemStaticText6, 0, wxALIGN_LEFT|wxLEFT|wxRIGHT|wxADJUST_MINSIZE, 5);

    temp = "";
    temp << "Build date: " << _(__DATE__);
    wxStaticText* itemStaticText7 = new wxStaticText( itemDialog1, wxID_STATIC, temp, wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText7->SetFont(wxFont(10, wxSWISS, wxNORMAL, 0, FALSE, _T("Courier New")));
    itemStaticBoxSizer4->Add(itemStaticText7, 0, wxALIGN_LEFT|wxLEFT|wxRIGHT|wxADJUST_MINSIZE, 5);

    temp = "";
    temp << "wxWidgets:  " << wxMAJOR_VERSION << "." << wxMINOR_VERSION << "." << wxRELEASE_NUMBER;
    wxStaticText* itemStaticText8 = new wxStaticText( itemDialog1, wxID_STATIC, temp, wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText8->SetFont(wxFont(10, wxSWISS, wxNORMAL, 0, FALSE, _T("Courier New")));
    itemStaticBoxSizer4->Add(itemStaticText8, 0, wxALIGN_LEFT|wxLEFT|wxRIGHT|wxADJUST_MINSIZE, 5);

    wxStaticLine* itemStaticLine9 = new wxStaticLine( itemDialog1, wxID_STATIC, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
    itemStaticBoxSizer4->Add(itemStaticLine9, 0, wxGROW|wxTOP|wxBOTTOM, 5);

    wxTextCtrl* itemTextCtrl10 = new wxTextCtrl( itemDialog1, ID_TEXTCTRL, 
        _("FBIde is an open source IDE for FreeBASIC compile. This program is under GNU GPL licence. If you notice any problems then please contact me at: vongodric@hotmail.com\n\nThis program is written in C++ and uses wxWidhets framework library for GUI and scintilla textediting control for syntax. Also we use icons from dev-cpp project.\n\nHomepage: http://fbide.sourceforge.net\ncontact: vongodric@hotmail.com"), 
        wxDefaultPosition, wxSize(-1, 100), wxTE_MULTILINE|wxTE_READONLY|wxTE_RICH );
    itemStaticBoxSizer4->Add(itemTextCtrl10, 0, wxGROW, 5);

    wxButton* itemButton11 = new wxButton( itemDialog1, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer2->Add(itemButton11, 0, wxALIGN_RIGHT|wxLEFT|wxRIGHT|wxBOTTOM, 5);

}


wxBitmap FB_About::GetBitmapResource( const wxString& name )
{
    if (name == wxT("ide/fbide.bmp"))
    {
        wxBitmap bitmap(_T("ide/fbide.bmp"), wxBITMAP_TYPE_BMP);
        return bitmap;
    }
    return wxNullBitmap;
}

void FB_About::OnOkClick( wxCommandEvent& event )
{
    this->EndModal(true);
}


void FB_About::OnCloseWindow( wxCloseEvent& event )
{
    this->EndModal(true);
}


