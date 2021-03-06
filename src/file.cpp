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

#include <wx/textfile.h>
#include "inc/main.h"
#include "inc/fbedit.h"
#include "inc/browser.h"
#include "inc/format.h"

void MyFrame::OnNew (wxCommandEvent& WXUNUSED(event)) {
    NewSTCPage(_T(""), true);
    SetTitle( _T("FBIde - ") + bufferList[FBNotebook->GetSelection()]->GetFileName() );
    return;
}



void MyFrame::OnOpen (wxCommandEvent& WXUNUSED(event)) {
    wxFileDialog dlg (this,
                      Lang[186],//Load File
                      _T(""),
                      _T(".bas"),
                      Lang[187],//Types
                      wxFILE_MUST_EXIST | wxMULTIPLE);
    if (dlg.ShowModal() != wxID_OK)
        return;
    wxArrayString File;
    dlg.GetPaths(File);
    for(int i=0;i<(int)File.Count();i++) {
        int result = bufferList.FileLoaded(File[i]);

        if (result != -1)
            FBNotebook->SetSelection(result);
        else {
            m_FileHistory->AddFileToHistory( File[i] );
            NewSTCPage(File[i], true);
        }
    }
    return;
}

void MyFrame::OnFileHistory( wxCommandEvent& event ) {
    wxString file = m_FileHistory->GetHistoryFile( event.GetId() - wxID_FILE1 );
    if( ::wxFileExists( file ) ) {
        int result = bufferList.FileLoaded( file );
        if( result != -1 )
            FBNotebook->SetSelection(result);
        else
            NewSTCPage( file, true );
    }
}

void MyFrame::OnSave (wxCommandEvent& WXUNUSED(event)) {
    if (stc==0)
        return;
    int index = FBNotebook->GetSelection();
    if (SaveFile(bufferList[index]))
        SetModified ( index, false );

    return;
}



void MyFrame::OnSaveAs (wxCommandEvent& WXUNUSED(event)) {
    if (stc==0)
        return;

    int index = FBNotebook->GetSelection();
    Buffer * buff = bufferList[index];
    wxString OldName = buff->GetFileName();
    if (SaveFile(buff, true)) {
        if (OldName != buff->GetFileName())
            SetModified ( index, false );
    }
    return;
}

void MyFrame::OnSaveAll (wxCommandEvent& WXUNUSED(event)) {
    if (stc==0)
        return;

    //unsigned int index = 0;
    int selectpage = FBNotebook->GetSelection();
    Buffer* buff;

    //while (bufferList.GetModifiedCount()) {
    for( int index = 0; index < FBNotebook->GetPageCount(); index++ ) {
        buff = bufferList[index];
        if (buff->GetModified()) {
            FBNotebook->SetSelection(index);
            if (SaveFile( buff )) {
                SetModified ( index, false );
            }
        }
        //index++;
    }

    FBNotebook->SetSelection(selectpage);

    return;
}



void MyFrame::OnCloseAll_       ( wxCommandEvent& WXUNUSED(event) ) {
    OnCloseAll();
}

void MyFrame::OnCloseAll        ( ) {
    if (stc == 0)
        return;

    Buffer* buff;

    while ( FBNotebook ) {
        buff = bufferList[0];
        FBNotebook->SetSelection(0);
        if (buff->GetModified()) {
            int result = wxMessageBox(Lang[188] + buff->GetFileName() + Lang[189],
                                      Lang[184],
                                      wxYES_NO | wxCANCEL | wxICON_EXCLAMATION);
            if (result==wxCANCEL)
                return;
            else if (result==wxYES) {
                if (SaveFile(buff))
                    CloseFile(0);
                else
                    return;
            }
            else if (result==wxNO)
                CloseFile(0);
            bufferList.DecrModCount();
        }
        else
            CloseFile(0);
    }
    SetTitle( _T("FBIde") );
    return;
}



