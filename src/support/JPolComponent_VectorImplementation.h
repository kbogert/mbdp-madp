/**\file JPolComponent_VectorImplementation.h
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
 * $Id: JPolComponent_VectorImplementation.h 3604 2009-08-25 10:52:24Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _JPOLCOMPONENT_VECTORIMPLEMENTATION_H_
#define _JPOLCOMPONENT_VECTORIMPLEMENTATION_H_ 1

/* the include directives */
#include "Globals.h"
#include "PolicyPureVector.h"

class Interface_ProblemToPolicyDiscretePure;

/** \brief JPolComponent_VectorImplementation implements functionality
 * common to several joint policy implementations. */
class JPolComponent_VectorImplementation 
{
    private:   
       /** \brief Private function that deletes all the individual
         * policies pointed to.*/
        void ClearIndividualPolicies();
        /// vector for  temporarily storing indiv. actions 
        /**(used by GetJointActionIndex)
         */
        Index * _m_indivActionIndices;
        
        ///Aux. function used by copy constructors
        void PrivClone(const JPolComponent_VectorImplementation& o);

        const Interface_ProblemToPolicyDiscretePure* _m_PTPDP;
        IndexDomainCategory _m_idc;

        void Construct(        
            const Interface_ProblemToPolicyDiscretePure& pu,
            PolicyGlobals::IndexDomainCategory idc,
            size_t depth);
    
    protected:
        std::vector<PolicyPureVector*> _m_indivPols_PolicyPureVector;
    
    public:
        // Constructor, destructor and copy assignment.
        /// (default) Constructor
        JPolComponent_VectorImplementation(
            const Interface_ProblemToPolicyDiscretePure& pu,
            size_t depth=MAXHORIZON);

        JPolComponent_VectorImplementation(
            const Interface_ProblemToPolicyDiscretePure& pu,
            PolicyGlobals::IndexDomainCategory idc,
            size_t depth=MAXHORIZON);

        /// Copy constructor.
        JPolComponent_VectorImplementation(
            const JPolComponent_VectorImplementation& a);

        /// Destructor.
        ~JPolComponent_VectorImplementation();
        /// Copy assignment operator
        JPolComponent_VectorImplementation& operator= (const
                JPolComponent_VectorImplementation& o);
        ///Performs increment. See Increment().

        bool operator++ ()   
        {    return( this->Increment() );     };
        
        /// Get the index of this joint policy.
        LIndex GetIndex() const;

        /// Returns a reference to the vector of pointers to individual policies
        /** This function should be used to manipulate individual policies.
         */
        std::vector<PolicyPureVector*>& GetIndividualPolicies()
        {return _m_indivPols_PolicyPureVector;};
        
        virtual PolicyDiscrete* GetIndividualPolicyDiscrete(Index agI) const
        { return _m_indivPols_PolicyPureVector.at(agI); }

        /// Sets the index of this joint policy.Updates the policies represented
        void SetIndex(LIndex i);

        //data manipulation (set) functions:
        ///Randomly initialize the joint policy.
        void RandomInitialization();
        ///Randomly initialize the policy for agentI.
        void RandomInitialization(Index agentI);
        /// Initialize the joint policy to the first joint policy.
        /** This is the joint policy that specifies action 0 --the
         *  first action-- for all observation histories.*/
        void ZeroInitialization();
        /// Initialize the policy of agentI to the first policy.
        /** This is the policy that specifies action 0 --the first
         *  action-- for all observation histories.*/
        void ZeroInitialization(Index agentI);


        ///Increments the individual policy of agentI.
        bool Increment(Index agentI) 
        {return( ++(*_m_indivPols_PolicyPureVector[agentI])) ;};
        ///Increments the joint policy, used to iterate over joint policies.
        bool Increment();

        void SetDepthForIndivPols(size_t d);

        ///Sets the policy for agentI to domainI->aI.
        void SetAction(Index agentI, Index domainI, Index aI)
            {_m_indivPols_PolicyPureVector[agentI]->SetAction(domainI, aI);}

        /// Prints a description of this to a string.
        std::string SoftPrint() const; 
        std::string SoftPrintBrief() const;

        
        ///Returns the jaI taken by this policy for joint domain index johI.
        Index GetJointActionIndex(Index i) const;
        ///Returns the action index for domainI for agent aI.
        Index GetActionIndex(Index aI, Index domainI) const
            {return _m_indivPols_PolicyPureVector[aI]->GetActionIndex(domainI);}
        
        


};


#endif /* !_JPOLCOMPONENT_VECTORIMPLEMENTATION_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
