/////////////////////////////////////////////////////////////////////////////
// Name:        wxmynotebook.cpp
// Purpose:     
// Author:      VonGodric
// Modified by: 
// Created:     08/14/05 17:16:30
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#include <vector>
#include "wx/wx.h"
#include "inc/main.h"
#include "inc/fbedit.h"
#include "inc/wxmynotebook.h"

BEGIN_EVENT_TABLE(wxMyNotebook,wxTabbedCtrl) 
    EVT_MOUSE_EVENTS(wxMyNotebook::OnMouseEvent) 
END_EVENT_TABLE() 

wxMyNotebook::wxMyNotebook(MyFrame* mf, wxWindow *parent, wxWindowID id, 
              const wxPoint& pos, const wxSize& size, 
              long style, const wxString& name)
              : wxTabbedCtrl(parent,id,pos,size,style,name) 
{ 
    p = mf;
}


void wxMyNotebook::OnMouseEvent(wxMouseEvent& event) 
{ 
    wxEventType eventType = event.GetEventType(); 
    
        m_X=event.GetX(); 
        m_Y=event.GetY(); 
        int tabid = HitTest(wxPoint(m_X, m_Y));
        
        if (eventType==wxEVT_RIGHT_DOWN) 
        {
            /*/
            // *  In the sake of integrity
            // *  this should be moved out of here... but How?
            // *  generate costom event and pass data along?
            // *  well for now it can stay here...
            /*/
            if ( tabid==wxNOT_FOUND ) return;
            if ( tabid!=GetSelection() ) SetSelection( tabid );
            FB_Edit * stc = p->stc;
            wxMenu popup("");
            popup.Append(Menu_Close,        _(p->Lang[21]));
            popup.Append(Menu_CloseAll,    _(p->Lang[173]));
            popup.AppendSeparator();
            popup.Append(Menu_Undo,         _(p->Lang[27]));
            popup.Enable(Menu_Undo, stc->CanUndo());
            popup.Append(Menu_Redo,         _(p->Lang[29]));
            popup.Enable(Menu_Redo, stc->CanRedo());
            popup.AppendSeparator();
            popup.Append(Menu_Copy,         _(p->Lang[33]));
            popup.Enable(Menu_Copy, (stc->GetSelectionEnd()-stc->GetSelectionStart()));
            popup.Append(Menu_Cut,          _(p->Lang[31]));
            popup.Enable(Menu_Cut,   (stc->GetSelectionEnd()-stc->GetSelectionStart()));
            popup.Append(Menu_Paste,        _(p->Lang[35]));
            popup.Enable(Menu_Paste, stc->CanPaste());
            popup.Append(Menu_SelectAll,    _(p->Lang[37]));
            popup.Enable(Menu_SelectAll, stc->GetLength());
            wxWindow::PopupMenu(&popup, m_X, m_Y);
            return;
        }
        else if (eventType==wxEVT_MIDDLE_DOWN)
        {
            if ( tabid==wxNOT_FOUND ) return;
            if ( tabid!=GetSelection() ) SetSelection( tabid );
            wxCommandEvent event( wxEVT_COMMAND_MENU_SELECTED, Menu_Close );
            GetEventHandler()->ProcessEvent( event );
            return;
        }
    event.Skip();
}


// new tabs :P
////////////////////////////////////////////////////////////////////////////////// 
// TabbedCtrl 
////////////////////////////////////////////////////////////////////////////////// 

IMPLEMENT_DYNAMIC_CLASS(wxTabbedCtrlEvent, wxNotifyEvent); 

IMPLEMENT_DYNAMIC_CLASS(wxTabbedCtrl, wxControl); 

DEFINE_EVENT_TYPE(wxEVT_COMMAND_TABBEDCTRL_PAGE_CHANGED) 
DEFINE_EVENT_TYPE(wxEVT_COMMAND_TABBEDCTRL_PAGE_CHANGING) 
DEFINE_EVENT_TYPE(wxEVT_COMMAND_TABBEDCTRL_PAGE_CLOSING) 

