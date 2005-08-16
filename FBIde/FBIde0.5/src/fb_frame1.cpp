/////////////////////////////////////////////////////////////////////////////
// Name:        fb_frame1.cpp
// Purpose:     
// Author:      VonGodric
// Modified by: 
// Created:     08/03/05 14:23:04
// RCS-ID:      
// Copyright:   
// Licence:     GPL
/////////////////////////////////////////////////////////////////////////////


#include "wx/wx.h"
#include "inc/fb_config.h"
#include "inc/fb_frame.h"

void FB_Frame::CreateToolbar()
{    
    
    if ( !Config->ShowToolBar ) return;
    ViewToolBar->Check( true );

    wxToolBarBase * toolbar = CreateToolBar( wxTB_FLAT|wxTB_HORIZONTAL|wxNO_BORDER, ID_TOOLBAR );
    toolbar->SetToolBitmapSize(wxSize(16, 16));

    toolbar->AddTool(wxID_NEW,       _T(""), wxBITMAP(bmp_newsrc),   _T(""));
    toolbar->AddTool(wxID_OPEN,      _T(""), wxBITMAP(bmp_opnproj),  _T(""));
    toolbar->AddTool(wxID_SAVE,      _T(""), wxBITMAP(bmp_save),     _T(""));
    toolbar->AddTool(wxID_SAVE_ALL,  _T(""), wxBITMAP(bmp_saveall),  _T(""));
    toolbar->AddTool(wxID_CLOSE,     _T(""), wxBITMAP(bmp_closefl),  _T(""));
    toolbar->AddSeparator();
    toolbar->AddTool(wxID_CUT,       _T(""), wxBITMAP(bmp_cut),      _T(""));
    toolbar->AddTool(wxID_COPY,      _T(""), wxBITMAP(bmp_copy),     _T(""));
    toolbar->AddTool(wxID_PASTE,     _T(""), wxBITMAP(bmp_paste),    _T(""));
    toolbar->AddSeparator();
    toolbar->AddTool(wxID_UNDO,      _T(""), wxBITMAP(bmp_undo),     _T(""));
    toolbar->AddTool(wxID_REDO,      _T(""), wxBITMAP(bmp_redo),     _T(""));
    toolbar->AddSeparator();
    toolbar->AddTool(fbideID_Compile,        _T(""), wxBITMAP(bmp_compile),  _T(""));
    toolbar->AddTool(fbideID_Run,            _T(""), wxBITMAP(bmp_run),      _T(""));
    toolbar->AddTool(fbideID_CompileAndRun,  _T(""), wxBITMAP(bmp_comprun),  _T(""));
    toolbar->AddTool(fbideID_RebuildAll,     _T(""), wxBITMAP(bmp_rebuild),  _T(""));
    toolbar->AddTool(fbideID_QuickRun,       _T(""), wxBITMAP(bmp_next),     _T(""));
    toolbar->AddSeparator();
    toolbar->AddTool(fbideID_OutPut, _T(""), wxBITMAP(bmp_tile), _T(""));
    toolbar->Realize();

}
