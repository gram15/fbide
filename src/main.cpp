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
#include "inc/fbedit.h"
#include <wx/image.h>
#include <wx/splash.h>
#include <wx/filename.h>


//------------------------------------------------------------------------------
BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_CLOSE ( MyFrame::OnClose )
    EVT_MENU(Menu_Quit,                 MyFrame::OnQuit)
    EVT_MENU(Menu_About,                MyFrame::OnAbout)
    EVT_MENU(Menu_New,	                MyFrame::OnNew)
    EVT_MENU(Menu_Open,                 MyFrame::OnOpen)
    EVT_MENU(Menu_Save,                 MyFrame::OnSave)
    EVT_MENU(Menu_SaveAS,               MyFrame::OnSaveAs)
    EVT_MENU(Menu_SaveAll,              MyFrame::OnSaveAll)
    EVT_MENU(Menu_SessionLoad,          MyFrame::OnSessionLoad)
    EVT_MENU(Menu_SessionSave,          MyFrame::OnSessionSave)
    EVT_MENU(Menu_Close,                MyFrame::OnCloseFile_)
    EVT_MENU(Menu_CloseAll,             MyFrame::OnCloseAll_)
    EVT_MENU(Menu_NewEditor,            MyFrame::OnNewWindow)

    EVT_MENU(Menu_Undo,                 MyFrame::OnMenuUndo)
    EVT_MENU(Menu_Redo,                 MyFrame::OnMenuRedo) 
    EVT_MENU(Menu_Cut,                  MyFrame::OnMenuCut)
    EVT_MENU(Menu_Copy,                 MyFrame::OnMenuCopy)
    EVT_MENU(Menu_Paste,                MyFrame::OnMenuPaste)
    EVT_MENU(Menu_SelectAll,            MyFrame::OnSelectAll)
    EVT_MENU(Menu_SelectLine,           MyFrame::OnSelectLine)
    EVT_MENU(Menu_IndentIncrease,       MyFrame::OnIndentInc)
    EVT_MENU(Menu_IndentDecrease,       MyFrame::OnIndentDecr)
    EVT_MENU(Menu_Comment,              MyFrame::OnComment)
    EVT_MENU(Menu_UnComment,            MyFrame::OnUncomment)

	EVT_MENU(Menu_Find,                 MyFrame::OnFind)
    EVT_MENU(Menu_Replace,              MyFrame::OnReplace)
    EVT_MENU(Menu_FindNext,             MyFrame::OnFindAgain)
    EVT_MENU(Menu_GotoLine,             MyFrame::OnGotoLine)
    EVT_FIND(-1,                        MyFrame::FindButton)
    EVT_FIND_CLOSE(-1,                  MyFrame::FindClose)
    EVT_FIND_NEXT(-1,                   MyFrame::MenuFindNext)
    EVT_FIND_REPLACE(-1,                MyFrame::ReplaceSel)
    EVT_FIND_REPLACE_ALL(-1,            MyFrame::MenuReplaceAll)
    
    EVT_MENU(Menu_Settings,             MyFrame::OnSettings)
    EVT_MENU(Menu_Format,               MyFrame::OnFormat)
    EVT_MENU(Menu_Result,               MyFrame::OnResult)
    EVT_MENU(Menu_Subs,                 MyFrame::OnSubs)
    
    EVT_MENU(Menu_Compile,              MyFrame::OnCompile)
    EVT_MENU(Menu_CompileAndRun,        MyFrame::OnCompileAndRun)
    EVT_MENU(Menu_Run,                  MyFrame::OnRun)
    EVT_MENU(Menu_QuickRun,             MyFrame::OnQuickRun)
    EVT_MENU(Menu_CmdPromt,             MyFrame::OnCmdPromt)
    EVT_MENU(Menu_Parameters,           MyFrame::OnParameters)
    EVT_MENU(Menu_ShowExitCode,         MyFrame::OnShowExitCode)
    
    EVT_NOTEBOOK_PAGE_CHANGED(-1,       MyFrame::ChangeNBPage)
    
    EVT_LIST_ITEM_ACTIVATED(-1,         MyFrame::OnGoToError) 
    
END_EVENT_TABLE()

IMPLEMENT_APP(MyApp)
//------------------------------------------------------------------------------



bool MyApp::OnInit()
{
    SetVendorName(_T("FBIde"));
    SetAppName(_T("FBIde"));
    new MyFrame(this, GetAppName());

    return true;
}



//------------------------------------------------------------------------------
MyFrame::MyFrame(MyApp * App, const wxString& title)
       : wxFrame( 0, wxID_ANY, title )
{
    
    
//    App->wxYield();
    
    FB_App = App;
    SetIcon(wxICON(sample));
    
    LoadSettings();

    wxImage::AddHandler(new wxPNGHandler);

    wxBitmap bitmap;
    if(bitmap.LoadFile(_T(this->EditorPath+"\\ide\\splash.png"), wxBITMAP_TYPE_PNG))
    {
      new wxSplashScreen(bitmap,
          wxSPLASH_CENTRE_ON_SCREEN|wxSPLASH_TIMEOUT,
          1000, this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
          wxSIMPLE_BORDER|wxSTAY_ON_TOP);
    }

    LoadkwFile ( SyntaxFile );
    Style = LoadThemeFile( ThemeFile );
    ProcessIsRunning = false;
    IsTemp           = false;
    InitState        = false;
    
    FindData        = new wxFindReplaceData(wxFR_DOWN);
    ReplaceData     = new wxFindReplaceData(wxFR_DOWN);
    FindDialog      = NULL;
    ReplaceDialog   = NULL;

    CurrentFileType = 0;
    LoadUI();
    
    wxFileName File(FB_App->argv[1]);
    
    if(File.GetExt() == "fbs") { SessionLoad ( FB_App->argv[1] ); }
    else {
        if (FB_App->argc>1)  NewSTCPage(FB_App->argv[1], true);
    }

    Show();

}

void MyFrame::OnClose 	(wxCloseEvent &event) {
    
    if (bufferList.GetModifiedCount()) {
        int result = wxMessageBox("Save changes?", "Save before exit?", wxYES_NO | wxCANCEL | wxICON_EXCLAMATION);
        if (result==wxCANCEL) return;
        if (result==wxYES) {
            OnCloseAll ();
            if (stc) return;
        }
    }
    
    if (FBCodePanel)     delete FBCodePanel;

    SaveSettings();
    event.Skip();
}

wxColour GetClr         ( uint color ) {
    wxColour clr((color >> 16) & 255, (color >> 8) & 255, color & 255);
    return clr;
}

