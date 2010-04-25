/**\file POSGDiscrete.cpp
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
 * $Id: POSGDiscrete.cpp 2151 2008-01-21 16:32:52Z mtjspaan $
 */

#include "POSGDiscrete.h"    

using namespace std;

POSGDiscrete::POSGDiscrete(string name, string descr, string pf) :
    MultiAgentDecisionProcessDiscrete(name, descr, pf)
{
    _m_initialized = false;
    size_t nrAgents = GetNrAgents();
    POSG::SetNrAgents(nrAgents);
    POSG::SetInitialized(true);
    _m_p_rModel = vector<RewardModelMapping*>(nrAgents, 0);

}

POSGDiscrete::~POSGDiscrete()
{
    for(vector<RewardModelMapping*>::iterator it = _m_p_rModel.begin();
            it != _m_p_rModel.end(); it++)
        delete *it;
}

bool POSGDiscrete::SetInitialized(bool b)
{
    if( MultiAgentDecisionProcessDiscrete::SetInitialized(true) )
    {
        _m_initialized = b;
        return(true);
    }
    else
        return(false);
}

void POSGDiscrete::CreateNewRewardModel
    (Index agentI, size_t nrS, size_t nrJA)
{
    if(_m_initialized)
    delete(_m_p_rModel.at(agentI));

    _m_p_rModel.at(agentI) = new RewardModelMapping( nrS, nrJA);
}

string POSGDiscrete::SoftPrint() const
{
    stringstream ss;
    ss << MultiAgentDecisionProcessDiscrete::SoftPrint();
    ss << POSG::SoftPrint();

    if(_m_initialized)
    {
        for(Index agentI = 0; agentI < GetNrAgents(); agentI++)
        {
            ss << "Reward model for agent "<<agentI<<": " << endl;
            ss << _m_p_rModel.at(agentI)->SoftPrint() << endl;
        }
    }
    else
        throw E("POSGDiscrete components (reward model) not initialized");

    return(ss.str());
}

double POSGDiscrete::GetReward(Index agentI, State* s, JointAction* ja) 
    const
{
    return GetReward(agentI, 
            ((StateDiscrete*)s)->GetIndex(), 
            ((JointActionDiscrete*)ja)->GetIndex());
}

void POSGDiscrete::SetReward(Index agentI, Index sI, Index jaI,
                             Index sucSI, double r)
{
    double rOld=GetReward(agentI, sI,jaI),
        rExp=GetTransitionProbability(sI,jaI,sucSI)*r;
    SetReward(agentI, sI,jaI,rOld+rExp);
}

void POSGDiscrete::SetReward(Index agentI, Index sI, Index jaI, Index sucSI,
                             Index joI, double r)
{
    throw(E("POSGDiscrete::SetReward(agentI, sI,jaI,sucSI,joI,r) not implemented"));
}

