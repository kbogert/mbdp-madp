/**\file QPOMDP.h
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
 * $Id: QPOMDP.h 3603 2009-08-25 10:38:25Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _QPOMDP_H_
#define _QPOMDP_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"
#include "QFunctionJAOHTree.h"


/**\brief QPOMDP is a class that represents the QPOMDP heuristic.
 *
 * It is associated with a PlanningUnitDecPOMDPDiscrete which it uses for things
 * as horizon, action-/observation(history) indices, etc.
 */
class QPOMDP : public QFunctionJAOHTree
{
private:

    /**Recursively compute the heuristic. This is called by Compute(). */
#if QFunctionJAOH_useIndices
    double ComputeRecursively(size_t time_step, 
                              LIndex joahI,
                              Index lastJAI);
#else    
    double ComputeRecursively(size_t time_step, 
                              JointActionObservationHistoryTree* jaoht, 
                              Index lastJAI);
#endif
    
protected:
    
public:
    // Constructor, destructor and copy assignment.
    /// (default) Constructor
    QPOMDP(const PlanningUnitDecPOMDPDiscrete& pu);
    
    // Destructor.
    ~QPOMDP();

};


#endif /* !_QPOMDP_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
