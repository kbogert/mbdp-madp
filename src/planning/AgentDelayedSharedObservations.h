/**\file AgentDelayedSharedObservations.h
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
 * $Id: AgentDelayedSharedObservations.h 2944 2008-10-23 16:10:26Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _AGENTDELAYEDSHAREDOBSERVATIONS_H_
#define _AGENTDELAYEDSHAREDOBSERVATIONS_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"

#include "AgentDecPOMDPDiscrete.h"



/**AgentDelayedSharedObservations represents an agent that acts on local
 * observations and the shared observation at the previous time step. */
class AgentDelayedSharedObservations : public AgentDecPOMDPDiscrete
{
private:    
    
protected:
    
public:
    // Constructor, destructor and copy assignment.
    /// (default) Constructor
    AgentDelayedSharedObservations(const PlanningUnitDecPOMDPDiscrete &pu,
                                   Index id) :
        AgentDecPOMDPDiscrete(pu,id){};

    /// Copy constructor.
    AgentDelayedSharedObservations(const AgentDelayedSharedObservations& a) :
        AgentDecPOMDPDiscrete(a){};

    /// Destructor.
    ~AgentDelayedSharedObservations(){};
   
    virtual Index Act(Index oI, Index prevJoI) = 0;
};


#endif /* !_AGENTDELAYEDSHAREDOBSERVATIONS_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
