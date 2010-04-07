/**\file AlphaVectorBG.h
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
 * $Id: AlphaVectorBG.h 3268 2009-04-29 18:42:43Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _ALPHAVECTORBG_H_
#define _ALPHAVECTORBG_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"

#include "AlphaVectorPlanning.h"
#include "BGBackupType.h"

class BayesianGameIdenticalPayoff;
class PlanningUnitDecPOMDPDiscrete;
class AlphaVector;



/**AlphaVectorBG implements Bayesian Game specific functionality for
 * alpha-vector based planning.  */
class AlphaVectorBG : virtual public AlphaVectorPlanning
{
private:    

    BayesianGameIdenticalPayoff *_m_bgip;

    std::vector<std::vector<bool> > GetMask(const ValueFunctionPOMDPDiscrete &V) const;

    AlphaVector BeliefBackupBGIP_Solver(const JointBeliefInterface &b,
                                     Index a,
                                     const GaoVectorSet &G,
                                     const ValueFunctionPOMDPDiscrete &V,
                                     BGBackupType type) const;

    AlphaVector
    BeliefBackupExhaustiveOnlyKeepMax(const JointBeliefInterface &b,
                                      Index a,
                                      const GaoVectorSet &G,
                                      const ValueFunctionPOMDPDiscrete &V) const;

    AlphaVector
    BeliefBackupExhaustiveStoreAll(const JointBeliefInterface &b,
                                   Index a,
                                   const GaoVectorSet &G,
                                   const ValueFunctionPOMDPDiscrete &V) const;

protected:
    
public:

    // Constructor, destructor and copy assignment.
    /// (default) Constructor
    AlphaVectorBG(const PlanningUnitDecPOMDPDiscrete& pu);
    /// Destructor.
    virtual ~AlphaVectorBG();

    AlphaVector BeliefBackup(const JointBeliefInterface &b,
                             Index a,
                             const GaoVectorSet &G,
                             const ValueFunctionPOMDPDiscrete &V,
                             BGBackupType type=BGIP_SOLVER_EXHAUSTIVE) const;

    static std::string SoftPrintBackupType(BGBackupType bgBackupType);

};


#endif /* !_ALPHAVECTORBG_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
