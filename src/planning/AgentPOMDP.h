/**\file AgentPOMDP.h
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
 * $Id: AgentPOMDP.h 2959 2008-10-31 15:47:48Z faolieho $
 */

/* Only include this header file once. */
#ifndef _AGENTPOMDP_H_
#define _AGENTPOMDP_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"

#include "AgentSharedObservations.h"
#include "QFunctionJAOHInterface.h"
#include "QAV.h"
#include "PerseusPOMDPPlanner.h"

class JointBeliefInterface;

/**AgentPOMDP represents an agent which POMDP-based policy. */
class AgentPOMDP : public AgentSharedObservations
{
private:    
    
    QAV<PerseusPOMDPPlanner> *_m_QPOMDP;

    size_t _m_t;

    JointBeliefInterface *_m_jb;
    
    Index _m_prevJaI;

public:

    // Constructor, destructor and copy assignment.
    /// (default) Constructor
    AgentPOMDP(const PlanningUnitDecPOMDPDiscrete &pu, Index id,
               QAV<PerseusPOMDPPlanner> *QPOMDP);

    /// Copy constructor.
    AgentPOMDP(const AgentPOMDP& a);

    /// Destructor.
    ~AgentPOMDP();

    Index Act(Index joI);

    void ResetEpisode();

};


#endif /* !_AGENTPOMDP_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
