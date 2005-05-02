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

#include "inc/main.h"
#include "inc/fbedit.h"

void MyFrame::OnNew (wxCommandEvent& WXUNUSED(event)) {
    NewSTCPage("", true);
    return;
}



void MyFrame::OnOpen (wxCommandEvent& WXUNUSED(event)) {
    wxFileDialog dlg (this,
        _T("Load file"),
        _T(""),
        _T(".bas"),
        _T("FBFiles (*.bas)|*.bas|FBHeader files(*.bi)|*.bi|All file(*)|*.*"),
    wxFILE_MUST_EXIST | wxCHANGE_DIR);
    if (dlg.ShowModal() != wxID_OK) return;
    wxString File = dlg.GetPath();
    int result = bufferList.FileLoaded(File);
    
    if (result != -1) FBNotebook->SetSelection(result);
    else NewSTCPage(dlg.GetPath(), true);

    return;
}



void MyFrame::OnSave (wxCommandEvent& WXUNUSED(event)) {
    if (stc==0) return;
    int index = FBNotebook->GetSelection();
    if (SaveFile(bufferList[index]))
        SetModified ( index, false );

    return;
}



void MyFrame::OnSaveAs (wxCommandEvent& WXUNUSED(event)) {
    if (stc==0) return;
    
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
    if (stc==0) return;
    
    unsigned int index = 0;
    int selectpage = FBNotebook->GetSelection();
    Buffer* buff;
    
    while (bufferList.GetModifiedCount()&&index<FBNotebook->GetPageCount()) {
        buff = bufferList[index];
        FBNotebook->SetSelection(index);
        if (SaveFile( buff ))
            SetModified ( index, false );
        index++;
    }
    
    SetSTCPage ( selectpage );
    
    return;
}



void MyFrame::OnCloseAll_       ( wxCommandEvent& WXUNUSED(event) ) { OnCloseAll(); }

void MyFrame::OnCloseAll        ( ) {
    if (stc == 0) return;
    
    Buffer* buff;
    
    while ( FBNotebook->GetPageCount() ) {
        buff = bufferList[0];
        FBNotebook->SetSelection(0);
        if (buff->GetModified()) {
            int result = wxMessageBox("File \"" + buff->GetFileName() + "\" has been modified. Save?", 
                             "Save file?",
                             wxYES_NO | wxCANCEL | wxICON_EXCLAMATION);
            if (result==wxCANCEL) return;
            else if (result==wxYES) {
                if (SaveFile(buff)) CloseFile(0);
            }
            else if (result==wxNO) CloseFile(0);
            bufferList.DecrModCount();
        }
        else CloseFile(0);
    }    
    return;
}



void MyFrame::OnCloseFile_      ( wxCommandEvent& WXUNUSED(event) ) { OnCloseFile(); }
void MyFrame::OnCloseFile       ( ) {
    if (stc==0) return;
    int index = FBNotebook->GetSelection();
    Buffer* buff = bufferList[index];
    
    if (buff->GetModified())
    {
        wxString message = wxString::Format(_("The file '%s' has been modified.\n"
            "Would you like to save the changes?"),
            wxFileNameFromPath(buff->GetFileName()).c_str());

        int closeDialog = wxMessageBox(message, _("File Modified"),
            wxYES_NO | wxCANCEL | wxICON_EXCLAMATION, GetParent());

        if (closeDialog == wxYES)
            SaveFile(buff);

        else if (closeDialog == wxCANCEL)
            return;
        bufferList.DecrModCount();
    }
    
    CloseFile ( index );
    
}

void MyFrame::CloseFile          ( int index ) {

    stc->SetBuffer( (Buffer *) 0 );
    OldTabSelected = -1;
    FBNotebook->RemovePage(index);
    bufferList.RemoveBuffer(index);
    
    stc->ClearAll();
    stc->ReleaseDocument( bufferList[index]->GetDocument() );
    if (bufferList.GetBufferCount() == 0) {
        delete stc;
        stc = 0;
        FBNotebook->Hide();
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
    wxString FileName = (SaveAS) ? "" : buff->GetFileName();
    
    if (FileName==""||FileName==FBUNNAMED) {
        wxFileDialog dlg (this,
            _T("Save file"),
            _T(""),
            _T(".bas"),
            _T("FBFiles (*.bas)|*.bas|FBHeader files(*.bi)|*.bi|Any file(*)|*.*"),
            wxSAVE|wxOVERWRITE_PROMPT);
        if (dlg.ShowModal() != wxID_OK) return false;
	    FileName = dlg.GetPath();
	    if (SaveAS) {
            if(wxMessageBox("Use new file?", "Question", wxICON_QUESTION|wxYES_NO|wxNO_DEFAULT ) == wxYES)
                buff->SetFileName( FileName );
        }
        else buff->SetFileName( FileName );
    }
    
    stc->SaveFile (FileName);
    return true;
}


