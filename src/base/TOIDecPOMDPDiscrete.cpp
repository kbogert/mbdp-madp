/**\file TOIDecPOMDPDiscrete.cpp
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
 * $Id: TOIDecPOMDPDiscrete.cpp 2962 2008-11-02 15:04:43Z mtjspaan $
 */

#include "TOIDecPOMDPDiscrete.h"
#include "RewardModelMappingSparse.h"
#include "RewardModelMapping.h"

using namespace std;

TOIDecPOMDPDiscrete::
TOIDecPOMDPDiscrete(
    string name, string descr, string pf) :
    TransitionObservationIndependentMADPDiscrete(name, descr, pf)
{
    _m_initialized = false;
    _m_p_rModel = 0;
}

TOIDecPOMDPDiscrete::TOIDecPOMDPDiscrete(const TOIDecPOMDPDiscrete& o) 
{
    throw(E("TOIDecPOMDPDiscrete: copy ctor not yet implemented"));
}
//Destructor
TOIDecPOMDPDiscrete::~TOIDecPOMDPDiscrete()
{
    delete(_m_p_rModel);
}
//Copy assignment operator
TOIDecPOMDPDiscrete& TOIDecPOMDPDiscrete::operator= (const TOIDecPOMDPDiscrete& o)
{
    if (this == &o) return *this;   // Gracefully handle self assignment
    // Put the normal assignment duties here...

    throw(E("TOIDecPOMDPDiscrete: assignment not yet implemented"));

    return *this;
}

void TOIDecPOMDPDiscrete::SetIndividualDecPOMDPD(DecPOMDPDiscrete *model,
                                                 Index agentI)
{
    if(_m_individualDecPOMDPDs.size()<=agentI)
        _m_individualDecPOMDPDs.resize(agentI+1);

    _m_individualDecPOMDPDs[agentI]=model;
}

bool TOIDecPOMDPDiscrete::SetInitialized(bool b)
{
    if(b == false)
    {
        _m_initialized = false;
        return(true);
    }

    if( TransitionObservationIndependentMADPDiscrete::SetInitialized(true) 
        )
    {
        if( b == true )
        {
            if (_m_p_rModel == 0)
                throw E("TOIDecPOMDPDiscrete::SetInitialized(true) : no reward model specified yet! ( _m_p_rModel == 0 )");

        }
        _m_initialized = b;
        return(true);
    }
    else
        return(false);
}

void TOIDecPOMDPDiscrete::CreateNewRewardModel()
{
    if(_m_initialized)
    delete(_m_p_rModel);
#if 0
    // cannot call GetNrJointStates() and GetNrJointActions() because
    // we're not initialized yet
    size_t nrJS=1, nrJA=1;
    for(Index i=0;i!=GetNrAgents();++i)
    {
        nrJS*=GetIndividualMADPD(i)->GetNrStates();
        nrJA*=GetIndividualMADPD(i)->GetNrJointActions();
    }

    if(GetSparse())
        _m_p_rModel = new RewardModelMappingSparse(nrJS, 
                                                   nrJA);
    else
        _m_p_rModel = new RewardModelMapping(nrJS, 
                                             nrJA);
#else
    _m_p_rModel = new RewardModelTOISparse();
#endif
}

string TOIDecPOMDPDiscrete::SoftPrint() const
{
    stringstream ss;
    ss << TransitionObservationIndependentMADPDiscrete::SoftPrint();
    ss << DecPOMDP::SoftPrint();

    if(_m_initialized)
    {
        ss << "Reward model: " << endl;
        ss << _m_p_rModel->SoftPrint();
    }
    else
        throw E("TOIDecPOMDPDiscrete components (reward model) not initialized");

    return(ss.str());
}
