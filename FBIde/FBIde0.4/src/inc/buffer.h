/**
 *    @class Buffer
 *    Buffer class
 *
 *    Holds information on files such as the file name, modification time,
 *    current highlighter, modification status and current selections. Also
 *    holds a pointer to the current document.
 *
 *    @todo Store the file name as a wxFileName object.
 *
 *    @verbatim
 *    (C) 2002-2003 by Matt Watkins <mattwat@users.sourceforge.net>
 *    Licensed under the MIT License. See License.txt for more information.
 *    @endverbatim
 */

#ifndef Buffer_H
#define Buffer_H

class Buffer
{
    public:
        Buffer(const wxString& fileName = "Untitled");

        const wxDateTime& GetModificationTime();
        void SetModificationTime(const wxDateTime& modTime);

        const wxString& GetFileName();
        void SetFileName(const wxString& fileName);
        bool IsUntitled();

        const wxString& GetHighlighter();
        void SetHighlighter(const wxString& highlighter);

        bool UpdateModTime();
        bool Exists();
        bool CheckModTime();

        void SetDocument(void* document);
        void* GetDocument();

        bool GetModified();
        void SetModified(bool modified);

        bool WasModified();
        void SetWasModified(bool wasModified);

        void SetPositions(int selStart, int selEnd);
        void SetCaretPos(int cp) { caretpos = cp; }
        int  GetCaretPos() { return caretpos; }
        void SetLine(int firstLine);

        int GetSelectionStart();
        int GetSelectionEnd();
        int GetLine();

    private:
        wxDateTime modTime;
        wxString fileName;
        wxString highlighter;

        bool wasModified;
        bool modified;

        void* document;

        int selStart, selEnd, firstLine, caretpos;
};

WX_DEFINE_ARRAY(Buffer*, BufferArray);

#endif // Buffer_H
