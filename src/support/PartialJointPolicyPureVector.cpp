/**\file PartialJointPolicyPureVector.cpp
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
 * $Id: PartialJointPolicyPureVector.cpp 3611 2009-08-25 15:02:24Z mtjspaan $
 */

#include "PartialJointPolicyPureVector.h"
#include "JointPolicyPureVector.h"

using namespace std;

PartialJointPolicyPureVector::PartialJointPolicyPureVector(
    const Interface_ProblemToPolicyDiscretePure& pu,
    PolicyGlobals::IndexDomainCategory idc,
    double pastReward,
    size_t depth) :
    PartialJointPolicyDiscretePure(pu, idc, pastReward),
    JPolComponent_VectorImplementation(pu, idc, depth)
{
    SetDepth(depth);
}

//Copy assignment operator
PartialJointPolicyPureVector& PartialJointPolicyPureVector::operator= (const PartialJointPolicyPureVector& o)
{
    if (this == &o) return *this;   // Gracefully handle self assignment
    // Put the normal assignment duties here...
    PartialJointPolicyDiscretePure::operator=(o);
    JPolComponent_VectorImplementation::operator=(o);
    return *this;
}
PartialJointPolicyPureVector& PartialJointPolicyPureVector::operator= (const 
        PartialJointPolicyDiscretePure& o)
{
    if (this == &o) return *this;   // Gracefully handle self assignment
    const PartialJointPolicyPureVector& p = 
        dynamic_cast<const PartialJointPolicyPureVector&>( o );
    return operator=(p);

}


string PartialJointPolicyPureVector::SoftPrint() const
{
    stringstream ss; 
    ss << "PartialJointPolicyPureVector, past reward="<<GetPastReward()<<endl;
    ss << JPolComponent_VectorImplementation::SoftPrint();
    return ss.str();
}

string PartialJointPolicyPureVector::SoftPrintBrief() const
{
    stringstream ss; 
    ss << "PartialJPPV, past R="<<GetPastReward()<<", ";
    ss << JPolComponent_VectorImplementation::SoftPrintBrief();
    return ss.str();
}

JointPolicyPureVector* PartialJointPolicyPureVector::ToJointPolicyPureVector() const
{ 
    return new JointPolicyPureVector(*this, *this);
}
