
#ifndef FB_DOCLIST_H
#define FB_DOCLIST_H

class FB_Doc;

WX_DEFINE_ARRAY( wxFileName *, FB_DocArray );

class FB_DocList {
    private:
        FB_DocArray m_Files;
    
    public:
        void Add( wxFileName File );
        void Remove( wxFileName File );
        void ReName( wxFileName OldFile, wxFileName NewFile );
        bool IsLoaded( wxFileName FileName );
        ~FB_DocList();
};

#endif
