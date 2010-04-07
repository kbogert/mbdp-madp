/**\file JointObservationDiscrete.h
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
 * $Id: JointObservationDiscrete.h 4016 2010-03-11 16:56:02Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _JOINTOBSERVATIONINTEGER_H_
#define _JOINTOBSERVATIONINTEGER_H_ 1

/* the include directives */

#include <iostream>
#include <vector>
#include "Globals.h"
#include "JointObservation.h"
#include "DiscreteEntity.h"

class ObservationDiscrete;

/// JointObservationDiscrete represents discrete joint observations.
class JointObservationDiscrete : public JointObservation,
                                 public DiscreteEntity
{
    private:
    
    
    protected:

    ///Pointers to individual observations that make up this joint observation.
    std::vector<Index> _m_oIndexVector;    
    ///Indices of individual observations that make up this joint observation.
    std::vector<const ObservationDiscrete*> _m_opVector;
    /// Constructs the vector of individual Observation indices from _m_apVector
    std::vector<Index> ConstructIndividualObservationDiscretesIndices() const;
    
    public:
        // Constructor, destructor and copy assignment.
        /// (default) Constructor
        JointObservationDiscrete(Index index = 0);
        /// Constructor with an index and a vector of individual observations.
        JointObservationDiscrete(Index index, std::vector<const ObservationDiscrete*> a);
        /// Copy constructor.
        JointObservationDiscrete(const JointObservationDiscrete& a);
        /// Destructor.
        ~JointObservationDiscrete();

        //operators:

        /// Adds an individual observation for agentI to this joint observation.
        /** This has to be called ordered: i.e., first for agent 0,
         * then for agent 1, etc.  up to nrAgents. This function is
         * also typically only used to construct the joint
         * observations.*/
        void AddIndividualObservation(const ObservationDiscrete* a, Index agentI);
        
        //get (data) functions:

        /// Get the ObservationDiscretes for this joint action.
        const std::vector<const ObservationDiscrete*>& 
            GetIndividualObservationDiscretes() const
        { return _m_opVector;}
        /// Get the Observation indices for this joint action.
        const std::vector<Index>& GetIndividualObservationDiscretesIndices() const
        { return _m_oIndexVector; }

        /// Returns a pointer to a copy of this class.
        virtual JointObservationDiscrete* Clone() const
        { return new JointObservationDiscrete(*this); }

        //other
        std::string SoftPrint() const;
        std::string SoftPrintBrief() const;
};


#endif /* !_JOINTOBSERVATIONINTEGER_H_ */


// Local Variables: ***
// mode:c++ ***
// End: ***
