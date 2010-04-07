/**\file JPPVIndexValuePair.cpp
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
 * $Id: JPPVIndexValuePair.cpp 3603 2009-08-25 10:38:25Z mtjspaan $
 */

#include "JPPVIndexValuePair.h"
#include "JointPolicyPureVector.h"

using namespace std;

JPPVIndexValuePair::JPPVIndexValuePair(JointPolicyPureVector* jp,
                                       double value) :
    JointPolicyValuePair(value)
{
    _m_jpol=0;
    _m_jpolIndex=jp->GetIndex();
    _m_jpolDepth=jp->GetDepth();
    _m_pu=jp->GetInterfacePTPDiscretePure();
}                

JPPVIndexValuePair::JPPVIndexValuePair(const JointPolicyPureVector& jp,
                                       double value) :
    JointPolicyValuePair(value)
{
    _m_jpol=0;
    _m_jpolIndex=jp.GetIndex();
    _m_jpolDepth=jp.GetDepth();
    _m_pu=jp.GetInterfacePTPDiscretePure();
}

JPPVIndexValuePair::~JPPVIndexValuePair()
{
    delete _m_jpol;
}

JointPolicyDiscretePure* JPPVIndexValuePair::GetJPol()
{ return GetJPPV(); }

JointPolicyPureVector* JPPVIndexValuePair::GetJPPV()
{
    if(_m_jpol==0)
        AllocateJPPV();

    return(_m_jpol);
}

void JPPVIndexValuePair::AllocateJPPV()
{
    if(_m_jpol==0) // not yet instantiated, do it now
    {
        _m_jpol=new JointPolicyPureVector(*_m_pu);
        _m_jpol->SetDepth(_m_jpolDepth);
        _m_jpol->SetIndex(_m_jpolIndex);
    }
}

string JPPVIndexValuePair::SoftPrint() const
{
    stringstream ss;
    ss << "JPPVIndexValuePair: value="<< GetValue() <<", jpolIndex:"; 
    ss << _m_jpolIndex;
    return(ss.str());
}

string JPPVIndexValuePair::SoftPrintBrief() const
{ 
    stringstream ss;
    ss << "JPPVIndexValuePair(" << GetValue() << ","
       << _m_jpolIndex << ")";
    return(ss.str());
}
