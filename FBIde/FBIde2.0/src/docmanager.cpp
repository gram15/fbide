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
 */

DocManager::DocManager () : m_bookCtrl(NULL), m_window(NULL)
{
    m_bookCtrl = new wxNotebook (Manager::Get()->GetUiManager()->GetFrame(), wxID_ANY);
    m_bookCtrl->Hide();
    m_window = m_bookCtrl;
    return;
}



DocManager::~DocManager ()
{
    /**
     * Deleteing Document this way is safe. it does callback
     * into doc managaer to clear itself.
     */
    while (m_list.Count())
      delete m_list[0];

    m_bookCtrl->Destroy();
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

    wxFrame * frame = Manager::Get()->GetUiManager()->GetFrame();
    frame->Freeze();
        m_bookCtrl->AddPage (doc->GetDocumentWindow(), doc->GetDocumentName());
        if (m_bookCtrl->GetPageCount() == 1) m_bookCtrl->Show();
    frame->Thaw();

    return true;
}



bool DocManager::Hide (DocumentBase * doc)
{
    if (!Exists(doc)) return false;

    wxFrame * frame = Manager::Get()->GetUiManager()->GetFrame();
    size_t page = 0;

    for ( ; page < m_bookCtrl->GetPageCount(); page++)
        if (m_bookCtrl->GetPage(page) == doc->GetDocumentWindow())
        {
            frame->Freeze();
                m_bookCtrl->RemovePage (page);
                if (m_bookCtrl->GetPageCount() == 0) m_bookCtrl->Hide();
                doc->GetDocumentWindow()->Hide();
            frame->Thaw();
            return true;
        }
    return false;
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
