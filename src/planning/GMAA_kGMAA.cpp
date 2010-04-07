/**\file GMAA_kGMAA.cpp
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
 * $Id: GMAA_kGMAA.cpp 3603 2009-08-25 10:38:25Z mtjspaan $
 */

#include "GMAA_kGMAA.h"
#include "JPPVValuePair.h"
#include "PartialJPDPValuePair.h"
#include "PartialPolicyPoolInterface.h"
#include "PolicyPoolPartialJPolValPair.h"
#include "BayesianGameForDecPOMDPStage.h"
#include "BayesianGameIdenticalPayoffSolver.h"
#include "BGIP_SolverCreatorInterface.h"
#include "PartialJointPolicyPureVector.h"

using namespace std;

GMAA_kGMAA::GMAA_kGMAA(
    const PlanningUnitMADPDiscreteParameters &params,
    const BGIP_SolverCreatorInterface<JointPolicyPureVector> * bgsc,
    size_t horizon, 
    DecPOMDPDiscreteInterface* p,
    size_t nrPoliciesToProcess) :
    GeneralizedMAAStarPlannerForDecPOMDPDiscrete(params, horizon, p),
    _m_newBGIP_Solver(bgsc)
{
    _m_nrPoliciesToProcess=nrPoliciesToProcess;
}

//This function will construct and sove a BG for the next timestep ts
bool GMAA_kGMAA::ConstructAndValuateNextPolicies(
        PartialPolicyPoolItemInterface* ppi, 
        PartialPolicyPoolInterface* poolOfNextPolicies
        )
{
    PartialJointPolicyDiscretePure* jpolPrevTs = ppi->GetJPol();//jpol^ts-1
    size_t ts = jpolPrevTs->GetDepth();     // = depth = ts(jpolPrevTs) + 1
    bool is_last_ts = (ts ==  GetHorizon() - 1);

    vector<Index> firstOHtsI(GetNrAgents());
    for(Index agI=0; agI < GetNrAgents(); agI++)
        firstOHtsI.at(agI) = GetFirstObservationHistoryIndex(agI, ts);
    // Construct the bayesian game for this timestep - 
    BayesianGameForDecPOMDPStage *bg_ts= new BayesianGameForDecPOMDPStage(
            this,
            _m_qHeuristic,
            jpolPrevTs
            );

    _m_bgCounter++;
    if(_m_bgBaseFilename!="")
    {
        stringstream ss;
        ss << _m_bgBaseFilename << _m_bgCounter;
        BayesianGameIdenticalPayoff::Save(*bg_ts,ss.str());
    }

    double prevPastReward = jpolPrevTs->GetPastReward();
    const vector<size_t>& nrOHts = bg_ts->GetNrTypes(); 
    //size_t nrJOHts = bg_ts->GetNrJointTypes(); 

    //The set of Indicies of the policies added to poolOfNextPolicies
    //(to avoid adding duplicates).
    set<Index> poolOfNextPoliciesIndices;

    //the policy for the Bayesian game 
    JointPolicyPureVector jpolBG = JointPolicyPureVector(*bg_ts,
            PolicyGlobals::TYPE_INDEX);

    stringstream ss;
    ss << "GMAA::kGMAA_ts" << ts;
    StartTimer(ss.str());

    //solve the Bayesian game
    BayesianGameIdenticalPayoffSolver<JointPolicyPureVector> * bgips = (*_m_newBGIP_Solver)(*bg_ts);
    //TODO bgips->SetAnyTimeResults(true, FILES...);
    bgips->Solve();
    BGIPSolution & solution = bgips->GetSolution();

    //for each solution in BGIPSolution  
    bg_ts->ComputeAllImmediateRewards();
    for(Index solI=0; solI < _m_nrPoliciesToProcess; solI++)
    {
        if(solution.IsEmptyJPPV())
        {
            cerr << "Warning, BGIP_Solver only returned "<<solI<<
                " usable joint policies"<<endl;
            break;
        }
        JPPVValuePair * jpvp = solution.GetNextSolutionJPPV();
        JointPolicyPureVector* bgpol = jpvp->GetJPPV();
        double val = jpvp->GetValue();

        solution.PopNextSolutionJPPV();
        PartialJointPolicyDiscretePure* jpolTs = 
            ConstructExtendedJointPolicy(*jpolPrevTs,
                                    *bgpol, nrOHts, firstOHtsI);
        //compute expected immediate reward for this stage
        double immR = bg_ts->ComputeDiscountedImmediateRewardForJPol(bgpol);
        double newPastreward = prevPastReward + immR;
        jpolTs->SetPastReward(newPastreward);
        //push this policy and value on the priority queue
        ////if last stage, if so, we want to return the 
        ////*EXACT* past reward, newPastreward.
        if(is_last_ts)
            poolOfNextPolicies->Insert( NewPPI(jpolTs,newPastreward) );
        else
            poolOfNextPolicies->Insert( NewPPI(jpolTs,
                                        val + prevPastReward) );
        delete jpvp;
    }
    //empty the imm reward cache
    bg_ts->ClearAllImmediateRewards();
    delete bg_ts;
    delete bgips; 
    StopTimer(ss.str());
    //if we created a BG for the last time step t=h-1 - we have a lowerbound
    return(is_last_ts);
}

void GMAA_kGMAA::SelectPoliciesToProcessFurther( PartialPolicyPoolInterface*
            poolOfNextPolicies, bool are_LBs, double bestLB)
{
    SelectKBestPoliciesToProcessFurther(poolOfNextPolicies, are_LBs, 
                                        bestLB, _m_nrPoliciesToProcess);
}                  

PartialPolicyPoolInterface* 
GMAA_kGMAA::NewPP()
{return (new PolicyPoolPartialJPolValPair);}

PartialPolicyPoolItemInterface* 
GMAA_kGMAA::NewPPI(PartialJointPolicyDiscretePure* jp, double v)
{
    //return (new JPPVValuePair(jp,v));
    PartialPolicyPoolItemInterface* ppi=new PartialJPDPValuePair(jp,v);
    return (ppi);
}


PartialJointPolicyDiscretePure* GMAA_kGMAA::NewJPol() const
{ 
    return new PartialJointPolicyPureVector(*this, OHIST_INDEX, 0.0);
}


