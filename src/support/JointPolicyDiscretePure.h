/**\file JointPolicyDiscretePure.h
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
 * $Id: JointPolicyDiscretePure.h 4016 2010-03-11 16:56:02Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _JOINTPOLICYDISCRETEPURE_H_
#define _JOINTPOLICYDISCRETEPURE_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"
#include "Interface_ProblemToPolicyDiscretePure.h"
#include "JointActionDiscrete.h"
#include "JointPolicyDiscrete.h"

class JointPolicyPureVector;
class PolicyDiscretePure;

/** \brief JointPolicyDiscretePure is represents a pure joint policy
 * for a discrete MADP.
 *
 * The number of pure joint policies as represented by this class is finite.
 * */
class JointPolicyDiscretePure : public JointPolicyDiscrete
{
    private:  

    
    protected:
    
    public:
        // Constructor, destructor and copy assignment.
        /// default Constructor - constructs empty policy
        JointPolicyDiscretePure() {};
        /// (default) Constructor
        JointPolicyDiscretePure(const Interface_ProblemToPolicyDiscretePure& pu,
                PolicyGlobals::IndexDomainCategory idc );
        /// Copy constructor.
        JointPolicyDiscretePure(const JointPolicyDiscretePure& a);
        /// Destructor.
        virtual ~JointPolicyDiscretePure()
        {};
        /// Copy assignment operator
        virtual JointPolicyDiscretePure& operator= (const JointPolicyDiscretePure& o);

        //operators:

        //data manipulation (set) functions:     
        
        
        ///Randomly initialize the joint policy.
        virtual void RandomInitialization() = 0;
        ///Randomly initialize the policy for agentI.
        virtual void RandomInitialization(Index agentI) = 0;
        
        //get (data) functions:
        
        /// Return pointer to the Interface_ProblemToPolicyDiscretePure.
        const Interface_ProblemToPolicyDiscretePure* 
            GetInterfacePTPDiscretePure() const
        {
            //Referrer<Interface_ProblemToPolicyDiscretePure>::GetReferred(); 
            const Interface_ProblemToPolicyDiscrete* p =
                GetInterfacePTPDiscrete();
            const Interface_ProblemToPolicyDiscretePure* pp = 
                dynamic_cast<const Interface_ProblemToPolicyDiscretePure*>(p);
// why not allow this to return 0 if not succeeded?            
//            if(pp==0)
//                throw(E("JointPolicyDiscretePure::GetInterfacePTPDiscretePure() dynamic_cast failed"));

            return pp;
        }
        ///Sets the planning unit for this joint policy
        inline void SetInterfacePTPDiscretePure(
                Interface_ProblemToPolicyDiscretePure* pu);
        
        ///Sets the policy for agentI to domainI->aI.
        virtual void SetAction(Index agentI, Index domainI, Index aI) =0;

        ///Returns the jaI taken by this policy for joint domain index johI.
        virtual Index GetJointActionIndex(Index i) const = 0;
        ///Returns the action index for domainI for agent aI.
        virtual Index GetActionIndex(Index aI, Index domainI) const = 0;

        virtual JointPolicyPureVector* ToJointPolicyPureVector() const =0;
   
        /**\brief Returns the probability that the policy specifies joint
         * action a for domain index i.
         *
         * Required by JointPolicyDiscrete.
         */
        double GetJointActionProb( Index i, Index ja ) const;
        /**\brief Returns the probability that the policy specifies 
         * action aI for domain index domI for agentI.
         *
         * Required by JointPolicyDiscrete.
         */
        double GetActionProb( Index agentI, Index domI, Index aI ) const;
                
        /// Returns a pointer to a copy of this class.
        virtual JointPolicyDiscretePure* Clone() const = 0;

        /// Prints a description of this JointPolicyPureVector to a string.
        virtual std::string SoftPrint() const = 0; 

        /// Prints a brief description to a string.
        virtual std::string SoftPrintBrief() const = 0; 
};


#endif /* !_JOINTPOLICYDISCRETEPURE_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
