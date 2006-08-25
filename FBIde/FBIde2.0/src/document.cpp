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

#include "inc/manager.h"
#include "inc/document.h"

void DocumentBase::CloseDocument ()
{
    Manager::Get()->GetDocManager()->Remove (this);
}


void DocumentBase::AddDocument ()
{
    Manager::Get()->GetDocManager()->Add (this, false);
    return;
}


void DocumentBase::ShowDocument ()
{
    DocManager * mngr = Manager::Get()->GetDocManager();

    if (!mngr->Exists(this))
        mngr->Add (this, true);
    else
        mngr->Show (this);
}



void DocumentBase::HideDocument ()
{
    Manager::Get()->GetDocManager()->Hide (this);
}



void DocumentBase::IsDocumentVisible ()
{
    Manager::Get()->GetDocManager()->IsVisible (this);
}


RegAccessor * DocumentBase::GetDocumentData () const
{
/*
  Registry * reg = Manager::Get()->GetRegManager(_T("documents"));
  wxString folder;
  folder << _T("/") << GetDocumentId();
  reg->SetPath(folder);
  return reg;
*/
    return NULL;
}


RegAccessor * DocumentBase::GetDocumentProperties () const
{
/*
  Registry * reg = GetDocumentData();
  reg->SetPath(_T("properties"));
  return reg;
*/
    return NULL;
}

