/**\file BGforStageCreation.cpp
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
 * $Id: BGforStageCreation.cpp 3604 2009-08-25 10:52:24Z mtjspaan $
 */

#include "BGforStageCreation.h"
#include "PlanningUnitMADPDiscrete.h"
#include "JointPolicyDiscretePure.h"

using namespace std;
/*
//Default constructor
BGforStageCreation::BGforStageCreation()
{
}
//Copy constructor.    
BGforStageCreation::BGforStageCreation(const BGforStageCreation& o) 
{
}
//Destructor
BGforStageCreation::~BGforStageCreation()
{
}
//Copy assignment operator
BGforStageCreation& BGforStageCreation::operator= (const BGforStageCreation& o)
{
    if (this == &o) return *this;   // Gracefully handle self assignment
    // Put the normal assignment duties here...

    return *this;
}
*/




void  BGforStageCreation::Fill_FirstOHtsI(
        const PlanningUnitMADPDiscrete* pu,
        Index ts, 
        vector<Index>& firstOHtsI
        )
{
    firstOHtsI.clear();
    //because the OHs are constructed breath-first, we know the OHs for agent i
    //for this time step are numbered:
    //firstOHtsGI[i]...firstOHtsGI[i]+nrOH[i]-1
    //
    //(read first-OH-for-time-step-ts its Global Index)
    //
    //i.e. ohGI = ohI + firstOHtsGI 

    for(Index agI=0; agI < pu->GetNrAgents(); agI++)
    {
        Index fI = pu->GetFirstObservationHistoryIndex(agI, ts);
        firstOHtsI.push_back(fI); 
    }
}

/*

//this function extends a previous policy jpolPrevTs for ts-1 with the behavior specified by the policy of the BayesianGame for time step ts (jpolBG).
PartialJointPolicyDiscretePure* 
BGforStageCreation::ConstructExtendedPolicy(
        PartialJointPolicyDiscretePure& jpolPrevTs, 
        JointPolicyDiscretePure& jpolBG, 
        vector<size_t>& nrOHts, 
        vector<Index>& firstOHtsI
        )
{
    //check policy types
    if(jpolPrevTs.GetIndexDomainCategory() != PolicyGlobals::OHIST_INDEX)
        throw E("BGforStageCreation::ConstructExtendedPolicy --- jpolPrevTs.GetIndexDomainCategory() != PolicyGlobals::OHIST_INDEX ");
    if(jpolBG.GetIndexDomainCategory() != PolicyGlobals::TYPE_INDEX)
        throw E("BGforStageCreation::ConstructExtendedPolicy --- jpolPrevTs.GetIndexDomainCategory() != PolicyGlobals::TYPE_INDEX ");
    //construct a policy for the DecPOMDP: 
    //a copy of jpolPrevTs with extended to this time step (ts) by 
    //jpolBG
    PartialJointPolicyDiscretePure* jpolTs = new 
        PartialJointPolicyPureVector(jpolPrevTs);
    jpolTs->SetDepth( jpolTs->GetDepth()+1 );
    for(Index agentI=0; agentI < GetNrAgents(); agentI++)
    {
        for(Index type = 0; type < nrOHts[agentI]; type++)
        {
            Index ohI = type + firstOHtsI[agentI];
            jpolTs->SetAction(agentI, ohI, 
                    jpolBG.GetActionIndex(agentI, type) );
        }         
    }
    return(jpolTs);
}
*/


void BGforStageCreation::Fill_joI_Array(
        const PlanningUnitMADPDiscrete* pu,
        const Index ts, 
        const vector<Index>& indTypes, 
        const vector<Index>& firstOHtsI, 
        Index* joI_arr)
{           
    //convert indiv type indices to ind. observation history indices:
    vector<Index> indOHI = vector<Index>(indTypes);
    // indivObservations[ti][agI]  will contain the observation agI received at tI+1
    vector< vector<Index> > indivObservations(ts,vector<Index>(
                pu->GetNrAgents() ) );
    for(Index agentI=0; agentI < pu->GetNrAgents(); agentI++)
    {
        indOHI[agentI] += firstOHtsI[agentI];
        Index * obsArr = new Index[ts];
        pu->GetObservationHistoryArrays(agentI, indOHI[agentI], ts, obsArr);
        //now obsArr is filled and can be copied into indivObservations
        for(Index tI=0; tI < ts; tI++)
            indivObservations.at(tI).at(agentI) = obsArr[tI];
		delete obsArr;
    }

    for(Index tI=0; tI < ts; tI++)
        joI_arr[tI] = pu->IndividualToJointObservationIndices(
                indivObservations[tI] );

/* old code - dependent on generation of individual observation histories.
    //convert indiv type indices to ind. observation history indices:
    vector<Index> indOHI = vector<Index>(indTypes);
    vector<const ObservationHistory*> indOH;
    for(Index agentI=0; agentI < GetNrAgents(); agentI++)
    {
        indOHI[agentI] += firstOHtsI[agentI];
        const ObservationHistoryTree* oht = 
            _m_pu->GetObservationHistoryTree(agentI, indOHI[agentI]);
        const ObservationHistory* oh = oht->GetObservationHistory();
        indOH.push_back(oh);
    }
    //convert the vector of  ind. observation history indices to a array of
    //joint observations
    for(int tI=ts-1; tI >= 0; tI--)
    {
        vector<Index> indivObservationsTI;
        for(Index agentI=0; agentI < GetNrAgents(); agentI++)
        {
            indivObservationsTI.push_back( indOH[agentI]->
                    GetLastObservationIndex() );
            indOH[agentI] =  indOH[agentI]->GetPredecessor();
        }
        joI_arr[tI] = _m_pu->IndividualToJointObservationIndices(
                indivObservationsTI);
    }
*/    
}

