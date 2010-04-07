/**\file BayesianGameBase.h
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
 * $Id: BayesianGameBase.h 3611 2009-08-25 15:02:24Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _BAYESIANGAMEBASE_H_
#define _BAYESIANGAMEBASE_H_ 1

/* the include directives */
#include <iostream>
#include <vector>
#include <map>
#include "Globals.h"
#include "Interface_ProblemToPolicyDiscretePure.h"
#include "IndexTools.h"
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/vector_sparse.hpp>

/**\brief BayesianGameBase is a class that represents a Bayesian game.
 *
 * This is a self
 * contained class - meaning that it does not depend on any Multi-agent 
 * decision problem or Planning unit.
 * This implies that, in order to convert a time-step of a MADP Planning
 * Unit to a Bayesian game, indices of observation(-action) histories have
 * to be converted. This class uses its own indices.
 */
class BayesianGameBase :
    public Interface_ProblemToPolicyDiscretePure //this class implements the interface
        //used by PolicyPureVector
{
    private:

        bool _m_useSparse;
        ///the probability distribution over joint types. A mapping from 
        ///joint indices to probabilities
        std::vector<double> _m_jTypeProbs;
        typedef boost::numeric::ublas::mapped_vector<double> SparseVector;
        SparseVector _m_jTypeProbsSparse;

        ///An joint type -> indiv. type indices cache:
        std::vector< std::vector<Index> > *_m_jointToIndTypes;
        ///An joint type -> indiv. type indices cache:
        std::map<Index, std::vector<Index> > *_m_jointToIndTypesMap;

    protected:
        /// private bool to indicate whether this BG is initialized.
        bool _m_initialized;

        /// _m_verboseness >0 verbose, <0 is quiet
        int _m_verboseness;

        ///the number of players (or agents)
        size_t _m_nrAgents;
        ///the number of actions for each agent
        std::vector<size_t> _m_nrActions;
        ///the number of types for each agent
        std::vector<size_t> _m_nrTypes;
        ///the number of joint actions:
        size_t _m_nrJTypes;
        ///the number of joint types:
        size_t _m_nrJA;
        
        ///an size_t array that caches the stepsize array for actions:
        size_t * _m_stepSizeActions;
        ///an size_t array that caches the stepsize array for types:
        size_t * _m_stepSizeTypes;

    public:
        // Constructor, destructor and copy assignment.
        // (default) Constructor
        BayesianGameBase();
        BayesianGameBase(const size_t nrAgents, 
                const std::vector<size_t> & nrActions,  
                const std::vector<size_t> & nrTypes,
                int verboseness=0);
        /// Copy constructor.
        BayesianGameBase(const BayesianGameBase& a);
        /// Destructor.
        ~BayesianGameBase();
        //operators:

        
        //data manipulation (set) functions:
        
        /**\brief Sets the initialized status to b. When setting to true - checks are
         * performed to see if this is a consistent Bayesian Game.*/
        bool SetInitialized(bool b);
        /**\brief Sets the probability of joint type i to p.*/
        void SetProbability(const Index i, const double p)
        { if(_m_useSparse) _m_jTypeProbsSparse[i]=p;
            else _m_jTypeProbs[i]=p;}
        /**\brief Sets the probability of joint type corresponding to the individual
         * type indices (indIndices) to p.*/
        void SetProbability(const std::vector<Index>& indIndices, const double p)
        {SetProbability(IndividualToJointTypeIndices(indIndices), p);}
        /**\brief Adds p to the probability of joint type i*/
        void AddProbability(const Index i, const double p)
            {if(_m_useSparse) _m_jTypeProbsSparse[i]+=p;
                else _m_jTypeProbs[i]+=p;}
        /**\brief Adds p to the probability of joint type corresponding to the 
         * individual type indices (indIndices).*/
        void AddProbability(const std::vector<Index>& indIndices, const double p)
        {AddProbability(IndividualToJointTypeIndices(indIndices), p);}


        //get (data) functions:
        size_t GetNrJointActions() const {return _m_nrJA;};
        size_t GetNrJointTypes() const {return _m_nrJTypes;};
        const std::vector<size_t>& GetNrTypes() const {return _m_nrTypes;}
        size_t GetNrTypes(Index agI) const {return _m_nrTypes.at(agI);}
        
        /**\brief Gets the probability of joint type i*/
        virtual double GetProbability(const Index i) const
        {if (_m_useSparse) return(_m_jTypeProbsSparse[i]);
            else  return(_m_jTypeProbs[i]);}
        /**\brief Gets the probability of joint type corresponding to the individual
         * type indices (indIndices)*/
        double GetProbability(const std::vector<Index>& indIndices)
        {return(GetProbability(IndividualToJointTypeIndices(indIndices)));}


        //indices

        //\todo TODO: Bayesian game caches the step_size etc. so the following
        //should be changed? TODO: <--- check this
        Index IndividualToJointActionIndices(const Index* IndArr)const
        { return IndexTools::IndividualToJointIndicesArrayStepSize(IndArr, 
                _m_stepSizeActions, _m_nrAgents);};
        Index IndividualToJointActionIndices(const std::vector<Index>& indices)
            const
        { return IndexTools::IndividualToJointIndicesStepSize(indices, 
                _m_stepSizeActions);};

        Index IndividualToJointTypeIndices(const std::vector<Index>& indices) const
        { return IndexTools::IndividualToJointIndicesStepSize(indices, 
                _m_stepSizeTypes);};
        std::vector<Index> JointToIndividualActionIndices(Index jaI) const
        { return IndexTools::JointToIndividualIndicesStepSize(jaI, 
                _m_stepSizeActions, _m_nrAgents);};
/*      std::vector<Index> JointToIndividualTypeIndices(Index jTypeI) const
        { return IndexTools::JointToIndividualIndicesStepSize(jTypeI, 
                _m_stepSizeTypes, _m_nrAgents);};
*/
        const std::vector<Index>& JointToIndividualTypeIndices(Index jTypeI) const
        {
            if(_m_useSparse)
            {
                if((*_m_jointToIndTypesMap).find(jTypeI)==
                   (*_m_jointToIndTypesMap).end())
                    (*_m_jointToIndTypesMap)[jTypeI]=
                        IndexTools::JointToIndividualIndices(
                            jTypeI, _m_nrTypes);
                return((*_m_jointToIndTypesMap)[jTypeI]);
                    
            }
            else
            {
                if((*_m_jointToIndTypes)[jTypeI].size()==0)
                    (*_m_jointToIndTypes)[jTypeI]=
                        IndexTools::JointToIndividualIndices(
                            jTypeI, _m_nrTypes);
                return((*_m_jointToIndTypes)[jTypeI]);
            }
        }



        /** Prints a description of this BayesianGameBase to a string.*/
        std::string SoftPrint() const;
        /**\brief Print this BayesianGameBase to cout.*/
        void Print() const
        {std::cout << SoftPrint();}

        bool SanityCheck() const;

        /// implement the Interface_ProblemToPolicyDiscrete interface:
        //\todo TODO adapt
        size_t GetNrAgents() const 
            {return _m_nrAgents;}
        size_t GetNrActions(Index agentI) const 
            {return _m_nrActions[agentI];}
        const std::vector<size_t>& GetNrActions() const 
            {return _m_nrActions;}
        size_t GetNrPolicyDomainElements(
            Index agentI, 
            PolicyGlobals::IndexDomainCategory cat,
            size_t depth=MAXHORIZON) const;
        LIndex GetNrPolicies(Index ag) const
        { return (Interface_ProblemToPolicyDiscretePure::GetNrPolicies(ag,
                PolicyGlobals::TYPE_INDEX) ); }
        LIndex GetNrJointPolicies() const
        { return (Interface_ProblemToPolicyDiscretePure::GetNrJointPolicies(
                PolicyGlobals::TYPE_INDEX) ); }
        //Index GetJointActionIndex(std::vector<Index>& indivIndices) const
        //    {return IndividualToJointActionIndices(indivIndices);}

        /**\brief implementation of JointToIndividualPolicyDomainIndices
         *
         * (specified in the Interface_ProblemToPolicyDiscrete )
         */
        std::vector<Index> JointToIndividualPolicyDomainIndices
            (Index jdI, PolicyGlobals::IndexDomainCategory cat) const
        {
            if(cat != PolicyGlobals::TYPE_INDEX)
                throw(E("BG only supports type as the domain of the policy"));
            return(JointToIndividualTypeIndices(jdI));
        }        
        /**\brief implementation of JointToIndividualPolicyDomainIndicesRef
         *
         * (specified in the Interface_ProblemToPolicyDiscrete )
         */
        const std::vector<Index>& JointToIndividualPolicyDomainIndicesRef
            (Index jdI, PolicyGlobals::IndexDomainCategory cat) const
        {
#if 0 // disable check for speed
            if(cat != PolicyGlobals::TYPE_INDEX)
                throw(E("BG only supports type as the domain of the policy"));
#endif
//            return( _m_jointToIndTypes[jdI]);
            return(JointToIndividualTypeIndices(jdI));
        }

        // A BG has types, not (A)OH histories. 
        // (and the joint -> individual type conversions are cached)
        bool CacheJointToIndivType_Indices() const {return true;};        
        bool CacheJointToIndivOH_Indices() const {return false;};
        bool CacheJointToIndivAOH_Indices() const {return false;};
        virtual bool AreCachedJointToIndivIndices(
            const PolicyGlobals::IndexDomainCategory pdc) const;

        /**\brief \todo TODO: check if this can be deprecated \deprecated
         * currently not implemented.*/ 
        std::string SoftPrintPolicyDomainElement(Index agentI, Index typeIndex,
               PolicyGlobals::IndexDomainCategory cat ) const;
        /**\brief \todo TODO: check if this can be deprecated \deprecated
         * currently not implemented.*/ 
        std::string SoftPrintAction(Index agentI, Index actionI) const;
        /**\brief \todo TODO: check if this can be deprecated \deprecated
         * currently not implemented.*/ 
        void PrintPolicyDomain(Index agentI, Index typeIndex) const;
        /**\brief y\todo TODO: check if this can be deprecated \deprecated
         * currently not implemented.*/ 
        void PrintAction(Index agentI, Index actionI) const;

        /*\brief the default IndexDomainCategory for the planning unit.
         *
         * as specified by Interface_ProblemToPolicyDiscrete. This can be 
         * overriden in derived classes.
         */
        virtual PolicyGlobals::IndexDomainCategory GetDefaultIndexDomCat()
            const;

        void SanityCheckBGBase();

        virtual void SanityCheck()
        { SanityCheckBGBase(); }
};

#endif /* !_BAYESIANGAMEBASE_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
