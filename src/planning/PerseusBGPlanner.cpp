/**\file PerseusBGPlanner.cpp
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
 * $Id: PerseusBGPlanner.cpp 3028 2008-11-15 14:44:05Z faolieho $
 */

#include "PerseusBGPlanner.h"
#include "BeliefValue.h"
#include <float.h>
#include <fstream>
#include <limits.h>

using namespace std;

#define DEBUG_PerseusBGPlanner 0
#define PerseusBGPlanner_alternativeSampling 0

//Default constructor
PerseusBGPlanner::PerseusBGPlanner(const PlanningUnitDecPOMDPDiscrete& pu,
                                   const QAVParameters& params) :
    AlphaVectorPlanning(pu),
    AlphaVectorBG(pu),
    PerseusQFunctionPlanner(pu),
    _m_backupType(params.bgBackupType)
{
    AlphaVectorPlanning::Initialize();
    Perseus::Initialize();
}

PerseusBGPlanner::PerseusBGPlanner(const PlanningUnitDecPOMDPDiscrete& pu) :
    AlphaVectorPlanning(pu),
    AlphaVectorBG(pu),
    PerseusQFunctionPlanner(pu),
    _m_backupType(BGIP_SOLVER_EXHAUSTIVE)
{
    AlphaVectorPlanning::Initialize();
    Perseus::Initialize();
}

//Destructor
PerseusBGPlanner::~PerseusBGPlanner()
{
}


QFunctionsDiscrete
PerseusBGPlanner::BackupStage(const BeliefSet &S,
                              const QFunctionsDiscrete &Q) const
{
    if(_m_computeVectorForEachBelief)
        return(BackupStageAll(S,Q));
    else
    {
#if PerseusBGPlanner_alternativeSampling
        return(BackupStageSamplingAlt(S,Q));
#else
        return(BackupStageSampling(S,Q));
#endif        
    }
}


QFunctionsDiscrete
PerseusBGPlanner::BackupStageAll(const BeliefSet &S,
                                 const QFunctionsDiscrete &Q) const
{
    vector<double> VB=BeliefValue::GetValues(S,Q),
        VBalpha;

    int nrB=VB.size(),
        nrS=GetPU()->GetNrStates();
    QFunctionsDiscrete Q1(Q.size());
    AlphaVector alpha(nrS);

    ValueFunctionPOMDPDiscrete V=QFunctionsToValueFunction(Q);
    GaoVectorSet Gao=BackupStageLeadIn(V);

    ValueFunctionPOMDPDiscrete Qalphas;

    for(int k=0;k<nrB;++k)
    {
        Qalphas.clear();
        for(unsigned int a=0;a!=GetPU()->GetNrJointActions();++a)
        {
            // backup the belief
            alpha=BeliefBackup(*S[k],a,Gao,V,_m_backupType);
           
            // add alpha to Q1
            if(!VectorIsInValueFunction(alpha,Q1[a]))
                Q1[a].push_back(alpha);
            Qalphas.push_back(alpha);
        }

        if(GetVerbose())
        {
            VBalpha=BeliefValue::GetValues(S,Qalphas);
            cout << "Added vectors for " << k << " (V " << VBalpha[k] 
                 << ")" << endl;
        }
    }

    BackupStageLeadOut(Gao);

    return(Q1);
}

