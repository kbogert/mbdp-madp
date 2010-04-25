/**\file MDPSolver.h
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
 * $Id: MDPSolver.h 3614 2009-08-25 15:59:51Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _MDPSOLVER_H_
#define _MDPSOLVER_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"

#include "QTable.h"

class PlanningUnitDecPOMDPDiscrete;
class JointBeliefInterface;

/**\brief MDPSolver is an interface for MDP solvers.
 */
class MDPSolver 
{
private:    

    /**A pointer to the PlanningUnit (which can only be a 
     * const PlanningUnitDecPOMDPDiscrete or derived type).*/
    const PlanningUnitDecPOMDPDiscrete* _m_pu;
    
protected:
    
public:
    // Constructor, destructor and copy assignment.
    /// (default) Constructor
    MDPSolver(){};

    MDPSolver(const PlanningUnitDecPOMDPDiscrete& pu): _m_pu(&pu){};
    
    /**Returns a ref to the PlanningUnit.*/
    const PlanningUnitDecPOMDPDiscrete* GetPU() const
        { return(_m_pu); }

    void SetPU(const PlanningUnitDecPOMDPDiscrete& pu){ _m_pu=&pu; }

    /// Destructor.
    virtual ~MDPSolver();
    
    virtual void Plan() = 0;

    /// Get Q-value for finite-horizon case.
    virtual double GetQ(Index time_step, Index sI,
                        Index jaI) const = 0;

    /// Get Q-value for infinite-horizon case.
    virtual double GetQ(Index sI, Index jaI) const = 0;

    virtual double GetQ(Index time_step, const JointBeliefInterface& jb,
                        Index jaI) const;

    virtual double GetQ(const JointBeliefInterface& jb,
                        Index jaI) const;

    virtual QTables GetQTables() const = 0;

    virtual QTable GetQTable(Index time_step) const = 0;

    virtual void SetQTables(const QTables &Qs) = 0;

    virtual void SetQTable(const QTable &Q, Index time_step) = 0;

    void Print() const;

    Index GetMaximizingAction(Index time_step, Index sI);

    QTable LoadQTable(std::string filename);

    static QTable LoadQTable(std::string filename,
                             unsigned int nrS,
                             unsigned int nrA);

    QTables LoadQTables(std::string filename, int nrTables);

    static QTables LoadQTables(std::string filename,
                               unsigned int nrS,
                               unsigned int nrA,
                               unsigned int nrTables);

    static void SaveQTable(const QTable &Q, std::string filename);

    static void SaveQTables(const QTables &Q, std::string filename);
};


#endif /* !_MDPSOLVER_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
