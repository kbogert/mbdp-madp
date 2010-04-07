/**\file BruteForceSearchPlanner.h
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
 * $Id: BruteForceSearchPlanner.h 2125 2008-01-18 12:51:50Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _BRUTEFORCESEARCHPLANNER_H_
#define _BRUTEFORCESEARCHPLANNER_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"
#include "PlanningUnitDecPOMDPDiscrete.h"
#include "ValueFunctionDecPOMDPDiscrete.h"
#include "JointPolicyPureVector.h"

/// BruteForceSearchPlanner implements an exact solution algorithm.
/** Uses brute force search, i.e., it loops over all joint policies,
 * computes the the value of each of them, and stores the one with the
 * highest value. This results necessarily in the optimal value. */
class BruteForceSearchPlanner : public PlanningUnitDecPOMDPDiscrete
{
    private:    
    JointPolicyPureVector _m_foundPolicy;
    double _m_expectedRewardFoundPolicy;
    
    protected:

    public:
    
    // Constructor, destructor and copy assignment.
    // (default) Constructor
    BruteForceSearchPlanner(size_t horizon=3, DecPOMDPDiscreteInterface* p=0);

    BruteForceSearchPlanner(const PlanningUnitMADPDiscreteParameters &params,
                            size_t horizon=3, DecPOMDPDiscreteInterface* p=0);

    //operators:

    //data manipulation (set) functions:
    ///The methods that performs the planning.
    void Plan();
    
    //get (data) functions:
    JointPolicy* GetJointPolicy(void){ return(&_m_foundPolicy); }
    JointPolicyDiscrete* GetJointPolicyDiscrete(void)
        { return(&_m_foundPolicy); }
    JointPolicyPureVector* GetJointPolicyPureVector(void)
        { return(&_m_foundPolicy); }

    double GetExpectedReward(void) const 
        { return(_m_expectedRewardFoundPolicy); }

};


#endif /* !_BRUTEFORCESEARCHPLANNER_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
