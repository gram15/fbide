/////////////////////////////////////////////////////////////////////////////
// Name:        fb_frame.cpp
// Purpose:     
// Author:      VonGodric
// Modified by: 
// Created:     08/03/05 14:23:04
// Licence:     GPL
/////////////////////////////////////////////////////////////////////////////

#include "wx/docview.h"
#include "inc/wxall.h"
#include "inc/wxfb_notebook.h"

#include "inc/fb_about.h"
#include "inc/fb_console.h"
#include "inc/fb_browser.h"
#include "inc/fb_statusbar.h"
#include "inc/fb_config.h"
#include "inc/fb_stc.h"
#include "inc/fb_doc.h"
#include "inc/fb_doclist.h"
#include "inc/fb_toolbar.h"
#include "inc/fb_frame.h"
#include <wx/sysopt.h>


/*!
 * FB_Frame type definition
 */

//IMPLEMENT_CLASS( FB_Frame, wxFrame )

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
    EVT_MENU( fbideID_CloseAET,         FB_Frame::OnCloseAET )
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
    
    // Tab handling
    EVT_MENU( fbideID_TabAreaPopUp,     FB_Frame::OnTabPopUp )
    
    // File history
    EVT_MENU_RANGE( wxID_FILE1, wxID_FILE9, FB_Frame::OnFileHistory )
    
    // tab changing
    EVT_NOTEBOOK_PAGE_CHANGED( fbideID_Notebook, FB_Frame::OnTabChanged )
    
    //on close
    EVT_CLOSE( FB_Frame::OnProgramClose )
    
END_EVENT_TABLE()


FB_Frame::FB_Frame( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style ) :
    wxFrame( parent, id, caption, pos, size, style ) {
    wxSystemOptions::SetOption(wxT("msw.notebook.themed-background"), 0);
    m_Config = new FB_Config(  );
    m_DocList = new FB_DocList;
    m_StatusBar = new FB_StatusBar( this );
    m_ToolBar = new FB_ToolBar( this );
        
    if ( m_Config->winw==-1||m_Config->winh==-1 ) {
        SetSize(300, 200);
        Centre();
        Maximize();
    }
    else {
        Move(m_Config->winx, m_Config->winy);
        SetSize(m_Config->winw, m_Config->winh);
    }
    Show( true );
        
    m_Code_area = NULL;
    m_ActiveTabID = -1;
    
    Freeze();
        CreateMenus();
        CreateToolbar();
        CreatePanels();
        CreateStatusBar();
    Thaw();

    SendSizeEvent();
    SetStatus();
    m_Config->m_FileHistory->AddFilesToMenu();
}

FB_Frame::~FB_Frame() {
    if (IsMaximized()||IsIconized()) {
        m_Config->winw=-1;
        m_Config->winh=-1;
        m_Config->winx=0;
        m_Config->winy=0;
    } else {
        GetSize(&m_Config->winw, &m_Config->winh);
        GetPosition(&m_Config->winx, &m_Config->winy);
    }
    
    delete m_Config;
    delete m_DocList;
    delete m_StatusBar;
    delete m_ToolBar;
    
    return;
}


void FB_Frame::OnEdit( wxCommandEvent& event )
{
    if( m_Code_areaTab ) {
        m_Code_areaTab->GetCurrentPage()->ProcessEvent( event );
    }
}

//-------

void FB_Frame::OnMenuOpen ( wxMenuEvent& event )
{
    if ( event.GetMenu() == m_EditMenu )
    {
        FB_STC * stc = 0;
        if( m_Code_areaTab != 0 )
            stc = reinterpret_cast<FB_STC *>( m_Code_areaTab->GetCurrentPage() );

        #define _ENABLE( id, func ) m_EditMenu->Enable( id, ( stc != 0 ) ? stc -> func : false )
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
        m_EditMenu->Enable(wxID_JUSTIFY_RIGHT,    ( stc ) ? true : false );
        m_EditMenu->Enable(wxID_JUSTIFY_LEFT,     ( stc ) ? true : false );
    }
}

//-------

void FB_Frame::OnSave( wxCommandEvent& event ) {
    SaveDocument(  );
}


void FB_Frame::OnNew( wxCommandEvent& event )
{
    CreateDocument(  );
}


