/**\file PolicyDiscretePure.h
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
 * $Id: PolicyDiscretePure.h 4016 2010-03-11 16:56:02Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _POLICYDISCRETEPURE_H_
#define _POLICYDISCRETEPURE_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"
#include "Interface_ProblemToPolicyDiscretePure.h"
#include "PolicyDiscrete.h"

/** \brief PolicyDiscretePure is an abstract class that represents a
 * pure  policy for a discrete MADP.
 *
 * The number of pure  policies as represented by this class is finite.
 * Therefore it is possible
 * */
class PolicyDiscretePure : public PolicyDiscrete
{
    private:    
    
    protected:
    
    public:
        // Constructor, destructor and copy assignment.
        /// (default) Constructor
        PolicyDiscretePure(
                const Interface_ProblemToPolicyDiscretePure& pu,
                PolicyGlobals::IndexDomainCategory idc,
                Index agentI
               );
        /// Copy constructor.
        PolicyDiscretePure(const PolicyDiscretePure& a);
        /// Destructor.
        virtual ~PolicyDiscretePure()
        {}

        //operators:

        //data manipulation (set) functions:        
        
        /// Randomly initialize the  policy.
        //virtual void RandomInitialization() = 0;
        /// Randomly initialize the policy for agentI.
        virtual void RandomInitialization(Index agentI) = 0;
        
        //get (data) functions:

        /// Return pointer to the Interface_ProblemToPolicyDiscretePure.
        const Interface_ProblemToPolicyDiscretePure* 
            GetInterfacePTPDiscretePure() const
        {
            const Interface_ProblemToPolicyDiscrete* p =
                GetInterfacePTPDiscrete();
            const Interface_ProblemToPolicyDiscretePure* pp = 
                dynamic_cast<const Interface_ProblemToPolicyDiscretePure*>(p);
            return pp;
        }
    
        /** \brief Returns the jaI taken by this policy for  domain
         * index i.*/
        virtual Index GetActionIndex(Index i) const = 0;
   
        /**\brief Returns the probability that the policy specifies 
         * action aI for domain index i.
         *
         * Required by PolicyDiscrete.
         */
        double GetActionProb( Index i, Index aI ) const;
        /// Returns a pointer to a copy of this class.
        virtual PolicyDiscretePure* Clone() const = 0;
        
};


#endif /* !_POLICYDISCRETEPURE_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
