/**\file PartialJointPolicyDiscretePure.h
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
 * $Id: PartialJointPolicyDiscretePure.h 3603 2009-08-25 10:38:25Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _PARTIALJOINTPOLICYDISCRETEPURE_H_
#define _PARTIALJOINTPOLICYDISCRETEPURE_H_ 1

/* the include directives */
#include "Globals.h"
#include "JointPolicyDiscretePure.h"
#include "PartialJointPolicy.h"

/** \brief PartialJointPolicyDiscretePure is a discrete and pure
 * PartialJointPolicy.  */
class PartialJointPolicyDiscretePure :
    //virtual <- this leads to pain in the ass...
    public JointPolicyDiscretePure
    , public PartialJointPolicy
{
    private:    
    
    protected:
    
    public:
        // Constructor, destructor and copy assignment.
        /// (default) Constructor
        PartialJointPolicyDiscretePure()
        {};
        PartialJointPolicyDiscretePure(
                const Interface_ProblemToPolicyDiscretePure& pu,
                PolicyGlobals::IndexDomainCategory idc,
                double pastReward = 0.0
                )
            : JointPolicyDiscretePure(pu, idc)
              ,PartialJointPolicy(pastReward)
        {};
        /// Copy constructor.
        PartialJointPolicyDiscretePure(const PartialJointPolicyDiscretePure& a)
            : 
                JointPolicyDiscretePure(a)
                , PartialJointPolicy(a)
        {};
        /// Destructor.
        //~PartialJointPolicyDiscretePure();
        /// Copy assignment operator
        virtual PartialJointPolicyDiscretePure& operator= 
                (const PartialJointPolicyDiscretePure& o);
        //operators:

        //data manipulation (set) functions:
        
        //get (data) functions:
};


#endif /* !_PARTIALJOINTPOLICYDISCRETEPURE_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
