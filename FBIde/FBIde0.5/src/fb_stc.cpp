/////////////////////////////////////////////////////////////////////////////
// Name:        fb_stc.cpp
// Purpose:     
// Author:      VonGodric
// Modified by: 
// Created:     08/03/05 14:23:04
// RCS-ID:      
// Copyright:   
// Licence:     GPL
/////////////////////////////////////////////////////////////////////////////


#include "wx/wx.h"
#include "inc/fb_doc.h"
#include "inc/fb_config.h"
#include "inc/fb_stc.h"



BEGIN_EVENT_TABLE (FB_STC, wxStyledTextCtrl)
    EVT_STC_CHARADDED   (-1,                FB_STC::OnCharAdded)
END_EVENT_TABLE()


FB_STC::FB_STC ( wxWindow * parent, FB_Doc * doc, FB_Config * config ) : 
    wxStyledTextCtrl ( parent, wxID_ANY )
{
    Config = config;
    Doc = doc;
    Parent = parent;
    return;
}

void FB_STC::LoadSettings ( ) 
{
    return;
}

void FB_STC::OnCharAdded ( wxStyledTextEvent &event ) 
{

}

//----

FB_STC_FB::FB_STC_FB ( wxWindow * parent, FB_Doc * doc, FB_Config * config ) :
    FB_STC( parent, doc, config )
{
    LoadSettings();
}

void FB_STC_FB::OnCharAdded ( wxStyledTextEvent &event ) 
{

}

void FB_STC_FB::LoadSettings (  ) 
{
    FB_Config    * Prefs  = Config;
    Style_STC_FB * Style  = &Config->Style_FB;

    // Clear all styles there might be defined
    StyleClearAll();
    
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
    
    // If Syntax HiLight is on then Load it.
    if (Prefs->SyntaxHighlight) {
        SetLexer (wxSTC_LEX_VB);
        
        //Initalise Highlighing colors, font styles and set lexer.
        int Nr = 0;
        int StyleNR[]={ wxSTC_B_DEFAULT,    wxSTC_B_COMMENT,
                        wxSTC_B_NUMBER,     wxSTC_B_KEYWORD,
                        wxSTC_B_STRING,     wxSTC_B_PREPROCESSOR,  
                        wxSTC_B_OPERATOR,   wxSTC_B_IDENTIFIER,
                        wxSTC_B_DATE,       wxSTC_B_STRINGEOL,
                        wxSTC_B_KEYWORD2,   wxSTC_B_KEYWORD3,
                        wxSTC_B_KEYWORD4,   wxSTC_B_CONSTANT,
                        wxSTC_B_ASM };
        
        #define _STYLE(nr) Style->Style[nr]
            for (int i=0;i<15;i++) 
            {
                Nr=StyleNR[i];
                wxString fontname="";
                
                StyleSetForeground (Nr, Prefs->GetClr(_STYLE(i).Face));
                StyleSetBackground (Nr, Prefs->GetClr(_STYLE(i).Back));
                
                wxFont font ( _STYLE(i).Size, wxMODERN, wxNORMAL, wxNORMAL, false, _STYLE(i).Font );
                StyleSetFont (Nr, font);
                
                //Font attributes
                StyleSetBold       (Nr, (_STYLE(i).Style & mySTC_STYLE_BOLD  ) > 0);
                StyleSetItalic     (Nr, (_STYLE(i).Style & mySTC_STYLE_ITALIC) > 0);
                StyleSetUnderline  (Nr, (_STYLE(i).Style & mySTC_STYLE_UNDERL) > 0);
                StyleSetCase       (Nr,  _STYLE(i).Case );
            }

            wxFont font ( _STYLE(0).Size, wxMODERN, wxNORMAL, wxNORMAL, false, _STYLE(0).Font );
            StyleSetFont( wxSTC_STYLE_DEFAULT, font );

            StyleSetForeground (wxSTC_STYLE_DEFAULT,    Prefs->GetClr(_STYLE(0).Face));
            StyleSetBackground (wxSTC_STYLE_DEFAULT,    Prefs->GetClr(_STYLE(0).Back));
            
            StyleSetForeground (wxSTC_STYLE_LINENUMBER, Prefs->GetClr(Style->LineNumberFace));
            StyleSetBackground (wxSTC_STYLE_LINENUMBER, Prefs->GetClr(Style->LineNumberBack));
            StyleSetFont( wxSTC_STYLE_LINENUMBER, font );
                        
            SetCaretForeground (Prefs->GetClr(Style->CaretFace));
            SetSelForeground(true, Prefs->GetClr(Style->SelectFace));
            SetSelBackground(true, Prefs->GetClr(Style->SelectBack));

        #undef STYLE
        SetKeyWords ( 0, Prefs->FB_Keywords[0] );
        SetKeyWords ( 1, Prefs->FB_Keywords[1] );
        SetKeyWords ( 2, Prefs->FB_Keywords[2] );
        SetKeyWords ( 3, Prefs->FB_Keywords[3] );
    }

    int LineNrMargin = TextWidth(wxSTC_STYLE_LINENUMBER, _T("0001"));
    SetMarginWidth (0, Prefs->LineNumber ? LineNrMargin : 0);
    SetMarginWidth (1,0);

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
