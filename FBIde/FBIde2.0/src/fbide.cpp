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
#include "inc/manager.h"

#include "inc/main.h"

#include "inc/document.h"
#include <wx/html/htmlwin.h>
#include <wx/uri.h>

/**
 * This is main entry function into our FBIde
 *
 * If returns false then application will not be started.
 * @return bool
 */

class WelcomePage : public Document<wxHtmlWindow>
{
    public:
        WelcomePage ()
        {
            Create (Manager::Get()->GetDocManager()->GetWindow(), wxID_ANY);
            std::auto_ptr<RegAccessor>reg(new RegAccessor(_T("base")));
            reg->SetPath(_T("/paths"));
            wxString file;
            file << reg->ReadString(_T("base")) << _T("test.html");
            LoadFile (file);
        }

        virtual wxString GetDocumentName ()
        {
            return _T("Welcome");
        }


        /**
         * Handle clicks on links
         * if scheme is: fbide:// then it is some fbide command
         * if scheme is: http:// then it is a link to internet
         * if screme is: file:// then it is a file under fbide
         */
        virtual void OnLinkClicked(const wxHtmlLinkInfo& link)
        {
            wxURI uri(link.GetHref());
            if (uri.GetScheme() == _T("fbide"))
            {
                wxMessageBox (uri.GetServer());
            } else if (uri.GetScheme() == _T("http")) {
                ::wxLaunchDefaultBrowser(link.GetHref());
            } else if (uri.GetScheme() == _T("file")) {
                wxMessageBox (uri.GetServer() + uri.GetPath());
            }
        }
};

bool FBIde::OnInit()
{
    // Force creation of managers
    (void)Manager::Get();

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
    WelcomePage * welcome = new WelcomePage;
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
