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

#include "inc/fb_frame.h"

/*!
 * FB_Frame type definition
 */

IMPLEMENT_CLASS( FB_Frame, wxFrame )

BEGIN_EVENT_TABLE( FB_Frame, wxFrame )
    // File menu
    EVT_MENU( wxID_NEW,                 FB_Frame::OnNewClick )
    EVT_MENU( fbideID_NewProject,       FB_Frame::OnFbideidNewprojectClick )
    EVT_MENU( fbideID_NewTemplate,      FB_Frame::OnFbideidNewtemplateClick )
    EVT_MENU( wxID_OPEN,                FB_Frame::OnOpenClick )
    EVT_MENU( wxID_SAVE,                FB_Frame::OnSaveClick )
    EVT_MENU( wxID_SAVEAS,              FB_Frame::OnSaveasClick )
    EVT_MENU( fbideID_SaveProjectAS,    FB_Frame::OnFbideidSaveprojectasClick )
    EVT_MENU( wxID_SAVE_ALL,            FB_Frame::OnSaveAllClick )
    EVT_MENU( fbideID_SessionLoad,      FB_Frame::OnFbideidSessionloadClick )
    EVT_MENU( fbideID_SessionSave,      FB_Frame::OnFbideidSessionsaveClick )
    EVT_MENU( wxID_CLOSE,               FB_Frame::OnCloseClick )
    EVT_MENU( wxID_CLOSE_ALL,           FB_Frame::OnCloseAllClick )
    EVT_MENU( fbideID_CloseProject,     FB_Frame::OnFbideidCloseprojectClick )
    EVT_MENU( fbideID_NewInstance,      FB_Frame::OnFbideidNewinstanceClick )
    EVT_MENU( wxID_EXIT,                FB_Frame::OnExitClick )

    // Edit menu
    EVT_MENU( wxID_UNDO,                FB_Frame::OnUndoClick )
    EVT_MENU( wxID_REDO,                FB_Frame::OnRedoClick )
    EVT_MENU( wxID_COPY,                FB_Frame::OnCopyClick )
    EVT_MENU( wxID_CUT,                 FB_Frame::OnCutClick )
    EVT_MENU( wxID_PASTE,               FB_Frame::OnPasteClick )
    EVT_MENU( wxID_SELECTALL,           FB_Frame::OnSelectallClick )
    EVT_MENU( fbideID_SelectLine,       FB_Frame::OnFbideidSelectlineClick )
    EVT_MENU( wxID_JUSTIFY_RIGHT,       FB_Frame::OnJustifyRightClick )
    EVT_MENU( wxID_JUSTIFY_LEFT,        FB_Frame::OnJustifyLeftClick )
    EVT_MENU( fbideID_CommentBlock,     FB_Frame::OnFbideidCommentblockClick )
    EVT_MENU( fbideID_UncommentBlock,   FB_Frame::OnFbideidUncommentblockClick )
    
    // Search menu
    EVT_MENU( wxID_FIND,                FB_Frame::OnFindClick )
    EVT_MENU( fbideID_FindNext,         FB_Frame::OnFbideidFindnextClick )
    EVT_MENU( wxID_REPLACE,             FB_Frame::OnReplaceClick )
    EVT_MENU( fbideID_Goto,             FB_Frame::OnFbideidGotoClick )
    EVT_MENU( fbideID_IncrSearch,       FB_Frame::OnFbideidIncrsearchClick )
    
    // View menu
    EVT_MENU( fbideID_OutPut,           FB_Frame::OnFbideidOutputClick )
    
    // Project menu
    EVT_MENU( fbideID_NewProjectFile,   FB_Frame::OnFbideidNewprojectfileClick )
    EVT_MENU( fbideID_ProjectAdd,       FB_Frame::OnFbideidProjectaddClick )
    EVT_MENU( fbideID_ProjectRemove,    FB_Frame::OnFbideidProjectremoveClick )
    EVT_MENU( fbideID_ProjectOptions,   FB_Frame::OnFbideidProjectoptionsClick )
    
    // Run menu
    EVT_MENU( fbideID_Compile,          FB_Frame::OnFbideidCompileClick )
    EVT_MENU( fbideID_CompileAndRun,    FB_Frame::OnFbideidCompileandrunClick )
    EVT_MENU( fbideID_RebuildAll,       FB_Frame::OnFbideidRebuildallClick )
    EVT_MENU( fbideID_QuickRun,         FB_Frame::OnFbideidQuickrunClick )
    EVT_MENU( fbideID_Run,              FB_Frame::OnFbideidRunClick )
    EVT_MENU( fbideID_Parameters,       FB_Frame::OnFbideidParametersClick )
    EVT_MENU( fbideID_Debug,            FB_Frame::OnFbideidDebugClick )
    EVT_MENU( fbideID_OpenConsole,      FB_Frame::OnFbideidOpenconsoleClick )
    EVT_MENU( fbideID_ProfileAnalysis,  FB_Frame::OnFbideidProfileanalysisClick )
    EVT_MENU( fbideID_ShowExitCode,     FB_Frame::OnFbideidShowexitcodeClick )
    
    // Tools menu
    EVT_MENU( wxID_PROPERTIES,          FB_Frame::OnPropertiesClick )
    EVT_MENU( fbideID_SrcFormatter,     FB_Frame::OnFbideidSrcformatterClick )
    
    // Help menu
    EVT_MENU( wxID_HELP,                FB_Frame::OnHelpClick )
    EVT_MENU( wxID_ABOUT,               FB_Frame::OnAboutClick )

