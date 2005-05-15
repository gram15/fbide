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

#include <wx/file.h>
#include <wx/colour.h>

#include "inc/main.h"
#include "inc/fbedit.h"
#include "inc/browser.h"

BEGIN_EVENT_TABLE (FB_Edit, wxStyledTextCtrl)

    EVT_STC_MARGINCLICK (-1,                FB_Edit::OnMarginClick)
    
    EVT_STC_CHARADDED   (-1,                FB_Edit::OnCharAdded)
    EVT_STC_UPDATEUI    (-1,                FB_Edit::OnUpdateUI)
    EVT_STC_MODIFIED    (-1,                FB_Edit::OnModified)
    EVT_STC_HOTSPOT_CLICK(-1,               FB_Edit::OnHotSpot)
    EVT_KEY_UP(                             FB_Edit::OnKeyUp)
    EVT_KEY_DOWN(                           FB_Edit::OnKeyDown)
    
END_EVENT_TABLE()

FB_Edit::FB_Edit (MyFrame * ParentFrame, wxWindow *parentNotebook, wxWindowID id,
			wxString FileToLoad,
            const wxPoint &pos,
            const wxSize &size,
            long style)
   			: wxStyledTextCtrl (parentNotebook, id, pos, size, style) {
    
    Parent = ParentFrame;
    braceLoc = -1;
    buff = 0;
    ChangeTab = 0;
    exitUUI = false;
}


void FB_Edit::LoadSTCSettings    (  ) {

    CommonInfo * Prefs = &Parent->Prefs;
    
    SetTabWidth (Prefs->TabSize);
    SetUseTabs (false);
    SetTabIndents (true);
    SetBackSpaceUnIndents (true);
    SetIndent(Prefs->TabSize);
    
    SetEdgeColumn (Prefs->EdgeColumn);
    SetEOLMode(0);
    
    SetViewEOL (Prefs->DisplayEOL);
    
    SetIndentationGuides (Prefs->IndentGuide);
    int LineNrMargin = TextWidth (wxSTC_STYLE_LINENUMBER, _T("0001"));
    SetMarginWidth (0, Prefs->LineNumber ? LineNrMargin: 0);
    SetMarginWidth (1,0);
    SetEdgeMode (Prefs->LongLine ? wxSTC_EDGE_LINE: wxSTC_EDGE_NONE);
    SetViewWhiteSpace (Prefs->whiteSpace ? wxSTC_WS_VISIBLEALWAYS: wxSTC_WS_INVISIBLE);
    CmdKeyClear (wxSTC_KEY_TAB, 0);

    return;
}


