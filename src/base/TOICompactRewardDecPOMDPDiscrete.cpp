/**\file TOICompactRewardDecPOMDPDiscrete.cpp
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
 * $Id: TOICompactRewardDecPOMDPDiscrete.cpp 4016 2010-03-11 16:56:02Z mtjspaan $
 */

#include "TOICompactRewardDecPOMDPDiscrete.h"

using namespace std;

#define DEBUG_TOICompactRewardDecPOMDPDiscrete 0

TOICompactRewardDecPOMDPDiscrete::
TOICompactRewardDecPOMDPDiscrete(
    string name, string descr, string pf) :
    TOIDecPOMDPDiscrete(name, descr, pf),
    _m_nrTwoAgentStates(2,0),
    _m_nrTwoAgentActions(2,0)
{
    _m_initialized = false;
}

TOICompactRewardDecPOMDPDiscrete::
TOICompactRewardDecPOMDPDiscrete(const TOICompactRewardDecPOMDPDiscrete& o) 
{
    throw(E("TOICompactRewardDecPOMDPDiscrete: copy ctor not yet implemented"));
}

TOICompactRewardDecPOMDPDiscrete::~TOICompactRewardDecPOMDPDiscrete()
{
    for(unsigned int i=0;i!=_m_p_rModels.size();++i)
        delete(_m_p_rModels[i]);
}

//Copy assignment operator
TOICompactRewardDecPOMDPDiscrete&
TOICompactRewardDecPOMDPDiscrete::operator=
(const TOICompactRewardDecPOMDPDiscrete& o)
{
    if (this == &o) return *this;   // Gracefully handle self assignment
    // Put the normal assignment duties here...

    throw(E("TOICompactRewardDecPOMDPDiscrete: assignment not yet implemented"));

    return *this;
}

bool TOICompactRewardDecPOMDPDiscrete::SetInitialized(bool b)
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
                throw E("TOICompactRewardDecPOMDPDiscrete::SetInitialized(true) : no reward models specified yet!");
                
            for(unsigned int i=0;i!=GetNrAgents();++i)
                if (_m_p_rModels[i] == 0)
                    throw E("TOICompactRewardDecPOMDPDiscrete::SetInitialized(true) : no reward model specified yet! ( _m_p_rModels[i] == 0 )");

            size_t nrStates=GetIndividualDecPOMDPD(0)->GetNrStates();
            for(unsigned int i=0;i!=GetNrAgents();++i)
                if(GetIndividualDecPOMDPD(i)->GetNrStates()!=nrStates)
                    throw E("TOICompactRewardDecPOMDPDiscrete::SetInitialized(true) : all agents are required to have the same state space (same number of individual states)");
        }

        for(Index i=0;i!=2;++i)
        {
            _m_nrTwoAgentStates[i]=GetIndividualMADPD(i)->GetNrStates();
            _m_nrTwoAgentActions[i]=GetIndividualMADPD(i)->GetNrJointActions();
        }

        _m_initialized = b;
        return(true);
    }
    else
        return(false);
}

double TOICompactRewardDecPOMDPDiscrete::GetReward(Index sI, Index jaI) const
{
    return(GetReward(JointToIndividualStateIndices(sI),
                     JointToIndividualActionIndices(jaI)));
}

