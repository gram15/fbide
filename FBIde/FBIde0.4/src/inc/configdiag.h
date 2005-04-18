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

#ifndef _CONFDIAG_H_
#define _CONFDIAG_H_

#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/checkbox.h>
#include <wx/spinctrl.h>
#include <wx/stattext.h>
#include <wx/statline.h>
#include <wx/button.h>
#include <wx/textctrl.h>
#include <wx/listbox.h>
#include <wx/combobox.h>
#include <wx/textfile.h>

enum ConfigENUMS {
    CDID_OK,
    CDID_Cancel,
    CDID_GetCompPath,
    CDID_Foreground,
    CDID_Background,
    CDID_SaveTheme,
    CDID_ThemeSelector,
    CDID_KeywordSelector    
};


class ConfigDialog: public wxDialog {
public:
    ConfigDialog(   wxWindow* parent, 
                    wxWindowID id = -1, 
                    const wxString& title = wxT(""), 
                    long style = wxCAPTION|
                                 wxSYSTEM_MENU|
                                 wxCLOSE_BOX|
                                 wxDIALOG_NO_PARENT|
                                 wxDEFAULT_DIALOG_STYLE|
                                 wxMINIMIZE_BOX,
                    const wxString& name = wxT("dialogBox") );

    // Pointer control
    
    void Button_OK              ( wxCommandEvent&  event );
    void Button_Cancel          ( wxCommandEvent&  event );
    void Button_GetCompPath     ( wxCommandEvent&  event );
    void Button_Foreground      ( wxCommandEvent&  event );
    void Button_Background      ( wxCommandEvent&  event );
    void Button_SaveTheme       ( wxCommandEvent&  event );
    void ListBox_Select         ( wxCommandEvent&  event );
    
    void LoadStyle              ( StyleInfo   LoadStyle );
    void SaveStyle              ( StyleInfo   LoadStyle );
    void SaveSettings           (  );
    void ThemeSelector          ( wxCommandEvent& event );
    void KeywordSelect          ( wxCommandEvent& event );
        
    bool ModKw, ModTheme;
    StyleInfo   Style;
    int         Oldselection;
    int         OldKWSelect;
    uint        bg;
    uint        fg;
    
    wxNotebook *CD_Notebook;;
    wxPanel *CD_Settings;
    wxPanel *CD_Theme;
    wxCheckBox *CB_CurrentLine;
    wxCheckBox *CB_HiLightBraces;
    wxCheckBox *CB_SyntaxHiLight;
    wxCheckBox *CB_LongLine;
    wxCheckBox *CB_LineEndings;
    wxCheckBox *CB_WhiteSpaces;
    wxCheckBox *CB_IndentGuides;
    wxSpinCtrl *TB_Width;
    wxCheckBox *CB_FoldMargin;
    wxStaticText *st20;
    wxStaticLine *lno21;
    wxCheckBox *CB_AutoIndent;
    wxButton *But_OK;
    wxButton *But_Cancel;
    wxStaticLine *lno31;
    wxStaticText *st33;
    wxStaticText *st34;
    wxTextCtrl *TB_CompilerPath;
    wxStaticText *st37;
    wxButton *But_GetCompilerPath;
    wxStaticText *st41;
    wxTextCtrl *CompilerCommand;
    wxStaticText *st43;
    wxSpinCtrl *spc44;
    wxListBox *LB_Types;
    wxButton *But_Foreground;
    wxButton *But_Background;
    wxCheckBox *CB_Bold;
    wxCheckBox *CB_Italic;
    wxCheckBox *CB_Underlined;
    wxButton *But_SaveTheme;
    wxComboBox *CB_Themes;
    wxStaticText *st58;
    wxStaticText *st59;
    wxStaticLine *lno60;
    wxStaticText *st61;
    wxStaticText *st62;
    wxStaticText *st63;
    wxStaticText *st64;
    wxStaticLine *lno65;
    wxStaticLine *lnv66;
    wxStaticText *st67;
    wxComboBox *cmb69;
    wxStaticText *st70;
    wxSpinCtrl *spc71;
    wxPanel *CD_Keywords;
    wxStaticLine *lno74;
    wxStaticText *st75;
    wxChoice *CB_KeywordGroup;
    wxStaticText *st77;
    wxStaticText *st78;
    wxTextCtrl *TB_KeywordFile;
    wxButton *But_KeywordFile;
    wxTextCtrl *TA_Keywords;
 
    ~ConfigDialog   (  );

    MyFrame * Parent;
protected:
    DECLARE_EVENT_TABLE()
};

#endif
