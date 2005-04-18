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
* Program URL   : http://www.hot.ee/fbide
*/

#include "inc/main.h"
#include <wx/fileconf.h>
#include <wx/wfstream.h>

void MyFrame::OpenLangFile( wxString FileName ){

     wxFileInputStream FileINIIS( EditorPath + "ide\\lang\\" + FileName + ".fbl" );
     wxFileConfig FileINI(FileINIIS);
          
     FileINI.SetPath("/menus");
     Language.MenuFile   = FileINI.Read("MenuFile",   "");
     Language.MenuEdit   = FileINI.Read("MenuEdit",   "");
     Language.MenuSearch = FileINI.Read("MenuSearch", "");
     Language.MenuView   = FileINI.Read("MenuView",   "");
     Language.MenuTools  = FileINI.Read("MenuTools",  "");
     Language.MenuRun    = FileINI.Read("MenuRun",    "");
     Language.MenuHelp   = FileINI.Read("MenuHelp",   "");
     
     return;               
}
               
