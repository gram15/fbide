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
#include "inc/format.h"

format::format(wxWindow* parent,wxWindowID id,const wxString& title,const wxPoint& pos,const wxSize& size,long style,const wxString& name)
VwX_INIT_OBJECTS_format
{
    Parent = ( MyFrame * ) parent;
    Create(parent,id,title,pos,size,style,name);
    
    if((pos==wxDefaultPosition)&&(size==wxDefaultSize)){
        SetSize(0,0,405,210);
    }
    
    if((pos!=wxDefaultPosition)&&(size==wxDefaultSize)){
        SetSize(405,210);
    }
    VwXinit();
}


format::~format()
{
    Parent->formatDialog=0;
}


void format::VwXinit()
{
    st5=new wxStaticText(this,-1,wxT(""),wxPoint(33,11),wxSize(218,19),wxST_NO_AUTORESIZE);
    st5->SetLabel(wxT(Parent->Lang[162])); //"Type of conversion:"
    
    lno6=new wxStaticLine(this,-1,wxPoint(29,32),wxSize(234,1));
 
    button_ok=new wxButton(this,-1,wxT(""),wxPoint(275,31),wxSize(93,24));
    button_ok->SetLabel(wxT(Parent->Lang[163])); //"Go!"
    
    sb9=new wxStaticBox(this,-1,wxT(""),wxPoint(20,117),wxSize(335,53));
    sb9->SetTitle(wxT(Parent->Lang[164])); //"Preview!"
    
    preview=new wxStaticText(this,-1,wxT(""),wxPoint(30,145),wxSize(45,13));
    preview->SetLabel(wxT("Cls:Locate 1,1:Print \"\""));
    
    wxString choices[]={"KeyWords","KEYWORDS","keywords","BBCode","HTML"};
    chc15=new wxChoice(this,-1,wxPoint(31,37),wxSize(214,21),5,choices);
    chc15->SetSelection(0);
    
    bt16=new wxButton(this,-1,wxT(""),wxPoint(275,61),wxSize(93,24));
    bt16->SetLabel(wxT(Parent->Lang[3]));
    bt17=new wxButton(this,-1,wxT(""),wxPoint(275,91),wxSize(93,24));
    bt17->SetLabel(wxT(Parent->Lang[112]));
    
    Refresh();
    Centre();
}

BEGIN_EVENT_TABLE(formatEvt,wxEvtHandler)

END_EVENT_TABLE()

BEGIN_EVENT_TABLE( format,wxDialog)
    EVT_BUTTON(-1,format::VwXVwXEvOnButtonClick)
    EVT_CHOICE(-1,format::VwXVwXEvOnChoiceSelect)
    EVT_CLOSE(format::OnClose)
END_EVENT_TABLE()


void format::VwXVwXEvOnChoiceSelect(wxCommandEvent& event){
     wxObject *m_wxWin = event.m_eventObject ;
     if(m_wxWin==chc15){chc15_VwXEvOnChoiceSelect(event,-1);return;}
     event.Skip(true);
}

void format::VwXVwXEvOnButtonClick(wxCommandEvent& event){
     wxObject *m_wxWin = event.m_eventObject ;
     if(m_wxWin==bt16){bt16_VwXEvOnButtonClick(event,-1);return;}
     if(m_wxWin==bt17){bt17_VwXEvOnButtonClick(event,-1);return;}
     if(m_wxWin==button_ok){button_ok_VwXEvOnButtonClick(event,-1);return;}
     event.Skip(true);
}

//[evtFunc]add your code here

