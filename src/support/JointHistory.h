/**\file JointHistory.h
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
 * $Id: JointHistory.h 2116 2008-01-16 23:11:49Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _JOINTHISTORY_H_
#define _JOINTHISTORY_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"
#include "History.h"

///JointHistory represents a joint history, i.e., a history for each agent.
class JointHistory : public History
{
private:    
    
protected:
    
public:
    // Constructor, destructor and copy assignment.
    /// (default) Constructor
    JointHistory(){};
    /// Destructor.
    virtual ~JointHistory(){};

};


#endif /* !_JOINTHISTORY_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
