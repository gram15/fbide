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


/////////////////////////////////////////////////////////////////////////////
// Name:        configdialog.cpp
// Purpose:     
// Author:      
// Modified by: 
// Created:     02/02/2006 04:47:03
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma implementation "inc/ConfigDialog.h"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

////@begin includes
////@end includes
#include <wx/textfile.h>
#include "inc/configdiag.h"

////@begin XPM images
////@end XPM images

/*!
 * ConfigDialog type definition
 */

IMPLEMENT_DYNAMIC_CLASS( ConfigDialog, wxDialog )

/*!
 * ConfigDialog event table definition
 */

BEGIN_EVENT_TABLE( ConfigDialog, wxDialog )

////@begin ConfigDialog event table entries
    EVT_LISTBOX( ID_listThemeType, ConfigDialog::OnThemeSelectType )

    EVT_CHOICE( ID_chTheme, ConfigDialog::OnSelectTheme )

    EVT_BUTTON( ID_btnSaveTheme, ConfigDialog::OnSaveTheme )

    EVT_BUTTON( ID_btnForeground, ConfigDialog::OnBtnForeground )

    EVT_BUTTON( ID_btnBackground, ConfigDialog::OnBtnBackground )

    EVT_CHOICE( ID_chKeywordGroup, ConfigDialog::OnKeywordsGroup )

    EVT_BUTTON( ID_btnCompilerPath, ConfigDialog::OnCompilerPath )

    EVT_BUTTON( ID_btnHelpFilePath, ConfigDialog::OnHelpPath )

    EVT_BUTTON( wxID_OK, ConfigDialog::OnOkClick )

    EVT_BUTTON( wxID_CANCEL, ConfigDialog::OnCancelClick )

////@end ConfigDialog event table entries

END_EVENT_TABLE()

/*!
 * ConfigDialog constructors
 */

ConfigDialog::ConfigDialog( )
{
}


/**
 * Constructor....
 *
 */
ConfigDialog::ConfigDialog( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    // Ugly YUCK!!!
    m_Parent = reinterpret_cast<MyFrame *>( parent );
    
    // get data
    m_Style = m_Parent->Style;
    m_Prefs = m_Parent->Prefs;
    m_Lang = m_Parent->Lang;
    
    Create(parent, id, caption, pos, size, style);
    
    LoadGeneral();
    LoadThemes();
    LoadKeywords();
    LoadCompiler();
}


/*!
 * ConfigDialog creator
 */

bool ConfigDialog::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin ConfigDialog member initialisation
    m_MoGeneral = false;
    m_ModTheme = false;
    m_ModKeyWord = false;
    m_ModCompiler = false;
    objNoteBook = NULL;
    objPanelGeneral = NULL;
    chkAutoIndent = NULL;
    chkIndentGuides = NULL;
    chkWhiteSpaces = NULL;
    chkLineEnd = NULL;
    chkMatchingBraces = NULL;
    spinRightMargin = NULL;
    chkSyntaxHighlight = NULL;
    chkLineNumbers = NULL;
    chkRightMargin = NULL;
    chkFoldMargin = NULL;
    chkSplashScreen = NULL;
    spinTabSize = NULL;
    chLanguage = NULL;
    objPanelThemes = NULL;
    listThemeType = NULL;
    chTheme = NULL;
    btnSaveTheme = NULL;
    btnForeground = NULL;
    btnBackground = NULL;
    chFont = NULL;
    chkBold = NULL;
    chkItalic = NULL;
    chkUnderLined = NULL;
    spinFontSize = NULL;
    objPanelKeywords = NULL;
    chKeywordGroup = NULL;
    textKeyWords = NULL;
    objPanelCompiler = NULL;
    textCompilerPath = NULL;
    btnCompilerPath = NULL;
    textCompilerCommand = NULL;
    textRunCommand = NULL;
    textHelpFile = NULL;
    btnHelpFilePath = NULL;
////@end ConfigDialog member initialisation

////@begin ConfigDialog creation
    SetExtraStyle(GetExtraStyle()|wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    GetSizer()->Fit(this);
    GetSizer()->SetSizeHints(this);
    Centre();
////@end ConfigDialog creation
    return true;
}

/*!
 * Control creation for ConfigDialog
 */

