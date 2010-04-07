/**\file MADPParser.h
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
 * $Id: MADPParser.h 3598 2009-08-20 12:29:54Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _MADPPARSER_H_
#define _MADPPARSER_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"

class DecPOMDPDiscrete;
class TOIDecPOMDPDiscrete;
class TOIDecMDPDiscrete;
class TOIFactoredRewardDecPOMDPDiscrete;
class TOICompactRewardDecPOMDPDiscrete;

/// MADPParser is a general class for parsers in MADP.
/** It is templatized to allow for different parsers to be
 * implemented. When constructed with particular model, the proper
 * parser is instantiated, and its Parse() function is called (see
 * ParserInterface).
 */
class MADPParser 
{
private:    

    /// Parse a DecPOMDPDiscrete using ParserDecPOMDPDiscrete.
    void Parse(DecPOMDPDiscrete *model);
    void Parse(TOIDecPOMDPDiscrete *model);
    void Parse(TOIDecMDPDiscrete *model);
    void Parse(TOIFactoredRewardDecPOMDPDiscrete *model);
    void Parse(TOICompactRewardDecPOMDPDiscrete *model);

protected:
    
public:
    // Constructor, destructor and copy assignment.
    /// Constructor, on return the model has been parsed.
    template <class A>
    MADPParser(A* model){ Parse(model); }

    /// Destructor.
    ~MADPParser(){};

};

#endif /* !_MADPPARSER_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
