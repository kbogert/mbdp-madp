/**\file Type.h
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
 * $Id: Type.h 2962 2008-11-02 15:04:43Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _TYPE_H_
#define _TYPE_H_ 1

/* the include directives */
#include "Globals.h"

/** \brief Type is an abstract class that represents a Type (e.g. for a 
 * Bayesian game). 
 *
 * So far Type_PointerTuple and Type_AOHIndex extend this class.
 **/
class Type 
{
    public:
        enum SubClass {UNDEFINED, AOHINDEX, POINTERTUPLE};
    private:    

    protected:
        SubClass _m_sc;
    
    public:
        // Constructor, destructor and copy assignment.
        /// (default) Constructor

        Type(SubClass s=AOHINDEX)
            : _m_sc(s) {};
        /// Destructor.
        virtual ~Type() {};
        /// Copy constructor.        
        Type(const Type& a)
            : _m_sc(a._m_sc) {};

        /// Copy assignment operator
        Type& operator= (const Type& o)
        {
            if (this == &o) return *this;   // Gracefully handle self assignment
            // Put the normal assignment duties here...
            _m_sc = o._m_sc;
            return *this;
        }



        virtual Type* Clone() const=0;
        //operators:

        //data manipulation (set) functions:
        
        //get (data) functions:
        SubClass GetSubClass() const
        {return _m_sc;};
        virtual std::string SoftPrint () const = 0;
};


#endif /* !_TYPE_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
