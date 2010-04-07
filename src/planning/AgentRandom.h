/**\file AgentRandom.h
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
 * $Id: AgentRandom.h 2979 2008-11-03 20:00:13Z faolieho $
 */

/* Only include this header file once. */
#ifndef _AGENTRANDOM_H_
#define _AGENTRANDOM_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"

#include "AgentFullyObservable.h"
#include "AgentLocalObservations.h"

/** \brief AgentRandom represents an agent which chooses action
 * uniformly at random. */
class AgentRandom : 
    public AgentFullyObservable 
    , public AgentLocalObservations 
    //, TODO, add all agent types (a random agent can have any type)
{
private:    
    
public:

    // Constructor, destructor and copy assignment.
    /// (default) Constructor
    AgentRandom(const PlanningUnitDecPOMDPDiscrete &pu, Index id);

    /// Copy constructor.
    AgentRandom(const AgentRandom& a);

    /// Destructor.
    ~AgentRandom();

    /// Returns an individual action uniformly at random.
    Index Act();
    Index Act(Index joI)
    {return Act();}
    Index Act(Index sI, Index joI, double reward) 
    {return Act();}

    void ResetEpisode();

};


#endif /* !_AGENTRANDOM_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
