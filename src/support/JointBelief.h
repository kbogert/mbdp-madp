/**\file JointBelief.h
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
 * $Id: JointBelief.h 4016 2010-03-11 16:56:02Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _JOINTBELIEF_H_
#define _JOINTBELIEF_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"

#include "Belief.h"
#include "JointBeliefInterface.h"

class MultiAgentDecisionProcessDiscreteInterface; //forward declaration to avoid including each other

/**
 * \brief JointBelief stores a joint belief, represented as a regular
 * (dense) vector of doubles.
 */
class JointBelief : public JointBeliefInterface,
                    public Belief
{
private:    
    
protected:
    
public:        
        
    /// Constructor which sets the \a size of the joint belief.
    JointBelief(size_t size=0);

    /// Constructor which copies \a belief in this joint belief.
    JointBelief(const std::vector<double> &belief);

    /// Constructor which copies \a belief in this joint belief.
    JointBelief(const JointBeliefInterface &belief);
    JointBelief(const StateDistribution& belief);

    /// Destructor
    ~JointBelief();

    JointBelief& operator= (const JointBelief& o);
    JointBeliefInterface& operator= (const JointBeliefInterface& o);

    double Update(const MultiAgentDecisionProcessDiscreteInterface &pu,
                  Index lastJAI, Index newJOI);
    /// Returns a pointer to a copy of this class.
    virtual JointBelief* Clone() const
        { return new JointBelief(*this); }


};

#endif /* !_JOINTBELIEF_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
