
/**
 *    @class BufferList
 *    Buffer List class
 *
 *    Buffer List class which holds all of the buffers.
 *
 *    @verbatim
 *    (C) 2002-2003 by Matt Watkins <mattwat@users.sourceforge.net>
 *    Licensed under the MIT License. See License.txt for more information.
 *    @endverbatim
 */

#ifndef BufferList_H
#define BufferList_H

#include <wx/dynarray.h>

class BufferList
{
    public:
        BufferList();
        ~BufferList();

        Buffer* AddBuffer(const wxString& highlighter = "Text");
        Buffer* AddFileBuffer(const wxString& fileName,
                              const wxString& highlighter);

        void SetBufferModified(int index);
        void SetBufferUnModified(int index);
        bool GetBufferModified(int index);

        int GetModifiedCount();
        int GetBufferCount();

        Buffer* GetBuffer(int index);
        Buffer* operator[](int index);
        void SetBuffer(int index, Buffer* buff);            
        Buffer* GetLastBuffer();
        void RemoveBuffer(int index);

    private:
        BufferArray buffers;
        int modifiedCount;
};

#endif
