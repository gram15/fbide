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

    // Edit menu
    EVT_MENU( wxID_UNDO,                FB_Frame::OnUndo )
    EVT_MENU( wxID_REDO,                FB_Frame::OnRedo )
    EVT_MENU( wxID_COPY,                FB_Frame::OnCopy )
    EVT_MENU( wxID_CUT,                 FB_Frame::OnCut )
    EVT_MENU( wxID_PASTE,               FB_Frame::OnPaste )
    EVT_MENU( wxID_SELECTALL,           FB_Frame::OnSelectall )
    EVT_MENU( fbideID_SelectLine,       FB_Frame::OnSelectline )
    EVT_MENU( wxID_JUSTIFY_RIGHT,       FB_Frame::OnJustifyRight )
    EVT_MENU( wxID_JUSTIFY_LEFT,        FB_Frame::OnJustifyLeft )
    EVT_MENU( fbideID_CommentBlock,     FB_Frame::OnCommentblock )
    EVT_MENU( fbideID_UncommentBlock,   FB_Frame::OnUncommentblock )
    
    // Search menu
    EVT_MENU( wxID_FIND,                FB_Frame::OnFind )
    EVT_MENU( fbideID_FindNext,         FB_Frame::OnFindnext )
    EVT_MENU( wxID_REPLACE,             FB_Frame::OnReplace )
    EVT_MENU( fbideID_Goto,             FB_Frame::OnGoto )
    EVT_MENU( fbideID_IncrSearch,       FB_Frame::OnIncrsearch )
    
    // View menu
    EVT_MENU( fbideID_OutPut,           FB_Frame::OnOutput )
    EVT_MENU( fbideID_Project,          FB_Frame::OnProject )
    
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


bool FB_Frame::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{

    wxFrame::Create( parent, id, caption, pos, size, style );
    CreateMenus();
    CreateToolbar();
    CreatePanels();
    Centre();
    return TRUE;

}

void FB_Frame::CreatePanels()
{

    HSplitter = new wxSplitterWindow( 
        this, 10, wxDefaultPosition, wxDefaultSize, 
        wxSP_FULLSASH|wxNO_BORDER );
    HSplitter->SetSashGravity( 1.0 );

    
    VSplitter = new wxSplitterWindow( 
        HSplitter, 100, wxDefaultPosition, wxDefaultSize, 
        wxSP_FULLSASH|wxNO_BORDER );
    
    Browser_area = new FB_Browser( VSplitter );
    Code_area = new wxPanel( VSplitter, 14, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );

    Code_area->SetBackgroundColour( wxColour(192,192,0));
    
    VSplitter->SetMinimumPaneSize( 100 );
    VSplitter->SplitVertically( Browser_area, Code_area, -350 );

    Console_area = new FB_Console( HSplitter );
    
    HSplitter->SetMinimumPaneSize( 100 );
    HSplitter->SplitHorizontally( VSplitter, Console_area, -100 );
    ViewConsole->Check( true );
    ViewProject->Check( true );
}


