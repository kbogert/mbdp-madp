/**\file ParserInterface.h
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
 * $Id: ParserInterface.h 2945 2008-10-25 11:14:45Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _PARSERINTERFACE_H_
#define _PARSERINTERFACE_H_ 1

/* the include directives */
#include <iostream>

/// ParserInterface is an interface for parsers.
class ParserInterface 
{
private:
    
protected:
    
public:
    // Constructor, destructor and copy assignment.
    /// (default) Constructor
    ParserInterface(){};

    virtual ~ParserInterface(){};
    
    virtual void Parse() = 0;

};


#endif /* !_PARSERINTERFACE_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
