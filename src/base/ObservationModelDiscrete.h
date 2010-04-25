/**\file ObservationModelDiscrete.h
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
 * $Id: ObservationModelDiscrete.h 4016 2010-03-11 16:56:02Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _OBSERVATIONMODELDISCRETE_H_
#define _OBSERVATIONMODELDISCRETE_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"
#include "ObservationModel.h"

/// ObservationModelDiscrete represents a discrete observation model.
class ObservationModelDiscrete : public ObservationModel
{
private:    
    
    /// The number of states.
    int _m_nrStates;
    /// The number of joint actions.
    int _m_nrJointActions;    
    /// The number of joint observations
    int _m_nrJointObservations;

protected:
    
public:
    /// Constructor with the dimensions of the observation model.
    ObservationModelDiscrete(int nrS = 1, int nrJA = 1, int nrJO = 1);

    /// Destructor.
    virtual ~ObservationModelDiscrete();
    
    /// Returns P(jo|ja,s')
    virtual double Get(Index ja_i, Index suc_s_i, Index jo_i) const = 0;

    //data manipulation funtions:
    /// Sets P(o|ja,s')
    /** Index jo_i, Index ja_i, Index suc_s_i, are indices of the
     * joint observation, taken joint action and resulting successor
     * state. prob is the probability. The order of events is ja, s',
     * o, so is the arg. list
     */
    virtual void Set(Index ja_i, Index suc_s_i, Index jo_i, double prob) = 0;
        
    /// Sample a joint observation.
    Index SampleJointObservation(Index jaI, Index sucI);

    /// Returns a pointer to a copy of this class.
    virtual ObservationModelDiscrete* Clone() const = 0;

    /// SoftPrints tabular observation model.
    std::string SoftPrint() const;
};


#endif /* !_OBSERVATIONMODELDISCRETE_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
