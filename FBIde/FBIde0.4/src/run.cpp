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
        long data = event.GetIndex();
        wxListItem list_item; 
        list_item.SetId ( data ); 
        list_item.SetColumn ( 1 ); 
        list_item.SetMask ( wxLIST_MASK_TEXT ); 
        FBConsole->GetItem ( list_item );
        wxString File = list_item.GetText();
        
        unsigned long LineNr = 0;
        
        FBConsole->GetItemText(data).ToULong(&LineNr);
        LineNr--;
        
        GoToError(LineNr, File);
        
    }
}


void MyFrame::GoToError ( int Linenr, wxString FileName ) {
    if ( wxFileNameFromPath(FileName).Lower()!="fbidetemp.bas") {
        int result = bufferList.FileLoaded(FileName);
        if (result != -1) {
            if (FBNotebook->GetSelection()!=result) {
                FBNotebook->SetSelection(result);
            }
        }
        else
        {
            NewSTCPage(FileName, true);
        }
    }

    if (stc->GetCurrentLine()!=(int)Linenr) {
        stc->ScrollToLine((int)Linenr-(stc->LinesOnScreen()/2));
        stc->GotoLine((int)Linenr);
    
    }
    stc->SetFocus();
    stc->EnsureCaretVisible();
}

//------------------------------------------------------------------------------

void MyFrame::OnCompile (wxCommandEvent& WXUNUSED(event)) {
    if (stc==0) return;
    if (ProcessIsRunning) return;
    if (Proceed()!=1) return;
    FBConsole->DeleteAllItems();
    SetStatusText( "Compiling..." );
    if (Compile( FBNotebook->GetSelection() )==0)
        SetStatusText( "Compilation Complete." );
    else
        SetStatusText( "Compilation Failed!" );
    return;
}

void MyFrame::OnCompileAndRun (wxCommandEvent& WXUNUSED(event)) {
    if (stc==0) return;
    if (ProcessIsRunning) return;
    if (Proceed()!=1) return;
    FBConsole->DeleteAllItems();
    SetStatusText( "Compiling..." );
    if (Compile( FBNotebook->GetSelection() )==0) {
        SetStatusText( "Compilation Complete." );
        wxString strFile = bufferList[ FBNotebook->GetSelection() ]->GetCompiledFile();
        Run( strFile );
    } 
    else
        SetStatusText( "Compilation Failed!" );
   	
    return;
}

void MyFrame::OnRun (wxCommandEvent& WXUNUSED(event)) {
    if (stc==0) return;
    
    wxString strFile = bufferList[ FBNotebook->GetSelection() ]->GetCompiledFile();
    Run( strFile );
    
    return;
}


void MyFrame::OnCmdPromt (wxCommandEvent& WXUNUSED(event)) {
    int major = 0, minor = 0;
    int result = wxGetOsVersion(&major, &minor);
    if (result==wxWINDOWS_NT) wxExecute("cmd.exe");
    else if(result==wxWIN95) wxExecute("command.com");
    else wxExecute("konsole");
    return;
}

