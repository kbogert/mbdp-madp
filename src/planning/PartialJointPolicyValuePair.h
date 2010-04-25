/**\file PartialJointPolicyValuePair.h
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
 * $Id: PartialJointPolicyValuePair.h 3604 2009-08-25 10:52:24Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _PARTIALJOINTPOLICYVALUEPAIR_H_
#define _PARTIALJOINTPOLICYVALUEPAIR_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"
#include "JointPolicyPureVector.h"
#include "PartialPolicyPoolItemInterface.h"



/**\brief PartialJointPolicyValuePair is a wrapper for a partial joint
 *policy and its heuristic value.
 *
 *PartialJointPolicyValuePair is a class that represents a (joint policy,value) pair
 * the operator less is defined for these pairs so they can be but in ordered
 * containers. 
 *
 *PartialJointPolicyValuePair is a PolicyPoolItem (i.e., it implements PartialPolicyPoolItemInterface)
 * */
class PartialJointPolicyValuePair : public PartialPolicyPoolItemInterface                    
{   
    private:
        double _m_val;

    protected:
    public:
        /// (default) Constructor
        PartialJointPolicyValuePair(double val)
        {
            _m_val = val;
        }                

        /// Destructor.
        ~PartialJointPolicyValuePair(){};

        /// Copy assignment operator
        PartialJointPolicyValuePair& operator= (const PartialJointPolicyValuePair& o)
        {
            throw E("Assigning PartialJointPolicyValuePair - but operator= not def'd");
        }

        double GetValue() const
            {return(_m_val);}   

};

namespace std{
    /**Overload the less<Type> template for PartialJointPolicyValuePair* (we want less
     * to give an ordering according to values, not addresses...).*/
    template <> 
    struct less< PartialJointPolicyValuePair* > //struct, so operator() is public by def. 
    {
        bool operator()(const PartialJointPolicyValuePair* x, const PartialJointPolicyValuePair* y) const
        { 
            //cout << "specialized less<PartialJointPolicyValuePair> called!"<<endl;
            return( x->GetValue() < y->GetValue() );
        }

    };
}

#endif /* !_PARTIALJPOLVALPAIR_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
