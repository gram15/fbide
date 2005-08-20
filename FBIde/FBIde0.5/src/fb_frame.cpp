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

#include "inc/fb_about.h"
#include "inc/fb_console.h"
#include "inc/fb_browser.h"
#include "inc/fb_statusbar.h"
#include "inc/fb_docmngr.h"
#include "inc/fb_config.h"
#include "inc/fb_stc.h"
#include "inc/fb_frame.h"


/*!
 * FB_Frame type definition
 */

IMPLEMENT_CLASS( FB_Frame, wxFrame )

BEGIN_EVENT_TABLE( FB_Frame, wxFrame )
    // File menu
    EVT_MENU( wxID_NEW,                 FB_Frame::OnNew )
    EVT_MENU( fbideID_NewProject,       FB_Frame::OnNewproject )
    EVT_MENU( fbideID_NewTemplate,      FB_Frame::OnNewtemplate )
    EVT_MENU( wxID_OPEN,                FB_Frame::OnOpen )
    EVT_MENU( wxID_SAVE,                FB_Frame::OnSave )
    EVT_MENU( wxID_SAVEAS,              FB_Frame::OnSaveas )
    EVT_MENU( fbideID_SaveProjectAS,    FB_Frame::OnSaveprojectas )
    EVT_MENU( wxID_SAVE_ALL,            FB_Frame::OnSaveAll )
    EVT_MENU( fbideID_SessionLoad,      FB_Frame::OnSessionload )
    EVT_MENU( fbideID_SessionSave,      FB_Frame::OnSessionsave )
    EVT_MENU( wxID_CLOSE,               FB_Frame::OnClose )
    EVT_MENU( wxID_CLOSE_ALL,           FB_Frame::OnCloseAll )
    EVT_MENU( fbideID_CloseProject,     FB_Frame::OnCloseproject )
    EVT_MENU( fbideID_NewInstance,      FB_Frame::OnNewinstance )
    EVT_MENU( wxID_EXIT,                FB_Frame::OnExit )

    // Edit menu OnEdit
    EVT_MENU_OPEN( FB_Frame::OnMenuOpen ) 
    EVT_MENU( wxID_UNDO,                FB_Frame::OnEdit )
    EVT_MENU( wxID_REDO,                FB_Frame::OnEdit )
    EVT_MENU( wxID_COPY,                FB_Frame::OnEdit )
    EVT_MENU( wxID_CUT,                 FB_Frame::OnEdit )
    EVT_MENU( wxID_PASTE,               FB_Frame::OnEdit )
    EVT_MENU( wxID_SELECTALL,           FB_Frame::OnEdit )
    EVT_MENU( fbideID_SelectLine,       FB_Frame::OnEdit )
    EVT_MENU( wxID_JUSTIFY_RIGHT,       FB_Frame::OnEdit )
    EVT_MENU( wxID_JUSTIFY_LEFT,        FB_Frame::OnEdit )
    EVT_MENU( fbideID_CommentBlock,     FB_Frame::OnEdit )
    EVT_MENU( fbideID_UncommentBlock,   FB_Frame::OnEdit )

    // Search menu
    EVT_MENU( wxID_FIND,                FB_Frame::OnFind )
    EVT_MENU( fbideID_FindNext,         FB_Frame::OnFindnext )
    EVT_MENU( wxID_REPLACE,             FB_Frame::OnReplace )
    EVT_MENU( fbideID_Goto,             FB_Frame::OnGoto )
    EVT_MENU( fbideID_IncrSearch,       FB_Frame::OnIncrsearch )
    
    // View menu
    EVT_MENU( fbideID_OutPut,           FB_Frame::OnOutput )
    EVT_MENU( fbideID_Project,          FB_Frame::OnProject )
    EVT_MENU( fbideID_ToolBar,          FB_Frame::OnToolBar )
    EVT_MENU( fbideID_StatusBar,        FB_Frame::OnStatusBar )
    EVT_MENU( fbideID_FullScreen,       FB_Frame::OnFullScreen )
    
    // Project menu
    EVT_MENU( fbideID_NewProjectFile,   FB_Frame::OnNewprojectfile )
    EVT_MENU( fbideID_ProjectAdd,       FB_Frame::OnProjectadd )
    EVT_MENU( fbideID_ProjectRemove,    FB_Frame::OnProjectremove )
    EVT_MENU( fbideID_ProjectOptions,   FB_Frame::OnProjectoptions )
    
    // Run menu
    EVT_MENU( fbideID_Compile,          FB_Frame::OnCompile )
    EVT_MENU( fbideID_CompileAndRun,    FB_Frame::OnCompileandrun )
    EVT_MENU( fbideID_RebuildAll,       FB_Frame::OnRebuildall )
    EVT_MENU( fbideID_QuickRun,         FB_Frame::OnQuickrun )
    EVT_MENU( fbideID_Run,              FB_Frame::OnRun )
    EVT_MENU( fbideID_Parameters,       FB_Frame::OnParameters )
    EVT_MENU( fbideID_Debug,            FB_Frame::OnDebug )
    EVT_MENU( fbideID_OpenConsole,      FB_Frame::OnOpenconsole )
    EVT_MENU( fbideID_ProfileAnalysis,  FB_Frame::OnProfileanalysis )
    EVT_MENU( fbideID_ShowExitCode,     FB_Frame::OnShowexitcode )
    
    // Tools menu
    EVT_MENU( wxID_PROPERTIES,          FB_Frame::OnProperties )
    EVT_MENU( fbideID_SrcFormatter,     FB_Frame::OnSrcformatter )
    
    // Help menu
    EVT_MENU( wxID_HELP,                FB_Frame::OnHelp )
    EVT_MENU( wxID_ABOUT,               FB_Frame::OnAbout )

