/**\file AlphaVectorPOMDP.h
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
 * $Id: AlphaVectorPOMDP.h 2944 2008-10-23 16:10:26Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _ALPHAVECTORPOMDP_H_
#define _ALPHAVECTORPOMDP_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"

#include "AlphaVectorPlanning.h"

class PlanningUnitDecPOMDPDiscrete;
class AlphaVector;



/**AlphaVectorPOMDP implements POMDP specific functionality for
 * alpha-vector based planning. */
class AlphaVectorPOMDP : virtual public AlphaVectorPlanning
{
private:    
    
protected:
    
public:
    // Constructor, destructor and copy assignment.
    /// (default) Constructor
    AlphaVectorPOMDP(const PlanningUnitDecPOMDPDiscrete& pu);

    /// Destructor.
    virtual ~AlphaVectorPOMDP();

    /// Computes the AlphaVector resulting from backing up JointBeliefInterface
    /// \a b with the back-projected vectors in \a G.
    AlphaVector BeliefBackup(const JointBeliefInterface &b,
                             const GaoVectorSet &G) const;
    
    AlphaVector BeliefBackup(const JointBeliefInterface &b,
                             Index a,
                             const GaoVectorSet &G) const;

};


#endif /* !_ALPHAVECTORPOMDP_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
