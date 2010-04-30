/**\file MBDPPlanner.h
 *
 * Authors:
 * Christopher Jackson <christopher.jackson@gmail.com>
 *
 * Copyright 2010 Institute for Artificial Intelligence, University of Georgia
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
 * $Id: $
 */

/* Only include this header file once. */
#ifndef _MBDPPLANNER_H_
#define _MBDPPLANNER_H_ 1

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

/// MBDPPlanner plans with the Memory-Bounded Dynamic Programming algorithm
/** It has been presented in refJESP (see DOC-References.h).
 */
class MBDPPlanner : public PlanningUnitDecPOMDPDiscrete
{
    private:    
        //the best found policy
        JointPolicyPureVector _m_foundPolicy;
        //the expected reward of the best found policy
        double _m_expectedRewardFoundPolicy;
        // the max number of trees kept in memory after a fullBackup
        int _m_maxTrees;
        // The exploration probability of the belief state (higher probability = more beliefs
        double prExploration;

    public:
        
        // Constructor, destructor and copy assignment.
        // (default) Constructor
        //MBDPPlanner();
        MBDPPlanner(
            const PlanningUnitMADPDiscreteParameters &params,
            size_t horizon, DecPOMDPDiscreteInterface* p,
            int maxTrees, double exploration);
        MBDPPlanner(int horizon,
		    DecPOMDPDiscreteInterface* p,
                    int maxTrees, double exploration);

        //operators:

        void Plan();
        int GetMaxTrees(void){ return(_m_maxTrees); }
	void SetMaxTrees(int maxTrees);
        JointActionObservationHistory* fullBackup(JointPolicyPureVector*);

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


#endif /* !_MBDPPLANNER_H_ */


// Local Variables: ***
// mode:c++ ***
// End: ***
