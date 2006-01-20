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

#include <filename.h>
#include "inc/main.h"
#include "inc/fbedit.h"
#include "inc/browser.h"


//------------------------------------------------------------------------------
//Load menu's
void MyFrame::LoadUI () {

    LoadToolBar();
    LoadMenu();
    LoadStatusBar();
    
    ConsoleSize = -100;

    FB_App->SetTopWindow(this);
    Freeze();
    
        HSplitter = new wxSplitterWindow( 
            this, 10, wxDefaultPosition, wxDefaultSize, 
            wxSP_FULLSASH|wxNO_BORDER );
        HSplitter->SetSashGravity( 1.0 );
        HSplitter->SetMinimumPaneSize( 100 );
        
        FBConsole = new wxListCtrl(HSplitter, 
                                   wxID_ANY, 
                                   wxDefaultPosition, 
                                   wxDefaultSize, 
                                   wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_HRULES|wxLC_VRULES );
                wxFont LbFont (10, wxMODERN, wxNORMAL, wxNORMAL, false);
            	FBConsole->SetFont(LbFont);
                wxListItem itemCol;
                itemCol.SetText(_T(Lang[165])); //"Line"
                itemCol.SetAlign(wxLIST_FORMAT_LEFT);
                FBConsole->InsertColumn(0, itemCol);
                itemCol.SetText(_T(Lang[166])); //"File"
                itemCol.SetAlign(wxLIST_FORMAT_LEFT);
                FBConsole->InsertColumn(1, itemCol);
                itemCol.SetText(_T(Lang[167])); //"Error nr"
                itemCol.SetAlign(wxLIST_FORMAT_LEFT);
                FBConsole->InsertColumn(2, itemCol);
                itemCol.SetText(_T(Lang[161])); //"Messages"
                itemCol.SetAlign(wxLIST_FORMAT_LEFT);
                FBConsole->InsertColumn(3, itemCol);
                FBConsole->SetColumnWidth( 0, 60 );
                FBConsole->SetColumnWidth( 1, 150 );
                FBConsole->SetColumnWidth( 2, 100 );
                FBConsole->SetColumnWidth( 3, 600 );
                FBConsole->Hide();
        
        FBCodePanel = new wxPanel(HSplitter, wxID_ANY,
            wxDefaultPosition, wxDefaultSize, wxCLIP_CHILDREN);
        FBCodePanel->SetBackgroundColour(wxSystemSettings::GetColour( wxSYS_COLOUR_APPWORKSPACE ));
        HSplitter->Initialize( FBCodePanel );

    Thaw();
    SendSizeEvent();
    stc = 0;
    EnableMenus(false);
    return;

}