double TOICompactRewardDecPOMDPDiscrete::GetReward(
    const std::vector<Index> &indSIs,
    const std::vector<Index> &indAIs) const
{
    double reward=0;

    for(unsigned int i=0;i!=GetNrAgents();++i)
        reward+=GetIndividualReward(indSIs[i],indAIs[i],i);

    switch(GetNrAgents())
    {
    case 2:
        reward+=_m_p_rModel->Get(indSIs,indAIs);
        break;
    default:
    {
        vector<Index> indexVec(2,0);
        vector<size_t> nrElems(2,GetNrAgents());

        do
        {
#if 0
            if(indexVec[0]!=indexVec[1] &&
               GetTwoAgentReward(indexVec[0],indexVec[1],indSIs,indAIs)!=0)
                cout << "adding  i " << indexVec[0]
                     << " si " << indSIs[indexVec[0]] 
                     << GetIndividualMADPD(indexVec[0])->GetState(indSIs[indexVec[0]])->SoftPrint()
                     << " j " << indexVec[1] 
                     << " sj " << indSIs[indexVec[1]]
                     << GetIndividualMADPD(indexVec[1])->GetState(indSIs[indexVec[1]])->SoftPrint()
                     << " r "
                     << GetTwoAgentReward(indexVec[0],indexVec[1],
                                          indSIs,indAIs) << endl;
#endif
            if(indexVec[0]!=indexVec[1])
                reward+=GetTwoAgentReward(indexVec[0],indexVec[1],
                                          indSIs,indAIs);
        }
        while(!IndexTools::Increment(indexVec,nrElems));

#if 0
        reward2+=GetTwoAgentReward(0,1,indSIs,indAIs);
        reward2+=GetTwoAgentReward(1,0,indSIs,indAIs);

        reward2+=GetTwoAgentReward(0,2,indSIs,indAIs);
        reward2+=GetTwoAgentReward(2,0,indSIs,indAIs);

        reward2+=GetTwoAgentReward(1,2,indSIs,indAIs);
        reward2+=GetTwoAgentReward(2,1,indSIs,indAIs);
#endif
        break;
    }
    }

#if DEBUG_TOICompactRewardDecPOMDPDiscrete
    cout << "GetReward(" << sI << "," << jaI << ") = " << reward << endl;
#endif
    return(reward);
}

double
TOICompactRewardDecPOMDPDiscrete::
GetTwoAgentReward(Index i, Index j,
                  const vector<Index> &indSIs,
                  const vector<Index> &indAIs) const
{
    vector<Index> sIs(2,0), aIs(2,0);

    sIs[0]=indSIs[i]; aIs[0]=indAIs[i];
    sIs[1]=indSIs[j]; aIs[1]=indAIs[j];
#if 0
    double reward=_m_p_rModel->
        Get(IndexTools::IndividualToJointIndices(sIs,_m_nrTwoAgentStates),
            IndexTools::IndividualToJointIndices(aIs,_m_nrTwoAgentActions));
#endif

    double reward=_m_p_rModel->Get(sIs,aIs);

#if 0
    cout << reward << "indSIs " << SoftPrintVector(indSIs) 
         <<  SoftPrintVector(sIs) << " indAIs " 
         << SoftPrintVector(indAIs)
         << IndexTools::IndividualToJointIndices(sIs,_m_nrTwoAgentStates)
         <<  SoftPrintVector(aIs) 
         << IndexTools::IndividualToJointIndices(aIs,_m_nrTwoAgentActions)
         << " i " << i << " j " << j << endl; 
#endif
    return(reward);
}

void TOICompactRewardDecPOMDPDiscrete::
SetIndividualRewardModel(RewardModel* rewardModel,
                         Index agentID)
{
    if(_m_p_rModels.size()<=agentID)
        _m_p_rModels.resize(agentID+1);

    _m_p_rModels[agentID]=rewardModel;
}

double TOICompactRewardDecPOMDPDiscrete::
GetIndividualReward(Index indSI, Index indAI, Index agentID) const
{
    double reward=_m_p_rModels[agentID]->Get(indSI,indAI);
#if DEBUG_TOICompactRewardDecPOMDPDiscrete
    cout << "GetIndividualReward[" << agentID << "](" << indSI << "," << indAI
         << ") = " << reward << endl;
#endif
    return(reward);
}

string TOICompactRewardDecPOMDPDiscrete::SoftPrint() const
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
        throw E("TOICompactRewardDecPOMDPDiscrete components (reward model) not initialized");

    return(ss.str());
}
