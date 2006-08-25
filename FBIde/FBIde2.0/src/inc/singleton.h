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

#ifndef SINGLETON_H_INCLUDED
#define SINGLETON_H_INCLUDED

    template <class T> class Singleton
    {
        private:
            static T    * m_instance;
            static bool   m_isShutdown;

            explicit Singleton (const Singleton<T>&) { };
            Singleton<T>& operator= (Singleton<T> const&) { };


        protected:

            Singleton()
            {
                // Safety check
                assert(Singleton<T>::m_instance == 0);
            }

            virtual ~Singleton()
            {
                Singleton<T>::m_instance = NULL;
            }


        public:

            static inline bool IsOk() { return m_instance; }

            static inline T * Get()
            {
                if(m_instance == 0 && m_isShutdown == false)
                    m_instance = new T();

                return m_instance;
            }

            static void Free()
            {
                m_isShutdown = true;
                delete m_instance;
                m_instance = NULL;
            }
    };

    template<class T>T * Singleton<T>::m_instance = NULL;
    template<class T>bool  Singleton<T>::m_isShutdown = false;

#endif //SINGLETON_H_INCLUDED
