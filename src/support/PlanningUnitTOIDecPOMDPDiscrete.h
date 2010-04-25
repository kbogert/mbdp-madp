/**\file PlanningUnitTOIDecPOMDPDiscrete.h
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
 * $Id: PlanningUnitTOIDecPOMDPDiscrete.h 3604 2009-08-25 10:52:24Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _PLANNINGUNITTOIDECPOMDPDISCRETE_H_
#define _PLANNINGUNITTOIDECPOMDPDISCRETE_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"
#include "Referrer.h"
#include "PlanningUnitDecPOMDPDiscrete.h"
#include "TOIDecPOMDPDiscrete.h"

class JointPolicyPureVector;

/** \brief PlanningUnitTOIDecPOMDPDiscrete represents a planning unit for
 * transition observation independent discrete Dec-POMDPs. */
class PlanningUnitTOIDecPOMDPDiscrete : 
    public Referrer<TOIDecPOMDPDiscrete>,
    public PlanningUnitDecPOMDPDiscrete 
{
private:

    bool SanityCheck() const;

protected:
    
public:
    // Constructor, destructor and copy assignment.
    ///the (default) Constructor. 
    PlanningUnitTOIDecPOMDPDiscrete(
        const PlanningUnitMADPDiscreteParameters &params,
        size_t horizon=3,
        TOIDecPOMDPDiscrete* p=0
        );
        
    PlanningUnitTOIDecPOMDPDiscrete(
        size_t horizon=3,
        TOIDecPOMDPDiscrete* p=0
        );

    //operators:
    
    //data manipulation (set) functions:
    
    /// Tell which SetReferred to use by default.
    void SetReferred(TOIDecPOMDPDiscrete* p) 
        {Referrer<TOIDecPOMDPDiscrete>::SetReferred(p);}
    ///Set the problem (TOIDecPOMDPDiscrete) using a pointer.
    void SetProblem(TOIDecPOMDPDiscrete* p);

    //get (data) functions:
    
    /// Returns the TOIDecPOMDPDiscrete pointer.
    /** Tell which GetReferred to use by default... (nl. the
     * Referrer<TOIDecPOMDPDiscrete>::GetReferred(), not the
     * PlanningUnitMADPDiscrete::GetReferred(). */
    TOIDecPOMDPDiscrete* GetReferred() const
        {return(Referrer<TOIDecPOMDPDiscrete>::GetReferred() );}

    /**\brief returns a vector of individual (local) state indices
     * corresponding to joint state index jointSI.*/
    const std::vector<Index>& JointToIndividualStateIndices(Index jointSI) const
        { return(GetReferred()->JointToIndividualStateIndices(jointSI)); }

    /**\brief returns the joint index for indivStateIndices*/
    Index IndividualToJointStateIndices(const std::vector<Index>&
                                        indivStateIndices) const
        { return(GetReferred()->IndividualToJointStateIndices(indivStateIndices)); }

    std::vector<Index> SampleSuccessorState(const std::vector<Index> &sIs,
                                             const std::vector<Index> &aIs)
        const
        { return(GetReferred()->SampleSuccessorState(sIs,aIs)); }
                                             
    std::vector<Index> SampleJointObservation(const std::vector<Index> &aIs,
                                               const std::vector<Index> &sucIs)
        const
        { return(GetReferred()->SampleJointObservation(aIs,sucIs)); }

    std::vector<Index> SampleInitialStates(void) const
        { return(GetReferred()->SampleInitialStates()); }

};


#endif /* !_PLANNINGUNITTOIDECPOMDPDISCRETE_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
