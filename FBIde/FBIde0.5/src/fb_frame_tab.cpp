
#include "inc/wxall.h"
#include "inc/fb_config.h"
#include "inc/fb_doc.h"
#include "inc/fb_stc.h"
#include "inc/fb_stc_fb.h"
#include "inc/fb_stc_html.h"
#include "inc/wxfb_notebook.h"
#include "inc/fb_doclist.h"
#include "inc/fb_toolbar.h"
#include "inc/fb_statusbar.h"
#include "inc/fb_frame.h"


bool FB_Frame::SaveDocument ( int TabID ) {
    if ( m_Code_areaTab == 0 ) return true;
    
    if ( TabID == -1 ) TabID = m_Code_areaTab->GetSelection();
    FB_STC * stc = reinterpret_cast< FB_STC *>( m_Code_areaTab->GetPage( TabID ) );
    FB_Doc * doc = stc->GetDoc();
    
    if( doc->IsNewDoc() ) return SaveDocumentAs( TabID );
    
    stc->SaveFile( doc->GetFullPath() );
    SetStatus( TabID );
    return true;    
}


bool FB_Frame::SaveDocumentAs ( int TabID ) {
    if ( m_Code_areaTab == 0 ) return true;
    
    if ( TabID == -1 ) TabID = m_Code_areaTab->GetSelection();
    FB_STC * stc = reinterpret_cast< FB_STC *>( m_Code_areaTab->GetPage( TabID ) );
    FB_Doc * doc = stc->GetDoc();
    
    wxString FileTypes;
    FileTypes << "FB source files (*.bas)|*.bas" << "|"
              << "FB header files (*.bi)|*.bi"   << "|"
              << "HTML files (*.html)|*.html"    << "|"
              << "Resource files (*.rc)|*.rc"    << "|"
              << "Text files (*.txt)|*.txt"      << "|"
              << "All files|*.*";
    
    wxString OriginalType;
    if ( doc->GetDocType() == fbDoc_FBDoc && doc->IsNewDoc() ) OriginalType = ".bas";
    else OriginalType = "." + doc->GetFile().GetExt().Lower();
   
    wxFileDialog dlg(this, "Save File as...", "", 
                     OriginalType, FileTypes, wxSAVE|wxOVERWRITE_PROMPT );

    if( OriginalType == ".bas" )
        dlg.SetFilterIndex( 0 );
    else if( OriginalType == ".bi" )
        dlg.SetFilterIndex( 1 );
    else if( OriginalType == ".htm" || OriginalType == ".html" )
        dlg.SetFilterIndex( 2 );
    else if( OriginalType == ".rc" )
        dlg.SetFilterIndex( 3 );
    else if( OriginalType == ".txt" )
        dlg.SetFilterIndex( 4 );
    else
        dlg.SetFilterIndex( 5 );
    
    
    if ( dlg.ShowModal() != wxID_OK ) return false;
    wxString FileName = dlg.GetPath();
    
    stc->SaveFile( FileName );
    
    if ( doc->IsNewDoc() ) {
        m_DocList->Add( FileName );
        doc->SetFile( FileName );
    }
    
    SetStatus( TabID );
    if( TabID == m_ActiveTabID )
        SetTitle( "FBIde - " + m_ActiveDoc->GetFileName() );
        
    return true;
}


bool FB_Frame::SaveAllDocuments (  ) {
    if ( m_Code_areaTab == 0 ) return true;
    for( int i = 0; i <static_cast<int>( m_Code_areaTab->GetPageCount() ); i++ ) {
        if( !SaveDocument( i ) ) return false;
    }
    return true;
}


bool FB_Frame::CloseDocument ( int TabID ) {
    if ( m_Code_areaTab == 0 ) return true;

    if ( TabID == -1 ) TabID = m_Code_areaTab->GetSelection();
    
    FB_STC * stc = reinterpret_cast< FB_STC *>( m_Code_areaTab->GetPage( TabID ) );
    FB_Doc * doc = stc->GetDoc();

    if( doc->IsModified() ) {
        int action = wxMessageBox( "File \"" + doc->GetFullPath() + "\" is modified. Save?", 
                                   "Attention!", 
                                   wxICON_QUESTION|wxYES_NO|wxCANCEL|wxYES_DEFAULT );
        if( action == wxCANCEL ) return false;
        else if ( action == wxYES )
            if( !SaveDocument( TabID ) ) return false;
    }
    
    if ( !doc->IsNewDoc() )
        m_DocList->Remove( doc->GetFile() );

    DeleteDocument( TabID );

    return true;
}


