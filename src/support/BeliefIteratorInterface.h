/**\file BeliefIteratorInterface.h
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
 * $Id: BeliefIteratorInterface.h 4016 2010-03-11 16:56:02Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _BELIEFITERATORINTERFACE_H_
#define _BELIEFITERATORINTERFACE_H_ 1

/* the include directives */
#include "Globals.h"

/** \brief BeliefIteratorInterface is an interface for iterators over
 * beliefs. */
class BeliefIteratorInterface 
{
private:    
    
protected:
    
public:
    // Constructor, destructor and copy assignment.
    /// (default) Constructor
    BeliefIteratorInterface(){};

    /// Destructor.
    virtual ~BeliefIteratorInterface(){};

    /// Gets the probability at the current state.
    virtual double GetProbability() const = 0;
    /// Gets the index of the current state.
    virtual Index GetStateIndex() const = 0;
    /// Advance the iterator. Returns false if at the end.
    virtual bool Next() = 0;

    /// Returns a pointer to a copy of this class.
    virtual BeliefIteratorInterface* Clone() const = 0;

};


#endif /* !_BELIEFITERATORINTERFACE_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