void FB_Edit::LoadSTCTheme       ( int FileType ) {
    
    CommonInfo * Prefs = &(Parent->Prefs);
    StyleInfo  * Style = &(Parent->Style);
    
    SetLexer (0);
    for (int Nr = 0; Nr < 15; Nr++) {
        StyleSetForeground (Nr, GetClr(Style->DefaultFgColour));
        StyleSetBackground (Nr, GetClr(Style->DefaultBgColour));
        StyleSetBold (Nr, 0);
        StyleSetItalic (Nr, 0);
        StyleSetUnderline (Nr, 0);
        StyleSetCase (Nr, 0);
    }

    if (Prefs->SyntaxHighlight) {
        if (FileType == 0) {
            SetLexer (wxSTC_LEX_VB);
            //Initalise Highlighing colors, font styles and set lexer.
            int Nr=0;
            int StyleNR[]={ wxSTC_B_DEFAULT,    wxSTC_B_COMMENT,
                            wxSTC_B_NUMBER,     wxSTC_B_KEYWORD,
                            wxSTC_B_STRING,     wxSTC_B_PREPROCESSOR,  
                            wxSTC_B_OPERATOR,   wxSTC_B_IDENTIFIER,
                            wxSTC_B_DATE,       wxSTC_B_STRINGEOL,
                            wxSTC_B_KEYWORD2,   wxSTC_B_KEYWORD3,
                            wxSTC_B_KEYWORD4,   wxSTC_B_CONSTANT,
                            wxSTC_B_ASM };
            
            for (int i=1;i<15;i++) {
                Nr=StyleNR[i];
                wxString fontname="";
                
                //Foreground
                StyleSetForeground (Nr, GetClr(Style->Info[i].foreground));
                StyleSetBackground (Nr, GetClr(Style->Info[i].background));
                
                wxFont font (
                    Style->Info[i].fontsize, 
                    wxMODERN, 
                    wxNORMAL, 
                    wxNORMAL, 
                    false,
                    Style->Info[i].fontname );
                
                StyleSetFont (Nr, font);
                
                //Font attributes
                StyleSetBold       (Nr, (Style->Info[i].fontstyle & mySTC_STYLE_BOLD) > 0);
                StyleSetItalic     (Nr, (Style->Info[i].fontstyle & mySTC_STYLE_ITALIC) > 0);
                StyleSetUnderline  (Nr, (Style->Info[i].fontstyle & mySTC_STYLE_UNDERL) > 0);
                StyleSetVisible    (Nr, (Style->Info[i].fontstyle & mySTC_STYLE_HIDDEN) == 0);
                StyleSetCase       (Nr,  Style->Info[i].lettercase );
            }
            for (int Nr = 0; Nr < 4; Nr++)
                SetKeyWords (Nr, Parent->Keyword[Nr+1]);
            
        }
        else if(FileType == 1) {
            
            SetLexer (wxSTC_LEX_HTML);

            wxFont font (
                10, 
                wxMODERN, 
                wxNORMAL, 
                wxNORMAL, 
                false );
                
            for (int i = 0; i < 10; i++ ) {
                StyleSetFont (i, font);
                StyleSetBackground(i, *wxWHITE);
            }
            
            StyleSetForeground (wxSTC_H_DEFAULT, *wxBLACK);
            StyleSetForeground (wxSTC_H_TAG, wxColour(128,0,128));
            StyleSetForeground (wxSTC_H_TAGUNKNOWN, *wxBLACK);
            StyleSetForeground (wxSTC_H_ATTRIBUTE, *wxBLACK);
            StyleSetForeground (wxSTC_H_ATTRIBUTEUNKNOWN, *wxBLACK);
            StyleSetForeground (wxSTC_H_NUMBER, wxColour(0,0,255));
            StyleSetForeground (wxSTC_H_DOUBLESTRING, wxColour(0,0,255));
            StyleSetForeground (wxSTC_H_SINGLESTRING, wxColour(0,0,255));
            StyleSetForeground (wxSTC_H_COMMENT, *wxLIGHT_GREY);
            StyleSetForeground (wxSTC_H_ENTITY, wxColour(255,69,0));
            
            StyleSetBold       (wxSTC_H_TAG, true);
            StyleSetBold       (wxSTC_H_ATTRIBUTE, true);
            SetKeyWords (0, "color font b i body style size pre");
        }
    }
    else {
        for (int Nr = 0; Nr < 4; Nr++)
            SetKeyWords (Nr, "");
    }
    
    if (FileType==0||!Prefs->SyntaxHighlight) {
        StyleSetForeground (wxSTC_STYLE_DEFAULT,    GetClr(Style->DefaultFgColour));
        StyleSetBackground (wxSTC_STYLE_DEFAULT,    GetClr(Style->DefaultBgColour));
        
        StyleSetForeground (wxSTC_STYLE_LINENUMBER, GetClr(Style->LineNumberFgColour));
        StyleSetBackground (wxSTC_STYLE_LINENUMBER, GetClr(Style->LineNumberBgColour));
        SetCaretForeground (GetClr(Style->CaretColour));
        
        SetSelBackground(true, GetClr(Style->SelectBgColour));
        SetSelForeground(true, GetClr(Style->SelectFgColour));
        
        wxFont font (   Style->DefaultFontSize, 
                        wxMODERN, 
                        wxNORMAL, 
                        wxNORMAL, 
                        false,
                        Style->DefaultFont );
        StyleSetFont (wxSTC_STYLE_DEFAULT, font);
    }
    else {
        StyleSetForeground (wxSTC_STYLE_DEFAULT,    *wxBLACK );
        StyleSetBackground (wxSTC_STYLE_DEFAULT,    *wxWHITE );

        StyleSetForeground (wxSTC_STYLE_LINENUMBER, *wxWHITE);
        StyleSetBackground (wxSTC_STYLE_LINENUMBER,  wxColour(192,192,192));
        SetCaretForeground (*wxBLACK);
        
        SetSelBackground(true, wxColour(192,192,192));
        SetSelForeground(true, wxColour(255,255,255));
    }

    
    //   SetCaretLineBack("RED");

    //Brace light
    StyleSetForeground (wxSTC_STYLE_BRACELIGHT, GetClr(Style->BraceFgColour));
    StyleSetBackground (wxSTC_STYLE_BRACELIGHT, GetClr(Style->BraceBgColour));
    StyleSetBold       (wxSTC_STYLE_BRACELIGHT, (Style->BraceFontStyle & mySTC_STYLE_BOLD) > 0);
    StyleSetItalic     (wxSTC_STYLE_BRACELIGHT, (Style->BraceFontStyle & mySTC_STYLE_ITALIC) > 0);
    StyleSetUnderline  (wxSTC_STYLE_BRACELIGHT, (Style->BraceFontStyle & mySTC_STYLE_UNDERL) > 0);
    StyleSetVisible    (wxSTC_STYLE_BRACELIGHT, (Style->BraceFontStyle & mySTC_STYLE_HIDDEN) == 0);
//   
//   //BraceBad
    StyleSetForeground (wxSTC_STYLE_BRACEBAD, GetClr(Style->BadBraceFgColour));
    StyleSetBackground (wxSTC_STYLE_BRACEBAD, GetClr(Style->BadBraceBgColour));
    StyleSetBold       (wxSTC_STYLE_BRACEBAD, (Style->BadBraceFontStyle & mySTC_STYLE_BOLD) > 0);
    StyleSetItalic     (wxSTC_STYLE_BRACEBAD, (Style->BadBraceFontStyle & mySTC_STYLE_ITALIC) > 0);
    StyleSetUnderline  (wxSTC_STYLE_BRACEBAD, (Style->BadBraceFontStyle & mySTC_STYLE_UNDERL) > 0);
    StyleSetVisible    (wxSTC_STYLE_BRACEBAD, (Style->BadBraceFontStyle & mySTC_STYLE_HIDDEN) == 0);

//   
    

   
   //Markers
    SetMarginType (2, wxSTC_MARGIN_SYMBOL);
    SetMarginMask (2, wxSTC_MASK_FOLDERS);
    
    SetFoldFlags(wxSTC_FOLDFLAG_LINEAFTER_CONTRACTED);
    MarkerDefine(wxSTC_MARKNUM_FOLDER,          wxSTC_MARK_BOXPLUS, "white", "gray");
    MarkerDefine(wxSTC_MARKNUM_FOLDEREND,       wxSTC_MARK_BOXPLUSCONNECTED, "white", "gray");
    MarkerDefine(wxSTC_MARKNUM_FOLDERMIDTAIL,   wxSTC_MARK_TCORNER, "white", "gray");
    MarkerDefine(wxSTC_MARKNUM_FOLDEROPEN,      wxSTC_MARK_BOXMINUS, "white", "gray");
    MarkerDefine(wxSTC_MARKNUM_FOLDEROPENMID,   wxSTC_MARK_BOXMINUSCONNECTED, "white", "gray");
    MarkerDefine(wxSTC_MARKNUM_FOLDERSUB,       wxSTC_MARK_VLINE, "white", "gray");
    MarkerDefine(wxSTC_MARKNUM_FOLDERTAIL,      wxSTC_MARK_LCORNER, "white", "gray");
    
    SetProperty (_T("fold"), "1");
    SetProperty (_T("fold.comment"), "1");
    SetProperty (_T("fold.compact"), "1");
    SetProperty (_T("fold.preprocessor"), "1");
    
    if (Prefs->FolderMargin) {
        SetMarginWidth (2, 14);
        SetMarginSensitive (2, 1);
    }
    else {
        SetMarginWidth (2, 0);
        SetMarginSensitive (2, 0);        
    }
    
    return;
}

