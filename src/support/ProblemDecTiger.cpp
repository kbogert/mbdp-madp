/**\file ProblemDecTiger.cpp
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
 * $Id: ProblemDecTiger.cpp 3598 2009-08-20 12:29:54Z mtjspaan $
 */

#include "ProblemDecTiger.h"

using namespace std;

#define DEBUG_PDT 0
#define DEBUG_TM 0
#define DEBUG_CJA 0
#define DEBUG_CJO 0
#define DEBUG_CA 0
#define DEBUG_CO 0
#define DEBUG_GETJA 0

ProblemDecTiger::ProblemDecTiger() :
    DecPOMDPDiscrete(
        "The Dec-Tiger Problem",
        "A toy problem, 2-agent Dec-POMDP. 2 agents have to select 1 out of 2 doors, behind one is a tiger, behind the other treasure.",
        "DecTiger"),
    NUMBER_OF_STATES(2),
    NUMBER_OF_AGENTS(2),
    NUMBER_OF_OBSERVATIONS(2),
    NUMBER_OF_ACTIONS(3)
{
    SetNrAgents(NUMBER_OF_AGENTS);
    SetNrStates(NUMBER_OF_STATES);

    SetUniformISD();
    SetDiscount(1);
    
    // add actions:
    ConstructActions();
    if(DEBUG_CJA) cout << "\n>>>Creating joint actions and set...\n"<<endl;
    // add joint actions
    size_t testNRJA = MADPComponentDiscreteActions::ConstructJointActions();
    if(DEBUG_CA) cout << "testNRJA="<<testNRJA<<endl;    

    MADPComponentDiscreteActions::SetInitialized(true);

    // add observations:
    ConstructObservations();
    size_t testNRJO = ConstructJointObservations();
    if(DEBUG_CO) cout << "testNRJO="<<testNRJO<<endl;

    MADPComponentDiscreteObservations::SetInitialized(true);

    // add the transition model
    if(DEBUG_PDT) cout << "\n>>>Adding Transition model...\n"<<endl;
    CreateNewTransitionModel();
    FillTransitionModel();    

    // add observation model
    if(DEBUG_PDT) cout << "\n>>>Adding Observation model...\n"<<endl;
    CreateNewObservationModel();
    FillObservationModel();
    MultiAgentDecisionProcessDiscrete::SetInitialized(true);

    // add rewards
    CreateNewRewardModel();
    FillRewardModel();
    if(DEBUG_PDT)     cout << "Model created..."<<endl; 
    DecPOMDPDiscrete::SetInitialized(true);
}

ProblemDecTiger::~ProblemDecTiger()
{
}

void ProblemDecTiger::ConstructActions()
{
    if(DEBUG_CA)        cout << "Creating actions and action sets..."<<endl;
    size_t nrJointActions = 1;
    for(Index agentIndex=0; agentIndex < _m_nrAgents; agentIndex++)
    {
        if(DEBUG_CA)    cout << "\nCreating agent "<<agentIndex<<"'s actions..."<<endl;
        size_t nrActionsThisAgent = NUMBER_OF_ACTIONS;
        nrJointActions *= nrActionsThisAgent;
        if(DEBUG_CA)        cout << "inserting this agent's nrActions...("<<nrActionsThisAgent<<")"<<endl;
        _m_nrActions.push_back(nrActionsThisAgent);
        if(DEBUG_CA)        cout << "inserting this new(=empty) actionSet..."<<endl;
        vector<ActionDiscrete> av_temp;
        //is copied into back of _m_actionVecs, so no need for new...
        _m_actionVecs.push_back( av_temp );
        if(DEBUG_CA)        cout << "inserted the new(=empty) actionSet"<<endl;
        for(Index actionI=0; actionI < nrActionsThisAgent; actionI++)
        {
            if(DEBUG_CA)            cout << "\nCreating action"<<actionI<<":";

            string name("a");
            stringstream ss;
            string strActionI, strAgentI;
            ss << agentIndex;
            ss >> strAgentI;
            name += strAgentI;
            ss.clear();
            ss << actionI;
            ss >> strActionI;
            name += strActionI;
            string whatAction;
            switch(actionI){
            case(LISTEN):    whatAction = "Listen";
                break;
            case(OPENLEFT):    whatAction = "OpenLeft";
                break;
            case(OPENRIGHT):whatAction = "OpenRight";
                break;
            }
            name += ":" + whatAction;

            string descr("Action ");
            descr += whatAction+" - #";
            descr += strActionI + " of agent " + strAgentI;  
            ActionDiscrete ad_temp =   ActionDiscrete(actionI,name,descr);
            _m_actionVecs[agentIndex].push_back( ad_temp );
            name.clear();
            strActionI.clear();
            strAgentI.clear();
            whatAction.clear();    
            descr.clear();
        }
    }
}

