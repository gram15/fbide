#ifndef DOC_HTML_H_INCLUDED
#define DOC_HTML_H_INCLUDED

#include <wx/html/htmlwin.h>
#include <wx/uri.h>
#include "doc_stc.h"

class Doc_Html : public Document<wxHtmlWindow>
{
    private:
        wxString m_file;
    public:
        Doc_Html (const wxString & file = _T(""))
        {

            Create (Manager::Get()->GetDocManager()->GetWindow(), wxID_ANY);
            /*
            std::auto_ptr<RegAccessor>reg(new RegAccessor(_T("base")));
            reg->SetPath(_T("/paths"));
            wxString file;
            file << reg->ReadString(_T("base")) << _T("welcome.html");
            */
            LoadFile (file);
            m_file = file;
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
                if (uri.GetServer() == _T("menu"))
                {
                    #define REDIRECT(name) { \
                        wxString str(_T("/")); \
                        str << _T(#name); \
                        if (uri.GetPath() == str) \
                        { \
                            wxCommandEvent event(wxEVT_COMMAND_MENU_SELECTED, name); \
                            Manager::Get()->GetFrame()->GetEventHandler()->ProcessEvent(event); \
                        } }
                    REDIRECT(wxID_NEW)
                    REDIRECT(wxID_OPEN)
                    REDIRECT(wxID_CLOSE)
                    REDIRECT(wxID_SAVE)
                    REDIRECT(wxID_EXIT)

                    #undef REDIRECT
                } else if (uri.GetServer() == _T("reload")) {
                    LoadFile (m_file);
                }
            } else if (uri.GetScheme() == _T("http")) {
                ::wxLaunchDefaultBrowser(link.GetHref());
            } else if (uri.GetScheme() == _T("file")) {
                wxMessageBox (uri.GetServer() + uri.GetPath());
            }
        }
};

#endif // DOC_HTML_H_INCLUDED