void MyFrame::LoadMenu () {

    MenuBar = new wxMenuBar();
    
    //File
    FB_File = new wxMenu;
    FB_File->Append (Menu_New, _T(Lang[11] + "\tCtrl+N"), _T(Lang[12]));
    FB_File->Append (Menu_Open, _T(Lang[13] + "\tCtrl+O"), _T(Lang[14]));
    
    FB_File->AppendSeparator();
    FB_File->Append (Menu_Save,	_T(Lang[15] + "\tCtrl+S"), _T(Lang[16]));
    FB_File->Append (Menu_SaveAS, _T(Lang[17] + "\tCtrl+Shift+S"), _T(Lang[18]));
    FB_File->Append (Menu_SaveAll, _T(Lang[19]), _T(Lang[20]));
    
    FB_File->AppendSeparator();
    FB_File->Append (Menu_SessionLoad, _T(Lang[169]), _T(Lang[170]));
    FB_File->Append (Menu_SessionSave, _T(Lang[171]), _T(Lang[172]));
    
    FB_File->AppendSeparator();
    FB_File->Append (Menu_Close, _T(Lang[21] + "\tCtrl+F4"), _T(Lang[22]));
    FB_File->Append (Menu_CloseAll, Lang[173], Lang[174]);

    FB_File->AppendSeparator();
    FB_File->Append (Menu_NewEditor, _T(Lang[23] + "\tShift+Ctrl+N"), _T(Lang[24]));
    FB_File->Append (Menu_Quit, _T(Lang[25] + "\tCtrl+Q"), _T(Lang[26]));



    // Edit menu
    _FB_Edit = new wxMenu;
    _FB_Edit->Append (Menu_Undo, 	_(Lang[27] + "\tCtrl+Z"), _(Lang[28]));
    _FB_Edit->Append (Menu_Redo, 	_(Lang[29] + "\tCtrl+Shift+Z"), _(Lang[30]));
    _FB_Edit->AppendSeparator();
    
    _FB_Edit->Append (Menu_Cut, 		_(Lang[31] + "\tCtrl+X"), _(Lang[32]));
    _FB_Edit->Append (Menu_Copy, 	_(Lang[33] + "\tCtrl+C"), _(Lang[34]));
    _FB_Edit->Append (Menu_Paste, 	_(Lang[35] + "\tCtrl+V"), _(Lang[36]));
    _FB_Edit->AppendSeparator();

    _FB_Edit->Append (Menu_SelectAll,	_(Lang[37] + "\tCtrl+A"), _(Lang[38]));
    _FB_Edit->Append (Menu_SelectLine,	_(Lang[39] + "\tCtrl+L"), _(Lang[40]));
    _FB_Edit->AppendSeparator();

    _FB_Edit->Append (Menu_IndentIncrease, _(Lang[41] + "\tTab"), _(Lang[42]));
    _FB_Edit->Append (Menu_IndentDecrease, _(Lang[43] + "\tShift+Tab"), _(Lang[44]));

    _FB_Edit->AppendSeparator();
    _FB_Edit->Append (Menu_Comment,      _(Lang[45] + "\tCtrl+M"), _(Lang[46]));
    _FB_Edit->Append (Menu_UnComment,    _(Lang[47] + "\tCtrl+Shift+M"), _(Lang[48]));


    // Search menu
    FB_Search = new wxMenu;
    FB_Search->Append (Menu_Find,	  _(Lang[49] + "\tCtrl+F"), _(Lang[50]));
    FB_Search->Append (Menu_FindNext, _(Lang[51] + "\tF3"), _(Lang[52]));
    FB_Search->Append (Menu_Replace,  _(Lang[53] + "\tCtrl+R"), _(Lang[54]));
    FB_Search->Append (Menu_GotoLine, _(Lang[55] + "\tCtrl+G"), _(Lang[56]));



    // View menu
    FB_View = new wxMenu;
    FB_View->Append          (Menu_Settings, _(Lang[57]), _(Lang[58]));
    FB_View->Append          (Menu_Format, Lang[175], Lang[176]);
    FB_View->AppendCheckItem (Menu_Result, _(Lang[59] + "\tF4"), _(Lang[60]));
    FB_View->Append (Menu_Subs, _(Lang[61] + "\tF2"), _(Lang[62]));
    //FB_Tools->Append (Menu_Converter, _(Language.ToolsConverter), _(Language.ToolsConverterDesc));


    //Run menu
    FB_Run = new wxMenu;
    FB_Run->Append (Menu_Compile,       _(Lang[63] + "\tCtrl+F9"), _(Lang[64]));
    FB_Run->Append (Menu_CompileAndRun, _(Lang[65] + "\tF9"), _(Lang[66]));
    FB_Run->Append (Menu_Run,           _(Lang[67] + "\tShift+Ctrl+F9"), _(Lang[68]));
    FB_Run->Append (Menu_QuickRun,      _(Lang[69] + "\tF5"), _(Lang[70]));
    FB_Run->Append (Menu_CmdPromt,      _(Lang[71] + "\tF8"), _(Lang[72]));
    FB_Run->Append (Menu_Parameters,    _(Lang[73]), _(Lang[74]));
    FB_Run->AppendCheckItem (Menu_ShowExitCode, _(Lang[77]), _(Lang[78]));
	FB_Run->Check  (Menu_ShowExitCode,  Prefs.ShowExitCode);


    //Help
    HelpMenu = new wxMenu;
    HelpMenu->Append(Menu_Help, _T(Lang[ 10 ] + "\tF1" ) );
    HelpMenu->Append(Menu_QuickKeys, _T("QuickKeys.txt") );
    HelpMenu->Append(Menu_ReadMe, _T("ReadMe.txt") );
    HelpMenu->Append(Menu_Fpp, _T("Fpp.txt") );
    HelpMenu->AppendSeparator();
    HelpMenu->Append(Menu_About,   _T(Lang[79]),    _T(Lang[80]));


    //Implement menus
    MenuBar->Append(FB_File,  _T(Lang[4]));
    MenuBar->Append(_FB_Edit,  _T(Lang[5]));
    MenuBar->Append(FB_Search,_T(Lang[6]));
    MenuBar->Append(FB_View,  _T(Lang[7]));
    MenuBar->Append(FB_Run,   _T(Lang[9]));
    MenuBar->Append(HelpMenu, _T(Lang[10]));
    MenuBar->Enable(1, false);
    
    SetMenuBar(MenuBar);
    
    return;
}



