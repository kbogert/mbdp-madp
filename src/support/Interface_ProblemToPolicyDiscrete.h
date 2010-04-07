/**\file Interface_ProblemToPolicyDiscrete.h
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
 * $Id: Interface_ProblemToPolicyDiscrete.h 3598 2009-08-20 12:29:54Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _INTERFACE_PROBLEMTOPOLICYDISCRETE_H_
#define _INTERFACE_PROBLEMTOPOLICYDISCRETE_H_ 1

/* the include directives */
#include <iostream>
#include <vector>
#include <cmath>
#include "Globals.h"
#include "PolicyGlobals.h"

/** \brief Interface_ProblemToPolicyDiscrete is an interface from
 * discrete problems to policies.
 *
 * I.e., it defines functions that must be implemented by a derived
 * (problem) class such that it can be used to construct a
 * JointPolicyPureVector / PolicyPureVector.
 * 
 * (the class (Joint)PolicyPureVector refers to objects implementing
 * this interface. ) */
class Interface_ProblemToPolicyDiscrete 
{
    private:       

    protected:
    
    public:
        // Constructor, destructor and copy assignment.
        /// (default) Constructor
        Interface_ProblemToPolicyDiscrete()
        {}
        /// Destructor.
        virtual ~Interface_ProblemToPolicyDiscrete() {}

        /// Check whether certain index conversions are cached.
        virtual bool AreCachedJointToIndivIndices(
                const PolicyGlobals::IndexDomainCategory pdc) const = 0;

        /// Get the number of agents involved in this problem.
        virtual size_t GetNrAgents() const = 0;
        /// Get the number of joint actions.
        size_t GetNrJointActions() const
        {
            size_t nrJA = 1;
            for(Index i=0; i < GetNrAgents(); i++)
                nrJA *= GetNrActions(i);
            return(nrJA);
        }

        /// Get the number of invididual actions of a particular agent.
        virtual size_t GetNrActions(Index agentI) const = 0;   
        /// Get the number of elements in the domain of an agent's policy.
        virtual size_t GetNrPolicyDomainElements(Index agentI,
                                                 PolicyGlobals::IndexDomainCategory cat,
                                                 size_t depth=MAXHORIZON) const = 0;

        /// Converts individual action indices to a joint action index.
        /** indivIndices is an array of size GetNrAgents()
         */
        virtual Index IndividualToJointActionIndices(
                const Index* indivIndices) const = 0;
        /// Converts individual action indices to a joint action index.
        virtual Index IndividualToJointActionIndices(
                const std::vector<Index>& indivIndices) const = 0;

        /// Return the default IndexDomainCategory for the problem.
        virtual PolicyGlobals::IndexDomainCategory GetDefaultIndexDomCat()
            const = 0;

        /// Converts joint indices to individual policy domain element indices.
        /**A function that should be implemented by a derived class,
         * if this derived class caches index vectors of the policy
         * domains elements corresponding to a joint index. See
         * AreCachedJointToIndivIndices()
         */
        virtual std::vector<Index> JointToIndividualPolicyDomainIndices(Index jdI,
                PolicyGlobals::IndexDomainCategory cat) const = 0;
        /// Converts individual policy domain element indices to joint indices.
        /**A function that should be implemented by a derived class,
         * if this derived class caches index vectors of the policy
         * domains elements corresponding to a joint index. See
         * AreCachedJointToIndivIndices()
         */
        virtual const std::vector<Index>& JointToIndividualPolicyDomainIndicesRef( 
                Index jdI, PolicyGlobals::IndexDomainCategory cat) const = 0;
        /**Virtual function that has to be implemented by derived class.
         * This should return a string describing element dIndex of the domain
         * (e.g. an observation history) of agent agentI.*/
        virtual std::string SoftPrintPolicyDomainElement(Index agentI, Index dIndex,
                PolicyGlobals::IndexDomainCategory cat ) 
            const=0;
        /**Virtual function that has to be implemented by derived class.
         * This should return a string describing action actionI 
         * of agent agentI.*/
        virtual std::string SoftPrintAction(Index agentI, Index actionI) const =0;

        //operators:

        //data manipulation (set) functions:
        
        //get (data) functions:
};


#endif /* !_INTERFACE_PROBLEMTOPOLICYDISCRETE_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
