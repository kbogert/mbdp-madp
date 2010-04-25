/**\file AgentBG.cpp
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
 * $Id: AgentBG.cpp 3199 2009-04-06 14:43:39Z mtjspaan $
 */

#include "AgentBG.h"
#include <float.h>
#include "PlanningUnitDecPOMDPDiscrete.h"
#include "PerseusBGPlanner.h"
#include "BayesianGameIdenticalPayoff.h"
#include "JointPolicyPureVector.h"
#include "QFunctionJAOHInterface.h"

using namespace std;

#define DEBUG_AgentBG 0

AgentBG::AgentBG(const PlanningUnitDecPOMDPDiscrete &pu, Index id,
                 QAV<PerseusBGPlanner> *QBG) :
    AgentDelayedSharedObservations(pu,id),
    _m_QBG(QBG),
    _m_t(0)
{
    _m_bgip=new BayesianGameIdenticalPayoff(pu.GetNrAgents(),
                                            pu.GetReferred()->GetNrActions(), 
                                            pu.GetReferred()->
                                            GetNrObservations());
    _m_jpol=new JointPolicyPureVector(*_m_bgip);
#if DEBUG_AgentBG
    cout << GetIndex() << " " <<_m_jpol->SoftPrint() << endl;
#endif
}

AgentBG::AgentBG(const AgentBG& a) :
    AgentDelayedSharedObservations(a),
    _m_QBG(a._m_QBG), // share the QBG, just copy the pointer
    _m_t(a._m_t),
    _m_prevJB(a._m_prevJB),
    _m_oIs(a._m_oIs),
    _m_prevJoIs(a._m_prevJoIs),
    _m_prevJaIs(a._m_prevJaIs),
    _m_aIs(a._m_aIs),
    _m_jaIfirst(a._m_jaIfirst)
{
    _m_bgip=new BayesianGameIdenticalPayoff(*a._m_bgip);
    _m_jpol=new JointPolicyPureVector(*a._m_jpol);
}

//Destructor
AgentBG::~AgentBG()
{
    delete _m_bgip;
    delete _m_jpol;
}

Index AgentBG::Act(Index oI, Index prevJoI)
{
    int betaMaxI=INT_MAX;
    Index aI=INT_MAX;

    _m_oIs.push_back(oI);
    _m_prevJoIs.push_back(prevJoI);

#if DEBUG_AgentBG
//     cout << " oIs "; PrintVectorCout(_m_oIs);
//     cout << " prevJoIs "; PrintVectorCout(_m_prevJoIs);
#endif

    switch(_m_t)
    {
    case 0: // we know joint belief at t=0, namely the ISD, so we can
            // use the POMDP action
    {
        JointBeliefInterface* jbi = GetPU()->GetNewJointBeliefFromISD();
        Index ja=GetMaximizingActionIndex(*jbi);
        delete jbi;
        vector<Index> aIs=GetPU()->JointToIndividualActionIndices(ja);
        aI=aIs[GetIndex()];
        _m_jaIfirst=ja;
#if DEBUG_AgentBG
        cout << GetIndex() << ": ja " << ja << " aI " << aI << endl;
#endif
        break;
    }
    case 1: // at t=1, the previous joint belief is the ISD, but now
            // we use the BG policy
    {
        JointBeliefInterface* jbi = GetPU()->GetNewJointBeliefFromISD();
        betaMaxI=GetMaximizingBGIndex(*jbi);
        delete jbi;

        _m_jpol->SetIndex(betaMaxI);
        aI=_m_jpol->GetActionIndex(GetIndex(),oI);
        break;
    }
    case 2: // now we start updating the previous joint beliefs, using
            // the joint action we took at t=0
    {
        _m_prevJB.Update(*GetPU()->GetReferred(),_m_jaIfirst,prevJoI);

        betaMaxI=GetMaximizingBGIndex(_m_prevJB);

        _m_jpol->SetIndex(betaMaxI);
        aI=_m_jpol->GetActionIndex(GetIndex(),oI);
        break;
    }
    default: // the rest of the time we use the previous BG jpol to
             // get the joint action to update the joint belief
    {
        _m_prevJB.Update(*GetPU()->GetReferred(),_m_jpol->GetJointActionIndex(prevJoI),
                         prevJoI);

        betaMaxI=GetMaximizingBGIndex(_m_prevJB);

        _m_jpol->SetIndex(betaMaxI);
        aI=_m_jpol->GetActionIndex(GetIndex(),oI);
        break;
    }
    }

    _m_t++;

    _m_aIs.push_back(aI);

#if DEBUG_AgentBG
//     cout << GetIndex() << ": t " << _m_t << " oI " << oI
//          << " prevJoI " << prevJoI << endl;

//     cout << GetIndex() << ":";
//     cout << " prevJaIs "; PrintVectorCout(_m_prevJaIs);
//     cout << " aIs "; PrintVectorCout(_m_aIs);
//     cout << endl;

#endif

    return(aI);
}

void AgentBG::ResetEpisode()
{
    _m_t=0;

    JointBeliefInterface* jbi = GetPU()->GetNewJointBeliefFromISD();
    _m_prevJB.Set(jbi->Get());
    delete jbi;
    _m_oIs.clear();
    _m_prevJoIs.clear();
    _m_prevJaIs.clear();
    _m_aIs.clear();
}

int AgentBG::GetMaximizingBGIndex(const JointBeliefInterface &jb) const
{
    double v=-DBL_MAX,q;
    int bI,betaMaxI=INT_MAX;

    for(Index a=0;a!=GetPU()->GetNrJointActions();++a)
    {
        q=_m_QBG->GetQ(jb,a,bI);
        if(q>v)
        {
            v=q;
            betaMaxI=bI;
        }
    }

#if DEBUG_AgentBG
    cout << "GetMaximizingBGIndex " << GetIndex() << ": betaMaxI " << betaMaxI 
         << " " << jb.SoftPrint() << endl;
#endif
    return(betaMaxI);
}

Index AgentBG::GetMaximizingActionIndex(const JointBeliefInterface &jb) const
{
    double v=-DBL_MAX,q;
    Index ja=INT_MAX;
    int bI;

    for(Index a=0;a!=GetPU()->GetNrJointActions();++a)
    {
        q=_m_QBG->GetQ(jb,a,bI);
        
        if(q>v)
        {
            v=q;
            ja=a;
        }
    }

    return(ja);
}