void ProblemDecTiger::ConstructObservations()
{
    /// add observations:
    size_t nrJointObservations = 1;
    for(Index agentIndex=0; agentIndex < _m_nrAgents; agentIndex++)
    {
        size_t nrObservationsThisAgent = NUMBER_OF_OBSERVATIONS;
        nrJointObservations *= nrObservationsThisAgent;
    
        _m_nrObservations.push_back(nrObservationsThisAgent);
        vector<ObservationDiscrete> ov_temp;
        //Again, this is copied into _m_observationVecs, so no 'new' needed
        _m_observationVecs.push_back( ov_temp );
        for(Index obsI=0; obsI < nrObservationsThisAgent; obsI++)
        {
            string name("o");
            stringstream ss;
            string strObsI, strAgentI;        
            ss << agentIndex;
            ss >> strAgentI;
            name += strAgentI;
            ss.clear();
            ss << obsI;
            ss >> strObsI;
            name += strObsI; 
            string whatObs;
            switch(obsI){
            case(HEARLEFT):    whatObs = "HearLeft";
                break;
            case(HEARRIGHT):whatObs = "HearRight";
                break;
            }
            name += ":" + whatObs;
            
            string descr("Observation ");
            descr += whatObs + " - #";
            descr += strObsI + " of agent " + strAgentI;
            ObservationDiscrete od_temp = ObservationDiscrete(obsI,name,descr);
            _m_observationVecs[agentIndex].push_back( od_temp );
            name.clear(); 
            strObsI.clear(); 
            strAgentI.clear(); 
            whatObs.clear();
            descr.clear();
        }
    }
}

void ProblemDecTiger::FillTransitionModel()
{
    // add transitions:
    for(Index s1=0; s1<NUMBER_OF_STATES;s1++) 
        for(Index s2=0; s2<NUMBER_OF_STATES;s2++) 
            for(Index ja=0; ja<GetNrJointActions(); ja++)
            {
                if(DEBUG_TM)    cout << "ProblemDecTiger::FillTransitionModel() - calling SetTransitionProbability("<<s1<<", "<<ja<<", "<<s2<<", 0.5)"<<endl;
                SetTransitionProbability(s1, ja, s2, 0.5);
        
                if(DEBUG_TM)    cout << " - GetTransitionProb gives " << GetTransitionProbability(s1, ja, s2) << endl;
            }
    SetTransitionProbability(SLEFT, LISTEN_LISTEN, SLEFT, 1.0);
    SetTransitionProbability(SLEFT, LISTEN_LISTEN, SRIGHT, 0.0);
    SetTransitionProbability(SRIGHT, LISTEN_LISTEN, SRIGHT, 1.0);
    SetTransitionProbability(SRIGHT, LISTEN_LISTEN, SLEFT, 0.0);
}

void ProblemDecTiger::FillObservationModel()
{
    for(Index  ja=0; ja< GetNrJointActions(); ja++)
        for(Index s1=0; s1<NUMBER_OF_STATES;s1++) 
            for(Index jo=0; jo<GetNrJointObservations();jo++) 
            {
                double prob = 0;
                if(ja != LISTEN_LISTEN)
                {
                    prob = 0.25;   
                }
                else if(jo == HEARLEFT_HEARLEFT)
                {
                    if        (s1 == SLEFT)   prob = 0.85*0.85;
                    else if (s1 == SRIGHT)  prob = 0.15*0.15;
                }
                else if(jo == HEARLEFT_HEARRIGHT)
                {
                    if        (s1 == SLEFT)   prob = 0.85*0.15;
                    else if (s1 == SRIGHT)  prob = 0.15*0.85;
                }    
                else if(jo == HEARRIGHT_HEARLEFT)
                {
                    if        (s1 == SLEFT)   prob = 0.85*0.15;
                    else if (s1 == SRIGHT)  prob = 0.15*0.85;
                }    
                else if(jo == HEARRIGHT_HEARRIGHT)
                {
                    if        (s1 == SLEFT)   prob = 0.15*0.15;
                    else if (s1 == SRIGHT)  prob = 0.85*0.85;
                }    
                SetObservationProbability(ja, s1, jo, prob);
            }
}

void ProblemDecTiger::FillRewardModel()
{
    SetReward(SLEFT, LISTEN_LISTEN, -2);
    SetReward(SRIGHT, LISTEN_LISTEN, -2);
    SetReward(SLEFT, LISTEN_OPENLEFT, -101);
    SetReward(SLEFT, LISTEN_OPENRIGHT, +9);
    SetReward(SLEFT, OPENLEFT_LISTEN, -101);
    SetReward(SLEFT, OPENLEFT_OPENLEFT, -50);
    SetReward(SLEFT, OPENLEFT_OPENRIGHT, -100);
    SetReward(SLEFT, OPENRIGHT_LISTEN, +9);
    SetReward(SLEFT, OPENRIGHT_OPENLEFT, -100);
    SetReward(SLEFT, OPENRIGHT_OPENRIGHT, +20);
    SetReward(SRIGHT, LISTEN_OPENLEFT, +9);
    SetReward(SRIGHT, LISTEN_OPENRIGHT, -101);
    SetReward(SRIGHT, OPENLEFT_LISTEN, +9);
    SetReward(SRIGHT, OPENLEFT_OPENLEFT, +20);
    SetReward(SRIGHT, OPENLEFT_OPENRIGHT, -100);
    SetReward(SRIGHT, OPENRIGHT_LISTEN, -101);
    SetReward(SRIGHT, OPENRIGHT_OPENLEFT, -100);
    SetReward(SRIGHT, OPENRIGHT_OPENRIGHT, -50);
}