/*
//compute the joint actions taken bu jpolPrevTs when joht is the true joint 
//observation history at stage ts.
void BGforStageCreation::Fill_jaI_Array_OLD(
        Index ts, 
        const JointObservationHistoryTree* joht, 
        const JointPolicyDiscretePure* jpolPrevTs, 
        Index* jaI_arr
        )
{
    if(! (ts >= 1) ) // to guarantee that t2 > 0
    {   //ts == 0, we're constructing the first time-step BG...
        ; //TODO:check if we need to do something special here(?)
    }
    else // ts > 1
    {
        Index t2 = ts;// t2 > 0
        do
        {
            t2--; //in first iter. t2 = ts-1 > 0 (because ts > 1, see above)
            joht = joht->GetPredecessor();
            Index johI = joht->GetIndex();
            jaI_arr[t2] = jpolPrevTs->GetJointActionIndex(johI);
        }
        while(t2 > 0);
    }
    //t2 == 0
}
*/

//compute the joint actions taken bu jpolPrevTs when joIs is the true joint 
//observation history at stage ts.
void BGforStageCreation::Fill_jaI_Array(
        const PlanningUnitMADPDiscrete* pu,
        Index ts, 
        Index joIs[], //the array of joint observations issued 
        const JointPolicyDiscretePure* jpolPrevTs, 
        Index* jaI_arr
        )
{
    Index johI = 0;
    Index t = 0;
    while(t < ts)
    {
        Index ja = jpolPrevTs->GetJointActionIndex(johI);
        jaI_arr[t] = ja;

        Index next_joI = joIs[t];
        johI = pu->GetSuccessorJOHI(johI, next_joI);
        t++;
    }
}

/*
const JointObservationHistoryTree* BGforStageCreation:: 
Get_joht(PlanningUnitMADPDiscrete* pu, const Index ts, const Index* joI_arr)
{
    JointObservationHistoryTree* joht = 
        pu->GetJointObservationHistoryTree(0);
    Index tI = 0;
    while(tI < ts)
    {
        joht = joht->GetSuccessor(joI_arr[tI]);
        tI++;
    }
    return(joht);

} 
*/

/**Calculates the jaohI corresponding to jaI_arr and joI_arr and also 
 * returnes the P(jaohI) and the expected obtained reward for previous
 * time steps GIVEN this joint action history.
 *
 * \todo TODO add following to .h
 *
 * basically this function is a form of
 *      PlanningUnitMADPDiscrete::GetJAOHProbs(Recursively)
 * that also computes the reward.
 *
void BGforStageCreation::ProbRewardForjoahI(
        //input args
        Index ts, Index jtI, Index* jaI_arr,Index* joI_arr, 
        //output args
        Index& jaohI, double& PjaohI, double& ExpR_0_prevTS_thisJAOH )
{
    //first we get the initial jaoh
    JointActionObservationHistoryTree * jaoht = 
        _m_pu->GetJointActionObservationHistoryTree(0);

    double CPjaohI = 1.0; 
    PjaohI = CPjaohI; // == 1.0

    // get the initaal belief
    JointBeliefInterface* jb = _m_pu->GetISD();

    Index tI = 0;
    while(tI < ts)
    {
        //calculate the R for tI
        double ExpR_0_prevTS_thisJAOH_thisT = 0.0;
#if USE_BeliefIteratorGeneric
        BeliefIteratorGeneric it=jb->GetIterator();
        do
        {
            double R_si_ja = _m_pu->GetReward(it.GetStateIndex(), jaI_arr[tI]); 
            if(DEBUG_BG4DECPOMDP4) 
                cout << "R(s="<<it.GetStateIndex()<<",ja="<<jaI_arr[tI]<<")="<< R_si_ja << "\n";
            ExpR_0_prevTS_thisJAOH_thisT += it.GetProbability() * R_si_ja;
        } while(it.Next());
#else
        for(Index sI=0; sI < _m_pu->GetNrStates(); sI++)
        {
            double R_si_ja = _m_pu->GetReward(sI, jaI_arr[tI]); 
            if(DEBUG_BG4DECPOMDP4) 
                cout << "R(s="<<sI<<",ja="<<jaI_arr[tI]<<")="<< R_si_ja << "\n";
            ExpR_0_prevTS_thisJAOH_thisT += jb->Get(sI) * R_si_ja;
        }
#endif
        ExpR_0_prevTS_thisJAOH += ExpR_0_prevTS_thisJAOH_thisT;
        if(DEBUG_BG4DECPOMDP4)
        {
            cout << "calculating expected reward R(oaHist,a) for tI="<<tI
                <<"oaHist:"; jaoht->GetJointActionObservationHistory()->Print();
            cout << endl; cout << "R(b,a) (exp reward for jtI="  << jtI << 
                ", tI="<<tI<<") is "<< ExpR_0_prevTS_thisJAOH_thisT <<endl;

        }
            jaoht = jaoht->GetSuccessor( jaI_arr[tI], joI_arr[tI] );
            jaohI = jaoht->GetIndex();

        CPjaohI = jb->Update( *_m_pu, jaI_arr[tI], joI_arr[tI]  );
        PjaohI =  PjaohI * CPjaohI;     
        tI++;
    }
    delete jb; //free the belief allocated with 'new'
    if(DEBUG_BG4DECPOMDP4)
    {
        cout << "expected previous reward (up to ts-1) for (jtI="  << jtI << 
            ") ";
        jaoht->GetJointActionObservationHistory()->Print();
        cout << " is "<< ExpR_0_prevTS_thisJAOH <<endl << endl;
    }
}

 * */
