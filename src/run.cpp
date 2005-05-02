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
#include <wx/process.h>

class MyProcess : public wxProcess
{
public:
    MyProcess(MyFrame *parent, const wxString& cmd)
        : wxProcess(parent), m_cmd(cmd)
    {
        m_parent = parent;
    }

    // instead of overriding this virtual function we might as well process the
    // event from it in the frame class - this might be more convenient in some
    // cases
    virtual void OnTerminate(int pid, int status);

protected:
    MyFrame *m_parent;
    wxString m_cmd;
};


void MyFrame::AddListItem ( int Linenr, int ErrorNr, wxString FileName, wxString Message ) {

    // FBConsole is a pointer to wxListCtrl control
    
    Message=Message.Trim(true).Trim(false);
    wxString lnr;
    if (Linenr!=-1)
        lnr << Linenr;
    int Itemcount = FBConsole->GetItemCount();
    long tmp = FBConsole->InsertItem(Itemcount, lnr, 0);
    FBConsole->SetItemData(tmp, 0);
    FBConsole->SetItem(Itemcount, 1, FileName);
    lnr = "";
    if (ErrorNr!=-1)
        lnr << ErrorNr;
    FBConsole->SetItem(Itemcount, 2, lnr);
    FBConsole->SetItem(Itemcount, 3, Message);
}


void MyFrame::OnGoToError ( wxListEvent& event ) {
    if (stc==0) return;
    //int idx = event.GetData();

    if(event.GetText().Len()) {
        //wxMessageBox(event.GetText());
        long data = event.GetIndex();
        unsigned long LineNr = 0;
        FBConsole->GetItemText(data).ToULong(&LineNr);
        LineNr--;
        if (stc->GetLineVisible((int)LineNr)==false)
            stc->GotoLine(0);
        if (stc->GetCurrentLine()!=(int)LineNr)
            stc->GotoLine((int)LineNr);
        stc->SetFocus();
        
    }
}


void MyFrame::OnCompile (wxCommandEvent& WXUNUSED(event)) {
    if (stc==0) return;
    if (ProcessIsRunning) return;
    if (Proceed()!=1) return;
    FBConsole->DeleteAllItems();
    Compile();
    return;
}

void MyFrame::OnCompileAndRun (wxCommandEvent& WXUNUSED(event)) {
    if (stc==0) return;
    if (ProcessIsRunning) return;
    if (Proceed()!=1) return;
    FBConsole->DeleteAllItems();
    if (Compile()==0)
   	    Run();
    return;
}

void MyFrame::OnRun (wxCommandEvent& WXUNUSED(event)) {
    if (stc==0) return;
    Run();
    return;
}

void MyFrame::OnQuickRun (wxCommandEvent& WXUNUSED(event)) {
    if (stc==0) return;
    if (ProcessIsRunning) return;
    
    int index = FBNotebook->GetSelection();
    Buffer* buff = bufferList[index];
    
    wxString OldRunFileName = CompiledFile;
    if (buff->GetFileName()==""||buff->GetFileName()==FBUNNAMED) {
        wxFileName w(FB_App->argv[0]);
        CurFolder = w.GetPath(wxPATH_GET_SEPARATOR|wxPATH_GET_VOLUME);
    }
    else {
        wxFileName w(buff->GetFileName());
        CurFolder = w.GetPath(wxPATH_GET_SEPARATOR|wxPATH_GET_VOLUME);
    }

    stc->SaveFile (CurFolder + "FBIDETEMP.bas");
    FBConsole->DeleteAllItems();

    if (Compile(CurFolder + "FBIDETEMP.bas")==0) Run();
    else {
        wxRemoveFile(CurFolder + "FBIDETEMP.bas");
        wxRemoveFile(CurFolder + "fbidetemp.asm");
        wxRemoveFile(CurFolder + "fbidetemp.o");
    }

    CompiledFile = OldRunFileName;
    IsTemp=true;
    return;
}

void MyFrame::OnCmdPromt (wxCommandEvent& WXUNUSED(event)) {
    wxString OS=wxGetOsDescription();
    if (OS.Find("NT")) wxExecute("cmd.exe");
    else wxExecute("command.com");
    return;
}

void MyFrame::OnParameters (wxCommandEvent& WXUNUSED(event)) {
    wxTextEntryDialog dialog(this, _T("Parameters to pass to your program"),
                                  _T("Parameters..."),
                                  _T(ParameterList),
                           wxOK | wxCANCEL);
    
    if (dialog.ShowModal() == wxID_OK)
    {
    ParameterList = dialog.GetValue();
    }   
    return;
}