void MyFrame::OnCloseFile_      ( wxCommandEvent& WXUNUSED(event) ) {
    OnCloseFile();
}
void MyFrame::OnCloseFile       ( ) {
    if (stc==0)
        return;
    int index = FBNotebook->GetSelection();
    Buffer* buff = bufferList[index];

    if (buff->GetModified()) {
        wxString message = wxString::Format(Lang[190],
                                            wxFileNameFromPath(buff->GetFileName()).c_str());

        int closeDialog = wxMessageBox(message, Lang[192], //"File Modified"
                                       wxYES_NO | wxCANCEL | wxICON_EXCLAMATION, GetParent());

        if (closeDialog == wxYES)
            SaveFile(buff);

        else if (closeDialog == wxCANCEL)
            return;
        bufferList.DecrModCount();
    }

    CloseFile ( index );
    if(bufferList.GetBufferCount()>0)
        SetTitle( _T("FBIde - ") + bufferList[FBNotebook->GetSelection()]->GetFileName() );
    else
        SetTitle(_T("FBIde"));
}


void MyFrame::CloseFile          ( int index ) {

    if ( SFDialog && FBNotebook->GetPageCount()==1 ) {
        SFDialog->Close(true);
    }
    if (FindDialog)     {
        FindDialog->Close(true);
    }
    if (ReplaceDialog)  {
        ReplaceDialog->Close(true);
    }
    if (formatDialog)   {
        formatDialog->Close(true);
    }

    stc->SetBuffer( (Buffer *) 0 );
    stc->ClearAll();
    stc->ReleaseDocument( bufferList[index]->GetDocument() );
    FBNotebook->DeletePage(index);
    bufferList.RemoveBuffer(index);
    if (bufferList.GetBufferCount() == 0) {
        //m_TabStcSizer->Remove( FBNotebook );
        //m_TabStcSizer->Remove( stc );
        m_TabStcSizer->Detach( FBNotebook );
        m_TabStcSizer->Detach( stc );        
        delete stc;
        delete FBNotebook;
        FBCodePanel->SetSizer( NULL );
        stc = 0;
        FBNotebook = 0;
        m_TabStcSizer = 0;
        EnableMenus(false);
    }
    else {
        SetSTCPage(FBNotebook->GetSelection());
    }

    return;
}


void MyFrame::OnQuit (wxCommandEvent& event) {

    Close(true);
}



void MyFrame::OnNewWindow     (wxCommandEvent &WXUNUSED(event)) {
    wxExecute (FB_App->argv[0]);
    return;
}


//----------------------------------------------------------------------------







bool MyFrame::SaveFile (Buffer* buff, bool SaveAS) {
    wxString FileName = (SaveAS) ? _T("") : buff->GetFileName();

    int ft = buff->GetFileType();

    wxString Temp = (ft==0) ? Lang[193] : Lang[200];
    Temp <<  Lang[194];

    if (FileName==_T("")||FileName==FBUNNAMED) {
        wxFileDialog dlg (this,
                          Lang[195],//Save file
                          _T(""),
                          ( (ft==0) ? _T(".bas") : _T(".html") ),
                          Temp,
                          wxSAVE|wxOVERWRITE_PROMPT);
        if (dlg.ShowModal() != wxID_OK)
            return false;
        FileName = dlg.GetPath();
        if (SaveAS) {
            if(wxMessageBox(Lang[196], Lang[197], wxICON_QUESTION|wxYES_NO|wxNO_DEFAULT ) == wxYES)
                buff->SetFileName( FileName );
        }
        else {
            buff->SetFileName( FileName );
        }
    }

    stc->SaveFile (FileName);
    SetTitle( _T("FBIde - ") + bufferList[FBNotebook->GetSelection()]->GetFileName() );
    return true;
}



void MyFrame::OnSessionLoad      ( wxCommandEvent& event ) {
    wxFileDialog dlg (this,
                      Lang[186], //Load file
                      _T(""),
                      _T(".bas"),
                      Lang[198], //FBIde Session
                      wxFILE_MUST_EXIST );
    if (dlg.ShowModal() != wxID_OK)
        return;
    wxString File = dlg.GetPath();

    SessionLoad(File);
}

