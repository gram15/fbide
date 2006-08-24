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

#ifndef DOCUMENTLIST_H_INCLUDED
#define DOCUMENTLIST_H_INCLUDED

    #include "document.h"

    /**
     * DocumentList
     *
     * This class holds documents
     */
    class DocumentList
    {
        private:
            typedef std::vector<DocumentBase *> docList;
            docList m_list;

        public:
            typedef docList::iterator iterator;

            DocumentList () { }
            DocumentList (const DocumentList & list);

            /**
             * stl style functions for iterator usage
             */
            iterator begin () { return m_list.begin(); }
            iterator end () { return m_list.end(); }
            void erase (iterator loc) { m_list.erase (loc); }


            void Add (DocumentBase * doc) { m_list.push_back(doc); }

            /**
             * return document
             */
            DocumentBase * Get (size_t idx) const { return m_list.at (idx); }
            DocumentBase * operator[] (size_t idx) const { return m_list.at (idx); }
            DocumentBase * GetById (int id) const
            {
                for (size_t i = 0; i < Count(); i++)
                    if (m_list[i]->GetDocumentId() == id) return m_list[i];
                return NULL;
            }


            /**
             * Return document ID based on index
             */
            int GetId (size_t idx) const
            {
                return m_list[idx]->GetDocumentId();
            }


            /**
             * Get document index based on ID
             */
            size_t GetIndex (int id) const
            {
                for (size_t i = 0; i < Count(); i++)
                    if (m_list[i]->GetDocumentId() == id) return i;
                return 0;
            }


            /**
             * Get document index based on DocumentBse *
             */
            size_t GetIndex (DocumentBase * doc) const
            {
                for (size_t i = 0; i < Count(); i++)
                    if (m_list[i]->GetDocumentId() == doc->GetDocumentId()) return i;
                return 0;
            }


            /**
             * return if document with given document with given id exists
             */
            bool Exists (int id) const
            {
                for (size_t i = 0; i < Count(); i++)
                    if (m_list[i]->GetDocumentId() == id) return true;
                return false;
            }


            /**
             * return if document with given document exists
             */
            bool Exists (DocumentBase * doc) const
            {
                for (size_t i = 0; i < Count(); i++)
                    if (m_list[i] == doc) return true;
                return false;
            }


            /**
             * return count of documents
             */
            size_t Count() const
            {
                return m_list.size();
            }


            /**
             * remove from list by ID
             */
            void Remove (size_t index)
            {
                size_t idx = 0;
                for (iterator iter = begin(); iter != end(); iter++, idx++)
                    if (idx == index)
                    {
                        erase (iter);
                        return;
                    }
            }


            /**
             * Remove from list by Documnent *
             */
            void Remove (DocumentBase * doc) { RemoveByID (doc->GetDocumentId()); }


            /**
             * Remove by id
             */
            void RemoveByID (int id)
            {
                for (iterator iter = begin(); iter != end(); iter++)
                    if ((*iter)->GetDocumentId() == id)
                    {
                        erase(iter);
                        return;
                    }
            }
    };


#endif // DOCUMENTLIST_H_INCLUDED
