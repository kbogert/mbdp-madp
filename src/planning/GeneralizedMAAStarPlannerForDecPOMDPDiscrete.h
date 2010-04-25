/**\file GeneralizedMAAStarPlannerForDecPOMDPDiscrete.h
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
 * $Id: GeneralizedMAAStarPlannerForDecPOMDPDiscrete.h 3614 2009-08-25 15:59:51Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _GENERALIZEDMAASTARPLANNERFORDECPOMDPDISCRETE_H_
#define _GENERALIZEDMAASTARPLANNERFORDECPOMDPDISCRETE_H_ 1

/* the include directives */
#include <iostream>
#include <time.h>
#include <sys/times.h>
#include <fstream>

//#include "Globals.h"
#include "PlanningUnitDecPOMDPDiscrete.h"
#include "GeneralizedMAAStarPlanner.h"

//needed becaise of inline at bottom of file
#include "QFunctionJAOHInterface.h"



/**\brief GeneralizedMAAStarPlannerForDecPOMDPDiscrete is a class that 
 * represents the Generalized MAA* planner.
 *
 * This implements GMAA pretty much as described in #refGMAA (see
 * DOC-References.h).  The 'NEXT'  as described in #refGMAA, is called
 * 'ConstructAndValuateNextPolicies'.
 *
 * Additionally there is a function 'SelectPoliciesToProcessFurther'. (not to
 * be confused with the 'SELECT' function from #refGMAA !!!) Given the result
 * of ConstructAndValuateNextPolicies, SelectPoliciesToProcessFurther
 * determines which of these will actually be added to the policy pool. I.e.,
 * ConstructAndValuateNextPolicies and SelectPoliciesToProcessFurther together
 * form 'NEXT'.
 *
 * The 'SELECT' function as described in #refGMAA is implemented by the policy
 * pool (see PartialPolicyPoolInterface) itself.
 * \todo....
 *
 * This class also implements a 'NEXT' and 'SELECT' functions that can be used
 * by derived classes.
 *
 *
 * \sa GMAA_MAAstar, GMAA, PartialPolicyPoolInterface
 *
 * */
class GeneralizedMAAStarPlannerForDecPOMDPDiscrete :
    public PlanningUnitDecPOMDPDiscrete, //don't make virtual (everything will fail!
    public GeneralizedMAAStarPlanner
{
    private:    
    protected:
        ///A pointer to the heuristic used by this 
        //GeneralizedMAAStarPlannerForDecPOMDPDiscrete
        QFunctionJAOHInterface* _m_qHeuristic;

//Functions that can be overriden by derived classes to influence the working of
//GMAA:
        
        /// Returns a new policy of the type used by the GMAA implementation
        virtual PartialJointPolicyDiscretePure* NewJPol() const;
        ///Return a new PartialPolicyPoolItemInterface*.
        /**This function returns a pointer to new instance of the 
         * PartialPolicyPoolItemInterface used by this class.
         */
        virtual PartialPolicyPoolItemInterface* NewPPI(PartialJointPolicyDiscretePure* jp,
                double v) const;
        ///Return a new PartialPolicyPoolInterface*.
        /**This function returns a pointer to new instance of the 
         * PartialPolicyPoolInterface used by this class.
         */
        virtual PartialPolicyPoolInterface* NewPP() const;

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
         * firstOHtsI - a vector that specifies the index of the first 
         *              observation history in time step ts for each agent 
         *              (this functions
         *              as the offset in the conversion BG->DecPOMDP index 
         *              conversion).
         *
         * returns a new JointPolicyPureVector (so it must be explicitly 
         * deleted)
         * */
        virtual PartialJointPolicyDiscretePure* ConstructExtendedJointPolicy(
                const PartialJointPolicyDiscretePure& jpolPrevTs
                , const JointPolicyDiscretePure& jpolBG
                , const std::vector<size_t>& nrOHts
                , const std::vector<Index>& firstOHtsI);


        inline
        double GetHeuristicQ(Index joahI, Index jaI) const;

    public:
        // Constructor, destructor and copy assignment.
        /// (default) Constructor
        GeneralizedMAAStarPlannerForDecPOMDPDiscrete(
            const PlanningUnitMADPDiscreteParameters &params,
            size_t horizon=3, 
            DecPOMDPDiscreteInterface* p=0,
            int verbose_level=0
            );

        GeneralizedMAAStarPlannerForDecPOMDPDiscrete(
            size_t horizon=3, 
            DecPOMDPDiscreteInterface* p=0);

        /// Destructor.
        //~GeneralizedMAAStarPlannerForDecPOMDPDiscrete();
        /// Copy assignment operator
        GeneralizedMAAStarPlannerForDecPOMDPDiscrete& operator=(const 
                GeneralizedMAAStarPlannerForDecPOMDPDiscrete& o);
        
        void SetQHeuristic(QFunctionJAOHInterface& q)
            {_m_qHeuristic = &q;}
        void SetQHeuristic(QFunctionJAOHInterface* q)
            {_m_qHeuristic = q;}

        virtual GeneralizedMAAStarPlannerForDecPOMDPDiscrete* 
            GetThisFromMostDerivedPU()
        { return this; }
        //some functions necessary because we derive from 
        //PlanningUnitDecPOMDPDiscrete
        void Plan() 
        {   GeneralizedMAAStarPlanner::Plan();  }
        double GetExpectedReward() const 
        {   return GeneralizedMAAStarPlanner::GetExpectedReward();  }
        JointPolicy* GetJointPolicy()
        {   return GeneralizedMAAStarPlanner::GetJointPolicy();    }
        
};

inline
double GeneralizedMAAStarPlannerForDecPOMDPDiscrete::
GetHeuristicQ(Index joahI, Index jaI) const
{return(_m_qHeuristic->GetQ(joahI, jaI));}



#endif /* !_GENERALIZEDMAASTARPLANNERFORDECPOMDPDISCRETE_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