END_EVENT_TABLE()


FB_Frame::FB_Frame( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Create( parent, id, caption, pos, size, style );
}

FB_Frame::~FB_Frame() {
    if (IsMaximized()||IsIconized()) {
        Config->winw=-1;
        Config->winh=-1;
        Config->winx=0;
        Config->winy=0;
    }
    else {
        GetSize(&Config->winw, &Config->winh);
        GetPosition(&Config->winx, &Config->winy);
    }
    delete Config;
    return;
}

bool FB_Frame::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{

    wxFrame::Create( parent, id, caption, pos, size, style );

    Config = new FB_Config(  );
        
    if ( Config->winw==-1||Config->winh==-1 ) Maximize();
    else 
    {
        wxFrame::Move(Config->winx, Config->winy);
        wxFrame::SetSize(Config->winw, Config->winh);
    }
    Show( true );
        
    StatusBar = NULL;
    Code_area = NULL;
    
    Freeze();
        CreateMenus();
        CreateToolbar();
        CreatePanels();
        CreateStatusBar();
    Thaw();
    SendSizeEvent();
    return true;

}



bool FB_Frame::ShowToolTips()
{
    return TRUE;
}

//-------

void FB_Frame::OnEdit( wxCommandEvent& event )
{
    if ( DocMngr->GetPage() ) DocMngr->GetPage()->ProcessEvent( event );
}

//-------

void FB_Frame::OnMenuOpen ( wxMenuEvent& event )
{
    if ( event.GetMenu() == EditMenu )
    {
        FB_STC * stc = DocMngr->GetPage();
        #define _ENABLE( id, func ) EditMenu->Enable( id, ( stc != 0 ) ? stc -> func : false )
            _ENABLE( wxID_UNDO,                 CanUndo() );
            _ENABLE( wxID_REDO,                 CanRedo() );
            _ENABLE( wxID_COPY,                 HasSelection() );
            _ENABLE( wxID_CUT,                  HasSelection() );
            _ENABLE( wxID_PASTE,                CanPaste() );
            _ENABLE( wxID_SELECTALL,            GetLength() );
            _ENABLE( fbideID_SelectLine,        GetLength() );
            _ENABLE( fbideID_CommentBlock,      CanComment() );
            _ENABLE( fbideID_UncommentBlock,    CanComment() );
        #undef _ENABLE
        EditMenu->Enable(wxID_JUSTIFY_RIGHT,    ( stc ) ? true : false );
        EditMenu->Enable(wxID_JUSTIFY_LEFT,     ( stc ) ? true : false );
    }
}

