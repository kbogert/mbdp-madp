/**\file QFunctionJointBeliefInterface.h
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
 * $Id: QFunctionJointBeliefInterface.h 2979 2008-11-03 20:00:13Z faolieho $
 */

/* Only include this header file once. */
#ifndef _QFUNCTIONJOINTBELIEFINTERFACE_H_
#define _QFUNCTIONJOINTBELIEFINTERFACE_H_ 1

/* the include directives */
#include "Globals.h"
#include "QFunctionForDecPOMDPInterface.h"

class JointBeliefInterface;

/** \brief QFunctionJointBeliefInterface is an interface for
 * QFunctionJointBelief. */
class QFunctionJointBeliefInterface 
    : virtual public QFunctionForDecPOMDPInterface
{
private:
    
protected:
    
public:
    // Constructor, destructor and copy assignment.
    /// (default) Constructor
    QFunctionJointBeliefInterface(){}

    /// Destructor.
    virtual ~QFunctionJointBeliefInterface(){}

    /// Returns Q(\a b, \a jaI).
    virtual double GetQ(const JointBeliefInterface &b, Index jaI) const = 0;

    /// Returns Q(\a b, \a jaI) for a particular \a time_step.
    virtual double GetQ(const JointBeliefInterface &b,
                        Index time_step, Index jaI) const = 0;
};


#endif /* !_QFUNCTIONJOINTBELIEFINTERFACE_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
