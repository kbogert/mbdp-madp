/**\file PlanningUnitMADPDiscreteParameters.h
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
 * $Id: PlanningUnitMADPDiscreteParameters.h 3604 2009-08-25 10:52:24Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _PLANNINGUNITMADPDISCRETEPARAMETERS_H_
#define _PLANNINGUNITMADPDISCRETEPARAMETERS_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"

/** \brief PlanningUnitMADPDiscreteParameters stores parameters of
 * PlanningUnitMADPDiscrete. 
 *
 * It controls which types of histories are generated when
 * initializing the PlanningUnitMADPDiscrete. What to generate depends
 * on the particular planning algorithm derived from it, for instance,
 * some algorithms use joint beliefs, others don't (in which case
 * there is no point in generating and storing them). This class also
 * indicates whether joint beliefs should represented sparsely or not.
 **/
class PlanningUnitMADPDiscreteParameters 
{
private:    

    /// Generate individual observation histories or not.
    bool _m_individualObservationHistories;
    /// Generate individual action histories or not.
    bool _m_individualActionHistories;
    /// Generate individual action-observation histories or not.
    bool _m_individualActionObservationHistories;
    /// Generate joint observation histories or not.
    bool _m_jointObservationHistories;
    /// Generate joint action histories or not.
    bool _m_jointActionHistories;
    /** \brief Whether or not joint action observation histories are
     * generated and stored.
     * 
     * If they are stored, also their (conditional) probabilities are
     * cached.*/
    bool _m_jointActionObservationHistories;
    /** \brief Whether joint beliefs are cached.
     *
     * Only applicable when jointActionObservationHistories are
     * generated.).*/
    bool _m_JointBeliefs;
    /// Use sparse beliefs or the full representation.
    bool _m_useSparseBeliefs;



protected:
    
public:
    /// Ensures no illegal combination of parameters has been set.
    /**Sanity check is called by the constructor of PlanningUnitMADPDiscrete.
     * 
     * The old procedure "Is called after each call to a Set function."
     * made no sense, as it was not possible to do 
     *      params.SetComputeJointActionHistories(false);
     *      params.SetComputeJointBeliefs(false);
     * as it started complaining at the first call...
     * */
    void SanityCheck() const;


    // Constructor, destructor and copy assignment.
    /// Default constructor.
    /** By default, all histories are generated, joint beliefs are
     * cached and not represented sparsely. */
    PlanningUnitMADPDiscreteParameters();
    /// Destructor.
    ~PlanningUnitMADPDiscreteParameters();

    /// Switch on or off the generation of all joint histories.
    void SetComputeAllJointHistories(bool val);
    /// Switch on or off the generation of all individual histories.
    void SetComputeAllIndividualHistories(bool val);
    /// Switch on or off the generation of all histories.
    void SetComputeAll(bool val);

    /// Switch on or off the generation of individual observation histories.
    void SetComputeIndividualObservationHistories(bool val){
        _m_individualObservationHistories = val; 
    }
    
    /// Switch on or off the generation of individual action histories.
    void SetComputeIndividualActionHistories(bool val){
        _m_individualActionHistories = val; 
    }
    
    /// Switch on or off the generation of individual action-observation histories.
    void SetComputeIndividualActionObservationHistories(bool val){
        _m_individualActionObservationHistories = val; 
    }
    
    /// Switch on or off the generation of joint observation histories.
    void SetComputeJointObservationHistories(bool val){
        _m_jointObservationHistories = val; 
    }
    
    /// Switch on or off the generation of joint action histories.
    void SetComputeJointActionHistories(bool val){
        _m_jointActionHistories = val; 
    }
    
    /// Switch on or off the generation of joint action-observation histories.
    void SetComputeJointActionObservationHistories(bool val){
        _m_jointActionObservationHistories = val; 
    }
    
    /// Switch on or off storing the joint beliefs.
    void SetComputeJointBeliefs(bool val){
        _m_JointBeliefs = val; 
    }

    /// Switch on or off whether joint beliefs should be represented sparsely.
    void SetUseSparseJointBeliefs(bool val){
        _m_useSparseBeliefs = val; 
    }

    /// Are individual observation histories generated or not.
    bool GetComputeIndividualObservationHistories() const{
        return(_m_individualObservationHistories);
    }

    /// Are individual action histories generated or not.
    bool GetComputeIndividualActionHistories() const{
        return(_m_individualActionHistories);
    }

    /// Are individual action-observation histories generated or not.
    bool GetComputeIndividualActionObservationHistories() const{
        return(_m_individualActionObservationHistories);
    }

    /// Are joint observation histories generated or not.
    bool GetComputeJointObservationHistories() const{
        return(_m_jointObservationHistories);
    }

    /// Are joint action histories generated or not.
    bool GetComputeJointActionHistories() const{
        return(_m_jointActionHistories);
    }

    /// Are joint action-observation histories generated or not.
    bool GetComputeJointActionObservationHistories() const{
        return(_m_jointActionObservationHistories);
    }

    /// Are the joint beliefs cached or not.
    bool GetComputeJointBeliefs() const{
        return(_m_JointBeliefs);
    }

    /// Are sparse beliefs used or not.
    bool GetUseSparseJointBeliefs() const{
        return(_m_useSparseBeliefs);
    }

    /// Print out the parameters to cout.
    void Print() const;

};


#endif /* !_PLANNINGUNITMADPDISCRETEPARAMETERS_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
