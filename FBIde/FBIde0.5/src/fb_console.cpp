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

FB_Console::FB_Console( wxWindow * parent ) :
    wxNotebook( parent, wxID_ANY, 
                wxDefaultPosition, wxDefaultSize, 
                wxNB_TOP | wxCLIP_CHILDREN | wxNO_BORDER )
{
    wxImageList* imageList = new wxImageList(16, 16, true, 3);
    {
        wxBitmap bitmap(wxBITMAP(bmp_compile));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        imageList->Add(bitmap);
    }
    {
        wxBitmap bitmap(wxBITMAP(bmp_debug));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        imageList->Add(bitmap);
    }
    {
        wxBitmap bitmap(wxBITMAP(bmp_search));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        imageList->Add(bitmap);
    }
    AssignImageList( imageList );
    
    CreateCompilerTab();
    CreateDebugTab();
    CreateSearchTab();
    
}


void FB_Console::CreateCompilerTab(  ) 
{
    Compiler = new wxListCtrl( this, conID_CompileTab, 
                               wxDefaultPosition, wxDefaultSize, 
                               wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_HRULES|wxLC_VRULES );
    wxFont LbFont (8, wxMODERN, wxNORMAL, wxNORMAL, false);
    Compiler->SetFont(LbFont);
    wxListItem itemCol;
    itemCol.SetText(_("Line")); //"Line"
    itemCol.SetAlign(wxLIST_FORMAT_LEFT);
    Compiler->InsertColumn(0, itemCol);

    itemCol.SetText(_("File")); //"File"
    itemCol.SetAlign(wxLIST_FORMAT_LEFT);
    Compiler->InsertColumn(1, itemCol);
    
    itemCol.SetText(_("Error")); //"Error nr"
    itemCol.SetAlign(wxLIST_FORMAT_LEFT);
    Compiler->InsertColumn(2, itemCol);

    itemCol.SetText(_("Message")); //"Messages"
    itemCol.SetAlign(wxLIST_FORMAT_LEFT);
    Compiler->InsertColumn(3, itemCol);
    
    Compiler->SetColumnWidth( 0, 60 );
    Compiler->SetColumnWidth( 1, 150 );
    Compiler->SetColumnWidth( 2, 50 );
    Compiler->SetColumnWidth( 3, 500 );
    this->AddPage(Compiler, _("Compiler"), false, 0);
}

void FB_Console::CreateDebugTab(  ) 
{
    Debug = new wxPanel( this, conID_DebugTab, 
                         wxDefaultPosition, wxDefaultSize, 
                         wxNO_BORDER|wxTAB_TRAVERSAL );
    this->AddPage(Debug, _("Debug"), false, 1);
}

void FB_Console::CreateSearchTab(  ) 
{
    SearchResult = new wxListCtrl( this, conID_SearchTab,
                               wxDefaultPosition, wxDefaultSize, 
                               wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_HRULES|wxLC_VRULES );

    wxFont LbFont (8, wxMODERN, wxNORMAL, wxNORMAL, false);
    SearchResult->SetFont(LbFont);
    wxListItem itemCol;
    itemCol.SetText(_("Line")); //"Line"
    itemCol.SetAlign(wxLIST_FORMAT_LEFT);
    SearchResult->InsertColumn(0, itemCol);

    itemCol.SetText(_("Col")); //"File"
    itemCol.SetAlign(wxLIST_FORMAT_LEFT);
    SearchResult->InsertColumn(1, itemCol);
    
    itemCol.SetText(_("File")); //"Error nr"
    itemCol.SetAlign(wxLIST_FORMAT_LEFT);
    SearchResult->InsertColumn(2, itemCol);

    itemCol.SetText(_("Message")); //"Messages"
    itemCol.SetAlign(wxLIST_FORMAT_LEFT);
    SearchResult->InsertColumn(3, itemCol);
    
    SearchResult->SetColumnWidth( 0, 60 );
    SearchResult->SetColumnWidth( 1, 50 );
    SearchResult->SetColumnWidth( 2, 100 );
    SearchResult->SetColumnWidth( 3, 500 );
    this->AddPage(SearchResult, _("Search results"), false, 2);
}