//------------------------------------------------------------------------------
// Load toolbar
void MyFrame::LoadToolBar () {
	
    // FB_Toolbar = GetToolBar();
    FB_Toolbar = CreateToolBar();
    
    // Add controls:
    wxBitmap toolBarBitmaps[15];
    toolBarBitmaps[0] = wxBITMAP(new);
    toolBarBitmaps[1] = wxBITMAP(open);
    toolBarBitmaps[2] = wxBITMAP(save);
    toolBarBitmaps[3] = wxBITMAP(cut);
    toolBarBitmaps[4] = wxBITMAP(copy);
    toolBarBitmaps[5] = wxBITMAP(paste);
    toolBarBitmaps[6] = wxBITMAP(undo);
    toolBarBitmaps[7] = wxBITMAP(redo);
    toolBarBitmaps[8] = wxBITMAP(compile);
    toolBarBitmaps[9] = wxBITMAP(run);
    toolBarBitmaps[10]= wxBITMAP(compnrun);
    toolBarBitmaps[11]= wxBITMAP(qrun);
    toolBarBitmaps[12]= wxBITMAP(saveall);
    toolBarBitmaps[13]= wxBITMAP(close);
    toolBarBitmaps[14]= wxBITMAP(output);
    
    FB_Toolbar->AddTool(Menu_New, wxBITMAP(new), wxNullBitmap, FALSE, 100, 100, (wxObject *) NULL, _(Lang[83]));
    FB_Toolbar->AddTool(Menu_Open, wxBITMAP(open), wxNullBitmap, FALSE, -1, -1, (wxObject *) NULL, _(Lang[84]));
    FB_Toolbar->AddTool(Menu_Save, toolBarBitmaps[2], wxNullBitmap, FALSE, -1, -1, (wxObject *) NULL, _(Lang[85]));
    FB_Toolbar->AddTool(Menu_SaveAll, toolBarBitmaps[12], wxNullBitmap, FALSE, -1, -1, (wxObject *) NULL, _(Lang[86]));
    FB_Toolbar->AddTool(Menu_Close, toolBarBitmaps[13], wxNullBitmap, FALSE, -1, -1, (wxObject *) NULL, _(Lang[87]));
    FB_Toolbar->AddSeparator();
    FB_Toolbar->AddTool(Menu_Cut, toolBarBitmaps[3], wxNullBitmap, FALSE, -1, -1, (wxObject *) NULL, _(Lang[88]));
    FB_Toolbar->AddTool(Menu_Copy, toolBarBitmaps[4], wxNullBitmap, FALSE, -1, -1, (wxObject *) NULL, _(Lang[89]));
    FB_Toolbar->AddTool(Menu_Paste, toolBarBitmaps[5], wxNullBitmap, FALSE, -1, -1, (wxObject *) NULL, _(Lang[90]));
    FB_Toolbar->AddSeparator();
    FB_Toolbar->AddTool(Menu_Undo, toolBarBitmaps[6], wxNullBitmap, FALSE, -1, -1, (wxObject *) NULL, _(Lang[91]));
    FB_Toolbar->AddTool(Menu_Redo, toolBarBitmaps[7], wxNullBitmap, FALSE, -1, -1, (wxObject *) NULL, _(Lang[92]));
    FB_Toolbar->AddSeparator();
    FB_Toolbar->AddTool(Menu_Compile, toolBarBitmaps[8], wxNullBitmap, FALSE, -1, -1, (wxObject *) NULL, _(Lang[93]));
    FB_Toolbar->AddTool(Menu_Run, toolBarBitmaps[9], wxNullBitmap, FALSE, -1, -1, (wxObject *) NULL, _(Lang[94]));
    FB_Toolbar->AddTool(Menu_CompileAndRun, toolBarBitmaps[10], wxNullBitmap, FALSE, -1, -1, (wxObject *) NULL, _(Lang[95]));
    FB_Toolbar->AddTool(Menu_QuickRun, toolBarBitmaps[11], wxNullBitmap, FALSE, -1, -1, (wxObject *) NULL, _(Lang[96]));
    FB_Toolbar->AddTool(Menu_Result, toolBarBitmaps[14], wxNullBitmap, FALSE, -1, -1, (wxObject *) NULL, _(Lang[97]));
    
    FB_Toolbar->Realize();


    return;
}

