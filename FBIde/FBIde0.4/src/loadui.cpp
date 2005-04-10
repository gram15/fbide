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
* Program URL   : http://www.hot.ee/fbide
*/

#include "inc/main.h"

//------------------------------------------------------------------------------
//Load menu's
void MyFrame::LoadUI () {

    LoadToolBar();
    LoadMenu();
    LoadStatusBar();

    FB_App->SetTopWindow(this);
    FBNotebook = new wxNotebook( this, -1 );
    FBNotebook->Hide();

    Show(true);    
    return;
}



void MyFrame::LoadMenu () {

    wxMenuBar *MenuBar = new wxMenuBar();
    
    //File
    wxMenu *FB_File = new wxMenu;
    FB_File->Append (Menu_New, _T("&New ..\tCtrl+N"), _T("Open new empty document"));
    FB_File->Append (Menu_Open, _T("&Open ..\tCtrl+O"), _T("Open new document"));
    FB_File->Append (Menu_Save,	_T("&Save\tCtrl+S"), _T("Save current file"));
    FB_File->Append (Menu_SaveAS, _T("Save &as ..\tCtrl+Shift+S"), _T("Save current file under new name"));
    FB_File->Append (Menu_SaveAll, _T("Save all"), _T("Save all opened files"));
    FB_File->Append (Menu_Close, _T("Close\tCtrl+F4"), _T("Close current file"));

    FB_File->AppendSeparator();
    FB_File->Append (Menu_NewEditor, _T("New &window \tShift+Ctrl+N"), _T("Open new editor window"));
    FB_File->Append (Menu_Quit, _T("&Quit\tCtrl+Q"), _T("Quit FBIde"));



   // Edit menu
    wxMenu *FB_Edit = new wxMenu;
    FB_Edit->Append (Menu_Undo, 	_("&Undo\tCtrl+Z"), _("Undo last action"));
    FB_Edit->Append (Menu_Redo, 	_("&Redo\tCtrl+Shift+Z"), _("Redo last action"));
    FB_Edit->AppendSeparator();
    
    FB_Edit->Append (Menu_Cut, 		_("Cu&t\tCtrl+X"), _("Cut selected text and copy to clipboard"));
    FB_Edit->Append (Menu_Copy, 	_("&Copy\tCtrl+C"), _("Copy selected text to clipboard"));
    FB_Edit->Append (Menu_Paste, 	_("&Paste\tCtrl+V"), _("Paste from clipboard"));
    FB_Edit->AppendSeparator();

    FB_Edit->Append (Menu_SelectAll,	_("&Select all\tCtrl+A"), _("Select whole document"));
    FB_Edit->Append (Menu_SelectLine,	_("Select &line\tCtrl+L"), _("Select current line"));
    FB_Edit->AppendSeparator();

    FB_Edit->Append (Menu_IndentIncrease, _("&Indent increase\tTab"), _("Indent selected text to right"));
    FB_Edit->Append (Menu_IndentDecrease, _("Indent reduce\tShift+Tab"), _("Deindent selected text to left"));

    FB_Edit->AppendSeparator();
    FB_Edit->Append (Menu_Comment,      _("Comment block \tCtrl+M"), _("Comments out selected text"));
    FB_Edit->Append (Menu_UnComment,    _("UnComment block\tCtrl+Shift+M"), _("Uncomments selected text"));


    // Search menu
    wxMenu *FB_Search = new wxMenu;
    FB_Search->Append (Menu_Find,	  _("Find \tCtrl+F"), _("Find in the document"));
    FB_Search->Append (Menu_FindNext, _("Find Next \tF3"), _("Repeat lest search"));
    FB_Search->Append (Menu_Replace,  _("Replace \tCtrl+R"), _("Replace text in the document"));
    FB_Search->Append (Menu_GotoLine, _("Goto line...\tCtrl+G"), _("Goyo to the line in document"));



    // View menu
    wxMenu *FB_View = new wxMenu;
    FB_View->Append          (Menu_Settings, _("Settings"), _("Set editor settings"));


    //Tools
    wxMenu *FB_Tools = new wxMenu;
    FB_Tools->Append (Menu_Subs, _("Subs... \tF2"), _("Open sub, function browser"));
    FB_Tools->Append (Menu_Converter, _("Converter"), _("Converts source code to BB or html format"));



    //Run menu
    wxMenu *FB_Run = new wxMenu;
    FB_Run->Append (Menu_Compile,       _("Compile\tCtrl+F9"), _("Compile current file"));
    FB_Run->Append (Menu_CompileAndRun, _("Compile && Run\tF9"), _("Compile and run current file"));
    FB_Run->Append (Menu_Run,           _("Run\tShift+Ctrl+F9"), _("Run previously compiled file"));
    FB_Run->Append (Menu_QuickRun,      _("Quick Run\tF5"), _("Run program without saving (uses temp file)"));
    FB_Run->Append (Menu_CmdPromt,      _("CMD Prompt\tF8"), _("Open command prompt"));
    FB_Run->Append (Menu_Parameters,    _("&Parameters..."), _("Set parameters to pass to your program"));
    FB_Run->Append (Menu_CompParam,     _("&Compiler Parameters..."), _("Set compiler parameter list prototype"));
    FB_Run->AppendCheckItem (Menu_ShowExitCode, _("&Show exit code"), _("Show\'s program exit code."));
	FB_Run->Check  (Menu_ShowExitCode,  Prefs.ShowExitCode);


    //Help
    wxMenu *HelpMenu = new wxMenu;
    HelpMenu->Append(Menu_About,   _T("&About...\tF1"),    _T("Show about dialog"));


    //Implement menus
    MenuBar->Append(FB_File,  _T("&File"));
    MenuBar->Append(FB_Edit,  _T("&Edit"));
    MenuBar->Append(FB_Search,_T("&Search"));
    MenuBar->Append(FB_View,  _T("&View"));
    MenuBar->Append(FB_Tools, _T("&Tools"));
    MenuBar->Append(FB_Run,   _T("&Run"));
    MenuBar->Append(HelpMenu, _T("&Help"));
    
    SetMenuBar(MenuBar);
    return;
}



