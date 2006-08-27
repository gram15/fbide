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

extern int fbiID_DOCBOOK;

UiManager::UiManager() : m_frame(NULL), m_docNotebook(NULL)
{
    m_frame = new Main();
    m_docNotebook = new wxNotebook (m_frame, fbiID_DOCBOOK);
    m_docNotebook->Hide();
    CreateMenu();
    return;
}



UiManager::~UiManager()
{
    return;
}



void UiManager::CreateToolbar ()
{
    return;
}



void UiManager::SetTitle (const wxString & title)
{
    wxString newTitle;

    if (title.Len())
        newTitle << _T("FBIde - ") << title;
    else
        newTitle << _T("FBIde");

    m_frame->SetTitle (newTitle);
}



void UiManager::CreateMenu ()
{
    wxMenuBar * menubar = new wxMenuBar;

    #define BEGIN_MENU { \
        wxMenu * menu = new wxMenu;

    #define APPEND(id, title, help) { \
            wxMenuItem * item = new wxMenuItem (menu, id, title, help); \
            item->SetBitmap(GetMenuIcon(id)); \
            menu->Append (item); \
        }

    #define APPEND_SEPERATOR() menu->AppendSeparator();

    #define END_MENU(base, name) base->Append(menu, name); }

    BEGIN_MENU
        APPEND(wxID_NEW, _T("New document\tCtrl+N"), _T("Create new document"))
        APPEND_SEPERATOR()
        APPEND(wxID_OPEN, _T("Open\tCtrl+O"), _T("Open file"));
        APPEND(wxID_SAVE, _T("Save\tCtrl+O"), _T("Save current document"));
        APPEND_SEPERATOR()
        APPEND(wxID_CLOSE, _T("Close\tCtrl+F4"), _T("Close current document"));
        APPEND_SEPERATOR()
        APPEND(wxID_EXIT, _T("Exit\tCtrl+Q"), _T("Exit FBIde"))
    END_MENU(menubar, _T("&File"))

    m_frame->SetMenuBar (menubar);

    return;
}



void UiManager::CreateLayout ()
{
    return;
}



wxBookCtrlBase * UiManager::GetDocumentBook()
{
    return m_docNotebook;
}



void UiManager::ShowDocumentBook()
{
    m_docNotebook->Show();
    m_frame->SendSizeEvent();
}



void UiManager::HideDocumentBook()
{
    m_docNotebook->Hide();
}



wxBitmap UiManager::GetMenuIcon (int id)
{
    #define MAP_START(id) switch (id) {
    #define ENTRY(id, name) \
        case id : {\
            wxBitmap bitmap(wxBITMAP(bmp_##name)); \
            bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) ); \
            return bitmap; \
            break; }
    #define MAP_END default: {\
            wxBitmap bitmap(wxBITMAP(bmp_##empty)); \
            bitmap.SetMask( new wxMask( bitmap, wxColour( 191, 191, 191) ) ); \
            return bitmap; \
            break; } \
        }

    MAP_START(id)
        ENTRY(wxID_ABOUT,   about)
        ENTRY(wxID_NEW,     newsrc)
        ENTRY(wxID_SAVE,    save)
        ENTRY(wxID_CLOSE,   closefl)
        ENTRY(wxID_EXIT,    close)
        ENTRY(wxID_OPEN,    opnproj)
    MAP_END
}
