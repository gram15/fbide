
// Don't modify comment 
#include "inc/main.h"
#include "inc/about.h"
//[inc]add your include files here


//[inc]end your include
    

about::about(wxWindow* parent,wxWindowID id,const wxString& title,const wxPoint& pos,const wxSize& size,long style,const wxString& name)
        VwX_INIT_OBJECTS_about
{
    Parent = ( MyFrame * ) parent;
    OnPreCreate();
    Create(parent,id,title,pos,size,style,name);

    if((pos==wxDefaultPosition)&&(size==wxDefaultSize)){
                    SetSize(0,0,350,320);
    }

    if((pos!=wxDefaultPosition)&&(size==wxDefaultSize)){
                    SetSize(350,320);
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
    bm3=new wxStaticBitmap(this,-1,*bm3Img0,wxPoint(22,15),wxSize(300,75));
    button_ok=new wxButton(this,-1,wxT(""),wxPoint(100,254),wxSize(123,24));
            button_ok->SetLabel(wxT("Ok"));
    txm7=new wxTextCtrl(this,-1,wxT(""),wxPoint(23,103),wxSize(294,139),wxVSCROLL|wxHSCROLL|wxTE_READONLY|wxTE_RICH2|wxTE_DONTWRAP|wxTE_MULTILINE);
            txm7->SetLabel(wxT(""));
    wxArrayString myarr;
    myarr.Add(wxString::Format("[bold]FBIde %d.%d",VER_MAJOR,VER_MINOR));
    myarr.Add(wxString::Format("Build %d[/bold]",VER_BUILD));
    myarr.Add(Parent->Lang[204]);
    myarr.Add(Parent->Lang[205]);
    myarr.Add(Parent->Lang[206]);
    myarr.Add("");
    myarr.Add("[bold]"+Parent->Lang[207]);
    myarr.Add(Parent->Lang[208]+"[/bold]");
    myarr.Add("");
    myarr.Add("VonGodric - "+Parent->Lang[209]);
    myarr.Add("marzec - "+Parent->Lang[210]);
    myarr.Add("dilyias - "+Parent->Lang[211]);
    myarr.Add("dumbledore - "+Parent->Lang[212]);
    myarr.Add("Madedog - "+Parent->Lang[213]);
    myarr.Add("");
    myarr.Add("[bold]"+Parent->Lang[214]+"[/bold]");
    myarr.Add("");
    myarr.Add("aetherFox - "+Parent->Lang[215]);
    myarr.Add("Mecki - "+Parent->Lang[216]);
    myarr.Add("");
    myarr.Add("[bold]"+Parent->Lang[217]+"[/bold]");
    myarr.Add("");
    myarr.Add("Shadowolf\tAetherFox");
    myarr.Add("Z!re\t\tak00ma");
    myarr.Add("nodveidt\t\tWhitetiger");
    myarr.Add("DrV\t\tAdosorken");
    myarr.Add("SJ Zero\t\tNexinarus");
    myarr.Add("Ak00ma\t\tshiftLynx");
    myarr.Add("");
    myarr.Add("Language files by:"); //Language files by:
    myarr.Add("");
    myarr.Add(Parent->Lang[218]);
    wxString tag="";
    wxTextAttr myattr=txm7->GetDefaultStyle();
    wxFont defFont=myattr.GetFont();
    wxFont boldFont=myattr.GetFont();
    boldFont.SetWeight(wxFONTWEIGHT_BOLD);
    bool nesting=false;
    for(int i=0;i<(int)myarr.Count();i++)
    {
        for(int j=0;j<(int)myarr[i].Len();j++)
        {
            char thechar=(char)*myarr[i].Mid(j,1);
            if(thechar=='['&&!nesting)
            {
                nesting=true;
            }
            else if(thechar==']'&&nesting)
            {
                nesting=false;
                tag=tag.MakeLower();
                if(tag=="bold")
                    myattr.SetFont(boldFont);
                else if(tag=="/bold")
                    myattr.SetFont(defFont);
                txm7->SetDefaultStyle(myattr);
                tag="";
            }
            else if(nesting)
            {
                tag+=thechar;
            }
            else
            {
                txm7->WriteText(thechar);
            }
        }
        txm7->WriteText("\r\n");
    }
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
    Centre();
}

void about::OnPreCreate(){
    //add your code here

}

void about::Dabout(){
    //add your code here

}

//[evtFunc]end your code
