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

#ifndef DOCUMENT_H_INCLUDED
#define DOCUMENT_H_INCLUDED

    #include "regaccessor.h"

    #define FBI_DOCUMENT_CAN_EDIT       1
    #define FBI_DOCUEMTN_CAN_SEARCH     (1 << 1)
    #define FBI_DOCUMENT_CAN_REPLACE    (1 << 2)
    #define FBI_DOCUMENT_CAN_UNDO       (1 << 3)
    #define FBI_DOCUMENT_CAN_REDO       (1 << 4)
    #define FBI_DOCUEMTN_CAN_SAVE       (1 << 5)


    /**
    * Document
    *
    * This class is a base for all documents.
    * Either they represent a real file, or just "virtual"
    * one -doesn't matter. It is used for having a single and
    * consistant interface for managing documents on the screen.
    *
    * Each created instance of the document has an unique id
    */
    class DocumentBase
    {
        private:
            int m_id;
            wxWindow * m_window;

            int GetNewId()
            {
                static int idx = 0;
                return ++idx;
            }

            int m_flags;


        public:

            /**
             * Constructors
             * Ensure unique id as well.
             */
            DocumentBase (wxWindow * window) : m_id(GetNewId()), m_window(window), m_flags(0) {  }
            virtual ~DocumentBase () { }


            /**
             * Add docuemtn to doc manager
             */
            void AddDocument ();
            void CloseDocument ();


            /**
             * Send event to document window
             */
            virtual bool ProcessDocumentEvent (wxEvent & event)
            {
                return m_window->GetEventHandler()->ProcessEvent (event);
            }


            /**
             * Show the document. If it is not in the
             * docManager then add
             */
            void ShowDocument ();


            /**
             * Hide the document if is visible.
             */
            void HideDocument ();


            /**
             * Return if is visible
             */
            void IsDocumentVisible ();


            /**
             * Get window
             */
            wxWindow * GetDocumentWindow () const { return m_window; }


            /**
             * Return ID of this document
             */
            int GetDocumentId () const { return m_id; }


            /**
             * Get name of the given document
             * Is used to place on tabs and etc...
             */
            virtual wxString GetDocumentName ()
            {
                wxString tmp;
                tmp << _T("Untitled ") << (int)GetDocumentId();
                return tmp;
            }

            void ResetDocumentFlags (int flags) { m_flags = flags; }
            int GetDocumentFlags () const { return m_flags; }
            void SetDocumentFlag (int flag) { m_flags |= flag; }
            void UnsetDocumentFlag (int flag) { if (m_flags & flag) m_flags ^= flag; }
            void ToggleDocumentFlag (int flag) { m_flags ^= flag; }
            bool IsDocumentFlagSet (int flag) const { return m_flags & flag; }

            /**
             * This function returns registry accessor
             * to the document's data in the registry.
             * Document data is located in
             * documents://docId/
             * where docID is the ID of the given document
             */
            RegAccessor * GetDocumentData () const;

            /**
             * Get Registry accessor to documents properties
             * documents://docId/proprties
             */
            RegAccessor * GetDocumentProperties () const;

    };



    /**
     * This temmplate class is used to derive
     * new document classes. Template argument
     * must be either wxWindow class or derived
     * from it.
     */
    template<class T>
        class Document : public DocumentBase, public T
        {
            public:
                Document () : DocumentBase(this)
                {
                    T::Hide();
                    AddDocument(); // Add this document to docManager
                }

                virtual ~Document ()
                {
                    CloseDocument(); // Remove this document from docManager
                }
        };


#endif // DOCUMENT_H_INCLUDED
