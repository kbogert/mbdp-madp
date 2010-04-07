/**\file EInvalidIndex.h
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
 * $Id: EInvalidIndex.h 2151 2008-01-21 16:32:52Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _EINVALIDINDEX_H_
#define _EINVALIDINDEX_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"
#include "E.h"

/// EInvalidIndex represents an invalid index exception.
class EInvalidIndex : public E 
{
    private:    
    
    protected:
    
    public:
    // Constructor, destructor and copy assignment.    
    /// Constructor with a C-style string
    EInvalidIndex(const char* arg):E(arg) {}
    /// Constructor with an STL string
    EInvalidIndex(std::string arg):E(arg) {}
    /// Constructor with an STL stringstream
    EInvalidIndex(const std::stringstream& arg) : E(arg) {}

};


#endif /* !_EINVALIDINDEX_H_ */


// Local Variables: ***
// mode:c++ ***
// End: ***
