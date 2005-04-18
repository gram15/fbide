
#include "inc/main.h"

/**
 * BufferList constructor.
 * Constructs a BufferList object holding multiple buffers.
 * @see BufferList::~BufferList()
 */
BufferList::BufferList()
    : modifiedCount(0)
{
}

/**
 * BufferList destructor.
 * Cleans up all of the buffers held by the BufferList.
 * @see BufferList::BufferList()
 */
BufferList::~BufferList()
{
    WX_CLEAR_ARRAY(buffers)
}

/**
 * Adds a new untitled buffer using the highlighter passed to the function.
 * @param highlighter The highlighter the new buffer should use.
 * @see BufferList::AddFileBuffer(const wxString& fileName, const wxString& highlighter)
 * @return A pointer to the newly created buffer object.
 */
Buffer* BufferList::AddBuffer(const wxString& highlighter)
{
    Buffer* buff = new Buffer("Untitled");
    buffers.Add(buff);

    return buff;
}

/**
 * Adds a new buffer with a file name. This function also initializes the
 * highlighter for the new buffer.
 * @param fileName The file name the new buffer should use.
 * @param highlighter The highlighter the new buffer should use.
 * @see BufferList::AddBuffer(const wxString& highlighter)
 * @return A pointer to the newly created buffer object.
 */
Buffer* BufferList::AddFileBuffer(const wxString& fileName, const wxString& highlighter)
{
    Buffer* buff = new Buffer(fileName);
    buffers.Add(buff);

    return buff;
}

/**
 * Gets a pointer to the buffer at the index specified.
 * @param index The index of the buffer to get a pointer for.
 * @see BufferList::operator[](int index)
 * @return A pointer to the buffer specified by index.
 */
Buffer* BufferList::GetBuffer(int index)
{
    return buffers[index];
}

/**
 * Gets the number of buffers in the buffer list.
 * @see BufferList::GetModifedCount()
 * @return The number of buffers in this buffer list.
 */
int BufferList::GetBufferCount()
{
    return buffers.GetCount();
}

/**
 * Checks to see if the buffer at index is modified.
 * @param index The index of the buffer to check.
 * @return Whether the buffer is modified or not.
 */
bool BufferList::GetBufferModified(int index)
{
    return buffers[index]->GetModified();
}

/**
 * Gets the last buffer in the buffer list.
 * @return A pointer to the last buffer in the buffer list.
 */
Buffer* BufferList::GetLastBuffer()
{
    return buffers.Last();
}

/**
 * Gets the number of buffers which are currently modified.
 * @see BufferList::GetBufferCount
 * @return How many buffers are currently modified.
 */
int BufferList::GetModifiedCount()
{
    return modifiedCount;
}

/**
 * Gets a pointer to the buffer at the index specified.
 * @param index The index of the buffer to get a pointer for.
 * @see BufferList::GetBuffer(int index)
 * @return A pointer to the buffer specified by index.
 */
Buffer* BufferList::operator[](int index)
{
    return buffers[index];
}

/**
 * Removes the buffer at index.
 * @param index The index of the buffer to remove.
 * @see BufferList::AddBuffer(const wxString& highlighter)
 * @see BufferList::AddFileBuffer(const wxString& fileName, const wxString& highlighter)
 */
void BufferList::RemoveBuffer(int index)
{
    delete buffers[index];
    buffers.RemoveAt(index);
}

/**
 * Sets the buffer at index as modified.
 * @param index The index of the buffer to set as modified.
 * @see BufferList::SetBufferUnModified(int index)
 */
void BufferList::SetBufferModified(int index)
{
    buffers[index]->SetModified(true);
    modifiedCount++;
}

/**
 * Sets the buffer at index as unmodified.
 * @param index The index of the buffer to set as unmodified.
 * @see BufferList::SetBufferModified(int index)
 */
void BufferList::SetBufferUnModified(int index)
{
    buffers[index]->SetModified(false);
    modifiedCount--;
}

void BufferList::SetBuffer(int index, Buffer* buff) {
    buffers[index] = buff;
}