bool FB_Frame::CloseAllDocument (  ) {
    if( m_Code_areaTab == 0 ) return true;
    
    while( m_Code_areaTab ) {
        if( !CloseDocument() ) return false;
    }
    return true;
}


bool FB_Frame::CloseAET (  ) {
    if ( m_Code_areaTab == 0 ) return true;
    
    int ActiveTab = m_Code_areaTab->GetSelection();
    
    for( int i = m_Code_areaTab->GetPageCount()-1; i > -1; i-- ) {
        if( ActiveTab != i )
            if( !CloseDocument( i ) ) return false;
    }
        
    return true;
}


void FB_Frame::CreateDocument ( wxString File, bool SelectTab ) {

    FB_Doc * doc;
    FB_STC * stc;
    
    if( File != "" ) {
        if( m_DocList->IsLoaded( File ) ) {
            if( SelectTab ) {
                for( size_t i = 0; i < m_Code_areaTab->GetPageCount(); i++ ) {
                    stc = reinterpret_cast<FB_STC *>( m_Code_areaTab->GetPage( i ) );
                    doc = stc->GetDoc();
                    if( doc->GetFile() == File ) {
                        if( m_ActiveTabID != static_cast<int>(i) ) 
                            m_Code_areaTab->SetSelection( i );
                        return;
                    }
                }
            }
            return;            
        }
        m_DocList->Add( File );
    }
    
    if ( m_Code_areaTab == 0 ) {
        wxPanel * old = reinterpret_cast<wxPanel *>( m_Code_area );
        m_Code_areaTab = new wxFB_Notebook( m_VSplitter, fbideID_Notebook );
        m_VSplitter->ReplaceWindow( old, m_Code_areaTab );
        delete old;
        m_Code_area = m_Code_areaTab;
    }
    
    doc = new FB_Doc( File );
    switch( doc->GetDocType() ) {
        case fbDoc_FBDoc : 
            stc = new FB_STC_FB;
            break;
        case fbDoc_HTML :
            stc = new FB_STC_HTML;
            break;
        case fbDoc_TXT :
        case fbDoc_UNKNOWN :
        default:
            stc = new FB_STC;
            break;
    }
    
    stc->CreateDoc( m_Code_areaTab, doc, this );
    m_Code_areaTab->AddPage( stc, doc->GetFileName(), SelectTab );

}


void FB_Frame::DeleteDocument ( int idx ) {
    Freeze();
    m_Code_areaTab->DeletePage( idx );
    if( m_Code_areaTab->GetPageCount() == 0 ) {
        wxFB_Notebook * old = m_Code_areaTab;
        m_Code_area = new wxPanel ( m_VSplitter, wxID_ANY, 
                       wxDefaultPosition, wxDefaultSize,
                       wxTAB_TRAVERSAL|wxSUNKEN_BORDER );
        m_Code_area->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_APPWORKSPACE ) );
        m_VSplitter->ReplaceWindow( old, m_Code_area );
        delete old;
        m_Code_areaTab = NULL;
        m_ActiveTabID = -1;
        SetStatus();
        SetTitle( "FBIde" );
    }
    Thaw();
    return;
}


