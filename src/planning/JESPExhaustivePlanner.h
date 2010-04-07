/**\file JESPExhaustivePlanner.h
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
 * $Id: JESPExhaustivePlanner.h 3603 2009-08-25 10:38:25Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _JESPEXHAUSTIVEPLANNER_H_
#define _JESPEXHAUSTIVEPLANNER_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"
#include "PlanningUnitDecPOMDPDiscrete.h"
#include "ValueFunctionDecPOMDPDiscrete.h"
#include "JointPolicyPureVector.h"
#include "JointPolicy.h"

/// JESPExhaustivePlanner plans with the Exhaustive JESP algorithm.
/** It has been presented in refJESP (see DOC-References.h).
 */
class JESPExhaustivePlanner : public PlanningUnitDecPOMDPDiscrete
{
    private:    
        //the best found policy
        JointPolicyPureVector _m_foundPolicy;
        //the expected reward of the best found policy
        double _m_expectedRewardFoundPolicy;
        //intermediate result from ExhaustiveBestResponse
        //JointPolicyPureVector _m_exhBRBestPol;
    protected:
    
    public:
        
        // Constructor, destructor and copy assignment.
        // (default) Constructor
        //JESPExhaustivePlanner();
        JESPExhaustivePlanner(
            const PlanningUnitMADPDiscreteParameters &params,
            size_t horizon, DecPOMDPDiscreteInterface* p);
        JESPExhaustivePlanner(int horizon, DecPOMDPDiscreteInterface* p);

        //operators:

        //data manipulation (set) functions:
        /**The methods that performs the planning according to the Exhaustive
         * JESP algorithm. */
        void Plan();
        double ExhaustiveBestResponse(JointPolicyPureVector* jpol, int agentI);

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


#endif /* !_JESPEXHAUSTIVEPLANNER_H_ */


// Local Variables: ***
// mode:c++ ***
// End: ***