BEGIN_EVENT_TABLE(wxTabbedCtrl, wxControl) 
   EVT_PAINT(wxTabbedCtrl::OnPaint) 
   EVT_LEFT_DOWN(wxTabbedCtrl::OnMouse) 
   EVT_MOTION(wxTabbedCtrl::OnMouse) 
   EVT_SIZE(wxTabbedCtrl::OnSize) 
   EVT_ERASE_BACKGROUND(wxTabbedCtrl::OnEraseBackground) 
END_EVENT_TABLE() 

wxTabbedCtrl::wxTabbedCtrl() 
: active(-1), img_list(0), style(0) 
{ 
}  

void wxTabbedCtrl::Create(wxWindow *parent, wxWindowID id, 
      const wxPoint &position, const wxSize &size, 
      long style, const wxString &name) 
{ 
   wxWindow::Create(parent, id, position, size, wxNO_BORDER, name); 
   active = -1; 
   img_list = 0; 
   this->style = style; 
   padding.x = 5; 
   padding.y = 3; 
   hover = false; 
} 

void wxTabbedCtrl::AddPage(const wxString &text, bool select, int img) { 
   pages.push_back(wxTabbedPage(text, img)); 
   if(select || GetSelection()==-1) SetSelection(GetPageCount()-1); 
   else Refresh(); 
} 

void wxTabbedCtrl::InsertPage(int pg, const wxString& text, bool select, int img) { 
   wxASSERT_MSG(pg >= 0 && pg <= GetPageCount(), "Got invalid page number"); 
   pages_type::iterator it = pages.begin() + pg; 
   pages.insert(it, wxTabbedPage(text, img)); 
   if(select || GetSelection()==-1) SetSelection(pg); 
   else Refresh(); 
} 

void wxTabbedCtrl::DeleteAllPages() { 
   pages.clear(); 
   active = -1; 
   Refresh(); 
} 

void wxTabbedCtrl::DeletePage(int pg) { 
   wxASSERT_MSG(pg >= 0 && pg < GetPageCount(), "Got invalid page number"); 
   pages_type::iterator it = pages.begin() + pg; 
   pages.erase(it); 
   if(pg < active) active--; 
   else if(active==pg && active==GetPageCount()) active--; 
   Refresh(); 
} 

void wxTabbedCtrl::SetSelection(int pg) { 
   wxASSERT_MSG(pg >= 0 && pg < GetPageCount(), "Got invalid page number"); 
   if(pg != active) { 
      wxTabbedCtrlEvent event(wxEVT_COMMAND_TABBEDCTRL_PAGE_CHANGING, m_windowId); 
      event.SetSelection(pg); 
      event.SetOldSelection(active); 
      event.SetEventObject(this); 
      if(!GetEventHandler()->ProcessEvent(event) || event.IsAllowed()) 
      { 
         // program allows the page change 
         active = pg; 
         event.SetEventType(wxEVT_COMMAND_TABBEDCTRL_PAGE_CHANGED); 
         event.SetOldSelection(active); 
         GetEventHandler()->ProcessEvent(event); 
         Refresh(); 
      } 
   } 
} 

wxString wxTabbedCtrl::GetPageText(int pg) { 
   wxASSERT_MSG(pg >= 0 && pg < GetPageCount(), "Got invalid page number"); 
   return pages[pg].text; 
} 

void wxTabbedCtrl::SetPageText(int pg, const wxString &t) { 
   wxASSERT_MSG(pg >= 0 && pg < GetPageCount(), "Got invalid page number"); 
   if(pages[pg].text != t) { 
      pages[pg].text = t; 
      Refresh(); 
   } 
} 

int wxTabbedCtrl::GetPageImage(int pg) { 
   wxASSERT_MSG(pg >= 0 && pg < GetPageCount(), "Got invalid page number"); 
   return pages[pg].image; 
} 

void wxTabbedCtrl::SetPageImage(int pg, int img) { 
   wxASSERT_MSG(pg >= 0 && pg < GetPageCount(), "Got invalid page number"); 
   if(pages[pg].image != img) { 
      pages[pg].image = img; 
      Refresh(); 
   } 
} 

