/**\file Type_AOHIndex.h
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
 * $Id: Type_AOHIndex.h 3598 2009-08-20 12:29:54Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _TYPE_AOHINDEX_H_
#define _TYPE_AOHINDEX_H_ 1

/* the include directives */
#include "Globals.h"
#include "Type.h"

/** \brief Type_AOHIndex  is a implementation (extenstion) of Type and 
 * represents a type in e.g. a BG.
 * 
 * In particular this implementation of Type is a wrapper for an individual
 * action-observation history.
 **/
class Type_AOHIndex : public Type
{
    private:    
        Index _m_aohI;
        
    protected:
    
    public:
        
        // Constructor, destructor and copy assignment.
        /// (default) Constructor
        Type_AOHIndex(Index aohI) :
            Type(AOHINDEX)
            , _m_aohI(aohI) 
        {};
        /// Copy constructor.
        Type_AOHIndex(const Type_AOHIndex& a) : 
            Type(a)
            ,_m_aohI(a._m_aohI) 
        {};
        /// Destructor.
        virtual ~Type_AOHIndex(){};
        /// Copy assignment operator
        Type_AOHIndex& operator= (const Type_AOHIndex& o);
        Type* Clone() const;

        //operators:

        //data manipulation (set) functions:
        
        //get (data) functions:
        Index GetAOHIndex() const
        {return _m_aohI; };
        
        std::string SoftPrint() const;
};


#endif /* !_TYPE_AOHINDEX_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
