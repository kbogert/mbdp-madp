/**\file BruteForceSearchPlanner.cpp
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
 * $Id: BruteForceSearchPlanner.cpp 3639 2009-08-31 12:49:42Z mtjspaan $
 */

#include "BruteForceSearchPlanner.h"
#include <float.h>

using namespace std;

#define DEBUG_BFS 0

//Default constructor
BruteForceSearchPlanner::BruteForceSearchPlanner(size_t horizon, 
        DecPOMDPDiscreteInterface* p) :
    PlanningUnitDecPOMDPDiscrete(horizon, p),
    _m_foundPolicy(*this)
{
    SetReferred(p);
}

BruteForceSearchPlanner::BruteForceSearchPlanner(
    const PlanningUnitMADPDiscreteParameters &params,
    size_t horizon, DecPOMDPDiscreteInterface* p) :
    PlanningUnitDecPOMDPDiscrete(params, horizon, p),
    _m_foundPolicy(*this)
{
    SetReferred(p);
}

void BruteForceSearchPlanner::Plan()
{    
    bool round = false;
    JointPolicyPureVector* jpol = new JointPolicyPureVector(*this);
    JointPolicyPureVector best(*this);
    double v_best = -DBL_MAX;
    double v = 0.0;
    
    int i = 0;
    if(DEBUG_BFS)
        cout << "Starting Bruteforce search - v_best is init to "
             << v_best << endl;
    LIndex nrJPols = GetNrJointPolicies();
    
    while(!round)
    {
        if(DEBUG_BFS){    cout << "Jpol#"<< i << " - ";}
        PrintProgress("Jpol #",i,nrJPols,1000);
        i++;

        ValueFunctionDecPOMDPDiscrete vf(this, jpol);
        v = vf.CalculateV(true);//set caching to true!
        if(DEBUG_BFS)    cout << "Expected value = "<< v;
        if(v > v_best)
        {
            if(DEBUG_BFS) cout << " -> new best policy!!!";
            v_best = v;
            best = *jpol;
        }
        if(DEBUG_BFS) cout << endl << "Incrementing joint policy..." <<endl; 
        round = ++(*jpol);
    }

    _m_foundPolicy=best;
    _m_expectedRewardFoundPolicy=v_best;
}
