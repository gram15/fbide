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
    
    wxFileName w(dlg.GetPath());    //Format filename
    w.Normalize();
    Document = w.GetFullPath();
    NewSTCPage(Document, true);

    return;
}



void MyFrame::OnSave (wxCommandEvent& WXUNUSED(event)) {
    if (stc==0) return;
    SaveFile(stc->DocumentName);
    wxFileName w(stc->DocumentName);
    FBNotebook->SetPageText(FBNotebook->GetSelection(), w.GetFullName());
    return;
}



void MyFrame::OnSaveAs (wxCommandEvent& WXUNUSED(event)) {
    if (stc==0) return;
    SaveFile("");
    wxFileName w(stc->DocumentName);
    FBNotebook->SetPageText(FBNotebook->GetSelection(), w.GetFullName());
    return;
}

void MyFrame::OnSaveAll (wxCommandEvent& WXUNUSED(event)) {
    if (stc==0) return;
    return;
}



void MyFrame::OnCloseFile (wxCommandEvent& WXUNUSED(event)) {

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
            SaveFile(buff->GetFileName());

        else if (closeDialog == wxCANCEL)
            return;
    }
    
    OldTabSelected = -1;
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
}
    


void MyFrame::OnQuit (wxCommandEvent &WXUNUSED(event)) {
   Close(true);
}



void MyFrame::OnNewWindow     (wxCommandEvent &WXUNUSED(event)) {
   wxExecute (FB_App->argv[0]);
   return;
}


//----------------------------------------------------------------------------



int MyFrame::Proceed   	(void) {
    if (stc==0) return 1;
    if (stc->GetModify()||IDE_Modified) {
        if (stc->GetLength()) {
            wxString Temp;
            wxString FileName;
            if (Document==FBUNNAMED||Document=="") {
                Temp="Save file?";
            }
            else {
                Temp ="Save changes to \"";
                Temp+=Document;
                Temp+="\"?";
            }
            int Question= wxMessageBox (_(Temp), _("Confirm"),
                wxYES_NO | wxCANCEL | wxICON_QUESTION);
            
            if (Question==wxNO) return 2;
            else if (Question==wxCANCEL) return 0;
            if (!SaveFile(Document)) return 0;
        }
    }
    IDE_Modified=false;
    return 1;
}



bool MyFrame::SaveFile (wxString FileName) {
    
    if (FileName==""||FileName==FBUNNAMED) {
        wxFileDialog dlg (this,
            _T("Save file"),
            _T(""),
            _T(".bas"),
            _T("FBFiles (*.bas)|*.bas|FBHeader files(*.bi)|*.bi|Any file(*)|*.*"),
            wxSAVE|wxOVERWRITE_PROMPT);
        if (dlg.ShowModal() != wxID_OK) return false;
	    FileName = dlg.GetPath();
    }
    
    wxFileName w (FileName); 	//Format filename
    w.Normalize();
    FileName = w.GetFullPath();
    stc->DocumentName = FileName;
    stc->SaveFile (FileName);
    Document=FileName;
    return true;
}


