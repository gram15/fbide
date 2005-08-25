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
#include "inc/about.h"
    
BEGIN_EVENT_TABLE( about,wxDialog)
    EVT_BUTTON(-1,  about::On_button_ok)
END_EVENT_TABLE()

about::about(wxWindow* parent,wxWindowID id,const wxString& title,const wxPoint& pos,const wxSize& size,long style,const wxString& name)
    : wxDialog(parent,id,title,pos,size,style,name)
{
    Parent = ( MyFrame * ) parent;
    
    if((pos==wxDefaultPosition)&&(size==wxDefaultSize)){
                    SetSize(0,0,350,320);
    }

    if((pos!=wxDefaultPosition)&&(size==wxDefaultSize)){
                    SetSize(350,320);
    }
    fileImgBuf[0]=wxBITMAP(fbide);
    bm3Img0=&fileImgBuf[0];

    bm3=new wxStaticBitmap(this,-1,*bm3Img0,wxPoint(22,15),wxSize(300,75));
    button_ok=new wxButton(this,-1,wxT(""),wxPoint(100,254),wxSize(123,24));
            button_ok->SetLabel(wxT("Ok"));
    txm7=new wxTextCtrl(this,-1,wxT(""),wxPoint(23,103),wxSize(294,139),wxVSCROLL|wxHSCROLL|wxTE_READONLY|wxTE_RICH2|wxTE_DONTWRAP|wxTE_MULTILINE);
            txm7->SetLabel(wxT(""));
    wxArrayString myarr;
    myarr.Add(wxString::Format("[bold]FBIde %d.%d.%d[/bold]",VER_MAJOR,VER_MINOR,VER_RELEASE));
    myarr.Add(Parent->Lang[204]);
    myarr.Add(Parent->Lang[205]);
    myarr.Add(Parent->Lang[206]);
    myarr.Add("");
    myarr.Add("[bold]"+Parent->Lang[207]);
    myarr.Add(Parent->Lang[208]+"[/bold]");
    myarr.Add("VonGodric - "+Parent->Lang[209]);
    myarr.Add("dilyias - "+Parent->Lang[211]);
    myarr.Add("dumbledore - "+Parent->Lang[212]);
    myarr.Add("Madedog - "+Parent->Lang[213]);
    myarr.Add("");
    myarr.Add("[bold]"+Parent->Lang[214]+"[/bold]");
    myarr.Add("aetherFox - "+Parent->Lang[215]);
    myarr.Add("Mecki - "+Parent->Lang[216]);
    myarr.Add("");
    myarr.Add("[bold]"+Parent->Lang[217]+"[/bold]");
    myarr.Add("Shadowolf\tAetherFox");
    myarr.Add("Z!re\t\tak00ma");
    myarr.Add("Adosorken\tWhitetiger");
    myarr.Add("DrV\t\tshiftLynx");
    myarr.Add("SJ Zero\t\tNexinarus");
    myarr.Add("");
    myarr.Add("[bold]Language files by[/bold]"); //Language files by:
    myarr.Add("v!ct0r\t\t- portuguese");
    myarr.Add("Mecki\t\t- german");
    myarr.Add("MystikShadows\t- french");
    myarr.Add("Dutchtux\t\t- dutch");
    myarr.Add("E. Gerfanow \t- russion");
    myarr.Add("Rojalus Kele \t- chinese");
    myarr.Add("Drakontas\t- greek");
    myarr.Add("Shion\t\t- japanese");
    myarr.Add("Nicolae Panaitoiu \t- romanian");
    myarr.Add("Lurah \t\t- finnish");
    myarr.Add("Etko \t\t- slovak");
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
    Centre();
}

about::~about()
{
    return;
}

void about::On_button_ok(wxCommandEvent& event){
    this->EndModal(true);
}