void MyFrame::EnableMenus ( bool state ) {
    for (int i=Menu_Save ; i<=(ProcessIsRunning ? Menu_Subs : Menu_QuickRun); i++) {
        if (i==Menu_Result||i==Menu_Settings||
            i==Menu_SessionLoad||i==Menu_FileHistory) continue;
        MenuBar->Enable(i, state );
    }
    FB_Toolbar->EnableTool(Menu_Save, state);
    FB_Toolbar->EnableTool(Menu_SaveAll, state);
    FB_Toolbar->EnableTool(Menu_Close, state);
    FB_Toolbar->EnableTool(Menu_Cut, state);
    FB_Toolbar->EnableTool(Menu_Copy, state);
    FB_Toolbar->EnableTool(Menu_Paste, state);
    FB_Toolbar->EnableTool(Menu_Undo, state);
    FB_Toolbar->EnableTool(Menu_Redo, state);
    if ( !ProcessIsRunning ) {
        FB_Toolbar->EnableTool(Menu_Compile, state);
        FB_Toolbar->EnableTool(Menu_Run, state);
        FB_Toolbar->EnableTool(Menu_CompileAndRun, state);
        FB_Toolbar->EnableTool(Menu_QuickRun, state);
    }

    return;
}

//------------------------------------------------------------------------------
// Load Statusbar
void MyFrame::LoadStatusBar () {
    CreateStatusBar(2);
    SetStatusText(_T(Lang[1]));
    return;
}


