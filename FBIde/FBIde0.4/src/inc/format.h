
// Don't modify comment 
#ifndef __VwX_MyDlg_H__
#define __VwX_MyDlg_H__
#include <wx/settings.h>
#include <wx/dialog.h>
 
//[inc]add your include files here



//[inc]end your include
 
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/statline.h>
#include <wx/button.h>
#include <wx/statbox.h>
#include <wx/choice.h>
class format;
class formatEvt:public wxEvtHandler
{
public:
 formatEvt(format *parent){ptr_winPan=parent;}
protected:  
 format *ptr_winPan;
 DECLARE_EVENT_TABLE()     
//[evt]add your code here



//[evt]end your code
};

class format:public wxDialog
{
 friend class formatEvt;
public:
 format(wxWindow* parent, wxWindowID id = -1, const wxString& title = wxT(""), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxCAPTION|wxSYSTEM_MENU|wxCLOSE_BOX|wxDIALOG_NO_PARENT|wxDEFAULT_DIALOG_STYLE, const wxString& name = wxT("dialogBox"));
// Pointer control
 wxStaticText *st5;
 wxStaticLine *lno6;
 wxButton *button_ok;
 wxStaticBox *sb9;
 wxStaticText *preview;
 wxChoice *chc15;
 wxButton *bt16;
 MyFrame * Parent;
 wxString guts;
 wxString output;
 wxButton *bt17;
 virtual ~format();
 virtual void Dformat();
 virtual void initBefore();
 void OnPreCreate();
 void VwXinit();
 virtual void initAfter();
protected:
 void VwXVwXEvOnButtonClick(wxCommandEvent& event);
 void VwXVwXEvOnChoiceSelect(wxCommandEvent& event);
 void chc15_VwXEvOnChoiceSelect(wxCommandEvent& event,int index=-1);
 void button_ok_VwXEvOnButtonClick(wxCommandEvent& event,int index=-1);
 void bt17_VwXEvOnButtonClick(wxCommandEvent& event,int index=-1);
 void bt16_VwXEvOnButtonClick(wxCommandEvent& event,int index=-1);
 wxString hex(wxColour clr);
 bool format::isNumeric(wxString kw);
 int isKeyword(wxString kw);
 DECLARE_EVENT_TABLE()  
//[win]add your code here



 #define VwX_INIT_OBJECTS_format
//[win]end your code 
};
// end format

#endif