int wxTabbedCtrl::HitTest(const wxPoint &p, long *flags) { 
   int height, width, pom; 
   bool mirror = style & wxTB_BOTTOM; 
//   bool drawx = style & wxTB_X; 
   wxSize size = GetSize(); 
   wxClientDC dc(this); 

   wxFont normal_font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT); 
   wxFont bold_font = normal_font; 
   bold_font.SetWeight(wxFONTWEIGHT_BOLD); 
    
   if(flags) *flags = wxTB_HITTEST_NOWHERE; 
   dc.SetFont(bold_font); 
   dc.GetTextExtent("Aq", &pom, &height); 
   if(p.x <= 0 || p.x >= size.x) return wxNOT_FOUND; 
   if(!mirror && (p.y <= size.y-height-padding.y*2 || p.y >= size.y)) return wxNOT_FOUND; 
   if(mirror && (p.y <= 0 || p.y >= height+padding.y*2)) return wxNOT_FOUND; 

   int posx = 3; 
   for(int i = 0; i < GetPageCount(); i++) { 
      dc.SetFont((i==GetSelection()) ? bold_font : normal_font); 
      dc.GetTextExtent(GetPageText(i), &width, &pom); 
      
      wxBitmap bmp; 
      if(GetPageImage(i) >= 0) bmp = img_list->GetBitmap(i); 
      int space = padding.x; 
      if(bmp.Ok()) space += bmp.GetWidth()+padding.x; 

      if(p.x > posx && p.x < posx+width+space+padding.x) { 
         if(flags) *flags = wxTB_HITTEST_ONITEM; 
          
         //onicon attempt 
         if(flags && bmp.Ok() && p.x >= posx+padding.x && p.x <= posx+bmp.GetWidth()+padding.x) { 
            if(!mirror && p.y >= size.y-height-padding.y && p.y <= size.y-padding.y) *flags = wxTB_HITTEST_ONICON; 
            else if(mirror && p.y >= padding.y && p.y <= padding.y+bmp.GetHeight()) *flags = wxTB_HITTEST_ONICON; 
         } 
         //onlabel attempt 
         else if(flags && p.x >= posx+space && p.x <= posx+space+width) { 
            if(!mirror && p.y >= size.y-height-padding.y && p.y <= size.y-padding.y) *flags = wxTB_HITTEST_ONLABEL; 
            else if(mirror && p.y >= padding.y && p.y <= padding.y+height) *flags = wxTB_HITTEST_ONLABEL; 
         } 
          
         return i; 
      } 
      
      posx += width+space+padding.x; 
   } 
    
   return wxNOT_FOUND; 
} 

void wxTabbedCtrl::OnMouse(wxMouseEvent &ev) { 
   if(ev.GetEventType()==wxEVT_MOTION) { 
      wxPoint mouse = ev.GetPosition(); 
      bool nhover = mouse.x >= x_rect.x && mouse.x <= x_rect.x+x_rect.width && mouse.y >= x_rect.y && mouse.y <= x_rect.y+x_rect.height; 
      if(hover != nhover) { 
         hover = nhover; 
         wxClientDC dc(this); 
         DrawX(hover, dc); 
      } 
   } 
   else if(ev.GetEventType()==wxEVT_LEFT_DOWN) { 
      if(hover) { 
            wxCommandEvent event( wxEVT_COMMAND_MENU_SELECTED, Menu_Close );
            GetEventHandler()->ProcessEvent( event );
      } 
      else { 
         int page = HitTest(ev.GetPosition());  
         if(page != wxNOT_FOUND) SetSelection(page); 
      } 
   } 
} 

void wxTabbedCtrl::OnSize(wxSizeEvent &) { 
   Refresh(); 
} 

void wxTabbedCtrl::OnEraseBackground(wxEraseEvent &) { 
} 

