#ifndef _FB_STC_FB_H_
#define _FB_STC_FB_H_

class FB_Doc;
class FB_Frame;
class FB_STC;

class FB_STC_FB : public FB_STC
{
    private:
        void OnCharAdded        ( wxStyledTextEvent &event );        
        void OnModified         ( wxStyledTextEvent& event );
        void OnUpdateUI         ( wxStyledTextEvent& event );

        void OnCommentblock     ( wxCommandEvent& event );
        void OnUncommentblock   ( wxCommandEvent& event );

        bool IsBrace( wxChar brace ) {
            return brace == '{' || brace == '}' ||
            brace == '[' || brace == ']' ||
            brace == '(' || brace == ')';
        }
        
        int m_braceLoc;

    public:
        FB_STC_FB (  );
        FB_STC_FB( wxWindow * parent, FB_Doc * Doc, FB_Frame * Ide );
        ~FB_STC_FB(  );
        void CreateDoc ( wxWindow * parent, FB_Doc * Doc, FB_Frame * Ide );
        void LoadSettings (  );
};


#endif