void MyFrame::OnShowExitCode (wxCommandEvent& WXUNUSED(event)) {
    Prefs.ShowExitCode = !Prefs.ShowExitCode;
    return;
}

int  MyFrame::Compile            ( wxString FileName ) {
    if (stc->GetLength()==0) {
        wxMessageBox (_("Nothing to compile!"), _("Error"));
        return 1;
    }
    
    wxString Temp=GetCompileData( FileName );
    if (Temp=="") return false;
    
    unsigned long LineNumber = 0, errornr = 0;
    wxString NumTemp, Message;
    
    wxArrayString output, erroutput;
    int answer = wxExecute(Temp, output, erroutput);
    bool errline = false;

    if (answer!=0) {
        Temp="";

        if (output.Count()) {
            for (unsigned int ii=0;ii<output.Count();ii++) {
                Temp = output[ii];
                for (unsigned int i=0; i<Temp.Len();i++) {
                    NumTemp = "";
                    unsigned int x = 0;
                    if (Temp.Mid(i,1)=="(") {
                        for (x=i+1;x<Temp.Len();x++) {
                   	        if (Temp.Mid(x,1)==")") {
                                errline = true;
                                break;
                            }
                            NumTemp+=Temp.Mid(x,1);
                        }
                        if (errline) {
                            
                            if (!NumTemp.IsNumber()) {
                                errline = false;
                                break;
                            }
                            NumTemp.ToULong(&LineNumber);
                            FileName = Temp.Left(i);
                            x+=10;
                            NumTemp="";
                            for (;x<Temp.Len();x++) {
                   	            if (Temp.Mid(x,1)==":") break;
                                NumTemp+=Temp.Mid(x,1);
                            }
                            if (x==Temp.Len()) {
                                errline = false;
                                break;
                            }
                            if (!NumTemp.IsNumber()) {
                                errline = false;
                                break;
                            }
                            NumTemp.ToULong(&errornr);
                            Message = Temp.Mid(x+2);
                            break;
                        }
                    }
                }
                if (errline) {
                    AddListItem(LineNumber, errornr, FileName, Message);
                    if ( output[ii+1].Len() )
                        AddListItem(-1, -1, "", output[ii+1]);
                    if ( output[ii+2].Len() )
                        AddListItem(-1, -1, "", output[ii+2]);
                    if ( output[ii+3].Len() )
                        AddListItem(-1, -1, "", output[ii+3]);
                    ii+=3;
                }
                else AddListItem(-1, -1, "", output[ii]);
                errline = false;
            } //for
        } //end output.Count()
        
        if (erroutput.Count()) {
            for (unsigned int ii=0;ii<erroutput.Count();ii++) {
                AddListItem(-1, -1, "", erroutput[ii]);
            }
        }
                    
        if (!FBConsole->IsShown()) {
            FB_View->Check(Menu_Result, true);
            FBConsole->Show();
            s_Code->Add(s_Console, 0,  wxEXPAND | wxALL, 0);
            s_Code->Layout();
        }
        return answer;
    }
    
    if (output.Count()) {
        for (unsigned int ii=0;ii<output.Count();ii++) {
            AddListItem(-1, -1, "", output[ii]);
        }
        
        if (!FBConsole->IsShown()) {
            FB_View->Check(Menu_Result, true);
            FBConsole->Show();
            s_Code->Add(s_Console, 0,  wxEXPAND | wxALL, 0);
            s_Code->Layout();
        }
    }
        
    return 0;
}


void MyFrame::Run                ( wxString FileName ) {
    if (ProcessIsRunning) return;
    if (FileName=="") FileName = CompiledFile;
    
    if (FileName=="") {
        if (stc==0) return;
    	int Question= wxMessageBox ("You need first to compile the program before you can run! Compile?",
                                  "Compile?",
                                   wxYES_NO | wxICON_QUESTION);
       if (Question==wxNO) return;
       if (Compile()!=0)   return;
    }
    wxString Temp;
    Temp<<FileName<<" "<<ParameterList;
    
    MyProcess * process = new MyProcess(this, Temp);
    int m_pidLast = wxExecute(Temp, wxEXEC_ASYNC, process);
    if ( !m_pidLast )
    {
        delete process;
        ProcessIsRunning=false;
        wxMessageBox ("An error occured when trying to rin \"" + Temp + "\"", 
                      "Error",
                      wxICON_ERROR);
        return;
    }
    
    FB_Toolbar->EnableTool(Menu_Compile, false);
    FB_Toolbar->EnableTool(Menu_CompileAndRun, false);
    FB_Toolbar->EnableTool(Menu_Run, false);
    FB_Toolbar->EnableTool(Menu_QuickRun, false);
    FB_Toolbar->Realize();
    
    FB_Run->Enable(Menu_Compile, false);
    FB_Run->Enable(Menu_CompileAndRun, false);
    FB_Run->Enable(Menu_Run, false);
    FB_Run->Enable(Menu_QuickRun, false);
    
    ProcessIsRunning=true;
    return;
}


