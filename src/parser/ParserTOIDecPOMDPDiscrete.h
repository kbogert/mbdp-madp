/**\file ParserTOIDecPOMDPDiscrete.h
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
 * $Id: ParserTOIDecPOMDPDiscrete.h 3603 2009-08-25 10:38:25Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _PARSERTOIDECPOMDPDISCRETE_H_
#define _PARSERTOIDECPOMDPDISCRETE_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"

#include "TOIDecPOMDPDiscrete.h"
#include "DecPOMDPDiscrete.h"
#include "ParserInterface.h"



/**\brief ParserTOIDecPOMDPDiscrete is a parser for
 * TOIDecPOMDPDiscrete. */
class ParserTOIDecPOMDPDiscrete :
    public ParserInterface
{
private:    
    
    TOIDecPOMDPDiscrete *_m_problem;

    void ParseBase();
    void ParseAgent(Index id);

    virtual void StoreDecPOMDP(DecPOMDPDiscrete *decpomdp,
                               Index id);

protected:

    void ParseRewards(size_t nrAgents,
                      const std::vector<size_t> &nrStates,
                      const std::vector<size_t> &nrActions);
    virtual void ParseRewards();
    
public:
    // Constructor, destructor and copy assignment.
    /// (default) Constructor
    ParserTOIDecPOMDPDiscrete(TOIDecPOMDPDiscrete
                              *problem);

    virtual ~ParserTOIDecPOMDPDiscrete(){};

    void Parse();

};


#endif /* !_PARSERTOIDECPOMDPDISCRETE_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
