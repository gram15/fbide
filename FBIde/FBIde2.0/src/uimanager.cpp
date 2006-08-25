/*
 * This file is part of FBIde, an open-source (cross-platform) IDE for
 * FreeBasic compiler.
 * Copyright (C) 2005 - 2006 Albert Varaksin
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

#include "inc/manager.h"
#include "inc/main.h"

UiManager::UiManager() : m_frame(NULL)
{
    m_frame = new Main();
    return;
}



UiManager::~UiManager()
{
    return;
}


/*
void UiManager::OnClose (wxCloseEvent & event)
{
    FBIdeEvent custom(EVT_FBIDE_COMMAND, wxID_EXIT);
    GetEventHandler()->ProcessEvent( custom );
    if (!custom.IsAllowed()) return;


    Manager::Get()->ShutDown();
    event.Skip();
}



void UiManager::Close (FBIdeEvent & event)
{
    if (wxMessageBox(_T("Exit FBIde?"), _T("Quit"), wxYES_NO | wxICON_QUESTION) == wxNO)
        event.Veto();
}
*/
