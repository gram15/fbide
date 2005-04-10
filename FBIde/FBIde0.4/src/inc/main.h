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

#ifndef MAIN_H
#define MAIN_H

#include "wx/wxprec.h"
#include "wx/wx.h"
#include "wx/fileconf.h"
#include "wx/wfstream.h"
#include "wx/file.h"
#include "wx/filename.h"
#include "wx/fdrepdlg.h"
#include "wx/notebook.h"
#include "wx/panel.h"
#include <wx/sizer.h>
#include <wx/checkbox.h>
#include <wx/spinctrl.h>
#include <wx/stattext.h>
#include <wx/statline.h>
#include <wx/button.h>
#include <wx/textctrl.h>
#include <wx/listbox.h>
#include <wx/combobox.h>
#include <wx/settings.h>
#include <wx/dialog.h>
#include "wx/colordlg.h"
#include "wx/filesys.h"

// STC header
#include "wx/stc/stc.h"

//// fl headers
//#include "wx/fl/controlbar.h"    // core API
//#include "wx/fl/barhintspl.h"    // bevel for bars with "X"s and grooves
//#include "wx/fl/rowdragpl.h"     // NC-look with draggable rows
//#include "wx/fl/cbcustom.h"      // customization plugin
//#include "wx/fl/hintanimpl.h"
//#include "wx/fl/gcupdatesmgr.h"  // smooth d&d
//#include "wx/fl/antiflickpl.h"   // double-buffered repaint of decorations
//#include "wx/fl/dyntbar.h"       // auto-layout toolbar
//#include "wx/fl/dyntbarhnd.h"    // control-bar dimension handler for it


#include "../../FBIde0.4_private.h"
#define FBUNNAMED       "Untitled"
#define KWGROUPS        4
#define mySTC_STYLE_BOLD 	1
#define mySTC_STYLE_ITALIC 	2
#define mySTC_STYLE_UNDERL 	4
#define mySTC_STYLE_HIDDEN 	8

typedef unsigned int uint;

struct CommonInfo {
    bool SyntaxHighlight;
    bool IndentGuide;
    bool DisplayEOL;
    bool LineNumber;
    bool LongLine;
    bool whiteSpace;
    bool AutoIndent;
    bool BraceHighlight;
    bool ShowExitCode;
    bool FolderMargin;
    bool FloatBars;
    bool CurrentLine;
    int  TabSize;
    int  EdgeColumn;
};


typedef unsigned int uint;

struct StyleInfo {
    uint        DefaultBgColour;
    uint        DefaultFgColour;
    wxString    DefaultFont;
    int         DefaultFontSize;
    int         DefaultFontStyle;

    uint        LineNumberBgColour;
    uint        LineNumberFgColour;
    uint        SelectBgColour;
    uint        SelectFgColour;
    uint        CaretColour;
    
    uint        BraceFgColour;
    uint        BraceBgColour;
    int         BraceFontStyle;
    
    uint        BadBraceFgColour;
    uint        BadBraceBgColour;
    int         BadBraceFontStyle;

    uint        MarginBgColour;
    uint        MarginFgColour;
    int         MarginSize;
    
    uint        CaretLine;
    
    struct Info{
        uint        foreground;
        uint        background;
        wxString 	fontname;
        int    		fontsize;
        int    		fontstyle;
        int    		lettercase;

        Info( ) { };

        Info( const Info& i )
        {
            foreground  = i.foreground;
            background  = i.background;
            fontname    = i.fontname;
            fontsize    = i.fontsize;
            lettercase  = i.lettercase;
            
        }
    }Info[16];
    
    StyleInfo ( ) { };

    StyleInfo ( const StyleInfo& si )
    {
        DefaultBgColour     = si.DefaultBgColour;
        DefaultFgColour     = si.DefaultFgColour;
        DefaultFont         = si.DefaultFont;
        DefaultFontSize     = si.DefaultFontSize;
        DefaultFontStyle    = si.DefaultFontStyle;
        
        LineNumberBgColour  = si.LineNumberBgColour;
        LineNumberFgColour  = si.LineNumberFgColour;
        SelectBgColour      = si.SelectBgColour;
        SelectFgColour      = si.SelectFgColour;
        CaretColour         = si.CaretColour;
        
        BraceFgColour       = si.BraceFgColour;
        BraceBgColour       = si.BraceBgColour;
        BraceFontStyle      = si.BraceFontStyle;
        
        BadBraceFgColour    = si.BadBraceFgColour;
        BadBraceBgColour    = si.BadBraceBgColour;
        BadBraceFontStyle   = si.BadBraceFontStyle;
        
        MarginBgColour      = si.MarginBgColour;
        MarginFgColour      = si.MarginFgColour;
        MarginSize          = si.MarginSize;
        CaretLine           = si.CaretLine;
        
        for (int i=1; i<15;i++) 
            Info[i] = si.Info[i];
    }
    
};


wxColour GetClr         ( uint color );

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

class FB_Edit;

class MyFrame : public wxFrame
{
public:
    MyFrame                 ( MyApp * App, const wxString& title );
    void OnClose		    ( wxCloseEvent & event );
    void LoadSettings       (  );
    void SaveSettings       (  );
    StyleInfo LoadThemeFile ( wxString ThemeFile  );
    void SaveThemeFile      ( StyleInfo Style, wxString ThemeFile );
    void LoadkwFile         ( wxString SyntaxFile );
    void SavekwFile         ( wxString SyntaxFile );
    void LoadUI             (  );
    void LoadMenu           (  );
    void LoadToolBar        (  );
    void LoadStatusBar      (  );
    
