/**\file GeneralizedMAAStarPlanner.h
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
 * $Id: GeneralizedMAAStarPlanner.h 3614 2009-08-25 15:59:51Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _GENERALIZEDMAASTARPLANNER_H_
#define _GENERALIZEDMAASTARPLANNER_H_ 1

/* the include directives */
#include <iostream>
#include <time.h>
#include <sys/times.h>
#include <fstream>
#include "Globals.h"
#include "TimedAlgorithm.h"

//use forward declarations when possible to speed up compilation:
//class PlanningUnitDecPOMDPDiscrete;
//class BayesianGameIdenticalPayoff;

//class JPolValPair;
//class QFunctionJAOHInterface;
//class TimedAlgorithm;
//class PolicyPoolJPolValPair;

class PartialPolicyPoolInterface;
class PartialPolicyPoolItemInterface;

class JointPolicy;
class JointPolicyDiscrete;
class JointPolicyDiscretePure;
class JointPolicyPureVector;
class PartialJointPolicyDiscretePure;
class PartialJointPolicyPureVector;

class Interface_ProblemToPolicyDiscretePure;
// keep these in header file so derived classes can use them
#define DEBUG_GMAA3 0
#define DEBUG_GMAA4 0
#define DEBUG_GMAA5 0

/**\brief GeneralizedMAAStarPlanner is a class that represents the Generalized
 * MAA* planner class.
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
class GeneralizedMAAStarPlanner :
    public TimedAlgorithm
{

    private:
    protected:
        ///the best found policy
        JointPolicyDiscretePure* _m_foundPolicy;
        ///the expected reward of the best found policy
        double _m_expectedRewardFoundPolicy;


        ///the level of verboseness, default=0, >0 verbose, <0 silent
        int _m_verboseness;

        /**a counter that maintains the maximum size of the policy pool during 
         * the planning process.*/
        LIndex _m_maxJPolPoolSize;

        /**Pointer to an file stream to store the intermediate (timing) results.
         * */
        std::ofstream* _m_intermediateResultFile;

        bool _m_useSparseBeliefs;

        bool _m_saveIntermediateTiming;
        std::string _m_intermediateTimingFilename;

        size_t _m_bgCounter;
        std::string _m_bgBaseFilename;

        /*the # of joint policies for Bayesian Games that are evaluated.*/
        LIndex _m_nrJPolBGsEvaluated;
    
        size_t _m_nrPoliciesToProcess;

        /**when the heuristic is not admissible, or the past reward is an approximation,
         * we may add some slack such that good policies are not pruned
         */
        double _m_slack;

        ///every derived class must implement this function as follows:
        /**GetThisFromMostDerivedPU()
         * { return this; }
         * Giving us access to the Interface_ProblemToPolicyDiscretePure
         * in this base class.
         */
        virtual Interface_ProblemToPolicyDiscretePure* 
            GetThisFromMostDerivedPU() = 0;

        // The 'NEXT' and 'SELECT' functions
    
        /**\brief The 'NEXT' function as described in #refGMAA.
         *
         * The function that from a given <jpol,val> pair construct a new
         * (ordered by value->priority_queue) set of joint policies.
         * This function should be overriden in derived classes to get 
         * different planning behavior.*/
        virtual bool ConstructAndValuateNextPolicies(
                PartialPolicyPoolItemInterface* ppi, PartialPolicyPoolInterface*
                poolOfNextPolicies)=0;

        /**\brief Limits the policies to be further examined. 
         *
         * Of the <jpol,val> pairs found by ConstructAndValuateNextPolicies,
         * we may not want to process all of them further. This function 
         * performs a selection.
         * This function should be overriden in derived classes to get 
         * different planning behavior.*/
        virtual void SelectPoliciesToProcessFurther( PartialPolicyPoolInterface*
                poolOfNextPolicies, bool are_LBs, double bestLB)=0;

        /**\brief return a new policy pool.
         *
         * this function must be implemented by a derived class and return a
         * pointer to a PartialPolicyPoolInterface object. This way,the derived class
         * can determine the implementation of the policy pools used and thus
         * the 'SELECT' functions as described in #refGMAA.
         *
         * it returns a pointer to a PartialPolicyPoolInterface that is created by
         * 'new' therefore, do not forget to 'delete'!!
         */
        virtual PartialPolicyPoolInterface* NewPP()const=0;
        /**\brief return a new policy pool item. 
         *
         * This function must be implemented by a derived class and return a
         * pointer to a newly created PolicyPoolItem object. This way,the
         * derived class can determine the implementation of the policy pools
         * used and thus the 'SELECT' functions as described in #refGMAA.
         *
         * it returns a pointer to a PartialPolicyPoolInterface that is created by
         * 'new' therefore, do not forget to 'delete'!!
         */
