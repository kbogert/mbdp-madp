/**\file GMAA_MAAstar.h
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
 * $Id: GMAA_MAAstar.h 3598 2009-08-20 12:29:54Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _GMAA_MAASTAR_H_
#define _GMAA_MAASTAR_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"
#include "GeneralizedMAAStarPlannerForDecPOMDPDiscrete.h"
#include "PolicyPoolPartialJPolValPair.h"
#include "PartialJointPolicyPureVector.h"



/**\brief GMAA_MAAstar is a class that represents a planner that performs
 * MAA* as described by Szer et al. (see #refMAA in DOC-References.h)
 * 
 * MAA* performs a heuristic search for the optimal policy. When used 
 * with an admissible heuristic it is guaranteed to find the optimal policy.
 *
 * \sa refMAA 
 * */
class GMAA_MAAstar : public GeneralizedMAAStarPlannerForDecPOMDPDiscrete
{
    private:

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
         * In this class this is a PolicyPoolPartialJPolValPair
         */
        PartialPolicyPoolInterface* NewPP()
        {return (new PolicyPoolPartialJPolValPair);};
        /**\brief Return a new PartialPolicyPoolItemInterface*.
         *
         * This function returns a pointer to new instance of the 
         * PartialPolicyPoolItemInterface used by this class.
         *
         * In this class this is a JPolValPair
         */
        PartialPolicyPoolItemInterface* NewPPI(PartialJointPolicyDiscretePure* jp, double v);
        /**\brief Return a new Joint policy.

        JointPolicyDiscretePure* NewJPol() const
        { return new PartialJointPolicyPureVector();}
         */
        
    public:
        
        // Constructor, destructor and copy assignment.
        /**\brief Constructor.
         *
         * Takes the planning horizon as argument and
         * a pointer to the DecPOMDPDiscreteInterface for which planning
         * takes place.  the booleans arguments are passed down to
         * PlanningUnitMADPDiscrete.  .*/
        GMAA_MAAstar(
                const PlanningUnitMADPDiscreteParameters &params,
                size_t horizon=3, 
                DecPOMDPDiscreteInterface* p=0,
                int verboseness=0
                     );

        /**\brief Default constructor.
         *
         * \todo TODO: check if this is used? is working? is desirable?
         */
        GMAA_MAAstar(size_t horizon=3, DecPOMDPDiscreteInterface* p=0);

        /*
        /// Copy constructor.
        GMAA_MAAstar(const GMAA_MAAstar& a);
        /// Destructor.
        ~GMAA_MAAstar();
        /// Copy assignment operator
        GMAA_MAAstar& operator= (const GMAA_MAAstar& o);
        */

        //operators:

        //data manipulation (set) functions:
        
        //get (data) functions:
};


#endif /* !_GMAA_MAASTAR_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
