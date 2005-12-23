#include "inc/wxall.h"

#include "inc/fb_frame.h"
#include "inc/fb_toolbar.h"

FB_ToolBar::FB_ToolBar( FB_Frame * parent ) :
    m_Parent( parent), m_ToolBar( NULL ) {
        
    m_ToolBar = new wxToolBar( m_Parent, ID_TOOLBAR, wxDefaultPosition, wxDefaultSize, 
        wxTB_FLAT|wxTB_HORIZONTAL|wxNO_BORDER );
    
    m_ToolBar->Hide();
    
    m_ToolBar->SetToolBitmapSize(wxSize(16, 16));

    m_ToolBar->AddTool(wxID_NEW,               _T(""), wxBITMAP(bmp_newsrc),   _T(""));
    m_ToolBar->AddTool(wxID_OPEN,              _T(""), wxBITMAP(bmp_opnproj),  _T(""));
    m_ToolBar->AddTool(wxID_SAVE,              _T(""), wxBITMAP(bmp_save),     _T(""));
    m_ToolBar->AddTool(wxID_SAVE_ALL,          _T(""), wxBITMAP(bmp_saveall),  _T(""));
    m_ToolBar->AddTool(wxID_CLOSE,             _T(""), wxBITMAP(bmp_closefl),  _T(""));
    m_ToolBar->AddSeparator();
    m_ToolBar->AddTool(wxID_CUT,               _T(""), wxBITMAP(bmp_cut),      _T(""));
    m_ToolBar->AddTool(wxID_COPY,              _T(""), wxBITMAP(bmp_copy),     _T(""));
    m_ToolBar->AddTool(wxID_PASTE,             _T(""), wxBITMAP(bmp_paste),    _T(""));
    m_ToolBar->AddSeparator();
    m_ToolBar->AddTool(wxID_UNDO,              _T(""), wxBITMAP(bmp_undo),     _T(""));
    m_ToolBar->AddTool(wxID_REDO,              _T(""), wxBITMAP(bmp_redo),     _T(""));
    m_ToolBar->AddSeparator();
    m_ToolBar->AddTool(fbideID_Compile,        _T(""), wxBITMAP(bmp_compile),  _T(""));
    m_ToolBar->AddTool(fbideID_Run,            _T(""), wxBITMAP(bmp_run),      _T(""));
    m_ToolBar->AddTool(fbideID_CompileAndRun,  _T(""), wxBITMAP(bmp_comprun),  _T(""));
    m_ToolBar->AddTool(fbideID_RebuildAll,     _T(""), wxBITMAP(bmp_rebuild),  _T(""));
    m_ToolBar->AddTool(fbideID_QuickRun,       _T(""), wxBITMAP(bmp_next),     _T(""));
    m_ToolBar->AddSeparator();
    m_ToolBar->AddTool(fbideID_OutPut,         _T(""), wxBITMAP(bmp_tile), _T(""));
    m_ToolBar->Realize();
}


FB_ToolBar::~FB_ToolBar() {
    HideToolBar();
    delete m_ToolBar;
}


void FB_ToolBar::ShowToolBar() {
    m_Parent->Freeze();
        m_ToolBar->Reparent( m_Parent );
        m_ToolBar->Show();
        m_Parent->SetToolBar( m_ToolBar );
        m_Parent->Refresh();
        m_Parent->Update();
    m_Parent->Thaw();
}


void FB_ToolBar::HideToolBar() {
    m_Parent->Freeze();
        m_ToolBar->Hide();
        m_ToolBar->Reparent( NULL );
        m_Parent->SetToolBar( NULL );
    m_Parent->Thaw();
}


void FB_ToolBar::Show( bool status ) {
    if( status ) ShowToolBar();
    else HideToolBar();
}


void FB_ToolBar::EnableTool(int toolId, const bool enable) {
    if( m_ToolBar == NULL ) return;
    m_ToolBar->EnableTool(toolId, enable);
}

