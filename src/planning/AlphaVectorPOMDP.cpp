/**\file AlphaVectorPOMDP.cpp
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
 * $Id: AlphaVectorPOMDP.cpp 2944 2008-10-23 16:10:26Z mtjspaan $
 */

#include "AlphaVectorPOMDP.h"
#include "BeliefValue.h"
#include <float.h>
#include <fstream>
#include "PlanningUnitDecPOMDPDiscrete.h"
#include "AlphaVector.h"

using namespace std;

//Default constructor
AlphaVectorPOMDP::AlphaVectorPOMDP(const PlanningUnitDecPOMDPDiscrete& pu) :
    AlphaVectorPlanning(pu)
{
}

//Destructor
AlphaVectorPOMDP::~AlphaVectorPOMDP()
{
}

/**
 * Implements equation (3.18) of PhD thesis Matthijs.
 */
AlphaVector AlphaVectorPOMDP::BeliefBackup(const JointBeliefInterface &b,
                                           const GaoVectorSet &G) const
{
    int nrA=GetPU()->GetNrJointActions(),
        nrO=GetPU()->GetNrJointObservations(),
        nrS=GetPU()->GetNrStates();
    VectorSet *VS;
    // stores the index of the vector that maximizes b's value
    int maximizingVectorI;

    StartTimer("BeliefBackupPOMDP");

    VectorSet Gab(nrA,nrS);

    // compute the Gab vectors
    for(GaoVectorSetIndex a=0;a!=nrA;a++)
    {
        // initialize each Gab vector with the immediate reward
        for(int s=0;s!=nrS;s++)
            Gab(a,s)=GetPU()->GetReward(s,a);

        for(GaoVectorSetIndex o=0;o!=nrO;o++)
        {
            VS=G[a][o];
            maximizingVectorI=BeliefValue::GetMaximizingVectorIndex(b,*VS);

            // add discounted maximizing vector (3.16)
            for(int s=0;s!=nrS;s++)
                Gab(a,s)+=GetPU()->GetDiscount()*
                    (*VS)(maximizingVectorI,s);
        }
    }

    // find the maximizing Gab vector
    int maxA=BeliefValue::GetMaximizingVectorIndex(b,Gab);

    // create the vector for b
    AlphaVector newVector(nrS);
    newVector.SetAction(maxA);
    for(int s=0;s!=nrS;s++)
        newVector.SetValue(Gab(maxA,s),s);

    StopTimer("BeliefBackupPOMDP");

    return(newVector);
}

AlphaVector AlphaVectorPOMDP::BeliefBackup(const JointBeliefInterface &b,
                                           Index a,
                                           const GaoVectorSet &G) const
{
    int nrO=GetPU()->GetNrJointObservations(),
        nrS=GetPU()->GetNrStates();
    VectorSet *VS;
    // stores the index of the vector that maximizes b's value
    int maximizingVectorI;

    StartTimer("BeliefBackupPOMDP");

    vector<double> Gab(nrS);

    // initialize Gab vector with the immediate reward
    for(int s=0;s!=nrS;s++)
        Gab[s]=GetPU()->GetReward(s,a);
    
    for(GaoVectorSetIndex o=0;o!=nrO;o++)
    {
        VS=G[a][o];
        maximizingVectorI=BeliefValue::GetMaximizingVectorIndex(b,*VS);
        
        // add discounted maximizing vector (3.16)
        for(int s=0;s!=nrS;s++)
            Gab[s]+=GetPU()->GetDiscount()*
                (*VS)(maximizingVectorI,s);
    }

    // create the vector for b
    AlphaVector newVector(nrS);
    newVector.SetAction(a);
    for(int s=0;s!=nrS;s++)
        newVector.SetValue(Gab[s],s);

    StopTimer("BeliefBackupPOMDP");

    return(newVector);
}
