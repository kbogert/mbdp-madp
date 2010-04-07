/**\file PolicyPoolItemInterface.h
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
 * $Id: PolicyPoolItemInterface.h 3603 2009-08-25 10:38:25Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _POLICYPOOLITEMINTERFACE_H_
#define _POLICYPOOLITEMINTERFACE_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"

class JointPolicyDiscretePure;

/**\brief PolicyPoolItemInterface is a class that gives the interface for a 
 * PolicyPoolItem. A PolicyPoolItem is a wrapper for a partial
 * joint policy (together with some properties) when placed in a PolicyPool.
 *
 **/
class PolicyPoolItemInterface 
{
    private:    
    
    protected:
    
    public:
        // Constructor, destructor and copy assignment.
        /// (default) Constructor
        //PolicyPoolItemInterface();
        /// Copy constructor.
        //PolicyPoolItemInterface(const PolicyPoolItemInterface& a);
        /// Destructor.
        virtual ~PolicyPoolItemInterface()
        {};
        /// Copy assignment operator
        //PolicyPoolItemInterface& operator= (const PolicyPoolItemInterface& o);

        //operators:

        //data manipulation (set) functions:
        
        //get (data) functions:
        //
        /**\brief Returns a pointer to the wrapped (partial) joint policy*/
        virtual JointPolicyDiscretePure* GetJPol() = 0;
        /**\brief Returns the heuristic value.*/
        virtual double GetValue() const=0;
        /**Softprint the PolicyPoolItemInterface*/
        virtual std::string SoftPrint() const = 0;
        /**Softprint the PolicyPoolItemInterface in brief*/
        virtual std::string SoftPrintBrief() const = 0;
        /**Prints a description to stdout.*/
        void Print() const 
        {std::cout << SoftPrint();}
        /**Prints a brief description to stdout.*/
        void PrintBrief() const 
        {std::cout << SoftPrint();}
};


#endif /* !_POLICYPOOLITEMINTERFACE_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
