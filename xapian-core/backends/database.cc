/* database.cc: Methods for Database
 *
 * ----START-LICENCE----
 * Copyright 1999,2000,2001 BrightStation PLC
 * Copyright 2002 Ananova Ltd
 * Copyright 2003 Olly Betts
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
 * USA
 * -----END-LICENCE-----
 */

#include <config.h>
#include "database.h"
#include "xapian/error.h"

Database::Database()
	: session_in_progress(false),
	  transaction_in_progress(false)
{
}

Database::~Database()
{
    // Can't end_session() here because derived class destructors have already
    // run, and the derived classes therefore don't exist.  Thus, the
    // derived classes have responsibility for ending outstanding sessions
    // (by calling internal_end_session()):  let's check they did their job.
    Assert(!session_in_progress);
}

void
Database::keep_alive() const
{
    /* For the normal case of local databases, nothing needs to be done.
     */
}

void
Database::ensure_session_in_progress()
{
    if (!session_in_progress) {
	do_begin_session();
	session_in_progress = true;
    }
}

void
Database::internal_end_session()
{
    if (!session_in_progress) return;

    if (transaction_in_progress) {
	try {
	    transaction_in_progress = false;
	    do_cancel_transaction();
	} catch (...) {
	    session_in_progress = false;
	    try {
		do_end_session();
	    } catch (...) {
		// Discard exception - we want to re-throw the first error
		// which occured
	    }
	    throw;
	}
    }

    session_in_progress = false;
    do_end_session();
}

void
Database::flush()
{
    if (session_in_progress) {
	do_flush();
    }
}

void
Database::begin_transaction()
{
    ensure_session_in_progress();
    if (transaction_in_progress)
	throw Xapian::InvalidOperationError("Cannot begin transaction - transaction already in progress");
    do_begin_transaction();
    transaction_in_progress = true;
}

void
Database::commit_transaction()
{
    if (!transaction_in_progress)
	throw Xapian::InvalidOperationError("Cannot commit transaction - no transaction currently in progress");
    transaction_in_progress = false;
    Assert(session_in_progress);
    do_commit_transaction();
}

void
Database::cancel_transaction()
{
    if (!transaction_in_progress)
	throw Xapian::InvalidOperationError("Cannot cancel transaction - no transaction currently in progress");
    transaction_in_progress = false;
    Assert(session_in_progress);
    do_cancel_transaction();
}

om_docid
Database::add_document(const OmDocument & document)
{
    ensure_session_in_progress();
    return do_add_document(document);
}

void
Database::delete_document(om_docid did)
{
    ensure_session_in_progress();
    do_delete_document(did);
}

void
Database::replace_document(om_docid did, const OmDocument & document)
{
    ensure_session_in_progress();
    do_replace_document(did, document);
}
