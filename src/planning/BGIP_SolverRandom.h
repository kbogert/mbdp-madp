/**\file BGIP_SolverRandom.h
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
 * $Id: BGIP_SolverRandom.h 3604 2009-08-25 10:52:24Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _BGIP_SOLVERRANDOM_H_
#define _BGIP_SOLVERRANDOM_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"
#include "JointPolicyPureVector.h"
#include "BayesianGameIdenticalPayoffSolver.h"



/** \brief BGIP_SolverRandom creates random solutions to Bayesian
 * games for testing purposes
 */
class BGIP_SolverRandom : public BayesianGameIdenticalPayoffSolver<JointPolicyPureVector>
{
private:    

protected:
    
public:
    // Constructor, destructor and copy assignment.

    /**Constructor. Directly Associates a problem with the planner
     * Information regarding the problem is used to construct a joint policy
     * of the proper shape.*/
    BGIP_SolverRandom(const BayesianGameIdenticalPayoff& bg);

    double Solve();
        
};


#endif /* !_BGIP_SOLVERRANDOM_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
