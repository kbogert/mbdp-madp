/**\file StateDiscrete.h
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
 * $Id: StateDiscrete.h 2151 2008-01-21 16:32:52Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _STATEDISCRETE_H_
#define _STATEDISCRETE_H_ 1

/* the include directives */
#include <iostream>
#include <string>
#include "Globals.h"

#include "State.h"
#include "DiscreteEntity.h"


/// StateDiscrete represents discrete states.
/** 
 * StateDiscrete is a class that represent states in a discrete state
 * set, which are identified by their index.  */
class StateDiscrete : public State,
                      public DiscreteEntity
{
private:    
    
protected:
    
public:
    // Constructor, destructor and copy assignment.
    /// (default) Constructor
    StateDiscrete(Index i , std::string name=std::string("undefined"),
                  std::string description=std::string("undefined")) :
        State(name, description),
        DiscreteEntity(i){};

};

#endif /* !_STATEDISCRETE_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
