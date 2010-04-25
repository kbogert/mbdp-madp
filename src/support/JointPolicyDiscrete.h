/**\file JointPolicyDiscrete.h
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
 * $Id: JointPolicyDiscrete.h 4016 2010-03-11 16:56:02Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _JOINTPOLICYDISCRETE_H_
#define _JOINTPOLICYDISCRETE_H_ 1

/* the include directives */
#include <iostream>
#include <stdlib.h>
#include "Globals.h"
#include "JointPolicy.h"
#include "Interface_ProblemToPolicyDiscrete.h"
#include "Referrer.h"


using namespace PolicyGlobals;

class PolicyDiscrete;
/**\brief JointPolicyDiscrete is a class that represents a discrete joint
 * policy.
 *
 * A `discrete joint policy' is a policy for a discrete problem. I.e., the 
 * problem specifies, for each agent, a discrete domain for the policy and 
 * discrete actions.
 *
 * A JointPolicyDiscrete from discrete indices over the domain (typically 
 * action-observation histories or types) to (degenerate) probability 
 * distributions over indices over (joint) actions.
 *
 * This means that this class includes both pure and stochastic pure policies.
 *
 * */
class JointPolicyDiscrete : public JointPolicy
{
    private:   
        /// Maintains the IndexDomainCategory. 
        PolicyGlobals::IndexDomainCategory _m_indexDomCat;
        /// Interface that allows this policy to get some info on the problem
        const Interface_ProblemToPolicyDiscrete* _m_PTPD;
    
    protected:
    
    public:
        // Constructor, destructor and copy assignment.
        /// default constructor creates an empty policy
        JointPolicyDiscrete()
            : 
                JointPolicy(0),
                _m_PTPD(0)
        {};
        /// (default) Constructor
        JointPolicyDiscrete(const Interface_ProblemToPolicyDiscrete& pu,
                PolicyGlobals::IndexDomainCategory idc );
        /// Copy constructor.
        JointPolicyDiscrete(const JointPolicyDiscrete& a);
        /// Destructor.
        virtual ~JointPolicyDiscrete()
        {};
        /// Assignment operator
        virtual JointPolicyDiscrete& operator= (const JointPolicyDiscrete& o);

        //operators:

        //data manipulation (set) functions:
        /**\brief sets the category of the domain over which the indices of
         * this policy are specified.
         */
        void SetIndexDomainCategory(IndexDomainCategory idc)
        {_m_indexDomCat = idc;};
        
        //get (data) functions:
        /**\brief returns the Category of the domain over which the indices of
         * this policy are specified.
         */
        IndexDomainCategory GetIndexDomainCategory() const
        {return (_m_indexDomCat);};


        /**\brief return pointer to individual policy of agent agI
         */
        virtual PolicyDiscrete* GetIndividualPolicyDiscrete(Index agI) const = 0;
        /**\brief Returns the probability that the policy of
         * agentI specifies action aI
         * for domain index domI.
         *
         * Implementations for pure policies clearly should return 0 or 1.
         */
        virtual double GetActionProb( Index agentI, 
                Index domI, Index aI ) const = 0;

        /**\brief Returns the probability that the policy specifies joint action
         * for joint domain index i.
         *
         * Implementations for pure policies clearly should return 0 or 1.
         */
        virtual double GetJointActionProb( Index i, Index ja ) const = 0;
        
        /**\brief Returns a sampled joint action.
         * i is the i-th joint domain index  */
        Index SampleJointAction( Index i ) const;
        /**\brief Returns a sampled joint action.
         * Is is the vector of domain indices  */
        Index SampleJointAction( const std::vector<Index>&  Is ) const;
        /**\brief Returns a sampled joint action.
         * i is the i-th joint domain index  */
        void SampleJointActionVector(Index i, std::vector<Index>& jaVec ) const;
        /**\brief Returns a sampled joint action.
         * Is is the vector of domain indices  */
        void SampleJointActionVector( 
                const std::vector<Index>& Is, std::vector<Index>& jaVec ) const;
        
        /**\brief return a pointer to the referred 
         * Interface_ProblemToPolicyDiscrete.
         */
        const Interface_ProblemToPolicyDiscrete* GetInterfacePTPDiscrete() const
        {return _m_PTPD;}
        /**\brief sets the pointer to the Interface_ProblemToPolicyDiscrete.
         */
        void SetInterfacePTPDiscrete(const 
                Interface_ProblemToPolicyDiscrete* p)
        {_m_PTPD = p;}

        /// Returns the number of policy domain elements for agent agentI.
        size_t GetNrDomainElements(Index agentI) const
        { return(GetInterfacePTPDiscrete()->GetNrPolicyDomainElements(agentI,
                    GetIndexDomainCategory() )); };

        /// Returns a pointer to a copy of this class.
        virtual JointPolicyDiscrete* Clone() const = 0;

};


#endif /* !_JOINTPOLICYDISCRETE_H_ */


// Local Variables: ***
// mode:c++ ***
// End: ***
