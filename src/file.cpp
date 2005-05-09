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

void MyFrame::OnNew (wxCommandEvent& WXUNUSED(event)) {
    NewSTCPage("", true);
    return;
}



void MyFrame::OnOpen (wxCommandEvent& WXUNUSED(event)) {
    wxFileDialog dlg (this,
        _T(Lang[186]),//Load File
        _T(""),
        _T(".bas"),
        _T(Lang[187]),//Types
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
    
    FBNotebook->SetSelection(selectpage);
    
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
            int result = wxMessageBox(Lang[188] + buff->GetFileName() + Lang[189], 
                             Lang[184],
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
        wxString message = wxString::Format(_(Lang[190]),
            wxFileNameFromPath(buff->GetFileName()).c_str());

        int closeDialog = wxMessageBox(message, _(Lang[192]), //"File Modified"
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

    if (SFDialog)       { SFDialog->Close(true); }
    if (FindDialog)     { FindDialog->Close(true); }
    if (ReplaceDialog)  { ReplaceDialog->Close(true); }
    
    stc->SetBuffer( (Buffer *) 0 );
    OldTabSelected = -1;
        
    stc->ClearAll();
    stc->ReleaseDocument( bufferList[index]->GetDocument() );
    FBNotebook->RemovePage(index);
    bufferList.RemoveBuffer(index);
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
    
    int ft = buff->GetFileType();
    
    wxString Temp = (ft==0) ? Lang[193] : Lang[200];
    Temp <<  Lang[194];

    if (FileName==""||FileName==FBUNNAMED) {
        wxFileDialog dlg (this,
            _T(Lang[195]),//Save file
            _T(""),
            _T( (ft==0) ? ".bas" : ".html" ),
            _T( Temp ),
            wxSAVE|wxOVERWRITE_PROMPT);
        if (dlg.ShowModal() != wxID_OK) return false;
	    FileName = dlg.GetPath();
	    if (SaveAS) {
            if(wxMessageBox(Lang[196], Lang[197], wxICON_QUESTION|wxYES_NO|wxNO_DEFAULT ) == wxYES)
                buff->SetFileName( FileName );
        }
        else { buff->SetFileName( FileName ); }
    }
    
    stc->SaveFile (FileName);
    return true;
}



void MyFrame::OnSessionLoad      ( wxCommandEvent& event ) {
    wxFileDialog dlg (this,
        _T(Lang[186]), //Load file
        _T(""),
        _T(".bas"),
        _T(Lang[198]), //FBIde Session
    wxFILE_MUST_EXIST | wxCHANGE_DIR);
    if (dlg.ShowModal() != wxID_OK) return;
    wxString File = dlg.GetPath();
    
    SessionLoad(File);
}

void MyFrame::SessionLoad ( wxString File ) {

    wxTextFile TextFile(File);
    TextFile.Open();
    if(TextFile.GetLineCount()==0) return;
    
    wxString Temp;
    int result = 0;
    unsigned long selectedtab = 0;    
    
    for( unsigned int i=1; i< TextFile.GetLineCount();i++ ) {
        Temp = TextFile[i];
        if(Temp!=""&&wxFileExists(Temp)) {
            result = bufferList.FileLoaded(Temp);
            if (result == -1) NewSTCPage(Temp, false);
        }
    }
    
    Temp=TextFile[0];
    Temp.ToULong(&selectedtab);
    
    FBNotebook->SetSelection(selectedtab);
    
    TextFile.Close();
    
    return;
}


void MyFrame::OnSessionSave      ( wxCommandEvent& event ) {
    if (stc==0) return;
    
    wxString FileName;
    
    wxFileDialog dlg (this,
        _T(Lang[199]),
        _T(""),
        _T(".fbs"),
        _T(Lang[198]),
        wxSAVE|wxOVERWRITE_PROMPT);
    if (dlg.ShowModal() != wxID_OK) return;
    FileName = dlg.GetPath();
    
    wxTextFile TextFile(FileName);
    if (TextFile.Exists()) { TextFile.Open(); TextFile.Clear(); }
    else { TextFile.Create(); }
    
    Buffer* buff;
    bool session = false;
    bool header = true;
    
    int SelectedTab = FBNotebook->GetSelection();
    
    for (unsigned int i=0; i < FBNotebook->GetPageCount();i++ ) {
        buff = bufferList[i];
        if (buff->GetModified()) {
            FBNotebook->SetSelection(i);
            int result = wxMessageBox(Lang[188] + buff->GetFileName() + Lang[189], 
                             Lang[184],
                             wxYES_NO | wxCANCEL | wxICON_EXCLAMATION);
            if (result==wxCANCEL) return;
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
        else { session = true; }
        
        if ( session && buff->GetFileName()!=FBUNNAMED ) {
            if (header) {
                header = false;
                wxString t;
                t << SelectedTab;
                TextFile.AddLine(t);
            }
            session = false;
            TextFile.AddLine(buff->GetFileName());
        }
    } 
    
    FBNotebook->SetSelection(SelectedTab);
    
    if(TextFile.GetLineCount()) {
        TextFile.Write();
    }
    
    TextFile.Close();
    
    return;
}
