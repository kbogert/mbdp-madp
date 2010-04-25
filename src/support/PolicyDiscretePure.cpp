/**\file PolicyDiscretePure.cpp
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
 * $Id: PolicyDiscretePure.cpp 3598 2009-08-20 12:29:54Z mtjspaan $
 */

#include "PolicyDiscretePure.h"

//Default constructor
PolicyDiscretePure::PolicyDiscretePure(
        const Interface_ProblemToPolicyDiscretePure& pu,
        PolicyGlobals::IndexDomainCategory idc,
        Index agentI ) :
    PolicyDiscrete( pu , idc, agentI )
{
}

//Copy constructor.    
PolicyDiscretePure::PolicyDiscretePure(const 
        PolicyDiscretePure& o) 
    :
    PolicyDiscrete( o )
{
}

double PolicyDiscretePure::GetActionProb(Index i, Index aI ) const
{
    if(GetActionIndex(i) == aI)
        return(1.0);

    return(0.0);
}
