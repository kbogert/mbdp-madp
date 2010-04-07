/**\file ProblemFireFighting.h
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
 * $Id: ProblemFireFighting.h 3611 2009-08-25 15:02:24Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _PROBLEMFIREFIGHTING_H_
#define _PROBLEMFIREFIGHTING_H_ 1

/* the include directives */
#include "Globals.h"
#include "DecPOMDPDiscrete.h"
#include "IndexTools.h"

/** \brief ProblemFireFighting is a class that represents 
 * the firefighting problem as described in #refGMAA (DOC-references.h).
 * */
class ProblemFireFighting : public DecPOMDPDiscrete
{
    private: 
        enum observation_t { FLAMES, NOFLAMES };
        size_t _m_nrAgents;
        size_t _m_nrHouses;
        size_t _m_nrFireLevels;
        bool _m_includePositions;

        size_t _m_nrStateFeatures;
        //vector that stores the number of values per state feature.
        std::vector<size_t> _m_nrPerStateFeatureVec;

        size_t _m_nrJointFirelevels;
        //vector that stores the number of values per state feature.
        std::vector<size_t> _m_nrFLs_vec;
        
        ///Construct all the Actions and actionSets (the vector _m_actionVecs).
        void ConstructActions();
        ///Construct all the observations and observation sets.
        void ConstructObservations();
        ///Fills the transition model with the  problem transitions.
        void FillTransitionModel();
        ///Fills the observation model with the  problem obs. probs.
        void FillObservationModel();
        ///Fills the reward model with the  problem rewards.
        void FillRewardModel();
    
        size_t NumberOfContainedStartPositions(const 
                std::vector<Index>& state) const;
    protected:
        static std::string SoftPrintBriefDescription(
                size_t nrAgents, size_t nrHouses, size_t nrFLs);
        static std::string SoftPrintDescription(size_t nrAgents,
                size_t nrHouses, size_t nrFLs);
        std::vector< Index> GetStateVector(Index sI) const
        {
            return IndexTools::JointToIndividualIndices
                (sI, _m_nrPerStateFeatureVec );
        }
        double ComputeTransitionProb(
                const std::vector< Index>& s1,
                const std::vector< Index>& ja,
                const std::vector< Index>& s2
                ) const;        
        double ComputeObservationProb(
                const std::vector< Index>& ja,
                const std::vector< Index>& s1,
                const std::vector< Index>& jo
                ) const;
        double ComputeReward(Index sI) const;
        //is a neighbor of house hI burning?
        static bool isNeighborBurning( const std::vector< Index>& s1, 
                Index hI) ;

    
    public:
        // Constructor, destructor and copy assignment.
        /// (default) Constructor
        ProblemFireFighting(size_t nrAgents, size_t nrHouses, size_t nrFLs,
                double costOfMove=0.0, bool forcePositionRepres = false);
};


#endif /* !_PROBLEMFIREFIGHTING_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
