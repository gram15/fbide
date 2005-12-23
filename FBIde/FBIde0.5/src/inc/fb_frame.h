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
    fbideID_ToolBar,
    fbideID_StatusBar,
    fbideID_FullScreen,
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
    fbideID_SrcFormatter,
    fbideID_TabAreaPopUp,
    fbideID_Notebook,
    fbideID_CloseAET,
    fbideID_ReOpen,
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
class FB_Browser;
class FB_StatusBar;
class FB_Config;
class wxFB_Notebook;
class FB_Doc;
class FB_STC;
class FB_DocList;
class FB_ToolBar;

class FB_Frame: public wxFrame {    
    
    private:
        DECLARE_EVENT_TABLE()
        FB_Config           * m_Config;
        FB_DocList          * m_DocList;

        wxSplitterWindow    * m_HSplitter;
        wxSplitterWindow    * m_VSplitter;
        wxFB_Notebook       * m_Code_areaTab;
        FB_Console          * m_Console_area;
        FB_Browser          * m_Browser_area;
        FB_StatusBar        * m_StatusBar;
        FB_ToolBar          * m_ToolBar;

        wxWindow            * m_Code_area;
        
        wxMenuItem          * m_ViewProject;
        wxMenuItem          * m_ViewConsole;
        wxMenuItem          * m_ViewToolBar;
        wxMenuItem          * m_ViewStatusBar;
        wxMenu              * m_EditMenu;
        wxMenu              * m_FileMenu;
        wxMenu              * m_FileMenu_New;
        wxMenu              * m_FileMenu_ReOpen;
        wxMenu              * m_SearchMenu;
        wxMenu              * m_ViewMenu;
        wxMenu              * m_ProjectMenu;
        wxMenu              * m_RunMenu;
        wxMenu              * m_ToolsMenu;
        wxMenu              * m_HelpMenu;
        wxMenuBar           * m_MenuBar;
        
        FB_STC              * m_ActiveSTC;
        FB_Doc              * m_ActiveDoc;
        int                 m_ActiveTabID;

        /// Creates the controls and sizers
        void CreateMenus();
        void CreateToolbar();
        void CreatePanels();
        void CreateStatusBar();
    
        /// Event handlers
        void OnEdit             ( wxCommandEvent& event );
        void OnMenuOpen         ( wxMenuEvent& event );
        
        void OnNew              ( wxCommandEvent& event );
        void OnNewproject       ( wxCommandEvent& event );
        void OnNewtemplate      ( wxCommandEvent& event );
        void OnOpen             ( wxCommandEvent& event );
        void OnFileHistory      ( wxCommandEvent& event );
        void OnSave             ( wxCommandEvent& event );
        void OnSaveas           ( wxCommandEvent& event );
        void OnSaveprojectas    ( wxCommandEvent& event );
        void OnSaveAll          ( wxCommandEvent& event );
        void OnSessionload      ( wxCommandEvent& event );
        void OnSessionsave      ( wxCommandEvent& event );
        void OnClose            ( wxCommandEvent& event );
        void OnCloseAll         ( wxCommandEvent& event );
        void OnCloseAET         ( wxCommandEvent& event );
        void OnCloseproject     ( wxCommandEvent& event );
        void OnNewinstance      ( wxCommandEvent& event );
        void OnExit             ( wxCommandEvent& event );
        void OnFind             ( wxCommandEvent& event );
        void OnFindnext         ( wxCommandEvent& event );
        void OnReplace          ( wxCommandEvent& event );
        void OnGoto             ( wxCommandEvent& event );
        void OnIncrsearch       ( wxCommandEvent& event );
        void OnOutput           ( wxCommandEvent& event );
        void OnProject          ( wxCommandEvent& event );
        void OnToolBar          ( wxCommandEvent& event );
        void OnStatusBar        ( wxCommandEvent& event );
        void OnFullScreen       ( wxCommandEvent& event );
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
        
        void OnTabPopUp         ( wxCommandEvent& event );
        void OnTabChanged       ( wxNotebookEvent& event );
        
        void OnProgramClose     ( wxCloseEvent &event );
        
        bool SaveDocument       ( int TabID = -1 );
        bool SaveDocumentAs     ( int TabID = -1 );
        bool SaveAllDocuments   (  );
        
        bool CloseDocument      ( int TabID = -1 );
        bool CloseAllDocument   (  );
        bool CloseAET           (  );
                
        void CreateDocument     ( wxString File = "", bool SelectTab = true );
        void DeleteDocument     ( int idx );

    public:
        // Constructor
        FB_Frame( wxWindow* parent, wxWindowID id = SYMBOL_FB_FRAME_IDNAME, const wxString& caption = SYMBOL_FB_FRAME_TITLE, const wxPoint& pos = SYMBOL_FB_FRAME_POSITION, const wxSize& size = SYMBOL_FB_FRAME_SIZE, long style = SYMBOL_FB_FRAME_STYLE );
        
        // Destructor
        ~FB_Frame();
        
        FB_Config * GetConfig() const { return m_Config; }
        
        void SetStatus( int idx = -1 );
};

#endif
    // _FB_FRAME_H_
