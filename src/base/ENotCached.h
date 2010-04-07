/**\file ENotCached.h
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
 * $Id: ENotCached.h 3604 2009-08-25 10:52:24Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _ENOTCACHED_H_
#define _ENOTCACHED_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"
#include "E.h"

/// ENotCached represents an invalid index exception.
class ENotCached : public E 
{
    private:    
    
    protected:
    
    public:
    // Constructor, destructor and copy assignment.    
    /// Constructor with a C-style string
    ENotCached(const char* arg):E(arg) {}
    /// Constructor with an STL string
    ENotCached(std::string arg):E(arg) {}
    /// Constructor with an STL stringstream
    ENotCached(const std::stringstream& arg) : E(arg) {}

};


#endif /* !_ENOTCACHED_H_ */


// Local Variables: ***
// mode:c++ ***
// End: ***