void ConfigDialog::CreateControls()
{    
////@begin ConfigDialog content construction
    ConfigDialog* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    objNoteBook = new wxNotebook( itemDialog1, ID_NOTEBOOK, wxDefaultPosition, wxDefaultSize, wxNB_TOP|wxCLIP_CHILDREN  );

    //
    // 1 st tab
    //
    objPanelGeneral = new wxPanel( objNoteBook, TabID_General, wxDefaultPosition, wxDefaultSize, wxNO_BORDER|wxCLIP_CHILDREN |wxTAB_TRAVERSAL );
    wxBoxSizer* itemBoxSizer5 = new wxBoxSizer(wxVERTICAL);
    objPanelGeneral->SetSizer(itemBoxSizer5);

    wxStaticText* itemStaticText6 = new wxStaticText( objPanelGeneral, wxID_STATIC, m_Lang[104], wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer5->Add(itemStaticText6, 0, wxGROW|wxALL|wxADJUST_MINSIZE, 5);

    wxStaticLine* itemStaticLine7 = new wxStaticLine( objPanelGeneral, wxID_STATIC, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
    itemBoxSizer5->Add(itemStaticLine7, 0, wxGROW, 5);

    wxBoxSizer* itemBoxSizer8 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer5->Add(itemBoxSizer8, 0, wxGROW, 5);
    wxBoxSizer* itemBoxSizer9 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer8->Add(itemBoxSizer9, 1, wxALIGN_TOP|wxALL, 5);
    chkAutoIndent = new wxCheckBox( objPanelGeneral, ID_chkAutoIndent, m_Lang[112], wxDefaultPosition, wxDefaultSize, wxCHK_2STATE );
    chkAutoIndent->SetValue(false);
    itemBoxSizer9->Add(chkAutoIndent, 0, wxGROW|wxALL, 5);

    chkIndentGuides = new wxCheckBox( objPanelGeneral, ID_chkIndentGuides, m_Lang[110], wxDefaultPosition, wxDefaultSize, wxCHK_2STATE );
    chkIndentGuides->SetValue(false);
    itemBoxSizer9->Add(chkIndentGuides, 0, wxGROW|wxALL, 5);

    chkWhiteSpaces = new wxCheckBox( objPanelGeneral, ID_chkWhiteSpaces, m_Lang[109], wxDefaultPosition, wxDefaultSize, wxCHK_2STATE );
    chkWhiteSpaces->SetValue(false);
    itemBoxSizer9->Add(chkWhiteSpaces, 0, wxGROW|wxALL, 5);

    chkLineEnd = new wxCheckBox( objPanelGeneral, ID_chkLineEnd, m_Lang[108], wxDefaultPosition, wxDefaultSize, wxCHK_2STATE );
    chkLineEnd->SetValue(false);
    itemBoxSizer9->Add(chkLineEnd, 0, wxGROW|wxALL, 5);

    chkMatchingBraces = new wxCheckBox( objPanelGeneral, ID_chkMatchingBraces, m_Lang[105], wxDefaultPosition, wxDefaultSize, wxCHK_2STATE );
    chkMatchingBraces->SetValue(false);
    itemBoxSizer9->Add(chkMatchingBraces, 0, wxGROW|wxALL, 5);

    wxBoxSizer* itemBoxSizer15 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer9->Add(itemBoxSizer15, 0, wxGROW, 5);
    spinRightMargin = new wxSpinCtrl( objPanelGeneral, ID_spinRightMargin, _T("0"), wxDefaultPosition, wxSize(50, -1), wxSP_ARROW_KEYS, 0, 1000, 0 );
    itemBoxSizer15->Add(spinRightMargin, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText17 = new wxStaticText( objPanelGeneral, wxID_STATIC, m_Lang[116], wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer15->Add(itemStaticText17, 1, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);

    wxStaticLine* itemStaticLine18 = new wxStaticLine( objPanelGeneral, wxID_STATIC, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
    itemBoxSizer8->Add(itemStaticLine18, 0, wxGROW, 5);

    wxBoxSizer* itemBoxSizer19 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer8->Add(itemBoxSizer19, 1, wxALIGN_TOP|wxALL, 5);
    chkSyntaxHighlight = new wxCheckBox( objPanelGeneral, ID_chkSyntaxHighlight, m_Lang[106], wxDefaultPosition, wxDefaultSize, wxCHK_2STATE );
    chkSyntaxHighlight->SetValue(false);
    itemBoxSizer19->Add(chkSyntaxHighlight, 0, wxGROW|wxALL, 5);

    chkLineNumbers = new wxCheckBox( objPanelGeneral, ID_chkLineNumbers, m_Lang[103], wxDefaultPosition, wxDefaultSize, wxCHK_2STATE );
    chkLineNumbers->SetValue(false);
    itemBoxSizer19->Add(chkLineNumbers, 0, wxGROW|wxALL, 5);

    chkRightMargin = new wxCheckBox( objPanelGeneral, ID_chkRightMargin, m_Lang[107], wxDefaultPosition, wxDefaultSize, wxCHK_2STATE );
    chkRightMargin->SetValue(false);
    itemBoxSizer19->Add(chkRightMargin, 0, wxGROW|wxALL, 5);

    chkFoldMargin = new wxCheckBox( objPanelGeneral, ID_chkFoldMargin, m_Lang[111], wxDefaultPosition, wxDefaultSize, wxCHK_2STATE );
    chkFoldMargin->SetValue(false);
    itemBoxSizer19->Add(chkFoldMargin, 0, wxGROW|wxALL, 5);

    chkSplashScreen = new wxCheckBox( objPanelGeneral, ID_chkSplashScreen, m_Lang[232], wxDefaultPosition, wxDefaultSize, wxCHK_2STATE );
    chkSplashScreen->SetValue(false);
    itemBoxSizer19->Add(chkSplashScreen, 0, wxGROW|wxALL, 5);

    wxBoxSizer* itemBoxSizer25 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer19->Add(itemBoxSizer25, 0, wxGROW, 5);
    spinTabSize = new wxSpinCtrl( objPanelGeneral, ID_spinTabSize, _T("0"), wxDefaultPosition, wxSize(50, -1), wxSP_ARROW_KEYS, 0, 100, 0 );
    itemBoxSizer25->Add(spinTabSize, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText27 = new wxStaticText( objPanelGeneral, wxID_STATIC, m_Lang[117], wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer25->Add(itemStaticText27, 1, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);

    itemBoxSizer5->Add(5, 5, 0, wxGROW|wxLEFT|wxRIGHT|wxBOTTOM, 5);

    wxStaticText* itemStaticText29 = new wxStaticText( objPanelGeneral, wxID_STATIC, m_Lang[201], wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer5->Add(itemStaticText29, 0, wxALIGN_LEFT|wxALL|wxADJUST_MINSIZE, 5);

    wxStaticLine* itemStaticLine30 = new wxStaticLine( objPanelGeneral, wxID_STATIC, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
    itemBoxSizer5->Add(itemStaticLine30, 0, wxGROW, 5);

    wxBoxSizer* itemBoxSizer31 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer5->Add(itemBoxSizer31, 0, wxGROW, 5);
    wxStaticText* itemStaticText32 = new wxStaticText( objPanelGeneral, wxID_STATIC, m_Lang[203], wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer31->Add(itemStaticText32, 1, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);

    wxString* chLanguageStrings = NULL;
    chLanguage = new wxChoice( objPanelGeneral, ID_chLanguage, wxDefaultPosition, wxDefaultSize, 0, chLanguageStrings, 0 );
    itemBoxSizer31->Add(chLanguage, 1, wxGROW|wxALL, 5);

    wxStaticText* itemStaticText34 = new wxStaticText( objPanelGeneral, wxID_STATIC, m_Lang[202], wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer5->Add(itemStaticText34, 1, wxGROW|wxALL|wxADJUST_MINSIZE, 5);

    objNoteBook->AddPage(objPanelGeneral, m_Lang[99]);

    
    //
    // 2nd tab
    //
    
    objPanelThemes = new wxPanel( objNoteBook, TabID_Themes, wxDefaultPosition, wxDefaultSize, wxNO_BORDER|wxCLIP_CHILDREN |wxTAB_TRAVERSAL );
    wxBoxSizer* itemBoxSizer36 = new wxBoxSizer(wxVERTICAL);
    objPanelThemes->SetSizer(itemBoxSizer36);

    wxStaticText* itemStaticText37 = new wxStaticText( objPanelThemes, wxID_STATIC, m_Lang[140], wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer36->Add(itemStaticText37, 0, wxGROW|wxALL|wxADJUST_MINSIZE, 5);

    wxStaticLine* itemStaticLine38 = new wxStaticLine( objPanelThemes, wxID_STATIC, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
    itemBoxSizer36->Add(itemStaticLine38, 0, wxGROW, 5);

    wxBoxSizer* itemBoxSizer39 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer36->Add(itemBoxSizer39, 1, wxGROW|wxLEFT|wxRIGHT|wxBOTTOM, 5);
    wxBoxSizer* itemBoxSizer40 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer39->Add(itemBoxSizer40, 0, wxGROW, 5);
    wxStaticText* itemStaticText41 = new wxStaticText( objPanelThemes, wxID_STATIC, m_Lang[143], wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer40->Add(itemStaticText41, 0, wxGROW|wxTOP|wxBOTTOM|wxADJUST_MINSIZE, 5);

    wxString* listThemeTypeStrings = NULL;
    listThemeType = new wxListBox( objPanelThemes, ID_listThemeType, wxDefaultPosition, wxDefaultSize, 0, listThemeTypeStrings, wxLB_SINGLE );
    itemBoxSizer40->Add(listThemeType, 1, wxGROW, 5);

    wxBoxSizer* itemBoxSizer43 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer39->Add(itemBoxSizer43, 1, wxGROW|wxLEFT, 5);
    wxStaticText* itemStaticText44 = new wxStaticText( objPanelThemes, wxID_STATIC, m_Lang[140], wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer43->Add(itemStaticText44, 0, wxGROW|wxTOP|wxBOTTOM|wxADJUST_MINSIZE, 5);

    wxBoxSizer* itemBoxSizer45 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer43->Add(itemBoxSizer45, 0, wxGROW, 5);
    wxString* chThemeStrings = NULL;
    chTheme = new wxChoice( objPanelThemes, ID_chTheme, wxDefaultPosition, wxDefaultSize, 0, chThemeStrings, 0 );
    itemBoxSizer45->Add(chTheme, 1, wxALIGN_CENTER_VERTICAL|wxRIGHT, 5);

    btnSaveTheme = new wxButton( objPanelThemes, ID_btnSaveTheme, m_Lang[139], wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer45->Add(btnSaveTheme, 0, wxALIGN_CENTER_VERTICAL, 5);

    wxStaticLine* itemStaticLine48 = new wxStaticLine( objPanelThemes, wxID_STATIC, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
    itemBoxSizer43->Add(itemStaticLine48, 0, wxGROW|wxTOP|wxBOTTOM, 5);

    wxBoxSizer* itemBoxSizer49 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer43->Add(itemBoxSizer49, 0, wxGROW, 5);
    wxBoxSizer* itemBoxSizer50 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer49->Add(itemBoxSizer50, 1, wxGROW, 5);
    wxStaticText* itemStaticText51 = new wxStaticText( objPanelThemes, wxID_STATIC, m_Lang[144], wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer50->Add(itemStaticText51, 0, wxGROW|wxTOP|wxBOTTOM|wxADJUST_MINSIZE, 5);

    btnForeground = new wxButton( objPanelThemes, ID_btnForeground, _T(""), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer50->Add(btnForeground, 0, wxGROW|wxBOTTOM, 5);

    wxStaticText* itemStaticText53 = new wxStaticText( objPanelThemes, wxID_STATIC, m_Lang[145], wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer50->Add(itemStaticText53, 0, wxGROW|wxTOP|wxADJUST_MINSIZE, 5);

    btnBackground = new wxButton( objPanelThemes, ID_btnBackground, _T(""), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer50->Add(btnBackground, 0, wxGROW|wxBOTTOM, 5);

    wxStaticText* itemStaticText55 = new wxStaticText( objPanelThemes, wxID_STATIC, m_Lang[147], wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer50->Add(itemStaticText55, 0, wxGROW|wxTOP|wxADJUST_MINSIZE, 5);

    wxString* chFontStrings = NULL;
    chFont = new wxChoice( objPanelThemes, ID_chFont, wxDefaultPosition, wxDefaultSize, 0, chFontStrings, 0 );
    itemBoxSizer50->Add(chFont, 0, wxGROW|wxBOTTOM, 5);

    wxStaticLine* itemStaticLine57 = new wxStaticLine( objPanelThemes, wxID_STATIC, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
    itemBoxSizer49->Add(itemStaticLine57, 0, wxGROW|wxLEFT|wxRIGHT|wxBOTTOM, 5);

    wxBoxSizer* itemBoxSizer58 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer49->Add(itemBoxSizer58, 0, wxGROW, 5);
    wxStaticText* itemStaticText59 = new wxStaticText( objPanelThemes, wxID_STATIC, m_Lang[146], wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer58->Add(itemStaticText59, 0, wxGROW|wxTOP|wxBOTTOM|wxADJUST_MINSIZE, 5);

    chkBold = new wxCheckBox( objPanelThemes, ID_chkBold, m_Lang[136], wxDefaultPosition, wxDefaultSize, wxCHK_2STATE );
    chkBold->SetValue(false);
    itemBoxSizer58->Add(chkBold, 0, wxGROW|wxBOTTOM, 5);

    chkItalic = new wxCheckBox( objPanelThemes, ID_chkItalic, m_Lang[137], wxDefaultPosition, wxDefaultSize, wxCHK_2STATE );
    chkItalic->SetValue(false);
    itemBoxSizer58->Add(chkItalic, 0, wxGROW|wxTOP, 5);

    chkUnderLined = new wxCheckBox( objPanelThemes, ID_chkUnderLined, m_Lang[138], wxDefaultPosition, wxDefaultSize, wxCHK_2STATE );
    chkUnderLined->SetValue(false);
    itemBoxSizer58->Add(chkUnderLined, 0, wxGROW|wxTOP|wxBOTTOM, 5);

    itemBoxSizer58->Add(5, 5, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxStaticText* itemStaticText64 = new wxStaticText( objPanelThemes, wxID_STATIC, m_Lang[148], wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer58->Add(itemStaticText64, 0, wxGROW|wxTOP|wxADJUST_MINSIZE, 5);

    spinFontSize = new wxSpinCtrl( objPanelThemes, ID_spinFontSize, _T("0"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100, 0 );
    itemBoxSizer58->Add(spinFontSize, 0, wxALIGN_CENTER_HORIZONTAL, 5);

    objNoteBook->AddPage(objPanelThemes, m_Lang[140]);

    
    //
    // 3rd tab
    //
    
    objPanelKeywords = new wxPanel( objNoteBook, TabID_Keywords, wxDefaultPosition, wxDefaultSize, wxNO_BORDER|wxCLIP_CHILDREN |wxTAB_TRAVERSAL );
    wxBoxSizer* itemBoxSizer67 = new wxBoxSizer(wxVERTICAL);
    objPanelKeywords->SetSizer(itemBoxSizer67);

    wxStaticText* itemStaticText68 = new wxStaticText( objPanelKeywords, wxID_STATIC, m_Lang[149], wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer67->Add(itemStaticText68, 0, wxGROW|wxALL|wxADJUST_MINSIZE, 5);

    wxStaticLine* itemStaticLine69 = new wxStaticLine( objPanelKeywords, wxID_STATIC, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
    itemBoxSizer67->Add(itemStaticLine69, 0, wxGROW, 5);

    wxStaticText* itemStaticText70 = new wxStaticText( objPanelKeywords, wxID_STATIC, m_Lang[150], wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer67->Add(itemStaticText70, 0, wxGROW|wxLEFT|wxRIGHT|wxTOP|wxADJUST_MINSIZE, 5);

    wxString* chKeywordGroupStrings = NULL;
    chKeywordGroup = new wxChoice( objPanelKeywords, ID_chKeywordGroup, wxDefaultPosition, wxDefaultSize, 0, chKeywordGroupStrings, 0 );
    itemBoxSizer67->Add(chKeywordGroup, 0, wxALIGN_LEFT|wxALL, 5);

    textKeyWords = new wxTextCtrl( objPanelKeywords, ID_textKeyWords, _T(""), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
    itemBoxSizer67->Add(textKeyWords, 1, wxGROW|wxLEFT|wxRIGHT|wxBOTTOM, 5);

    objNoteBook->AddPage(objPanelKeywords, m_Lang[101]);

    
    //
    // 4th tab
    //    
    
    objPanelCompiler = new wxPanel( objNoteBook, TabID_Compiler, wxDefaultPosition, wxDefaultSize, wxNO_BORDER|wxCLIP_CHILDREN |wxTAB_TRAVERSAL );
    wxBoxSizer* itemBoxSizer74 = new wxBoxSizer(wxVERTICAL);
    objPanelCompiler->SetSizer(itemBoxSizer74);

    wxStaticText* itemStaticText75 = new wxStaticText( objPanelCompiler, wxID_STATIC, m_Lang[239], wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer74->Add(itemStaticText75, 0, wxGROW|wxALL|wxADJUST_MINSIZE, 5);

    wxStaticLine* itemStaticLine76 = new wxStaticLine( objPanelCompiler, wxID_STATIC, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
    itemBoxSizer74->Add(itemStaticLine76, 0, wxGROW, 5);

    wxStaticBox* itemStaticBoxSizer77Static = new wxStaticBox(objPanelCompiler, wxID_ANY, m_Lang[114]);
    wxStaticBoxSizer* itemStaticBoxSizer77 = new wxStaticBoxSizer(itemStaticBoxSizer77Static, wxHORIZONTAL);
    itemBoxSizer74->Add(itemStaticBoxSizer77, 0, wxGROW|wxALL, 5);
    textCompilerPath = new wxTextCtrl( objPanelCompiler, ID_textCompilerPath, _T(""), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticBoxSizer77->Add(textCompilerPath, 1, wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxBOTTOM, 5);

    btnCompilerPath = new wxButton( objPanelCompiler, ID_btnCompilerPath, _("..."), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticBoxSizer77->Add(btnCompilerPath, 0, wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxBOTTOM, 5);

    wxStaticBox* itemStaticBoxSizer80Static = new wxStaticBox(objPanelCompiler, wxID_ANY, m_Lang[115]);
    wxStaticBoxSizer* itemStaticBoxSizer80 = new wxStaticBoxSizer(itemStaticBoxSizer80Static, wxVERTICAL);
    itemBoxSizer74->Add(itemStaticBoxSizer80, 0, wxGROW|wxALL, 5);
    textCompilerCommand = new wxTextCtrl( objPanelCompiler, ID_textCompilerCommand, _T(""), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticBoxSizer80->Add(textCompilerCommand, 0, wxGROW|wxLEFT|wxRIGHT|wxBOTTOM, 5);

    wxStaticBox* itemStaticBoxSizer82Static = new wxStaticBox(objPanelCompiler, wxID_ANY, m_Lang[240]);
    wxStaticBoxSizer* itemStaticBoxSizer82 = new wxStaticBoxSizer(itemStaticBoxSizer82Static, wxVERTICAL);
    itemBoxSizer74->Add(itemStaticBoxSizer82, 0, wxGROW|wxALL, 5);
    textRunCommand = new wxTextCtrl( objPanelCompiler, ID_textRunCommand, _T(""), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticBoxSizer82->Add(textRunCommand, 0, wxGROW|wxLEFT|wxRIGHT|wxBOTTOM, 5);

    wxStaticBox* itemStaticBoxSizer84Static = new wxStaticBox(objPanelCompiler, wxID_ANY, m_Lang[241]);
    wxStaticBoxSizer* itemStaticBoxSizer84 = new wxStaticBoxSizer(itemStaticBoxSizer84Static, wxHORIZONTAL);
    itemBoxSizer74->Add(itemStaticBoxSizer84, 0, wxGROW|wxALL, 5);
    textHelpFile = new wxTextCtrl( objPanelCompiler, ID_textHelpFile, _T(""), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticBoxSizer84->Add(textHelpFile, 1, wxALIGN_TOP|wxLEFT|wxRIGHT|wxBOTTOM, 5);

    btnHelpFilePath = new wxButton( objPanelCompiler, ID_btnHelpFilePath, _("..."), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticBoxSizer84->Add(btnHelpFilePath, 0, wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxBOTTOM, 5);

    objNoteBook->AddPage(objPanelCompiler, m_Lang[242]);

    itemBoxSizer2->Add(objNoteBook, 1, wxGROW|wxALL, 5);

    wxStdDialogButtonSizer* itemStdDialogButtonSizer87 = new wxStdDialogButtonSizer;

    itemBoxSizer2->Add(itemStdDialogButtonSizer87, 0, wxALIGN_RIGHT|wxLEFT|wxRIGHT|wxBOTTOM, 5);
    wxButton* itemButton88 = new wxButton( itemDialog1, wxID_OK, m_Lang[2], wxDefaultPosition, wxDefaultSize, 0 );
    itemStdDialogButtonSizer87->AddButton(itemButton88);

    wxButton* itemButton89 = new wxButton( itemDialog1, wxID_CANCEL, m_Lang[3], wxDefaultPosition, wxDefaultSize, 0 );
    itemStdDialogButtonSizer87->AddButton(itemButton89);

    itemStdDialogButtonSizer87->Realize();

////@end ConfigDialog content construction
}

/*!
 * Should we show tooltips?
 */

bool ConfigDialog::ShowToolTips()
{
    return false;
}

/*!
 * Get bitmap resources
 */

wxBitmap ConfigDialog::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin ConfigDialog bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end ConfigDialog bitmap retrieval
}


wxIcon ConfigDialog::GetIconResource( const wxString& name )
{
    wxUnusedVar(name);
    return wxNullIcon;
}


//------------------------------------------------------------------------------

void ConfigDialog::OnCompilerPath( wxCommandEvent& event ) {
    wxFileDialog dlg (this,
        _T(m_Parent->Lang[155]), //Open file
        _T(""),
    #ifdef __WXMSW__
        _T("fbc.exe"),
        _T(m_Parent->Lang[156]), //"All programs (*.exe)|*.exe"
    #else
        _T("fbc"),
        _T(""),
    #endif
    wxFILE_MUST_EXIST );
    if (dlg.ShowModal() != wxID_OK) return;
    
    textCompilerPath->SetValue( dlg.GetPath() );
}



void ConfigDialog::OnKeywordsGroup( wxCommandEvent& event ) {
    int selection = chKeywordGroup->GetSelection();
    if( m_KeywordsGroupOld > -1 ) {
        m_Keywords[m_KeywordsGroupOld] = textKeyWords->GetValue();
        textKeyWords->Clear();
        textKeyWords->AppendText( m_Keywords[selection] );
    }
    m_KeywordsGroupOld = selection;
}




void ConfigDialog::OnSaveTheme( wxCommandEvent& event ) {
    
    StoreTypeSelection( m_ThemeTypeOld );
    if (chTheme->GetSelection()!=0)
        m_Parent->SaveThemeFile(m_Style, chTheme->GetStringSelection());
    else {
        wxTextEntryDialog dialog(this, _T(m_Lang[157]), //"Enter theme name:"
                                        _T(m_Lang[158]), //"Paremeters..."
                                        "", wxOK | wxCANCEL);
        if (dialog.ShowModal() != wxID_OK) return;
        
        wxString fn = dialog.GetValue();
        fn = fn.Lower();
        fn = fn.Trim(true);
        fn = fn.Trim(false);

        wxFileSystem File;
        if (File.FindFirst( m_Parent->EditorPath+"IDE/"+fn+".fbt" )!="" ) {
            //"Theme \""+ fn +"\" already exists!\nOverwrite it?"
            if (wxMessageBox (m_Lang[159]+ fn + m_Lang[160], m_Lang[161], wxICON_QUESTION | wxYES_NO )!=wxOK) 
                return;
        }
        else {
            wxTextFile temp(m_Parent->EditorPath+"IDE/"+fn+".fbt");
            temp.Create();
            temp.Write();
            temp.Close();
        }
            
        m_Parent->SaveThemeFile(m_Style, fn);
        m_Parent->ThemeFile = fn;
        chTheme->Append(fn);
        chTheme->SetSelection(chTheme->GetCount()-1);
    }
    return;
}




void ConfigDialog::OnSelectTheme( wxCommandEvent& event ) {
    if ( chTheme->GetSelection()!=0 ) {
        m_Style = m_Parent->LoadThemeFile( chTheme->GetStringSelection() );
    }
    SetTypeSelection( m_ThemeTypeOld );
    return;
}




void ConfigDialog::OnBtnForeground( wxCommandEvent& event ) {
    wxColour clrt;
    m_Parent->colr.SetChooseFull(false);

    wxColourDialog dlg( this, &( m_Parent->colr ) );
    if ( dlg.ShowModal() != wxID_OK ) return;

    m_Parent->colr = dlg.GetColourData();
    clrt = m_Parent->colr.GetColour();

    btnForeground->SetBackgroundColour( clrt );
    m_fg = ( clrt.Red() << 16 ) | ( clrt.Green() << 8 ) | clrt.Blue();
    
    return;
}




void ConfigDialog::OnBtnBackground( wxCommandEvent& event ) {
    wxColour clrt;
    m_Parent->colr.SetChooseFull(false);

    wxColourDialog dlg( this, &( m_Parent->colr ) );
    if ( dlg.ShowModal() != wxID_OK ) return;

    m_Parent->colr = dlg.GetColourData();
    clrt = m_Parent->colr.GetColour();

    btnBackground->SetBackgroundColour( clrt );
    m_bg = ( clrt.Red() << 16 ) | ( clrt.Green() << 8 ) | clrt.Blue();
    
    return;
}




void ConfigDialog::OnThemeSelectType( wxCommandEvent& event ) {
    if ( m_ThemeTypeOld > 0 )
        StoreTypeSelection( m_ThemeTypeOld );
    m_ThemeTypeOld = listThemeType->GetSelection()+1;
    SetTypeSelection( m_ThemeTypeOld );
}




void ConfigDialog::SetTypeSelection( int intSel ) {
    bool ModFG = false, ModBG = false, ModFont = false, ModStyle = false, ModSize = false;
    bool SetBold = false, SetItalic = false, SetUnderlined = false;
    int SetSize = 0;
    wxString SetFont = ""; 
    int selection = intSel;

    
    if ( selection < 13 ) {
        ModFG = true; ModBG = true;
        ModFont = true; ModStyle = true; ModSize = true;
        SetBold = (m_Style.Info[selection].fontstyle & mySTC_STYLE_BOLD)>0;
        SetItalic = (m_Style.Info[selection].fontstyle & mySTC_STYLE_ITALIC)>0;
        SetUnderlined = (m_Style.Info[selection].fontstyle & mySTC_STYLE_UNDERL)>0;    
        SetSize = m_Style.Info[selection].fontsize;
        SetFont = m_Style.Info[selection].fontname;
        m_fg = m_Style.Info[selection].foreground;
        m_bg = m_Style.Info[selection].background;
    }
    else if (selection==13) {
        ModFG = true;
        m_fg = m_Style.CaretColour;
    }
    else if (selection==14) {
        ModFG = true; ModBG = true;
        m_bg = m_Style.LineNumberBgColour;
        m_fg = m_Style.LineNumberFgColour;
    }
    else if (selection==15) {
        ModFG = true; ModBG = true;
        m_bg = m_Style.SelectBgColour;
        m_fg = m_Style.SelectFgColour;
    }
    else if (selection==16) {
        ModStyle = true;
        ModFG = true;
        ModBG = true;
        SetBold = (m_Style.BraceFontStyle & mySTC_STYLE_BOLD)>0;
        SetItalic = (m_Style.BraceFontStyle & mySTC_STYLE_ITALIC)>0;
        SetUnderlined = (m_Style.BraceFontStyle & mySTC_STYLE_UNDERL)>0;
        m_fg = m_Style.BraceFgColour;
        m_bg = m_Style.BraceBgColour;
    }
    else if (selection==17) {
        ModStyle = true;
        ModFG = true;
        ModBG = true;
        SetBold = (m_Style.BadBraceFontStyle & mySTC_STYLE_BOLD)>0;
        SetItalic = (m_Style.BadBraceFontStyle & mySTC_STYLE_ITALIC)>0;
        SetUnderlined = (m_Style.BadBraceFontStyle & mySTC_STYLE_UNDERL)>0;
        m_bg = m_Style.BadBraceBgColour;
        m_fg = m_Style.BadBraceFgColour;
    }
    else if (selection==18) {
        ModBG = true, ModFG = true, ModSize = true;
        m_bg = m_Style.DefaultBgColour;
        m_fg = m_Style.DefaultFgColour;
        SetSize = m_Style.DefaultFontSize;
    }


    if (ModStyle) {
        chkBold->Enable();
        chkItalic->Enable();
        chkUnderLined->Enable();
        
        chkBold->SetValue(SetBold);
        chkItalic->SetValue(SetItalic);
        chkUnderLined->SetValue(SetUnderlined);
    }
    else {
        chkBold->Disable();
        chkItalic->Disable();
        chkUnderLined->Disable();
    }
    

    if (ModSize) {
        spinFontSize->Enable();
        spinFontSize->SetValue(SetSize);
    }
    else spinFontSize->Disable();
    

    if (ModFont) {
        chFont->Enable();
        if( chFont->FindString( SetFont ) == wxNOT_FOUND )
            chFont->SetStringSelection( "Courier New" );
        else
            chFont->SetStringSelection( SetFont );
        
    }
    else chFont->Disable();
    
    if (ModFG) {
        btnForeground->Enable();
        btnForeground->SetBackgroundColour(GetClr(m_fg));
    }
    else {
        btnForeground->Disable();
        btnForeground->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_3DFACE));
    }
    
    if (ModBG) {
        btnBackground->Enable();
        btnBackground->SetBackgroundColour(GetClr(m_bg));
    }
    else {
        btnBackground->Disable();
        btnBackground->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_3DFACE));
    }
}




void ConfigDialog::StoreTypeSelection( int intSel ) {
    int selection = intSel;
    if (selection < 13) {
        m_Style.Info[selection].fontstyle = 0;
        if (chkBold->GetValue())
                m_Style.Info[selection].fontstyle |= mySTC_STYLE_BOLD;
        if (chkItalic->GetValue())
                m_Style.Info[selection].fontstyle |= mySTC_STYLE_ITALIC;
        if (chkUnderLined->GetValue())
                m_Style.Info[selection].fontstyle |= mySTC_STYLE_UNDERL;

        m_Style.Info[selection].fontsize = spinFontSize->GetValue();
        m_Style.Info[selection].fontname = chFont->GetStringSelection();
        m_Style.Info[selection].foreground = m_fg;
        m_Style.Info[selection].background = m_bg;
    }
    else if (selection==13) {
        m_Style.CaretColour = m_fg;
    }
    else if (selection==14) {
        m_Style.LineNumberBgColour = m_bg;
        m_Style.LineNumberFgColour = m_fg;
    }
    else if (selection==15) {
        m_Style.SelectBgColour = m_bg;
        m_Style.SelectFgColour = m_fg;
    }
    else if (selection==16) {
        
        m_Style.BraceFontStyle = 0;
        if (chkBold->GetValue())
                m_Style.BraceFontStyle |= mySTC_STYLE_BOLD;
        if (chkItalic->GetValue())
                m_Style.BraceFontStyle |= mySTC_STYLE_ITALIC;
        if (chkUnderLined->GetValue())
                m_Style.BraceFontStyle |= mySTC_STYLE_UNDERL;
        m_Style.BraceFgColour = m_fg;
        m_Style.BraceBgColour = m_bg;
    }
    else if (selection==17) {
        m_Style.BadBraceFontStyle = 0;
        if (chkBold->GetValue())
                m_Style.BadBraceFontStyle |= mySTC_STYLE_BOLD;
        if (chkItalic->GetValue())
                m_Style.BadBraceFontStyle |= mySTC_STYLE_ITALIC;
        if (chkUnderLined->GetValue())
                m_Style.BadBraceFontStyle |= mySTC_STYLE_UNDERL;
        m_Style.BadBraceBgColour = m_bg;
        m_Style.BadBraceFgColour = m_fg;
    }
    else if (selection==18) {
        m_Style.DefaultBgColour = m_bg;
        m_Style.DefaultFgColour = m_fg;
        m_Style.DefaultFontSize = spinFontSize->GetValue();
    }
}




/**
 * If dialog OK button was clicked. we need to retreave data
 * and save it into parent. this is ugly, but this is 0.4...
 */
void ConfigDialog::OnOkClick( wxCommandEvent& event ) {
    
    // Get general data
    m_Prefs.AutoIndent = chkAutoIndent->GetValue( );
    m_Prefs.IndentGuide = chkIndentGuides->GetValue( );
    m_Prefs.whiteSpace = chkWhiteSpaces->GetValue( );
    m_Prefs.DisplayEOL = chkLineEnd->GetValue( );
    m_Prefs.BraceHighlight = chkMatchingBraces->GetValue( );
    m_Prefs.SyntaxHighlight = chkSyntaxHighlight->GetValue( );
    m_Prefs.LineNumber = chkLineNumbers->GetValue( );
    m_Prefs.EdgeColumn = chkRightMargin->GetValue( );
    m_Prefs.FolderMargin = chkFoldMargin->GetValue( );
    m_Prefs.SplashScreen = chkSplashScreen->GetValue( );
    m_Prefs.EdgeColumn = spinRightMargin->GetValue( );
    m_Prefs.TabSize = spinTabSize->GetValue( );
    m_Prefs.Language = chLanguage->GetStringSelection( );
    
    // Get data from keywords tab
    m_Parent->Keyword[1] = m_Keywords[0];
    m_Parent->Keyword[2] = m_Keywords[1];
    m_Parent->Keyword[3] = m_Keywords[2];
    m_Parent->Keyword[4] = m_Keywords[3];
    
    // Get data from compiler tab
    if( m_Prefs.HelpFile != textHelpFile->GetValue() ) {
        m_Prefs.HelpFile = textHelpFile->GetValue().Trim( true ).Trim( false );
        #ifdef __WXMSW__
            wxString dir;
            wxFileName helpFile( m_Prefs.HelpFile );
            if( helpFile.IsRelative() && m_Prefs.HelpFile != "" )
                dir = m_Parent->EditorPath + "IDE/" + m_Prefs.HelpFile;
            else
                dir = m_Prefs.HelpFile;
            if( ::wxFileExists( dir ) ) {
                m_Prefs.UseHelp = true;
                m_Parent->help.Initialize( dir );
            } else {
                m_Prefs.UseHelp = false;
            }
            
        #endif
    }
    
    m_Parent->CompilerPath = textCompilerPath->GetValue();
    m_Parent->CMDPrototype = textCompilerCommand->GetValue();
    m_Parent->RunPrototype = textRunCommand->GetValue();
    
    if ( chTheme->GetSelection()!=0 )
        m_Parent->ThemeFile = chTheme->GetStringSelection();
    
    StoreTypeSelection( m_ThemeTypeOld );
    
    // Set general data
    m_Parent->Style = m_Style;
    m_Parent->Prefs = m_Prefs;
    
    this->EndModal( wxID_OK );
}




/**
 * If dialog close button or cancel was clicked then this method is called.
 * Just end modal here and leave. no changes are to be saved.
 */
void ConfigDialog::OnCancelClick( wxCommandEvent& event ) {
    this->EndModal( wxID_CANCEL );
}




void ConfigDialog::OnHelpPath( wxCommandEvent& event ) {
    wxFileDialog dlg (this,
        _T(m_Lang[155]), //Open file
        _T(""),
        _T(""),
        _T( m_Lang[243] + "|*.chm"),
    wxFILE_MUST_EXIST );
    if (dlg.ShowModal() != wxID_OK) return;
    
    textHelpFile->SetValue(dlg.GetPath());
}



//==============================================================================


/**
 *  Load Generak tab
 */
void ConfigDialog::LoadGeneral() {
    chkAutoIndent->SetValue( m_Prefs.AutoIndent );
    chkIndentGuides->SetValue( m_Prefs.IndentGuide );
    chkWhiteSpaces->SetValue( m_Prefs.whiteSpace );
    chkLineEnd->SetValue( m_Prefs.DisplayEOL );
    chkMatchingBraces->SetValue( m_Prefs.BraceHighlight );
    
    chkSyntaxHighlight->SetValue( m_Prefs.SyntaxHighlight );
    chkLineNumbers->SetValue( m_Prefs.LineNumber );
    chkRightMargin->SetValue( m_Prefs.EdgeColumn );
    chkFoldMargin->SetValue( m_Prefs.FolderMargin );
    chkSplashScreen->SetValue( m_Prefs.SplashScreen );
    
    spinRightMargin->SetValue( m_Prefs.EdgeColumn );
    spinTabSize->SetValue( m_Prefs.TabSize );
    
    
    wxArrayString arrLangs;
    wxFileSystem LangFiles;
    wxString fileQuery = LangFiles.FindFirst( m_Parent->EditorPath+"IDE/lang/*.fbl" );
    wxFileName objLangFile;
    
    int counter=0, selector=0;
    while ( fileQuery != "" ) {
        objLangFile.Assign(fileQuery, wxPATH_NATIVE);
        fileQuery = objLangFile.GetName();
        fileQuery = fileQuery.Lower();
        if ( fileQuery == m_Prefs.Language ) selector = counter;
        arrLangs.Add(fileQuery);
        fileQuery = LangFiles.FindNext();
        counter++;
    }
    chLanguage->Append( arrLangs );
    chLanguage->SetSelection( selector );
}




/**
 *  Load themes tab
 */
void ConfigDialog::LoadThemes() {
    
    //Theme colors types:
    wxArrayString arrThemeType;
    arrThemeType.Add(m_Lang[118]);        //Comments
    arrThemeType.Add(m_Lang[119]);        //Numbers
    arrThemeType.Add(m_Lang[120]);        //Keywords 1
    arrThemeType.Add(m_Lang[121]);        //String Closed
    arrThemeType.Add(m_Lang[122]);        //Preprocessor
    arrThemeType.Add(m_Lang[123]);        //Operator
    arrThemeType.Add(m_Lang[124]);        //Identifier
    arrThemeType.Add(m_Lang[125]);        //Date (doesn't work)
    arrThemeType.Add(m_Lang[126]);        //String Open
    arrThemeType.Add(m_Lang[127]);        //Keywords 2
    arrThemeType.Add(m_Lang[128]);        //Keywords 3
    arrThemeType.Add(m_Lang[129]);        //Keywords 4
    arrThemeType.Add(m_Lang[130]);        //Caret
    arrThemeType.Add(m_Lang[131]);        //Line numbers
    arrThemeType.Add(m_Lang[132]);        //Text select
    arrThemeType.Add(m_Lang[133]);        //Brace match
    arrThemeType.Add(m_Lang[134]);        //Brace mismatch
    arrThemeType.Add(m_Lang[135]);        //Editor
    listThemeType->Append( arrThemeType );
    m_ThemeTypeOld = 1;
    listThemeType->SetSelection( 0 );
    
    
    // Get themes
    wxArrayString arrThemes;
    arrThemes.Add( m_Lang[141] ); //"Create new theme"
    wxFileSystem ThemeFiles;
    wxString fileQuery = ThemeFiles.FindFirst( m_Parent->EditorPath+"IDE/*.fbt" );
    wxFileName objThemeFile;
    
    int counter=0, selector=0;
    while ( fileQuery != "" ) {
        counter++;
        objThemeFile.Assign(fileQuery, wxPATH_NATIVE);
        fileQuery = objThemeFile.GetName();
        fileQuery = fileQuery.Lower();
        if ( fileQuery == m_Parent->ThemeFile ) selector = counter;
        arrThemes.Add(fileQuery);
        fileQuery = ThemeFiles.FindNext();
    }
    chTheme->Append( arrThemes );
    m_ThemeOld = 0;
    chTheme->SetSelection( selector );
    
    
    // Fonts
    wxFontEnumerator objFontEnum;
    objFontEnum.EnumerateFacenames(  );
    chFont->Append( *objFontEnum.GetFacenames() );
    
    SetTypeSelection( 1 );
    
}




/**
 *  Load keywords tab
 */
void ConfigDialog::LoadKeywords() {
    
    m_Keywords.Add( m_Parent->Keyword[1] );
    m_Keywords.Add( m_Parent->Keyword[2] );
    m_Keywords.Add( m_Parent->Keyword[3] );
    m_Keywords.Add( m_Parent->Keyword[4] );
    
    chKeywordGroup->Append(m_Lang[151]);//"Group 1"
    chKeywordGroup->Append(m_Lang[152]);//"Group 2"
    chKeywordGroup->Append(m_Lang[153]);//"Group 3"
    chKeywordGroup->Append(m_Lang[154]);//"Group 4"
    textKeyWords->AppendText( m_Keywords[0] );
    m_KeywordsGroupOld = 0;
    chKeywordGroup->SetSelection( 0 );
}




/**
 *  Load compiler/freebasic tab
 */
void ConfigDialog::LoadCompiler() {
    textHelpFile->SetValue( m_Prefs.HelpFile );
    textCompilerPath->SetValue( m_Parent->CompilerPath );
    textCompilerCommand->SetValue( m_Parent->CMDPrototype );
    textRunCommand->SetValue( m_Parent->RunPrototype );
}





/*
#include "inc/main.h"
#include "inc/configdiag.h"
#include <wx/fontenum.h>

BEGIN_EVENT_TABLE( ConfigDialog, wxDialog)
    EVT_BUTTON(CDID_OK,             ConfigDialog::Button_OK)
    EVT_BUTTON(CDID_Cancel,         ConfigDialog::Button_Cancel)
    EVT_BUTTON(CDID_GetCompPath,    ConfigDialog::Button_GetCompPath)
    EVT_BUTTON(CDID_Background,     ConfigDialog::Button_Background)
    EVT_BUTTON(CDID_Foreground,     ConfigDialog::Button_Foreground)
    EVT_BUTTON(CDID_SaveTheme,      ConfigDialog::Button_SaveTheme)
    
    EVT_LISTBOX(-1,                 ConfigDialog::ListBox_Select)
    EVT_COMBOBOX(CDID_ThemeSelector,ConfigDialog::ThemeSelector)
    EVT_CHOICE(CDID_KeywordSelector,ConfigDialog::KeywordSelect)
END_EVENT_TABLE()

ConfigDialog::ConfigDialog( wxWindow* parent,
                            wxWindowID id,
                            const wxString& title,
                            long style,
                            const wxString& name )
{
    
    Parent = ( MyFrame * ) parent;
    ModKw=false;
    ModTheme=false;
    Style = Parent->Style;
    Oldselection = 0;

    Create(parent,id,title,wxDefaultPosition, wxSize(405, 330), style, name);
    
    CD_Notebook=new wxNotebook(this,-1,wxPoint(5,4),wxSize(390,265));
    //CD_Notebook->SetTitle(wxT(_(Lang[98])));
    
    CD_Settings=new wxPanel(CD_Notebook,-1,wxPoint(4,22),wxSize(382,234));
    CD_Notebook->AddPage((wxNotebookPage *)CD_Settings, _(Parent->Lang[99]) ,false);
    
    CD_Theme=new wxPanel(CD_Notebook,-1,wxPoint(4,22),wxSize(382,234));
    CD_Notebook->AddPage((wxNotebookPage *)CD_Theme,_(Parent->Lang[100]),false);
    
    CD_Keywords=new wxPanel(CD_Notebook,-1,wxPoint(4,22),wxSize(382,234));
    CD_Notebook->AddPage((wxNotebookPage *)CD_Keywords,_(Parent->Lang[101]),false);
    
    CD_Compiler=new wxPanel(CD_Notebook,-1,wxPoint(4,22),wxSize(382,234));
    CD_Notebook->AddPage((wxNotebookPage *)CD_Compiler,_(Parent->Lang[102]),false);

    
    //--------------------------------------------------------------------------
    CB_AutoIndent=new wxCheckBox(CD_Settings,-1,wxT(""),wxPoint(10,30),wxSize(165,13));
    CB_AutoIndent->SetTitle(wxT(Parent->Lang[112]));
    CB_AutoIndent->SetValue(Parent->Prefs.AutoIndent);
    
    CB_IndentGuides=new wxCheckBox(CD_Settings,-1,wxT(""),wxPoint(10,50),wxSize(165,13));
    CB_IndentGuides->SetTitle(wxT(Parent->Lang[110]));
    CB_IndentGuides->SetValue(Parent->Prefs.IndentGuide);
    
    CB_WhiteSpaces=new wxCheckBox(CD_Settings,-1,wxT(""),wxPoint(10,69),wxSize(165,13));
    CB_WhiteSpaces->SetTitle(wxT(Parent->Lang[109]));
    CB_WhiteSpaces->SetValue(Parent->Prefs.whiteSpace);
    
    CB_HiLightBraces=new wxCheckBox(CD_Settings,-1,wxT(""),wxPoint(10,90),wxSize(165,13));
    CB_HiLightBraces->SetTitle(wxT(Parent->Lang[105]));
    CB_HiLightBraces->SetValue(Parent->Prefs.BraceHighlight);

    CB_LongLine=new wxCheckBox(CD_Settings,-1,wxT(""),wxPoint(10,110),wxSize(165,13));
    CB_LongLine->SetTitle(wxT(Parent->Lang[107]));
    CB_LongLine->SetValue(Parent->Prefs.LongLine);

    CB_SplashScreen=new wxCheckBox(CD_Settings,-1,wxT(""),wxPoint(10,130),wxSize(165,13));
    CB_SplashScreen->SetTitle(wxT(Parent->Lang[232]));
    CB_SplashScreen->SetValue(Parent->Prefs.SplashScreen);
        
    //is used for linenumbers
    CB_CurrentLine=new wxCheckBox(CD_Settings,-1,wxT(""),wxPoint(180,30),wxSize(165,13));
    CB_CurrentLine->SetTitle(wxT(Parent->Lang[103]));
    CB_CurrentLine->SetValue(Parent->Prefs.LineNumber);

    CB_SyntaxHiLight=new wxCheckBox(CD_Settings,-1,wxT(""),wxPoint(180,50),wxSize(165,13));
    CB_SyntaxHiLight->SetTitle(wxT(Parent->Lang[106]));
    CB_SyntaxHiLight->SetValue(Parent->Prefs.SyntaxHighlight);
    
   
    CB_LineEndings=new wxCheckBox(CD_Settings,-1,wxT(""),wxPoint(180,70),wxSize(165,13));
    CB_LineEndings->SetTitle(wxT(Parent->Lang[108]));
    CB_LineEndings->SetValue(Parent->Prefs.DisplayEOL);
    
    CB_FoldMargin=new wxCheckBox(CD_Settings,-1,wxT(""),wxPoint(180,90),wxSize(165,13));
    CB_FoldMargin->SetTitle(wxT(Parent->Lang[111]));
    CB_FoldMargin->SetValue(Parent->Prefs.FolderMargin);


    st20=new wxStaticText(CD_Settings,-1,wxT(""),wxPoint(10,5),wxSize(90,13),wxST_NO_AUTORESIZE);
    st20->SetTitle(wxT(Parent->Lang[104]));

    
    
    TB_Width=new wxSpinCtrl(CD_Settings,-1,wxT(""),wxPoint(275,110),wxSize(60,15));
    TB_Width->SetRange(1, 1000);
    TB_Width->SetValue(Parent->Prefs.EdgeColumn);
    
    lno21=new wxStaticLine(CD_Settings,-1,wxPoint(10,20),wxSize(360,2));
    
    new wxStaticLine(CD_Settings,-1,wxPoint(10,165),wxSize(360,2));
    new wxStaticText(CD_Settings,-1,wxT(Parent->Lang[201]),wxPoint(10,150),wxSize(360,13),wxST_NO_AUTORESIZE);
    new wxStaticText(CD_Settings,-1,wxT(Parent->Lang[202]),wxPoint(10,215),wxSize(360,13),wxST_NO_AUTORESIZE);
    new wxStaticText(CD_Settings,-1,wxT(Parent->Lang[203]),wxPoint(10,180),wxSize(150,13),wxST_NO_AUTORESIZE);

    
    wxArrayString Langs;
    wxFileSystem LangFiles;
    wxString Fn = LangFiles.FindFirst(Parent->EditorPath+"ide\\lang\\*.fbl");
    wxFileName l;
    
    int counter=0, selector=0;
    while (Fn!="") {
        counter++;
        l.Assign(Fn, wxPATH_NATIVE);
        Fn = l.GetName();
        Fn = Fn.Lower();
        if (Fn==Parent->Prefs.Language) selector = counter-1;
        Langs.Add(Fn);
        Fn = LangFiles.FindNext();
    }
    CB_Langs=new wxComboBox(CD_Settings,-1,wxT(""),wxPoint(180,175),wxSize(190,21),Langs, wxCB_READONLY | wxCB_DROPDOWN );
    CB_Langs->Select(selector);
    
    // compile page
    st33=new wxStaticText(CD_Compiler,-1,wxT(""),wxPoint(10,5),wxSize(105,13),wxST_NO_AUTORESIZE);
    st33->SetLabel(wxT(Parent->Lang[113]));
    lno31=new wxStaticLine(CD_Compiler,-1,wxPoint(10,20),wxSize(360,2));

    st37=new wxStaticText(CD_Compiler,-1,wxT(""),wxPoint(10,30),wxSize(70,13),wxST_NO_AUTORESIZE);
    st37->SetLabel(wxT(Parent->Lang[114]));
    
    TB_CompilerPath=new wxTextCtrl(CD_Compiler,-1,wxT(""),wxPoint(85,28),wxSize(250,21));
    TB_CompilerPath->SetValue(Parent->CompilerPath);

    But_GetCompilerPath=new wxButton(CD_Compiler, CDID_GetCompPath,wxT(""),wxPoint(340,30),wxSize(30,20));
    But_GetCompilerPath->SetLabel(wxT("..."));
    
    //Compiler command
    st41=new wxStaticText(CD_Compiler,-1,wxT(""),wxPoint(10,60),wxSize(70, 13),wxST_NO_AUTORESIZE);
    st41->SetLabel(wxT(Parent->Lang[115]));
    
    CompilerCommand=new wxTextCtrl(CD_Compiler,-1,wxT(""),wxPoint(85,58),wxSize(250,21));
    CompilerCommand->SetValue(Parent->CMDPrototype);
    
//////////////////////////////////////////////////

    
    st34=new wxStaticText(CD_Settings,-1,wxT(""),wxPoint(180,110),wxSize(95,13),wxST_NO_AUTORESIZE);
    st34->SetLabel(wxT(Parent->Lang[116]));
    
    //Compiler path
    
    //Tab Size
    st43=new wxStaticText(CD_Settings,-1,wxT(""),wxPoint(180,130),wxSize(95,13),wxST_NO_AUTORESIZE);
    st43->SetLabel(wxT(Parent->Lang[117]));

    spc44=new wxSpinCtrl(CD_Settings,-1,wxT(""),wxPoint(275,130),wxSize(60,15));
    spc44->SetValue(Parent->Prefs.TabSize);


    //Theme colors types:
    wxArrayString Choices;
    Choices.Add(Parent->Lang[118]);        //Comments
    Choices.Add(Parent->Lang[119]);        //Numbers
    Choices.Add(Parent->Lang[120]);        //Keywords 1
    Choices.Add(Parent->Lang[121]);        //String Closed
    Choices.Add(Parent->Lang[122]);        //Preprocessor
    Choices.Add(Parent->Lang[123]);        //Operator
    Choices.Add(Parent->Lang[124]);        //Identifier
    Choices.Add(Parent->Lang[125]);        //Date (doesn't work)
    Choices.Add(Parent->Lang[126]);        //String Open
    Choices.Add(Parent->Lang[127]);        //Keywords 2
    Choices.Add(Parent->Lang[128]);        //Keywords 3
    Choices.Add(Parent->Lang[129]);        //Keywords 4

    Choices.Add(Parent->Lang[130]);        //Caret
    Choices.Add(Parent->Lang[131]);        //Line numbers
    Choices.Add(Parent->Lang[132]);        //Text select
    Choices.Add(Parent->Lang[133]);        //Brace match
    Choices.Add(Parent->Lang[134]);        //Brace mismatch
    Choices.Add(Parent->Lang[135]);        //Editor

    LB_Types=new wxListBox(CD_Theme,-1,wxPoint(10,45),wxSize(120,176), Choices);
    LB_Types->SetSelection(0);
    
    But_Foreground=new wxButton(CD_Theme, CDID_Foreground, wxT(""),wxPoint(135,95),wxSize(145,21));
    But_Foreground->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_3DFACE));
    
    But_Background=new wxButton(CD_Theme, CDID_Background, wxT(""),wxPoint(135,140),wxSize(145,21));
    But_Background->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_3DFACE));

    
    CB_Bold=new wxCheckBox(CD_Theme,-1,wxT(""),wxPoint(300,95),wxSize(70,13));
    CB_Bold->SetTitle(wxT(Parent->Lang[136])); //"Bold"
    
    CB_Italic=new wxCheckBox(CD_Theme,-1,wxT(""),wxPoint(300,115),wxSize(70,13));
    CB_Italic->SetTitle(wxT(Parent->Lang[137])); //"Italic"
    
    CB_Underlined=new wxCheckBox(CD_Theme,-1,wxT(""),wxPoint(300,135),wxSize(70,13));
    CB_Underlined->SetTitle(wxT(Parent->Lang[138])); //"Underlined"
    
    But_SaveTheme=new wxButton(CD_Theme, CDID_SaveTheme,wxT(""),wxPoint(285,45),wxSize(85,20));
    But_SaveTheme->SetLabel(wxT(Parent->Lang[139])); //"Save theme"
    
    st58=new wxStaticText(CD_Theme,-1,wxT(""),wxPoint(135,30),wxSize(100,13),wxST_NO_AUTORESIZE);
    st58->SetLabel(wxT(Parent->Lang[140])); //"Theme"

    wxArrayString Themes;
    Themes.Add(Parent->Lang[141]); //"Create new theme"
//    Themes.Add(w.GetFullName());

    wxFileSystem ThemeFiles;
    Fn = ThemeFiles.FindFirst(Parent->EditorPath+"ide\\*.fbt");
    wxFileName w;
    
    counter=0; selector=0;
    while (Fn!="") {
        counter++;
        w.Assign(Fn, wxPATH_NATIVE);
        Fn = w.GetName();
        Fn = Fn.Lower();
        if (Fn==Parent->ThemeFile) selector = counter;
        Themes.Add(Fn);
        Fn = ThemeFiles.FindNext();
    }
        
    CB_Themes=new wxComboBox(CD_Theme, CDID_ThemeSelector,wxT(""),wxPoint(135,45),wxSize(145,21),Themes, wxCB_READONLY | wxCB_DROPDOWN );
    CB_Themes->Select(selector);
    
    st59=new wxStaticText(CD_Theme,-1,wxT(""),wxPoint(10,5),wxSize(200,13),wxST_NO_AUTORESIZE);
    st59->SetLabel(wxT(Parent->Lang[142])); //"Colors"
    
    lno60=new wxStaticLine(CD_Theme,-1,wxPoint(10,20),wxSize(360,2));
    
    st61=new wxStaticText(CD_Theme,-1,wxT(""),wxPoint(10,30),wxSize(100,13),wxST_NO_AUTORESIZE);
    st61->SetLabel(wxT(Parent->Lang[143])); //"Type"
    
    st62=new wxStaticText(CD_Theme,-1,wxT(""),wxPoint(135,80),wxSize(100,13),wxST_NO_AUTORESIZE);
    st62->SetLabel(wxT(Parent->Lang[144])); //"Foreground"
    
    st63=new wxStaticText(CD_Theme,-1,wxT(""),wxPoint(135,125),wxSize(100,13),wxST_NO_AUTORESIZE);
    st63->SetLabel(wxT(Parent->Lang[145])); //"Background"
    
    st64=new wxStaticText(CD_Theme,-1,wxT(""),wxPoint(300,80),wxSize(70,13),wxST_NO_AUTORESIZE);
    st64->SetLabel(wxT(Parent->Lang[146])); //"Fontstyle"
    
    lno65=new wxStaticLine(CD_Theme,-1,wxPoint(135,75),wxSize(235,2));
    
    lnv66=new wxStaticLine(CD_Theme,-1,wxPoint(290,80),wxSize(2,120),wxLI_VERTICAL);
    
    st67=new wxStaticText(CD_Theme,-1,wxT(""),wxPoint(135,165),wxSize(100,13),wxST_NO_AUTORESIZE);
    st67->SetLabel(wxT(Parent->Lang[147])); //"Font\r\n"
    
    
    wxArrayString Fonts;
    wxFontEnumerator fn;
    fn.EnumerateFacenames(  );
    Fonts = *fn.GetFacenames();
    
    cmb69=new wxComboBox(CD_Theme,-1, wxT("Courier"),wxPoint(135,180),wxSize(145,21),Fonts, wxCB_READONLY | wxCB_DROPDOWN | wxCB_SORT );
    cmb69->Select(1);
    
    st70=new wxStaticText(CD_Theme,-1,wxT(""),wxPoint( 300,165 ),wxSize(70,13),wxST_NO_AUTORESIZE);
    st70->SetLabel(wxT(Parent->Lang[148])); //"Fontsize\r\n"
    
    //
    spc71=new wxSpinCtrl(CD_Theme,-1,wxT(""),wxPoint(300,180),wxSize(70,20));
    

    lno74=new wxStaticLine(CD_Keywords,-1,wxPoint(10,20),wxSize(360,2));
    
    st75=new wxStaticText(CD_Keywords,-1,wxT(""),wxPoint(10,5),wxSize(100,13),wxST_NO_AUTORESIZE);
    st75->SetLabel(wxT(Parent->Lang[149])); //"Keywords\r\n"
    
    st77=new wxStaticText(CD_Keywords,-1,wxT(""),wxPoint(10,30),wxSize(200,13),wxST_NO_AUTORESIZE);
    st77->SetLabel(wxT(Parent->Lang[150]));//"Select keyword group"
    
    CB_KeywordGroup=new wxChoice(CD_Keywords,CDID_KeywordSelector,wxPoint(10,45),wxSize(150,21),0);
    CB_KeywordGroup->Append(Parent->Lang[151]);//"Group 1"
    CB_KeywordGroup->Append(Parent->Lang[152]);//"Group 2"
    CB_KeywordGroup->Append(Parent->Lang[153]);//"Group 3"
    CB_KeywordGroup->Append(Parent->Lang[154]);//"Group 4"
    CB_KeywordGroup->Select(0);
    OldKWSelect = 1;
    
    TA_Keywords=new wxTextCtrl(CD_Keywords, -1,wxT(""),wxPoint(10,70),wxSize(360,158),wxTE_WORDWRAP|wxTE_MULTILINE);
    TA_Keywords->AppendText(Parent->Keyword[1]);
    
    But_OK=new wxButton(this, CDID_OK,wxT(""),wxPoint(250,270),wxSize(70,25));
    But_OK->SetLabel(wxT(Parent->Lang[2])); //OK
    
    But_Cancel=new wxButton(this, CDID_Cancel, wxT(""),wxPoint(325,270),wxSize(70,25));
    But_Cancel->SetLabel(wxT(Parent->Lang[3])); //Cancel
    
    Refresh();
    wxCommandEvent test;
    ListBox_Select (test);
}


void ConfigDialog::Button_OK      (wxCommandEvent&  event) {
    
    int selection = LB_Types->GetSelection();
    Oldselection=selection;
    Oldselection++;
    if (Oldselection>0) SaveSettings();
//    if (CB_Themes->GetSelection()!=0)
//        Parent->SaveThemeFile(Style, CB_Themes->GetValue());
    
    Parent->Keyword[OldKWSelect]    = TA_Keywords->GetValue();
    Parent->SavekwFile( Parent->SyntaxFile );
    
    Parent->Prefs.LineNumber        = CB_CurrentLine->GetValue();
    Parent->Prefs.BraceHighlight    = CB_HiLightBraces->GetValue();
    Parent->Prefs.SyntaxHighlight   = CB_SyntaxHiLight->GetValue();
    Parent->Prefs.LongLine          = CB_LongLine->GetValue();
    Parent->Prefs.DisplayEOL        = CB_LineEndings->GetValue();
    Parent->Prefs.whiteSpace        = CB_WhiteSpaces->GetValue();
    Parent->Prefs.IndentGuide       = CB_IndentGuides->GetValue();
    Parent->Prefs.FolderMargin      = CB_FoldMargin->GetValue();
    Parent->Prefs.AutoIndent        = CB_AutoIndent->GetValue();
    
    Parent->Prefs.EdgeColumn        = TB_Width->GetValue();
    Parent->Prefs.TabSize           = spc44->GetValue();
    Parent->CompilerPath            = TB_CompilerPath->GetValue();
    Parent->CMDPrototype            = CompilerCommand->GetValue();
    Parent->Prefs.Language          = CB_Langs->GetValue();
    Parent->Prefs.SplashScreen      = CB_SplashScreen->GetValue();
    
    Parent->Style = Style;
    
    Close(true);
    return;
}


void ConfigDialog::Button_Cancel  (wxCommandEvent&  event){
    Close(true);
    return;
}


void ConfigDialog::Button_GetCompPath   (wxCommandEvent&  event) {

    wxFileDialog dlg (this,
        _T(Parent->Lang[155]), //Open file
        _T(""),
        _T("fbc.exe"),
        _T(Parent->Lang[156]), //"All programs (*.exe)|*.exe"
    wxFILE_MUST_EXIST );
    if (dlg.ShowModal() != wxID_OK) return;
    
    TB_CompilerPath->SetValue(dlg.GetPath());

    return;
}

void ConfigDialog::ListBox_Select (wxCommandEvent &event) {

    bool ModFG = false, ModBG = false, ModFont = false, ModStyle = false, ModSize = false;
    bool SetBold = false, SetItalic = false, SetUnderlined = false;
    int SetSize = 0;
    wxString SetFont = ""; 
    int selection = LB_Types->GetSelection();
    selection++;
    
    if (Oldselection==selection) return;
    if (Oldselection>0) SaveSettings();
    Oldselection=selection;
    
    if ( selection < 13 ) {
        ModFG = true; ModBG = true;
        ModFont = true; ModStyle = true; ModSize = true;
        SetBold = (Style.Info[selection].fontstyle & mySTC_STYLE_BOLD)>0;
        SetItalic = (Style.Info[selection].fontstyle & mySTC_STYLE_ITALIC)>0;
        SetUnderlined = (Style.Info[selection].fontstyle & mySTC_STYLE_UNDERL)>0;    
        SetSize = Style.Info[selection].fontsize;
        SetFont = Style.Info[selection].fontname;
        fg = Style.Info[selection].foreground;
        bg = Style.Info[selection].background;
    }
    else if (selection==13) {
        ModFG = true;
        fg = Style.CaretColour;
    }
    else if (selection==14) {
        ModFG = true; ModBG = true;
        bg = Style.LineNumberBgColour;
        fg = Style.LineNumberFgColour;
    }
    else if (selection==15) {
        ModFG = true; ModBG = true;
        bg = Style.SelectBgColour;
        fg = Style.SelectFgColour;
    }
    else if (selection==16) {
        ModStyle = true;
        ModFG = true;
        ModBG = true;
        SetBold = (Style.BraceFontStyle & mySTC_STYLE_BOLD)>0;
        SetItalic = (Style.BraceFontStyle & mySTC_STYLE_ITALIC)>0;
        SetUnderlined = (Style.BraceFontStyle & mySTC_STYLE_UNDERL)>0;
        fg = Style.BraceFgColour;
        bg = Style.BraceBgColour;
    }
    else if (selection==17) {
        ModStyle = true;
        ModFG = true;
        ModBG = true;
        SetBold = (Style.BadBraceFontStyle & mySTC_STYLE_BOLD)>0;
        SetItalic = (Style.BadBraceFontStyle & mySTC_STYLE_ITALIC)>0;
        SetUnderlined = (Style.BadBraceFontStyle & mySTC_STYLE_UNDERL)>0;
        bg = Style.BadBraceBgColour;
        fg = Style.BadBraceFgColour;
    }
    else if (selection==18) {
        ModBG = true, ModFG = true, ModSize = true;
        bg = Style.DefaultBgColour;
        fg = Style.DefaultFgColour;
        SetSize = Style.DefaultFontSize;
    }


    if (ModStyle) {
        CB_Bold->Enable();
        CB_Italic->Enable();
        CB_Underlined->Enable();
        
        CB_Bold->SetValue(SetBold);
        CB_Italic->SetValue(SetItalic);
        CB_Underlined->SetValue(SetUnderlined);
    }
    else {
        CB_Bold->Disable();
        CB_Italic->Disable();
        CB_Underlined->Disable();
    }
    

    if (ModSize) {
        spc71->Enable();
        spc71->SetValue(SetSize);
    }
    else spc71->Disable();
    

    if (ModFont) {
        cmb69->Enable();
        if( cmb69->FindString( SetFont ) == wxNOT_FOUND )
            cmb69->SetValue( "Courier New" );
        else
            cmb69->SetValue( SetFont );
        
    }
    else cmb69->Disable();
    
    if (ModFG) {
        But_Foreground->Enable();
        But_Foreground->SetBackgroundColour(GetClr(fg));
    }
    else {
        But_Foreground->Disable();
        But_Foreground->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_3DFACE));
    }
    
    if (ModBG) {
        But_Background->Enable();
        But_Background->SetBackgroundColour(GetClr(bg));
    }
    else {
        But_Background->Disable();
        But_Background->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_3DFACE));
    }
        

//    Choices.Add("Caret");
//    Choices.Add("Linenumbers");
//    Choices.Add("Text select");
//    Choices.Add("Brace match");
//    Choices.Add("Brace mismatch");

    return;

}

void ConfigDialog::Button_Foreground ( wxCommandEvent&  event ) {
    wxColour clrt;
    Parent->colr.SetChooseFull(false);

    wxColourDialog dlg(this, &(Parent->colr));
    if (dlg.ShowModal()!=wxID_OK) return;

    Parent->colr = dlg.GetColourData();
    clrt = Parent->colr.GetColour();

    But_Foreground->SetBackgroundColour(clrt);
    fg = (clrt.Red() << 16) | (clrt.Green() << 8) | clrt.Blue();
    
    return;
}

void ConfigDialog::Button_Background ( wxCommandEvent&  event ) {
    wxColour clrt;
    Parent->colr.SetChooseFull(false);
    
    wxColourDialog dlg(this, &(Parent->colr));
    if (dlg.ShowModal()!=wxID_OK) return;
    
    Parent->colr = dlg.GetColourData();
    clrt = Parent->colr.GetColour();
    
    But_Background->SetBackgroundColour(clrt);
    bg = (clrt.Red() << 16) | (clrt.Green() << 8) | clrt.Blue();
    
    return;
}

void ConfigDialog::SaveSettings () {
    int selection = Oldselection;
    if (selection < 13) {
        Style.Info[selection].fontstyle = 0;
        if (CB_Bold->GetValue())
                Style.Info[selection].fontstyle |= mySTC_STYLE_BOLD;
        if (CB_Italic->GetValue())
                Style.Info[selection].fontstyle |= mySTC_STYLE_ITALIC;
        if (CB_Underlined->GetValue())
                Style.Info[selection].fontstyle |= mySTC_STYLE_UNDERL;

        Style.Info[selection].fontsize = spc71->GetValue();
        Style.Info[selection].fontname = cmb69->GetValue();
        Style.Info[selection].foreground = fg;
        Style.Info[selection].background = bg;
    }
    else if (selection==13) {
        Style.CaretColour = fg;
    }
    else if (selection==14) {
        Style.LineNumberBgColour = bg;
        Style.LineNumberFgColour = fg;
    }
    else if (selection==15) {
        Style.SelectBgColour = bg;
        Style.SelectFgColour = fg;
    }
    else if (selection==16) {
        
        Style.BraceFontStyle = 0;
        if (CB_Bold->GetValue())
                Style.BraceFontStyle |= mySTC_STYLE_BOLD;
        if (CB_Italic->GetValue())
                Style.BraceFontStyle |= mySTC_STYLE_ITALIC;
        if (CB_Underlined->GetValue())
                Style.BraceFontStyle |= mySTC_STYLE_UNDERL;
        Style.BraceFgColour = fg;
        Style.BraceBgColour = bg;
    }
    else if (selection==17) {
        Style.BadBraceFontStyle = 0;
        if (CB_Bold->GetValue())
                Style.BadBraceFontStyle |= mySTC_STYLE_BOLD;
        if (CB_Italic->GetValue())
                Style.BadBraceFontStyle |= mySTC_STYLE_ITALIC;
        if (CB_Underlined->GetValue())
                Style.BadBraceFontStyle |= mySTC_STYLE_UNDERL;
        Style.BadBraceBgColour = bg;
        Style.BadBraceFgColour = fg;
    }
    else if (selection==18) {
        Style.DefaultBgColour = bg;
        Style.DefaultFgColour = fg;
        Style.DefaultFontSize = spc71->GetValue();
    }
}

void ConfigDialog::ThemeSelector (wxCommandEvent & event) {
    
    if (CB_Themes->GetSelection()!=0) {
        Style = Parent->LoadThemeFile(CB_Themes->GetValue());
        Parent->ThemeFile = CB_Themes->GetValue();
    }
    Oldselection = 0;
    wxCommandEvent test;
    ListBox_Select (test);
    
    return;
}


void ConfigDialog::Button_SaveTheme ( wxCommandEvent&  event ) {
    
    SaveSettings();
    if (CB_Themes->GetSelection()!=0)
        Parent->SaveThemeFile(Style, CB_Themes->GetValue());
    else {
        wxTextEntryDialog dialog(this, _T(Parent->Lang[157]), //"Enter theme name:"
                                        _T(Parent->Lang[158]), //"Paremeters..."
                                        "", wxOK | wxCANCEL);
        if (dialog.ShowModal() != wxID_OK) return;
        
        wxString fn = dialog.GetValue();
        fn = fn.Lower();
        fn = fn.Trim(true);
        fn = fn.Trim(false);

        wxFileSystem File;
        if (File.FindFirst(Parent->EditorPath+"ide\\"+fn+".fbt")!="") {
            //"Theme \""+ fn +"\" already exists!\nOverwrite it?"
            if (wxMessageBox (Parent->Lang[159]+ fn + Parent->Lang[160], Parent->Lang[161], wxICON_QUESTION | wxYES_NO )!=wxOK) 
                return;
        }
        else {
            wxTextFile temp(Parent->EditorPath+"ide\\"+fn+".fbt");
            temp.Create();
            temp.Write();
            temp.Close();
        }
            
        Parent->SaveThemeFile(Style, fn);
        Parent->ThemeFile = fn;
        CB_Themes->Append(fn);
        CB_Themes->Select(CB_Themes->GetCount()-1);
    }
    return;
}


void ConfigDialog::KeywordSelect          ( wxCommandEvent& event ) {
    int selection = CB_KeywordGroup->GetSelection() + 1;
    Parent->Keyword[OldKWSelect] = TA_Keywords->GetValue();
    TA_Keywords->Clear();
    TA_Keywords->AppendText( Parent->Keyword[selection] );
    OldKWSelect = selection;

}


ConfigDialog::~ConfigDialog   (  ) {
 
    //delete CD_Settings;
    //delete CD_Theme;
    //delete CD_Keywords;
    //delete CD_Compiler;
    //delete CD_Notebook;
}
*/
