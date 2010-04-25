/**\file TransitionModelDiscrete.h
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
 * $Id: TransitionModelDiscrete.h 4016 2010-03-11 16:56:02Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _TRANSITIONMODELDISCRETE_H_
#define _TRANSITIONMODELDISCRETE_H_ 1

/* the include directives */
#include <boost/numeric/ublas/matrix.hpp>
#include "Globals.h"
#include "TransitionModel.h"

/// TransitionModelDiscrete represents a discrete transition model.
class TransitionModelDiscrete : public TransitionModel
{
private:

    /// The number of states.
    int _m_nrStates;
    /// The number of joint actions.
    int _m_nrJointActions;
    
protected:
    
public:
    // Constructor, destructor and copy assignment.
    /// Constructor with the dimensions of the transition model.
    TransitionModelDiscrete(int nrS = 1, int nrJA = 1);

    virtual ~TransitionModelDiscrete();    
        
    /// Returns P(s'|s,ja).
    virtual double Get(Index sI, Index jaI, Index sucSI) const = 0;

    //data manipulation funtions:
    /// Sets P(s'|s,ja)
    /** sI, jaI, sucSI, are indices of the state, * taken joint action
     * and resulting successor state. prob is * the probability. The
     * order of events is s, ja, s', so is the arg. list
     */
    virtual void Set(Index sI, Index jaI, Index sucSI, double prob) = 0;

    /// Sample a successor state.
    Index SampleSuccessorState(Index sI, Index jaI);
       
    /// Returns a pointer to a copy of this class.
    virtual TransitionModelDiscrete* Clone() const = 0;

    /// SoftPrints tabular transition model.
    std::string SoftPrint() const;
};

#endif /* !_TRANSITIONMODELDISCRETE_H_ */


// Local Variables: ***
// mode:c++ ***
// End: ***
