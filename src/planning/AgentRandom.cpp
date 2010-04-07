/**\file AgentRandom.cpp
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
 * $Id: AgentRandom.cpp 2979 2008-11-03 20:00:13Z faolieho $
 */

#include "AgentRandom.h"
#include <float.h>
#include "PlanningUnitDecPOMDPDiscrete.h"

using namespace std;

#define DEBUG_AgentRandom 0

AgentRandom::AgentRandom(const PlanningUnitDecPOMDPDiscrete &pu, Index id) :
    AgentDecPOMDPDiscrete(pu,id)
{
}

AgentRandom::AgentRandom(const AgentRandom& a) :
    AgentDecPOMDPDiscrete(a)
{
}

//Destructor
AgentRandom::~AgentRandom()
{
}

Index AgentRandom::Act()
{
    vector<size_t> nrAis=GetPU()->GetNrActions();
    Index aI=static_cast<Index>(nrAis[GetIndex()]*
                                  (rand() / (RAND_MAX + 1.0)));
    return(aI);
}

void AgentRandom::ResetEpisode()
{
}