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
BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_CLOSE ( MyFrame::OnClose )
    EVT_MENU(Menu_Quit,                 MyFrame::OnQuit)
    EVT_MENU(Menu_About,                MyFrame::OnAbout)
    EVT_MENU(Menu_New,	                MyFrame::OnNew)
    EVT_MENU(Menu_Open,                 MyFrame::OnOpen)
    EVT_MENU(Menu_Save,                 MyFrame::OnSave)
    EVT_MENU(Menu_SaveAS,               MyFrame::OnSaveAs)
    EVT_MENU(Menu_SaveAll,              MyFrame::OnSaveAll)
    EVT_MENU(Menu_Close,                MyFrame::OnCloseFile)
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
    
    EVT_NOTEBOOK_PAGE_CHANGED(-1,       MyFrame::ChangeNBPage)
    
END_EVENT_TABLE()

IMPLEMENT_APP(MyApp)
//------------------------------------------------------------------------------



bool MyApp::OnInit()
{
    SetVendorName(_T("FBIde"));
    SetAppName(_T("FBIde"));
    MyFrame *frame = new MyFrame(this, _T(PRODUCT_NAME));
    frame->Show(true);
    return true;
}



//------------------------------------------------------------------------------
MyFrame::MyFrame(MyApp * App, const wxString& title)
       : wxFrame( 0, wxID_ANY, title )
{
    FB_App = App;
    SetIcon(wxICON(sample));
    
    LoadSettings();
    LoadkwFile ( SyntaxFile );
    Style = LoadThemeFile( ThemeFile );
    
    FindData        = new wxFindReplaceData(wxFR_DOWN);
    ReplaceData     = new wxFindReplaceData(wxFR_DOWN);
    FindDialog      = NULL;
    ReplaceDialog   = NULL;

    LoadUI();

}

void MyFrame::OnClose 	(wxCloseEvent &event) {
    if (Proceed() == 0) return;
    
    if (FBNotebook) {
        if (FBNotebook->GetPageCount())
            FBNotebook->DeleteAllPages();
        delete FBNotebook;
    }
    if (FB_Toolbar) delete FB_Toolbar;
    if (FindData)   delete FindData;
    if (ReplaceData) delete ReplaceData;
    SaveSettings();
    event.Skip();
}

wxColour GetClr         ( uint color ) {
    wxColour clr((color >> 16) & 255, (color >> 8) & 255, color & 255);
    return clr;
}

