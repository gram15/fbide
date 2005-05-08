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
    
    void OnCharAdded  		( wxStyledTextEvent &event );
	void OnUpdateUI		    ( wxStyledTextEvent &event );
    static bool IsBrace     ( wxChar brace );
    void OnMarginClick      ( wxStyledTextEvent &event );
    void OnModified         ( wxStyledTextEvent &event );
    void OnKeyDown          ( wxKeyEvent &event );
    void OnKeyUp            ( wxKeyEvent &event );
    void OnHotSpot          ( wxStyledTextEvent &event );

    wxString    DocumentName;
    int braceLoc;
    int ChangeTab;
    bool exitUUI;
    
    inline bool IsIndentWord ( wxString word ) {
        return  (word == "if" || word == "for" || word=="sub" ||
                word == "asm" || word == "type" || word=="union" ||
                word == "enum" || word == "function" || word=="case" ||
                word == "else" || word == "do" || word=="while" ||
                word == "elseif" || word == "select" || word=="with");
    }
    
    inline bool IsEndDeIndentWord ( wxString word ) {
        return (word == "if"   || word == "sub"     || word == "asm"    || 
                word == "type" || word == "union"   || word == "enum"   || 
                word == "with" || word == "select"  || word == "function");
    }
    
    inline bool IsDeIndentWord ( wxString word ) {
        return (word == "next" || word == "loop" || word == "wend");
    }
    
    inline wxString ClearCmdLine ( wxString cmdline ) {
        cmdline = cmdline.Trim(false).Lower();
        bool instring =false;
        wxString temp;
        for (unsigned int i=0; i < cmdline.Len(); i++) {
            if (cmdline[i] == '\"') instring = !instring;
            else if (cmdline[i] == '\'' && !instring) break;
            temp << cmdline[i];
        }
        return temp.Trim(true);
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
    
    
//   ~FB_Edit ();
private:

    DECLARE_EVENT_TABLE()
};

#endif // _EDIT_H_
