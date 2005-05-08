/*
* This file is part of FBIde, an open-source (cross-platform) IDE for 
* FreeBasic compiler.
* Copyright (C) 2005  Albert Varaksin
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
* Contact e-mail: Albert Varaksin <vongodric@hotmail.com>
* Program URL   : http://fbide.sourceforge.net
*/

#include "inc/main.h"
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/listbox.h>
#include "inc/fbedit.h"
#include "inc/browser.h"

BEGIN_EVENT_TABLE( SFBrowser, wxDialog)
    EVT_TEXT(SearchBoxId,       SFBrowser::OnCharAdded)
    EVT_TEXT_ENTER(SearchBoxId, SFBrowser::OnEnter)
    EVT_LIST_ITEM_SELECTED(-1,  SFBrowser::OnSelect)
    EVT_LIST_ITEM_ACTIVATED(-1, SFBrowser::OnActivate)
END_EVENT_TABLE()

SFBrowser::SFBrowser(   wxWindow* parent,
                        wxWindowID id,
                        const wxString& title,
                        long style,
                        const wxString& name )
{
    
    Parent = ( MyFrame * ) parent;
    Create(parent,id,title,wxDefaultPosition, wxSize(300, 400), style, name);
 
    Panel = new wxPanel(this, wxID_ANY,
        wxDefaultPosition, wxDefaultSize, wxCLIP_CHILDREN);
        
    SearchLabel=new wxStaticText(Panel,-1, wxT(""),wxPoint(5,7),wxSize(60,13),wxST_NO_AUTORESIZE);
    SearchLabel->SetLabel(wxT("Search:"));
    
    SearchBox=new wxTextCtrl(Panel, SearchBoxId,wxT(""),wxPoint(70,5),wxSize(220,21),wxTE_PROCESS_ENTER );
    wxBoxSizer * Sizer = new wxBoxSizer(wxVERTICAL);
    
    SFList = new wxListCtrl(   Panel, 
                               wxID_ANY, 
                               wxDefaultPosition, 
                               wxDefaultSize, 
                               wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_HRULES|wxLC_VRULES );
    
    wxFont LbFont (10, wxMODERN, wxNORMAL, wxNORMAL, false);
	SFList->SetFont(LbFont);

    
    //    wxFont LbFont (12, wxMODERN, wxNORMAL, wxNORMAL, false);
    //	SFList->SetFont(LbFont);
	
	Sizer->Add(SearchLabel, 0, 0, 0);
	Sizer->Add(SearchBox, 0, wxGROW|wxRIGHT, 0);
    Sizer->Add(SFList, 3, wxGROW | (wxALL & ~wxTOP), 0);
	
	Panel->SetSizer(Sizer);
	
	SetMinSize(wxSize(510, 300));
    
    Sizer->Fit(this);
    Sizer->SetSizeHints(this);
    
    
    wxListItem itemCol;
    itemCol.SetText(_T("Line"));
    itemCol.SetAlign(wxLIST_FORMAT_LEFT);
    SFList->InsertColumn(0, itemCol);

    itemCol.SetText(_T("Type"));
    itemCol.SetAlign(wxLIST_FORMAT_LEFT);
    SFList->InsertColumn(1, itemCol);
    
    itemCol.SetText(_T("Arguments"));
    itemCol.SetAlign(wxLIST_FORMAT_LEFT);
    SFList->InsertColumn(2, itemCol);

    SFList->SetColumnWidth( 0, 50  );
    SFList->SetColumnWidth( 1, 50 );
    SFList->SetColumnWidth( 2, 400 );
	
//	
	
    Refresh();
    
    wxString Temp;
    wxString fkw;
    wxString skw;
    int type = 0;
    wxString Arg;
    bool Add = false;
    FB_Edit * stc = Parent->stc;

    for ( int i = 0; i < stc->GetLineCount(); i++ ) {
        Temp = stc->GetLine(i);
        Temp = stc->ClearCmdLine( Temp );
        fkw = stc->GetFirstKw( Temp );
        skw = stc->GetSecondKw( Temp );
        
        if (fkw == "private"||fkw == "static") {
            if (skw=="sub") { type = 1; Add = true; }
            else if (skw =="function") { type = 2; Add = true; }
            Arg = Temp.Mid(Temp.Find(' '));
            Arg = Arg.Trim(false).Trim(true);
            Arg = Arg.Mid(Arg.Find(' '));
        }
        else if (fkw == "sub") { 
            type= 1; 
            Add = true; 
            Arg = Temp.Mid(Temp.Find(' '));
            Arg = Arg.Trim(false).Trim(true);
        }
        else if (fkw == "function" && skw.Left(1)!="=") {
            type= 2; 
            Add = true; 
            Arg = Temp.Mid(Temp.Find(' '));
            Arg = Arg.Trim(false).Trim(true);
        }
        
        if (Add) {
            Add = false;
            Temp = "";
            if (type==1) Temp << "sub";
            else  Temp << "func";
            Temp  << " " << Arg;
            
            Original.Add(Temp);
            OriginalArg.Add(Arg);
            
            OrigLineNr.push_back(i);
            OrigType.push_back(type);
        }
    } // ~for
    GenerateList("");
}


