#include "inc/wxall.h"
#include "inc/fb_config.h"
#include "inc/fb_stc.h"
#include "inc/fb_doc.h"
#include "inc/fb_frame.h"

#include "inc/fb_stc.h"
#include "inc/fb_stc_fb.h"

FB_STC_FB::FB_STC_FB (  ) {   }
FB_STC_FB::FB_STC_FB ( wxWindow * parent, FB_Doc * Doc, FB_Frame * Ide ) {
    CreateDoc( parent, Doc, Ide );
}

FB_STC_FB::~FB_STC_FB(  ) {
    return;
}


void FB_STC_FB::CreateDoc( wxWindow * parent, FB_Doc * Doc, FB_Frame * Ide ) {
    CreateSTC( parent, Doc, Ide );
    m_CanComment = true;
    LoadSettings();
}    


void FB_STC_FB::OnModified ( wxStyledTextEvent& event ) {
    //m_Ide->SetModified(  );
}


void FB_STC_FB::OnUpdateUI ( wxStyledTextEvent& event ) {
    m_Ide->SetStatus(  );
    if (m_Ide->GetConfig()->BraceHighlight ) {
        if ( IsBrace( GetCharAt( GetCurrentPos() ) ) ) {
            m_braceLoc = BraceMatch( GetCurrentPos() );
            
            if ( m_braceLoc != -1 ) {
                BraceHighlight( GetCurrentPos(), m_braceLoc );
            } else {
                BraceBadLight( GetCurrentPos() );
                m_braceLoc = GetCurrentPos();
            }
        } else if(  IsBrace( GetCharAt( GetCurrentPos() - 1 ) ) ) {
            m_braceLoc = BraceMatch( GetCurrentPos() - 1 );
            
            if ( m_braceLoc != -1 ) {
                BraceHighlight( GetCurrentPos() - 1, m_braceLoc );
            } else {
                BraceBadLight( GetCurrentPos() - 1);
                m_braceLoc = GetCurrentPos() - 1;
            }
        } else {
            if ( m_braceLoc != -1) {
                BraceHighlight(-1, -1);
                m_braceLoc = -1;
            }
        }
    }
}


void FB_STC_FB::OnCharAdded ( wxStyledTextEvent &event ) {

}

