/**\file TOIDecMDPDiscrete.cpp
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
 * $Id: TOIDecMDPDiscrete.cpp 2962 2008-11-02 15:04:43Z mtjspaan $
 */

#include "TOIDecMDPDiscrete.h"

using namespace std;

//Default constructor
TOIDecMDPDiscrete::TOIDecMDPDiscrete(
    string name, string descr, string pf) :
    TOIDecPOMDPDiscrete(name, descr, pf)
{
    _m_initialized = false;
}

//Destructor
TOIDecMDPDiscrete::~TOIDecMDPDiscrete()
{
}

bool TOIDecMDPDiscrete::SetInitialized(bool b)
{
    if( TOIDecPOMDPDiscrete::SetInitialized(true) )
    {
        if( b == true )
        {
            //\todo TODO: check that the Dec-MDP is indeed locally observable
        }
        _m_initialized = b;
        return(true);
    }
    else
        return(false);
}
    
void TOIDecMDPDiscrete::CreateStateObservations()
{
    for(Index agI=0; agI < GetNrAgents(); agI++)
    {
        size_t nrStatesAgent = GetNrStates(agI);
        size_t nrActionsAgent = GetNrActions(agI);
        SetNrObservations(agI, nrStatesAgent);
        MultiAgentDecisionProcessDiscrete* ind_madp = GetIndividualMADPD(agI);
        ind_madp->CreateNewObservationModel();

        for(Index sI=0; sI < nrStatesAgent; sI++)
            for(Index aI=0; aI < nrActionsAgent; aI++)
                ind_madp->SetObservationProbability(aI, sI, sI, 1.0);
    }
}