//Stc events
void FB_Edit::OnModified        ( wxStyledTextEvent &WXUNUSED(event) ) {
    if(buff!=0) {
        if(GetModify()!=buff->GetModified()) { 
            Parent->SetModified(-1, !buff->GetModified()); 
        }
    }
    if(Parent->SFDialog) { if (Parent->SFDialog->ChangePos == false) Parent->SFDialog->Rebuild(); }
}
    
void FB_Edit::OnUpdateUI	    ( wxStyledTextEvent &event ) {
//    if (exitUUI) { event.Skip(); return; }
//
//    if (Parent->Prefs.LineNumber) {
//        exitUUI = true;
//        int t = GetCurrentLine();
//        wxString st;
//        st << t << "0";
//    
//        int LineNrMargin = TextWidth (wxSTC_STYLE_LINENUMBER, _T(st));
//    
//        SetMarginWidth (0, LineNrMargin);
//        SetMarginWidth (1,0);
//        exitUUI = false;
//    }

    if (Parent->Prefs.BraceHighlight) {
      if (IsBrace(GetCharAt(GetCurrentPos()))) {
        braceLoc = BraceMatch(GetCurrentPos());

        if (braceLoc != -1) 
            BraceHighlight(GetCurrentPos(), braceLoc);
        else {
            BraceBadLight(GetCurrentPos());
            braceLoc = GetCurrentPos();
        }
      }
      else {
        if (braceLoc != -1) {
            BraceHighlight(-1, -1);
            braceLoc = -1;
        }
      }
   }
    
    wxString pos;
    pos.Printf("  %d : %d", LineFromPosition(GetCurrentPos()) + 1,
                GetColumn(GetCurrentPos()) + 1);
    Parent->SetStatusText(pos, 1);
}