wxString MyFrame::GetCompileData ( wxString FileName ) {
    wxString Cmd;
    wxString Temp;
    wxString TempCmdPath;
    wxString MetaCommand;
    
    int index = FBNotebook->GetSelection();
    Buffer * buff = bufferList[index];
    
    if (FileName=="") FileName = buff->GetFileName();
    
    Temp=CMDPrototype;
    Temp=Temp.Trim(false).Lower();
    
    bool check=false;
    bool eliminateSpaces=false;
    CompiledFile="";

    TempCmdPath = CompilerPath;

    if (Temp.Len()>0) {
        for (unsigned int i=0;i<Temp.Len()+1;i++) {

            if (Temp.Mid(i,1)==" ") {
                if (eliminateSpaces==true) continue;
                eliminateSpaces=true;
            }
            else eliminateSpaces=false;

            if (Temp.Mid(i,1)=="<" || Temp.Mid(i,1)==">") {
         	  check=!check;
         	  continue;
            }

        	if (check) {
        	   MetaCommand+=Temp.Mid(i,1);
        	   continue;
        	}

            if (Temp.Mid(i,3)=="-x ") {
                bool terminate=false;
                for (unsigned int x=i+3 ; x<Temp.Len()+1;x++) {
                    if (Temp.Mid(x,1)==" ") {
                        if (terminate==false)continue;
                    }
                    terminate=true;
                    if (Temp.Mid(x,1)==" ") break;
                    CompiledFile+=Temp.Mid(x,1);
                }
            }

            MetaCommand=MetaCommand.Trim(true).Trim(false);
            if (MetaCommand>"") {
                if (MetaCommand=="fbc") Cmd+=TempCmdPath;
                else if (MetaCommand=="filename") {
                    Cmd<<"\"" << FileName << "\"";
                }
                MetaCommand="";
                Cmd+=" ";
            }
            Cmd+=Temp.Mid(i,1);
        }
    }
    else {
        Cmd = "";
  		Cmd << TempCmdPath << " \"" << FileName << "\"";
    }

    if (CompiledFile=="") {
        Temp=FileName;
        Temp=Temp.Trim(true).Trim(false).Lower();
        if (Temp.Right(4)==".bas") {
            CompiledFile=Temp.Left(Temp.Len()-4);
            CompiledFile+=".exe";
        }
    }
	return Cmd;
}


int MyFrame::Proceed   	(void) {
    int index = FBNotebook->GetSelection();
    Buffer * buff = bufferList[index]; 
    
    if (buff->GetModified()) {
        if (wxMessageBox("File is modified and to contrinue needs to be save!", 
                         "Save file?", 
                         wxICON_EXCLAMATION|wxYES_NO) == wxYES) {
            if (SaveFile(buff)) {
                SetModified ( index, false );
                return 1;
            }
        }
        return 0;
    }
    return 1;
}


void MyProcess::OnTerminate(int pid, int status)
{
    m_parent->ProcessIsRunning=false;
    if (m_parent->Prefs.ShowExitCode) {
        wxString Temp;
        Temp<<status;
        wxMessageBox(Temp, "ExitCode");
    }
    if (m_parent->IsTemp) {
         wxRemoveFile(m_parent->CurFolder + "FBIDETEMP.bas");
         wxRemoveFile(m_parent->CurFolder + "FBIDETEMP.exe");
         m_parent->IsTemp=false;
    }
    m_parent->Raise();
    m_parent->SetFocus();
    m_parent->stc->SetFocus();
    
    m_parent->FB_Toolbar->EnableTool(Menu_Compile, true);
    m_parent->FB_Toolbar->EnableTool(Menu_CompileAndRun, true);
    m_parent->FB_Toolbar->EnableTool(Menu_Run, true);
    m_parent->FB_Toolbar->EnableTool(Menu_QuickRun, true);
    m_parent->FB_Toolbar->Realize();
    
    m_parent->FB_Run->Enable(Menu_Compile, true);
    m_parent->FB_Run->Enable(Menu_CompileAndRun, true);
    m_parent->FB_Run->Enable(Menu_Run, true);
    m_parent->FB_Run->Enable(Menu_QuickRun, true);
    
    delete this;
}

