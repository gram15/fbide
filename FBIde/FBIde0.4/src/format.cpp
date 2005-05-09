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

// Don't modify comment 
#include "inc/main.h"
#include "inc/fbedit.h"
#include "inc/format.h"
//[inc]add your include files here


//[inc]end your include


format::format(wxWindow* parent,wxWindowID id,const wxString& title,const wxPoint& pos,const wxSize& size,long style,const wxString& name)
VwX_INIT_OBJECTS_format
{
    Parent = ( MyFrame * ) parent;
    OnPreCreate();
    Create(parent,id,title,pos,size,style,name);
    
    if((pos==wxDefaultPosition)&&(size==wxDefaultSize)){
        SetSize(0,0,405,210);
    }
    
    if((pos!=wxDefaultPosition)&&(size==wxDefaultSize)){
        SetSize(405,210);
    }
    initBefore();
    VwXinit();initAfter();
}


format::~format()
{
    Dformat();
}


void format::VwXinit()
{
    st5=new wxStaticText(this,-1,wxT(""),wxPoint(33,11),wxSize(218,19),wxST_NO_AUTORESIZE);
    st5->SetLabel(wxT("Type of conversion:"));
    
    lno6=new wxStaticLine(this,-1,wxPoint(29,32),wxSize(234,1));
    
    button_ok=new wxButton(this,-1,wxT(""),wxPoint(275,31),wxSize(93,24));
    button_ok->SetLabel(wxT("Go!"));
    
    sb9=new wxStaticBox(this,-1,wxT(""),wxPoint(20,117),wxSize(335,53));
    sb9->SetTitle(wxT("Preview"));
    
    preview=new wxStaticText(this,-1,wxT(""),wxPoint(30,145),wxSize(45,13));
    preview->SetLabel(wxT("Cls:Locate 1,1:Print \"\""));
    
    wxString choices[]={"KeyWords","KEYWORDS","keywords","BBCode","HTML"};
    
    chc15=new wxChoice(this,-1,wxPoint(31,37),wxSize(214,21),5,choices);
    
    bt16=new wxButton(this,-1,wxT(""),wxPoint(275,61),wxSize(93,24));
    bt16->SetLabel(wxT("Cancel"));
    
    bt17=new wxButton(this,-1,wxT(""),wxPoint(275,91),wxSize(93,24));
    bt17->SetLabel(wxT("Auto Indent"));
    Refresh();
}

BEGIN_EVENT_TABLE(formatEvt,wxEvtHandler)
//[evtEvt]add your code here


//[evtEvt]end your code
END_EVENT_TABLE()

    BEGIN_EVENT_TABLE( format,wxDialog)
    EVT_BUTTON(-1,format::VwXVwXEvOnButtonClick)
    EVT_CHOICE(-1,format::VwXVwXEvOnChoiceSelect)
//[evtwin]add your code here


//[evtwin]end your code
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
for(int i=0;i<Parent->stc->GetLineCount();i++)
{
//wxString line=Parent->stc->GetLine(i).Trim(false).Trim(true);
int cLine=i;
int lineInd=Parent->stc->GetLineIndentation(cLine-1);
int plineind=Parent->stc->GetLineIndentation(cLine-2);
int TabSize=Parent->Prefs.TabSize;

//Previous line
wxString TempCL=Parent->stc->ClearCmdLine(Parent->stc->GetLine(cLine-1));
wxString clfkw=Parent->stc->GetFirstKw(TempCL);
wxString cllkw=Parent->stc->GetLastKw(TempCL);

//Line before previous
wxString TempPL=Parent->stc->ClearCmdLine(Parent->stc->GetLine(cLine-2));
wxString plfkw=Parent->stc->GetFirstKw(TempPL);
wxString pllkw=Parent->stc->GetLastKw(TempPL);


if (lineInd>0) {
if ( clfkw == "end" && Parent->stc->IsEndDeIndentWord(cllkw) ) {
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
else  { if (plineind<=lineInd) lineInd -= TabSize; } }
else if ( clfkw == "else" || clfkw == "elseif" ) {
if ((plfkw == "if" && pllkw == "then") ||
(plfkw == "elseif")) { lineInd = plineind; } 
else   { if (plineind<=lineInd) lineInd -= TabSize; } }              
}
Parent->stc->SetLineIndentation (cLine-1, lineInd);
}  
if (Parent->stc->IsIndentWord(clfkw)) {
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
if (TempCL.Find('=')==-1) lineInd += TabSize; }
else  lineInd += TabSize;
}  
Parent->stc->SetLineIndentation (cLine, lineInd);
//Parent->stc->GotoPos(PositionFromLine (cLine) + lineInd);
}
this->Close();
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
this->Close();
} //end function

