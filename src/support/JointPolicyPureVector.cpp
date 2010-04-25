/**\file JointPolicyPureVector.cpp
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
 * $Id: JointPolicyPureVector.cpp 3611 2009-08-25 15:02:24Z mtjspaan $
 */

#include "JointPolicyPureVector.h"
#include "IndexTools.h"

using namespace std;

#define DEBUG_JPPT 0 
#define DEBUG_JPPT_GETJA_LOCAL 0

//TODO: check this code
JointPolicyPureVector& JointPolicyPureVector::operator= (const JointPolicyPureVector& o)
{
#if DEBUG_JPOLASSIGN 
    cout << "JointPolicyPureVector::operator=(const JointPolicyPureVector& jp) called"<<endl;
#endif
    if (this == &o) return *this;  // Gracefully handle self assignment
    // Put the normal assignment duties here...
    JointPolicyDiscretePure::operator=(o);
    JPolComponent_VectorImplementation::operator=(o);
    return *this;
}

JointPolicyPureVector& JointPolicyPureVector::operator= (const JointPolicyDiscretePure& o)
{
#if DEBUG_JPOLASSIGN 
    cerr << "JointPolicyPureVector::operator=(const JointPolicyDiscretePure& jp) called"<<endl;
#endif
    if (this == &o) return *this;   // Gracefully handle self assignment
    const JointPolicyPureVector& p = 
        dynamic_cast<const JointPolicyPureVector&>( o );
    return operator=(p);
}


string JointPolicyPureVector::SoftPrint(void) const
{
    stringstream ss;
    ss << "JointPolicyPureVector: " <<endl;
    ss << JPolComponent_VectorImplementation::SoftPrint();
    return(ss.str());
} 

string JointPolicyPureVector::SoftPrintBrief(void) const
{
    stringstream ss; 
    ss << "JPPV: ";
    ss << JPolComponent_VectorImplementation::SoftPrintBrief();
    return ss.str();
}
        

JointPolicyPureVector* JointPolicyPureVector::ToJointPolicyPureVector() const
{ 
    return new JointPolicyPureVector(*this);
}
