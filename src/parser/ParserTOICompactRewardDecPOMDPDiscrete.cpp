/**\file ParserTOICompactRewardDecPOMDPDiscrete.cpp
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
 * $Id: ParserTOICompactRewardDecPOMDPDiscrete.cpp 3604 2009-08-25 10:52:24Z mtjspaan $
 */

#include "ParserTOICompactRewardDecPOMDPDiscrete.h"

ParserTOICompactRewardDecPOMDPDiscrete::
ParserTOICompactRewardDecPOMDPDiscrete(
    TOICompactRewardDecPOMDPDiscrete
    *problem) :
    ParserTOIDecPOMDPDiscrete(problem),
    _m_problem(problem)
{
}

void ParserTOICompactRewardDecPOMDPDiscrete::
StoreDecPOMDP(DecPOMDPDiscrete *decpomdp,
              Index id)
{
    MultiAgentDecisionProcessDiscrete* madp = 
        _m_problem->GetIndividualMADPD(id);

    decpomdp->ExtractMADPDiscrete(madp);
    _m_problem->SetIndividualRewardModel(decpomdp->GetRewardModelPtr(), id);

    _m_problem->SetIndividualDecPOMDPD(decpomdp,id);
}

void ParserTOICompactRewardDecPOMDPDiscrete::ParseRewards()
{
    size_t nrAgentsInInteraction=2;
    std::vector<size_t> nrStates(nrAgentsInInteraction,0),
        nrActions(nrAgentsInInteraction,0);
    for(Index i=0;i!=nrAgentsInInteraction;++i)
    {
        nrStates[i]=_m_problem->GetIndividualMADPD(i)->GetNrStates();
        nrActions[i]=_m_problem->GetIndividualMADPD(i)->GetNrJointActions();
    }
    ParseRewards(nrAgentsInInteraction,nrStates,nrActions);
}