    //FileMenu-event and related stuff
    void OnNew              ( wxCommandEvent& event );
    void OnOpen             ( wxCommandEvent& event );
    void OnSave             ( wxCommandEvent& event );
    void OnSaveAs           ( wxCommandEvent& event );
    void OnSaveAll          ( wxCommandEvent& event );
    void OnCloseFile        ( wxCommandEvent& event );
    void OnQuit             ( wxCommandEvent& event );
    void OnNewWindow        ( wxCommandEvent& event );
    int  Proceed   	        ( void );
    bool SaveFile           ( wxString FileName );
    
    
    //Editmenu-events and related stuff
    void OnMenuUndo         ( wxCommandEvent& event );
    void OnMenuRedo         ( wxCommandEvent& event );
    void OnMenuCut          ( wxCommandEvent& event );
    void OnMenuCopy         ( wxCommandEvent& event );
    void OnMenuPaste        ( wxCommandEvent& event );
    void OnSelectAll        ( wxCommandEvent& event );
    void OnSelectLine       ( wxCommandEvent& event );
    void OnIndentInc        ( wxCommandEvent& event );
    void OnIndentDecr       ( wxCommandEvent& event );
    void OnComment          ( wxCommandEvent& event );
    void OnUncomment        ( wxCommandEvent& event );    

    //Searchmenu and related stuff
    void OnFind             ( wxCommandEvent& event );
    void OnReplace          ( wxCommandEvent& event );
    void OnFindAgain        ( wxCommandEvent& event );
    void OnGotoLine         ( wxCommandEvent& event );
    void FindButton         ( wxFindDialogEvent& event );
    void FindClose          ( wxFindDialogEvent& event );
    void MenuFindNext       ( wxFindDialogEvent& event );
    void ReplaceSel         ( wxFindDialogEvent& event );
    void MenuReplaceAll     ( wxFindDialogEvent& event );
    bool HasSelection       (  );
    bool HasText            (  );
    bool FindCurrentWord    ( int direc );
    void ReplaceCurrentWord ( const wxString& text );
    void Replace            ( const wxString& findStr, const wxString& replaceStr, int flags );
    void ReplaceAll         ( const wxString& findStr, const wxString& replaceStr, int flags );
    void ReplaceText        ( int from, int to, const wxString& value );
    bool FindOccurence      ( const wxString& findStr, int direc, int flags = 0 );
    bool FindNext           (  );
    bool FindPrevious       (  );
    void FindNextWord       ( wxCommandEvent& event );
    void FindPreviousWord   ( wxCommandEvent& event );
    wxString GetTextUnderCursor (  );
    wxString GetTextUnderCursor ( int& startPos, int& endPos );
    
    
    //View menu stuff
    void OnDisplayEOL 		( wxCommandEvent &event );
	void OnIndentGuide 		( wxCommandEvent &event );
	void OnLineNumber 		( wxCommandEvent &event );
	void OnLongLineOn 		( wxCommandEvent &event );
	void OnWhiteSpace 		( wxCommandEvent &event );
	void OnSyntaxHighLight 	( wxCommandEvent &event );
	void OnAutoIndent		( wxCommandEvent &event );
	void OnBraceHighLight   ( wxCommandEvent &event );
	void OnFolderMargin     ( wxCommandEvent &event );
    void OnSettings         ( wxCommandEvent &event );
	
	

    wxFindReplaceData*      FindData;
    wxFindReplaceData*      ReplaceData;
    wxFindReplaceDialog*    FindDialog;
    wxFindReplaceDialog*    ReplaceDialog;
    wxString                findText;
    wxString                replaceText;
    wxString                findString;
    int                     FindFlags;

    
    
    void OnAbout        ( wxCommandEvent& event );
    
    FB_Edit * NewSTCPage( wxString InitFile, bool select = false );
    void ChangeNBPage   ( wxNotebookEvent& event );
    
    //Pointers
    MyApp               * FB_App;
    FB_Edit             * stc;
    wxToolBar           * FB_Toolbar;
    wxNotebook          * FBNotebook;
    wxPanel             * FBCodePanel;
    wxPanel             * FBProjectPanel;
    wxPanel             * FBConsolePanel;
    
    bool                IDE_Modified;
    int                 braceLoc;
    
    wxString CompilerPath, SyntaxFile, CMDPrototype, ThemeFile;
    wxString Document, CompiledFile, EditorPath;
    CommonInfo Prefs;
    StyleInfo  Style; 
    
    wxString Keyword[KWGROUPS + 1];
    
    wxColourData colr;
    
private:
    DECLARE_EVENT_TABLE()
};

enum
{
    Menu_Quit           = wxID_EXIT,
    Menu_About          = wxID_ABOUT,
    
    //File-menu
    Menu_New            = wxID_HIGHEST,
    Menu_NewEditor,
    Menu_Open,
    Menu_Save,
    Menu_SaveAS,
    Menu_SaveAll,
    Menu_Close,
    Menu_FileHistory,
    
	//EditMenu:
	Menu_Undo,
	Menu_Redo,
	Menu_Cut,
	Menu_Copy,
	Menu_Paste,
	Menu_SelectAll,
	Menu_SelectLine,
	Menu_IndentIncrease,
	Menu_IndentDecrease,
	Menu_Comment,
	Menu_UnComment,

	//Search:
	Menu_Find,
	Menu_FindNext,
	Menu_Replace,
	Menu_GotoLine,
	Menu_FindPrevious,
	
	//ViewMenu:
	Menu_Subs,
	Menu_Settings,
	
	//Tools menu
    Menu_Converter,

	//RunMenu
	Menu_Compile,
	Menu_CompileAndRun,
	Menu_Run,
	Menu_QuickRun,
	Menu_CmdPromt,
	Menu_Parameters,
	Menu_CompParam,
	Menu_ShowExitCode
};

#include "configdiag.h"
#include "fbedit.h"

#endif
