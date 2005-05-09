
// Don't modify comment 
#include "inc/about.h"
#include "inc/main.h"
#include "inc/fbedit.h"
//[inc]add your include files here


//[inc]end your include
 

about::about(wxWindow* parent,wxWindowID id,const wxString& title,const wxPoint& pos,const wxSize& size,long style,const wxString& name)
  VwX_INIT_OBJECTS_about
{
 OnPreCreate();
 Create(parent,id,title,pos,size,style,name);

 if((pos==wxDefaultPosition)&&(size==wxDefaultSize)){
     SetSize(0,0,510,525);
 }

 if((pos!=wxDefaultPosition)&&(size==wxDefaultSize)){
     SetSize(510,525);
 }
 initBefore();
 fileImgBuf[0]=wxBITMAP(fbide);
 bm3Img0=&fileImgBuf[0];
 VwXinit();initAfter();
}
about::~about()
{
  Dabout();
}
void about::VwXinit()
{
 button_ok=new wxButton(this,-1,wxT(""),wxPoint(180,459),wxSize(123,24));
   button_ok->SetLabel(wxT("Ok"));
 st4=new wxStaticText(this,-1,wxT(""),wxPoint(33,105),wxSize(436,345));
   StatChange();
 bm3=new wxStaticBitmap(this,-1,*bm3Img0,wxPoint(92,15),wxSize(300,75));
 Refresh();
}
 
BEGIN_EVENT_TABLE(aboutEvt,wxEvtHandler)
//[evtEvt]add your code here


//[evtEvt]end your code
END_EVENT_TABLE()
 
BEGIN_EVENT_TABLE( about,wxDialog)
  EVT_BUTTON(-1,about::VwXVwXEvOnButtonClick)
//[evtwin]add your code here

//[evtwin]end your code
END_EVENT_TABLE()
void about::VwXVwXEvOnButtonClick(wxCommandEvent& event){
 wxObject *m_wxWin = event.m_eventObject ;
 if(m_wxWin==button_ok){button_ok_VwXEvOnButtonClick(event,-1);return;}
 event.Skip(true);
}

//[evtFunc]add your code here

void about::button_ok_VwXEvOnButtonClick(wxCommandEvent& event,int index){ //init function
 //[74a]Code event VwX...Don't modify[749]//
 //add your code here
 this->Close();
} //end function

void about::initBefore(){
 //add your code here

}

void about::initAfter(){
 //add your code here
 //the_timer.Start(500);
 Centre();
}

void about::OnPreCreate(){
 //add your code here
 textstuffs.Add(wxString::Format("FBIde %d.%d",VER_MAJOR,VER_MINOR));
 textstuffs.Add(wxString::Format("Build %d",VER_BUILD));
 textstuffs.Add("an open-source IDE for the FreeBASIC compiler");
 textstuffs.Add("(www.freebasic.net)");
 textstuffs.Add("made using c++ with wxWidgets and the scintilla text control");
 textstuffs.Add("");
 textstuffs.Add("credits:");
 textstuffs.Add("programmers");
 textstuffs.Add("");
 textstuffs.Add("VonGodric - head programmer, project administrator and founder of the project");
 textstuffs.Add("marzec - project supervisor, network code (client and serverside)");
 textstuffs.Add("dilyias - autocompletion code");
 textstuffs.Add("dumbledore - code exporting and formatting routines");
 textstuffs.Add("Madedog - translation modules");
 textstuffs.Add("");
 textstuffs.Add("misc");
 textstuffs.Add("");
 textstuffs.Add("aetherFox - webmaster and documentation");
 textstuffs.Add("");
 textstuffs.Add("testers");
 textstuffs.Add("");
 textstuffs.Add("Shadowolf\tAetherFox");
 textstuffs.Add("Z!re\t\tak00ma");
 textstuffs.Add("nodveidt\tWhitetiger");
 textstuffs.Add("DrV");
 textstuffs.Add("");
 textstuffs.Add("...and everyone we forgot. :D");
}

void about::Dabout(){
 //add your code here

}

void about::StatChange(){
 wxString mystr="";
 for(int i=0;i<(int)textstuffs.Count();i++)
  mystr+=textstuffs[i]+"\r\n";
 st4->SetLabel(wxT(mystr.Mid(0,mystr.Len()-2)));
}

//[evtFunc]end your code


