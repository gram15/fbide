/*
 * This file is part of FBIde, an open-source (cross-platform) IDE for
 * FreeBasic compiler.
 * Copyright (C) 2005  Albert Varaksin
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
 * Program URL   : http://fbide.sourceforge.net
 */

#include "inc/main.h"
#include <wx/fileconf.h>
#include <wx/wfstream.h>

void MyFrame::OpenLangFile( wxString FileName ) {

    //First lets select the file we are going to use...
    wxFFileInputStream FileINIIS( EditorPath + _T("IDE/lang/") + FileName + _T(".fbl") );

    //And then open it as an INI file
    wxFileConfig FileINI(FileINIIS);

    //Pathname to search...
    FileINI.SetPath( _T("/FBIde") );

    //And GO!
    wxString temp;
    for (int i=0; i < 245; i++) {
        temp = _T("");
        temp<<i;
        //Lang.Add(FileINI.Read(temp,""));
        Lang.Add(FileINI.Read(temp, _T("")));
    }

    Lang.Shrink();

    return;
}

