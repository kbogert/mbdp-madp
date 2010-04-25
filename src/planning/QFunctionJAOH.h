/**\file QFunctionJAOH.h
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
 * $Id: QFunctionJAOH.h 3604 2009-08-25 10:52:24Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _QFUNCTIONJOINTHISTORY_H_
#define _QFUNCTIONJOINTHISTORY_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"

#include "QFunctionJAOHInterface.h"
#include "QFunctionForDecPOMDP.h"
#include "QTable.h"

class JointActionObservationHistoryTree;

#define QFunctionJAOH_useIndices 1

/**\brief QFunctionJAOH represents a Q-function that operates on
 * joint action-observation histories. */
class QFunctionJAOH : 
    public QFunctionJAOHInterface //Interface
    , virtual public QFunctionForDecPOMDP //implementation
{
private:    
    
protected:

    ///  Table in which the Qvalues are stored.
    QTable _m_QValues;

    /// See ComputeWithCachedQValuesdQValues(), this version accepts a filename.
    virtual void ComputeWithCachedQValues(std::string filenameCache);

public:
    // Constructor, destructor and copy assignment.
    /// Default constructor, requires a planning unit.
    QFunctionJAOH(const PlanningUnitDecPOMDPDiscrete &pu);

    /// Destructor.
    //virtual ~QFunctionJAOH(){};

    /// Compute Qvalue function, while caching the Qvalues to disk.
    /** Before computing them, the function checks whether the Qvalues
     * have been computed before, and if so, loads them from disk. If
     * not, it computes them, and afterwards saves them for re-use.
     */
    void ComputeWithCachedQValues();

};


#endif /* !_QFUNCTIONJOINTHISTORY_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
