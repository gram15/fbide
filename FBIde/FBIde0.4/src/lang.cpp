#include "inc/main.h"

struct FBIdeLangFile{
       //Menu bar captions
       wxString MenuFile;
       wxString MenuEdit;
       wxString MenuSearch;
       wxString MenuView;
       wxString MenuTools;
       wxString MenuRun;
       wxString MenuHelp;
       
       //File menu: first is caption, second is description
       wxString FileNew;
       wxString FileNewDesc;
       wxString FileOpen;
       wxString FileOpenDesc;
       wxString FileSave;
       wxString FileSaveDesc;
       wxString FileSaveas;
       wxString FileSaveasDesc;
       wxString FileSaveall;
       wxString FileSaveallDesc;
       wxString FileClose;
       wxString FileCloseDesc;
       wxString FileNewWindow;
       wxString FileNewWindowDesc;
       wxString FileQuit;
       wxString FileQuitDesc;
       
       //Edit menu
       wxString EditUndo;
       wxString EditUndoDesc;
       wxString EditRedo;
       wxString EditRedoDesc;
       wxString EditCut;
       wxString EditCutDesc;
       wxString EditCopy;
       wxString EditCopyDesc;
       wxString EditPaste;
       wxString EditPasteDesc;
       wxString EditSelectall;
       wxString EditSelectallDesc;
       wxString EditSelectline;
       wxString EditSelectlineDesc;
       wxString EditIndentIncrease;
       wxString EditIndentIncreaseDesc;
       wxString EditIndentDecrease;
       wxString EditIndentDecreaseDesc;
       
       //Search menu
       wxString SearchFind;
       wxString SearchFindDesc;
       wxString SearchFindnext;
       wxString SearchFindnextDesc;
       wxString SearchReplace;
       wxString SearchReplaceDesc;
       wxString SearchGotoline;
       wxString SearchGotolineDesc;
       
       //View menu
       wxString ViewSettings;
       wxString ViewSettingsDesc;
       
       //Tools menu
       wxString ToolsSubs;
       wxString ToolsSubsDesc;
       wxString ToolsConverter;
       wxString ToolsConverterDesc;
       
       //Run menu
       wxString RunCompile;
       wxString RunCompileDesc;
       wxString RunCompileandrun;
       wxString RunCompileandrunDesc;
       wxString RunRun;
       wxString RunRunDesc;
       wxString RunQuickrun;
       wxString RunQuickrunDesc;
       wxString RunCmdprompt;
       wxString RunCmdpromptDesc;
       wxString RunParameters;
       wxString RunParametersDesc;
       wxString RunCompparam;
       wxString RunCompparamDesc;
       wxString RunShowexitcode;
       wxString RunShowexitcodeDesc;
       
       //Help menu
       wxString HelpAbout;
       wxString HelpAboutDesc;
       };

FBIdeLangFile FBIdeLanguage;
