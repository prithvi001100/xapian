// om.h: Include all externally visible parts of om
//
// ----START-LICENCE----
// Copyright 1999,2000,2001 BrightStation PLC
// Copyright 2002 Ananova Ltd
// Copyright 2002,2003 Olly Betts
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation; either version 2 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
// USA
// -----END-LICENCE-----

#ifndef XAPIAN_INCLUDED_OM_H
#define XAPIAN_INCLUDED_OM_H

// Set defines for library version and check C++ ABI versions match
#include <xapian/version.h>

// Backward compatibility
#include <string>
typedef std::string om_termname;
#define OmStem Xapian::Stem
#define OmError Xapian::Error
#define OmLogicError Xapian::LogicError
#define OmRuntimeError Xapian::RuntimeError
#define OmAssertionError Xapian::AssertionError
#define OmUnimplementedError Xapian::UnimplementedError
#define OmInvalidArgumentError Xapian::InvalidArgumentError
#define OmInvalidOperationError Xapian::InvalidOperationError
#define OmDocNotFoundError Xapian::DocNotFoundError
#define OmRangeError Xapian::RangeError
#define OmInternalError Xapian::InternalError
#define OmDatabaseError Xapian::DatabaseError
#define OmFeatureUnavailableError Xapian::FeatureUnavailableError
#define OmNetworkError Xapian::NetworkError
#define OmNetworkTimeoutError Xapian::NetworkTimeoutError
#define OmDatabaseCorruptError Xapian::DatabaseCorruptError
#define OmDatabaseCreateError Xapian::DatabaseCreateError
#define OmOpeningError Xapian::OpeningError
#define OmDatabaseLockError Xapian::DatabaseLockError
#define OmDatabaseModifiedError Xapian::DatabaseModifiedError
#define OmInvalidResultError Xapian::InvalidResultError
#define OmTypeError Xapian::TypeError
#define OmInvalidDataError Xapian::InvalidDataError
#define OmDataFlowError Xapian::DataFlowError
#define OmExpandDecider Xapian::ExpandDecider
#define OmExpandDeciderAnd Xapian::ExpandDeciderAnd
#define OmExpandDeciderFilterTerms Xapian::ExpandDeciderFilterTerms
#define OmPositionListIterator Xapian::PositionListIterator
#define OmTermIterator Xapian::TermIterator
#define OmPostListIterator Xapian::PostListIterator

// om/omoutput.h used to include iostream, but xapian/output.h includes iosfwd
// instead.  So we include iostream here in case anyone relied on iostream
// being implicitly included.
#include <iostream>

// Types and exceptions
#include <xapian/types.h>
#include <xapian/error.h>
#include <xapian/errorhandler.h>

// Data access
#include "om/omdocument.h"
#include "om/omdatabase.h"
#include <xapian/postlistiterator.h>
#include <xapian/positionlistiterator.h>
#include <xapian/termiterator.h>
#include "om/omvalueiterator.h"

// Searching
#include "om/omenquire.h"
#include "om/omquery.h"
#include <xapian/expanddecider.h>

// Stemming
#include <xapian/stem.h>

// Output
#include <xapian/output.h>

#endif /* XAPIAN_INCLUDED_OM_H */
