/**\file PartialJPDPValuePair.h
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
 * $Id: PartialJPDPValuePair.h 3603 2009-08-25 10:38:25Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _PARTIALJPDPVALUEPAIR_H_
#define _PARTIALJPDPVALUEPAIR_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"
#include "PartialJointPolicyValuePair.h"

class PartialJointPolicyDiscretePure;



/**\brief PartialJPDPValuePair represents a (PartialJointPolicyDiscretePure,Value) pair, which
 * stores the full PartialJointPolicyDiscretePure. */
class PartialJPDPValuePair : public PartialJointPolicyValuePair
{
private:    

    PartialJointPolicyDiscretePure* _m_jpol;
    
protected:
    
public:
    // Constructor, destructor and copy assignment.

    PartialJPDPValuePair(PartialJointPolicyDiscretePure* jp, double val);
    PartialJPDPValuePair(PartialJointPolicyDiscretePure& jp, double val);

    /// Destructor.
    ~PartialJPDPValuePair();

    PartialJointPolicyDiscretePure* GetJPol()
        {return(_m_jpol);}

    std::string SoftPrint() const;
    std::string SoftPrintBrief() const;
};


namespace std{
    /**\brief Overload the less<Type> template for JPolValPair* (we want less
     * to give an ordering according to values, not addresses...).*/
    template <> 
    struct less< PartialJPDPValuePair * > //struct, so operator() is public by def. 
    {
        bool operator()(const PartialJPDPValuePair* x, const PartialJPDPValuePair* y) const
        { 
            //cout << "specialized less<PartialJPDPValuePair> called!"<<endl;
            return( x->GetValue() < y->GetValue() );
        }

    };
}


#endif /* !_PARTIALJPDPVALUEPAIR_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
