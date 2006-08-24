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

#ifndef DOCMANAGER_H_INCLUDED
#define DOCMANAGER_H_INCLUDED

  #include "document.h"
  #include "documentlist.h"

  /**
   * DocManager
   *
   * This class is a base of document managment.
   * It manages document visibility, lifetime and etc
   * regarding to user responses.
   */

  class DocManager
  {
    private:
        DocumentList        m_list;
        wxBookCtrlBase    * m_bookCtrl;
        wxWindow          * m_window;

    public:
        DocManager ();
        ~DocManager ();

        /**
         * return pointer to window where
         * objects can be placed
         */
        wxWindow * GetWindow() const { return m_window; }

        /**
         * Add new document.
         * Returns true if added and false otherwise (already exists)
         */
        bool Add (DocumentBase * doc, bool show);

        /**
         * Add doduments from list
         * Returns number of documents added
         */
        int Add (DocumentList * docs, bool show);


        /**
         * Get all documents that have been added in a list
         */
        const DocumentList * GetList () const { return &m_list; }


        /**
         * Show document
         */
        bool Show (DocumentBase * doc);
        bool Show (int id) { return Show(m_list.GetById(id)); }


        /**
         * Hide
         */
        bool Hide (DocumentBase * doc);
        bool Hide (int id) { return Hide(m_list.GetById(id)); }


        /**
         * If document exists (has been added and not yet removed / destroyed)
         */
        bool Exists (DocumentBase * doc) { return m_list.Exists(doc); }
        bool Exists (int id) { return m_list.Exists(id); }


        /**
         * Remove document from manager
         */
        bool Remove (DocumentBase * doc);
        bool Remove (int id) { return Remove(m_list.GetById(id)); }


        /**
         * Return if document is visible or not
         */
        bool IsVisible (DocumentBase * doc);
        bool IsVisible (int id) { return IsVisible (m_list.GetById(id)); }


        /**
         * Traverse between documents.
         * return false if not possible (no document loaded?)
         */
        bool FocusNextDocument ();
        bool FocusPrevDocument ();


        /**
         * Focus given document.
         */
        bool FocusDocument (DocumentBase * doc);
        bool FocusDocument (int id);

  };


#endif // DOCMANAGER_H_INCLUDED
