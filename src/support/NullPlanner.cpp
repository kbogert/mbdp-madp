/**\file NullPlanner.cpp
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
 * $Id: NullPlanner.cpp 3604 2009-08-25 10:52:24Z mtjspaan $
 */

#include "NullPlanner.h"

NullPlanner::NullPlanner(DecPOMDPDiscreteInterface* p)
{
    PlanningUnitMADPDiscreteParameters params;
    params.SetComputeAll(false);

    SetParams(params);
    SetProblem(p);

}
    
NullPlanner::NullPlanner(size_t horizon, DecPOMDPDiscreteInterface* p)
{
    PlanningUnitMADPDiscreteParameters params;
    params.SetComputeAll(false);

    SetParams(params);
    SetProblem(p);
    SetHorizon(horizon);
}

NullPlanner::NullPlanner(const PlanningUnitMADPDiscreteParameters &params,
                         size_t horizon, DecPOMDPDiscreteInterface* p) :
    PlanningUnitDecPOMDPDiscrete(params,horizon,p)
{
}

void NullPlanner::Plan()
{
    throw(E("NullPlanner::Plan() should not be called"));
}

double NullPlanner::GetExpectedReward() const
{
    throw(E("NullPlanner::GetExpectedReward() should not be called"));
    return(0);
}

JointPolicy* NullPlanner::GetJointPolicy()
{
    throw(E("NullPlanner::GetJointPolicy() should not be called"));
    return(0);
}
