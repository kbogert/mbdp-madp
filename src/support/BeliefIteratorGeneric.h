/**\file BeliefIteratorGeneric.h
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
 * $Id: BeliefIteratorGeneric.h 3604 2009-08-25 10:52:24Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _BELIEFITERATORGENERIC_H_
#define _BELIEFITERATORGENERIC_H_ 1

/* the include directives */
#include "Globals.h"
#include "BeliefIteratorInterface.h"

#define USE_BeliefIteratorGeneric 1

/** \brief BeliefIteratorGeneric is an iterator for beliefs.
 */
class BeliefIteratorGeneric
{
private:    

    BeliefIteratorInterface* _m_it;
    
protected:
    
public:
    // Constructor, destructor and copy assignment.
    /// (default) Constructor
    BeliefIteratorGeneric(BeliefIteratorInterface *it) :
        _m_it(it)
        {}

    /// Destructor.
    virtual ~BeliefIteratorGeneric()
        {
            delete(_m_it);
        }

    double GetProbability() const { return(_m_it->GetProbability()); }
    Index GetStateIndex() const { return(_m_it->GetStateIndex()); }
    bool Next() const { return(_m_it->Next()); }

};


#endif /* !_BELIEFITERATORGENERIC_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
