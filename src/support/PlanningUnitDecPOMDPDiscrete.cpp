/**\file PlanningUnitDecPOMDPDiscrete.cpp
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
 * $Id: PlanningUnitDecPOMDPDiscrete.cpp 3604 2009-08-25 10:52:24Z mtjspaan $
 */

#include "PlanningUnitDecPOMDPDiscrete.h"

using namespace std;

//Default constructor
PlanningUnitDecPOMDPDiscrete::PlanningUnitDecPOMDPDiscrete(
    const PlanningUnitMADPDiscreteParameters &params,
    size_t horizon,
    DecPOMDPDiscreteInterface* p
    ) :
    Referrer<DecPOMDPDiscreteInterface>(p),
    PlanningUnitMADPDiscrete(params,horizon,p) 
{
    if(DEBUG_PU_CONSTRUCTORS) cout << "PlanningUnitDecPOMDPDiscrete(PlanningUnitMADPDiscreteParameters params, size_t horizon, DecPOMDPDiscreteInterface* p)  called" << endl;
    if(p!=0)
        SanityCheck();
}

PlanningUnitDecPOMDPDiscrete::PlanningUnitDecPOMDPDiscrete(
    size_t horizon,
    DecPOMDPDiscreteInterface* p
    ) :
    Referrer<DecPOMDPDiscreteInterface>(p),
    PlanningUnitMADPDiscrete(horizon,p)
{
    if(DEBUG_PU_CONSTRUCTORS) cout << "PlanningUnitDecPOMDPDiscrete(size_t horizon, DecPOMDPDiscreteInterface* p)  called" << endl;
    if(p!=0)
        SanityCheck();
}

void PlanningUnitDecPOMDPDiscrete::SetProblem(DecPOMDPDiscreteInterface* p)
{
    if(p == GetReferred())
        return;
    SetReferred(p);

    //set (and initialize) the problem at PlanningUnitMADPDiscrete level:
    MultiAgentDecisionProcessDiscreteInterface* p2 = 
        static_cast<MultiAgentDecisionProcessDiscreteInterface*>(p);
    PlanningUnitMADPDiscrete::SetProblem(p2);

    SanityCheck();
}

bool PlanningUnitDecPOMDPDiscrete::SanityCheck() const
{
    bool sane=PlanningUnitMADPDiscrete::SanityCheck();

    // we cannot check anything check
    if(GetReferred()==0)
        return(sane);

    if(GetDiscount() < 0 || GetDiscount() > 1)
    {
        sane=false;
        throw(E("PlanningUnitDecPOMDPDiscrete::SanityCheck() failed, discount should be between 0 and 1"));
    }

    if(GetHorizon() == MAXHORIZON &&
       abs(GetDiscount()-1) < PROB_PRECISION)
    {
        sane=false;
        throw(E("PlanningUnitDecPOMDPDiscrete::SanityCheck() failed, in the infinite-horizon case the discount should be less than one"));
    }

    return(sane);
}

