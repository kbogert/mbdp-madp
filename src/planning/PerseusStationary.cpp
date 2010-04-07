/**\file PerseusStationary.cpp
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
 * $Id: PerseusStationary.cpp 3633 2009-08-27 12:32:02Z mtjspaan $
 */

#include "PerseusStationary.h"
#include "argumentHandlers.h"

using namespace std;

//Default constructor
PerseusStationary::PerseusStationary(const PlanningUnitDecPOMDPDiscrete& pu) :
    AlphaVectorPlanning(pu),
    Perseus(pu)
{
}

//Destructor
PerseusStationary::~PerseusStationary()
{
    if(_m_beliefsInitialized)
        delete(_m_beliefs);
}

double PerseusStationary::GetQ(const JointBeliefInterface &b, Index jaI) const
{
    return(BeliefValue::GetValue(b,_m_qFunction[jaI]));
}

double PerseusStationary::GetQ(const JointBeliefInterface &b, Index jaI,
                               int &betaMaxI) const
{
    Index maxI=BeliefValue::
        GetMaximizingVectorIndex(b,_m_qFunction[jaI]);
    betaMaxI=_m_qFunction[jaI][maxI].GetBetaI();
    return(b.InnerProduct(_m_qFunction[jaI][maxI].GetValues()));
}

double PerseusStationary::GetQ(const JointBeliefInterface &b, Index t,
                               Index jaI) const
{
    throw(E("PerseusStationary::GetQ not implemented for non-stationary case"));
    return(42);
}

double PerseusStationary::GetQ(const JointBeliefInterface &b, Index t,
                               Index jaI, int &betaMaxI) const
{
    throw(E("PerseusStationary::GetQ not implemented for non-stationary case"));
    return(42);
}

/// If no belief is specified, one will be sampled using default
/// settings.
void PerseusStationary::SetBeliefSet(const BeliefSet &S)
{
    if(_m_beliefsInitialized)
        delete(_m_beliefs);
    _m_beliefs=new BeliefSet(S);
    _m_beliefsInitialized=true;
}

void PerseusStationary::ExportBeliefSet(const string &filename) const
{
    if(!_m_beliefsInitialized)
    {
        cout << "PerseusStationary::ExportBeliefSet: belief set not set"
             << endl;
    }
    else
        AlphaVectorPlanning::ExportBeliefSet(*_m_beliefs,filename);
}

/// Calls AlphaVectorPlanning::ExportValueFunction.
void PerseusStationary::ExportValueFunction(const string &filename) const
{
    AlphaVectorPlanning::ExportValueFunction(filename,_m_valueFunction);
}

std::vector<double> PerseusStationary::GetImmediateRewardBeliefSet() const
{
    return(BeliefValue::GetValues(*_m_beliefs,
                                  AlphaVectorPlanning::
                                  GetImmediateRewardValueFunction(GetPU())));
}

/** Also updates _m_qFunction. */
void PerseusStationary::SetValueFunction(const string &filename)
{
    _m_valueFunction=ImportValueFunction(filename);
    _m_qFunction=AlphaVectorPlanning::
        ValueFunctionToQ(_m_valueFunction,
                         GetPU()->GetNrJointActions(),
                         GetPU()->GetNrStates());
}

void PerseusStationary::InitializeBeliefs(int nrB, bool uniquify)
{
    ArgumentHandlers::Arguments args;
    args.nrBeliefs=nrB;
    args.uniqueBeliefs=uniquify;
    SetBeliefSet(SampleBeliefs(args));
}

void PerseusStationary::StoreValueFunction(const ValueFunctionPOMDPDiscrete &V)
{
    // store the resulting value function
    _m_valueFunction=V;
    // compute the Q functions from the value function
    _m_qFunction=ValueFunctionToQ(_m_valueFunction);
}

void PerseusStationary::StoreValueFunction(const QFunctionsDiscrete &Q)
{
    // store the resulting Q function and the value function
    _m_qFunction=Q;
    _m_valueFunction.clear();
    for(QFDcit i=Q.begin();i!=Q.end();++i)
        for(VFPDcit j=i->begin();j!=i->end();++j)
            if(j->GetAction()!=INT_MAX)
                _m_valueFunction.push_back(*j);
}
