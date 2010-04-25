/**\file JointActionDiscrete.h
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
 * $Id: JointActionDiscrete.h 4016 2010-03-11 16:56:02Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _JOINTACTIONINTEGER_H_
#define _JOINTACTIONINTEGER_H_ 1

/* the include directives */

#include <iostream>
#include "Globals.h"
#include "JointAction.h"
#include "DiscreteEntity.h"

class ActionDiscrete;

/// JointActionDiscrete represents discrete joint actions.
class JointActionDiscrete : public JointAction,
                            public DiscreteEntity
{
    private:
    
    /// Pointers to the individual actions that make up this joint action.
    std::vector<Index> _m_aIndexVector;    
    /// Indices of the individual actions that make up this joint action.
    std::vector<const ActionDiscrete*> _m_apVector;
    /// Constructs the vector of individual Action indices from _m_apVector
    std::vector<Index> ConstructIndividualActionDiscretesIndices() const;

    protected:


    
    public:
    // Constructor, destructor and copy assignment.
    /// (default) Constructor
    JointActionDiscrete(Index index = 0);
    /// Constructor with an index and a vector of individual actions.
    JointActionDiscrete(Index index, std::vector<const ActionDiscrete*> a);
    /// Copy constructor.
    JointActionDiscrete(const JointActionDiscrete& a);
    /// Destructor.
    ~JointActionDiscrete();

    //operators:

    //data manipulation (set) functions
    /// Deletes the individual actions to which this joint action points.
    /** This function will typically *NOT* be used: normally multiple
     * joint actions share their individual actions...*/
    void DeleteIndividualActions();

    /// Adds an individual action for agentI to this joint action.
    /** This has to be called ordered: i.e., first for agent 0, then
     * for agent 1, etc.  up to nrAgents. This function is also
     * typically only used to construct the joint actions.*/
    void AddIndividualAction(const ActionDiscrete* a, Index agentI);
    
    //get (data) functions:
    /// Get the ActionDiscretes for this joint action.
    const std::vector<const ActionDiscrete*>& GetIndividualActionDiscretes() const
    { return(_m_apVector);}
    /// Get the Action indices for this joint action.
    const std::vector<Index>& GetIndividualActionDiscretesIndices() const
    { return(_m_aIndexVector);}
    /// Returns a pointer to a copy of this class.
    virtual JointActionDiscrete* Clone() const
        { return new JointActionDiscrete(*this); }

    //other
    std::string SoftPrint() const;
    std::string SoftPrintBrief() const;
};


#endif /* !_JOINTACTIONINTEGER_H_ */


// Local Variables: ***
// mode:c++ ***
// End: ***
