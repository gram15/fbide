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


#include "inc/wxall.h"
#include "inc/fb_config.h"
#include "inc/fb_toolbar.h"
#include "inc/fb_frame.h"

void FB_Frame::CreateToolbar() {    
    m_ViewToolBar->Check( m_Config->ShowToolBar );
    m_ToolBar->Show( m_Config->ShowToolBar );
}
