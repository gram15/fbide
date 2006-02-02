/////////////////////////////////////////////////////////////////////////////
// Name:        class.pluginlist.cpp
// Purpose:     
// Author:      
// Modified by: 
// Created:     01/02/2006 01:42:59
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma implementation "class.pluginlist.h"
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
#include <wx/filedlg.h>
#include "inc\class.pluginlist.h"
extern wxApp & wxGetApp();

////@begin XPM images
////@end XPM images

/*!
 * classPluginList type definition
 */

IMPLEMENT_DYNAMIC_CLASS( classPluginList, wxPanel )

/*!
 * classPluginList event table definition
 */

BEGIN_EVENT_TABLE( classPluginList, wxPanel )

////@begin classPluginList event table entries
    EVT_BUTTON( ID_BUTTON, classPluginList::OnButtonClick )

////@end classPluginList event table entries

END_EVENT_TABLE()

/*!
 * classPluginList constructors
 */

classPluginList::classPluginList( )
{
}

classPluginList::classPluginList( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
{
    Create(parent, id, pos, size, style);
}

/*!
 * classPluginList creator
 */

bool classPluginList::Create( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
{
////@begin classPluginList member initialisation
    m_objInputBox = NULL;
    m_objPluginListCtrl = NULL;
////@end classPluginList member initialisation

////@begin classPluginList creation
    wxPanel::Create( parent, id, pos, size, style );

    CreateControls();
    GetSizer()->Fit(this);
    GetSizer()->SetSizeHints(this);
////@end classPluginList creation
    return true;
}

/*!
 * Control creation for classPluginList
 */

void classPluginList::CreateControls()
{    
////@begin classPluginList content construction
    classPluginList* itemPanel1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemPanel1->SetSizer(itemBoxSizer2);

    wxStaticBox* itemStaticBoxSizer3Static = new wxStaticBox(itemPanel1, wxID_ANY, _("Load new plugin"));
    wxStaticBoxSizer* itemStaticBoxSizer3 = new wxStaticBoxSizer(itemStaticBoxSizer3Static, wxHORIZONTAL);
    itemBoxSizer2->Add(itemStaticBoxSizer3, 0, wxGROW|wxALL, 5);

    wxButton* itemButton4 = new wxButton( itemPanel1, ID_BUTTON, _("..."), wxDefaultPosition, wxSize(50, -1), 0 );
    itemStaticBoxSizer3->Add(itemButton4, 0, wxALIGN_CENTER_VERTICAL|wxRIGHT, 5);

    m_objInputBox = new wxTextCtrl( itemPanel1, ID_TextBox_Input, _T(""), wxDefaultPosition, wxSize(200, -1), 0 );
    itemStaticBoxSizer3->Add(m_objInputBox, 1, wxALIGN_TOP|wxFIXED_MINSIZE, 5);

    wxButton* itemButton6 = new wxButton( itemPanel1, ID_Button_Input, _("Load"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticBoxSizer3->Add(itemButton6, 0, wxALIGN_CENTER_VERTICAL|wxLEFT, 5);

    wxStaticBox* itemStaticBoxSizer7Static = new wxStaticBox(itemPanel1, wxID_ANY, _("Loaded plugins"));
    wxStaticBoxSizer* itemStaticBoxSizer7 = new wxStaticBoxSizer(itemStaticBoxSizer7Static, wxHORIZONTAL);
    itemBoxSizer2->Add(itemStaticBoxSizer7, 1, wxGROW|wxALL, 5);

    m_objPluginListCtrl = new wxListCtrl( itemPanel1, ID_PluginList, wxDefaultPosition, wxSize(100, 100), wxLC_REPORT|wxLC_SINGLE_SEL );
    m_objPluginListCtrl->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxNORMAL, false, _T("Tahoma")));
    itemStaticBoxSizer7->Add(m_objPluginListCtrl, 1, wxGROW, 5);

////@end classPluginList content construction
    wxListItem item;
    item.SetText("File");
    item.SetAlign(wxLIST_FORMAT_LEFT);
    m_objPluginListCtrl->InsertColumn( 0, item );
    m_objPluginListCtrl->SetColumnWidth( 0, 300  );
    
    item.SetText("ID");
    item.SetAlign(wxLIST_FORMAT_LEFT);
    m_objPluginListCtrl->InsertColumn( 1, item );
    m_objPluginListCtrl->SetColumnWidth( 1, 50  );
}

/*!
 * Should we show tooltips?
 */

bool classPluginList::ShowToolTips()
{
    return true;
}

/*!
 * Get bitmap resources
 */

wxBitmap classPluginList::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin classPluginList bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end classPluginList bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon classPluginList::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin classPluginList icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end classPluginList icon retrieval
}
/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON
 */

void classPluginList::OnButtonClick( wxCommandEvent& event )
{
    wxFileDialog dlg( this, "Choose plugin to load...", ::wxPathOnly( ::wxGetApp().argv[0] ) + "/plugins", "", "*.dll", wxOPEN | wxFILE_MUST_EXIST );
    if( dlg.ShowModal() != wxID_OK ) return;
    m_objInputBox->Clear();
    m_objInputBox->SetValue( dlg.GetPath() );
}


