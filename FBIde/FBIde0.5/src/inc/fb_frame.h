/////////////////////////////////////////////////////////////////////////////
// Name:        fb_frame.h
// Purpose:     
// Author:      VonGodric
// Modified by: 
// Created:     08/03/05 14:23:04
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _FB_FRAME_H_
#define _FB_FRAME_H_

#include "wx/frame.h"
#include "wx/toolbar.h"
#include "wx/splitter.h"


////@begin control identifiers
#define ID_FRAME 10000
#define SYMBOL_FB_FRAME_STYLE       wxDEFAULT_FRAME_STYLE
#define SYMBOL_FB_FRAME_TITLE       _("FBIde")
#define SYMBOL_FB_FRAME_IDNAME      ID_FRAME
#define SYMBOL_FB_FRAME_SIZE        wxSize(500, 350)
#define SYMBOL_FB_FRAME_POSITION    wxDefaultPosition
#define ID_MENU 10013

#define wxID_SAVE_ALL   10004
#define ID_TOOLBAR      10005
#define ID_SASHWINDOW   10033

enum fbideID_Enums {
    fbideID_NewProject = 100,
    fbideID_NewTemplate,
    fbideID_SaveProjectAS,
    fbideID_SessionLoad,
    fbideID_SessionSave,
    fbideID_CloseProject,
    fbideID_NewInstance,
    fbideID_SelectLine,
    fbideID_CommentBlock,
    fbideID_UncommentBlock,
    fbideID_FindNext,
    fbideID_Goto,
    fbideID_IncrSearch,
    fbideID_OutPut,
    fbideID_NewProjectFile,
    fbideID_Project,
    fbideID_ProjectAdd,
    fbideID_ProjectRemove,
    fbideID_ProjectOptions,
    fbideID_Compile,
    fbideID_CompileAndRun,
    fbideID_RebuildAll,
    fbideID_QuickRun,
    fbideID_Run,
    fbideID_Parameters,
    fbideID_Debug,
    fbideID_OpenConsole,
    fbideID_ProfileAnalysis,
    fbideID_ShowExitCode,
    fbideID_SrcFormatter
};

/*!
 * Compatibility
 */

#ifndef wxCLOSE_BOX
#define wxCLOSE_BOX 0x1000
#endif
#ifndef wxFIXED_MINSIZE
#define wxFIXED_MINSIZE 0
#endif

/*!
 * FB_Frame class declaration
 */

class FB_Console;

class FB_Frame: public wxFrame
{    
    DECLARE_CLASS( FB_Frame )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    FB_Frame( wxWindow* parent, wxWindowID id = SYMBOL_FB_FRAME_IDNAME, const wxString& caption = SYMBOL_FB_FRAME_TITLE, const wxPoint& pos = SYMBOL_FB_FRAME_POSITION, const wxSize& size = SYMBOL_FB_FRAME_SIZE, long style = SYMBOL_FB_FRAME_STYLE );
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_FB_FRAME_IDNAME, const wxString& caption = SYMBOL_FB_FRAME_TITLE, const wxPoint& pos = SYMBOL_FB_FRAME_POSITION, const wxSize& size = SYMBOL_FB_FRAME_SIZE, long style = SYMBOL_FB_FRAME_STYLE );

    /// Creates the controls and sizers
    void CreateMenus();
    void CreateToolbar();
    void CreatePanels();

    /// Event handlers
    void OnNew              ( wxCommandEvent& event );
    void OnNewproject       ( wxCommandEvent& event );
    void OnNewtemplate      ( wxCommandEvent& event );
    void OnOpen             ( wxCommandEvent& event );
    void OnSave             ( wxCommandEvent& event );
    void OnSaveas           ( wxCommandEvent& event );
    void OnSaveprojectas    ( wxCommandEvent& event );
    void OnSaveAll          ( wxCommandEvent& event );
    void OnSessionload      ( wxCommandEvent& event );
    void OnSessionsave      ( wxCommandEvent& event );
    void OnClose            ( wxCommandEvent& event );
    void OnCloseAll         ( wxCommandEvent& event );
    void OnCloseproject     ( wxCommandEvent& event );
    void OnNewinstance      ( wxCommandEvent& event );
    void OnExit             ( wxCommandEvent& event );
    void OnUndo             ( wxCommandEvent& event );
    void OnRedo             ( wxCommandEvent& event );
    void OnCopy             ( wxCommandEvent& event );
    void OnCut              ( wxCommandEvent& event );
    void OnPaste            ( wxCommandEvent& event );
    void OnSelectall        ( wxCommandEvent& event );
    void OnSelectline       ( wxCommandEvent& event );
    void OnJustifyRight     ( wxCommandEvent& event );
    void OnJustifyLeft      ( wxCommandEvent& event );
    void OnCommentblock     ( wxCommandEvent& event );
    void OnUncommentblock   ( wxCommandEvent& event );
    void OnFind             ( wxCommandEvent& event );
    void OnFindnext         ( wxCommandEvent& event );
    void OnReplace          ( wxCommandEvent& event );
    void OnGoto             ( wxCommandEvent& event );
    void OnIncrsearch       ( wxCommandEvent& event );
    void OnOutput           ( wxCommandEvent& event );
    void OnProject          ( wxCommandEvent& event );
    void OnNewprojectfile   ( wxCommandEvent& event );
    void OnProjectadd       ( wxCommandEvent& event );
    void OnProjectremove    ( wxCommandEvent& event );
    void OnProjectoptions   ( wxCommandEvent& event );
    void OnCompile          ( wxCommandEvent& event );
    void OnCompileandrun    ( wxCommandEvent& event );
    void OnRebuildall       ( wxCommandEvent& event );
    void OnQuickrun         ( wxCommandEvent& event );
    void OnRun              ( wxCommandEvent& event );
    void OnParameters       ( wxCommandEvent& event );
    void OnDebug            ( wxCommandEvent& event );
    void OnOpenconsole      ( wxCommandEvent& event );
    void OnProfileanalysis  ( wxCommandEvent& event );
    void OnShowexitcode     ( wxCommandEvent& event );
    void OnProperties       ( wxCommandEvent& event );
    void OnSrcformatter     ( wxCommandEvent& event );
    void OnHelp             ( wxCommandEvent& event );
    void OnAbout            ( wxCommandEvent& event );

    static bool ShowToolTips();

    /// Data
    wxToolBar* FB_Toolbar;
    wxSplitterWindow* HSplitter;
    wxSplitterWindow* VSplitter;
    FB_Console* Console_area;
    wxMenuItem* ViewProject;
    wxMenuItem* ViewConsole;

};

#endif
    // _FB_FRAME_H_
