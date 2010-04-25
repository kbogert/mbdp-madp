/**\file PerseusBGPlanner.h
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
 * $Id: PerseusBGPlanner.h 2394 2008-03-03 12:39:37Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _PERSEUSBGPLANNER_H_
#define _PERSEUSBGPLANNER_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"

#include "AlphaVectorBG.h"
#include "PerseusQFunctionPlanner.h"

/**PerseusBGPlanner implements the Perseus planning algorithm for
 * BGs.  */
class PerseusBGPlanner : public AlphaVectorBG,
                         public PerseusQFunctionPlanner
{
private:    

    /// Compute a Perseus backup stage.
    QFunctionsDiscrete
    BackupStage(const BeliefSet &S,
                const QFunctionsDiscrete &V) const;

    QFunctionsDiscrete
    BackupStageAll(const BeliefSet &S,
                   const QFunctionsDiscrete &V) const;

    QFunctionsDiscrete
    BackupStageSampling(const BeliefSet &S,
                        const QFunctionsDiscrete &V) const;
    QFunctionsDiscrete
    BackupStageSamplingAlt(const BeliefSet &S,
                           const QFunctionsDiscrete &V) const;

    BGBackupType _m_backupType;

protected:

public:

    // Constructor, destructor and copy assignment.
    /// (default) Constructor
    PerseusBGPlanner(const PlanningUnitDecPOMDPDiscrete& pu,
                     const QAVParameters& params);

    PerseusBGPlanner(const PlanningUnitDecPOMDPDiscrete& pu);

    /// Destructor.
    ~PerseusBGPlanner();

};


#endif /* !_PERSEUSBGPLANNER_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
