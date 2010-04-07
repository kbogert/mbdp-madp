/**\file AgentBG.h
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
 * $Id: AgentBG.h 2944 2008-10-23 16:10:26Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _AGENTBG_H_
#define _AGENTBG_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"
#include "JointBeliefSparse.h"
#include "AgentDelayedSharedObservations.h"
#include "QAV.h"

class PerseusBGPlanner;
class JointBeliefInterface;
class JointPolicyPureVector;
class BayesianGameIdenticalPayoff;

/**AgentBG represents an agent which uses a BG-based policy. */
class AgentBG : public AgentDelayedSharedObservations
{
private:    
    
    QAV<PerseusBGPlanner> *_m_QBG;

    size_t _m_t;

    JointBeliefSparse _m_prevJB;
    
    BayesianGameIdenticalPayoff *_m_bgip;

    JointPolicyPureVector *_m_jpol;

    std::vector<Index> _m_oIs,_m_prevJoIs,_m_prevJaIs,_m_aIs;

    Index _m_jaIfirst;

    int GetMaximizingBGIndex(const JointBeliefInterface &jb) const;
    Index GetMaximizingActionIndex(const JointBeliefInterface &jb) const;

public:

    // Constructor, destructor and copy assignment.
    /// (default) Constructor
    AgentBG(const PlanningUnitDecPOMDPDiscrete &pu, Index id,
            QAV<PerseusBGPlanner> *QBG);

    /// Copy constructor.
    AgentBG(const AgentBG& a);

    /// Destructor.
    ~AgentBG();

    Index Act(Index oI, Index prevJoI);

    void ResetEpisode();

};


#endif /* !_AGENTBG_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
