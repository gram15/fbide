/////////////////////////////////////////////////////////////////////////////
// Name:        fb_frame3.cpp
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
    EditMenu = new wxMenu;
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
    {
        ViewToolBar = new wxMenuItem(ViewMenu, fbideID_ToolBar, _("View Toolbar"), _T(""), wxITEM_CHECK);
        ViewToolBar->SetMarginWidth( 16 );
        ViewMenu->Append(ViewToolBar);
    }
    {
        ViewStatusBar = new wxMenuItem(ViewMenu, fbideID_StatusBar, _("View Statusbar"), _T(""), wxITEM_CHECK);
        ViewStatusBar->SetMarginWidth( 16 );
        ViewMenu->Append(ViewStatusBar);
    }
    {
        wxMenuItem * menuitem = new wxMenuItem( ViewMenu, fbideID_FullScreen, _("View Fullscreen\tAlt+Enter"), _T(""), wxITEM_CHECK);
        menuitem->SetMarginWidth( 16 );
        ViewMenu->Append( menuitem );
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