void FB_STC_FB::LoadSettings (  ) {
    FB_Config    * Prefs  = m_Ide->GetConfig();
    Style_STC_FB * Style  = &Prefs->Style_FB;

    // Clear all styles there might be defined
    StyleClearAll();
    
    // Load lexer for syntax hilighting
    SetLexer (wxSTC_LEX_VB);

    // Tab and indenting
    SetTabWidth             ( Prefs->TabSize );
    SetUseTabs              ( false );
    SetTabIndents           ( true );
    SetBackSpaceUnIndents   ( true );
    SetIndent               ( Prefs->TabSize );
    SetIndentationGuides    ( Prefs->IndentGuide );
    SetUseAntiAliasing      ( true );
    
    // Right margin
    SetEdgeMode   ( Prefs->RightMargin ? wxSTC_EDGE_LINE: wxSTC_EDGE_NONE );
    SetEdgeColumn ( Prefs->EdgeColumn );
    
    // Line and line ending
    SetEOLMode ( 0 );
    SetViewEOL ( Prefs->DisplayEOL );
    SetViewWhiteSpace ( Prefs->WhiteSpace ? wxSTC_WS_VISIBLEALWAYS: wxSTC_WS_INVISIBLE );
    
    // Misc
    CmdKeyClear (wxSTC_KEY_TAB, 0);
    
    //Initalise Highlighing colors, font styles and set lexer.
    int StyleNR[]={ wxSTC_B_DEFAULT,    wxSTC_B_COMMENT,
                    wxSTC_B_NUMBER,     wxSTC_B_KEYWORD,
                    wxSTC_B_STRING,     wxSTC_B_PREPROCESSOR,  
                    wxSTC_B_OPERATOR,   wxSTC_B_IDENTIFIER,
                    wxSTC_B_DATE,       wxSTC_B_STRINGEOL,
                    wxSTC_B_KEYWORD2,   wxSTC_B_KEYWORD3,
                    wxSTC_B_KEYWORD4,   wxSTC_B_CONSTANT,
                    wxSTC_B_ASM };
    
    #define _STYLE(nr) Style->Style[nr]
        for (int i = 0; i < 15; i++) 
        {
            int Nr = StyleNR[i];
            int idx = Prefs->SyntaxHighlight ? i : 0;

            wxString fontname="";
            
            StyleSetForeground (Nr, Prefs->GetClr(_STYLE(idx).Face));
            StyleSetBackground (Nr, Prefs->GetClr(_STYLE(idx).Back));
            
            wxFont font ( _STYLE(idx).Size, wxMODERN, wxNORMAL, wxNORMAL, false, _STYLE(idx).Font );
            StyleSetFont (Nr, font);
            
            //Font attributes
            StyleSetBold       (Nr, (_STYLE(idx).Style & mySTC_STYLE_BOLD  ) > 0);
            StyleSetItalic     (Nr, (_STYLE(idx).Style & mySTC_STYLE_ITALIC) > 0);
            StyleSetUnderline  (Nr, (_STYLE(idx).Style & mySTC_STYLE_UNDERL) > 0);
            StyleSetCase       (Nr,  _STYLE(idx).Case );
        }

        wxFont font ( _STYLE(0).Size, wxMODERN, wxNORMAL, wxNORMAL, false, _STYLE(0).Font );
        StyleSetFont( wxSTC_STYLE_DEFAULT, font );
        StyleSetFont( wxSTC_STYLE_LINENUMBER, font ); 

        StyleSetForeground (wxSTC_STYLE_DEFAULT,    Prefs->GetClr(_STYLE(0).Face));
        StyleSetBackground (wxSTC_STYLE_DEFAULT,    Prefs->GetClr(_STYLE(0).Back));
        
        StyleSetForeground (wxSTC_STYLE_LINENUMBER, Prefs->GetClr(Style->LineNumberFace));
        StyleSetBackground (wxSTC_STYLE_LINENUMBER, Prefs->GetClr(Style->LineNumberBack));
        StyleSetFont( wxSTC_STYLE_LINENUMBER, font );
                    
        SetCaretForeground (Prefs->GetClr(Style->CaretFace));
        SetSelForeground(true, Prefs->GetClr(Style->SelectFace));
        SetSelBackground(true, Prefs->GetClr(Style->SelectBack));
        wxFont brace_font ( _STYLE(6).Size, wxMODERN, wxNORMAL, wxNORMAL, false, _STYLE(6).Font );
    #undef STYLE

    if (Prefs->SyntaxHighlight)
    {
        SetKeyWords ( 0, Prefs->FB_Keywords[0] );
        SetKeyWords ( 1, Prefs->FB_Keywords[1] );
        SetKeyWords ( 2, Prefs->FB_Keywords[2] );
        SetKeyWords ( 3, Prefs->FB_Keywords[3] );
    }

    int LineNrMargin = TextWidth(wxSTC_STYLE_LINENUMBER, _T("00001"));
    SetMarginWidth (0, Prefs->LineNumber ? LineNrMargin : 0);
    SetMarginWidth (1,0);

    if ( Prefs->CurrentLine )
    {
        SetCaretLineVisible( true );
        SetCaretLineBack( Prefs->GetClr( Style->CaretLine ) );
    }

    StyleSetForeground (wxSTC_STYLE_BRACELIGHT, Prefs->GetClr(Style->BraceFace));
    StyleSetBackground (wxSTC_STYLE_BRACELIGHT, Prefs->GetClr(Style->BraceBack));
    StyleSetFont( wxSTC_STYLE_BRACELIGHT, brace_font );
    StyleSetBold       (wxSTC_STYLE_BRACELIGHT, (Style->BraceStyle & mySTC_STYLE_BOLD  ) > 0);
    StyleSetItalic     (wxSTC_STYLE_BRACELIGHT, (Style->BraceStyle & mySTC_STYLE_ITALIC) > 0);
    StyleSetUnderline  (wxSTC_STYLE_BRACELIGHT, (Style->BraceStyle & mySTC_STYLE_UNDERL) > 0);
        
    StyleSetForeground (wxSTC_STYLE_BRACEBAD, Prefs->GetClr(Style->BadBraceFace));
    StyleSetBackground (wxSTC_STYLE_BRACEBAD, Prefs->GetClr(Style->BadBraceBack));
    StyleSetFont( wxSTC_STYLE_BRACEBAD, brace_font );
    StyleSetBold       (wxSTC_STYLE_BRACEBAD, (Style->BadBraceStyle & mySTC_STYLE_BOLD  ) > 0);
    StyleSetItalic     (wxSTC_STYLE_BRACEBAD, (Style->BadBraceStyle & mySTC_STYLE_ITALIC) > 0);
    StyleSetUnderline  (wxSTC_STYLE_BRACEBAD, (Style->BadBraceStyle & mySTC_STYLE_UNDERL) > 0);
    
}


void FB_STC_FB::OnCommentblock ( wxCommandEvent& event ) {
    int SelStart    = GetSelectionStart();
    int SelEnd      = GetSelectionEnd();
    int lineStart   = LineFromPosition (SelStart);
    int lineEnd     = LineFromPosition (SelEnd);

    BeginUndoAction();
        for(int i = lineStart;i <= lineEnd; i++) {
            InsertText(PositionFromLine( i ),"\'");
        }
    EndUndoAction();

    if (lineStart!=lineEnd)
        SetSelection( PositionFromLine( lineStart ), GetLineEndPosition( lineEnd ) );

}


void FB_STC_FB::OnUncommentblock ( wxCommandEvent& event ) {
    int lineStart = LineFromPosition (GetSelectionStart());
    int lineEnd = LineFromPosition (GetSelectionEnd());
    int x = 0;
    wxString Temp;

    BeginUndoAction();
        for(;lineStart <= lineEnd; lineStart++) {
            Temp = GetLine(lineStart);
            Temp = Temp.Lower();
            Temp = Temp.Trim(false);
            Temp = Temp.Trim(true);
            Temp+= " ";
            x = PositionFromLine(lineStart) + GetLineIndentation(lineStart);
            if (Temp.Left(4) == "rem "||Temp.Left(4) == "rem\t")
                ReplaceText(x, x+3, "");
            else if (Temp.Left(1) == "\'")
                ReplaceText(x, x+1, "");
        }
    EndUndoAction();
}