void format::bt17_VwXEvOnButtonClick(wxCommandEvent& event,int index){ //init function
     //[64b]Code event VwX...Don't modify[64a]//
     //add your code here
     FB_Edit * stc = Parent->stc;
     stc->BeginUndoAction();
         for(int i=0;i<stc->GetLineCount();i++)
         {
                //wxString line=Parent->stc->GetLine(i).Trim(false).Trim(true);
                int cLine=i;
                int lineInd=stc->GetLineIndentation(cLine-1);
                int plineind=stc->GetLineIndentation(cLine-2);
                int TabSize=Parent->Prefs.TabSize;
                
                //Previous line
                wxString TempCL=stc->ClearCmdLine(stc->GetLine(cLine-1));
                wxString clfkw=stc->GetFirstKw(TempCL);
                wxString cllkw=stc->GetLastKw(TempCL);
                
                //Line before previous
                wxString TempPL=stc->ClearCmdLine(stc->GetLine(cLine-2));
                wxString plfkw=stc->GetFirstKw(TempPL);
                wxString pllkw=stc->GetLastKw(TempPL);
                
                
                if (lineInd>0) {
                    if ( clfkw == "end" && stc->IsEndDeIndentWord(cllkw) ) {
                        if (cllkw!=plfkw) { 
                            if (cllkw == "select" && plfkw == "case") lineInd = plineind;
                            else if (plineind<=lineInd) lineInd -= TabSize; 
                        }
                        else if (cllkw=="function" && TempPL.Find('=')!=-1) lineInd -= TabSize;
                        else if (plfkw == "if" && pllkw!="then") {
                            if (plineind<=lineInd) lineInd -= TabSize; }
                            else lineInd = plineind;
                        }
                        else if (clfkw != pllkw) {
                            if (( clfkw == "next" && plfkw != "for")||
                                ( clfkw == "loop" && plfkw != "do")||
                                ( clfkw == "wend" && plfkw != "while")) {
                                if (plineind<=lineInd) lineInd -= TabSize;
                            }
                            else if (( clfkw == "next" && plfkw == "for")||
                                     ( clfkw == "loop" && plfkw == "do")||
                                     ( clfkw == "wend" && plfkw == "while"))
                                     lineInd = plineind;
                            else if ( clfkw == "case" ) {
                                 if (plfkw == "case" || plfkw == "select") { lineInd = plineind; }
                                 else  { if (plineind<=lineInd) lineInd -= TabSize; }
                            }
                            else if ( clfkw == "else" || clfkw == "elseif" ) {
                                 if ((plfkw == "if" && pllkw == "then") ||
                                     (plfkw == "elseif")) { lineInd = plineind; } 
                                 else {
                                      if (plineind<=lineInd) lineInd -= TabSize;
                                 }
                            }              
                        }
                        else if(clfkw == "next" && plfkw != "for")
                            if (plineind<=lineInd) lineInd -= TabSize;
                    stc->SetLineIndentation (cLine-1, lineInd);
                }  
                if (stc->IsIndentWord(clfkw)) {
                    if (clfkw == "if") {
                        if (cllkw == "then") lineInd += TabSize;
                    }
                    else if (clfkw == "do") {
                        if (cllkw != "loop") lineInd += TabSize;
                    }
                    else if (clfkw == "while") {
                        if (cllkw != "wend") lineInd += TabSize;
                    }
                    else if (clfkw == "type") {
                        if ((!TempCL.Contains(" as "))&&(!TempCL.Contains("\tas "))&&
                            (!TempCL.Contains(" as\t"))&&(!TempCL.Contains("\tas\t")))
                            lineInd += TabSize;
                    }
                    else if (clfkw=="function") {
                        if (TempCL.Find('=')==-1) lineInd += TabSize;
                    }
                    else  lineInd += TabSize;
                }  
                stc->SetLineIndentation (cLine, lineInd);
                //Parent->stc->GotoPos(PositionFromLine (cLine) + lineInd);
         }
    stc->EndUndoAction();
} //end function

void format::chc15_VwXEvOnChoiceSelect(wxCommandEvent& event,int index){ //init function
     //[4a9]Code event VwX...Don't modify[4a8]//
     //add your code here
     switch(chc15->GetSelection())
     {
         case 0:
              preview->SetLabel("Cls:Locate 1,1:Print \"\"");
              break;
         case 1:
              preview->SetLabel("CLS:a$=MID$(\"1234\",1)");
              break;
         case 2:
              preview->SetLabel("cls:locate 1,1:print \"\"");
              break;
         case 3:
              preview->SetLabel("[b]cls[/b]:[b]locate[/b] 1,1");
              break;
         case 4:
              preview->SetLabel("<b>cls</b>:<b>locate</b> 1,1");
              break;
     }
} //end function

void format::bt16_VwXEvOnButtonClick(wxCommandEvent& event,int index){ //init function
     //[4aa]Code event VwX...Don't modify[4a9]//
     //add your code here
     Close(true);
} //end function

