/**\file JointBeliefSparse.h
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
 * $Id: JointBeliefSparse.h 4016 2010-03-11 16:56:02Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _JOINTBELIEFSPARSE_H_
#define _JOINTBELIEFSPARSE_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"
#include "JointBeliefInterface.h"
#include "BeliefSparse.h"

class MultiAgentDecisionProcessDiscreteInterface; //forward declaration to avoid including each other

/// JointBeliefSparse represents a sparse joint belief.
class JointBeliefSparse : public JointBeliefInterface,
                          public BeliefSparse
{
private:    

    /// Slow version of Update(), if GetTransitionModelDiscretePtr() is 0.
    double UpdateSlow(const MultiAgentDecisionProcessDiscreteInterface &pu,
                      Index lastJAI, Index newJOI);

protected:
    
public:
    // Constructor, destructor and copy assignment.
    /// Default Constructor
    JointBeliefSparse();

    /// Constructor which sets the \a size of the joint belief.
    JointBeliefSparse(size_t size);
        
    /// Constructor which copies \a belief in this joint belief.
    JointBeliefSparse(const std::vector<double> &belief);

    /// Constructor which copies \a belief in this joint belief.
    JointBeliefSparse(const JointBeliefInterface &belief);
    JointBeliefSparse(const StateDistribution& belief);

    /// Destructor.
    ~JointBeliefSparse();

    // operators:
    using BeliefSparse::operator=;
    JointBeliefSparse& operator= (const JointBeliefSparse& o);
    JointBeliefInterface& operator= (const JointBeliefInterface& o);

    double Update(const MultiAgentDecisionProcessDiscreteInterface &pu,
                  Index lastJAI, Index newJOI);
    /// Returns a pointer to a copy of this class.
    virtual JointBeliefSparse* Clone() const
        { return new JointBeliefSparse(*this); }

};


#endif /* !_JOINTBELIEFSPARSE_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
