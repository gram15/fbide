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
* Contact e-mail: Indrek Triipus <madedog@gmail.com>
* Program URL   : http://fbide.sourceforge.net
*/

#include "inc/main.h"
#include <wx/fileconf.h>
#include <wx/wfstream.h>

void MyFrame::OpenLangFile( wxString FileName ){
     
     //First lets select the file we are going to use...
     wxFFileInputStream FileINIIS( EditorPath + "ide/lang/" + FileName + ".fbl" );
     //And then open it as an INI file

     wxFileConfig FileINI(FileINIIS);
          
     //First the key to "general"
     FileINI.SetPath("/general");     
     
     wxString temp;
     for (int i=0; i<RowCount; i++){
         temp="";
         temp<<i;
         Lang[i] = FileINI.Read(temp,"");
     }
         
     
     //And begin =D
     Language.WelcomeMessage = FileINI.Read("WelcomeMessage", "");
     
     //Configuration Dialog stuff
     FileINI.SetPath("/configdialog");
     Language.ConfigTitle = FileINI.Read("ConfigTitle", "");
     
     //Lets set the key to "menus"
     FileINI.SetPath("/menus");
     Language.MenuFile   = FileINI.Read("MenuFile",   "");
     Language.MenuEdit   = FileINI.Read("MenuEdit",   "");
     Language.MenuSearch = FileINI.Read("MenuSearch", "");
     Language.MenuView   = FileINI.Read("MenuView",   "");
     Language.MenuTools  = FileINI.Read("MenuTools",  "");
     Language.MenuRun    = FileINI.Read("MenuRun",    "");
     Language.MenuHelp   = FileINI.Read("MenuHelp",   "");
     
     Language.FileNew           = FileINI.Read("FileNew",          "");
     Language.FileNewDesc       = FileINI.Read("FileNewDesc",      "");
     Language.FileOpen          = FileINI.Read("FileOpen",         "");
     Language.FileOpenDesc      = FileINI.Read("FileOpenDesc",     "");
     Language.FileSave          = FileINI.Read("FileSave",         "");
     Language.FileSaveDesc      = FileINI.Read("FileSaveDesc",     "");
     Language.FileSaveall       = FileINI.Read("FileSaveall",      "");
     Language.FileSaveallDesc   = FileINI.Read("FileSaveallDesc",  "");
     Language.FileSaveas        = FileINI.Read("FileSaveas",       "");
     Language.FileSaveasDesc    = FileINI.Read("FileSaveasDesc",   "");
     Language.FileClose         = FileINI.Read("FileClose",        "");
     Language.FileCloseDesc     = FileINI.Read("FileCloseDesc",    "");
     Language.FileNewWindow     = FileINI.Read("FileNewWindow",    "");
     Language.FileNewWindowDesc = FileINI.Read("FileNewWindowDesc","");
     Language.FileQuit          = FileINI.Read("FileQuit",         "");
     Language.FileQuitDesc      = FileINI.Read("FileQuitDesc",     "");
     
     Language.EditUndo               = FileINI.Read("EditUndo",              "");
     Language.EditUndoDesc           = FileINI.Read("EditUndoDesc",          "");
     Language.EditRedo               = FileINI.Read("EditRedo",              "");
     Language.EditRedoDesc           = FileINI.Read("EditRedoDesc",          "");
     Language.EditCut                = FileINI.Read("EditCut",               "");
     Language.EditCutDesc            = FileINI.Read("EditCutDesc",           "");
     Language.EditCopy               = FileINI.Read("EditCopy",              "");
     Language.EditCopyDesc           = FileINI.Read("EditCopyDesc",          "");
     Language.EditPaste              = FileINI.Read("EditPaste",             "");
     Language.EditPasteDesc          = FileINI.Read("EditPasteDesc",         "");
     Language.EditSelectall          = FileINI.Read("EditSelectall",         "");
     Language.EditSelectallDesc      = FileINI.Read("EditSelectallDesc",     "");
     Language.EditSelectline         = FileINI.Read("EditSelectline",        "");
     Language.EditSelectlineDesc     = FileINI.Read("EditSelectlineDesc"    ,"");
     Language.EditIndentIncrease     = FileINI.Read("EditIndentIncrease",    "");
     Language.EditIndentIncreaseDesc = FileINI.Read("EditIndentIncreaseDesc","");
     Language.EditIndentDecrease     = FileINI.Read("EditIndentDecrease",    "");
     Language.EditIndentDecreaseDesc = FileINI.Read("EditIndentDecreaseDesc","");
     Language.EditComment            = FileINI.Read("EditComment",           "");
     Language.EditCommentDesc        = FileINI.Read("EditCommentDesc",       "");
     Language.EditUnComment          = FileINI.Read("EditUnComment",         "");
     Language.EditUnCommentDesc      = FileINI.Read("EditUnCommentDesc",     "");
     
     Language.SearchFind         = FileINI.Read("SearchFind",         "");
     Language.SearchFindDesc     = FileINI.Read("SearchFindDesc",     "");
     Language.SearchFindnext     = FileINI.Read("SearchFindnext",     "");
     Language.SearchFindnextDesc = FileINI.Read("SearchFindnextDesc", "");
     Language.SearchReplace      = FileINI.Read("SearchReplace",      "");
     Language.SearchReplaceDesc  = FileINI.Read("SearchReplaceDesc",  "");
     Language.SearchGotoline     = FileINI.Read("SearchGotoline",     "");
     Language.SearchGotolineDesc = FileINI.Read("SearchGotolineDesc", "");

     Language.ViewSettings     = FileINI.Read("ViewSettings",     "");
     Language.ViewSettingsDesc = FileINI.Read("ViewSettingsDesc", "");
     
     Language.ToolsSubs          = FileINI.Read("ToolsSubs",          "");
     Language.ToolsSubsDesc      = FileINI.Read("ToolsSubsDesc",      "");
     Language.ToolsConverter     = FileINI.Read("ToolsConverter",     "");
     Language.ToolsConverterDesc = FileINI.Read("ToolsConverterDesc", "");
     
     Language.RunCompile           = FileINI.Read("RunCompile",          "");
     Language.RunCompileDesc       = FileINI.Read("RunCompileDesc",      "");
     Language.RunCompileandrun     = FileINI.Read("RunCompileandrun",    "");
     Language.RunCompileandrunDesc = FileINI.Read("RunCompileandrunDesc","");
     Language.RunRun               = FileINI.Read("RunRun",              "");
     Language.RunRunDesc           = FileINI.Read("RunRunDesc",          "");
     Language.RunQuickrun          = FileINI.Read("RunQuickrun",         "");
     Language.RunQuickrunDesc      = FileINI.Read("RunQuickrunDesc",     "");
     Language.RunCmdprompt         = FileINI.Read("RunCmdprompt",        "");
     Language.RunCmdpromptDesc     = FileINI.Read("RunCmdpromptDesc",    "");
     Language.RunParameters        = FileINI.Read("RunParameters",       "");
     Language.RunParametersDesc    = FileINI.Read("RunParamteres",       "");
     Language.RunCompparam         = FileINI.Read("RunCompparam",        "");
     Language.RunCompparamDesc     = FileINI.Read("RunCompparamDesc",    "");
     Language.RunShowexitcode      = FileINI.Read("RunShowexitcode",     "");
     Language.RunShowexitcodeDesc  = FileINI.Read("RunShowexitcodeDesc", "");
     
     Language.HelpAbout     = FileINI.Read("HelpAbout",     "");
     Language.HelpAboutDesc = FileINI.Read("HelpAboutDesc", "");
     
     return;               
}
               