void FB_Frame::SetStatus( int idx ) {
    if( m_Code_areaTab ) {
        FB_STC * stc;
        FB_Doc * doc;
        if ( idx == -1 || idx == m_ActiveTabID ) {
            idx = m_ActiveTabID;
            stc = m_ActiveSTC;
            doc = m_ActiveDoc;
            m_ToolBar->EnableTool( wxID_UNDO,   stc->CanUndo() );
            m_ToolBar->EnableTool( wxID_REDO,   stc->CanRedo() );
            m_ToolBar->EnableTool( wxID_CUT,    stc->HasSelection() );
            m_ToolBar->EnableTool( wxID_COPY,   stc->HasSelection() );
            m_ToolBar->EnableTool( wxID_PASTE,  stc->CanPaste() );
            m_ToolBar->EnableTool( wxID_SAVE,   stc->GetModify() );
            m_ToolBar->EnableTool( wxID_SAVE_ALL,    true );
            m_ToolBar->EnableTool( wxID_CLOSE,       true );
        } else {
            stc = reinterpret_cast<FB_STC *>( m_Code_areaTab->GetPage( idx ) );
            doc = stc->GetDoc();
        }
        
        if( stc->GetModify() != doc->IsModified() ) { 
            doc->SetModified( stc->GetModify() );
            
            wxString PageTitle( doc->GetFileName() );
            if ( doc->IsModified() )
                PageTitle += " [*]";
            m_Code_areaTab->SetPageText( idx, PageTitle );
        }
        wxString Temp;
        Temp << stc->LineFromPosition( stc->GetCurrentPos() ) + 1 <<
             " : " << stc->GetColumn( stc->GetCurrentPos() ) + 1 << "";
        
        m_StatusBar->SetStatusText( Temp, 0 );
        
        Temp = "";
        Temp << stc->GetLineCount() << " Lines in file";        
        m_StatusBar->SetStatusText( Temp, 1 );
    } else {
        m_ToolBar->EnableTool(wxID_SAVE,        false );
        m_ToolBar->EnableTool(wxID_SAVE_ALL,    false );
        m_ToolBar->EnableTool(wxID_CLOSE,       false );
        m_ToolBar->EnableTool(wxID_CUT,         false );
        m_ToolBar->EnableTool(wxID_COPY,        false );
        m_ToolBar->EnableTool(wxID_PASTE,       false );
        m_ToolBar->EnableTool(wxID_UNDO,        false );
        m_ToolBar->EnableTool(wxID_REDO,        false );
        m_ToolBar->EnableTool(fbideID_Compile,  false );
        m_ToolBar->EnableTool(fbideID_Run,      false );
        m_ToolBar->EnableTool(fbideID_CompileAndRun,    false );
        m_ToolBar->EnableTool(fbideID_RebuildAll,       false );
        m_ToolBar->EnableTool(fbideID_QuickRun,         false );
    }
}



void FB_Frame::OnTabPopUp( wxCommandEvent& event ) {
    FB_STC * stc = reinterpret_cast<FB_STC *>( m_Code_areaTab->GetCurrentPage() );
    wxMenu popup("");
    popup.Append(wxID_CLOSE,        _("Close"));
    popup.Append(wxID_CLOSE_ALL,    _("Close all"));
    popup.Append(fbideID_CloseAET,  _("Close all except this"));
    popup.AppendSeparator();
    popup.Append(wxID_UNDO,         _("Undo"));
    popup.Enable(wxID_UNDO, stc->CanUndo());
    popup.Append(wxID_REDO,         _("Redo"));
    popup.Enable(wxID_REDO, stc->CanRedo());
    popup.AppendSeparator();
    popup.Append(wxID_COPY,         _("Copy"));
    popup.Enable(wxID_COPY, stc->HasSelection());
    popup.Append(wxID_CUT,          _("Cut"));
    popup.Enable(wxID_CUT,  stc->HasSelection());
    popup.Append(wxID_PASTE,        _("Paste"));
    popup.Enable(wxID_PASTE, stc->CanPaste());
    popup.Append(wxID_SELECTALL,    _("Select All"));
    popup.Enable(wxID_SELECTALL, stc->GetLength());
    m_Code_areaTab->PopupMenu( &popup );
}



void FB_Frame::OnTabChanged( wxNotebookEvent& event ) {
    m_ActiveTabID = m_Code_areaTab->GetSelection();
    m_ActiveSTC = reinterpret_cast<FB_STC *>( m_Code_areaTab->GetCurrentPage() );
    m_ActiveDoc = m_ActiveSTC->GetDoc();
    m_ActiveSTC->SetFocus();
    SetStatus();
    SetTitle( "FBIde - " + m_ActiveDoc->GetFileName() );
}
