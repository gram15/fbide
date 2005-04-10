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

#include "inc/main.h"

BEGIN_EVENT_TABLE (FB_Edit, wxStyledTextCtrl)
    EVT_STC_MARGINCLICK (-1,                FB_Edit::OnMarginClick)
    
    EVT_STC_CHARADDED   (-1,                FB_Edit::OnCharAdded)
    EVT_STC_UPDATEUI    (-1,                FB_Edit::OnUpdateUI)
END_EVENT_TABLE()

FB_Edit::FB_Edit (MyFrame * ParentFrame, wxWindow *parentNotebook, wxWindowID id,
			wxString FileToLoad,
            const wxPoint &pos,
            const wxSize &size,
            long style)
   			: wxStyledTextCtrl (parentNotebook, id, pos, size, style) {
    
    Parent = ParentFrame;
    DocumentName = FileToLoad;
    braceLoc = -1;
}


void FB_Edit::LoadSTCSettings    (  ) {

    CommonInfo * Prefs = &Parent->Prefs;
    
    SetTabWidth (Parent->Prefs.TabSize);
    SetUseTabs (false);
    SetTabIndents (true);
    SetBackSpaceUnIndents (true);
    SetIndent(Prefs->TabSize);
    
    SetEdgeColumn (Prefs->EdgeColumn);
    SetEOLMode(0);
    
    SetIndentationGuides (Prefs->IndentGuide);
    int LineNrMargin = TextWidth (wxSTC_STYLE_LINENUMBER, _T("0000"));
    SetMarginWidth (0, Prefs->LineNumber ? LineNrMargin: 0);
    SetMarginWidth (1,0);
    SetEdgeMode (Prefs->LongLine ? wxSTC_EDGE_LINE: wxSTC_EDGE_NONE);
    SetViewWhiteSpace (Prefs->whiteSpace ? wxSTC_WS_VISIBLEALWAYS: wxSTC_WS_INVISIBLE);
    CmdKeyClear (wxSTC_KEY_TAB, 0);
    
    return;
}


void FB_Edit::LoadSTCTheme       (  ) {
    
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
    else
        for (int Nr = 0; Nr < 4; Nr++)
            SetKeyWords (Nr, "");
    
    //   SetCaretLineBack("RED");
    StyleSetForeground (wxSTC_STYLE_DEFAULT,    GetClr(Style->DefaultFgColour));
    StyleSetBackground (wxSTC_STYLE_DEFAULT,    GetClr(Style->DefaultBgColour));
    StyleSetForeground (wxSTC_STYLE_LINENUMBER, GetClr(Style->LineNumberFgColour));
    StyleSetBackground (wxSTC_STYLE_LINENUMBER, GetClr(Style->LineNumberBgColour));
 
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
    SetCaretForeground (GetClr(Style->CaretColour));

    SetSelBackground(true, GetClr(Style->SelectBgColour));
    if (Style->SelectFgColour!=0)
		SetSelForeground(true, GetClr(Style->SelectFgColour));

    wxFont font (   Style->DefaultFontSize, 
                    wxMODERN, 
                    wxNORMAL, 
                    wxNORMAL, 
                    false,
                    Style->DefaultFont );

    StyleSetFont (wxSTC_STYLE_DEFAULT, font);
    StyleSetForeground (wxSTC_STYLE_LINENUMBER, GetClr(Style->LineNumberFgColour));
    StyleSetBackground (wxSTC_STYLE_LINENUMBER, GetClr(Style->LineNumberBgColour));

   
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
void FB_Edit::OnUpdateUI	    ( wxStyledTextEvent &event ) {

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
            else if (plfkw == "if" && pllkw!="then") {
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



