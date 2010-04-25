/**\file IndividualBeliefJESP.h
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
 * $Id: IndividualBeliefJESP.h 3604 2009-08-25 10:52:24Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _INDIVIDUALBELIEFJESP_H_
#define _INDIVIDUALBELIEFJESP_H_ 1

/* the include directives */
#include <iostream>
#include <vector>
#include "Globals.h"
#include "IndexTools.h"
#include "Belief.h"

class JointPolicyPureVector;
class PlanningUnitMADPDiscrete; //forward declaration to avoid including each other

/**
 * \brief IndividualBeliefJESP stores individual beliefs for the JESP
 * algorithm.
 */
class IndividualBeliefJESP :
        public Belief
{
private:  
    ///pointer to PlanningUnitMADPDiscrete 
    /**(might be 0 when this belief is not associated with a PUMADP)
     */
    const PlanningUnitMADPDiscrete* _m_pumadp;
    ///The time step this belief belongs to.
    Index _m_stage;
    ///the number of agents    
    size_t _m_nrAgents;
    ///The agent for which this belief is
    Index _m_agentI;
    ///The scope of the others
    std::vector<Index> _m_others;
    ///The number of observation histories of agents != _m_agentI
    std::vector<size_t> _m_nrOH_others;
    ///a vector describing the size of the belief: _m_sizeVec=<nrS,nrJOHothers>
    std::vector<size_t> _m_sizeVec;
    ///the step-size cache for eIndex <-> <S, joHistJ>  conversion
    size_t * _m_stepsizeSJOH;
    ///the step-size cache for joHistJ <-> <oHist1,...oHistnrA> conversion
    size_t * _m_stepsizeJOHOH;
    
protected:
    
public:        
        
    /**This constructor usess it arguments to set additional information
     */
    IndividualBeliefJESP(Index agentI, Index stage,
        const PlanningUnitMADPDiscrete& pu);
    // Constructor which copies \a belief in this joint belief.
    // IndividualBeliefJESP(const IndividualBeliefJESPInterface &belief);

    /// Destructor
    ~IndividualBeliefJESP();

    IndividualBeliefJESP& operator= (const IndividualBeliefJESP& o);

    // Constructor, destructor and copy assignment.

    ///The individual belief update
    /**This gets only an \em individual action \a lastAI and \em individual
     * observation \a newOI, as its arguments.
     */
    double Update(const IndividualBeliefJESP& b_prev, Index lastAI, 
            Index newOI, const JointPolicyPureVector* jpol);

    ///Get the state corresponding to augmented state index eI
    Index GetStateIndex(Index eI) const;
    ///Get the vector with others' observation history indices cor.to eI
    std::vector<Index> GetOthersObservationHistIndex(Index eI) const;
    //
    Index GetAugmentedStateIndex(Index sI, 
            const std::vector<Index>& oHist_others) const;

    std::string SoftPrint() const;
    void Print() const
    { std::cout << SoftPrint();};

};

inline
Index
IndividualBeliefJESP::GetStateIndex(Index eI) const
{
    std::vector<Index> v = 
        IndexTools::JointToIndividualIndicesStepSize(eI, _m_stepsizeSJOH, 2);
    return v.at(0);
}



#endif /* !_INDIVIDUALBELIEFJESP_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
