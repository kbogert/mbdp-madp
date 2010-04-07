/**\file PlanningUnit.h
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
 * $Id: PlanningUnit.h 3604 2009-08-25 10:52:24Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _PLANNINGUNIT_H_
#define _PLANNINGUNIT_H_ 1

/* the include directives */
#include <iostream>
#include <stdlib.h>
#include "Globals.h"
#include "MultiAgentDecisionProcessInterface.h"

#define DEBUG_PU_CONSTRUCTORS 0

class JointPolicy;

/** \brief PlanningUnit represents a planning unit, i.e., a planning
 * algorithm.
 *
 * This is a very general class, that only manages the planning
 * horizon and can initialize the random number generator (srand).
*/
class PlanningUnit
{
    private:

    /// Pointer to the problem.
    MultiAgentDecisionProcessInterface *_m_problem;

    /// Used by GetNextAgentIndex().
    Index _m_agentI;
    
    /// The planning horizon: MAXHORIZON for infinite horizon. */
    size_t _m_horizon;
    /// The random seed.
    int _m_seed;

    protected:

    public:
    // Constructor, destructor and copy assignment.
    /// (default) Constructor

    /// Constructor which sets the horizon and the problem.
    PlanningUnit(size_t horizon,
                 MultiAgentDecisionProcessInterface* p) :
        _m_problem(p),
        _m_agentI(0),
        _m_horizon(horizon),
        _m_seed(0)
        {}

    /// Destructor.
    virtual ~PlanningUnit(){}

    //operators:

    //data manipulation (set) functions:
    /// Stores the random seed and calls InitSeed().
    void SetSeed(int s){ _m_seed = s; InitSeed(); }

    /// Updates the problem pointer.
    void SetProblem(MultiAgentDecisionProcessInterface* p) { _m_problem = p; }

    /// Updates the horizon of the planning problem.
    virtual void SetHorizon(size_t horizon) { _m_horizon = horizon; }

    /// Initializes the random number generator (srand) to the stored seed.
    void InitSeed() const { srand(_m_seed); }

    //get (data) functions:    
    /// Returns the planning horizon.
    size_t GetHorizon() const { return(_m_horizon); }
    /// Returns the random seed stored.
    int GetSeed() const { return(_m_seed); }

    /// Return the number of agents.     
    size_t GetNrAgents() const { return(_m_problem->GetNrAgents()); }

    /// Maintains a agent index and returns the next one on calling */
    Index GetNextAgentIndex() {
        Index curIndex = _m_agentI;
        _m_agentI = (_m_agentI+1) % GetNrAgents();
        return(curIndex);
    }

    /// Get the problem pointer.
    const MultiAgentDecisionProcessInterface* GetProblem() const
        { return(_m_problem); }

    //other

    /// The function that performs the actual planning.
    virtual void Plan() = 0;

    /// Returns a pointer to the computed joint policy.
    virtual JointPolicy* GetJointPolicy() = 0;
};


#endif /* !_PLANNINGUNIT_H_ */


// Local Variables: ***
// mode:c++ ***
// End: ***