void format::button_ok_VwXEvOnButtonClick(wxCommandEvent& event,int index){ //init function
     //[3d7]Code event VwX...Don't modify[3d6]//
     //add your code here
     //here's where i write the conversion $h17....

     FB_Edit * stc = Parent->stc;
     int idx = Parent->FBNotebook->GetSelection();
     Buffer * buff = Parent->bufferList[idx];
     
     if (buff->GetFileType()>0) return;
     
     wxString guts=Parent->stc->GetText(),tagstart="",tagend="";
     int sel=chc15->GetSelection();
     bool dotags=false,dokeyws=false;
     wxString output="";
     StyleInfo * Style = &(Parent->Style);
     switch(sel)
     {
        case 0:
             dokeyws=true;
             break;
        case 1:
             dokeyws=true;
             break;
        case 2:
             dokeyws=true;
             break;
        case 3:
             dotags=true;
             tagstart="[";
             tagend="]";
             output="[quote=\"fbide 0.4 bbcode generator\"][size=12]";
             break;
        case 4:
             dotags=true;
             tagstart="<";
             tagend=">";
             output="<!DOCTYPE html PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\">\n<html>\n<head>\n<meta http-equiv=\"content-type\" content=\"text/html;charset=iso-8859-1\">\n<title></title>\n</head>\n<body style=\"font-size:12pt; background-color:#"+hex(GetClr(Style->DefaultBgColour))+"; color:#"+hex(GetClr(Style->Info[wxSTC_B_IDENTIFIER].foreground))+"\"><pre>";
             break;
     }
     wxString curword="";
     initkeywords();
     int kwtyp=0;
     bool commenting=false,dontadd=false,quoting=false,bold=false,italic=false;
     
     wxString colours[]={hex(GetClr(Style->Info[wxSTC_B_KEYWORD].foreground)),
                         hex(GetClr(Style->Info[wxSTC_B_KEYWORD2].foreground)),
                         hex(GetClr(Style->Info[wxSTC_B_KEYWORD3].foreground)),
                         hex(GetClr(Style->Info[wxSTC_B_KEYWORD4].foreground)),
                         hex(GetClr(Style->Info[wxSTC_B_COMMENT].foreground)),
                         hex(GetClr(Style->Info[wxSTC_B_OPERATOR].foreground)),
                         hex(GetClr(Style->Info[wxSTC_B_STRING].foreground)),
                         hex(GetClr(Style->Info[wxSTC_B_NUMBER].foreground)),
                         hex(GetClr(Style->Info[wxSTC_B_PREPROCESSOR].foreground))};
     int teh_len=(int)guts.Len(),real_len=(int)guts.Len(),color=-1;
     for(int i=0;i<teh_len;i++)
     {
         unsigned char j00_n00b=guts.GetChar(i);
         curword+=j00_n00b;
         if(j00_n00b!=38&&
            (j00_n00b>0&&j00_n00b<46)||
            j00_n00b==47||
            (j00_n00b>57&&j00_n00b<65)||
            (j00_n00b>90&&j00_n00b<95)||
            j00_n00b==96||
            (j00_n00b>122&&j00_n00b<128))
         {
             curword=curword.Left(curword.Len()-1);
             if(dotags&&!commenting&&!quoting&&(kwtyp=isKeyword(curword))!=0)
             {
                 if(color!=kwtyp-1)
                 {
                     if(color!=-1) output+=tagstart+(sel==4?"/span":"/color")+tagend;
                     if(bold) output+=tagstart+"/b"+tagend;
                     if(italic) output+=tagstart+"/i"+tagend;
                     output+=tagstart+"b"+tagend+tagstart+(sel==4?"span style=\"color:#":"color=#")+colours[kwtyp-1]+ \
                         (sel==4?"\"":"")+tagend+curword+(dontadd?"":wxString::Format("%c",j00_n00b));
                 }
                 else
                     output+=curword+(dontadd?"":wxString::Format("%c",j00_n00b));
                 color=kwtyp-1;
                 bold=true;
                 italic=false;
             }
             else if(dotags&&!commenting&&!quoting&&isNumeric(curword))
             {
                 if(color!=7)
                 {
                     if(color!=-1) output+=tagstart+(sel==4?"/span":"/color")+tagend;
                     if(bold) output+=tagstart+"/b"+tagend;
                     if(italic) output+=tagstart+"/i"+tagend;
                     output+=tagstart+(sel==4?"span style=\"color:#":"color=#")+colours[7]+ \
                         (sel==4?"\"":"")+tagend+curword+(dontadd?"":wxString::Format("%c",j00_n00b));
                 }
                 else
                     output+=curword+(dontadd?"":wxString::Format("%c",j00_n00b));
                 color=7;
                 bold=false;
                 italic=false;
             }
             else if(dokeyws&&!commenting&&!quoting&&isKeyword(curword)!=0)
             {
                 switch(sel)
                 {
                      case 0:
                          curword=curword.Left(1).MakeUpper()+curword.Mid(1).MakeLower();
                          break;
                      case 1:
                           curword=curword.MakeUpper();
                           break;
                      case 2:
                           curword=curword.MakeLower();
                           break;
                 }
                 output+=curword+(dontadd?"":wxString::Format("%c",j00_n00b));
             }
             else
             {
                 if(!commenting&&!quoting)
                 {
                     if(color!=-1) output+=tagstart+(sel==4?"/span":"/color")+tagend;
                     if(bold) output+=tagstart+"/b"+tagend;
                     if(italic) output+=tagstart+"/i"+tagend;
                     color=-1;
                 }
                 bold=false;
                 italic=false;
                 output+=curword+(dontadd?"":wxString::Format("%c",j00_n00b));
             }
             curword="";
             int mylen=output.Len();
             if(!commenting&&!quoting&&j00_n00b=='\'')
             {
                 commenting=true;
                 if(dotags)
                 {
                     output=output.Left(mylen-1);
                     if(color!=-1) output+=tagstart+(sel==4?"/span":"/color")+tagend;
                     if(bold) output+=tagstart+"/b"+tagend;
                     if(italic) output+=tagstart+"/i"+tagend;
                     output+=tagstart+"i"+tagend+tagstart+(sel==4?"span style=\"color:#":"color=#")+colours[4]+ \
                     (sel==4?"\"":"")+tagend;
                     output+=j00_n00b;
                 }
             }
             else if((j00_n00b=='\n'||j00_n00b=='\r')&&commenting)
             {
                 commenting=false;
                 color=-1;
                 bold=false;
                 italic=false;
                 if(dotags)
                 {
                     output=output.Left(mylen-1);
                     output+=tagstart+(sel==4?"/span":"/color")+tagend+tagstart+"/i"+tagend;
                     output+=j00_n00b;
                 }
             }
             if(!commenting&&!quoting&&j00_n00b=='\"')
             {
                 if(dotags)
                 {
                     output=output.Left(mylen-1);
                     if(color!=-1) output+=tagstart+(sel==4?"/span":"/color")+tagend;
                     if(bold) output+=tagstart+"/b"+tagend;
                     if(italic) output+=tagstart+"/i"+tagend;
                     output+=tagstart+(sel==4?"span style=\"color:#":"color=#")+colours[6]+ \
                             (sel==4?"\"":"")+tagend;
                     output+=j00_n00b;
                 }
                 quoting=true;
             }
             else if((j00_n00b=='\"'||j00_n00b=='\n'||j00_n00b=='\r')&&quoting)
             {
                 quoting=false;
                 color=-1;
                 bold=false;
                 italic=false;
                 if(dotags) output+=tagstart+(sel==4?"/span":"/color")+tagend;
             }
             if(!commenting&&!quoting&&j00_n00b=='#'&&(i==0||(output.Mid(output.Len()-2,1)=="\n"||output.Mid(output.Len()-2,1)=="\r")))
             {
                 output=output.Left(mylen-1);
                 if(color!=-1) output+=tagstart+(sel==4?"/span":"/color")+tagend;
                 if(bold) output+=tagstart+"/b"+tagend;
                 if(italic) output+=tagstart+"/i"+tagend;
                 color=-1; bold=false; italic=false;
                 if(dotags) output+=tagstart+(sel==4?"span style=\"color:#":"color=#")+colours[8]+ \
                        (sel==4?"\"":"")+tagend;
                        output+=j00_n00b;
                 for(i++;guts.GetChar(i)!='\r'&&guts.GetChar(i)!='\n'&&i<teh_len;i++)
                 {
                     output+=guts.Mid(i,1);
                 }
                 if(dotags) output << tagstart+(sel==4?"/span":"/color")+tagend << guts.GetChar(i);
             }
             else if(dotags&&!commenting&&!quoting&&j00_n00b=='#')
             {
                 output=output.Left(mylen-1);
                 output+=tagstart+"b"+tagend+tagstart+(sel==4?"span style=\"color:#":"color=#")+colours[5]+ \
                         (sel==4?"\"":"")+tagend;
                 output+=j00_n00b;
                 output+=tagstart+(sel==4?"/span":"/color")+tagend+tagstart+"/b"+tagend;
             }
             if(dotags&&((j00_n00b>39&&j00_n00b<46)||j00_n00b==47||
                (j00_n00b>57&&j00_n00b<64)||j00_n00b==92||j00_n00b==94||
                (j00_n00b>122&&j00_n00b<128))&&!commenting&&!quoting)
             {
                 output=output.Left(mylen-1);
                 output+=tagstart+"b"+tagend+tagstart+(sel==4?"span style=\"color:#":"color=#")+colours[5]+ \
                         (sel==4?"\"":"")+tagend;
                 output+=j00_n00b;
                 output+=tagstart+(sel==4?"/span":"/color")+tagend+tagstart+"/b"+tagend;
             }
         }
         if(i+1==real_len) { guts+="\n"; teh_len++; dontadd=true; }
     }
     if (sel < 3) {
         buff = stc->buff;
         buff->SetPositions(stc->GetSelectionStart(), stc->GetSelectionEnd());
         buff->SetLine(stc->GetFirstVisibleLine());
         buff->SetCaretPos(stc->GetCurrentPos());
         stc->SetText(output);
         stc->ScrollToLine(buff->GetLine());
         stc->SetCurrentPos(buff->GetCaretPos());
         stc->SetSelectionStart(buff->GetSelectionStart());
         stc->SetSelectionEnd(buff->GetSelectionEnd());
    }
    else { 
        if(color!=-1) output+=tagstart+(sel==4?"/span":"/color")+tagend;
        if(bold) output+=tagstart+"/b"+tagend;
        if(italic) output+=tagstart+"/i"+tagend;
        if     (sel==4) output+="</pre></body></html>";
        else if(sel==3) output+="[/size][/quote]";
        Parent->NewSTCPage("",true, 1);
        stc->SetText(output);
    }
} //end function

