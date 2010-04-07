/**\file AgentPOMDP.cpp
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
 * $Id: AgentPOMDP.cpp 3199 2009-04-06 14:43:39Z mtjspaan $
 */

#include "AgentPOMDP.h"
#include <float.h>
#include "PlanningUnitDecPOMDPDiscrete.h"
#include "JointBeliefInterface.h"

using namespace std;

#define DEBUG_AgentPOMDP 0

AgentPOMDP::AgentPOMDP(const PlanningUnitDecPOMDPDiscrete &pu, Index id,
                       QAV<PerseusPOMDPPlanner> *QPOMDP) :
    AgentSharedObservations(pu,id),
    _m_QPOMDP(QPOMDP),
    _m_t(0)
{
    _m_jb=GetPU()->GetNewJointBeliefInterface();
}

AgentPOMDP::AgentPOMDP(const AgentPOMDP& a) :
    AgentSharedObservations(a),
    _m_QPOMDP(a._m_QPOMDP),
    _m_t(a._m_t),
    _m_prevJaI(a._m_prevJaI)
{
    _m_jb=GetPU()->GetNewJointBeliefInterface();
    *_m_jb=*a._m_jb;
}

//Destructor
AgentPOMDP::~AgentPOMDP()
{
    delete _m_jb;
}

Index AgentPOMDP::Act(Index joI)
{
    if(_m_t>0)
        _m_jb->Update(*GetPU()->GetReferred(),_m_prevJaI,joI);

    Index jaInew=INT_MAX;
    double q,v=-DBL_MAX;
    for(size_t a=0;a!=GetPU()->GetNrJointActions();++a)
    {
        q=_m_QPOMDP->GetQ(*_m_jb,a);
        if(q>v)
        {
            v=q;
            jaInew=a;
        }
    }

#if DEBUG_AgentPOMDP
    cout << GetIndex() << ": ";
    _m_jb.Print();
    cout << " v " << v << endl;
#endif

    vector<Index> aIs=GetPU()->JointToIndividualActionIndices(jaInew);
    
    _m_prevJaI=jaInew;
    _m_t++;

    return(aIs[GetIndex()]);
}

void AgentPOMDP::ResetEpisode()
{
    _m_t=0;
    *_m_jb=*GetPU()->GetNewJointBeliefFromISD(); // isa JointBeliefInterface*
    _m_prevJaI=INT_MAX;
}