inline bool FB_Edit::IsBrace(wxChar brace)
{
    return brace == '{' || brace == '}' ||
           brace == '[' || brace == ']' ||
           brace == '(' || brace == ')';
}



void FB_Edit::OnCharAdded  		( wxStyledTextEvent &event ) {
    event.Skip();
    if (!Parent->Prefs.AutoIndent) return;

    char        key     = event.GetKey();
    int         cLine   = GetCurrentLine();
    int         lineInd = GetLineIndentation(cLine - 1);
    int         plineind= GetLineIndentation(cLine - 2);
    int         TabSize = Parent->Prefs.TabSize;
    if (key!='\n') return;

    //Previous line
    wxString    TempCL  = ClearCmdLine(GetLine(cLine - 1));
    wxString    clfkw   = GetFirstKw(TempCL);
    wxString    cllkw   = GetLastKw(TempCL);

    //Line before previous
    wxString    TempPL  = ClearCmdLine(GetLine(cLine - 2));
    wxString    plfkw   = GetFirstKw(TempPL);
    wxString    pllkw   = GetLastKw(TempPL);
    
    
    if (lineInd>0) {
        if ( clfkw == "end" && IsEndDeIndentWord(cllkw) ) {
            if (cllkw!=plfkw) { 
                if (cllkw == "select" && plfkw == "case") lineInd = plineind;
                else if (plineind<=lineInd) lineInd -= TabSize; 
            }
            else if (cllkw=="function" && TempPL.Find('=')!=-1) lineInd -= TabSize;
            else if (plfkw== "if" && pllkw!="then") {
                if (plineind<=lineInd) lineInd -= TabSize; }
            else lineInd = plineind;
        }
        
        else if (clfkw != pllkw) {
            if (( clfkw == "next" && plfkw != "for")||
                ( clfkw == "loop" && plfkw != "do")||
                ( clfkw == "wend" && plfkw != "while")) {
                    if (plineind<=lineInd) lineInd -= TabSize;
                }
            else if (( clfkw == "next" && plfkw == "for")||
                 ( clfkw == "loop" && plfkw == "do")||
                 ( clfkw == "wend" && plfkw == "while"))
                lineInd = plineind;
            else if ( clfkw == "case" ) {
                if (plfkw == "case" || plfkw == "select") { lineInd = plineind; }
                else  { if (plineind<=lineInd) lineInd -= TabSize; } }
            else if ( clfkw == "else" || clfkw == "elseif" ) {
                if ((plfkw == "if" && pllkw == "then") ||
                    (plfkw == "elseif")) { lineInd = plineind; } 
                else   { if (plineind<=lineInd) lineInd -= TabSize; } }
                
        }
        else if(clfkw == "next" && plfkw != "for")
            if (plineind<=lineInd) lineInd -= TabSize;
            
        SetLineIndentation (cLine-1, lineInd);
    }
    
    if (IsIndentWord(clfkw)) {
        if      (clfkw == "if") {
            if (cllkw == "then") lineInd += TabSize;
        }
        else if (clfkw == "do") {
            if (cllkw != "loop") lineInd += TabSize;
        }
        else if (clfkw == "while") {
            if (cllkw != "wend") lineInd += TabSize;
        }
        else if (clfkw == "for") {
            if (cllkw != "next") lineInd += TabSize;
        }
        else if (clfkw == "type") {
            if ((!TempCL.Contains(" as "))&&(!TempCL.Contains("\tas "))&&
                (!TempCL.Contains(" as\t"))&&(!TempCL.Contains("\tas\t")))
                lineInd += TabSize;
        }
        else if (clfkw=="function") {
            if (TempCL.Find('=')==-1) lineInd += TabSize;
        }
        else  lineInd += TabSize;
    }
    
    SetLineIndentation (cLine, lineInd);
    GotoPos(PositionFromLine (cLine) + lineInd);
    
}



