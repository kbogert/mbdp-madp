/**\file JESPDynamicProgrammingPlanner.h
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
 * $Id: JESPDynamicProgrammingPlanner.h 3604 2009-08-25 10:52:24Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _JESPDYNAMICPROGRAMMINGPLANNER_H_
#define _JESPDYNAMICPROGRAMMINGPLANNER_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"
#include "PlanningUnitDecPOMDPDiscrete.h"
//#include "ValueFunctionDecPOMDPDiscrete.h"
#include "JointPolicyPureVector.h"
//#include "JointPolicy.h"

class ValueFunctionDecPOMDPDiscrete;
//class JointPolicyPureVector;
class JointPolicy;
class IndividualBeliefJESP;

/// JESPDynamicProgrammingPlanner plans with the DP JESP algorithm.
/** It has been presented in refJESP (see DOC-References.h).
 */
class JESPDynamicProgrammingPlanner : public PlanningUnitDecPOMDPDiscrete
{
    private:    
        //the best found policy
        JointPolicyPureVector _m_foundPolicy;
        //the expected reward of the best found policy
        double _m_expectedRewardFoundPolicy;
        //intermediate result from ExhaustiveBestResponse
        //JointPolicyPureVector _m_exhBRBestPol;
    protected:
        ///Computes a best response for agentI recursively
        /**
         *\li agentI  -the agent we are computing the best response for
         *\li ohI     -the observation history index of agentI
         *\li B       -the belief for which we compute the value+action
         *\li stage   -the stage of B
         *\li jpol    -the joint policy
         *\li new_pol -vector that will contain the best action for each AOH for
         *             agent i
         */
        double DPBestResponseRecursively (
                const Index agentI, 
                const Index aohI,
                const IndividualBeliefJESP& B, 
                const Index stage, 
                JointPolicyPureVector* jpol,
                std::vector<Index>& new_pol
                );
        void ConstructPolicyRecursively  (
             const Index agentI, //the agent we are computing for
             const Index aohI,    //the action-observation history of agentI
             const Index ohI,    //the observation history of agentI
             const Index stage, //the stage of B
             JointPolicyPureVector* jpol,//the joint policy
             std::vector<Index>& new_pol
            );
    public:
        
        // Constructor, destructor and copy assignment.
        // (default) Constructor
        //JESPDynamicProgrammingPlanner();
        JESPDynamicProgrammingPlanner(
            const PlanningUnitMADPDiscreteParameters &params,
            size_t horizon, DecPOMDPDiscreteInterface* p);
        JESPDynamicProgrammingPlanner(int horizon, 
                DecPOMDPDiscreteInterface* p);

        //operators:

        //data manipulation (set) functions:
        /**The methods that performs the planning according to the Exhaustive
         * JESP algorithm. */
        void Plan();
        double DynamicProgrammingBestResponse(JointPolicyPureVector* jpol, 
                Index agentI);

        //get (data) functions:
        JointPolicy* GetJointPolicy(void)
            { return(&_m_foundPolicy); }
        JointPolicyDiscrete* GetJointPolicyDiscrete(void)
            { return(&_m_foundPolicy); }
        JointPolicyPureVector* GetJointPolicyPureVector(void)
            { return(&_m_foundPolicy); }
        double GetExpectedReward(void) const
            { return(_m_expectedRewardFoundPolicy); }

};


#endif /* !_JESPDYNAMICPROGRAMMINGPLANNER_H_ */


// Local Variables: ***
// mode:c++ ***
// End: ***
