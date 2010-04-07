/**\file NullPlannerTOI.h
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
 * $Id: NullPlannerTOI.h 3604 2009-08-25 10:52:24Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _NULLPLANNERTOI_H_
#define _NULLPLANNERTOI_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"

#include "PlanningUnitTOIDecPOMDPDiscrete.h"

/** \brief NullPlannerTOI represents a planner which does nothing, but
 * can be used to instantiate a PlanningUnitTOIDecPOMDPDiscrete. */
class NullPlannerTOI : public PlanningUnitTOIDecPOMDPDiscrete
{
private:    
    
protected:
    
public:

    /// (default) Constructor
    NullPlannerTOI(TOIDecPOMDPDiscrete* p);

    NullPlannerTOI(size_t horizon, TOIDecPOMDPDiscrete* p);

    NullPlannerTOI(const PlanningUnitMADPDiscreteParameters &params,
                size_t horizon, TOIDecPOMDPDiscrete* p);

    ~NullPlannerTOI(){};

    /// Only present to satisfy the interface.
    void Plan();
    /// Only present to satisfy the interface.
    double GetExpectedReward() const;
    /// Only present to satisfy the interface.
    JointPolicy* GetJointPolicy();

};


#endif /* !_NULLPLANNERTOI_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
