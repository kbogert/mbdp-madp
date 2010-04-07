/**\file IndividualHistory.h
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
 * $Id: IndividualHistory.h 2116 2008-01-16 23:11:49Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _INDIVIDUALHISTORY_H_
#define _INDIVIDUALHISTORY_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"

#include "History.h"

///IndividualHistory represents a history for a single agent.
class IndividualHistory : public History
{
private:    
    
protected:
    
    ///The agent this history belongs to.
    Index _m_agentI;
    
public:
    // Constructor, destructor and copy assignment.
    /// (default) Constructor
    IndividualHistory(Index agentI) : _m_agentI(agentI){};
    /// Destructor.
    virtual ~IndividualHistory(){};
    
};


#endif /* !_INDIVIDUALHISTORY_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