//------------------------------------------------------------------------------
// Load toolbar
void MyFrame::LoadToolBar () {
	
    wxToolBarBase *FB_Toolbar = GetToolBar();
    FB_Toolbar = CreateToolBar(wxTB_FLAT | wxTB_TEXT);
    
    //Add controls:
    wxBitmap toolBarBitmaps[14];
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
    
    FB_Toolbar->AddTool(Menu_New, toolBarBitmaps[0], wxNullBitmap, FALSE, 100, 100, (wxObject *) NULL, "New file (Ctrl+N)");
    FB_Toolbar->AddTool(Menu_Open, toolBarBitmaps[1], wxNullBitmap, FALSE, -1, -1, (wxObject *) NULL, "Open file (Ctrl+O)");
    FB_Toolbar->AddTool(Menu_Save, toolBarBitmaps[2], wxNullBitmap, FALSE, -1, -1, (wxObject *) NULL, "Save file (Ctrl+S)");
    FB_Toolbar->AddTool(Menu_SaveAll, toolBarBitmaps[12], wxNullBitmap, FALSE, -1, -1, (wxObject *) NULL, "Save all file");
    FB_Toolbar->AddTool(Menu_Close, toolBarBitmaps[13], wxNullBitmap, FALSE, -1, -1, (wxObject *) NULL, "Close current file");
    FB_Toolbar->AddSeparator();
    FB_Toolbar->AddTool(Menu_Cut, toolBarBitmaps[3], wxNullBitmap, FALSE, -1, -1, (wxObject *) NULL, "Cut (Ctrl+X)");
    FB_Toolbar->AddTool(Menu_Copy, toolBarBitmaps[4], wxNullBitmap, FALSE, -1, -1, (wxObject *) NULL, "Copy (Ctrl+C)");
    FB_Toolbar->AddTool(Menu_Paste, toolBarBitmaps[5], wxNullBitmap, FALSE, -1, -1, (wxObject *) NULL, "Paste (Ctrl+V)");
    FB_Toolbar->AddSeparator();
    FB_Toolbar->AddTool(Menu_Undo, toolBarBitmaps[6], wxNullBitmap, FALSE, -1, -1, (wxObject *) NULL, "Undo (Ctrl+Z)");
    FB_Toolbar->AddTool(Menu_Redo, toolBarBitmaps[7], wxNullBitmap, FALSE, -1, -1, (wxObject *) NULL, "Redo (Ctrl+Shift+Z)");
    FB_Toolbar->AddSeparator();
    FB_Toolbar->AddTool(Menu_Compile, toolBarBitmaps[8], wxNullBitmap, FALSE, -1, -1, (wxObject *) NULL, "Compile (Ctrl+F9)");
    FB_Toolbar->AddTool(Menu_Run, toolBarBitmaps[9], wxNullBitmap, FALSE, -1, -1, (wxObject *) NULL, "Run (Ctrl+Shift+F9)");
    FB_Toolbar->AddTool(Menu_CompileAndRun, toolBarBitmaps[10], wxNullBitmap, FALSE, -1, -1, (wxObject *) NULL, "Compile and Run (F9)");
    FB_Toolbar->AddTool(Menu_QuickRun, toolBarBitmaps[11], wxNullBitmap, FALSE, -1, -1, (wxObject *) NULL, "Quick run (F5)");
    
    FB_Toolbar->Realize();


    return;
}



//------------------------------------------------------------------------------
// Load Statusbar
void MyFrame::LoadStatusBar () {
    CreateStatusBar(2);
    SetStatusText(_T("Welcome to FBIde!"));
    return;
}


FB_Edit * MyFrame::NewSTCPage ( wxString InitFile, bool select ) {
    
    if ( InitFile == "" ) InitFile = FBUNNAMED;
    
    if (stc==NULL)
        FBNotebook->Show();
    
    FB_Edit * stcPage = new FB_Edit( this, FBNotebook, -1, InitFile );
    FBNotebook->AddPage( stcPage, "", select );
    stcPage->LoadSTCSettings();
    stcPage->LoadSTCTheme();
    stcPage->Refresh();
    stcPage->CreateDocument();
    
    if ( InitFile != FBUNNAMED ) {
        stcPage->LoadFile(Document);        //Load file
        stcPage->ConvertEOLs(0);         	//Set windows end of lines
        stcPage->GotoPos(0);             	//Goto to the beginning of the file.
        stcPage->EnsureCaretVisible();      //Ensure that everything is visible
        wxFileName w(InitFile);             //Format filename
        InitFile = w.GetFullName();
    }
    else
        InitFile = InitFile <<  " " << ( FBNotebook->GetSelection() + 1 );
    
    FBNotebook->SetPageText(FBNotebook->GetSelection(), InitFile);
    return stcPage;

    return stc;
}


void MyFrame::ChangeNBPage   ( wxNotebookEvent& WXUNUSED(event)) {
    
    stc = (FB_Edit *) FBNotebook->GetCurrentPage();
    stc->LoadSTCSettings();
    stc->LoadSTCTheme();

    return;
}