//-------

void FB_Frame::OnSave( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnNew( wxCommandEvent& event )
{
    DocMngr->AddPage();
}


void FB_Frame::OnNewproject( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnNewtemplate( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnOpen( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnSaveas( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnSaveprojectas( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnSaveAll( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnSessionload( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnSessionsave( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnClose( wxCommandEvent& event )
{
    DocMngr->ClosePage();
}


void FB_Frame::OnCloseAll( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnCloseproject( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnNewinstance( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnExit( wxCommandEvent& event )
{
    event.Skip();
    Close( true );
}



void FB_Frame::OnFind( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnFindnext( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnReplace( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnGoto( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnIncrsearch( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnNewprojectfile( wxCommandEvent& event )
{
    event.Skip();
}

void FB_Frame::OnProjectadd( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnProjectremove( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnProjectoptions( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnCompile( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnCompileandrun( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnRebuildall( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnQuickrun( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnRun( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnParameters( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnDebug( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnProfileanalysis( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnShowexitcode( wxCommandEvent& event )
{
    event.Skip();
}


// Toggles Console Area ON and OFF
void FB_Frame::OnOutput( wxCommandEvent& event )
{
    if ( HSplitter->IsSplit() ) { 
        Console_area->SetSize( HSplitter->GetSashPosition() );
        HSplitter->Unsplit( Console_area );
        ViewConsole->Check( false );
        Config->ShowConsole = false;
    }
    else { 
        HSplitter->SplitHorizontally( VSplitter, Console_area, Console_area->GetSize() );
        ViewConsole->Check( true );
        Config->ShowConsole = true;
    }
}


// Toggles Project Panel ON and OFF
void FB_Frame::OnProject( wxCommandEvent& event )
{
    if ( VSplitter->IsSplit() ) {
        Browser_area->SetSize( VSplitter->GetSashPosition() );
        VSplitter->Unsplit( Browser_area );
        Config->ShowProject = false;
    }
    else {
        VSplitter->SplitVertically( Browser_area, Code_area, Browser_area->GetSize() );
        Config->ShowProject = true;
    }
}


// Toggles ToolBar ON and OFF
void FB_Frame::OnToolBar( wxCommandEvent& event )
{
    wxToolBar *toolbar = GetToolBar();
    if ( !toolbar )
    {
        Config->ShowToolBar = true;
        CreateToolbar();
    }
    else
    {
        Config->ShowToolBar = false;
        delete toolbar;
        SetToolBar(NULL);
    }
}


// Toggles StatusBar ON and OFF
void FB_Frame::OnStatusBar( wxCommandEvent& event )
{
    if ( !Config->ShowStatusBar ) 
    {
        Config->ShowStatusBar = true;
        CreateStatusBar();
    } 
    else 
    {
        Config->ShowStatusBar = false;
        delete StatusBar;
        StatusBar = NULL;
        SetStatusBar( NULL );
    }
}


// Toggles fullscreen mode
void FB_Frame::OnFullScreen( wxCommandEvent& event )
{
    ShowFullScreen( !IsFullScreen(), wxFULLSCREEN_NOCAPTION | wxFULLSCREEN_NOBORDER );
    SendSizeEvent();
}


//Opens a console
void FB_Frame::OnOpenconsole( wxCommandEvent& event )
{
    int major = 0, minor = 0;
    int result = wxGetOsVersion(&major, &minor);
    if (result==wxWINDOWS_NT) wxExecute("cmd.exe");
    else if(result==wxWIN95) wxExecute("command.com");
}


void FB_Frame::OnProperties( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnSrcformatter( wxCommandEvent& event )
{
    event.Skip();
}



void FB_Frame::OnHelp( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnAbout( wxCommandEvent& event )
{
    FB_About About( this, wxID_ANY, "About" );
    About.ShowModal();
}