void FB_Frame::CreateMenus()
{    
    wxMenuBar* menuBar = new wxMenuBar;
    
    // File menu
    wxMenu* FileMenu = new wxMenu;
    wxMenu* NewMenu = new wxMenu;
    {
        wxMenuItem* menuItem = new wxMenuItem(NewMenu, wxID_NEW, _("Source File\tCtrl+N"), _T(""));
        wxBitmap bitmap(wxBITMAP(bmp_newsrc));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        NewMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(NewMenu, fbideID_NewProject, _("Project..."), _T(""));
        wxBitmap bitmap(wxBITMAP(bmp_newproj));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        NewMenu->Append(menuItem);
    }
    NewMenu->AppendSeparator();
    {
        wxMenuItem* menuItem = new wxMenuItem(NewMenu, fbideID_NewTemplate, _("Template..."), _T(""));
        wxBitmap bitmap(wxBITMAP(bmp_newtemp));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        NewMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(FileMenu, ID_MENU, _("New"));
        menuItem->SetSubMenu( NewMenu );
        menuItem->SetMarginWidth( 16 );
        FileMenu->Append(menuItem);
    }
    FileMenu->AppendSeparator();
    {
        wxMenuItem* menuItem = new wxMenuItem(FileMenu, wxID_OPEN, _("Open...\tCtrl+O"), _T(""));
        wxBitmap bitmap(wxBITMAP(bmp_opnproj));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        FileMenu->Append(menuItem);
    }
    FileMenu->AppendSeparator();
    {
        wxMenuItem* menuItem = new wxMenuItem(FileMenu, wxID_SAVE, _("Save\tCtrl+S"), _T(""));
        wxBitmap bitmap(wxBITMAP(bmp_save));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        FileMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(FileMenu, wxID_SAVEAS, _("Save as ..."), _T(""));
        wxBitmap bitmap(wxBITMAP(bmp_saveas));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        FileMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(FileMenu, fbideID_SaveProjectAS, _("Save Project as ..."), _T(""));
        wxBitmap bitmap(wxBITMAP(bmp_saveas));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        FileMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(FileMenu, wxID_SAVE_ALL, _("Save All"), _T(""));
        wxBitmap bitmap(wxBITMAP(bmp_saveall));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        FileMenu->Append(menuItem);
    }
    FileMenu->AppendSeparator();
    {
        wxMenuItem* menuItem = new wxMenuItem(FileMenu, fbideID_SessionLoad, _("Load Session"), _T(""));
        menuItem->SetMarginWidth( 16 );
        FileMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(FileMenu, fbideID_SessionSave, _("Save Session"), _T(""));
        menuItem->SetMarginWidth( 16 );
        FileMenu->Append(menuItem);
    }
    FileMenu->AppendSeparator();
    {
        wxMenuItem* menuItem = new wxMenuItem(FileMenu, wxID_CLOSE, _("Close\tCtrl+F4"), _T(""));
        wxBitmap bitmap(wxBITMAP(bmp_closefl));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        FileMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(FileMenu, wxID_CLOSE_ALL, _("Cloase All"), _T(""));
        menuItem->SetMarginWidth( 16 );
        FileMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(FileMenu, fbideID_CloseProject, _("Close Project"), _T(""));
        menuItem->SetMarginWidth( 16 );
        FileMenu->Append(menuItem);
    }
    FileMenu->AppendSeparator();
    {
        wxMenuItem* menuItem = new wxMenuItem(FileMenu, fbideID_NewInstance, _("New window"), _T(""));
        menuItem->SetMarginWidth( 16 );
        FileMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(FileMenu, wxID_EXIT, _("Exit\tCtrl+Q"), _T(""));
        wxBitmap bitmap(wxBITMAP(bmp_close));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        FileMenu->Append(menuItem);
    }
    menuBar->Append(FileMenu, _("File"));
    

    // Edit menu
    wxMenu* EditMenu = new wxMenu;
    {
        wxMenuItem* menuItem = new wxMenuItem(EditMenu, wxID_UNDO, _("Undo\tCtrl+Z"), _T(""));
        wxBitmap bitmap(wxBITMAP(bmp_undo));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        EditMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(EditMenu, wxID_REDO, _("Redo\tCtrl+Shift+Z"), _T(""));
        wxBitmap bitmap(wxBITMAP(bmp_redo));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        EditMenu->Append(menuItem);
    }
    EditMenu->AppendSeparator();
    {
        wxMenuItem* menuItem = new wxMenuItem(EditMenu, wxID_COPY, _("Copy\tCtrl+C"), _T(""));
        wxBitmap bitmap(wxBITMAP(bmp_copy));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        EditMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(EditMenu, wxID_CUT, _("Cut\tCtrl+X"), _T(""));
        wxBitmap bitmap(wxBITMAP(bmp_cut));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        EditMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(EditMenu, wxID_PASTE, _("Paste\tCtrl+V"), _T(""));
        wxBitmap bitmap(wxBITMAP(bmp_paste));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        EditMenu->Append(menuItem);
    }
    EditMenu->AppendSeparator();
    {
        wxMenuItem* menuItem = new wxMenuItem(EditMenu, wxID_SELECTALL, _("Select all\tCtrl+A"), _T(""));
        menuItem->SetMarginWidth( 16 );
        EditMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(EditMenu, fbideID_SelectLine, _("Select line"), _T(""));
        menuItem->SetMarginWidth( 16 );
        EditMenu->Append(menuItem);
    }
    EditMenu->AppendSeparator();
    {
        wxMenuItem* menuItem = new wxMenuItem(EditMenu, wxID_JUSTIFY_RIGHT, _("Indent increase\tTab"), _T(""));
        menuItem->SetMarginWidth( 16 );
        EditMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(EditMenu, wxID_JUSTIFY_LEFT, _("Indent decrease\tShift+Tab"), _T(""));
        menuItem->SetMarginWidth( 16 );
        EditMenu->Append(menuItem);
    }
    EditMenu->AppendSeparator();
    {
        wxMenuItem* menuItem = new wxMenuItem(EditMenu, fbideID_CommentBlock, _("Comment block\tCtrl+M"), _T(""));
        menuItem->SetMarginWidth( 16 );
        EditMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(EditMenu, fbideID_UncommentBlock, _("UnComment Block\tCtrl+Shift+M"), _T(""));
        menuItem->SetMarginWidth( 16 );
        EditMenu->Append(menuItem);
    }
    menuBar->Append(EditMenu, _("Edit"));
    

    // Search menu
    wxMenu* SearchMenu = new wxMenu;
    {
        wxMenuItem* menuItem = new wxMenuItem(SearchMenu, wxID_FIND, _("Find...\tCtrl+F"), _T(""));
        wxBitmap bitmap(wxBITMAP(bmp_search));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        SearchMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(SearchMenu, fbideID_FindNext, _("Search again\tF3"), _T(""));
        wxBitmap bitmap(wxBITMAP(bmp_srcagain));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        SearchMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(SearchMenu, wxID_REPLACE, _("Replace"), _T(""));
        wxBitmap bitmap(wxBITMAP(bmp_srchrep));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        SearchMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(SearchMenu, fbideID_Goto, _("Goto to line\tCtrl+G"), _T(""));
        wxBitmap bitmap(wxBITMAP(bmp_goto));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        SearchMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(SearchMenu, fbideID_IncrSearch, _("Incremental Search\tCtrl+I"), _T(""));
        menuItem->SetMarginWidth( 16 );
        SearchMenu->Append(menuItem);
    }
    menuBar->Append(SearchMenu, _("Search"));


    //View menu
    wxMenu* ViewMenu = new wxMenu;
    {
        ViewConsole = new wxMenuItem(ViewMenu, fbideID_OutPut, _("Console Area\tF4"), _T(""), wxITEM_CHECK);
        ViewConsole->SetMarginWidth( 16 );
        ViewMenu->Append(ViewConsole);
    }
    {
        ViewProject = new wxMenuItem(ViewMenu, fbideID_Project, _("Project browser\tF2"), _T(""), wxITEM_CHECK);
        ViewProject->SetMarginWidth( 16 );
        ViewMenu->Append(ViewProject);
    }
    menuBar->Append(ViewMenu, _("View"));
    

    // Project menu
    wxMenu* ProjectMenu = new wxMenu;
    {
        wxMenuItem* menuItem = new wxMenuItem(ProjectMenu, fbideID_NewProjectFile, _("New file"), _T(""));
        wxBitmap bitmap(wxBITMAP(bmp_newsrc));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        ProjectMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(ProjectMenu, fbideID_ProjectAdd, _("Add to Project"), _T(""));
        wxBitmap bitmap(wxBITMAP(bmp_addsrc));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        ProjectMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(ProjectMenu, fbideID_ProjectRemove, _("Remove from Project"), _T(""));
        wxBitmap bitmap(wxBITMAP(bmp_remsrc));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        ProjectMenu->Append(menuItem);
    }
    ProjectMenu->AppendSeparator();
    {
        wxMenuItem* menuItem = new wxMenuItem(ProjectMenu, fbideID_ProjectOptions, _("Project Options\tAlt+P"), _T(""));
        wxBitmap bitmap(wxBITMAP(bmp_projopt));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        ProjectMenu->Append(menuItem);
    }
    menuBar->Append(ProjectMenu, _("Project"));
    

    // Run Menu
    wxMenu* RunMenu = new wxMenu;
    {
        wxMenuItem* menuItem = new wxMenuItem(RunMenu, fbideID_Compile, _("Compile\tCtrl+F9"), _T(""));
        wxBitmap bitmap(wxBITMAP(bmp_compile));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        RunMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(RunMenu, fbideID_CompileAndRun, _("Compile and Run\tF9"), _T(""));
        wxBitmap bitmap(wxBITMAP(bmp_comprun));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        RunMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(RunMenu, fbideID_RebuildAll, _("Rebuild All"), _T(""));
        wxBitmap bitmap(wxBITMAP(bmp_rebuild));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        RunMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(RunMenu, fbideID_QuickRun, _("Quick Run\tF5"), _T(""));
        wxBitmap bitmap(wxBITMAP(bmp_next));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        RunMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(RunMenu, fbideID_Run, _("Run\tShift+F9"), _T(""));
        wxBitmap bitmap(wxBITMAP(bmp_run));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        RunMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(RunMenu, fbideID_Parameters, _("Parameters"), _T(""));
        menuItem->SetMarginWidth( 16 );
        RunMenu->Append(menuItem);
    }
    RunMenu->AppendSeparator();
    {
        wxMenuItem* menuItem = new wxMenuItem(RunMenu, fbideID_Debug, _("Debug"), _T(""));
        wxBitmap bitmap(wxBITMAP(bmp_debug));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        RunMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(RunMenu, fbideID_OpenConsole, _("Command Prompt"), _T(""));
        wxBitmap bitmap(wxBITMAP(bmp_dos));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        RunMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(RunMenu, fbideID_ProfileAnalysis, _("Profile Analysis"), _T(""));
        menuItem->SetMarginWidth( 16 );
        RunMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(RunMenu, fbideID_ShowExitCode, _("Show exit code"), _T(""), wxITEM_CHECK);
        menuItem->SetMarginWidth( 16 );
        RunMenu->Append(menuItem);
    }
    menuBar->Append(RunMenu, _("Run"));
    

    // Tools menu
    wxMenu* ToolsMenu = new wxMenu;
    {
        wxMenuItem* menuItem = new wxMenuItem(ToolsMenu, wxID_PROPERTIES, _("Settings"), _T(""));
        wxBitmap bitmap(wxBITMAP(bmp_envopt));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        ToolsMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(ToolsMenu, fbideID_SrcFormatter, _("Formatter"), _T(""));
        wxBitmap bitmap(wxBITMAP(bmp_resrc));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        ToolsMenu->Append(menuItem);
    }
    menuBar->Append(ToolsMenu, _("Tools"));
    

    // Help menu
    wxMenu* HelpMenu = new wxMenu;
    {
        wxMenuItem* menuItem = new wxMenuItem(HelpMenu, wxID_HELP, _("Help on FBIde\tF1"), _T(""));
        wxBitmap bitmap(wxBITMAP(bmp_help));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        HelpMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(HelpMenu, wxID_ABOUT, _("About"), _T(""));
        wxBitmap bitmap(wxBITMAP(bmp_about));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        HelpMenu->Append(menuItem);
    }
    menuBar->Append(HelpMenu, _("Help"));
    this->SetMenuBar(menuBar);
}