void FB_Edit::OnMarginClick     ( wxStyledTextEvent &event ) {
    if (event.GetMargin() == 2) {
        int lineClick = LineFromPosition (event.GetPosition());
        int levelClick = GetFoldLevel (lineClick);
        if ((levelClick & wxSTC_FOLDLEVELHEADERFLAG) > 0) {
            ToggleFold (lineClick);
        }
    }
}


void FB_Edit::OnKeyDown          ( wxKeyEvent &event ) {
    event.Skip();
    if (event.ControlDown()) {
        int key = event.GetKeyCode();
        if (key>=48 && key <= 57) {
            int tab = (key-49) + (event.ShiftDown() ? 10 : 0);
            if (tab!=(int)Parent->FBNotebook->GetSelection()&&
                tab< (int)Parent->FBNotebook->GetPageCount()) {
                Parent->FBNotebook->SetSelection(tab);
            }
            return;
        }
//        else if(key==WXK_F4) { Parent->OnCloseFile(); }
    }
    if (!event.ControlDown()) return;
    SetMouseDownCaptures(false);
    StyleSetHotSpot(wxSTC_B_PREPROCESSOR, true);
    return;
}

void FB_Edit::OnKeyUp            ( wxKeyEvent &event ) {
    event.Skip();
    if (event.ControlDown()) return;
    SetMouseDownCaptures(true);
    StyleSetHotSpot(wxSTC_B_PREPROCESSOR, false);
    return;
}

void FB_Edit::OnHotSpot          ( wxStyledTextEvent &event ) {

    ChangeTab = LineFromPosition(event.GetPosition());
    wxString FileName = ClearCmdLine(GetLine(ChangeTab));
    wxString fkw = GetFirstKw(FileName);

    if (fkw!="#include") return;


    FileName = FileName.Left(FileName.Len()-1);
    FileName = FileName.Mid(FileName.Find('\"', true)+1);
    wxFileName File(FileName);
    
    if (!File.HasVolume()) {
        wxString FilePath = buff->GetFileName();
        wxString FBCPath = Parent->CompilerPath;
        if (FilePath==""||FilePath==FBUNNAMED)
            FilePath="";
            
        wxFileName w(FilePath);
        FilePath = w.GetPath(wxPATH_GET_SEPARATOR|wxPATH_GET_VOLUME);

        w.Assign(FBCPath);
        FBCPath = w.GetPath(wxPATH_GET_SEPARATOR|wxPATH_GET_VOLUME);
        
        if (FileName!="") {
            if(FileExists(FilePath+FileName)) {
                FileName=FilePath+FileName;
            }
            else if(FileExists(FBCPath+FileName)) {
                FileName=FBCPath+FileName;
            }
            else if(FileExists(FBCPath+"inc\\"+FileName)) {
                FileName=FBCPath+"inc\\"+FileName;
            }
            else FileName="";
        }
    }
    
    if(FileName!="") {
        if(FileExists(FileName)) {
            int result = Parent->bufferList.FileLoaded(FileName);
            if (result != -1) Parent->FBNotebook->SetSelection(result);
            else Parent->NewSTCPage(FileName, true);
            return;
        }

    }
}

