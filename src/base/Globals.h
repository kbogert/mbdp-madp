/**\file Globals.h
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
 * $Id: Globals.h 4016 2010-03-11 16:56:02Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _GLOBALS_H_
#define _GLOBALS_H_ 1

#include <vector>
#include <cmath>
#include <iostream>
#include "versions.h"
#include <limits.h>

/// Globals contains several definitions global to the MADP toolbox.
namespace Globals {

#define INDEX_MAX UINT_MAX

/// A general index.
typedef unsigned int Index;
/// A long long index.
typedef unsigned long long int LIndex;

/* constants */

/// The highest horizon we will consider.
/** When the horizon of a problem is set to this value, we consider it
 * an infinite-horizon problem. */
const unsigned int MAXHORIZON=999999;

/// The precision for probabilities.

/** Used to determine when two probabilities are considered equal, for
 * instance when converting full beliefs to sparse beliefs. */
const double PROB_PRECISION=1e-8;
/** Used to determine when two (immediate) rewards are considered equal */
const double REWARD_PRECISION=1e-8;

bool EqualProbability(double p1, double p2);
bool EqualReward(double r1, double r2);

/// The initial (=empty) joint observation history index.
const Index INITIAL_JOHI=0;
/// The initial (=empty) joint action-observation history index.
const Index INITIAL_JAOHI=0;

/// Inherited from Tony's POMDP file format.
enum reward_t {REWARD, COST};

}

using namespace Globals;

//Frans: should not matter if NDEBUG is defined?
//http://lists.boost.org/MailArchives/ublas/2007/02/1764.php
// Tell Boost Ublas to not use exceptions for speed reasons.
//#define BOOST_UBLAS_NO_EXCEPTIONS 1


#include "PrintTools.h"
using namespace PrintTools;

#include "E.h"
#include "EInvalidIndex.h"

#endif /* !_GLOBALS_H_ */


// Local Variables: ***
// mode:c++ ***
// End: ***
