/**\file JointBeliefInterface.h
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
 * $Id: JointBeliefInterface.h 4016 2010-03-11 16:56:02Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _JOINTBELIEFINTERFACE_H_
#define _JOINTBELIEFINTERFACE_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"
#include "BeliefInterface.h"

class MultiAgentDecisionProcessDiscreteInterface; //forward declaration to avoid including each other

/// JointBeliefInterface represents an interface for joint beliefs.
class JointBeliefInterface : virtual public BeliefInterface
{
private:    
    
protected:
    
public:
    // Constructor, destructor and copy assignment.
    /// (default) Constructor
    JointBeliefInterface(){};

    /// Destructor.
    virtual ~JointBeliefInterface(){};

    /**\brief assignment operator.
     *
     * This must be implemented by the derived class (with this prototype).
     *
     * For now, this function is purely abstract. Might there be some 
     * members added to this (base) class, then an implementation could
     * be made. This should then be called using
     *          PolicyPoolInterface::operator=(o)
     * from the copy assignment operator of the derived class. See also
     * http://www.icu-project.org/docs/papers/cpp_report/the_assignment_operator_revisited.html .
     */    
    virtual JointBeliefInterface& operator= (const JointBeliefInterface& o)=0;

    /// Performs a joint belief update on this joint belief.
    /**Performs the belief update. I.e., given the current joint belief b
     * (which is represented by \e this), 
     * we compute P(s'|b, a, o) for all new states s'.
     * This function updates this belief (alter this object).
     * Returned is the normalization factor P(o|b,a), which is also to 
     * probability that this new history (belief) occurs given the previous 
     * one.
     */
    virtual double Update(const MultiAgentDecisionProcessDiscreteInterface &pu,
                          Index lastJAI, Index newJOI) = 0;

    /// Returns a pointer to a copy of this class.
    virtual JointBeliefInterface* Clone() const = 0;

};


#endif /* !_JOINTBELIEFINTERFACE_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
