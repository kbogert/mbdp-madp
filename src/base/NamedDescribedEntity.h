/**\file NamedDescribedEntity.h
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
 * $Id: NamedDescribedEntity.h 2151 2008-01-21 16:32:52Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _NAMED_DESCRIBED_ENTITY_H_
#define _NAMED_DESCRIBED_ENTITY_H_ 1

/* the include directives */
#include <iostream>
#include <string>
#include "Globals.h"

/// NamedDescribedEntity represents named entities.
/** For example actions and observations in a decision process.  */
class NamedDescribedEntity
{
    private:
    
    protected:
    /// Pointer to the name.
    std::string* _m_name;
    /// Pointer to the description.
    std::string* _m_description;
    
    public:
    // Constructor, destructor and copy assignment.
    /// (default) Constructor
    NamedDescribedEntity(std::string name=std::string("undefined"), std::string \
        description=std::string("undefined"));
    /// copy constructor.
    NamedDescribedEntity(const NamedDescribedEntity&);
    /// Destructor.
    virtual ~NamedDescribedEntity();
    // 'get' functions:
    /// Get the name of the NamedDescribedEntity
    std::string GetName() const {return *_m_name;};
    /// Get the description of the NamedDescribedEntity
    std::string GetDescription() const {return *_m_description;};

    /// Set the name.
    void SetName(std::string name){
        *_m_name=name;
    }

    /// Set the description.
    void SetDescription(std::string description){
        *_m_description=description;
    }

    /// Returns the name and description (if not reimplemented).
    virtual std::string SoftPrint() const;
    /// Returns the name (if not reimplemented).
    virtual std::string SoftPrintBrief() const;
    /// Prints the name and description (by default).
    void Print() const {std::cout << SoftPrint();}
    /// Prints the name (by default).
    void PrintBrief() const {std::cout << SoftPrintBrief(); }
};

#endif /* !_NAMED_DESCRIBED_ENTITY_H_ */


// Local Variables: ***
// mode:c++ ***
// End: ***
