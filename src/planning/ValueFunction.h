/**\file ValueFunction.h
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
 * $Id: ValueFunction.h 2116 2008-01-16 23:11:49Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _VALUEFUNCTION_H_
#define _VALUEFUNCTION_H_ 1

/* the include directives */
#include <iostream>
#include "PlanningUnit.h"


/** \brief ValueFunction is a class that represents a value function
 * of a joint policy.
 *
 * As the value function also depends on the problem type (DecPOMDP, POSG,etc.)
 * this is an abstract base class.*/
class ValueFunction  
{
    private:    
    
    protected:
    
    public:
    // Constructor, destructor and copy assignment.

    /// Destructor.
    virtual ~ValueFunction(){};

    ///Return a reference to the planning unit.
    virtual PlanningUnit* GetPU() const = 0;
};


#endif /* !_VALUEFUNCTION_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
