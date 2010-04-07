/**\file DiscreteEntity.h
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
 * $Id: DiscreteEntity.h 2116 2008-01-16 23:11:49Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _DISCRETEENTITY_H_
#define _DISCRETEENTITY_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"

/// DiscreteEntity is a general class for tracking discrete entities.
/**DiscreteEntity represents entities in discrete spaces, that hence
 * can be represented by an index. For example, actions in a finite
 * action space. */
class DiscreteEntity 
{
private:
    
protected:

    /// The index of this discrete entity.
    Index _m_index;

public:
    // Constructor, destructor and copy assignment.
    /// (default) Constructor
    DiscreteEntity(Index i) : _m_index(i){}

    /// Destructor.
    virtual ~DiscreteEntity(){}

    /// Return this DiscreteEntity's index.
    Index GetIndex() const { return(_m_index); }

    /// Set this DiscreteEntity's index.
    void SetIndex(Index i) { _m_index=i; }

    /// The less (<) operator. This is needed to put DiscreteEntities in a set.
    bool operator< (const DiscreteEntity& a) const {
        return( _m_index < a._m_index );}

};


#endif /* !_DISCRETEENTITY_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
