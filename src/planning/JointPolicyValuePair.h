/**\file JointPolicyValuePair.h
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
 * $Id: JointPolicyValuePair.h 3603 2009-08-25 10:38:25Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _JOINTPOLICYVALUEPAIR_H_
#define _JOINTPOLICYVALUEPAIR_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"
#include "PolicyPoolItemInterface.h"

/**\brief JointPolicyValuePair is a wrapper for a partial joint policy
 * and its heuristic value.
 *
 * JointPolicyValuePair is a class that represents a (joint
 * *policy,value) pair the operator less is defined for these pairs so
 * *they can be but in ordered containers.
 *
 * JointPolicyValuePair is a PolicyPoolItem (i.e., it implements
 * PolicyPoolItemInterface)
 */
class JointPolicyValuePair 
    : public PolicyPoolItemInterface                    
{   
    private:
        double _m_val;

    protected:
    public:
        /// (default) Constructor
        JointPolicyValuePair(double val)
        {
            _m_val = val;
        }                

        /// Destructor.
        ~JointPolicyValuePair(){};

        /// Copy assignment operator
        JointPolicyValuePair& operator= (const JointPolicyValuePair& o)
        {
            throw E("Assigning JointPolicyValuePair - but operator= not def'd");
        }

        double GetValue() const
            {return(_m_val);}   

};

namespace std{
    /**\brief Overload the less<Type> template for JointPolicyValuePair* (we want less
     * to give an ordering according to values, not addresses...).*/
    template <> 
    struct less< JointPolicyValuePair* > //struct, so operator() is public by def. 
    {
        bool operator()(const JointPolicyValuePair* x, const JointPolicyValuePair* y) const
        { 
            //cout << "specialized less<JointPolicyValuePair> called!"<<endl;
            return( x->GetValue() < y->GetValue() );
        }

    };
}

#endif /* !_JPOLVALPAIR_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
