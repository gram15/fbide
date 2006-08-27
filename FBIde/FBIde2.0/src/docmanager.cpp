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

/**
 * @todo - allow documents to have an image
 * @todo - adding a list of documents
 * @todo - when tab's undocking is done,
 *         then allow focusing untabbed documents too
 * @todo - send events when needed!
 */


BEGIN_EVENT_TABLE(DocManager, wxEvtHandler)
    EVT_NOTEBOOK_PAGE_CHANGING(-1,  DocManager::OnPageChanging)
    EVT_NOTEBOOK_PAGE_CHANGED(-1,   DocManager::OnPageChanged)
END_EVENT_TABLE()


DocManager::DocManager () : m_bookCtrl(NULL), m_window(NULL), m_activeDoc(NULL)
{
    m_bookCtrl = Manager::Get()->GetUiManager()->GetDocumentBook();
    m_window = m_bookCtrl;
    return;
}



DocManager::~DocManager ()
{
    while (m_list.Count())
      delete m_list[0];

    Manager::Get()->GetUiManager()->HideDocumentBook();
}



void DocManager::OnPageChanging (wxNotebookEvent & event)
{

}



void DocManager::OnPageChanged (wxNotebookEvent & event)
{
    m_activeDoc = DetectActive();
    Manager::Get()->GetUiManager()->SetTitle(m_activeDoc->GetDocumentName());
    m_activeDoc->GetDocumentWindow()->SetFocus();
}



bool DocManager::Add (DocumentBase * doc, bool show)
{
    if (Exists(doc)) return false;

    m_list.Add(doc);

    if (show)
        Show (doc);

    return true;
}



int DocManager::Add (DocumentList * docs, bool show)
{
    return 0;
}



bool DocManager::Remove (DocumentBase * doc)
{
    if (!Exists(doc)) return false;

    Hide (doc);
    m_list.Remove (doc);

    return true;
}



bool DocManager::IsVisible (DocumentBase * doc)
{
    if (!Exists(doc)) return false;

    for (size_t page = 0 ; page < m_bookCtrl->GetPageCount(); page++)
        if (m_bookCtrl->GetPage(page) == doc->GetDocumentWindow())
            return true;

    return false;
}



bool DocManager::Show (DocumentBase * doc)
{
    if (!Exists(doc)) return false;

    m_bookCtrl->AddPage (doc->GetDocumentWindow(), doc->GetDocumentName(), true);

    if (m_bookCtrl->GetPageCount() == 1)
        Manager::Get()->GetUiManager()->ShowDocumentBook();

    return true;
}



bool DocManager::Hide (DocumentBase * doc)
{
    if (!Exists(doc)) return false;

    for (size_t page = 0; page < m_bookCtrl->GetPageCount(); page++)
        if (m_bookCtrl->GetPage(page) == doc->GetDocumentWindow())
        {
            m_bookCtrl->RemovePage (page);
            if (m_bookCtrl->GetPageCount() == 0)
            {
                Manager::Get()->GetUiManager()->HideDocumentBook();
                m_activeDoc = NULL;
                Manager::Get()->GetUiManager()->SetTitle(_T(""));
            }
            return true;
        }

    return false;
}



DocumentBase * DocManager::DetectActive () const
{
    if (m_bookCtrl->GetPageCount() == 0) return NULL;

    wxWindow * active = m_bookCtrl->GetCurrentPage();
    for (size_t i = 0; i < m_list.Count(); i++)
        if (m_list[i]->GetDocumentWindow() == active)
            return m_list[i];

    return NULL;
}



bool DocManager::FocusNextDocument ()
{
    if (m_bookCtrl->GetPageCount() < 2) return false;
    m_bookCtrl->AdvanceSelection (true);
    return true;
}



bool DocManager::FocusPrevDocument ()
{
    if (m_bookCtrl->GetPageCount() < 2) return false;
    m_bookCtrl->AdvanceSelection (false);
    return true;
}
