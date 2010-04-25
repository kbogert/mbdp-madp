/**\file AgentQMDP.h
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
 * $Id: AgentQMDP.h 2959 2008-10-31 15:47:48Z faolieho $
 */

/* Only include this header file once. */
#ifndef _AGENTQMDP_H_
#define _AGENTQMDP_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"

#include "AgentSharedObservations.h"
#include "QFunctionJAOHInterface.h"
#include "JointBeliefSparse.h"
#include "QTable.h"



/**AgentQMDP represents an agent which uses a QMDP-based policy. */
class AgentQMDP : public AgentSharedObservations
{
private:    
    
    QTable _m_Q;

    size_t _m_t;

    JointBeliefSparse _m_jb;
    
    Index _m_prevJaI;

public:

    // Constructor, destructor and copy assignment.
    /// (default) Constructor
    AgentQMDP(const PlanningUnitDecPOMDPDiscrete &pu, Index id,
              const QTable &Q);

    /// Copy constructor.
    AgentQMDP(const AgentQMDP& a);

    /// Destructor.
    ~AgentQMDP();

    Index Act(Index joI);

    void ResetEpisode();

};


#endif /* !_AGENTQMDP_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
