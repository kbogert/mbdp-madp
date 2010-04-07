/**\file QPOMDP.cpp
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
 * $Id: QPOMDP.cpp 3598 2009-08-20 12:29:54Z mtjspaan $
 */

#include "QPOMDP.h"
#include "PlanningUnitDecPOMDPDiscrete.h"
#include "JointActionObservationHistoryTree.h"
#include "JointObservationHistoryTree.h"
#include "JointObservation.h"
#include "JointBeliefInterface.h"
#include "BeliefIteratorGeneric.h"
#include <float.h>

using namespace std;

#define DEBUG_QPOMDP 0
#define DEBUG_QPOMDP_COMP 0
#define DEBUG_QPOMDP_COMPREC 0

#if DEBUG_QPOMDP_COMPREC
#include "BayesianGameIdenticalPayoff.h"
#endif

//Default constructor
QPOMDP::QPOMDP(const PlanningUnitDecPOMDPDiscrete& pu)
    :
    QFunctionForDecPOMDP(pu), //virtual base first
    QFunctionJAOHTree(pu) 
{
}

//Destructor
QPOMDP::~QPOMDP()
{
}

//this uses cached joint beliefs per def.:
#if QFunctionJAOH_useIndices
double QPOMDP::ComputeRecursively(size_t time_step, 
                                  LIndex jaohI,
                                  Index lastJAI)
#else
double QPOMDP::ComputeRecursively(size_t time_step, 
                                  JointActionObservationHistoryTree* jaoht,
                                  Index lastJAI)
#endif
// time_step    is the time-step of the BG that is constructed (and solved) in 
//              this function
//              
// jah          joint action history at t=time_step-1
// joh          joint obser. history at t=time_step-1
// (together they are denoted jaoh, the joint act-obs hist. at t-1 )
//
// jB           jaoh induces a probability over states, the joint belief
//
// lastJA       ja at t=time_step-1 (so the JA taken at joah )
{
    bool last_t = ( (time_step + 1) == GetPU()->GetHorizon()) ;

#if !QFunctionJAOH_useIndices
    JointActionObservationHistory* jaoh = jaoht->
        GetJointActionObservationHistory();
    Index jaohI = jaoht->GetIndex();
#endif

#if DEBUG_QPOMDP_COMPREC
    cout << "QPOMDP::ComputeRecursively:"<< endl 
         << "time_step t="<<time_step << ", prev. jaoh index jaoh^(t-1)="<<jaohI
         << ", prev. ja="<<lastJAI <<endl;

    BayesianGameIdenticalPayoff bg_time_step(GetPU()->GetNrAgents(), 
                                             GetPU()->GetNrActions(),
                                             GetPU()->GetNrObservations());
#endif

    double v = 0.0;
    double discount = GetPU()->GetDiscount();
//--------------------------------------------
//XXX TODO discuss with how this should be changed for sparse beliefs
//such that the line below doesn't crash.
//-------------------------------------------
    JointBeliefInterface* newJB = GetPU()->GetNewJointBeliefInterface();
    //for all jointobservations newJO (jo^time_step)
    for(Index newJOI=0; newJOI < GetPU()->GetNrJointObservations(); newJOI++)
    {
        if(DEBUG_QPOMDP_COMPREC){ 
            cout << "looking for joint observationI="<<newJOI <<" (=";
            GetPU()->GetJointObservation(newJOI)->Print();cout <<")"<<endl;}

        Index new_jaohI;
#if QFunctionJAOH_useIndices
        new_jaohI = GetPU()->GetSuccessorJAOHI(jaohI, lastJAI, newJOI);
#else    
        JointActionObservationHistoryTree* new_jaoht = jaoht->GetSuccessor(
                lastJAI,newJOI);
        new_jaohI = new_jaoht->GetIndex();
#endif
        
        //get the new joint belief at this time-step resulting from lastJAI, 
        //newJOI...(the true prob. dist over states for the actions and obser-
        //vations as given by the history < jaoh, lastJA, newJOI > )
            
        //double Po_ba = GetPU()->GetJBeliefConditionalProb(new_jaohI);


//--------------------------------------------
//TODO XXX
//why does it not crash here?!
//-------------------------------------------
        double Po_ba = GetPU()->GetJAOHProbs(newJB, new_jaohI, jaohI);

        // if the probability of this observation occurring is zero,
        // the belief is not defined, and don't have to consider this
        // part of the tree anymore
        if(Po_ba<PROB_PRECISION)
            continue;

        if(DEBUG_QPOMDP_COMPREC){
            cout << "the new jaoh (for this joint observationI="<<newJOI<<")\n"
                "new jaohI="<< new_jaohI <<
                endl<<" new belief newJB="<< newJB->SoftPrint() << endl; }
#if DEBUG_QPOMDP_COMPREC
            bg_time_step.SetProbability(newJOI, Po_ba);
#endif
        double maxQ = -DBL_MAX;
        for(Index newJAI=0; newJAI < GetPU()->GetNrJointActions(); newJAI++)
        {
            //calculate R(joah',newJA) - expected immediate reward for time_step
            double exp_imm_R = 0.0;

#if USE_BeliefIteratorGeneric
            BeliefIteratorGeneric it=newJB->GetIterator();
            do exp_imm_R += it.GetProbability() *
                GetPU()->GetReward(it.GetStateIndex(), newJAI);
            while(it.Next());
#else
            for(Index sI=0; sI < GetPU()->GetNrStates(); sI++)
//--------------------------------------------
//TODO XXX
//the following line crashes with sparse beliefs, because sparse beliefs
//are initialized with
//        return (new JointBeliefSparse() );
//( rather then new JointBelief(GetNrStates()) )
//Therefore the Get() request here can fail:
//--------------------------------------------
                exp_imm_R += newJB->Get(sI)*GetPU()->GetReward(sI, newJAI);
#endif
            
            //calculate Q(jaoh', newJA) =  R(joah',newJA) + exp. future R
            //  and the exp. future R = ComputeRecursively(t+1, jaoh', newJA)
            double exp_fut_R = 0.0;
            if(!last_t)
#if QFunctionJAOH_useIndices
                exp_fut_R = ComputeRecursively(time_step+1, new_jaohI, newJAI);
#else
                exp_fut_R = ComputeRecursively(time_step+1, new_jaoht, newJAI);
#endif
            double Q = exp_imm_R + discount * exp_fut_R;
            if(Q > maxQ)
                maxQ = Q;
            _m_QValues(new_jaohI,newJAI)=Q;
#if DEBUG_QPOMDP_COMPREC
                bg_time_step.SetUtility(newJOI, newJAI, Q);
#endif
        }//end for newJAI
#if DEBUG_QPOMDP_COMPREC
        {
            //BG used to store and then print
            bg_time_step.PrintUtilForJointType(newJOI);
            cout << "->max = " << maxQ<<endl;
        }
#endif
        // v = v + P(jo|b,a) * max_a Q(b'_jo,a)
        v += Po_ba * maxQ;
    }//end for newJOI

    delete newJB;

    if(DEBUG_QPOMDP_COMPREC)
    {
        cout << "QPOMDP::ComputeRecursively:"<< endl << "time_step t="<<
            time_step << ", prev. jaoh index jaoh^(t-1)="<<jaohI
             << ", prev. ja="<<lastJAI <<endl
             <<"FINISHED - v="<<v<<endl<<endl;
    }
    return( v );
}