inline int format::isKeyword(wxString kw)
{
    kw=kw.MakeUpper();
    unsigned int kwlen=kw.Len();
    for(int i=0;i<4;i++)
    {
        int keywcount=(int)keyw[i].Count()-1;
        for(int j=0;j<keywcount-1;j++)
        {
            //check the lenght of the kw and keyw, if matxhes then
            //check first char as well.
            if (keyw[i][j].Len()==kwlen) {
                if(keyw[i][j].GetChar(0)==kw.GetChar(0)) {
                    if(keyw[i][j]==kw) return i+1;
                }
            }
        }
    }
    return 0;
}

void format::initkeywords()
{
    wxString curword="";
    char j00_n00b;
    for(int i=0;i<4;i++)
    {
        keyw[i].Clear();
        for(int j=0;j<(int)Parent->Keyword[i+1].Len();j++)
        {
            j00_n00b=Parent->Keyword[i+1].GetChar(j);
            curword+=j00_n00b;
            if(j00_n00b==' '||j00_n00b=='\n'||j00_n00b=='\r'||
               j+1==(int)Parent->Keyword[i+1].Len())
            {
                if(curword.Trim(false).Trim(true).Len()>0)
                    keyw[i].Add(curword.Trim(false).Trim(true).MakeUpper());
                curword="";
            }
        }
    }
}

inline bool format::isNumeric(wxString kw)
{
     if(kw.Len()==0) return false;
     if(kw.GetChar(0)=='&')
     {
         switch(kw.MakeLower().GetChar(1))
         {
             case 'b':
                 kw=kw.Mid(2);
                 break;
             case 'o':
                 kw=kw.Mid(2);
                 break;
             case 'h':
                 kw=kw.Mid(2);
                 break;
         }
     }
     char ch;
     for(int i=0;i<(int)kw.Len();i++)
     {
        ch = kw.GetChar(i);
        if( ch >= 46 && ch <= 57 ) {
            if (ch==47) return false;
        }
        else { return false; }
     }
     return true;
}

inline wxString format::hex(wxColour clr)
{
    wxString hexs="0123456789abcdef";
    int r=clr.Red(),b=clr.Blue(),g=clr.Green();
    return hexs.Mid((r&0xF0)>>4,1)+hexs.Mid(r&0xF,1)+hexs.Mid((g&0xF0)>>4,1)+ \
           hexs.Mid(g&0xF,1)+hexs.Mid((b&0xF0)>>4,1)+hexs.Mid(b&0xF,1);
}

void format::OnClose(wxCloseEvent &event)
{
    delete this;
}