void SFBrowser::AddListItem ( int Linenr, wxString Type, wxString Message ) {

    Message=Message.Trim(true).Trim(false);
    wxString lnr;
    lnr << Linenr;
    int Itemcount = SFList->GetItemCount();
    long tmp = SFList->InsertItem(Itemcount, lnr, 0);
    SFList->SetItemData(tmp, 0);
    SFList->SetItem(Itemcount, 1, Type.Trim(true).Trim(false));
    SFList->SetItem(Itemcount, 2, Message.Trim(true).Trim(false));
}


void SFBrowser::OnCharAdded ( wxCommandEvent& event ) {
    GenerateList(event.GetString().Lower());
    return;
}


void SFBrowser::OnEnter ( wxCommandEvent& event ) {
    FB_Edit * stc = Parent->stc;
    if (SFList->GetItemCount()) {
        unsigned long linnr = 0;
        SFList->GetItemText(0).ToULong(&linnr);
        stc->GotoLine(stc->GetLineCount());
        stc->GotoLine(linnr-1);
    }
    Close(true);
}


void SFBrowser::OnSelect ( wxListEvent& event ) {
    FB_Edit * stc = Parent->stc;
    int index = event.GetIndex();
    unsigned long linnr = 0;
    SFList->GetItemText(index).ToULong(&linnr);
    stc->GotoLine(stc->GetLineCount());
    stc->GotoLine(linnr-1);
    return;
}

void SFBrowser::OnActivate ( wxListEvent& event ) {
    FB_Edit * stc = Parent->stc;
    int index = event.GetIndex();
    unsigned long linnr = 0;
    SFList->GetItemText(index).ToULong(&linnr);
    stc->GotoLine(stc->GetLineCount());
    stc->GotoLine(linnr-1);
    Close(true);
    return;
}


void SFBrowser::GenerateList ( wxString Search ) {
    
    SFList->DeleteAllItems();
    if (Search.Len()) {
        for( unsigned int i = 0; i < Original.Count(); i++) {
            if (Original[i].Contains(Search)) {
                AddListItem(OrigLineNr[i] + 1, (OrigType[i] == 1) ? "Sub" : "Func", OriginalArg[i]);
            }
        }
    }
    else {
        for( unsigned int i = 0; i < Original.Count(); i++) {
            AddListItem(OrigLineNr[i] + 1, (OrigType[i] == 1) ? "Sub" : "Func", OriginalArg[i]);
        }
    }
    return;
}


SFBrowser::~SFBrowser () {
    delete Panel;
    Parent->SFDialog=0;
//    delete this;
    return;
}
