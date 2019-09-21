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

#ifndef _STCEDIT_H_
#define _STCEDIT_H_


#include <wx/stc/stc.h>

namespace kw {
    enum {
        SUB         = 1,
        FUNCTION,
        IF,
        THEN,
        ELSE,
        ELSEIF,
        CASE,
        SELECT,
        WITH,
        ASM,
        TYPE,
        UNION,
        ENUM,
        SCOPE,
        DO,
        FOR,
        WHILE,
        //------
        LOOP,
        NEXT,
        WEND,
        END,
        STATIC,
        PRIVATE
    };
    const int word_count = 23;
    const wxString words[word_count] = {
                                           _T("sub"), _T("function"), _T("if"), _T("then"), _T("else"), _T("elseif"),
                                           _T("case"), _T("select"), _T("with"), _T("asm"), _T("type"), _T("union"),
                                           _T("enum"), _T("scope"), _T("do"), _T("for"), _T("while"), _T("loop"), _T("next"),
                                           _T("wend"), _T("end"), _T("static"), _T("private")
                                       };
}

class FB_Edit: public wxStyledTextCtrl {
public:
    FB_Edit ( MyFrame * ParentFrame, wxWindow *parentNotebook, wxWindowID id = -1,
              wxString FileToLoad= FBUNNAMED,
              const wxPoint &pos = wxDefaultPosition,
              const wxSize &size = wxDefaultSize,
              long style = wxSUNKEN_BORDER|wxVSCROLL
            );

    MyFrame * Parent;
    Buffer* buff;

    void LoadSTCSettings    (  );
    void LoadSTCTheme       ( int FileType = 0 );

    void OnCharAdded    ( wxStyledTextEvent &event );
    void OnUpdateUI      ( wxStyledTextEvent &event );
    static bool IsBrace     ( wxChar brace );
    void OnMarginClick      ( wxStyledTextEvent &event );
    void OnModified         ( wxStyledTextEvent &event );
    void OnKeyDown          ( wxKeyEvent &event );
    void OnKeyUp            ( wxKeyEvent &event );
    void OnHotSpot          ( wxStyledTextEvent &event );

    //void FB_Edit::IndentLine ( int & lineInd, int cLine );
    void IndentLine ( int & lineInd, int cLine );

    wxString    DocumentName;
    int braceLoc;
    int ChangeTab;
    bool exitUUI;

    int GetID( wxString kw ) {
        for( int i = 0; i < kw::word_count; i++ ) {
            if( kw[0] == kw::words[i][0] ) {
                if ( kw == kw::words[i] ) {
                    if ( i != kw::ELSE )
                        i++;
                    return i;
                }
            }
        }
        return 0;
    }

    inline wxString ClearCmdLine ( int cLine ) {
        wxString cmdline( GetLine(cLine).Trim(false).Lower() );
        bool instring =false;
        int len = 0;
        if ( cmdline[0]=='#'||(cmdline[0]=='\''&&cmdline[1]=='$'))
            return cmdline.Trim( true );
        for (unsigned int i=0; i < cmdline.Len(); i++) {
            if (cmdline[i] == '\"')
                instring = !instring;
            else if (cmdline[i] == '\'' && !instring)
                break;
            len++;
        }
        return cmdline.Left( len ).Trim(true);
    }

    inline wxString GetFirstKw ( wxString cmdline ) {
        wxString Temp = cmdline.Left(cmdline.Find(' '));
        Temp = Temp.Left(Temp.Find('('));
        return Temp;
    }

    inline wxString GetSecondKw ( wxString cmdline ) {
        int sp = cmdline.Find(' ');
        wxString Temp = cmdline.Mid(sp);
        Temp.Trim(true).Trim(false);
        return GetFirstKw( Temp );
    }

    inline wxString GetLastKw ( wxString cmdline ) {
        return cmdline.Right(cmdline.Len() - cmdline.Find(' ', true) - 1);
    }

    inline void SetBuffer ( Buffer* buff ) {
        this->buff = buff;
    }

    inline bool FileExists ( wxString File ) {
        wxFileName w(File);
        return w.FileExists();
    }

    int m_CursorPos;
    char m_CharAtCur;


    //   ~FB_Edit ();
private:

    DECLARE_EVENT_TABLE()
};

#endif // _EDIT_H_
