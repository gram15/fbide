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


#ifndef Browser_H
#define Browser_H

#include <vector>


// deprecated versions defined for compatibility reasons
#define wxRESIZE_BOX            wxMAXIMIZE_BOX
#define wxTHICK_FRAME           wxRESIZE_BORDER

// obsolete styles, unused any more
#define wxDIALOG_MODAL          0
#define wxDIALOG_MODELESS       0
#define wxNO_3D                 0
#define wxUSER_COLOURS          0
#define wxSP_FULLSASH           0


using namespace std;

class SFBrowser: public wxDialog {
public:
    SFBrowser(  wxWindow* parent,
                wxWindowID id = -1,
                const wxString& title = wxT(""),
                long style = wxCAPTION|
                             wxSYSTEM_MENU|
                             wxCLOSE_BOX|
                             wxDIALOG_NO_PARENT|
                             wxDEFAULT_DIALOG_STYLE|
                             wxMINIMIZE_BOX|
                             wxRESIZE_BOX|
                             wxRESIZE_BORDER|
                             wxWANTS_CHARS ,
                const wxString& name = wxT("sfbrower") );
    ~SFBrowser();

    void AddListItem ( int Linenr, bool Type, wxString Message );
    void OnCharAdded ( wxCommandEvent& event );
    void OnEnter     ( wxCommandEvent& event );
    void OnSelect    ( wxListEvent& event );
    void OnActivate  ( wxListEvent& event );

    void GenerateList( wxString Search );

    void OnClose ( wxCloseEvent & event);
    void OnKeyUp ( wxKeyEvent &event );
    //    void SFBClose (  ) { delete this; }

    void Rebuild (  );

    MyFrame     * Parent;
    wxStaticText* SearchLabel;
    wxTextCtrl  * SearchBox;
    wxListCtrl  * SFList;
    wxPanel     * Panel;

    wxArrayString Original;
    wxArrayString OriginalArg;
    vector <int> OrigLineNr;
    vector <bool> OrigType;

    wxString SearchString;
    bool     ChangePos;

    enum {
        SearchBoxId,
        SFListId,
    };

protected:
    DECLARE_EVENT_TABLE()
};

// Pointer control



#endif

