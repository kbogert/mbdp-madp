/**\file PerseusQFunctionPlanner.h
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
 * $Id: PerseusQFunctionPlanner.h 2293 2008-02-19 18:07:32Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _PERSEUSQFUNCTIONPLANNER_H_
#define _PERSEUSQFUNCTIONPLANNER_H_ 1

/* the include directives */
#include "Globals.h"
#include "PerseusStationary.h"

class PlanningUnitDecPOMDPDiscrete;

/** \brief PerseusQFunctionPlanner is a Perseus planner that uses
 * QFunctions. */
class PerseusQFunctionPlanner : public PerseusStationary

{
private:    

    virtual QFunctionsDiscrete
    BackupStage(const BeliefSet &S,
                const QFunctionsDiscrete &V) const = 0;
    
protected:
    
public:

    PerseusQFunctionPlanner(const PlanningUnitDecPOMDPDiscrete& pu);

    /// Destructor.
    virtual ~PerseusQFunctionPlanner();

    void Plan();

};


#endif /* !_PERSEUSQFUNCTIONPLANNER_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
