/**\file QMDP.h
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
 * $Id: QMDP.h 3603 2009-08-25 10:38:25Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _QMDP_H_
#define _QMDP_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"

#include "MDPValueIteration.h"
#include "QFunctionJAOH.h"
#include "QFunctionJointBeliefInterface.h"

/**\brief QMDP is a class that represents the QMDP heuristic.
 *
 * It is associated with a PlanningUnitDecPOMDPDiscrete which it uses for things
 * as horizon, action-/observation(history) indices, etc. *
 *  */
class QMDP : virtual public QFunctionJAOH,
             virtual public QFunctionJointBeliefInterface
{
private:

    MDPSolver *_m_p;
    
    bool _m_initialized, _m_useJaohQValuesCache;

    void Initialize();
    void DeInitialize();

    void CacheJaohQValues();

protected:
    
public:
    // Constructor, destructor and copy assignment.
    /// (default) Constructor
    QMDP(const PlanningUnitDecPOMDPDiscrete& pu,
         bool useJaohQValuesCache=false);
    /// Destructor.
    ~QMDP();
    
    //operators:
    
    //data manipulation (set) functions:
                
    /**Compute the heuristic. (after associated with an initialized 
     * PlanningUnitDecPOMDPDiscrete).
     *
     * Note: unlike QBG and QPOMDP, the QMDP heuristic can be computed 
     * without access to JointActionObservationHistory (Indices) and 
     * JointBeliefs. So there is only 1 compute version. However in
     * order to get the Q for a particular  JointActionObservationHistory 
     * (Index) this information is needed. Therefore there are multiple
     * GetQ functions for this class.*/
    void Compute();
    
    //get (data) funct        
    /**Return the Qvalue for JointActionObservationHistory Index jaohI and
     * JointAction index jaI.
     */
    double GetQNoCache(Index jaohI, Index jaI) const;
    
    double GetQ(Index jaohI, Index jaI) const
        {  if(_m_useJaohQValuesCache) return (_m_QValues(jaohI,jaI));
            else return(GetQNoCache(jaohI,jaI)); }

    void SetPU(const PlanningUnitDecPOMDPDiscrete& pu);

    double GetQ(const JointBeliefInterface &b, Index jaI) const;
    double GetQ(const JointBeliefInterface &b, Index time_step,
                Index jaI) const;
    
    double GetQSA(Index t, Index sI, Index jaI) const;
    
    void Save(std::string filename) const;
    
    void Load(std::string filename);
    
};


#endif /* !_QMDP_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
