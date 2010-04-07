/**\file ValueFunctionPOMDPDiscrete.h
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
 * $Id: ValueFunctionPOMDPDiscrete.h 2747 2008-09-13 09:54:55Z faolieho $
 */

/* Only include this header file once. */
#ifndef _VALUEFUNCTIONPOMDPDISCRETE_H_
#define _VALUEFUNCTIONPOMDPDISCRETE_H_ 1

/* the include directives */

#include "AlphaVector.h"
#include "PrintTools.h"
#include <string>

/// A ValueFunctionPOMDPDiscrete is just a vector of AlphaVector's.
typedef std::vector<AlphaVector> ValueFunctionPOMDPDiscrete;
/// A const_iterator for ValueFunctionPOMDPDiscrete.
typedef ValueFunctionPOMDPDiscrete::const_iterator VFPDcit;

/// A QFunctionsDiscrete is just a vector of
/// ValueFunctionPOMDPDiscrete, one for each action.
typedef std::vector<ValueFunctionPOMDPDiscrete> QFunctionsDiscrete;
typedef QFunctionsDiscrete::const_iterator QFDcit;

/// A QFunctionsDiscreteNonStationary is just a vector of
/// QFunctionsDiscrete, one for each time step.
typedef std::vector<QFunctionsDiscrete> QFunctionsDiscreteNonStationary;
typedef QFunctionsDiscreteNonStationary::const_iterator QFDNScit;

#endif /* !_VALUEFUNCTIONPOMDPDISCRETE_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
