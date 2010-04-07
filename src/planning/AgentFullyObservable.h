/**\file AgentFullyObservable.h
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
 * $Id: AgentFullyObservable.h 2979 2008-11-03 20:00:13Z faolieho $
 */

/* Only include this header file once. */
#ifndef _AGENTFULLYOBSERVABLE_H_
#define _AGENTFULLYOBSERVABLE_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"

#include "AgentDecPOMDPDiscrete.h"
#include <vector>

/** \brief AgentFullyObservable represents an agent that receives the
 * true state, the joint observation and also the reward signal. */
class AgentFullyObservable : 
    virtual public AgentDecPOMDPDiscrete
{
private:    
    
protected:
    
public:
    // Constructor, destructor and copy assignment.
    /// (default) Constructor
    /**a derived class should first call the AgentDecPOMDPDiscrete constructor.
     * Therefore, we do not need to pass along any arguments anymore here.
     */
    AgentFullyObservable() :
        AgentDecPOMDPDiscrete() {};
    AgentFullyObservable(const PlanningUnitDecPOMDPDiscrete &pu, Index id) :
        AgentDecPOMDPDiscrete(pu,id){};

    /// Copy constructor.
    AgentFullyObservable(const AgentFullyObservable& a) :
        AgentDecPOMDPDiscrete(a){};

    /// Destructor.
    ~AgentFullyObservable(){};

    /** \brief Return an individual action based on state, last joint
     * observation and reward. */
    virtual Index Act(Index sI, Index joI, double reward) = 0;
};


#endif /* !_AGENTFULLYOBSERVABLE_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