void MyFrame::SessionLoad ( wxString File ) {

    wxTextFile TextFile(File);
    TextFile.Open();
    if(TextFile.GetLineCount()==0)
        return;

    wxString Temp;
    int result = 0;
    unsigned long selectedtab = 0;

    Temp = TextFile[0];
    int ver = 1;
    if( Temp.Trim( false ).Trim( true ).Lower() == _T("<fbide:session:version = \"0.2\"/>") )
        ver = 2;

    for( unsigned int i = ver; i < TextFile.GetLineCount(); i++) {
        Temp = TextFile[i];
        if( Temp != _T("") && ::wxFileExists( Temp ) ) {
            result = bufferList.FileLoaded(Temp);
            if (result == -1) {
                NewSTCPage(Temp, false);
                if( ver == 2 ) {
                    unsigned long t = 0;
                    i++;
                    Temp = TextFile[i];
                    Temp.ToULong( &t );
                    stc->ScrollToLine( t );

                    i++;
                    Temp = TextFile[i];
                    Temp.ToULong ( &t );
                    stc->SetCurrentPos( t );
                    stc->SetSelectionStart( t );
                    stc->SetSelectionEnd( t );
                }
            }
        }

    }

    if( ver == 2 )
        Temp = TextFile[1];
    else
        Temp = TextFile[0];

    Temp.ToULong(&selectedtab);

    FBNotebook->SetSelection(selectedtab);

    TextFile.Close();

    SetTitle( _T("FBIde - ") + bufferList[FBNotebook->GetSelection()]->GetFileName() );

    return;
}


void MyFrame::OnSessionSave      ( wxCommandEvent& event ) {
    if (stc==0)
        return;

    wxString FileName;

    wxFileDialog dlg (this,
                      Lang[199],
                      _T(""),
                      _T(".fbs"),
                      Lang[198],
                      wxSAVE|wxOVERWRITE_PROMPT);
    if (dlg.ShowModal() != wxID_OK)
        return;
    FileName = dlg.GetPath();

    wxTextFile TextFile(FileName);
    if (TextFile.Exists()) {
        TextFile.Open();
        TextFile.Clear();
    }
    else {
        TextFile.Create();
    }

    Buffer* buff;
    bool session = false;
    bool header = true;

    int SelectedTab = FBNotebook->GetSelection();
    TextFile.AddLine( _T("<fbide:session:version = \"0.2\"/>") );
    for (int i=0; i < FBNotebook->GetPageCount();i++ ) {
        buff = bufferList[i];
        if (buff->GetModified()) {
            FBNotebook->SetSelection(i);
            int result = wxMessageBox(Lang[188] + buff->GetFileName() + Lang[189],
                                      Lang[184],
                                      wxYES_NO | wxCANCEL | wxICON_EXCLAMATION);
            if (result==wxCANCEL)
                return;
            else if (result==wxYES) {
                SaveFile(buff);
                session = true;
                SetModified ( i, false );
            }
            else if (result==wxNO) {
                if (buff->GetFileName()!=FBUNNAMED) {
                    session = true;
                }
            }
        }
        else {
            session = true;
        }

        if ( session && buff->GetFileName()!=FBUNNAMED ) {
            if (header) {
                header = false;
                wxString t;
                t << SelectedTab;
                TextFile.AddLine(t);
            }
            wxString Temp;
            session = false;
            TextFile.AddLine(buff->GetFileName());
            if( i == (int)FBNotebook->GetSelection() )
                SaveDocumentStatus( i );
            Temp << buff->GetLine();
            TextFile.AddLine( Temp );
            Temp = _T("");
            Temp << buff->GetCaretPos();
            TextFile.AddLine( Temp );
        }
    }

    FBNotebook->SetSelection(SelectedTab);

    if(TextFile.GetLineCount()) {
        TextFile.Write();
    }

    TextFile.Close();

    return;
}
