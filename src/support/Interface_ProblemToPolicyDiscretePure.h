/**\file Interface_ProblemToPolicyDiscretePure.h
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
 * $Id: Interface_ProblemToPolicyDiscretePure.h 4020 2010-03-12 15:07:02Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _INTERFACE_PROBLEMTOPOLICYDISCRETEPURE_H_
#define _INTERFACE_PROBLEMTOPOLICYDISCRETEPURE_H_ 1

/* the include directives */
#include <iostream>
#include <vector>
#include <cmath>
#include "Globals.h"
#include "Interface_ProblemToPolicyDiscrete.h"
#include "EOverflow.h"

/** \brief Interface_ProblemToPolicyDiscretePure is an interface from
 * discrete problems to pure policies.
 *
 * I.e., it defines functions that must be implemented by a derived
 * (problem) class such that it can be used to construct a
 * JointPolicyPureVector / PolicyPureVector.
 * 
 * (the class (Joint)PolicyPureVector refers to objects implementing
 * this interface. ) */
class Interface_ProblemToPolicyDiscretePure : public Interface_ProblemToPolicyDiscrete
{
    private:       

    protected:
    
    public:
        /// Destructor.
        virtual ~Interface_ProblemToPolicyDiscretePure() {}

        /// Get the number of policies for an agent, given the policy's domain.
        LIndex GetNrPolicies(Index ag,
                             PolicyGlobals::IndexDomainCategory cat, 
                             size_t depth=MAXHORIZON) const
        {        
#if 0 // don't use powl(), we want to detect overflow
            LIndex nr_pols = 
                static_cast<LIndex>(
                    powl( GetNrActions(ag),
                          GetNrPolicyDomainElements(ag,cat,depth) ));
#endif
            LIndex nrPols=1;
            for(size_t k=0;k!=GetNrPolicyDomainElements(ag,cat,depth);++k)
            {
                LIndex nrPolsOld=nrPols;
                nrPols*=GetNrActions(ag);
                if(nrPols<nrPolsOld)
                    throw(EOverflow("Interface_ProblemToPolicyDiscretePure::GetNrPolicies() overflow detected"));
            }
            return(nrPols);
        }

        /// Get the number of joint policies, given the policy's domain.
        LIndex GetNrJointPolicies(PolicyGlobals::IndexDomainCategory cat, 
                                  size_t depth=MAXHORIZON) const
        {
            LIndex n=1;
            for(Index ag=0; ag < GetNrAgents(); ag++)
            {
                LIndex nOld=n;
                n *= GetNrPolicies(ag,cat,depth);
                if(n<nOld)
                    throw(EOverflow("Interface_ProblemToPolicyDiscretePure::GetNrJointPolicies() overflow detected"));
            }

            return(n);
        }

};


#endif /* !_INTERFACE_PROBLEMTOPOLICYDISCRETEPURE_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