QFunctionsDiscrete
PerseusBGPlanner::BackupStageSampling(const BeliefSet &S,
                                      const QFunctionsDiscrete &Q) const
{

    vector<double> VB=BeliefValue::GetValues(S,Q),
        VBalpha;
    vector<vector<double> > QB;
    for(unsigned int a=0;a!=Q.size();++a)
        QB.push_back(BeliefValue::GetValues(S,Q[a]));

    int nrB=VB.size(),
        nrNotImproved=nrB,
        nrS=GetPU()->GetNrStates(),
        k;
    double oldValue;
    vector<bool> stillNeedToBeImproved(nrB,true);
    QFunctionsDiscrete Q1(Q.size());
    AlphaVector alpha(nrS);

    ValueFunctionPOMDPDiscrete V=QFunctionsToValueFunction(Q);
    GaoVectorSet Gao=BackupStageLeadIn(V);

    ValueFunctionPOMDPDiscrete Qalphas;

    while(nrNotImproved!=0)
    {
        // sample a belief index from the number of not improved beliefs
        k=SampleNotImprovedBeliefIndex(stillNeedToBeImproved,nrNotImproved);

        Qalphas.clear();
        for(unsigned int a=0;a!=GetPU()->GetNrJointActions();++a)
        {
            // backup the belief
            alpha=BeliefBackup(*S[k],a,Gao,V,_m_backupType);

            // check whether alpha improves the value of S[k]
            double x=S[k]->InnerProduct(alpha.GetValues());

            // if not, get copy from old value function
            oldValue=QB[a][k];//VB[k]
            if(x<oldValue)
            {
#if DEBUG_PerseusBGPlanner
                cout << "Getting n-1 vector for action " << a << ", belief "
                     << k << " (" << x << " < " <<oldValue << ")" << endl;
#endif
                alpha=BeliefValue::GetMaximizingVector(S,k,Q[a]);
            }
            else
            {
                if(GetVerbose())
                    cout << "Added vector for action " << a << ", belief " 
                         << k << " (Q " << x << " >= " << oldValue << ")"
                         << endl;
            }
            // add alpha to Q1
            if(!VectorIsInValueFunction(alpha,Q1[a]))
                Q1[a].push_back(alpha);
            Qalphas.push_back(alpha);
        }

        // update which beliefs have been improved
        VBalpha=BeliefValue::GetValues(S,Qalphas);
        int nrImprovedByAlpha=0;
        for(int b=0;b!=nrB;b++)
            if(stillNeedToBeImproved[b] && VBalpha[b]>=VB[b])
            {
                stillNeedToBeImproved[b]=false;
                nrNotImproved--;
                nrImprovedByAlpha++;
            }

        if(GetVerbose())
            cout << "Added vectors for " << k << " (V " << VBalpha[k] 
                 << " improved " << nrImprovedByAlpha << ")" << endl;
    }

    BackupStageLeadOut(Gao);

    return(Q1);
}

QFunctionsDiscrete
PerseusBGPlanner::BackupStageSamplingAlt(const BeliefSet &S,
                                         const QFunctionsDiscrete &Q) const
{
    vector<double> VB=BeliefValue::GetValues(S,Q),
        VBalpha;

    int nrB=VB.size(),
        nrNotImproved=nrB,
        nrS=GetPU()->GetNrStates(),
        k;
    vector<bool> stillNeedToBeImproved(nrB,true);
    QFunctionsDiscrete Q1(Q.size());
    AlphaVector alpha(nrS);

    ValueFunctionPOMDPDiscrete V=QFunctionsToValueFunction(Q);
    GaoVectorSet Gao=BackupStageLeadIn(V);

    ValueFunctionPOMDPDiscrete Qalphas;

    k=-1;

    while(nrNotImproved!=0)
    {
        Qalphas.clear();
        for(unsigned int a=0;a!=GetPU()->GetNrJointActions();++a)
        {
            // sample a belief index from the number of not improved beliefs
            k=SampleNotImprovedBeliefIndex(stillNeedToBeImproved,nrNotImproved);
            // backup the belief
            alpha=BeliefBackup(*S[k],a,Gao,V,_m_backupType);

            // check whether alpha improves the value of S[k]
            double x=S[k]->InnerProduct(alpha.GetValues());
            // if not, get copy from old value function
            if(x<VB[k]) //QB[a][k])//VB[k])
            {
#if DEBUG_PerseusBGPlanner
                cout << "Getting n-1 vector for action " << a << ", belief "
                     << k << " (" << x << " < " << VB[k] << ")" << endl;
#endif
                alpha=BeliefValue::GetMaximizingVector(S,k,Q[a]);
            }
            else
            {
                if(GetVerbose())
                    cout << "Added vector for action " << a << ", belief " 
                         << k << " (Q " << x << " >= " << VB[k] << ")"
                         << endl;
            }
            
            // add alpha to Q1
            if(!VectorIsInValueFunction(alpha,Q1[a]))
                Q1[a].push_back(alpha);
            Qalphas.push_back(alpha);
        }

        // update which beliefs have been improved
        VBalpha=BeliefValue::GetValues(S,Qalphas);
        int nrImprovedByAlpha=0;
        for(int b=0;b!=nrB;b++)
            if(stillNeedToBeImproved[b] && VBalpha[b]>=VB[b])
            {
                stillNeedToBeImproved[b]=false;
                nrNotImproved--;
                nrImprovedByAlpha++;
            }

        if(GetVerbose())
            cout << "Added vectors for " << k << " (V " << VBalpha[k] 
                 << " improved " << nrImprovedByAlpha << ")" << endl;
    }

    BackupStageLeadOut(Gao);

    return(Q1);
}
