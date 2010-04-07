/**\file QFunctionJAOHTree.cpp
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
 * $Id: QFunctionJAOHTree.cpp 3604 2009-08-25 10:52:24Z mtjspaan $
 */

#include "QFunctionJAOHTree.h"
#include "PlanningUnitDecPOMDPDiscrete.h"
#include "MDPSolver.h"
#include "BayesianGameIdenticalPayoff.h"
#include "JointBeliefInterface.h"
#include "BGIP_SolverBruteForceSearch.h"

using namespace std;

#define DEBUG_QHEUR_COMP_TREE 0

//Default constructor
QFunctionJAOHTree::
QFunctionJAOHTree(const PlanningUnitDecPOMDPDiscrete &pu) :
    QFunctionForDecPOMDP(pu), //virtual base first
    QFunctionJAOH(pu)
{
    _m_initialized = false;
}

//Destructor
QFunctionJAOHTree::~QFunctionJAOHTree()
{
    DeInitialize();
}

void QFunctionJAOHTree::DeInitialize()
{
    _m_QValues.clear();
    _m_initialized=false;
}

void QFunctionJAOHTree::Initialize()
{
    _m_QValues.resize(GetPU()->GetNrJointActionObservationHistories(),
                      GetPU()->GetNrJointActions(),
                      false);
    _m_initialized = true;
}

void QFunctionJAOHTree::SetPU(const PlanningUnitDecPOMDPDiscrete& pu)
{
    DeInitialize();
    QFunctionJAOH::SetPU(pu);
}

void QFunctionJAOHTree::Compute()
{
    if(!_m_initialized)
        Initialize();

    ComputeQ();
}

void QFunctionJAOHTree::Save(string filename) const
{
    MDPSolver::SaveQTable(_m_QValues,filename);
}

void QFunctionJAOHTree::Load(string filename)
{
    _m_QValues=MDPSolver::LoadQTable(filename,
                                     GetPU()->
                                     GetNrJointActionObservationHistories(),
                                     GetPU()->GetNrJointActions());
}

void QFunctionJAOHTree::ComputeQ()
{
    if(GetPU() == 0)
        throw E("QFunctionJAOHTree::ComputeQ - GetPU() returns 0; no PlanningUnit available!");

    size_t time_step = 0;
#if QFunctionJAOH_useIndices
#else    
    JointActionObservationHistoryTree* root = GetPU()->
        GetJointActionObservationHistoryTree(Globals::INITIAL_JAOHI);
#endif
    JointBeliefInterface* b0p = GetPU()->GetNewJointBeliefFromISD(); 
    JointBeliefInterface& b0 =  *b0p;
    
    bool last_t = false;
    if( (time_step + 1) == GetPU()->GetHorizon()) //unlikely, but possible
        last_t = true;

    if(DEBUG_QHEUR_COMP_TREE){cout << "QFunctionJAOHTree::Compute() called" << endl;}

    //in the first time_step t=0, there is no previous action and there is only
    //the empty observation action history.
    //Therefore we're going to construct a Bayesian game where there is only 1
    //type for each agent.
    vector<size_t> nrTypes = vector<size_t>(GetPU()->GetNrAgents(), 1);
    BayesianGameIdenticalPayoff bg_time_step(GetPU()->GetNrAgents(), 
            GetPU()->GetNrActions(),nrTypes);

    size_t empty_jaohI = 0;
    bg_time_step.SetProbability(empty_jaohI, 1.0);
    for(Index newJAI=0; newJAI < GetPU()->GetNrJointActions(); newJAI++)
    {
        //calculate R(joah',newJA) - expected immediate reward for time_step
        double exp_imm_R = 0.0;
#if USE_BeliefIteratorGeneric
        BeliefIteratorGeneric it=b0.GetIterator();
        do exp_imm_R += it.GetProbability() *
            GetPU()->GetReward(it.GetStateIndex(), newJAI);
        while (it.Next());
#else
        for(Index sI=0; sI < GetPU()->GetNrStates(); sI++)
            exp_imm_R += (b0.Get(sI)) * GetPU()->GetReward(sI, newJAI);
#endif        
        //calculate Q(jaoh', newJA) =  R(joah',newJA) + exp. future R
        //  and the exp. future R = ComputeRecursively(t+1, root, newJA)
        double exp_fut_R = 0.0;
        if(!last_t)
#if QFunctionJAOH_useIndices
            exp_fut_R = ComputeRecursively( 1, Globals::INITIAL_JAOHI, newJAI);
#else    
            exp_fut_R = ComputeRecursively( 1, root, newJAI);
#endif
        double Q = exp_imm_R + GetPU()->GetDiscount() * exp_fut_R;
        _m_QValues(empty_jaohI,newJAI)=Q;
        bg_time_step.SetUtility(empty_jaohI, newJAI, Q);
    }//end for newJAI
    if(DEBUG_QHEUR_COMP_TREE)
    {
        cout << "QFunctionJAOHTree::ComputeQ() for..."<<endl<<
            " time_step=0  called, with ISD=";
        b0.Print();
        cout <<endl;
        bg_time_step.Print();
    }
    //solve this bayesian game
    BGIP_SolverBruteForceSearch<JointPolicyPureVector> bgs(bg_time_step);
    double v = bgs.Solve();
    if(DEBUG_QHEUR_COMP_TREE)
        cout << "QFunctionJAOHTree::ComputeQ() - Expected V(b0) = " << v << endl<< endl;
    delete b0p;
    return;
}
