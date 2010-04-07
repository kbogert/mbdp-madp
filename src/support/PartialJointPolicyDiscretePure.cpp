/**\file PartialJointPolicyDiscretePure.cpp
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
 * $Id: PartialJointPolicyDiscretePure.cpp 3603 2009-08-25 10:38:25Z mtjspaan $
 */

#include "PartialJointPolicyDiscretePure.h"

using namespace std;

//Copy assignment operator
PartialJointPolicyDiscretePure& PartialJointPolicyDiscretePure::operator= (const PartialJointPolicyDiscretePure& o)
{
    if (this == &o) return *this;   // Gracefully handle self assignment
    // Put the normal assignment duties here...
    JointPolicyDiscretePure::operator= ( o );
    PartialJointPolicy::operator= ( o );

    return *this;
}
