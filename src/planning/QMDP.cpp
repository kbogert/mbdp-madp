/**\file QMDP.cpp
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
 * $Id: QMDP.cpp 3598 2009-08-20 12:29:54Z mtjspaan $
 */

#include "QMDP.h"
#include "JointActionObservationHistoryTree.h"
#include "JointBelief.h"
#include "JointBeliefSparse.h"

using namespace std;

//Default constructor
QMDP::QMDP(const PlanningUnitDecPOMDPDiscrete& pu,
           bool useJaohQValuesCache) :
    QFunctionForDecPOMDP(pu), //virtual base first
    QFunctionJAOH(pu),
    _m_initialized(false),
    _m_useJaohQValuesCache(useJaohQValuesCache)
{
}

//Destructor
QMDP::~QMDP()
{    
    DeInitialize();
}

void QMDP::Initialize()
{
    if(_m_useJaohQValuesCache)
        _m_QValues.resize(GetPU()->GetNrJointActionObservationHistories(),
                          GetPU()->GetNrJointActions(),
                          false);

    _m_p=new MDPValueIteration(*GetPU());

    _m_initialized=true;
}

void QMDP::DeInitialize()
{
    delete _m_p;
    _m_QValues.clear();
    _m_initialized=false;
}

void QMDP::SetPU(const PlanningUnitDecPOMDPDiscrete& pu)
{
    DeInitialize();
    QFunctionJAOH::SetPU(pu);
}

void QMDP::Compute()
{
    if(!_m_initialized)
        Initialize();

    _m_p->Plan();

    if(_m_useJaohQValuesCache)
        CacheJaohQValues();
}

void QMDP::CacheJaohQValues()
{
    for(Index jaohI=0;
        jaohI!=GetPU()->GetNrJointActionObservationHistories();
        ++jaohI)
    {
        Index t = GetPU()->GetJointActionObservationHistoryTree(jaohI)->
            GetJointActionObservationHistory()->GetLength();
        for(Index jaI=0;jaI!=GetPU()->GetNrJointActions();++jaI)
            _m_QValues(jaohI,jaI)=
                _m_p->GetQ (t, *GetPU()->GetJointBeliefInterface(jaohI), jaI);
    }
}

double QMDP::GetQNoCache(Index jaohI, Index jaI) const
{
    Index t = GetPU()->GetTimeStepForJAOHI(jaohI);
    //Index t = GetPU()->GetJointActionObservationHistoryTree(jaohI)->
        //GetJointActionObservationHistory()->GetLength();
    JointBeliefInterface * jb = GetPU()->GetJointBeliefInterface(jaohI);
    double q = _m_p->GetQ (t, *jb, jaI);
    delete jb;
    return( q );
}

double QMDP::GetQSA(Index t, Index sI, Index jaI) const
{
    double q = _m_p->GetQ (t, sI, jaI);
    return( q );
}

double QMDP::GetQ(const JointBeliefInterface &b, Index jaI) const
{
    return(_m_p->GetQ(b,jaI));
}

double QMDP::GetQ(const JointBeliefInterface &b, Index time_step,
                  Index jaI) const
{
    return(_m_p->GetQ(time_step,b,jaI));
}

void QMDP::Save(string filename) const
{
    if(_m_useJaohQValuesCache)
        MDPSolver::SaveQTable(_m_QValues,filename);
    else
        MDPSolver::SaveQTables(_m_p->GetQTables(),filename);
}

void QMDP::Load(string filename)
{
    if(_m_useJaohQValuesCache)
        _m_QValues=MDPSolver::LoadQTable(filename,
                                         GetPU()->
                                         GetNrJointActionObservationHistories(),
                                         GetPU()->GetNrJointActions());
    else
        _m_p->SetQTables(MDPSolver::LoadQTables(filename,
                                                GetPU()->GetNrStates(),
                                                GetPU()->GetNrJointActions(),
                                                GetPU()->GetHorizon()));
}