void MyFrame::NewSTCPage ( wxString InitFile, bool select, int FileType ) {
    
    void* doc;
    if ( InitFile == "" ) InitFile = FBUNNAMED;
    Buffer* buff;
    
    wxFileName File(InitFile);
    
    if(File.GetExt() == "html"||File.GetExt() == "htm") { FileType = 1; }
    else if( File.GetExt() == "txt" ) { FileType = 2; }

    if (stc==NULL) {
        EnableMenus(true);
        OldTabSelected = -1;
        Freeze();
            int style = wxNO_FULL_REPAINT_ON_RESIZE|wxCLIP_CHILDREN|wxBC_DEFAULT;
            FBNotebook = new wxMyNotebook( this, HSplitter, wxID_ANY, wxDefaultPosition,
                wxDefaultSize, style);
        
            HSplitter->ReplaceWindow( FBCodePanel, FBNotebook );
            delete FBCodePanel;
            FBCodePanel = NULL;
        
            stc = new FB_Edit( this, FBNotebook, -1, "" );
        CurrentFileType = FileType;
        stc->LoadSTCTheme( CurrentFileType );
        stc->LoadSTCSettings();
        stc->StyleClearAll();
        stc->LoadSTCTheme( CurrentFileType );
        stc->LoadSTCSettings();
        buff = bufferList.AddFileBuffer("", "");
        buff->SetFileType(FileType);
        doc = stc->GetDocPointer();
        stc->AddRefDocument(doc);
        stc->SetDocPointer(doc);
        if (InitFile!=FBUNNAMED) stc->LoadFile(InitFile);
        FBNotebook->AddPage( stc, wxFileNameFromPath(InitFile), true );
        Thaw();
    }
    else {
        stc->SetBuffer( (Buffer *) 0 );
        buff = bufferList.AddFileBuffer("", "");
        buff->SetFileType(FileType);
        SaveDocumentStatus(FBNotebook->GetSelection());
        doc = stc->CreateDocument();
        stc->AddRefDocument(doc);
        stc->SetDocPointer(doc);
        OldTabSelected = -1;
        if (InitFile!=FBUNNAMED) stc->LoadFile(InitFile);
        FBNotebook->InsertPage(FBNotebook->GetPageCount(), stc, wxFileNameFromPath(InitFile), true);
        
        if ( FileType != CurrentFileType ) {
            CurrentFileType = FileType;
            stc->LoadSTCTheme( CurrentFileType );
        }
        stc->LoadSTCSettings();
    }
    
    buff->SetFileName(InitFile);
    buff->SetModified(false);
    buff->UpdateModTime();
    buff->SetDocument(doc);
    stc->SetBuffer( (Buffer *) buff );
    stc->SetFocus();
    
    if (SFDialog) SFDialog->Rebuild();

    return;
}

void MyFrame::ChangingNBPage   ( wxNotebookEvent& event) {
    return;
}

void MyFrame::ChangeNBPage   ( wxNotebookEvent& event) {
    if (OldTabSelected==-1) {
        OldTabSelected = 0 ;
        return;
    }
    
    if (stc==0) return;
    
    int index = event.GetSelection();
    if (FBNotebook->GetPageCount()>1) SaveDocumentStatus(event.GetOldSelection());
    SetSTCPage ( index );
    SetTitle( "FBIde - " + bufferList[index]->GetFileName() );
    return;
}


void MyFrame::SaveDocumentStatus ( int docID ) {
    Buffer* buff = bufferList.GetBuffer(docID);
    buff->SetPositions(stc->GetSelectionStart(), stc->GetSelectionEnd());
    buff->SetLine(stc->GetFirstVisibleLine());
    buff->SetCaretPos(stc->GetCurrentPos());
}

void MyFrame::SetSTCPage ( int index ) {
    if (stc == 0) return;
    
    //stc->Freeze();
                
        stc->SetBuffer( (Buffer *) 0 );
        
        Buffer* buff = bufferList.GetBuffer(index);
        
        void* doc = buff->GetDocument();
        stc->AddRefDocument(doc);
        stc->SetDocPointer(doc);
    
        stc->ScrollToLine(buff->GetLine());
        stc->SetCurrentPos(buff->GetCaretPos());
        stc->SetSelectionStart(buff->GetSelectionStart());
        stc->SetSelectionEnd(buff->GetSelectionEnd());
        stc->SetFocus();
        stc->SetBuffer( (Buffer *) buff);
        if ( buff->GetFileType() != CurrentFileType ) {
            CurrentFileType = buff->GetFileType();
            stc->LoadSTCTheme( CurrentFileType );
            stc->LoadSTCSettings();
        }
        
    //stc->Thaw();
    if (SFDialog) SFDialog->Rebuild();
}

void MyFrame::SetModified ( int index, bool status ) {

    if (index==-1) index = FBNotebook->GetSelection();
    
    Buffer* buff = bufferList.GetBuffer(index);

    buff->SetWasModified(buff->GetModified());
    wxString NewName;
    if(status) NewName << "[*] ";            
    
    bufferList.SetBufferModified(index, status);
    NewName << wxFileNameFromPath(buff->GetFileName());
    FBNotebook->SetPageText( index, NewName );

}

