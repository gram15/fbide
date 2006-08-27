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

#include "../sdk/sdk.h"
#include "inc/doc_stc.h"

#define SCE_FB_DEFAULT          0
#define SCE_FB_SLCOMMENT        1
#define SCE_FB_MLCOMMENT        2
#define SCE_FB_NUMBER           3
#define SCE_FB_OCTNUMBER        4
#define SCE_FB_HEXNUMBER        5
#define SCE_FB_BINNUMBER        6
#define SCE_FB_BADNUMBER        7
#define SCE_FB_STRING           8
#define SCE_FB_OPENSTRING       9
#define SCE_FB_IDENTIFIER       10
#define SCE_FB_LABEL            11
#define SCE_FB_OPERATOR         12
#define SCE_FB_KEYWORD1         13
#define SCE_FB_KEYWORD2         14
#define SCE_FB_KEYWORD3         15
#define SCE_FB_KEYWORD4         16
#define SCE_FB_KEYWORD5         17
#define SCE_FB_ASM_DEFAULT      18
#define SCE_FB_ASM_KEYWORD1     19
#define SCE_FB_ASM_KEYWORD2     20
#define SCE_FB_ASM_KEYWORD3     21
#define SCLEX_FB 79

BEGIN_EVENT_TABLE(Doc_Stc, wxStyledTextCtrl)
    EVT_MENU(wxID_SAVE,         Doc_Stc::OnSave)
    EVT_MENU(wxID_CLOSE,        Doc_Stc::OnClose)
END_EVENT_TABLE()

Doc_Stc::Doc_Stc(const wxString & file)
{
    Create (Manager::Get()->GetDocManager()->GetWindow(), wxID_ANY);
    LoadStyle();
    if (file.Len() && ::wxFileExists(file))
        LoadFile (file);
}


Doc_Stc::~Doc_Stc()
{

}


void Doc_Stc::OnClose (wxCommandEvent & event)
{
    if (GetModify())
    {
        int result = wxMessageBox(_T("This file has been modified. Save?"), _T("Save?"),
                                  wxYES_NO | wxCANCEL | wxICON_QUESTION);
        if (result == wxCANCEL) return;
    }
    delete this;
}


void Doc_Stc::OnSave (wxCommandEvent & event)
{
    wxMessageBox (_T("testing"));
}


void Doc_Stc::LoadStyle (const wxString & regPath)
{
    SetKeyWords (0, _T("asm print locate end sleep goto function sub color select case if then else elseif"));
    SetLexer (SCLEX_FB);

    StyleInfo defStyle;

    {
        StyleInfo info(defStyle);
        SetStyle(wxSTC_STYLE_DEFAULT, info);
        SetStyle(SCE_FB_DEFAULT, info);
        SetStyle(SCE_FB_ASM_DEFAULT, info);
        SetStyle(SCE_FB_IDENTIFIER, info);
    }

    {
        StyleInfo info(defStyle);
        info.SetFG(_T("RGB(0, 0, 255)"));
        SetStyle(SCE_FB_STRING, info);
        info.SetBold(true);
        SetStyle(SCE_FB_OPENSTRING, info);
    }

    {
        StyleInfo info(defStyle);
        info.SetFG(_T("RGB(200, 0, 200)"));
        SetStyle(SCE_FB_NUMBER, info);
        SetStyle(SCE_FB_HEXNUMBER, info);
        SetStyle(SCE_FB_BINNUMBER, info);
        SetStyle(SCE_FB_OCTNUMBER, info);
        info.SetBold(true);
        info.SetFG(_T("RGB(255, 0, 0)"));
        SetStyle(SCE_FB_BADNUMBER, info);
    }

    {
        StyleInfo info(defStyle);
        info.SetFG(_T("RGB(128, 128, 128)"));
        SetStyle(SCE_FB_SLCOMMENT, info);
        SetStyle(SCE_FB_MLCOMMENT, info);
    }

    {
        StyleInfo info(defStyle);
        info.SetFG(_T("RGB(0, 128, 128)"));
        SetStyle(SCE_FB_LABEL, info);
    }

    {
        StyleInfo info(defStyle);
        info.SetFG(_T("RGB(255, 0, 0)"));
        SetStyle(SCE_FB_OPERATOR, info);
    }

    {
        StyleInfo info(defStyle);
        info.SetBold(true);
        SetStyle(SCE_FB_KEYWORD1, info);
    }
}



void Doc_Stc::SetStyle (int style, const StyleInfo & data)
{
    StyleSetForeground (style, data.GetFG());
    StyleSetBackground (style, data.GetBG());
    StyleSetFontAttr (
        style,
        data.GetSize(), data.GetFont(),
        data.IsBold(), data.IsItalic(), data.IsUnderlined()
    );
}
