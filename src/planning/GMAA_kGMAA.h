/**\file GMAA_kGMAA.h
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
 * $Id: GMAA_kGMAA.h 3611 2009-08-25 15:02:24Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _GMAA_kGMAA_H_
#define _GMAA_kGMAA_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"
#include "GeneralizedMAAStarPlannerForDecPOMDPDiscrete.h"
#include "BGIP_SolverCreatorInterface.h"

/**\brief GMAA_kGMAA is a class that represents a GMAA planner that performs
 * k-GMAA, i.e. forward-sweep policy computation, but then returning the k
 * best-ranked policies from 'NEXT'. (see #refGMAA in DOC-References.h)
 * 
 * kGMAA computes an (approximate) policy using a (approximate) Q-value function. 
 *
 * \sa refGMAA 
 * */
class GMAA_kGMAA : public GeneralizedMAAStarPlannerForDecPOMDPDiscrete
{
    private:
        /**\brief The BGIP_SolverCreator object is used to creats a BGIP_Solver of 
         * the correct type.
         *
         * Also it already contains the correct parameters (those are set when
         * the BGIP_SolverCreator was initialized).
         */
        const BGIP_SolverCreatorInterface<JointPolicyPureVector> * _m_newBGIP_Solver;

    protected:        
        /**\brief the (main part of the) 'NEXT' function from #refGMAA.
         *
         * The function that from a given partial policy from the policy
         * pool constructs a new set of (partial) joint policies.
         *
         * This function can be overrides the one in the base class
         * GeneralizedMAAStarPlannerForDecPOMDPDiscrete
         *
         * \sa GeneralizedMAAStarPlannerForDecPOMDPDiscrete 
         **/
        bool ConstructAndValuateNextPolicies(PartialPolicyPoolItemInterface*
                ppi, PartialPolicyPoolInterface* poolOfNextPolicies);
        /**\brief the last part of the 'NEXT'  function from #refGMAA.
         *
         * This filters out some policies we do not want to process further.
         * Typically this function is used to only return the best k
         * policies.
         *
         * Also, this function returns nothing if are_LBs==true, which 
         * indicates that ALL the policies in poolOfNextPolicies are 
         * full-length policies (that should not be processed further).
         *
         * This function can be overrides the one in the base class*/
        void SelectPoliciesToProcessFurther( PartialPolicyPoolInterface*
                poolOfNextPolicies, bool are_LBs, double bestLB);
   
        /**\brief Return a new PartialPolicyPoolInterface*.
         *
         * This function returns a pointer to new instance of the 
         * PartialPolicyPoolInterface used by this class.
         *
         * In this class this is a PolicyPoolJPolValPair
         */
        PartialPolicyPoolInterface* NewPP();
        //{return (new PolicyPoolJPolValPair);};
        /**\brief Return a new PartialPolicyPoolItemInterface*.
         *
         * This function returns a pointer to new instance of the 
         * PartialPolicyPoolItemInterface used by this class.
         *
         * In this class this is a JPolValPair
         */
        PartialPolicyPoolItemInterface* NewPPI(PartialJointPolicyDiscretePure* jp, double v);
        //{return (new JPolValPair(jp,v));};
        /**\brief Return a new Joint policy.
         */
        PartialJointPolicyDiscretePure* NewJPol() const;
        //{ return new JointPolicyPureVector();}
        
    public:
        
        // Constructor, destructor and copy assignment.
        /**\brief Constructor.
         *
         * Takes the planning horizon as argument and
         * a pointer to the DecPOMDPDiscreteInterface for which planning takes place.
         * the booleans arguments are passed down to PlanningUnitMADPDiscrete. 
         * */
        GMAA_kGMAA(
            const PlanningUnitMADPDiscreteParameters &params,
            const BGIP_SolverCreatorInterface<JointPolicyPureVector> * bgs,
            size_t horizon=3,
            DecPOMDPDiscreteInterface* p=0,
            size_t nrPoliciesToProcess=1);

};


#endif /* !_GMAA_OPTIMALFORWARDSWEEP_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
