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
#include "inc/doc_stc.h"

int fbiID_DOCBOOK = ::wxNewId();

BEGIN_EVENT_TABLE(Main, wxFrame)
    EVT_MENU(wxID_EXIT,     Main::OnExit)
    EVT_MENU(wxID_NEW,      Main::OnNew)
    EVT_MENU(wxID_CLOSE,    Main::OnDocumentEvent)
    EVT_MENU(wxID_SAVE,     Main::OnDocumentEvent)
    EVT_CLOSE(Main::OnCloseFrame)

    // Document notebook
    EVT_NOTEBOOK_PAGE_CHANGED(fbiID_DOCBOOK, Main::OnDocumentBook)
    EVT_NOTEBOOK_PAGE_CHANGING(fbiID_DOCBOOK, Main::OnDocumentBook)
END_EVENT_TABLE()


Main::Main()
    : wxFrame(NULL, wxID_ANY, _T("FBIde"))
{

}




Main::~Main()
{
}



void Main::OnExit (wxCommandEvent & event)
{
    Close (true);
}



void Main::OnNew (wxCommandEvent & event)
{
    Doc_Stc * doc = new Doc_Stc();
    doc->ShowDocument();
    return;
}


void Main::OnDocumentBook (wxNotebookEvent & event)
{
    // send to document manager
    Manager::Get()->GetDocManager()->ProcessEvent(event);
    return;
}


void Main::OnDocumentEvent (wxCommandEvent & event)
{
    DocManager * mngr = Manager::Get()->GetDocManager();
    if (!mngr->IsActive()) return;

    // Send event to the document
    event.StopPropagation();
    mngr->GetActive()->ProcessDocumentEvent (event);
    return;
}



void Main::OnOpen (wxCommandEvent & event)
{
    return;
}



/**
 * This means that we want to exit FBIde
 * @todo - first generate FBIde notification
 *         event about exiting!
 */
void Main::OnCloseFrame (wxCloseEvent & event)
{
    Manager::Get()->ShutDown();
    event.Skip();
}
