/**\file DecPOMDPDiscrete.cpp
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
 * $Id: DecPOMDPDiscrete.cpp 4016 2010-03-11 16:56:02Z mtjspaan $
 */

#include "DecPOMDPDiscrete.h"    
#include "RGet.h"
#include "RewardModelMapping.h"
#include "RewardModelMappingSparse.h"

using namespace std;

#define DEBUG_DPOMDPD 0
//Debug Fill DecPOMDP Discrete - functions to initialize the DecPOMDPDiscrete
//(typically from a file)
#define DEBUG_FILLDPD 0

DecPOMDPDiscrete::DecPOMDPDiscrete(string name, string descr, string pf) :
    MultiAgentDecisionProcessDiscrete(name, descr, pf)
{
    _m_initialized = false;
    _m_p_rModel = 0;
}

DecPOMDPDiscrete::~DecPOMDPDiscrete()
{
    if(DEBUG_DPOMDPD)
        cout << "deleting DecPOMDPDiscrete (deleting rewards)"<<endl;
    delete(_m_p_rModel);
}

bool DecPOMDPDiscrete::SetInitialized(bool b)
{
    if( MultiAgentDecisionProcessDiscrete::SetInitialized(true) )
    {
        _m_initialized = b;
        return(true);
    }
    else
        return(false);
}

void DecPOMDPDiscrete::CreateNewRewardModel()
{
    if(_m_initialized)
    delete(_m_p_rModel);

    if(GetSparse())
        _m_p_rModel = new RewardModelMappingSparse( GetNrStates(), GetNrJointActions());
    else
        _m_p_rModel = new RewardModelMapping( GetNrStates(), GetNrJointActions());
}

RGet* DecPOMDPDiscrete::GetRGet() const
{ 
    return new RGet_RewardModelMapping(
        ((RewardModelMapping*)_m_p_rModel)  );
}

string DecPOMDPDiscrete::SoftPrint() const
{
    stringstream ss;
    ss << MultiAgentDecisionProcessDiscrete::SoftPrint();
    ss << DecPOMDP::SoftPrint();

    if(_m_initialized)
    {
        ss << "Reward model: " << endl;
        ss << _m_p_rModel->SoftPrint();
    }
    else
        throw E("DecPOMDPDiscrete components (reward model) not initialized");

    return(ss.str());
}

void DecPOMDPDiscrete::SetReward(Index sI, Index jaI, Index sucSI, double r)
{
    double rOld=GetReward(sI,jaI),
        rExp=GetTransitionProbability(sI,jaI,sucSI)*r;
    SetReward(sI,jaI,rOld+rExp);
}

void DecPOMDPDiscrete::SetReward(Index sI, Index jaI, Index sucSI,
                                 Index joI, double r)
{
    throw(E("DecPOMDPDiscrete::SetReward(sI,jaI,sucSI,joI,r) not implemented"));
}

void
DecPOMDPDiscrete::ExtractMADPDiscrete(MultiAgentDecisionProcessDiscrete *madp)
{
    madp->SetNrAgents(GetNrAgents());
    madp->SetName(GetName());
    madp->SetDescription(GetDescription());

    // transition model
    madp->SetTransitionModelPtr(
        const_cast<TransitionModelDiscrete*>(GetTransitionModelDiscretePtr()));

    // observation model
    madp->SetObservationModelPtr(
        const_cast<ObservationModelDiscrete*>(GetObservationModelDiscretePtr()));

    // MADPComponentDiscreteStates
    for(Index s=0;s!=GetNrStates();++s)
        madp->AddState(GetState(s)->GetName());

    madp->SetISD(GetISD());

    // MADPComponentDiscreteObservations
    for(Index id=0;id!=GetNrAgents();++id)
        for(Index o=0;o!=GetNrObservations(id);++o)
            madp->AddObservation(id,GetObservation(id,o)->GetName());
    madp->ConstructJointObservations();

    // MADPComponentDiscreteActions
    for(Index id=0;id!=GetNrAgents();++id)
        for(Index o=0;o!=GetNrActions(id);++o)
            madp->AddAction(id,GetAction(id,o)->GetName());
    madp->ConstructJointActions();

    madp->Initialize();
}
