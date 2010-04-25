/**\file PerseusQFunctionPlanner.cpp
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
 * $Id: PerseusQFunctionPlanner.cpp 2293 2008-02-19 18:07:32Z mtjspaan $
 */

#include "PerseusQFunctionPlanner.h"
#include "PlanningUnitDecPOMDPDiscrete.h"

using namespace std;

PerseusQFunctionPlanner::
PerseusQFunctionPlanner(const PlanningUnitDecPOMDPDiscrete& pu) :
    AlphaVectorPlanning(pu),
    PerseusStationary(pu)
{
}

//Destructor
PerseusQFunctionPlanner::~PerseusQFunctionPlanner()
{
}

void PerseusQFunctionPlanner::Plan()
{
    PlanLeadIn();

    QFunctionsDiscrete Q0,Q1;
    // records the value of each belief in the belief set
    vector<double> VB,VBnew;
    
    // get initial value function
    Q1=GetInitialQFunctions();
    VB=BeliefValue::GetValues(*_m_beliefs,Q1);

    int iter=0;                      
    bool done=false;
    while(!done)
    {
        // print out some info
        PlanStartOfIteration(iter,VB,Q1);

        // the real thing: compute the next stage value function
        Q0=Q1;
        Q1=BackupStage(*_m_beliefs,Q0);

        // compute the maximum difference in the values for all
        // beliefs: for the convergence test
        VBnew=BeliefValue::GetValues(*_m_beliefs,Q1);
       
        // test for convergence
        if(CheckConvergence(VB,VBnew,iter))
            done=true;

        VB=VBnew;
        iter++;

        PlanEndOfIteration(Q1);
    }

    PlanLeadOut();
}