void MyFrame::OnParameters (wxCommandEvent& WXUNUSED(event)) {
    wxTextEntryDialog dialog(this, _T(Lang[177]), //"Parameters to pass to your program"
                                  _T(Lang[158]),
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

void MyFrame::OnActivePath( wxCommandEvent& WXUNUSED(event)) {
    Prefs.ActivePath = !Prefs.ActivePath;
}

int MyFrame::Proceed   	(void) {
    int index = FBNotebook->GetSelection();
    Buffer * buff = bufferList[index]; 
    
    if (buff->GetModified()) {
        if (wxMessageBox(Lang[183], 
                         Lang[184], 
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


// -----------------------------------------------------------------------------

/**
 * MyFrame::Compile
 * This function compiles given src file. It calls MyFrame::GetCompileData to
 * receave data.
 * @param index about file from buffer list
 * @return int 0 on success, 1 on failure
 */
int MyFrame::Compile ( int index ) {
    
    //Safety checks
    if ( !stc ) return 1;
    if ( ProcessIsRunning ) return 1;
    
    // File that we are about to compile
    wxFileName objFile( bufferList[ index ]->GetFileName() );
    objFile.Normalize();
    
    // Get compiler cmdline and check it. if empty return.
    wxString strCompile( GetCompileData( index ) );
    if( !strCompile.Len() ) return 1;
    
    // If Active path is activated then set current working path
    // to show to the location of the src file.
    if( Prefs.ActivePath )
        ::wxSetWorkingDirectory( objFile.GetPath() );
    
    // Execute fbc and retreave results.
    wxArrayString arrError, arrErrOutput;
    int intCompileResult = wxExecute( strCompile, arrError, arrErrOutput );
    
    // if there was an error fbc returns 1. Now get error messages and put them 
    // into console area
    if ( intCompileResult  ) {
        // define variables
        wxString        strError;
        wxString        strTemp;
        wxFileName      objErrorFile;
        long            intError;
        long            intLine;
        int             intBraceStart;
        int             intBraceEnd;
        bool            isErrorHeader = false;
        
        wxString        strDebug;
        
        // Becouse fbc returns errors via both std and error channels,
        // we need to join them here.
        WX_APPEND_ARRAY( arrError, arrErrOutput );
        
        // Loop through arrError
        for( unsigned int cnt = 0; cnt < arrError.Count(); cnt++ ) {
            if( arrError[cnt].IsEmpty() ) continue;
            
            intBraceStart = arrError[cnt].Find( '(' );
            intBraceEnd = arrError[cnt].Find( ')' );
            
            // if intBraceStart is not -1 then hopefully line number was found.
            // as fbc returns things: file(linenumber): error nr : error message
            if( intBraceStart != -1 && intBraceEnd != -1 ) {
                // Get possible file name and check if it is indeed a filename
                objErrorFile = arrError[cnt].Left( intBraceStart );
                objErrorFile.Normalize();
                if( objErrorFile.IsOk() && objErrorFile.FileExists() ) {
                    //Now that it's indeed is a filename, get line, error number
                    // and error message on that line
                    strTemp = arrError[cnt].Mid( intBraceStart + 1, intBraceEnd - intBraceStart - 1);
                    strTemp.ToLong( &intLine );
                    
                    strTemp = arrError[cnt].Mid( intBraceEnd + 10);
                    strError = strTemp.Mid( strTemp.Find( ':' ) + 2 );
                    strTemp = strTemp.Left( strTemp.Find( ':' ) );
                    strTemp.ToLong( &intError );
                    
                    isErrorHeader = true;
                }
            }
            
            // If is error header ( includes filename, error number and line number then
            // add generated values. Else just add original message.
            if( isErrorHeader ) {
                isErrorHeader = false;
                AddListItem(intLine, intError, objErrorFile.GetFullPath(), strError);
            } else {
                AddListItem(-1, -1, "", arrError[cnt]);
            }
            
        }
        
        // Open console area
        if ( !HSplitter->IsSplit() ) { 
            HSplitter->SplitHorizontally( FBCodePanel, FBConsole, ConsoleSize );
            FB_View->Check(Menu_Result, true);
        }    
        
        return 1;
    }
    
    // Close console area -if no error then it is not needed.
    if ( HSplitter->IsSplit() ) { 
        ConsoleSize = HSplitter->GetSashPosition();
        HSplitter->Unsplit( FBConsole );
        FB_View->Check(Menu_Result, false);
    }
    
    // Set newly compiled filename:
    // Note that under linux extension is missing, in windows
    // it's exe
    if( objFile.GetExt() == "bas" || objFile.GetExt() == "bi" ) {
        #ifdef __WXMSW__
            objFile.SetExt( "exe" );
        #else
            objFile.SetExt( "" );
        #endif
        bufferList[ index ]->SetCompiledFile( objFile.GetFullPath() );
    }
    
    return 0;
}



/**
 * MyFrame::Run
 * This function executes compiled file and adds optional parameters.
 * @param wxFileName file - file to be executed
 * @return none
 */
void MyFrame::Run ( wxFileName file ) {
    
    //Safety checks
    if ( !stc ) return;
    if ( ProcessIsRunning ) return;
    
    // Check if passed filename is valid. If not then it's probably not saved yet!
    if ( !file.IsOk() )  {
        if ( wxMessageBox (Lang[180], Lang[181], wxYES_NO | wxICON_QUESTION) == wxNO )
            return;
       // hack... ugly !
       wxCommandEvent temp;
       OnCompileAndRun( temp );
       return;
    }
    
    // If Active path is activated then set current working path
    // to show to the location of the src file.
    if( Prefs.ActivePath )
        ::wxSetWorkingDirectory( file.GetPath() );
    
    // Generate string that get's executed. 
    // Note that linux doesn't want filenames in quotes!
    #ifdef __WXMSW__
        wxString strCommand( "\"" + file.GetFullPath() + "\" " + ParameterList );
    #else
        wxString strCommand( file.GetFullPath() + " " + ParameterList );
    #endif
    
    
    // Create new process
    MyProcess * objProcess = new MyProcess(this, strCommand);
    
    // Execute
    int result = wxExecute( strCommand, wxEXEC_ASYNC, objProcess );
    
    // if process is not created... something is wrong!
    // Delete object, show error message and return
    if ( !result ) {
        delete objProcess;
        ProcessIsRunning = false;
        wxMessageBox ( Lang[182] + strCommand + "\"", Lang[179], wxICON_ERROR );
        return;
    }
    
    FB_Toolbar->EnableTool(Menu_Compile,        false);
    FB_Toolbar->EnableTool(Menu_CompileAndRun,  false);
    FB_Toolbar->EnableTool(Menu_Run,            false);
    FB_Toolbar->EnableTool(Menu_QuickRun,       false);
    
    FB_Run->Enable(Menu_Compile,        false);
    FB_Run->Enable(Menu_CompileAndRun,  false);
    FB_Run->Enable(Menu_Run,            false);
    FB_Run->Enable(Menu_QuickRun,       false);
    
    ProcessIsRunning = true;
    return;
    
}



/**
 * MyFrame::OnQuickRun
 * This function compiles active tab as a temorary file and executes it,
 * when execution is terminated then temporary file is deleted.
 * @return none
 */
void MyFrame::OnQuickRun (wxCommandEvent& WXUNUSED(event)) {
    
    //Safety checks
    if ( !stc ) return;
    if ( ProcessIsRunning ) return;
    
    // Get data
    int index = FBNotebook->GetSelection();
    Buffer* buff = bufferList[index];
    
    wxString OldRunFileName = buff->GetCompiledFile();
    wxString OldFileName = buff->GetFileName();
    
    // Get working directory
    if ( OldFileName == "" || OldFileName == FBUNNAMED ) {
        if( CompilerPath.Len() )
            CurFolder = ::wxPathOnly( CompilerPath );
        else
            CurFolder = ::wxPathOnly( EditorPath );
    } else {
        CurFolder = ::wxPathOnly( OldFileName );
    }
    
    CurFolder << "/";
    
    // Set new temprary data
    stc->SaveFile( CurFolder + "FBIDETEMP.bas" );
    buff->SetFileName( CurFolder + "FBIDETEMP.bas" );
    
    // Set status
    FBConsole->DeleteAllItems();
    SetStatusText( "Compiling..." );
    
    
    // Compile it
    if ( Compile( index ) == 0 ) {
        SetStatusText( "Compilation Complete." );
        Run( buff->GetCompiledFile() );
    } else {
        SetStatusText( "Compilation Failed!" );
        wxRemoveFile( CurFolder + "FBIDETEMP.bas" );
        wxRemoveFile( CurFolder + "fbidetemp.asm" );
        wxRemoveFile( CurFolder + "fbidetemp.o" );
    }

    // Restore original data
    buff->SetCompiledFile( OldRunFileName );
    buff->SetFileName( OldFileName );

    // is temprary file
    IsTemp = true;
    return;
}



/**
 * MyFrame::GetCompileData
 * Generates compildation data that is used in compilation process
 * @param index about file from buffer list
 * @return compiler cmd-line
 */
wxString MyFrame::GetCompileData ( int index ) {
    
        // Retreave file original name and validate it
    wxFileName objFilePath( bufferList[ index ]->GetFileName() );
    objFilePath.Normalize();
    if( objFilePath.GetExt() != "bas" && objFilePath.GetExt() != "bi" &&
        objFilePath.GetExt() != "rc" ) return "";    
    wxString strReturn( CMDPrototype.Lower().Trim( true ).Trim( false ) );    
    
    #ifdef __WXMSW__
        wxFileName ObjCompilerPath( CompilerPath );
        ObjCompilerPath.Normalize();
        strReturn.Replace( "<fbc>", "\"" + ObjCompilerPath.GetFullPath() + "\"" );
        strReturn.Replace( "<filename>", "\"" + objFilePath.GetFullPath() + "\"" );
    #else
        strReturn.Replace( "<fbc>", CompilerPath );
        strReturn.Replace( "<filename>", objFilePath.GetFullPath() );
    #endif
    
    return strReturn;
}

/*




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
    SetStatusText( "Compiling..." );
    if (Compile(CurFolder + "FBIDETEMP.bas")==0) {
        SetStatusText( "Compilation Complete." );
        Run();
    }
    else {
        SetStatusText( "Compilation Failed!" );
        wxRemoveFile(CurFolder + "FBIDETEMP.bas");
        wxRemoveFile(CurFolder + "fbidetemp.asm");
        wxRemoveFile(CurFolder + "fbidetemp.o");
    }

    CompiledFile = OldRunFileName;
    IsTemp=true;
    return;
}


int  MyFrame::Compile            ( wxString FileName ) {
    if (stc->GetLength()==0) {
        wxMessageBox (_(Lang[178]), _(Lang[179]));
        return 1;
    }
    
    wxString Temp=GetCompileData( FileName );
    wxString FilePath = wxPathOnly( CompiledFile );

    if (Temp=="") return false;
    
    unsigned long LineNumber = 0, errornr = 0;
    wxString NumTemp, Message;
    
    wxArrayString output, erroutput;
    int answer = wxExecute(Temp, output, erroutput);
    bool errline = false;
    
    int FirstLine = 0;
    wxString FirstFile;

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
                                if ( NumTemp.Len() )
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
                    wxFileName tf(FileName);
                    if(!tf.HasVolume()) {
                        wxString FBCPath = wxFileName(CompilerPath).GetPath(wxPATH_GET_SEPARATOR|wxPATH_GET_VOLUME);
                        if (FileName!="") {
                            if(wxFileName(FilePath+"/"+FileName).FileExists()) {
                                FileName=FilePath+"/"+FileName;
                           }
                           else if(wxFileName(FBCPath+FileName).FileExists()) {
                               FileName=FBCPath+FileName;
                           }
                           else if(wxFileName(FBCPath+"inc/"+FileName).FileExists()) {
                               FileName=FBCPath+"inc/"+FileName;
                           }
                           //else FileName=FBCPath+"inc/"+FileName;;
                        }
                        //FileName=FilePath+"/"+FileName;
                    }
                                        
                    if (FirstFile=="") {
                        FirstFile=FileName;
                        FirstLine=LineNumber;
                    }
                    
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


        if ( !HSplitter->IsSplit() ) { 
            HSplitter->SplitHorizontally( FBCodePanel, FBConsole, ConsoleSize );
            FB_View->Check(Menu_Result, true);
        }
    
        if (FirstFile!="") {
            GoToError(FirstLine-1, FirstFile);
        }
        return answer;
    }
    
    if (output.Count()) {
        for (unsigned int ii=0;ii<output.Count();ii++) {
            AddListItem(-1, -1, "", output[ii]);
        }
        
        if ( !HSplitter->IsSplit() ) { 
            HSplitter->SplitHorizontally( FBCodePanel, FBConsole, ConsoleSize );
            FB_View->Check(Menu_Result, true);
        }
        return 0;
    }
    
    if ( HSplitter->IsSplit() ) { 
        ConsoleSize = HSplitter->GetSashPosition();
        HSplitter->Unsplit( FBConsole );
        FB_View->Check(Menu_Result, false);
    }
    return 0;
}


void MyFrame::Run                ( wxString FileName ) {
    if (ProcessIsRunning) return;
    if (FileName=="") FileName = CompiledFile;
    
    if (FileName=="") {
        if (stc==0) return;
    	int Question= wxMessageBox (Lang[180],
                                  Lang[181],
                                   wxYES_NO | wxICON_QUESTION);
       if (Question==wxNO) return;
       wxCommandEvent t;
       OnCompileAndRun( t );
       return;
    }
    wxString Temp;
    Temp << "\"" + FileName << "\" " << ParameterList;
    
    MyProcess * process = new MyProcess(this, Temp);
    int m_pidLast = wxExecute(Temp, wxEXEC_ASYNC, process);
    if ( !m_pidLast )
    {
        delete process;
        ProcessIsRunning=false;
        wxMessageBox (Lang[182] + Temp + "\"", 
                      Lang[179],
                      wxICON_ERROR);
        return;
    }
    
    FB_Toolbar->EnableTool(Menu_Compile, false);
    FB_Toolbar->EnableTool(Menu_CompileAndRun, false);
    FB_Toolbar->EnableTool(Menu_Run, false);
    FB_Toolbar->EnableTool(Menu_QuickRun, false);
    
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


*/

//------------------------------------------------------------------------------

void MyProcess::OnTerminate( int pid, int status )
{
    m_parent->ProcessIsRunning = false;
    if (m_parent->Prefs.ShowExitCode) {
        wxString Temp;
        Temp<<status;
        wxMessageBox(Temp, m_parent->Lang[185]);
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
    
    m_parent->FB_Run->Enable(Menu_Compile, true);
    m_parent->FB_Run->Enable(Menu_CompileAndRun, true);
    m_parent->FB_Run->Enable(Menu_Run, true);
    m_parent->FB_Run->Enable(Menu_QuickRun, true);
    m_parent->Refresh();
    m_parent->Update();
    delete this;
}