END_EVENT_TABLE()


FB_Frame::FB_Frame( ) {   }

FB_Frame::FB_Frame( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Create( parent, id, caption, pos, size, style );
}


bool FB_Frame::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{

    wxFrame::Create( parent, id, caption, pos, size, style );
    CreateControls();
    Centre();
    return TRUE;

}



void FB_Frame::CreateControls()
{    
    wxMenuBar* menuBar = new wxMenuBar;
    
    // File menu
    wxMenu* FileMenu = new wxMenu;
    wxMenu* NewMenu = new wxMenu;
    {
        wxMenuItem* menuItem = new wxMenuItem(NewMenu, wxID_NEW, _("Source File\tCtrl+N"), _T(""), wxITEM_NORMAL);
        wxBitmap bitmap(wxBITMAP(bmp_newsrc));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        NewMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(NewMenu, fbideID_NewProject, _("Project..."), _T(""), wxITEM_NORMAL);
        wxBitmap bitmap(wxBITMAP(bmp_newproj));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        NewMenu->Append(menuItem);
    }
    NewMenu->AppendSeparator();
    {
        wxMenuItem* menuItem = new wxMenuItem(NewMenu, fbideID_NewTemplate, _("Template..."), _T(""), wxITEM_NORMAL);
        wxBitmap bitmap(wxBITMAP(bmp_newtemp));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        NewMenu->Append(menuItem);
    }
    FileMenu->Append(ID_MENU, _("New"), NewMenu);

    FileMenu->AppendSeparator();
    {
        wxMenuItem* menuItem = new wxMenuItem(FileMenu, wxID_OPEN, _("Open...\tCtrl+O"), _T(""), wxITEM_NORMAL);
        wxBitmap bitmap(wxBITMAP(bmp_opnproj));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        FileMenu->Append(menuItem);
    }
    FileMenu->AppendSeparator();
    {
        wxMenuItem* menuItem = new wxMenuItem(FileMenu, wxID_SAVE, _("Save\tCtrl+S"), _T(""), wxITEM_NORMAL);
        wxBitmap bitmap(wxBITMAP(bmp_save));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        FileMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(FileMenu, wxID_SAVEAS, _("Save as ..."), _T(""), wxITEM_NORMAL);
        wxBitmap bitmap(wxBITMAP(bmp_saveas));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        FileMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(FileMenu, fbideID_SaveProjectAS, _("Save Project as ..."), _T(""), wxITEM_NORMAL);
        wxBitmap bitmap(wxBITMAP(bmp_saveas));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        FileMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(FileMenu, wxID_SAVE_ALL, _("Save All"), _T(""), wxITEM_NORMAL);
        wxBitmap bitmap(wxBITMAP(bmp_saveall));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        FileMenu->Append(menuItem);
    }
    FileMenu->AppendSeparator();
    {
        wxMenuItem* menuItem = new wxMenuItem(FileMenu, fbideID_SessionLoad, _("Load Session"), _T(""), wxITEM_NORMAL);
        wxBitmap bitmap(wxBITMAP(bmp_empty));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        FileMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(FileMenu, fbideID_SessionSave, _("Save Session"), _T(""), wxITEM_NORMAL);
        wxBitmap bitmap(wxBITMAP(bmp_empty));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        FileMenu->Append(menuItem);
    }
    FileMenu->AppendSeparator();
    {
        wxMenuItem* menuItem = new wxMenuItem(FileMenu, wxID_CLOSE, _("Close\tCtrl+F4"), _T(""), wxITEM_NORMAL);
        wxBitmap bitmap(wxBITMAP(bmp_closefl));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        FileMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(FileMenu, wxID_CLOSE_ALL, _("Cloase All"), _T(""), wxITEM_NORMAL);
        wxBitmap bitmap(wxBITMAP(bmp_empty));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        FileMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(FileMenu, fbideID_CloseProject, _("Close Project"), _T(""), wxITEM_NORMAL);
        wxBitmap bitmap(wxBITMAP(bmp_empty));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        FileMenu->Append(menuItem);
    }
    FileMenu->AppendSeparator();
    {
        wxMenuItem* menuItem = new wxMenuItem(FileMenu, fbideID_NewInstance, _("New window"), _T(""), wxITEM_NORMAL);
        wxBitmap bitmap(wxBITMAP(bmp_empty));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        FileMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(FileMenu, wxID_EXIT, _("Exit\\Ctrl+Q"), _T(""), wxITEM_NORMAL);
        wxBitmap bitmap(wxBITMAP(bmp_close));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        FileMenu->Append(menuItem);
    }
    menuBar->Append(FileMenu, _("File"));
    
    // Edit menu
    wxMenu* EditMenu = new wxMenu;
    {
        wxMenuItem* menuItem = new wxMenuItem(EditMenu, wxID_UNDO, _("Undo\tCtrl+Z"), _T(""), wxITEM_NORMAL);
        wxBitmap bitmap(wxBITMAP(bmp_undo));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        EditMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(EditMenu, wxID_REDO, _("Redo\tCtrl+Shift+Z"), _T(""), wxITEM_NORMAL);
        wxBitmap bitmap(wxBITMAP(bmp_redo));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        EditMenu->Append(menuItem);
    }
    EditMenu->AppendSeparator();
    {
        wxMenuItem* menuItem = new wxMenuItem(EditMenu, wxID_COPY, _("Copy\tCtrl+C"), _T(""), wxITEM_NORMAL);
        wxBitmap bitmap(wxBITMAP(bmp_copy));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        EditMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(EditMenu, wxID_CUT, _("Cut\tCtrl+X"), _T(""), wxITEM_NORMAL);
        wxBitmap bitmap(wxBITMAP(bmp_cut));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        EditMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(EditMenu, wxID_PASTE, _("Paste\tCtrl+V"), _T(""), wxITEM_NORMAL);
        wxBitmap bitmap(wxBITMAP(bmp_paste));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        EditMenu->Append(menuItem);
    }
    EditMenu->AppendSeparator();
    {
        wxMenuItem* menuItem = new wxMenuItem(EditMenu, wxID_SELECTALL, _("Select all\tCtrl+A"), _T(""), wxITEM_NORMAL);
        wxBitmap bitmap(wxBITMAP(bmp_empty));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        EditMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(EditMenu, fbideID_SelectLine, _("Select line"), _T(""), wxITEM_NORMAL);
        wxBitmap bitmap(wxBITMAP(bmp_empty));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        EditMenu->Append(menuItem);
    }
    EditMenu->AppendSeparator();
    {
        wxMenuItem* menuItem = new wxMenuItem(EditMenu, wxID_JUSTIFY_RIGHT, _("Indent increase\tTab"), _T(""), wxITEM_NORMAL);
        wxBitmap bitmap(wxBITMAP(bmp_empty));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        EditMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(EditMenu, wxID_JUSTIFY_LEFT, _("Indent decrease\tShift+Tab"), _T(""), wxITEM_NORMAL);
        wxBitmap bitmap(wxBITMAP(bmp_empty));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        EditMenu->Append(menuItem);
    }
    EditMenu->AppendSeparator();
    {
        wxMenuItem* menuItem = new wxMenuItem(EditMenu, fbideID_CommentBlock, _("Comment block\tCtrl+M"), _T(""), wxITEM_NORMAL);
        wxBitmap bitmap(wxBITMAP(bmp_empty));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        EditMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(EditMenu, fbideID_UncommentBlock, _("UnComment Block\tCtrl+Shift+M"), _T(""), wxITEM_NORMAL);
        wxBitmap bitmap(wxBITMAP(bmp_empty));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        EditMenu->Append(menuItem);
    }
    menuBar->Append(EditMenu, _("Edit"));
    
    // Search menu
    wxMenu* SearchMenu = new wxMenu;
    {
        wxMenuItem* menuItem = new wxMenuItem(SearchMenu, wxID_FIND, _("Find...\tCtrl+F"), _T(""), wxITEM_NORMAL);
        wxBitmap bitmap(wxBITMAP(bmp_search));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        SearchMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(SearchMenu, fbideID_FindNext, _("Search again"), _T(""), wxITEM_NORMAL);
        wxBitmap bitmap(wxBITMAP(bmp_srcagain));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        SearchMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(SearchMenu, wxID_REPLACE, _("Replace"), _T(""), wxITEM_NORMAL);
        wxBitmap bitmap(wxBITMAP(bmp_srchrep));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        SearchMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(SearchMenu, fbideID_Goto, _("Goto to line\tCtrl+G"), _T(""), wxITEM_NORMAL);
        wxBitmap bitmap(wxBITMAP(bmp_goto));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        SearchMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(SearchMenu, fbideID_IncrSearch, _("Incremental Search\tCtrl+I"), _T(""), wxITEM_NORMAL);
        wxBitmap bitmap(wxBITMAP(bmp_empty));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        SearchMenu->Append(menuItem);
    }
    menuBar->Append(SearchMenu, _("Search"));

    //View menu
    wxMenu* ViewMenu = new wxMenu;
    ViewMenu->Append(fbideID_OutPut, _("Console Area\tF4"), _T(""), wxITEM_CHECK);
    menuBar->Append(ViewMenu, _("View"));
    
    // Project menu
    wxMenu* ProjectMenu = new wxMenu;
    {
        wxMenuItem* menuItem = new wxMenuItem(ProjectMenu, fbideID_NewProjectFile, _("New file"), _T(""), wxITEM_NORMAL);
        wxBitmap bitmap(wxBITMAP(bmp_newsrc));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        ProjectMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(ProjectMenu, fbideID_ProjectAdd, _("Add to Project"), _T(""), wxITEM_NORMAL);
        wxBitmap bitmap(wxBITMAP(bmp_addsrc));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        ProjectMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(ProjectMenu, fbideID_ProjectRemove, _("Remove from Project"), _T(""), wxITEM_NORMAL);
        wxBitmap bitmap(wxBITMAP(bmp_remsrc));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        ProjectMenu->Append(menuItem);
    }
    ProjectMenu->AppendSeparator();
    {
        wxMenuItem* menuItem = new wxMenuItem(ProjectMenu, fbideID_ProjectOptions, _("Project Options\tAlt+P"), _T(""), wxITEM_NORMAL);
        wxBitmap bitmap(wxBITMAP(bmp_projopt));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        ProjectMenu->Append(menuItem);
    }
    menuBar->Append(ProjectMenu, _("Project"));
    
    // Run Menu
    wxMenu* RunMenu = new wxMenu;
    {
        wxMenuItem* menuItem = new wxMenuItem(RunMenu, fbideID_Compile, _("Compile\tCtrl+F9"), _T(""), wxITEM_NORMAL);
        wxBitmap bitmap(wxBITMAP(bmp_compile));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        RunMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(RunMenu, fbideID_CompileAndRun, _("Compile and Run\tF9"), _T(""), wxITEM_NORMAL);
        wxBitmap bitmap(wxBITMAP(bmp_comprun));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        RunMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(RunMenu, fbideID_RebuildAll, _("Rebuild All"), _T(""), wxITEM_NORMAL);
        wxBitmap bitmap(wxBITMAP(bmp_rebuild));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        RunMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(RunMenu, fbideID_QuickRun, _("Quick Run\tF5"), _T(""), wxITEM_NORMAL);
        wxBitmap bitmap(wxBITMAP(bmp_next));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        RunMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(RunMenu, fbideID_Run, _("Run\tShift+F9"), _T(""), wxITEM_NORMAL);
        wxBitmap bitmap(wxBITMAP(bmp_run));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        RunMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(RunMenu, fbideID_Parameters, _("Parameters"), _T(""), wxITEM_NORMAL);
        wxBitmap bitmap(wxBITMAP(bmp_empty));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        RunMenu->Append(menuItem);
    }
    RunMenu->AppendSeparator();
    {
        wxMenuItem* menuItem = new wxMenuItem(RunMenu, fbideID_Debug, _("Debug"), _T(""), wxITEM_NORMAL);
        wxBitmap bitmap(wxBITMAP(bmp_debug));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        RunMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(RunMenu, fbideID_OpenConsole, _("Command Prompt"), _T(""), wxITEM_NORMAL);
        wxBitmap bitmap(wxBITMAP(bmp_dos));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        RunMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(RunMenu, fbideID_ProfileAnalysis, _("Profile Analysis"), _T(""), wxITEM_NORMAL);
        wxBitmap bitmap(wxBITMAP(bmp_empty));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        RunMenu->Append(menuItem);
    }
    RunMenu->Append(fbideID_ShowExitCode, _("Show exit code"), _T(""), wxITEM_CHECK);
    menuBar->Append(RunMenu, _("Run"));
    
    // Tools menu
    wxMenu* ToolsMenu = new wxMenu;
    {
        wxMenuItem* menuItem = new wxMenuItem(ToolsMenu, wxID_PROPERTIES, _("Settings"), _T(""), wxITEM_NORMAL);
        wxBitmap bitmap(wxBITMAP(bmp_envopt));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        ToolsMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(ToolsMenu, fbideID_SrcFormatter, _("Formatter"), _T(""), wxITEM_NORMAL);
        wxBitmap bitmap(wxBITMAP(bmp_resrc));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        ToolsMenu->Append(menuItem);
    }
    menuBar->Append(ToolsMenu, _("Tools"));
    
    // Help menu
    wxMenu* HelpMenu = new wxMenu;
    {
        wxMenuItem* menuItem = new wxMenuItem(HelpMenu, wxID_HELP, _("Help on FBIde\tF1"), _T(""), wxITEM_NORMAL);
        wxBitmap bitmap(wxBITMAP(bmp_help));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        HelpMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(HelpMenu, wxID_ABOUT, _("About"), _T(""), wxITEM_NORMAL);
        wxBitmap bitmap(wxBITMAP(bmp_about));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        HelpMenu->Append(menuItem);
    }
    menuBar->Append(HelpMenu, _("Help"));
    this->SetMenuBar(menuBar);


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




void FB_Frame::OnSaveClick( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnNewClick( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnFbideidNewprojectClick( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnFbideidNewtemplateClick( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnOpenClick( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnSaveasClick( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnFbideidSaveprojectasClick( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnSaveAllClick( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnFbideidSessionloadClick( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnFbideidSessionsaveClick( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnCloseClick( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnCloseAllClick( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnFbideidCloseprojectClick( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnFbideidNewinstanceClick( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnExitClick( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnUndoClick( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnRedoClick( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnCopyClick( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnCutClick( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnPasteClick( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnSelectallClick( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnFbideidSelectlineClick( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnJustifyRightClick( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnJustifyLeftClick( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnFbideidCommentblockClick( wxCommandEvent& event )
{
    event.Skip();

}


void FB_Frame::OnFbideidUncommentblockClick( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnFindClick( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnFbideidFindnextClick( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnReplaceClick( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnFbideidGotoClick( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnFbideidIncrsearchClick( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnFbideidNewprojectfileClick( wxCommandEvent& event )
{
    event.Skip();
}

void FB_Frame::OnFbideidProjectaddClick( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnFbideidProjectremoveClick( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnFbideidProjectoptionsClick( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnFbideidCompileClick( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnFbideidCompileandrunClick( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnFbideidRebuildallClick( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnFbideidQuickrunClick( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnFbideidRunClick( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnFbideidParametersClick( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnFbideidDebugClick( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnFbideidProfileanalysisClick( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnFbideidShowexitcodeClick( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnFbideidOutputClick( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnFbideidOpenconsoleClick( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnPropertiesClick( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnFbideidSrcformatterClick( wxCommandEvent& event )
{
    event.Skip();
}



void FB_Frame::OnHelpClick( wxCommandEvent& event )
{
    event.Skip();
}


void FB_Frame::OnAboutClick( wxCommandEvent& event )
{
    event.Skip();
}
