/**\file ParserTOIFactoredRewardDecPOMDPDiscrete.h
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
 * $Id: ParserTOIFactoredRewardDecPOMDPDiscrete.h 3603 2009-08-25 10:38:25Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _PARSERTOIFACTOREDREWARDDECPOMDPDISCRETE_H_
#define _PARSERTOIFACTOREDREWARDDECPOMDPDISCRETE_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"

#include "TOIFactoredRewardDecPOMDPDiscrete.h"
#include "ParserTOIDecPOMDPDiscrete.h"
#include "DecPOMDPDiscrete.h"



/**\brief ParserTOIFactoredRewardDecPOMDPDiscrete is a parser for
 * TransitionObservationIndependentFactoredRewardDecPOMDPDiscrete. */
class ParserTOIFactoredRewardDecPOMDPDiscrete :
    public ParserTOIDecPOMDPDiscrete
{
private:    
    
    TOIFactoredRewardDecPOMDPDiscrete *_m_problem;

    void StoreDecPOMDP(DecPOMDPDiscrete *decpomdp,
                       Index id);

protected:
    
public:
    // Constructor, destructor and copy assignment.
    /// (default) Constructor
    ParserTOIFactoredRewardDecPOMDPDiscrete(
        TOIFactoredRewardDecPOMDPDiscrete
        *problem);

};


#endif /* !_PARSERTOIFACTOREDREWARDDECPOMDPDISCRETE_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
