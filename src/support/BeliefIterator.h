/**\file BeliefIterator.h
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
 * $Id: BeliefIterator.h 4016 2010-03-11 16:56:02Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _BELIEFITERATOR_H_
#define _BELIEFITERATOR_H_ 1

/* the include directives */
#include "Globals.h"
#include "BeliefIteratorInterface.h"
#include "Belief.h"

/** \brief BeliefIterator is an iterator for dense beliefs. */
class BeliefIterator : public BeliefIteratorInterface
{
private:    

    Index _m_i;
    const Belief *_m_belief;

protected:
    
public:

    // Constructor, destructor and copy assignment.
    /// (default) Constructor
    BeliefIterator(const Belief *b) : _m_i(0), _m_belief(b){}

    /// Destructor.
    virtual ~BeliefIterator(){}

    double GetProbability() const { return(_m_belief->_m_b[_m_i]); }
    Index GetStateIndex() const { return(_m_i); }
    bool Next()
        {
            if(_m_i>=(_m_belief->_m_b.size()-1))
                return(false);
            else
            {
                _m_i++;
                return(true);
            }
        }

    /// Returns a pointer to a copy of this class.
    virtual BeliefIterator* Clone() const
        { return new BeliefIterator(*this); }

};


#endif /* !_BELIEFITERATOR_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
