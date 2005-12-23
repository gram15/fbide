#include "inc/wxall.h"
#include "inc/fb_config.h"
#include "inc/fb_stc.h"
#include "inc/fb_doc.h"
#include "inc/fb_frame.h"

#include "inc/fb_stc.h"
#include "inc/fb_stc_html.h"

FB_STC_HTML::FB_STC_HTML (  ) {   }
FB_STC_HTML::FB_STC_HTML ( wxWindow * parent, FB_Doc * Doc, FB_Frame * Ide ) {
    CreateDoc( parent, Doc, Ide );
}

FB_STC_HTML::~FB_STC_HTML(  ) {
    return;
}


void FB_STC_HTML::CreateDoc( wxWindow * parent, FB_Doc * Doc, FB_Frame * Ide ) {
    CreateSTC( parent, Doc, Ide );
    m_CanComment = false;
    LoadSettings();
}    

void FB_STC_HTML::OnCharAdded ( wxStyledTextEvent &event ) {

}

void FB_STC_HTML::LoadSettings (  ) {
    FB_Config    * Prefs  = m_Ide->GetConfig();
    Style_STC_FB * Style  = &Prefs->Style_FB;

    // Clear all styles there might be defined
    StyleClearAll();
    
    // Load lexer for syntax hilighting
    SetLexer (wxSTC_LEX_HTML);

    // Tab and indenting
    SetTabWidth             ( Prefs->TabSize );
    SetUseTabs              ( false );
    SetTabIndents           ( true );
    SetBackSpaceUnIndents   ( true );
    SetIndent               ( Prefs->TabSize );
    SetIndentationGuides    ( Prefs->IndentGuide );
    
    // Right margin
    SetEdgeMode   ( Prefs->RightMargin ? wxSTC_EDGE_LINE: wxSTC_EDGE_NONE );
    SetEdgeColumn ( Prefs->EdgeColumn );
    
    // Line and line ending
    SetEOLMode ( 0 );
    SetViewEOL ( Prefs->DisplayEOL );
    SetViewWhiteSpace ( Prefs->WhiteSpace ? wxSTC_WS_VISIBLEALWAYS: wxSTC_WS_INVISIBLE );
    
    // Misc
    CmdKeyClear (wxSTC_KEY_TAB, 0);

    #define _STYLE(nr) Style->Style[nr]
        wxFont font ( 10, wxMODERN, wxNORMAL, wxNORMAL, false );
            
        for (int i = 0; i < 10; i++ ) {
            StyleSetFont (i, font);
            StyleSetBackground(i, *wxWHITE);
        }
        
        StyleSetForeground (wxSTC_H_DEFAULT, *wxBLACK);
        StyleSetForeground (wxSTC_H_TAG, wxColour(0,0,255));
        StyleSetForeground (wxSTC_H_TAGUNKNOWN, *wxBLACK);
        StyleSetForeground (wxSTC_H_ATTRIBUTE, wxColour(255,0,0));
        StyleSetForeground (wxSTC_H_ATTRIBUTEUNKNOWN, *wxBLACK);
        StyleSetForeground (wxSTC_H_NUMBER, wxColour(255,0,0));
        StyleSetForeground (wxSTC_H_DOUBLESTRING, wxColour(128,0,255));
        StyleSetForeground (wxSTC_H_SINGLESTRING, wxColour(128,0,255));
        StyleSetForeground (wxSTC_H_COMMENT, wxColour(0,128,0));
        StyleSetForeground (wxSTC_H_ENTITY, wxColour(255,69,0));
        
        StyleSetBold       (wxSTC_H_SINGLESTRING, true);
        StyleSetBold       (wxSTC_H_DOUBLESTRING, true);
        StyleSetItalic     (wxSTC_H_COMMENT, true);

        SetKeyWords (0, "color font b i body style size pre html head body meta http-equiv " \
                        "content charset span style title div class hr a href " \
                        "h1 h2 h3 h4 h5 h6 table tr td width height th link rel noshade li ul br " \
                        "name dl dd img src alt target border tt ol dt p" );
                        
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
    #undef STYLE

    int LineNrMargin = TextWidth(wxSTC_STYLE_LINENUMBER, _T("0001"));
    SetMarginWidth (0, Prefs->LineNumber ? LineNrMargin : 0);
    SetMarginWidth (1,0);

    if ( Prefs->CurrentLine )
    {
        SetCaretLineVisible( true );
        SetCaretLineBack( Prefs->GetClr( Style->CaretLine ) );
    }

    StyleSetForeground (wxSTC_STYLE_BRACELIGHT, Prefs->GetClr(Style->BraceFace));
    StyleSetBackground (wxSTC_STYLE_BRACELIGHT, Prefs->GetClr(Style->BraceBack));
    StyleSetBold       (wxSTC_STYLE_BRACELIGHT, (Style->BraceStyle & mySTC_STYLE_BOLD  ) > 0);
    StyleSetItalic     (wxSTC_STYLE_BRACELIGHT, (Style->BraceStyle & mySTC_STYLE_ITALIC) > 0);
    StyleSetUnderline  (wxSTC_STYLE_BRACELIGHT, (Style->BraceStyle & mySTC_STYLE_UNDERL) > 0);

    StyleSetForeground (wxSTC_STYLE_BRACEBAD, Prefs->GetClr(Style->BadBraceFace));
    StyleSetBackground (wxSTC_STYLE_BRACEBAD, Prefs->GetClr(Style->BadBraceBack));
    StyleSetBold       (wxSTC_STYLE_BRACEBAD, (Style->BadBraceStyle & mySTC_STYLE_BOLD  ) > 0);
    StyleSetItalic     (wxSTC_STYLE_BRACEBAD, (Style->BadBraceStyle & mySTC_STYLE_ITALIC) > 0);
    StyleSetUnderline  (wxSTC_STYLE_BRACEBAD, (Style->BadBraceStyle & mySTC_STYLE_UNDERL) > 0);
}


void FB_STC_HTML::OnCommentblock ( wxCommandEvent& event ) {

}


void FB_STC_HTML::OnUncommentblock ( wxCommandEvent& event ) {

}
