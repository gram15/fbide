#ifndef _FB_STC_HTML_H_
#define _FB_STC_HTML_H_

class FB_Doc;
class FB_Frame;
class FB_STC;

class FB_STC_HTML : public FB_STC
{
    private:
        void OnCharAdded        ( wxStyledTextEvent &event );        
        void OnCommentblock     ( wxCommandEvent& event );
        void OnUncommentblock   ( wxCommandEvent& event );
        
    public:
        FB_STC_HTML (  );
        FB_STC_HTML( wxWindow * parent, FB_Doc * Doc, FB_Frame * Ide );
        ~FB_STC_HTML(  );
        void CreateDoc ( wxWindow * parent, FB_Doc * Doc, FB_Frame * Ide );
        void LoadSettings (  );
};


#endif
