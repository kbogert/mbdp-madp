/**\file PartialPolicyPoolItemInterface.h
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
 * $Id: PartialPolicyPoolItemInterface.h 3604 2009-08-25 10:52:24Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _PARTIALPOLICYPOOLITEMINTERFACE_H_
#define _PARTIALPOLICYPOOLITEMINTERFACE_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"

class PartialJointPolicyDiscretePure;

/**\brief PartialPolicyPoolItemInterface is a class that gives the
 * interface for a PolicyPoolItem. A PolicyPoolItem is a wrapper for a
 * partial joint policy (together with some properties) when placed in
 * a PolicyPool.
 *
 **/
class PartialPolicyPoolItemInterface 
{
    private:    
    
    protected:
    
    public:
        // Constructor, destructor and copy assignment.
        /// (default) Constructor
        //PartialPolicyPoolItemInterface();
        /// Copy constructor.
        //PartialPolicyPoolItemInterface(const PartialPolicyPoolItemInterface& a);
        /// Destructor.
        virtual ~PartialPolicyPoolItemInterface()
        {};
        /// Copy assignment operator
        //PartialPolicyPoolItemInterface& operator= (const PartialPolicyPoolItemInterface& o);

        //operators:

        //data manipulation (set) functions:
        
        //get (data) functions:
        //
        /**\brief Returns a pointer to the wrapped (partial) joint policy*/
        virtual PartialJointPolicyDiscretePure* GetJPol() = 0;
        /**\brief Returns the heuristic value.*/
        virtual double GetValue() const=0;
        /**Softprint the PartialPolicyPoolItemInterface*/
        virtual std::string SoftPrint() const = 0;
        /**Softprint the PartialPolicyPoolItemInterface in brief*/
        virtual std::string SoftPrintBrief() const = 0;
        /**Prints a description to stdout.*/
        void Print() const 
        {std::cout << SoftPrint();}
        /**Prints a brief description to stdout.*/
        void PrintBrief() const 
        {std::cout << SoftPrint();}
};


#endif /* !_PARTIALPOLICYPOOLITEMINTERFACE_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