//        virtual PartialPolicyPoolItemInterface* NewPPI()=0;
        /**\brief Overloaded form of NewPP().
         *
         * Creates a PartialPolicyPoolItemInterface which contains joint policy p,
         * with value v.*/
        virtual PartialPolicyPoolItemInterface* NewPPI(
                PartialJointPolicyDiscretePure* p,
                double v) const=0;

        /**\brief return a new policy.
         *
         * Different versions of GMAA may make use of different implementations
         * of policies.
         * This function must be implemented by a derived class and return a
         * pointer to a newly created PolicyPoolItem object. This way,the
         * derived class can determine the implementation of the policy. 
         *
         * it returns a pointer to a PartialJointPolicyDiscretePure that is 
         * created by
         * 'new' therefore, do not forget to 'delete'!!
         */
        virtual PartialJointPolicyDiscretePure* NewJPol() const=0;


        /**\brief Returns the k best-ranked (partial) joint policies.
         *
         * An implementation of the 'SELECT' function, that returns the 
         * k (partial) joint policies with the highest heuristic values. */
        void SelectKBestPoliciesToProcessFurther(
        PartialPolicyPoolInterface* poolOfNextPolicies, bool are_LBs,
            double bestLB, size_t k);


        //auxiliary functions -\todo TODO all these functions are now performed in BayesianGameForDecPOMDPStage, this class should use that class.

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
                , const std::vector<Index>& firstOHtsI) = 0;
/* this uses GetNrAgents() and should therefore not be put here...
        //for convenience we also provide a possible implementation here
        PartialJointPolicyPureVector* ConstructExtendedJointPolicyPureVector(
                PartialJointPolicyPureVector& jpolPrevTs
                , JointPolicyPureVector& jpolBG
                , const std::vector<size_t>& nrOHts
                , const std::vector<Index>& firstOHtsI);
*/


        void Prune(PartialPolicyPoolInterface& JPVs, size_t k);
        
    public:
        // Constructor, destructor and copy assignment.
        /// (default) Constructor
        GeneralizedMAAStarPlanner(
            int verbose_level=0,
            double slack = 0.0
            );


        /// Destructor.
        ~GeneralizedMAAStarPlanner();
        /// Copy assignment operator
        GeneralizedMAAStarPlanner& operator=(const 
                GeneralizedMAAStarPlanner& o);
        //operators:

        //data manipulation (set) functions:

        void SetIntermediateResultFile(std::ofstream& of)
            {_m_intermediateResultFile = &of;}
        void SetIntermediateTimingFilename(std::string filename);
        void SetSaveAllBGs(std::string filename)
            { _m_bgBaseFilename=filename; }
        void SetVerbose(int verbose);

        void Plan();
        
        //get (data) functions:
        //do not define these functions here (that requires inclusion of 
        //header files...)
        JointPolicy* GetJointPolicy();
            //{ return(_m_foundPolicy); }
        JointPolicyDiscrete* GetJointPolicyDiscrete();
            //{ return(_m_foundPolicy); }
        JointPolicyDiscretePure* GetJointPolicyDiscretePure();
            //{ return(_m_foundPolicy); }

        double GetExpectedReward() const
            { return(_m_expectedRewardFoundPolicy); }
        LIndex GetMaxJPolPoolSize() const
            { return(_m_maxJPolPoolSize);}
        LIndex GetNrEvaluatedJPolBGs() const
        {return  _m_nrJPolBGsEvaluated;}
};


#endif /* !_GENERALIZEDMAASTARPLANNER_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
