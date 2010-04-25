/**\file Perseus.cpp
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
 * $Id: Perseus.cpp 3028 2008-11-15 14:44:05Z faolieho $
 */

#include "Perseus.h"
#include "AlphaVectorPlanning.h"
#include "PerseusBackupType.h"
#include <fstream>
#include <float.h>

using namespace std;

//Default constructor
Perseus::Perseus(const PlanningUnitDecPOMDPDiscrete& pu) :
    AlphaVectorPlanning(pu),
    _m_pu(&pu),
    _m_verbose(0),
    _m_initializeWithImmediateReward(false),
    _m_initializeWithZero(false),
    _m_bestValue(-DBL_MAX),
    _m_beliefsInitialized(false),
    _m_identification("Perseus"),
    _m_storeIntermediateValueFunctions(false),
    _m_storeTimings(false),
    _m_computeVectorForEachBelief(false),
    _m_dryrun(false)
{
    SetMinimumNumberOfIterations(10);
    SetMaximumNumberOfIterations(INT_MAX);
    UpdateValueFunctionName();
}

//Destructor
Perseus::~Perseus()
{
}

void Perseus::Initialize()
{
}

ValueFunctionPOMDPDiscrete Perseus::GetInitialValueFunction() const
{
    int nrS=_m_pu->GetNrStates(),
        nrA=_m_pu->GetNrJointActions();

    ValueFunctionPOMDPDiscrete V0;

    if(_m_initializeWithImmediateReward && _m_initializeWithZero)
        throw(E("Perseus::GetInitialValueFunction() can only initialize in one way"));

    if(_m_initializeWithImmediateReward)
    {
        AlphaVector alpha(nrS);
        for(int a=0;a<nrA;a++)
        {
            for(int s=0;s!=nrS;s++)
                alpha.SetValue(_m_pu->GetReward(s,a),s);
            V0.push_back(alpha);
        }
    }
    else
    {
        AlphaVector alpha(nrS);
        double initialValue;

        if(_m_initializeWithZero)
            initialValue=0;
        else
        {
            double minReward=DBL_MAX;
            for(int a=0;a<nrA;a++)
                for(int s=0;s<nrS;s++)
                    if(_m_pu->GetReward(s,a)<minReward)
                        minReward=_m_pu->GetReward(s,a);

            // check if the problem is finite or infinite horizon
            if(_m_pu->GetHorizon()!=MAXHORIZON)
                initialValue=minReward*_m_pu->GetHorizon();
            else
                initialValue=minReward/(1-_m_pu->GetDiscount());
        }

        for(int s=0;s!=nrS;s++)
            alpha.SetValue(initialValue,s);
        
        alpha.SetAction(INT_MAX); // set action to an illegal value
        V0.push_back(alpha);
    }

    return(V0);
}

QFunctionsDiscrete Perseus::GetInitialQFunctions() const
{
    QFunctionsDiscrete Q0;

    unsigned int nrS=_m_pu->GetNrStates(),
        nrA=_m_pu->GetNrJointActions();

    if(_m_initializeWithImmediateReward && _m_initializeWithZero)
        throw(E("Perseus::GetInitialQFunctions() can only initialize in one way"));

    if(_m_initializeWithImmediateReward)
    {
        AlphaVector alpha(nrS);
        ValueFunctionPOMDPDiscrete V0;
        for(unsigned int a=0;a!=nrA;++a)
        {
            V0.clear();
            for(unsigned int s=0;s!=nrS;++s)
                alpha.SetValue(_m_pu->GetReward(s,a),s);
            alpha.SetAction(a);
            V0.push_back(alpha);
            Q0.push_back(V0);
        }
    }
    else
    {
        ValueFunctionPOMDPDiscrete V0=GetInitialValueFunction();
        for(unsigned int a=0;a!=_m_pu->GetNrJointActions();++a)
        {
            for(unsigned int i=0;i!=V0.size();++i)
                V0[i].SetAction(a);
            Q0.push_back(V0);
        }
    }

    return(Q0);
}

QFunctionsDiscreteNonStationary
Perseus::GetInitialNonStationaryQFunctions() const
{
    QFunctionsDiscrete Qt0=GetInitialQFunctions();
    QFunctionsDiscreteNonStationary Q0;
    for(Index t=0;t!=GetPU()->GetHorizon();++t)
        Q0.push_back(Qt0);
    return(Q0);
}

void Perseus::PrintMaxRewardInBeliefSet() const
{
    if(!_m_beliefsInitialized)
        throw(E("Perseus::PrintMaxRewardInBeliefSet belief set not initialized"));

    vector<double> beliefValues=GetImmediateRewardBeliefSet();

    double maxBeliefValue=-DBL_MAX;
    for(unsigned int i=0;i!=beliefValues.size();i++)
    {
        if(beliefValues[i]>maxBeliefValue)
            maxBeliefValue=beliefValues[i];
    }
    if(GetVerbose() >= 0)
        cout << GetIdentification() << ": max reward in beliefset is "
             << maxBeliefValue << endl;
}

int Perseus::SampleNotImprovedBeliefIndex(vector<bool> stillNeedToBeImproved,
                                          int nrNotImproved) const
{
    int beliefI,l,k;

    // sample a belief index from the number of not improved beliefs
    beliefI=static_cast<int>(nrNotImproved*(rand() / (RAND_MAX + 1.0)));
    
    // figure out the index k of this belief in S 
    l=0;
    k=-1;
    for(unsigned int j=0;j!=stillNeedToBeImproved.size();j++)
    {
        if(stillNeedToBeImproved[j])
        {
            if(beliefI==l)
            {
                k=j;
                break;
            }
            l++;
        }
    }

    if(k==-1)
    {
        PrintVectorCout(stillNeedToBeImproved);
        cout << "nrNotImproved " << nrNotImproved << " beliefI "
             << beliefI << endl;
        throw(E("Perseus::SampleNotImprovedBeliefIndex did not sample valid k"));
    }
    return(k);
}

