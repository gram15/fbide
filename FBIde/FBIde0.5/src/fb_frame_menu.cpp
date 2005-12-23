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


#include "inc/wxall.h"
#include "wx/docview.h"
#include "inc/fb_config.h"
#include "inc/fb_frame.h"

void FB_Frame::CreateMenus()
{    
    m_MenuBar = new wxMenuBar;
    
    // File menu
    m_FileMenu = new wxMenu;
    m_FileMenu_New = new wxMenu;
    m_FileMenu_ReOpen = new wxMenu;
    m_Config->m_FileHistory->UseMenu( m_FileMenu_ReOpen );    
    {
        wxMenuItem* menuItem = new wxMenuItem(m_FileMenu_New, wxID_NEW, _("Source File\tCtrl+N"), _T("Create new document"));
        wxBitmap bitmap(wxBITMAP(bmp_newsrc));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        m_FileMenu_New->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(m_FileMenu_New, fbideID_NewProject, _("Project..."), _T("Create new project"));
        wxBitmap bitmap(wxBITMAP(bmp_newproj));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        m_FileMenu_New->Append(menuItem);
    }
    m_FileMenu_New->AppendSeparator();
    {
        wxMenuItem* menuItem = new wxMenuItem(m_FileMenu_New, fbideID_NewTemplate, _("Template..."), _T("Create new template"));
        wxBitmap bitmap(wxBITMAP(bmp_newtemp));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        m_FileMenu_New->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(m_FileMenu, ID_MENU, _("New"));
        menuItem->SetSubMenu( m_FileMenu_New );
        menuItem->SetMarginWidth( 16 );
        m_FileMenu->Append(menuItem);
    }
    m_FileMenu->AppendSeparator();
    {
        wxMenuItem* menuItem = new wxMenuItem(m_FileMenu, wxID_OPEN, _("Open...\tCtrl+O"), _T("Open saved documents or projects"));
        wxBitmap bitmap(wxBITMAP(bmp_opnproj));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        m_FileMenu->Append(menuItem);
    }
    
    {
        wxMenuItem* menuItem = new wxMenuItem(m_FileMenu, fbideID_ReOpen, _("Reopen"), _("Reopen previously opened documents"));
        menuItem->SetSubMenu( m_FileMenu_ReOpen );
        menuItem->SetMarginWidth( 16 );
        m_FileMenu->Append(menuItem);
    }
    m_FileMenu->AppendSeparator();
    {
        wxMenuItem* menuItem = new wxMenuItem(m_FileMenu, wxID_SAVE, _("Save\tCtrl+S"), _T("Save current document"));
        wxBitmap bitmap(wxBITMAP(bmp_save));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        m_FileMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(m_FileMenu, wxID_SAVEAS, _("Save as ..."), _T("Save current document under new name"));
        wxBitmap bitmap(wxBITMAP(bmp_saveas));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        m_FileMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(m_FileMenu, fbideID_SaveProjectAS, _("Save Project as ..."), _T("Save current project under new name"));
        wxBitmap bitmap(wxBITMAP(bmp_saveas));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        m_FileMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(m_FileMenu, wxID_SAVE_ALL, _("Save All"), _T("Save all open altered documents"));
        wxBitmap bitmap(wxBITMAP(bmp_saveall));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        m_FileMenu->Append(menuItem);
    }
    m_FileMenu->AppendSeparator();
    {
        wxMenuItem* menuItem = new wxMenuItem(m_FileMenu, fbideID_SessionLoad, _("Load Session"), _T("Load previously saved sesson"));
        menuItem->SetMarginWidth( 16 );
        m_FileMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(m_FileMenu, fbideID_SessionSave, _("Save Session"), _T("Save currently opened documents as session"));
        menuItem->SetMarginWidth( 16 );
        m_FileMenu->Append(menuItem);
    }
    m_FileMenu->AppendSeparator();
    {
        wxMenuItem* menuItem = new wxMenuItem(m_FileMenu, wxID_CLOSE, _("Close\tCtrl+F4"), _T("Close active document"));
        wxBitmap bitmap(wxBITMAP(bmp_closefl));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        m_FileMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(m_FileMenu, wxID_CLOSE_ALL, _("Cloase All"), _T("Close all opened documents"));
        menuItem->SetMarginWidth( 16 );
        m_FileMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(m_FileMenu, fbideID_CloseProject, _("Close Project"), _T("Close opened project"));
        menuItem->SetMarginWidth( 16 );
        m_FileMenu->Append(menuItem);
    }
    m_FileMenu->AppendSeparator();
    {
        wxMenuItem* menuItem = new wxMenuItem(m_FileMenu, fbideID_NewInstance, _("New window"), _T("Open new instance of FBIde"));
        menuItem->SetMarginWidth( 16 );
        m_FileMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(m_FileMenu, wxID_EXIT, _("Exit\tCtrl+Q"), _T("Exit from FBIde"));
        wxBitmap bitmap(wxBITMAP(bmp_close));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        m_FileMenu->Append(menuItem);
    }
    m_MenuBar->Append(m_FileMenu, _("File"));
    

    // Edit menu
    m_EditMenu = new wxMenu;
    {
        wxMenuItem* menuItem = new wxMenuItem(m_EditMenu, wxID_UNDO, _("Undo\tCtrl+Z"), _T(""));
        wxBitmap bitmap(wxBITMAP(bmp_undo));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        m_EditMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(m_EditMenu, wxID_REDO, _("Redo\tCtrl+Shift+Z"), _T(""));
        wxBitmap bitmap(wxBITMAP(bmp_redo));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        m_EditMenu->Append(menuItem);
    }
    m_EditMenu->AppendSeparator();
    {
        wxMenuItem* menuItem = new wxMenuItem(m_EditMenu, wxID_COPY, _("Copy\tCtrl+C"), _T(""));
        wxBitmap bitmap(wxBITMAP(bmp_copy));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        m_EditMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(m_EditMenu, wxID_CUT, _("Cut\tCtrl+X"), _T(""));
        wxBitmap bitmap(wxBITMAP(bmp_cut));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        m_EditMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(m_EditMenu, wxID_PASTE, _("Paste\tCtrl+V"), _T(""));
        wxBitmap bitmap(wxBITMAP(bmp_paste));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        m_EditMenu->Append(menuItem);
    }
    m_EditMenu->AppendSeparator();
    {
        wxMenuItem* menuItem = new wxMenuItem(m_EditMenu, wxID_SELECTALL, _("Select all\tCtrl+A"), _T(""));
        menuItem->SetMarginWidth( 16 );
        m_EditMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(m_EditMenu, fbideID_SelectLine, _("Select line"), _T(""));
        menuItem->SetMarginWidth( 16 );
        m_EditMenu->Append(menuItem);
    }
    m_EditMenu->AppendSeparator();
    {
        wxMenuItem* menuItem = new wxMenuItem(m_EditMenu, wxID_JUSTIFY_RIGHT, _("Indent increase\tTab"), _T(""));
        menuItem->SetMarginWidth( 16 );
        m_EditMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(m_EditMenu, wxID_JUSTIFY_LEFT, _("Indent decrease\tShift+Tab"), _T(""));
        menuItem->SetMarginWidth( 16 );
        m_EditMenu->Append(menuItem);
    }
    m_EditMenu->AppendSeparator();
    {
        wxMenuItem* menuItem = new wxMenuItem(m_EditMenu, fbideID_CommentBlock, _("Comment block\tCtrl+M"), _T(""));
        menuItem->SetMarginWidth( 16 );
        m_EditMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(m_EditMenu, fbideID_UncommentBlock, _("UnComment Block\tCtrl+Shift+M"), _T(""));
        menuItem->SetMarginWidth( 16 );
        m_EditMenu->Append(menuItem);
    }
    m_MenuBar->Append(m_EditMenu, _("Edit"));
    

    // Search menu
    m_SearchMenu = new wxMenu;
    {
        wxMenuItem* menuItem = new wxMenuItem(m_SearchMenu, wxID_FIND, _("Find...\tCtrl+F"), _T(""));
        wxBitmap bitmap(wxBITMAP(bmp_search));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        m_SearchMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(m_SearchMenu, fbideID_FindNext, _("Search again\tF3"), _T(""));
        wxBitmap bitmap(wxBITMAP(bmp_srcagain));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        m_SearchMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(m_SearchMenu, wxID_REPLACE, _("Replace"), _T(""));
        wxBitmap bitmap(wxBITMAP(bmp_srchrep));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        m_SearchMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(m_SearchMenu, fbideID_Goto, _("Goto to line\tCtrl+G"), _T(""));
        wxBitmap bitmap(wxBITMAP(bmp_goto));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        m_SearchMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(m_SearchMenu, fbideID_IncrSearch, _("Incremental Search\tCtrl+I"), _T(""));
        menuItem->SetMarginWidth( 16 );
        m_SearchMenu->Append(menuItem);
    }
    m_MenuBar->Append(m_SearchMenu, _("Search"));


    //View menu
    m_ViewMenu = new wxMenu;
    {
        m_ViewConsole = new wxMenuItem(m_ViewMenu, fbideID_OutPut, _("Console Area\tF4"), _T(""), wxITEM_CHECK);
        m_ViewConsole->SetMarginWidth( 16 );
        m_ViewMenu->Append(m_ViewConsole);
    }
    {
        m_ViewProject = new wxMenuItem(m_ViewMenu, fbideID_Project, _("Project browser\tF2"), _T(""), wxITEM_CHECK);
        m_ViewProject->SetMarginWidth( 16 );
        m_ViewMenu->Append(m_ViewProject);
    }
    {
        m_ViewToolBar = new wxMenuItem(m_ViewMenu, fbideID_ToolBar, _("View Toolbar"), _T(""), wxITEM_CHECK);
        m_ViewToolBar->SetMarginWidth( 16 );
        m_ViewMenu->Append(m_ViewToolBar);
    }
    {
        m_ViewStatusBar = new wxMenuItem(m_ViewMenu, fbideID_StatusBar, _("View Statusbar"), _T(""), wxITEM_CHECK);
        m_ViewStatusBar->SetMarginWidth( 16 );
        m_ViewMenu->Append(m_ViewStatusBar);
    }
    {
        wxMenuItem * menuitem = new wxMenuItem( m_ViewMenu, fbideID_FullScreen, _("View Fullscreen\tAlt+Enter"), _T(""), wxITEM_CHECK);
        menuitem->SetMarginWidth( 16 );
        m_ViewMenu->Append( menuitem );
    }
    m_MenuBar->Append(m_ViewMenu, _("View"));
    

    // Project menu
    m_ProjectMenu = new wxMenu;
    {
        wxMenuItem* menuItem = new wxMenuItem(m_ProjectMenu, fbideID_NewProjectFile, _("New file"), _T(""));
        wxBitmap bitmap(wxBITMAP(bmp_newsrc));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        m_ProjectMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(m_ProjectMenu, fbideID_ProjectAdd, _("Add to Project"), _T(""));
        wxBitmap bitmap(wxBITMAP(bmp_addsrc));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        m_ProjectMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(m_ProjectMenu, fbideID_ProjectRemove, _("Remove from Project"), _T(""));
        wxBitmap bitmap(wxBITMAP(bmp_remsrc));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        m_ProjectMenu->Append(menuItem);
    }
    m_ProjectMenu->AppendSeparator();
    {
        wxMenuItem* menuItem = new wxMenuItem(m_ProjectMenu, fbideID_ProjectOptions, _("Project Options\tAlt+P"), _T(""));
        wxBitmap bitmap(wxBITMAP(bmp_projopt));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        m_ProjectMenu->Append(menuItem);
    }
    m_MenuBar->Append(m_ProjectMenu, _("Project"));
    

    // Run Menu
    m_RunMenu = new wxMenu;
    {
        wxMenuItem* menuItem = new wxMenuItem(m_RunMenu, fbideID_Compile, _("Compile\tCtrl+F9"), _T(""));
        wxBitmap bitmap(wxBITMAP(bmp_compile));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        m_RunMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(m_RunMenu, fbideID_CompileAndRun, _("Compile and Run\tF9"), _T(""));
        wxBitmap bitmap(wxBITMAP(bmp_comprun));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        m_RunMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(m_RunMenu, fbideID_RebuildAll, _("Rebuild All"), _T(""));
        wxBitmap bitmap(wxBITMAP(bmp_rebuild));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        m_RunMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(m_RunMenu, fbideID_QuickRun, _("Quick Run\tF5"), _T(""));
        wxBitmap bitmap(wxBITMAP(bmp_next));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        m_RunMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(m_RunMenu, fbideID_Run, _("Run\tShift+F9"), _T(""));
        wxBitmap bitmap(wxBITMAP(bmp_run));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        m_RunMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(m_RunMenu, fbideID_Parameters, _("Parameters"), _T(""));
        menuItem->SetMarginWidth( 16 );
        m_RunMenu->Append(menuItem);
    }
    m_RunMenu->AppendSeparator();
    {
        wxMenuItem* menuItem = new wxMenuItem(m_RunMenu, fbideID_Debug, _("Debug"), _T(""));
        wxBitmap bitmap(wxBITMAP(bmp_debug));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        m_RunMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(m_RunMenu, fbideID_OpenConsole, _("Command Prompt"), _T(""));
        wxBitmap bitmap(wxBITMAP(bmp_dos));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        m_RunMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(m_RunMenu, fbideID_ProfileAnalysis, _("Profile Analysis"), _T(""));
        menuItem->SetMarginWidth( 16 );
        m_RunMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(m_RunMenu, fbideID_ShowExitCode, _("Show exit code"), _T(""), wxITEM_CHECK);
        menuItem->SetMarginWidth( 16 );
        m_RunMenu->Append(menuItem);
    }
    m_MenuBar->Append(m_RunMenu, _("Run"));
    

    // Tools menu
    m_ToolsMenu = new wxMenu;
    {
        wxMenuItem* menuItem = new wxMenuItem(m_ToolsMenu, wxID_PROPERTIES, _("Settings"), _T(""));
        wxBitmap bitmap(wxBITMAP(bmp_envopt));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        m_ToolsMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(m_ToolsMenu, fbideID_SrcFormatter, _("Formatter"), _T(""));
        wxBitmap bitmap(wxBITMAP(bmp_resrc));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        m_ToolsMenu->Append(menuItem);
    }
    m_MenuBar->Append(m_ToolsMenu, _("Tools"));
    

    // Help menu
    m_HelpMenu = new wxMenu;
    {
        wxMenuItem* menuItem = new wxMenuItem(m_HelpMenu, wxID_HELP, _("Help on FBIde\tF1"), _T(""));
        wxBitmap bitmap(wxBITMAP(bmp_help));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        m_HelpMenu->Append(menuItem);
    }
    {
        wxMenuItem* menuItem = new wxMenuItem(m_HelpMenu, wxID_ABOUT, _("About"), _T(""));
        wxBitmap bitmap(wxBITMAP(bmp_about));
        bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) );
        menuItem->SetBitmap(bitmap);
        m_HelpMenu->Append(menuItem);
    }
    m_MenuBar->Append(m_HelpMenu, _("Help"));
    
    this->SetMenuBar( m_MenuBar );
}
