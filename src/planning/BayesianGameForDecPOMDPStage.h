/**\file BayesianGameForDecPOMDPStage.h
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
 * $Id: BayesianGameForDecPOMDPStage.h 3614 2009-08-25 15:59:51Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _BAYESIANGAMEFORDECPOMDPSTAGE_H_
#define _BAYESIANGAMEFORDECPOMDPSTAGE_H_ 1

/* the include directives */
#include "Globals.h"
#include "BayesianGameIdenticalPayoff.h"
#include "BayesianGameForDecPOMDPStageInterface.h"

class JointBeliefInterface;
class PlanningUnitDecPOMDPDiscrete;
class PlanningUnitMADPDiscrete;
class JointPolicyDiscretePure;
class PartialJointPolicyDiscretePure;
class JointObservationHistoryTree;
class QFunctionJAOHInterface;


/** \brief BayesianGameForDecPOMDPStage represents a BG for a single stage.  */
class BayesianGameForDecPOMDPStage :
    //virtual 
    public BayesianGameForDecPOMDPStageInterface,
    public BayesianGameIdenticalPayoff
{
    private:    

    
    protected:

        ///Stores pointer to the PU.
        const PlanningUnitDecPOMDPDiscrete* _m_pu;
        ///A pointer to the heuristic used by this Bayesian game ---nec.?
        const QFunctionJAOHInterface* _m_qHeuristic;
        /// The joint beliefs induced by the joint types.
        std::vector< JointBeliefInterface* > _m_JBs;
        /// are the immediate rewards cached?
        bool _m_areCachedImmediateRewards;
        /// the cache for the immediate rewards: immR[jt][ja]
        std::vector< std::vector<double> > _m_immR;

        ///Initialized the BG - called from constructor.
        /**\brief Given the past policy and q function, the
         * probabilities and utility function are initialized.
         */
        void Initialize();

        /**\brief Extends a previous policy jpolPrevTs to the next stage.
         *
         * This function extends a previous policy jpolPrevTs for ts-1 with the 
         * behavior specified by the policy of the BayesianGame for time step ts
         * (jpolBG).
         * jpolPrevTs - a joint policy for the DecPOMDP up to time step ts-1
         *              (i.e. with depth=ts-2)
         * jpolBG     - a joint policy for the BayesianGame for time step ts.
         * nrOHts     - a vector that specifies the number of observation 
         *              histories
         *              for eac agents at time step ts.
         * firstOHtsI - a vector that specifies the index of the first time step
         *              ts observation history for each agent (this functions
         *              as the offset in the conversion BG->DecPOMDP index 
         *              conversion).
         *
         * returns a new JointPolicyDiscretePure (so it must be explicitly 
         * deleted)
         * */
        PartialJointPolicyDiscretePure* ConstructExtendedPolicy(
                PartialJointPolicyDiscretePure & jpolPrevTs 
                , JointPolicyDiscretePure& jpolBG
                , std::vector<size_t>& nrOHts
                , std::vector<Index>& firstOHtsI);

        /**Fills the (empty) vector firstOHtsI, with the indices (for each 
         * agent) of the first observation history of time step ts.*/
        void  Fill_FirstOHtsI(Index ts, std::vector<Index>& firstOHtsI);
        /**Fills the array of joint observation given the individual types and
         * offsets (firstOHtsI).*/
        void Fill_joI_Array(const Index ts, const std::vector<Index>& indTypes, 
                const std::vector<Index>& firstOHtsI, Index* joI_arr);
        /**Fills the array jaI_arr with the joint actions taken for the
         * JOHs as specified by the array of joint observations joIs
         * according to jpolPrevTs.*/
        void Fill_jaI_Array(Index ts, Index joIs[], 
                const JointPolicyDiscretePure* jpolPrevTs, Index* jaI_arr);
        /**Calculates the jaohI corresponding to jaI_arr and joI_arr and also 
         * returnes the P(jaohI) and the expected obtained reward for previous
         * time steps GIVEN this joint action history.
         *
         * input args
         *  Index ts, Index jtI, Index* jaI_arr,Index* joI_arr, 
         * output args 
         *  Index& jaohI, double& PjaohI, double& ExpR_0_prevTS_thisJAOH 
         *  
         *\todo TODO this is a strange function and should be updated i think...
         * */
        void ProbRewardForjoahI(
                Index ts, Index jtI, Index* jaI_arr, Index* joI_arr, 
                Index& jaohI, double& PjaohI, double& ExpR_0_prevTS_thisJAOH );

        ///Compute the immediate reward for an action and joint type.
        double ComputeImmediateReward(Index jtI, Index jaI) const;

        ///Constructor that only creates a BG of specified dimensions.
        /**This constructor does not initialize the BG. This is useful when
         * there are additional computations that have to be done. E.g., 
         * when this is a clusterable BG (BayesianGameWithClusterInfo), the 
         * types do not correspond in a straigtforward manner to action-observ.
         * histories and therefore the probs. and payoff function have to be
         * computed at this higher level.
         */
        BayesianGameForDecPOMDPStage(
                const PlanningUnitDecPOMDPDiscrete* pu,
                const QFunctionJAOHInterface* q,
                Index t,
                size_t nrAgents,
                const std::vector<size_t>& nrActions,
                const std::vector<size_t>& nrTypes
        );
    public:
        // Constructor, destructor and copy assignment.
        /// Constructor that creates and initializes a BG from scratch.
        /**This constructor creates and initializes a BG for the next stage
         * given the past policy and q function.
         */
        BayesianGameForDecPOMDPStage(
                const PlanningUnitDecPOMDPDiscrete* pu,
                const QFunctionJAOHInterface* q,
                const PartialJointPolicyDiscretePure* pastJPol
        );

        // Constructor, destructor and copy assignment.
        /// Constructor that creates an empty BG.
        BayesianGameForDecPOMDPStage(
                const PlanningUnitDecPOMDPDiscrete* pu
        );
        /// Copy constructor.
        BayesianGameForDecPOMDPStage(const BayesianGameForDecPOMDPStage& a);
        /// Destructor.
        ~BayesianGameForDecPOMDPStage();
        /// Copy assignment operator
        BayesianGameForDecPOMDPStage& operator= (const BayesianGameForDecPOMDPStage& o);

        //operators:

        //data manipulation (set) functions:
 
        /**Returns the (expected) immediate reward for jtI, jaI
         */
        double GetImmediateReward(Index jtI, Index jaI) const
        {
            if(_m_areCachedImmediateRewards)
                return _m_immR.at(jtI).at(jaI);
            else
                return ComputeImmediateReward(jtI, jaI);
        };
        /**When performing a lot of GetImmediateReward calls we can first 
         * compute a cache of immediate rewards, to speed things up.
         */
        void ComputeAllImmediateRewards();
        /**We can also clear this cache.
         */
        void ClearAllImmediateRewards()
        {   
            _m_immR.clear();
            _m_areCachedImmediateRewards = false;
        }
        /**\brief Compute the discounted expected imm reward for jpolBG.
         */
        double ComputeDiscountedImmediateRewardForJPol(
                JointPolicyDiscretePure* jpolBG) const;

       
        //get (data) functions:
        const PlanningUnitDecPOMDPDiscrete* GetPUDecPOMDPDiscrete() const
        {return _m_pu;}
       
        /** Prints a description of this  entire BayesianGameIdenticalPayoff 
         * to a string.*/
        std::string SoftPrint() const; 
        /**Print this BayesianGameIdenticalPayoff to cout.*/
        void Print() const
        { std::cout << SoftPrint();}
};


#endif /* !_BAYESIANGAMEFORDECPOMDPSTAGE_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
	