bool Perseus::CheckConvergence(const vector<double> &VB,
                               const vector<double> &VBnew,
                               int iter) const
{
    bool converged;

    double maxDiff=0;
    for(unsigned int i=0;i!=VB.size();i++)  // for all beliefs, 
        if(abs(VB[i]-VBnew[i])>maxDiff)     // get the difference in val
            maxDiff=abs(VB[i]-VBnew[i]);    // and store the maximum...

    if(GetVerbose() >= 1)
        cout << GetIdentification() << ":CheckConvergence maxDiff is "
             << maxDiff << endl;
    if(iter>=_m_maximumNumberOfIterations)
        converged=true;
    else if(maxDiff<1e-4 &&
       (static_cast<size_t>(iter) >
        max(static_cast<size_t>(_m_minimumNumberOfIterations),
            5*_m_pu->GetHorizon())))
        converged=true;
    else
    {
        if(iter>=max(_m_minimumNumberOfIterations,1000))
            converged=true;
        else
            converged=false;
    }

    return(converged);
}

void Perseus::PlanLeadIn()
{
    StartTimer(GetIdentification());

    if(!_m_beliefsInitialized)
    {
        int nrB=1000;
        // set the random seed and sample beliefs
        srand(42);
        if(GetVerbose() >= 0)
            cout << GetIdentification() << ": sampling " << nrB
                 << " beliefs"; cout.flush();
        InitializeBeliefs(nrB,true);
        if(GetVerbose() >= 0)
            cout << "." << endl;
    }

    // just a manual check to figure out if the belief set has potential
    PrintMaxRewardInBeliefSet();
}

void Perseus::PlanEndOfIteration() const
{
    if(_m_storeTimings)
    {
        stringstream ss;
        ss << directories::MADPGetResultsDir("POMDP",GetPU())
           << "/intermediate/" << GetIdentification() << "Timings_h"
           << GetPU()->GetHorizon();
        SaveTimers(ss.str());
    }
#if 0 // reduce verbosity
    PrintTimersSummary();
#endif
}

void Perseus::PlanLeadOut()
{
    StopTimer(GetIdentification());
    if(_m_storeTimings)
    {
        stringstream ss;
        ss << directories::MADPGetResultsDir("POMDP",GetPU()) << "/"
           << GetIdentification() << "Timings_h" << GetPU()->GetHorizon();
        SaveTimers(ss.str());
        if(GetVerbose() >= 1)
            cout << "Saved timing results to " << ss.str() << endl;
    }
}

GaoVectorSet
Perseus::BackupStageLeadIn(const ValueFunctionPOMDPDiscrete &V) const
{
    StartTimer(GetIdentification() + "BackupStage");

    return(BackProject(V));
}

void Perseus::BackupStageLeadOut(GaoVectorSet Gao) const
{
    // release the memory of the back-projected vectors
    for(unsigned int a=0;a!=GetPU()->GetNrJointActions();a++)
        for(unsigned int o=0;o!=GetPU()->GetNrJointObservations();o++)
            delete(Gao[a][o]);
    
    StopTimer(GetIdentification() + "BackupStage");
}

string Perseus::BackupTypeToString(const QAVParameters &params)
{
    stringstream ss;
    switch(params.backup)
    {
    case POMDP:
        ss << "POMDP";
        break;
    case BG:
        ss << "BG" << params.bgBackupType;
        break;
    default:
        ss << "PerseusBackupType " << params.backup << " is unknown";
        throw(E(ss));
    }
    return(ss.str());
}

QAVParameters Perseus::ProcessArguments(const ArgumentHandlers::Arguments &args)
{
    QAVParameters qavParams;
    qavParams.bgBackupType=BGIP_SOLVER_EXHAUSTIVE;
    
    qavParams.backup=args.backup;
    switch(args.backup)
    {
    case POMDP:
        break;
    case BG:
        qavParams.bgBackupType=args.bgBackup;
        break;
    }

    return(qavParams);
}

void Perseus::SetIdentification(string identification)
{ 
    _m_identification=identification;
    UpdateValueFunctionName();
}

void Perseus::SetResultsFilename(string filename)
{
    _m_resultsFilename=filename;
    UpdateValueFunctionName();
}

void Perseus::UpdateValueFunctionName()
{
    stringstream valueFunctionFilename;
    valueFunctionFilename << _m_resultsFilename
                          << GetIdentification()
                          << "ValueFunction_h" << _m_pu->GetHorizon();
    _m_valueFunctionFilename=valueFunctionFilename.str();

    if(GetVerbose() >= 1)
        cout << "Set value function filename to " << _m_valueFunctionFilename
             << endl;
}

void Perseus::StoreValueFunction(const ValueFunctionPOMDPDiscrete &V)
{
    throw(E("Perseus::StoreValueFunction should be implemented by deriving class"));
}

void Perseus::StoreValueFunction(const QFunctionsDiscrete &Q)
{
    throw(E("Perseus::StoreValueFunction should be implemented by deriving class"));
}

void Perseus::StoreValueFunction(const QFunctionsDiscreteNonStationary &Q)
{
    throw(E("Perseus::StoreValueFunction should be implemented by deriving class"));
}


