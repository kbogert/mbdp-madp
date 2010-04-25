/**\file TOIFactoredRewardDecPOMDPDiscrete.cpp
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
 * $Id: TOIFactoredRewardDecPOMDPDiscrete.cpp 4016 2010-03-11 16:56:02Z mtjspaan $
 */

#include "TOIFactoredRewardDecPOMDPDiscrete.h"

using namespace std;

#define DEBUG_TOIFactoredRewardDecPOMDPDiscrete 0

TOIFactoredRewardDecPOMDPDiscrete::
TOIFactoredRewardDecPOMDPDiscrete(
    string name, string descr, string pf) :
    TOIDecPOMDPDiscrete(name, descr, pf)
{
    _m_initialized = false;
}

TOIFactoredRewardDecPOMDPDiscrete::
TOIFactoredRewardDecPOMDPDiscrete(const TOIFactoredRewardDecPOMDPDiscrete& o) 
{
    throw(E("TOIFactoredRewardDecPOMDPDiscrete: copy ctor not yet implemented"));
}

TOIFactoredRewardDecPOMDPDiscrete::~TOIFactoredRewardDecPOMDPDiscrete()
{
    for(unsigned int i=0;i!=_m_p_rModels.size();++i)
        delete(_m_p_rModels[i]);
}

//Copy assignment operator
TOIFactoredRewardDecPOMDPDiscrete&
TOIFactoredRewardDecPOMDPDiscrete::operator=
(const TOIFactoredRewardDecPOMDPDiscrete& o)
{
    if (this == &o) return *this;   // Gracefully handle self assignment
    // Put the normal assignment duties here...

    throw(E("TOIFactoredRewardDecPOMDPDiscrete: assignment not yet implemented"));

    return *this;
}

bool TOIFactoredRewardDecPOMDPDiscrete::SetInitialized(bool b)
{
    if(b == false)
    {
        _m_initialized = false;
        return(true);
    }

    if( TOIDecPOMDPDiscrete::SetInitialized(true))
    {
        if( b == true )
        {
            if (_m_p_rModels.size()!=GetNrAgents())
                throw E("TOIFactoredRewardDecPOMDPDiscrete::SetInitialized(true) : no reward models specified yet!");
                
            for(unsigned int i=0;i!=GetNrAgents();++i)
                if (_m_p_rModels[i] == 0)
                    throw E("TOIFactoredRewardDecPOMDPDiscrete::SetInitialized(true) : no reward model specified yet! ( _m_p_rModels[i] == 0 )");

            //\todo TODO: do we need to check the reward model? any further?
        }
        _m_initialized = b;
        return(true);
    }
    else
        return(false);
}

double TOIFactoredRewardDecPOMDPDiscrete::GetReward(Index sI, Index jaI) const
{
    double reward=0;
    vector<Index> indSIs=JointToIndividualStateIndices(sI),
        indAIs=JointToIndividualActionIndices(jaI);

    for(unsigned int i=0;i!=GetNrAgents();++i)
        reward+=GetIndividualReward(indSIs[i],indAIs[i],i);

    reward+=_m_p_rModel->Get(indSIs,indAIs);
//    reward+=_m_p_rModel->Get(sI,jaI);

#if DEBUG_TOIFactoredRewardDecPOMDPDiscrete
    cout << "GetReward(" << sI << "," << jaI << ") = " << reward << endl;
#endif
    return(reward);
}

double
TOIFactoredRewardDecPOMDPDiscrete::GetReward(const std::vector<Index> &sIs,
                                             const std::vector<Index> &aIs) const
{
    double reward=0;

    for(unsigned int i=0;i!=GetNrAgents();++i)
        reward+=GetIndividualReward(sIs[i],aIs[i],i);

    reward+=_m_p_rModel->Get(sIs,aIs);

#if DEBUG_TOIFactoredRewardDecPOMDPDiscrete
    cout << "GetReward(" << sI << "," << jaI << ") = " << reward << endl;
#endif

    return(reward);
}

void TOIFactoredRewardDecPOMDPDiscrete::
SetIndividualRewardModel(RewardModel* rewardModel,
                         Index agentID)
{
    if(_m_p_rModels.size()<=agentID)
        _m_p_rModels.resize(agentID+1);

    _m_p_rModels[agentID]=rewardModel;
}

double TOIFactoredRewardDecPOMDPDiscrete::
GetIndividualReward(Index indSI, Index indAI, Index agentID) const
{
    double reward=_m_p_rModels[agentID]->Get(indSI,indAI);
#if DEBUG_TOIFactoredRewardDecPOMDPDiscrete
    cout << "GetIndividualReward[" << agentID << "](" << indSI << "," << indAI
         << ") = " << reward << endl;
#endif
    return(reward);
}

string TOIFactoredRewardDecPOMDPDiscrete::SoftPrint() const
{
    stringstream ss;
    ss << TOIDecPOMDPDiscrete::SoftPrint();

    if(_m_initialized)
    {
        ss << "Reward models: " << endl;
        for(unsigned int i=0;i!=GetNrAgents();++i)
        {
            ss << "Individual rewards for agent " << i << endl;
            ss << _m_p_rModels[i]->SoftPrint();
        }
    }
    else
        throw E("TOIFactoredRewardDecPOMDPDiscrete components (reward model) not initialized");

    return(ss.str());
}
