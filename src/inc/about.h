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
#ifndef __VwX_MyDlg_H__
#define __VwX_MyDlg_H__
#include <wx/settings.h>
#include <wx/dialog.h>
 
//[inc]add your include files here



//[inc]end your include
 
#include <wx/sizer.h>
#include <wx/statbmp.h>
#include <wx/button.h>
#include <wx/textctrl.h>
class about;
class aboutEvt:public wxEvtHandler
{
public:
 aboutEvt(about *parent){ptr_winPan=parent;}
protected:  
 about *ptr_winPan;
 DECLARE_EVENT_TABLE()     
//[evt]add your code here



//[evt]end your code
};

class about:public wxDialog
{
 friend class aboutEvt;
public:
 about(wxWindow* parent, wxWindowID id = -1, const wxString& title = wxT("About FBIde"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxCAPTION|wxCLOSE_BOX|wxDIALOG_NO_PARENT|wxDEFAULT_DIALOG_STYLE, const wxString& name = wxT("dialogBox"));
// Pointer control
 wxStaticBitmap *bm3;
 wxButton *button_ok;
 wxTextCtrl *txm7;
 virtual ~about();
 virtual void Dabout();
 virtual void initBefore();
 void OnPreCreate();
 void VwXinit();
 wxBitmap *bm3Img0;
 wxBitmap fileImgBuf[1];
 virtual void initAfter();
 MyFrame * Parent;
protected:
 void VwXVwXEvOnButtonClick(wxCommandEvent& event);
 void button_ok_VwXEvOnButtonClick(wxCommandEvent& event,int index=-1);
 DECLARE_EVENT_TABLE()  
//[win]add your code here



 #define VwX_INIT_OBJECTS_about
//[win]end your code 
};
// end about

#endif
