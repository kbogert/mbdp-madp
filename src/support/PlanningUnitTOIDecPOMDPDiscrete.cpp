/**\file PlanningUnitTOIDecPOMDPDiscrete.cpp
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
 * $Id: PlanningUnitTOIDecPOMDPDiscrete.cpp 3604 2009-08-25 10:52:24Z mtjspaan $
 */

#include "PlanningUnitTOIDecPOMDPDiscrete.h"

using namespace std;

//Default constructor
PlanningUnitTOIDecPOMDPDiscrete::PlanningUnitTOIDecPOMDPDiscrete(
    const PlanningUnitMADPDiscreteParameters &params,
    size_t horizon,
    TOIDecPOMDPDiscrete* p
    ) :
    Referrer<TOIDecPOMDPDiscrete>(p),
    PlanningUnitDecPOMDPDiscrete(params,horizon,p) 
{
    if(DEBUG_PU_CONSTRUCTORS) cout << "PlanningUnitTOIDecPOMDPDiscrete(PlanningUnitMADPDiscreteParameters params, size_t horizon, DecPOMDPDiscreteInterface* p)  called" << endl;
    if(p!=0)
        SanityCheck();
}

PlanningUnitTOIDecPOMDPDiscrete::PlanningUnitTOIDecPOMDPDiscrete(
    size_t horizon,
    TOIDecPOMDPDiscrete* p
    ) :
    Referrer<TOIDecPOMDPDiscrete>(p),
    PlanningUnitDecPOMDPDiscrete(horizon,p)
{
    if(DEBUG_PU_CONSTRUCTORS) cout << "PlanningUnitTOIDecPOMDPDiscrete(size_t horizon, DecPOMDPDiscreteInterface* p)  called" << endl;
    if(p!=0)
        SanityCheck();
}

void PlanningUnitTOIDecPOMDPDiscrete::SetProblem(TOIDecPOMDPDiscrete* p)
{
    if(p == GetReferred())
        return;
    SetReferred(p);
#if 0
    //set (and initialize) the problem at PlanningUnitDecPOMDPDiscrete level:
    DecPOMDPDiscreteInterface* p2 = 
        static_cast<DecPOMDPDiscreteInterface*>(p);
#endif
    PlanningUnitDecPOMDPDiscrete::SetProblem(p);

    SanityCheck();
}

bool PlanningUnitTOIDecPOMDPDiscrete::SanityCheck() const
{
    bool sane=PlanningUnitDecPOMDPDiscrete::SanityCheck();

    return(sane);
}

