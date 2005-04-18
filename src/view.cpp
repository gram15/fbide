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
* Program URL   : http://www.hot.ee/fbide
*/

#include "inc/main.h"
#include "inc/configdiag.h"
#include "inc/fbedit.h"

void MyFrame::OnSettings (wxCommandEvent 	&WXUNUSED(event)) {
    ConfigDialog dlg(this, -1, "FBIde settings");
    dlg.ShowModal();
    if (stc==0) return;
    stc->Freeze();
    stc->LoadSTCSettings();
    stc->LoadSTCTheme();
    stc->Thaw();
    return;
}
