/////////////////////////////////////////////////////////////////////////////
// Name:        fb_stc.h
// Purpose:     
// Author:      VonGodric
// Modified by: 
// Created:     08/03/05 14:23:04
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _FB_STC_H_
#define _FB_STC_H_

class FB_Doc;
class FB_Frame;

// Base class - Also ordinary txt file
class FB_STC : public wxStyledTextCtrl {
    private:
        DECLARE_EVENT_TABLE()

        void OnUndo             ( wxCommandEvent& event );
        void OnRedo             ( wxCommandEvent& event );
        void OnCopy             ( wxCommandEvent& event );
        void OnCut              ( wxCommandEvent& event );
        void OnPaste            ( wxCommandEvent& event );
        void OnSelectall        ( wxCommandEvent& event );
        void OnSelectline       ( wxCommandEvent& event );
        void OnJustifyRight     ( wxCommandEvent& event );
        void OnJustifyLeft      ( wxCommandEvent& event );
        virtual void OnCommentblock     ( wxCommandEvent& event );
        virtual void OnUncommentblock   ( wxCommandEvent& event );
        virtual void OnCharAdded        ( wxStyledTextEvent &event );
        virtual void OnModified         ( wxStyledTextEvent& event );
        virtual void OnUpdateUI         ( wxStyledTextEvent& event );

    protected:
        FB_Doc      * m_Doc;
        FB_Frame    * m_Ide;
        bool        m_CanComment;
        
        void CreateSTC( wxWindow * parent, FB_Doc * Doc, FB_Frame * Ide );
        
    public:
        FB_STC ( wxWindow * parent, FB_Doc * Doc, FB_Frame * Ide );
        FB_STC (  );
        
        virtual ~FB_STC();
        
        virtual void CreateDoc ( wxWindow * parent, FB_Doc * Doc, FB_Frame * Ide );
        virtual void LoadSettings  ( );

        bool HasSelection() { 
            return ( GetSelectionEnd() - GetSelectionStart() ) > 0;
        }
        
        void ReplaceText ( int from, int to, const wxString& text );

        bool CanComment() { 
            return m_CanComment;
        }

        FB_Doc * GetDoc () const { return m_Doc; }
};

#endif