void wxTabbedCtrl::DrawX(bool active, wxDC &dc) { 
   const int SIZE = 8; 
   wxSize size = GetSize(); 
   wxBrush back_brush = wxBrush(GetBackgroundColour()); 
   wxPen back_pen = wxPen(GetBackgroundColour()); 
   wxPen x_pen = wxPen(active ? wxSystemSettings::GetColour(wxSYS_COLOUR_BTNSHADOW) : *wxBLACK); 
   x_pen.SetWidth(2); 
    
   int posx = size.x-SIZE*2, posy = (size.y-SIZE)/2; 
   x_rect = wxRect(posx, posy, SIZE, SIZE); 

   dc.SetPen(back_pen); 
   dc.SetBrush(back_brush); 
   dc.DrawRectangle(posx-SIZE+1, 1, SIZE*3-2, size.y-2); 

   dc.SetPen(x_pen); 
   dc.DrawLine(posx, posy, posx+SIZE, posy+SIZE); 
   dc.DrawLine(posx, posy+SIZE, posx+SIZE, posy); 
} 

void wxTabbedCtrl::OnPaint(wxPaintEvent &) { 
   wxPaintDC dc(this); 
   wxSize size = GetSize(); 
   wxBrush back_brush = wxBrush(GetBackgroundColour()); 
   wxBrush nosel_brush = wxBrush(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE)); 
   wxBrush sel_brush = wxBrush(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNHIGHLIGHT)); 
   wxPen border_pen = wxPen(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNSHADOW)); 
   wxPen sel_pen = wxPen(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNHIGHLIGHT)); 
   wxPen back_pen = wxPen(GetBackgroundColour()); 
   wxFont normal_font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT); 
   wxFont bold_font = normal_font; 
   bold_font.SetWeight(wxFONTWEIGHT_BOLD); 
   bool mirror = style & wxTB_BOTTOM; 
   bool fullborder = !(style & wxNO_BORDER); 
   bool drawx = style & wxTB_X; 
    
   dc.BeginDrawing(); 

   //background 
   dc.SetTextBackground(GetBackgroundColour()); 
   dc.SetTextForeground(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNTEXT)); 
   dc.SetBrush(back_brush); 
   if(fullborder) { 
      dc.SetPen(border_pen); 
      dc.DrawRectangle(0, 0, size.x, size.y); 
   } 
   else { 
      dc.SetPen(back_pen); 
      dc.DrawRectangle(0, 0, size.x, size.y); 
      dc.SetPen(border_pen); 
      dc.DrawLine(0, mirror ? 0 : size.y-1, size.x, mirror ? 0 : size.y-1); 
   } 

   int height, width, pom; 
   dc.SetFont(bold_font); 
   dc.GetTextExtent("Aq", &pom, &height); 
   int posx = 3; 
    
   //and tabs 
   for(int i = 0; i < GetPageCount(); i++) { 
      dc.SetPen(border_pen); 
      dc.SetFont((i==GetSelection()) ? bold_font : normal_font); 
      dc.SetBrush((i==GetSelection()) ? sel_brush : nosel_brush); 
      dc.GetTextExtent(GetPageText(i), &width, &pom); 
          
      wxBitmap bmp; 
      if(GetPageImage(i) >= 0) bmp = img_list->GetBitmap(GetPageImage(i)); 
      
      int space = padding.x; 
      if(bmp.Ok()) space += padding.x + bmp.GetWidth(); 
      
      if(!mirror) { 
         dc.DrawRoundedRectangle(posx, size.y-height-padding.y*2, width+space+padding.x, height+padding.y*2+3, 3); 
         dc.DrawText(GetPageText(i), posx+space, size.y-height-padding.y); 
         if(i!=GetSelection()) dc.DrawLine(posx, size.y-1, posx+width+space+padding.x, size.y-1); 

         if(bmp.Ok()) dc.DrawBitmap(bmp, posx+padding.x, size.y-(height+2*padding.y+bmp.GetHeight())/2, true); 
      } 
      else { 
         dc.DrawRoundedRectangle(posx, -3, width+space+padding.x, height+padding.y*2+3, 3); 
         dc.DrawText(GetPageText(i), posx+space, padding.y); 
         if(i!=GetSelection()) dc.DrawLine(posx, 0, posx+width+space+padding.x, 0); 

         if(bmp.Ok()) dc.DrawBitmap(bmp, posx+padding.x, (height+2*padding.y-bmp.GetHeight())/2, true); 
      } 

      posx += width+space+padding.x; 
   } 

   //X 
   if(drawx) DrawX(hover, dc); 

   dc.EndDrawing(); 
} 
 
 
