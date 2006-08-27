/*
 * This file is part of FBIde, an open-source (cross-platform) IDE for
 * FreeBasic compiler.
 * Copyright (C) 2005 - 2006 Albert Varaksin
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

#include "inc/fbide.h"

#include "../sdk/sdk.h"

#include "inc/main.h"
#include "inc/doc_html.h"

/**
 * This is main entry function into our FBIde
 *
 * If returns false then application will not be started.
 * @return bool
 */


bool FBIde::OnInit()
{
    // Force creation of managers
    (void)Manager::Get(new Main);

    // Register all available image types
    ::wxInitAllImageHandlers();

    // Load registry and set some initial data
    (void)Manager::Get()->GetRegManager();
    std::auto_ptr<RegAccessor>reg(new RegAccessor(_T("base")));
    wxString base = ::wxPathOnly(argv[0]) + _T("/");
    reg->SetPath(_T("/paths"));
    reg->WriteString(_T("base"),      base);
    reg->WriteString(_T("config"),    base + _T("ide/config/"));
    reg->WriteString(_T("plugins"),   base + _T("ide/plugins/"));
    reg->WriteString(_T("langs"),     base + _T("ide/langs/"));

    // User interface manager
    (void)Manager::Get()->GetUiManager();

    // Document manager
    (void)Manager::Get()->GetDocManager();



    // Set top window
    SetTopWindow (Manager::Get()->GetUiManager()->GetFrame());

    // Show
    Manager::Get()->GetUiManager()->GetFrame()->Show();

    // Open welcome screen
    Doc_Html * welcome = new Doc_Html(base + _T("welcome.html"));
    welcome->ShowDocument();

    return true;
}



/**
 * This is function that gets called apon exit from FBIde
 *
 * Returns an exit code.
 * @return int
 */
int FBIde::OnExit()
{
  wxTheClipboard->Flush();
  return wxApp::OnExit();
}



/**
 * Implement and declare FBIde application
 */
IMPLEMENT_APP(FBIde)
DECLARE_APP(FBIde)