void FB_Frame::OnNewproject( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnNewtemplate( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnOpen( wxCommandEvent& event ) {
    wxFileDialog dlg (this,
        _T("Load file"),
        _T(""),
        _T(".bas"),
        _T("FBFiles (*.bas)|*.bas|FBHeader files(*.bi)|*.bi|HTML files (*.html)|*.html|All file(*)|*.*|"),
    wxFILE_MUST_EXIST | wxCHANGE_DIR | wxMULTIPLE);
    
    if (dlg.ShowModal() != wxID_OK) return;
    
    wxArrayString File;
    dlg.GetPaths(File);
    
    for(int i = 0; i < static_cast<int>( File.Count() ); i++ ) {
        m_Config->m_FileHistory->AddFileToHistory( File[i] );
        CreateDocument( File[i] );
    }
    
    return;
}


void FB_Frame::OnFileHistory( wxCommandEvent& event ) {
    CreateDocument( m_Config->m_FileHistory->GetHistoryFile(( event.GetId() - wxID_FILE1 ) ) );
}


void FB_Frame::OnSaveas( wxCommandEvent& event )
{
    SaveDocumentAs();
}


void FB_Frame::OnSaveprojectas( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnSaveAll( wxCommandEvent& event )
{
    SaveAllDocuments( );
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
    CloseDocument();
}


void FB_Frame::OnCloseAll( wxCommandEvent& event )
{
    CloseAllDocument();
}


void FB_Frame::OnCloseAET( wxCommandEvent& event )
{
    CloseAET();
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
    Close( true );
}


void FB_Frame::OnProgramClose( wxCloseEvent &event )
{
    if ( !CloseAllDocument() ) return;
    event.Skip();    
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
    if ( m_HSplitter->IsSplit() ) { 
        m_Console_area->SetSize( m_HSplitter->GetSashPosition() );
        m_HSplitter->Unsplit( m_Console_area );
        m_ViewConsole->Check( false );
        m_Config->ShowConsole = false;
    }
    else { 
        m_HSplitter->SplitHorizontally( m_VSplitter, m_Console_area, m_Console_area->GetSize() );
        m_ViewConsole->Check( true );
        m_Config->ShowConsole = true;
    }
}


// Toggles Project Panel ON and OFF
void FB_Frame::OnProject( wxCommandEvent& event )
{
    Freeze();
        if ( m_VSplitter->IsSplit() ) {
            m_Browser_area->SetSize( m_VSplitter->GetSashPosition() );
            m_VSplitter->Unsplit( m_Browser_area );
            m_Config->ShowProject = false;
        }
        else {
            m_VSplitter->SplitVertically( m_Browser_area, m_Code_area, m_Browser_area->GetSize() );
            m_Config->ShowProject = true;
        }
    Thaw();
}


// Toggles ToolBar ON and OFF
void FB_Frame::OnToolBar( wxCommandEvent& event )
{
    m_Config->ShowToolBar = !m_Config->ShowToolBar;
    m_ToolBar->Show( m_Config->ShowToolBar );
}


// Toggles StatusBar ON and OFF
void FB_Frame::OnStatusBar( wxCommandEvent& event ) {
    m_Config->ShowStatusBar = !m_Config->ShowStatusBar;
    m_StatusBar->Show( m_Config->ShowStatusBar );
}


// Toggles fullscreen mode
void FB_Frame::OnFullScreen( wxCommandEvent& event ) {
    ShowFullScreen( !IsFullScreen(), wxFULLSCREEN_NOCAPTION | wxFULLSCREEN_NOBORDER );
    SendSizeEvent();
}


//Opens a console
void FB_Frame::OnOpenconsole( wxCommandEvent& event ) {
    int major = 0, minor = 0;
    int result = wxGetOsVersion(&major, &minor);
    if (result==wxWINDOWS_NT) wxExecute("cmd.exe");
    else if(result==wxWIN95) wxExecute("command.com");
}


void FB_Frame::OnProperties( wxCommandEvent& event ) {
    event.Skip();
}


void FB_Frame::OnSrcformatter( wxCommandEvent& event ) {
    event.Skip();
}



void FB_Frame::OnHelp( wxCommandEvent& event ) {
    event.Skip();
}


void FB_Frame::OnAbout( wxCommandEvent& event ) {
    FB_About About( this, wxID_ANY, "About" );
    About.ShowModal();
}
