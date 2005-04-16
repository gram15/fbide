/*
* This file is part of FBIde, an open-source (cross-platform) IDE for 
* FreeBasic compiler.
* Copyright (C) 2005  Indrek Triipus
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
* Contact e-mail: Albert Varaksin <vongodric@hotmail.com>
* Program URL   : http://www.hot.ee/fbide
*/

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
