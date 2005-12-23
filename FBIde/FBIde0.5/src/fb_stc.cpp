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


#include "inc/wxall.h"
#include "inc/fb_config.h"
#include "inc/fb_doc.h"
#include "inc/fb_frame.h"

#include "inc/fb_stc.h"


BEGIN_EVENT_TABLE (FB_STC, wxStyledTextCtrl)
    EVT_STC_CHARADDED   (-1,            FB_STC::OnCharAdded)
    EVT_STC_MODIFIED    (-1,            FB_STC::OnModified)
    EVT_STC_UPDATEUI    (-1,            FB_STC::OnUpdateUI)
    EVT_MENU( wxID_UNDO,                FB_STC::OnUndo )
    EVT_MENU( wxID_REDO,                FB_STC::OnRedo )
    EVT_MENU( wxID_COPY,                FB_STC::OnCopy )
    EVT_MENU( wxID_CUT,                 FB_STC::OnCut )
    EVT_MENU( wxID_PASTE,               FB_STC::OnPaste )
    EVT_MENU( wxID_SELECTALL,           FB_STC::OnSelectall )
    EVT_MENU( fbideID_SelectLine,       FB_STC::OnSelectline )
    EVT_MENU( wxID_JUSTIFY_RIGHT,       FB_STC::OnJustifyRight )
    EVT_MENU( wxID_JUSTIFY_LEFT,        FB_STC::OnJustifyLeft )
    EVT_MENU( fbideID_CommentBlock,     FB_STC::OnCommentblock )
    EVT_MENU( fbideID_UncommentBlock,   FB_STC::OnUncommentblock )
END_EVENT_TABLE()


FB_STC::FB_STC (  ) { }

FB_STC::FB_STC ( wxWindow * parent, FB_Doc * Doc, FB_Frame * Ide ) {
    CreateSTC( parent, Doc, Ide );
}


FB_STC::~FB_STC() {
    delete m_Doc;
}


void FB_STC::CreateSTC ( wxWindow * parent, FB_Doc * Doc, FB_Frame * Ide ) {
    this->Hide();
    this->Create( parent, wxID_ANY );
    m_Ide = Ide;
    m_Doc = Doc;
    if ( !m_Doc->IsNewDoc() && m_Doc->GetFile().FileExists() ) {
        SetUndoCollection( false );
            LoadFile( m_Doc->GetFile().GetFullPath() );
        SetUndoCollection( true );
    }
    return;
}


void FB_STC::CreateDoc( wxWindow * parent, FB_Doc * Doc, FB_Frame * Ide ) {
    CreateSTC( parent, Doc, Ide );
    m_CanComment = false;
    LoadSettings();
    return;
}


void FB_STC::LoadSettings ( ) {
    FB_Config    * Prefs  = m_Ide->GetConfig();
    Style_STC_FB * Style  = &Prefs->Style_FB;

    // Clear all styles there might be defined
    StyleClearAll(  );
    SetLexer( 0 );
    
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
        wxFont font ( _STYLE(0).Size, wxMODERN, wxNORMAL, wxNORMAL, false, _STYLE(0).Font );

        StyleSetForeground (wxSTC_STYLE_DEFAULT,    Prefs->GetClr(_STYLE(0).Face));
        StyleSetBackground (wxSTC_STYLE_DEFAULT,    Prefs->GetClr(_STYLE(0).Back));
        StyleSetFont( wxSTC_STYLE_DEFAULT, font );

        StyleSetForeground (0,    Prefs->GetClr(_STYLE(0).Face));
        StyleSetBackground (0,    Prefs->GetClr(_STYLE(0).Back));
        StyleSetFont( 0, font );
        
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

}

void FB_STC::OnModified ( wxStyledTextEvent& event ) {
    //m_Ide->SetModified(  );
}


void FB_STC::OnUpdateUI ( wxStyledTextEvent& event ) {
    m_Ide->SetStatus(  );
}


void FB_STC::OnCharAdded ( wxStyledTextEvent &event ) {
    return;
}


//----
void FB_STC::OnUndo ( wxCommandEvent& event ) {
    if (!CanUndo()) return;
    Undo ();
}

void FB_STC::OnRedo ( wxCommandEvent& event ) {
    if (!CanRedo()) return;
    Redo ();
}


void FB_STC::OnCopy ( wxCommandEvent& event ) {
    if (GetSelectionEnd()-GetSelectionStart() <= 0) return;
    Copy ();
}


void FB_STC::OnCut ( wxCommandEvent& event ) {
    if (GetReadOnly() || (GetSelectionEnd()-GetSelectionStart() <= 0)) return;
    Cut ();
}


void FB_STC::OnPaste ( wxCommandEvent& event ) {
    if (!CanPaste()) return;
    Paste ();
}


void FB_STC::OnSelectall ( wxCommandEvent& event ) {
    SetSelection (0, GetTextLength ());
}


void FB_STC::OnSelectline ( wxCommandEvent& event ) {
    int lineStart = PositionFromLine (GetCurrentLine());
    int lineEnd = PositionFromLine (GetCurrentLine() + 1);
    SetSelection (lineStart, lineEnd);
}


void FB_STC::OnJustifyRight ( wxCommandEvent& event ) {
    CmdKeyExecute (wxSTC_CMD_TAB);
}


void FB_STC::OnJustifyLeft ( wxCommandEvent& event ) {
    CmdKeyExecute (wxSTC_CMD_BACKTAB);
}

void FB_STC::ReplaceText(int from, int to, const wxString& text) {
    if (from == to)
    {
        InsertText(to, text);
        return;
    }

    SetTargetStart(from);
    SetTargetEnd(to);
    ReplaceTarget(text);
}


void FB_STC::OnCommentblock ( wxCommandEvent& event ) {
    return;
}


void FB_STC::OnUncommentblock ( wxCommandEvent& event ) {
    return;
}

