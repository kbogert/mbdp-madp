/**\file PartialJPDPValuePair.cpp
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
 * $Id: PartialJPDPValuePair.cpp 3603 2009-08-25 10:38:25Z mtjspaan $
 */

#include "PartialJPDPValuePair.h"
#include "PartialJointPolicyDiscretePure.h"

using namespace std;

PartialJPDPValuePair::PartialJPDPValuePair(PartialJointPolicyDiscretePure* jp, double val) :
    PartialJointPolicyValuePair(val)
{
    _m_jpol = jp;
}                

PartialJPDPValuePair::PartialJPDPValuePair(PartialJointPolicyDiscretePure& jp, double val) :
    PartialJointPolicyValuePair(val)
{
    _m_jpol = &jp;
}

PartialJPDPValuePair::~PartialJPDPValuePair()
{
    delete _m_jpol;
}

string PartialJPDPValuePair::SoftPrint() const
{
    stringstream ss;
    ss << "PartialJPDPValuePair: val="<< GetValue() <<", pol:"; 
    ss << _m_jpol->SoftPrint();
    return(ss.str());
}

string PartialJPDPValuePair::SoftPrintBrief() const
{ 
    stringstream ss;
    ss << "PartialJPDPValuePair(" << GetValue() << ","
       << _m_jpol->SoftPrintBrief() << "[d=" << _m_jpol->GetDepth()
       << "])";
    return(ss.str());
}
