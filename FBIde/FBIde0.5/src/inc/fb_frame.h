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
#include "wx/sashwin.h"


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

class FB_Frame: public wxFrame
{    
    DECLARE_CLASS( FB_Frame )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    FB_Frame( );
    FB_Frame( wxWindow* parent, wxWindowID id = SYMBOL_FB_FRAME_IDNAME, const wxString& caption = SYMBOL_FB_FRAME_TITLE, const wxPoint& pos = SYMBOL_FB_FRAME_POSITION, const wxSize& size = SYMBOL_FB_FRAME_SIZE, long style = SYMBOL_FB_FRAME_STYLE );

    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_FB_FRAME_IDNAME, const wxString& caption = SYMBOL_FB_FRAME_TITLE, const wxPoint& pos = SYMBOL_FB_FRAME_POSITION, const wxSize& size = SYMBOL_FB_FRAME_SIZE, long style = SYMBOL_FB_FRAME_STYLE );

    /// Creates the controls and sizers
    void CreateControls();


    void OnNewClick( wxCommandEvent& event );
    void OnFbideidNewprojectClick( wxCommandEvent& event );
    void OnFbideidNewtemplateClick( wxCommandEvent& event );
    void OnOpenClick( wxCommandEvent& event );
    void OnSaveClick( wxCommandEvent& event );
    void OnSaveasClick( wxCommandEvent& event );
    void OnFbideidSaveprojectasClick( wxCommandEvent& event );
    void OnSaveAllClick( wxCommandEvent& event );
    void OnFbideidSessionloadClick( wxCommandEvent& event );
    void OnFbideidSessionsaveClick( wxCommandEvent& event );
    void OnCloseClick( wxCommandEvent& event );
    void OnCloseAllClick( wxCommandEvent& event );
    void OnFbideidCloseprojectClick( wxCommandEvent& event );
    void OnFbideidNewinstanceClick( wxCommandEvent& event );
    void OnExitClick( wxCommandEvent& event );
    void OnUndoClick( wxCommandEvent& event );
    void OnRedoClick( wxCommandEvent& event );
    void OnCopyClick( wxCommandEvent& event );
    void OnCutClick( wxCommandEvent& event );
    void OnPasteClick( wxCommandEvent& event );
    void OnSelectallClick( wxCommandEvent& event );
    void OnFbideidSelectlineClick( wxCommandEvent& event );
    void OnJustifyRightClick( wxCommandEvent& event );
    void OnJustifyLeftClick( wxCommandEvent& event );
    void OnFbideidCommentblockClick( wxCommandEvent& event );
    void OnFbideidUncommentblockClick( wxCommandEvent& event );
    void OnFindClick( wxCommandEvent& event );
    void OnFbideidFindnextClick( wxCommandEvent& event );
    void OnReplaceClick( wxCommandEvent& event );
    void OnFbideidGotoClick( wxCommandEvent& event );
    void OnFbideidIncrsearchClick( wxCommandEvent& event );
    void OnFbideidOutputClick( wxCommandEvent& event );
    void OnFbideidNewprojectfileClick( wxCommandEvent& event );
    void OnFbideidProjectaddClick( wxCommandEvent& event );
    void OnFbideidProjectremoveClick( wxCommandEvent& event );
    void OnFbideidProjectoptionsClick( wxCommandEvent& event );
    void OnFbideidCompileClick( wxCommandEvent& event );
    void OnFbideidCompileandrunClick( wxCommandEvent& event );
    void OnFbideidRebuildallClick( wxCommandEvent& event );
    void OnFbideidQuickrunClick( wxCommandEvent& event );
    void OnFbideidRunClick( wxCommandEvent& event );
    void OnFbideidParametersClick( wxCommandEvent& event );
    void OnFbideidDebugClick( wxCommandEvent& event );
    void OnFbideidOpenconsoleClick( wxCommandEvent& event );
    void OnFbideidProfileanalysisClick( wxCommandEvent& event );
    void OnFbideidShowexitcodeClick( wxCommandEvent& event );
    void OnPropertiesClick( wxCommandEvent& event );
    void OnFbideidSrcformatterClick( wxCommandEvent& event );
    void OnHelpClick( wxCommandEvent& event );
    void OnAboutClick( wxCommandEvent& event );

    static bool ShowToolTips();

    wxToolBar* FB_Toolbar;

};

#endif
    // _FB_FRAME_H_
