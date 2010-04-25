/**\file E.h
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
 * $Id: E.h 2151 2008-01-21 16:32:52Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _E_H_
#define _E_H_ 1

/* the include directives */
#include <iostream>
#include <string>
#include <sstream>

/// E is a class that represents a basic exception.
class E 
{
    private:    
    
    protected:
    
    public:
    
    /// The error message for this particular exception.
    std::string _m_error;

    // Constructor, destructor and copy assignment.

    /// Constructor with a C-style string
    E(const char* arg): _m_error(arg) {}
    /// Constructor with an STL string
    E(std::string arg) : _m_error(arg) {}
    /// Constructor with an STL stringstream
    E(const std::stringstream& arg) : _m_error(arg.str()) {}

    /// Destructor
    virtual ~E(){};

    /// Returns the error message.
    std::string SoftPrint() const {return _m_error;}
    /// Prints the error message to cout.
    void Print() const 
        { std::cout << "ERROR: "<< _m_error << std::endl;} 
};


#endif /* !_E_H_ */


// Local Variables: ***
// mode:c++ ***
// End: ***
