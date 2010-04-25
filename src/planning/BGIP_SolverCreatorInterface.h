/**\file BGIP_SolverCreatorInterface.h
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
 * $Id: BGIP_SolverCreatorInterface.h 3603 2009-08-25 10:38:25Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _BGIP_SOLVERCREATORINTERFACE_H_
#define _BGIP_SOLVERCREATORINTERFACE_H_ 1

/* the include directives */
#include "Globals.h"

class BayesianGameIdenticalPayoffInterface;
#include "BayesianGameIdenticalPayoffSolver.h"

/** \brief BGIP_SolverCreatorInterface is an interface for classes that create
 * BGIP solvers.
 *
 * The template argument JP represents the joint policy class the
 * solver should return.
 */
template<class JP>
class BGIP_SolverCreatorInterface 
{
private:    
    
protected:
    
public:
    // Constructor, destructor and copy assignment.
    /// (default) Constructor
    
    virtual ~BGIP_SolverCreatorInterface(){};

    //operators:

    /// Returns a pointer to a new BGIP solver object.
    virtual BayesianGameIdenticalPayoffSolver<JP>* operator()
        (const BayesianGameIdenticalPayoffInterface& bg) const = 0;

    /// Returns a description of the solver creator.
    virtual std::string SoftPrint() const = 0;

};


#endif /* !_BGIP_SOLVERCREATORINTERFACE_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
