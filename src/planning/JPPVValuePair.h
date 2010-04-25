/**\file JPPVValuePair.h
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
 * $Id: JPPVValuePair.h 3603 2009-08-25 10:38:25Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _JPPVVALUEPAIR_H_
#define _JPPVVALUEPAIR_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"
#include "JointPolicyValuePair.h"

class JointPolicyPureVector;
class JointPolicyDiscretePure;


/**\brief JPPVValuePair represents a (JointPolicyPureVector,Value) pair, which
 * stores the full JointPolicyPureVector. */
class JPPVValuePair : public JointPolicyValuePair
{
private:    

    JointPolicyPureVector* _m_jpol;
    
protected:
    
public:
    // Constructor, destructor and copy assignment.

    JPPVValuePair(JointPolicyPureVector* jp, double value);
    JPPVValuePair(JointPolicyPureVector& jp, double value);

    /// Destructor.
    ~JPPVValuePair();

    JointPolicyDiscretePure* GetJPol()
    {
        //we want to inherit from JPolValuePair, but this class is not a real
        //PolicyPoolItem...
        throw E("JPPVValuePair::GetJPol should not be called!");
        return(0);
    }
    JointPolicyPureVector* GetJPPV()
        {return(_m_jpol);}

    std::string SoftPrint() const;
    std::string SoftPrintBrief() const;
};


namespace std{
    /**\brief Overload the less<Type> template for JPolValuePair* (we want less
     * to give an ordering according to values, not addresses...).*/
    template <> 
    struct less< JPPVValuePair * > //struct, so operator() is public by def. 
    {
        bool operator()(const JPPVValuePair* x, const JPPVValuePair* y) const
        { 
            //cout << "specialized less<JPPVValuePair> called!"<<endl;
            return( x->GetValue() < y->GetValue() );
        }

    };
}


#endif /* !_JPPVVALUEPAIR_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
