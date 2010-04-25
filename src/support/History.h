/**\file History.h
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
 * $Id: History.h 4016 2010-03-11 16:56:02Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _HISTORY_H_
#define _HISTORY_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"

///History is a general class for histories.
class History 
{
private:    
    
protected:
    
    /// How long (how many time-steps) is this history?
    /** For example, history at... 
     * ts 0 - length 0 (received no action yet... )
     * ts 1 - length 1 (hist= (a0) )
     * ts 2 - length 2 (hist= (a0,a1) ) */
    size_t _m_length;
    
public:
    // Constructor, destructor and copy assignment.
    /// (default) Constructor
    History(){};
    /// Destructor.
    virtual ~History(){};
    
    /// Returns the length of the history, i.e., the number of time steps.
    size_t GetLength() const
        {
            return(_m_length);
        }

    ///Set the length of the history, i.e., the number of time steps.
    void SetLength(size_t length)
        {
            _m_length=length;
        }
    
    /// Returns a pointer to a copy of this class.
    virtual History* Clone() const = 0;

    virtual void Print() const = 0;
};


#endif /* !_HISTORY_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
