/**\file JESPExhaustivePlanner.cpp
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
 * $Id: JESPExhaustivePlanner.cpp 3004 2008-11-09 18:40:15Z mtjspaan $
 */

#include "JESPExhaustivePlanner.h"
#include <float.h>

using namespace std;

#define DEBUG_EXHBR 0
#define DEBUG_EXJESP 0

JESPExhaustivePlanner::JESPExhaustivePlanner(
    const PlanningUnitMADPDiscreteParameters &params,
    size_t horizon,
    DecPOMDPDiscreteInterface* p
    ) :
    PlanningUnitDecPOMDPDiscrete(params, horizon, p),
    _m_foundPolicy(*this)
    //,_m_exhBRBestPol(*this)
{
}

JESPExhaustivePlanner::JESPExhaustivePlanner(
    int horizon,
    DecPOMDPDiscreteInterface* p
    ) :
    PlanningUnitDecPOMDPDiscrete(horizon, p),
    _m_foundPolicy(*this)
    //,_m_exhBRBestPol(*this)
{
}

void JESPExhaustivePlanner::Plan()
{
    if(DEBUG_EXJESP){ 
        cout << "\n---------------------------------"<<endl;
        cout << "Exhaustive JESP  - Plan() started"<<endl;
        cout << "---------------------------------"<<endl;
    }
    double v_best = -DBL_MAX;
    JointPolicyPureVector* jpol = new JointPolicyPureVector(*this);
    JointPolicyPureVector* best = new JointPolicyPureVector(*this);
    jpol->RandomInitialization();
    
    if(DEBUG_EXJESP) {cout << "joint policy randomly initialized to:";
        jpol->Print();}
    
    int stop = 0;
    size_t nr_non_improving_agents = 0;
    while(nr_non_improving_agents < GetReferred()->GetNrAgents()
            && stop++ < 1000) 
    {
        int agentI = GetNextAgentIndex();
        double v = ExhaustiveBestResponse(jpol, agentI);
        if(v > v_best + 1e-9)
        {  
            (*best) = (*jpol);
            if(DEBUG_EXHBR)
                {cout << "Plan: new best policy:"<<endl; best->Print();}
            v_best = v;
            nr_non_improving_agents = 0;
        }        
        else
            nr_non_improving_agents++;
    }
    _m_foundPolicy = *best;
    _m_expectedRewardFoundPolicy=v_best;
    

    if(DEBUG_EXJESP){ 
        cout << "Exhaustive JESP  - resulting policy:"<<endl;
        cout << "------------------------------------"<<endl;
        best->Print();
    }
}

double JESPExhaustivePlanner::ExhaustiveBestResponse(JointPolicyPureVector* 
    jpol, int agentI)
{
    if(DEBUG_EXHBR)
        cout << "JESPExhaustivePlanner::ExhaustiveBestResponse called "
             << "for agent " << agentI << endl;

    bool round = false;
    JointPolicyPureVector best(*this);
    double v_best = -DBL_MAX;
    double v = 0.0;
    jpol->ZeroInitialization(agentI);
    
    while(!round)
    {
        ValueFunctionDecPOMDPDiscrete vf(this, jpol);
        v = vf.CalculateV(true);
        if(v > v_best)
        {
            best = (*jpol);
            if(DEBUG_EXHBR)
                {cout << "ExhaustiveBestResponse: new best policy:"<<endl; 
                best.Print();}
            v_best = v;
        }
        round = jpol->Increment(agentI);
    }
    //_m_exhBRBestPol = best;
    *jpol = best;
    if(DEBUG_EXJESP){   cout << "Best response V="<<v_best<<endl;}
    if(DEBUG_EXHBR){ cout << "policy="; jpol->Print();}
    return(v_best);
}