void FB_Frame::CreateToolbar()
{    
    // Toolbar construction
    FB_Toolbar = CreateToolBar( wxTB_FLAT|wxTB_HORIZONTAL|wxNO_BORDER, ID_TOOLBAR );
    FB_Toolbar->SetToolBitmapSize(wxSize(16, 16));

    FB_Toolbar->AddTool(wxID_NEW,       _T(""), wxBITMAP(bmp_newsrc),   _T(""));
    FB_Toolbar->AddTool(wxID_OPEN,      _T(""), wxBITMAP(bmp_opnproj),  _T(""));
    FB_Toolbar->AddTool(wxID_SAVE,      _T(""), wxBITMAP(bmp_save),     _T(""));
    FB_Toolbar->AddTool(wxID_SAVE_ALL,  _T(""), wxBITMAP(bmp_saveall),  _T(""));
    FB_Toolbar->AddTool(wxID_CLOSE,     _T(""), wxBITMAP(bmp_closefl),  _T(""));
    FB_Toolbar->AddSeparator();
    FB_Toolbar->AddTool(wxID_CUT,       _T(""), wxBITMAP(bmp_cut),      _T(""));
    FB_Toolbar->AddTool(wxID_COPY,      _T(""), wxBITMAP(bmp_copy),     _T(""));
    FB_Toolbar->AddTool(wxID_PASTE,     _T(""), wxBITMAP(bmp_paste),    _T(""));
    FB_Toolbar->AddSeparator();
    FB_Toolbar->AddTool(wxID_UNDO,      _T(""), wxBITMAP(bmp_undo),     _T(""));
    FB_Toolbar->AddTool(wxID_REDO,      _T(""), wxBITMAP(bmp_redo),     _T(""));
    FB_Toolbar->AddSeparator();
    FB_Toolbar->AddTool(fbideID_Compile,        _T(""), wxBITMAP(bmp_compile),  _T(""));
    FB_Toolbar->AddTool(fbideID_Run,            _T(""), wxBITMAP(bmp_run),      _T(""));
    FB_Toolbar->AddTool(fbideID_CompileAndRun,  _T(""), wxBITMAP(bmp_comprun),  _T(""));
    FB_Toolbar->AddTool(fbideID_RebuildAll,     _T(""), wxBITMAP(bmp_rebuild),  _T(""));
    FB_Toolbar->AddTool(fbideID_QuickRun,       _T(""), wxBITMAP(bmp_next),     _T(""));
    FB_Toolbar->AddSeparator();
    FB_Toolbar->AddTool(fbideID_OutPut, _T(""), wxBITMAP(bmp_tile), _T(""));
    FB_Toolbar->Realize();

    this->SetToolBar(FB_Toolbar);

}


