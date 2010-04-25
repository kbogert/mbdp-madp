/**\file AgentSharedObservations.h
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
 * $Id: AgentSharedObservations.h 2127 2008-01-18 14:06:16Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _AGENTSHAREDOBSERVATIONS_H_
#define _AGENTSHAREDOBSERVATIONS_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"
#include "AgentDecPOMDPDiscrete.h"

/** \brief AgentSharedObservations is represents an agent that
 * benefits from free communication, i.e., it can share all its
 * observations. */
class AgentSharedObservations : public AgentDecPOMDPDiscrete
{
private:    
    
protected:
    
public:
    // Constructor, destructor and copy assignment.
    /// (default) Constructor
    AgentSharedObservations(const PlanningUnitDecPOMDPDiscrete &pu, Index id) :
        AgentDecPOMDPDiscrete(pu,id){};

    /// Copy constructor.
    AgentSharedObservations(const AgentSharedObservations& a) :
        AgentDecPOMDPDiscrete(a){};

    /// Destructor.
    ~AgentSharedObservations(){};

    /** \brief Return an individual action index based on a joint
     *  observation index. */
    virtual Index Act(Index joI) = 0;

};


#endif /* !_AGENTSHAREDOBSERVATIONS_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
