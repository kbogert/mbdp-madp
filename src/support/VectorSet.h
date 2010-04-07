/**\file VectorSet.h
 *
 * Authors:
 * Frans Oliehoek <faolieho@science.uva.nl>
 * Matthijs Spaan <mtjspaan@isr.ist.utl.pt>
 *
 * Copyright 2008 Universiteit van Amsterdam, Instituto Superior Tecnico
 *
 * This file is part of MultiAgentDecisionProcess.
 *
 * MultiAgentDecisionProcess is free software: you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * MultiAgentDecisionProcess is distributed in the hope that it will
 * be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with MultiAgentDecisionProcess.  If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * $Id: VectorSet.h 3604 2009-08-25 10:52:24Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _VECTORSET_H_
#define _VECTORSET_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"

#include <boost/numeric/ublas/matrix_sparse.hpp>
#include <boost/numeric/ublas/matrix.hpp>



/// Represents a set of (alpha) vectors.
typedef boost::numeric::ublas::matrix<double> VectorSet;

typedef VectorSet::const_iterator1 VScit1;
typedef VectorSet::iterator1 VSit1;
typedef VectorSet::const_iterator2 VScit2;
typedef VectorSet::iterator2 VSit2;

#endif /* !_VECTORSET_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
