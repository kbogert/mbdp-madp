/**\file PlanningUnitMADPDiscreteParameters.cpp
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
 * $Id: PlanningUnitMADPDiscreteParameters.cpp 3604 2009-08-25 10:52:24Z mtjspaan $
 */

#include "PlanningUnitMADPDiscreteParameters.h"

using namespace std;

//Default constructor
PlanningUnitMADPDiscreteParameters::PlanningUnitMADPDiscreteParameters()
{
    _m_individualObservationHistories=true;
    _m_individualActionHistories=true;
    _m_individualActionObservationHistories=true;
    _m_jointObservationHistories=true;
    _m_jointActionHistories=true;
    _m_jointActionObservationHistories=true;
    _m_JointBeliefs=true;
    _m_useSparseBeliefs=false;
}

//Destructor
PlanningUnitMADPDiscreteParameters::~PlanningUnitMADPDiscreteParameters()
{
}

void PlanningUnitMADPDiscreteParameters::SetComputeAllJointHistories(bool val)
{
    SetComputeJointObservationHistories(val);
    SetComputeJointActionHistories(val);
    SetComputeJointActionObservationHistories(val);
}

void
PlanningUnitMADPDiscreteParameters::SetComputeAllIndividualHistories(bool val)
{
    SetComputeIndividualObservationHistories(val);
    SetComputeIndividualActionHistories(val);
    SetComputeIndividualActionObservationHistories(val);
}

void PlanningUnitMADPDiscreteParameters::SetComputeAll(bool val)
{
    SetComputeAllIndividualHistories(val);

    // order is important because of the sanity check
    if(val)
    {
        SetComputeAllJointHistories(val);
        SetComputeJointBeliefs(val);
    }
    else
    {
        SetComputeJointBeliefs(val);
        SetComputeAllJointHistories(val);
    }
}

void PlanningUnitMADPDiscreteParameters::Print() const
{
    cout << "ComputeIndividualObservationHistories: "
         << GetComputeIndividualObservationHistories() << endl;

    cout << "ComputeIndividualActionHistories: "
         << GetComputeIndividualActionHistories() << endl;

    cout << "ComputeIndividualActionObservationHistories: "
         << GetComputeIndividualActionObservationHistories() << endl;

    cout << "ComputeJointObservationHistories: "
         << GetComputeJointObservationHistories() << endl;

    cout << "ComputeJointActionHistories: "
         << GetComputeJointActionHistories() << endl;

    cout << "ComputeJointActionObservationHistories: "
         << GetComputeJointActionObservationHistories() << endl;

    cout << "ComputeJointBeliefs: "
         << GetComputeJointBeliefs() << endl;

    cout << "UseSparseJointBeliefs: "
         << GetUseSparseJointBeliefs() << endl;
}

void PlanningUnitMADPDiscreteParameters::SanityCheck() const
{
    if(GetComputeJointBeliefs() && !GetComputeJointActionObservationHistories())
    {
        Print();
        throw(E("PlanningUnitMADPDiscreteParameters::SanityCheck error, in order to compute joint beliefs all joint action observation histories also need to be generated"));
    }
}