bool FB_Frame::ShowToolTips()
{
    return TRUE;
}




void FB_Frame::OnSave( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnNew( wxCommandEvent& event )
{
    event.Skip();
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
    event.Skip();
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


void FB_Frame::OnUndo( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnRedo( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnCopy( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnCut( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnPaste( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnSelectall( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnSelectline( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnJustifyRight( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnJustifyLeft( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnCommentblock( wxCommandEvent& event )
{
    event.Skip();

}


void FB_Frame::OnUncommentblock( wxCommandEvent& event )
{
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


void FB_Frame::OnOutput( wxCommandEvent& event )
{
    if ( HSplitter->IsSplit() ) { 
        Console_area->SetSize( HSplitter->GetSashPosition() );
        HSplitter->Unsplit( Console_area );
        ViewConsole->Check( false );
    }
    else { 
        HSplitter->SplitHorizontally( VSplitter, Console_area, Console_area->GetSize() );
        ViewConsole->Check( true );
    }
}


void FB_Frame::OnProject( wxCommandEvent& event )
{
    if ( VSplitter->IsSplit() ) {
        Browser_area->SetSize( VSplitter->GetSashPosition() );
        VSplitter->Unsplit( Browser_area );
    }
    else {
        VSplitter->SplitVertically( Browser_area, Code_area, Browser_area->GetSize() );
    }
}


void FB_Frame::OnOpenconsole( wxCommandEvent& event )
{
    event.Skip();
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
