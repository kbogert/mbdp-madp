/**\file AgentQMDP.cpp
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
 * $Id: AgentQMDP.cpp 3199 2009-04-06 14:43:39Z mtjspaan $
 */

#include "AgentQMDP.h"
#include <float.h>
#include <limits.h>
#include "PlanningUnitDecPOMDPDiscrete.h"

using namespace std;

#define DEBUG_AgentQMDP 0

AgentQMDP::AgentQMDP(const PlanningUnitDecPOMDPDiscrete &pu, Index id,
                     const QTable &Q) :
    AgentSharedObservations(pu,id),
    _m_Q(Q),
    _m_t(0)
{
}

AgentQMDP::AgentQMDP(const AgentQMDP& a) :
    AgentSharedObservations(a),
    _m_Q(a._m_Q),
    _m_t(a._m_t),
    _m_jb(a._m_jb),
    _m_prevJaI(a._m_prevJaI)
{
}

//Destructor
AgentQMDP::~AgentQMDP()
{
}

Index AgentQMDP::Act(Index joI)
{
    if(_m_t>0)
        _m_jb.Update(*GetPU()->GetReferred(),_m_prevJaI,joI);

    Index jaInew=INT_MAX,aI;
    double q,v=-DBL_MAX;
    for(size_t a=0;a!=GetPU()->GetNrJointActions();++a)
    {
        q=0;
        for(unsigned s=0;s!=GetPU()->GetNrStates();++s)
            q+=_m_jb.Get(s)*_m_Q(s,a);

//        if(q>(v+PROB_PRECISION))
        if(q>v)
        {
            v=q;
            jaInew=a;
        }
    }

    vector<Index> aIs=GetPU()->JointToIndividualActionIndices(jaInew);
    aI=aIs[GetIndex()];

    _m_prevJaI=jaInew;
    _m_t++;

#if DEBUG_AgentQMDP
    cout << GetIndex() << ": ";
    _m_jb.Print();
    cout << " v " << v << " ja " << jaInew << " aI " << aI << endl;
#endif

    return(aI);
}

void AgentQMDP::ResetEpisode()
{
    _m_t=0;
    JointBeliefInterface* jbi = GetPU()->GetNewJointBeliefFromISD();
    _m_jb.Set(jbi->Get());
    delete jbi;
    _m_prevJaI=INT_MAX;
}