void format::button_ok_VwXEvOnButtonClick(wxCommandEvent& event,int index){ //init function
//[3d7]Code event VwX...Don't modify[3d6]//
//add your code here
//here's where i write the conversion $h17....
wxString guts=Parent->stc->GetText(),tagstart="",tagend="";
int sel=chc15->GetSelection();
bool dotags=false,dokeyws=false;
output="";
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
output="<body style=\"font-size:12pt; background-color:#"+hex(GetClr(Style->DefaultBgColour))+"; color:#"+hex(GetClr(Style->DefaultFgColour))+"\"><pre>";
break;
}
wxString curword="";
initkeywords();
int kwtyp=0;
bool commenting=false,dontadd=false,quoting=false;
wxColour colours[]={GetClr(Style->Info[wxSTC_B_KEYWORD].foreground),
GetClr(Style->Info[wxSTC_B_KEYWORD2].foreground),
GetClr(Style->Info[wxSTC_B_KEYWORD3].foreground),
GetClr(Style->Info[wxSTC_B_KEYWORD4].foreground),
GetClr(Style->Info[wxSTC_B_COMMENT].foreground),
GetClr(Style->Info[wxSTC_B_OPERATOR].foreground),
GetClr(Style->Info[wxSTC_B_STRING].foreground),
GetClr(Style->Info[wxSTC_B_NUMBER].foreground)};
for(int i=0;i<(int)guts.Len();i++)
{
char j00_n00b=(char)*guts.Mid(i,1);
curword+=j00_n00b;
if(j00_n00b=='('||j00_n00b==' '||j00_n00b==','||
guts.Mid(i,1).Trim(false).Trim(true)!=guts.Mid(i,1)||
j00_n00b=='['||j00_n00b=='\"'||j00_n00b=='\''||
i+1==(int)guts.Len()||j00_n00b==')'||j00_n00b=='='||
j00_n00b=='{'||j00_n00b=='}'||j00_n00b=='+'||
j00_n00b=='\\'||j00_n00b=='/'||j00_n00b=='*'||
j00_n00b=='-'||j00_n00b==';'||j00_n00b==','||
j00_n00b==':'||j00_n00b=='<'||j00_n00b=='>')
{
curword=curword.Mid(0,curword.Len()-1);
if(i+1==(int)guts.Len()&&!(j00_n00b=='('||j00_n00b==' '||j00_n00b==','||
guts.Mid(i,1).Trim(false).Trim(true)!=guts.Mid(i,1)||
j00_n00b=='['||j00_n00b=='\"'||j00_n00b=='\''||
j00_n00b==')'||j00_n00b=='='||
j00_n00b=='{'||j00_n00b=='}'||j00_n00b=='+'||
j00_n00b=='\\'||j00_n00b=='/'||j00_n00b=='*'||
j00_n00b=='-'||j00_n00b==';'||j00_n00b==','||
j00_n00b==':'||j00_n00b=='<'||j00_n00b=='>')) { curword+=j00_n00b; dontadd=true; }
if(dotags&&!commenting&&!quoting&&(kwtyp=isKeyword(curword))!=0)
{
output+=tagstart+"b"+tagend+tagstart+(sel==4?"font color=\"#":"color=#")+hex(colours[kwtyp-1])+ \
(sel==4?"\"":"")+tagend+curword+tagstart+(sel==4?"/font":"/color")+tagend+tagstart+"/b"+tagend+(dontadd?"":wxString::Format("%c",j00_n00b));
}
else if(dotags&&!commenting&&!quoting&&isNumeric(curword))
output+=tagstart+(sel==4?"font color=\"#":"color=#")+hex(colours[7])+ \
(sel==4?"\"":"")+tagend+curword+tagstart+(sel==4?"/font":"/color")+tagend+(dontadd?"":wxString::Format("%c",j00_n00b));
else if(dokeyws&&!commenting&&!quoting&&isKeyword(curword)!=0)
{
switch(sel)
{
case 0:
curword=curword.Mid(0,1).MakeUpper()+curword.Mid(1).MakeLower();
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
output+=curword+(dontadd?"":wxString::Format("%c",j00_n00b));
curword="";
if(!commenting&&!quoting&&j00_n00b=='\'')
{
commenting=true;
if(dotags)
{
output=output.Mid(0,output.Len()-1);
output+=tagstart+"i"+tagend+tagstart+(sel==4?"font color=\"#":"color=#")+hex(colours[4])+ \
(sel==4?"\"":"")+tagend+j00_n00b;
}
}
else if((j00_n00b=='\n'||j00_n00b=='\r')&&commenting)
{
commenting=false;
if(dotags)
{
output=output.Mid(0,output.Len()-1);
output+=tagstart+(sel==4?"/font":"/color")+tagend+tagstart+"/i"+tagend+j00_n00b;
}
}
if(dotags&&(j00_n00b=='('||j00_n00b==')'||j00_n00b=='='||
j00_n00b=='{'||j00_n00b=='}'||j00_n00b=='+'||
j00_n00b=='\\'||j00_n00b=='/'||j00_n00b=='*'||
j00_n00b=='-'||j00_n00b==';'||j00_n00b==',')&&!commenting)
{
output=output.Mid(0,output.Len()-1);
output+=tagstart+"b"+tagend+tagstart+(sel==4?"font color=\"#":"color=#")+hex(colours[5])+ \
(sel==4?"\"":"")+tagend+j00_n00b+tagstart+(sel==4?"/font":"/color")+tagend+tagstart+"/b"+tagend;
}
if(!commenting&&!quoting&&j00_n00b=='\"')
{
quoting=true;
if(dotags)
{
output=output.Mid(0,output.Len()-1);
output+=tagstart+(sel==4?"font color=\"#":"color=#")+hex(colours[6])+ \
(sel==4?"\"":"")+tagend+j00_n00b;
}
}
else if(j00_n00b=='\"'&&quoting)
{
quoting=false;
if(dotags) output+=tagstart+(sel==4?"/font":"/color")+tagend;
}
}
}
if(sel==4) output+="</pre></body>";
if(sel==3) output+="[/size][/quote]";
if(sel>2) Parent->NewSTCPage("",true, 1);
Parent->stc->SetText(output);
//Parent->stc->SaveFile("c:\\documents and settings\\dan\\desktop\\fbide_fb_linuxbuild\\fbidev3.html");
this->Close();
} //end function

int format::isKeyword(wxString kw)
{
kw=kw.MakeUpper();
for(int i=0;i<4;i++)
{
for(int j=0;j<(int)keyw[i].Count()-1;j++)
{
if(keyw[i][j]==kw||keyw[i][j]+"$"==kw) return i+1;
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
for(int j=0;j<(int)Parent->Keyword[i+1].Len();j++)
{
j00_n00b=(char)*Parent->Keyword[i+1].Mid(j,1);
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

bool format::isNumeric(wxString kw)
{
if(kw.Len()==0) return false;
bool yes=false;
wxString digits="0123456789";
for(int i=0;i<(int)kw.Len();i++)
{
for(int j=0;j<(int)digits.Len();j++)
{
if(kw.Mid(i,1)==digits.Mid(j,1)) { yes=true; break; }
}
if(yes==false) return false;
yes=false;
}
return true;
}

wxString format::hex(wxColour clr)
{
wxString hexs="0123456789abcdef";
int r=clr.Red(),b=clr.Blue(),g=clr.Green();
return hexs.Mid((r&0xF0)>>4,1)+hexs.Mid(r&0xF,1)+hexs.Mid((g&0xF0)>>4,1)+ \
hexs.Mid(g&0xF,1)+hexs.Mid((b&0xF0)>>4,1)+hexs.Mid(b&0xF,1);
}

void format::initBefore(){
//add your code here

}

void format::initAfter(){
//add your code here
chc15->SetSelection(0);
Centre();
}

void format::OnPreCreate(){
//add your code here

}

void format::Dformat(){
//add your code here

}

//[evtFunc]end your code
