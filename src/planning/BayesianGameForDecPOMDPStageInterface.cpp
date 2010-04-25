/**\file BayesianGameForDecPOMDPStageInterface.cpp
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
 * $Id: BayesianGameForDecPOMDPStageInterface.cpp 3604 2009-08-25 10:52:24Z mtjspaan $
 */

#include "BayesianGameForDecPOMDPStageInterface.h"
#include "PartialJointPolicyDiscretePure.h"
using namespace std;

//Default constructor
BayesianGameForDecPOMDPStageInterface::BayesianGameForDecPOMDPStageInterface(
        const PartialJointPolicyDiscretePure* pastJPol)
    :
        _m_t( pastJPol->GetDepth() )
        ,_m_pJPol(pastJPol)
{
}
BayesianGameForDecPOMDPStageInterface::BayesianGameForDecPOMDPStageInterface(
        Index t)
    :
        _m_t( t )
        ,_m_pJPol(0)
{
}
/*
//Copy constructor.    
BayesianGameForDecPOMDPStageInterface::BayesianGameForDecPOMDPStageInterface(const BayesianGameForDecPOMDPStageInterface& o) 
{
}
//Destructor
BayesianGameForDecPOMDPStageInterface::~BayesianGameForDecPOMDPStageInterface()
{
}
//Copy assignment operator
BayesianGameForDecPOMDPStageInterface& BayesianGameForDecPOMDPStageInterface::operator= (const BayesianGameForDecPOMDPStageInterface& o)
{
    if (this == &o) return *this;   // Gracefully handle self assignment
    // Put the normal assignment duties here...

    return *this;
}
*/



