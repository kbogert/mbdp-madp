/**\file Type_AOHIndex.cpp
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
 * $Id: Type_AOHIndex.cpp 2962 2008-11-02 15:04:43Z mtjspaan $
 */

#include "Type_AOHIndex.h"

using namespace std;

/*
//Default constructor
Type_AOHIndex::Type_AOHIndex()
{
}
//Copy constructor.    
Type_AOHIndex::Type_AOHIndex(const Type_AOHIndex& o) 
{
}
//Destructor
Type_AOHIndex::~Type_AOHIndex()
{
}
*/
//Copy assignment operator
Type_AOHIndex& Type_AOHIndex::operator= (const Type_AOHIndex& o)
{
    if (this == &o) return *this;   // Gracefully handle self assignment
    // Put the normal assignment duties here...
    _m_aohI = o._m_aohI;
    //call base class
    Type::operator=(o);

    return *this;
}


Type* Type_AOHIndex::Clone() const
{
    Type_AOHIndex* t = new Type_AOHIndex(*this);
    return (Type*) t;
}

string Type_AOHIndex::SoftPrint() const
{
    stringstream ss;
    ss << "aoh"<<_m_aohI;
    return(ss.str());
}
