/**\file BGforStageCreation.h
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
 * $Id: BGforStageCreation.h 3604 2009-08-25 10:52:24Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _BGFORSTAGECREATION_H_
#define _BGFORSTAGECREATION_H_ 1

/* the include directives */
#include "Globals.h"
class PlanningUnitMADPDiscrete;
class JointPolicyDiscretePure;
/** \brief BGforStageCreation is a class that provides some functions to
 * aid the construction of Bayesian games for a stage of a Dec-POMDP.
 *
 * this is a dummy class that only contains static functions.
 * (but by inheriting from this, derived classes can use these functions)
 *
 * */
class BGforStageCreation 
{
    private:    
    
    protected:
    
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
        PartialJointPolicyDiscretePure* ConstructExtendedPolicy(
                PartialJointPolicyDiscretePure & jpolPrevTs 
                , JointPolicyDiscretePure& jpolBG
                , std::vector<size_t>& nrOHts
                , std::vector<Index>& firstOHtsI);
         * */

        /**Fills the (empty) vector firstOHtsI, with the indices (for each 
         * agent) of the first observation history of time step ts.*/
        void  Fill_FirstOHtsI(const PlanningUnitMADPDiscrete* pu, 
                Index ts, std::vector<Index>& firstOHtsI);
        /**Fills the array of joint observation given the individual types and
         * offsets (firstOHtsI).*/
        void Fill_joI_Array(const PlanningUnitMADPDiscrete* pu, 
                const Index ts, const std::vector<Index>& indTypes, 
                const std::vector<Index>& firstOHtsI, Index* joI_arr);
        /**Gets the joint observation history from joI_Array.*/
        //const JointObservationHistoryTree* Get_joht(const Index ts, 
                //const Index* joI_arr);
        /**Fills the array jaI_arr with the joint actions taken for the
         * JOHs as specified by the array of joint observations joIs
         * according to jpolPrevTs.*/
        void Fill_jaI_Array(const PlanningUnitMADPDiscrete* pu, 
                Index ts, Index joIs[], 
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
        //void ProbRewardForjoahI(
                //Index ts, Index jtI, Index* jaI_arr, Index* joI_arr, 
                //Index& jaohI, double& PjaohI, double& ExpR_0_prevTS_thisJAOH );

    public:
/*        
        // Constructor, destructor and copy assignment.
        /// (default) Constructor
        BGforStageCreation();
        /// Copy constructor.
        BGforStageCreation(const BGforStageCreation& a);
        /// Copy assignment operator
        BGforStageCreation& operator= (const BGforStageCreation& o);
*/        
        /// Destructor.
        virtual ~BGforStageCreation(){};

        //operators:

        //data manipulation (set) functions:
        
        //get (data) functions:
};


#endif /* !_BGFORSTAGECREATION_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
