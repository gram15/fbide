
#include "inc/wxall.h"
#include <wx/dynarray.h>

#include "inc/fb_doc.h"
#include "inc/fb_doclist.h"

FB_DocList::~FB_DocList() {
    for( int i = 0; i < static_cast<int>( m_Files.GetCount() ); i++ ) {
        delete m_Files[ i ];
        m_Files.RemoveAt( i );
    }
    WX_CLEAR_ARRAY( m_Files )
}

void FB_DocList::Add( wxFileName File ) {
    m_Files.Add( new wxFileName( File ) );
}

void FB_DocList::Remove( wxFileName File ) {
    for( int i = 0; i < static_cast<int>( m_Files.GetCount() ); i++ ) {
        if ( m_Files[ i ]->SameAs( File ) ) {
            delete m_Files[ i ];
            m_Files.RemoveAt( i );
            return;
        }
    }
}


void FB_DocList::ReName( wxFileName OldFile, wxFileName NewFile ) {
    Remove( OldFile );
    Add( NewFile );
}


bool FB_DocList::IsLoaded( wxFileName File ) {
    for( int i = 0; i < static_cast<int>( m_Files.GetCount() ); i++ ) {
        if ( m_Files[ i ]->SameAs( File ) ) return true;
    }
    return false;
}

