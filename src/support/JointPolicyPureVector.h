/**\file JointPolicyPureVector.h
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
 * $Id: JointPolicyPureVector.h 4016 2010-03-11 16:56:02Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _JOINTPOLICYPUREVECTOR_H_
#define _JOINTPOLICYPUREVECTOR_H_ 1

/* the include directives */
#include <iostream>
#include <vector>
#include "Globals.h"
#include "JointPolicyDiscretePure.h"
#include "JPolComponent_VectorImplementation.h"


/// JointPolicyPureVector represents a discrete pure joint policy.
/** 
 * Each of the individual policies is a PolicyPureVector - a
 * deterministic mapping from observations to actions implemented by a
 * tree. This class acts as a wrapper. It contains a vector with
 * pointers to indiv. policies. 
 *
 * we delete the PolicyPureVectors pointed to: this means that we should not 
 * be able to add indiv. policies without copying them!!! 
 *
 * */
class JointPolicyPureVector  :  
    //virtual <- this leads to pain in the ass...
    public JointPolicyDiscretePure,
    private JPolComponent_VectorImplementation // use private inheritance for composition

{
    private:

    /** \brief Private function that deletes all the individual
     * policies pointed to.*/
    void ClearIndividualPolicies();

    /// vector for  temporarily storing indiv. actions 
    /**(used by GetJointActionIndex)
     */
    Index * _m_indivActionIndices;

    protected:
        std::vector<PolicyPureVector*> _m_indivPols_PolicyPureVector;

    public:
        // Constructor, destructor and copy assignment.

        /**\brief Constructor. 
         *
         * Associates a problem (typically a planning unit) with the joint
         * policy.  Information regarding the problem is used to construct a
         * joint policy of the proper shape.
         * 
         * Use the default IndexDomainCategory defined by pu.
         * */
        JointPolicyPureVector(const Interface_ProblemToPolicyDiscretePure& pu)
          :
          JointPolicyDiscretePure( pu , pu.GetDefaultIndexDomCat()  ),
          JPolComponent_VectorImplementation(pu,  pu.GetDefaultIndexDomCat() )
        {};
        /**\brief Constructor. 
         *
         * Associates a problem (typically a planning unit) with the joint
         * policy.  Information regarding the problem is used to construct a
         * joint policy of the proper shape.
         *
         * idc is the IndexDomainCategory over which the policy is specified.
         *
         * */
        JointPolicyPureVector(const Interface_ProblemToPolicyDiscretePure& pu,
                PolicyGlobals::IndexDomainCategory idc )
            :
            JointPolicyDiscretePure(pu, idc),
            JPolComponent_VectorImplementation(pu, idc)
        {};

        /// Copy constructor.
        JointPolicyPureVector(const JointPolicyPureVector& a)
            :
            JointPolicyDiscretePure(a)
            , JPolComponent_VectorImplementation(a)
        {};
        /// Copy constructor from base class a
        JointPolicyPureVector(const JointPolicyDiscretePure& a)
            :
            JointPolicyDiscretePure(a),
            JPolComponent_VectorImplementation( 
                dynamic_cast<const JointPolicyPureVector&>( a ) )
        {};
        /// Copy constructor from base class a
        JointPolicyPureVector(const JointPolicyDiscretePure& a1, 
                const JPolComponent_VectorImplementation& a2)
            :
            JointPolicyDiscretePure(a1),
            JPolComponent_VectorImplementation( a2 )
        {};
    private:
    public:
        /// Destructor.
        virtual ~JointPolicyPureVector() {};
        /**The copy assignment operator - makes deep copies using 
         * PolicyPureVector::operator= which makes deep copies.*/
        virtual JointPolicyPureVector& operator= (const JointPolicyPureVector& jp);
        /**The copy assignment operator - makes deep copies using 
         * PolicyPureVector::operator= which makes deep copies.*/
        virtual JointPolicyPureVector& operator= (const JointPolicyDiscretePure& jp);

        /// Sets the depth of the joint policy.
        /** Also sets the depth of each of the invididual policies. */
        void SetDepth(size_t d)
        {
            JointPolicy::SetDepth(d);
            JPolComponent_VectorImplementation::SetDepthForIndivPols(d);
        };

        /// Prints a description of this JointPolicyPureVector to a string.
        virtual std::string SoftPrint() const; 
        /// Prints a brief description to a string.
        virtual std::string SoftPrintBrief() const; 
        void PrintBrief() const
        { std::cout << SoftPrintBrief();}
        
        /**\brief Convert this joint policy to a JointPolicyPureVector.
         */
        JointPolicyPureVector* ToJointPolicyPureVector() const;
        
    //relay the following functions to the JPolComponent_VectorImplementation:
        
        ///Performs increment. See Increment().
        bool operator++ ()   {    return( this->Increment() );     };

        bool Increment(Index agentI)
        { return this->JPolComponent_VectorImplementation::Increment(agentI); }
        bool Increment()
        { return this->JPolComponent_VectorImplementation::Increment(); }
        
        /// Get the index of this joint policy.
        LIndex GetIndex() const
        {   return this->JPolComponent_VectorImplementation::GetIndex(); }
        /// Sets the index of this joint policy.Updates the policies represented
        void SetIndex(LIndex i)
        {   this->JPolComponent_VectorImplementation::SetIndex(i); }
        

        ///Returns the jaI taken by this policy for joint domain index johI.
        virtual Index GetJointActionIndex(Index i) const
        { return JPolComponent_VectorImplementation::GetJointActionIndex(i); }
        ///Returns the action index for domainI for agent aI.
        virtual Index GetActionIndex(Index agI , Index domainI) const
        { return JPolComponent_VectorImplementation::GetActionIndex(agI , domainI);}

        virtual PolicyDiscrete* GetIndividualPolicyDiscrete(Index i) const
        { return JPolComponent_VectorImplementation::GetIndividualPolicyDiscrete(i) ;}
        /// Returns a reference to the vector of pointers to individual policies
        /** This function should be used to manipulate individual policies.
         */
        std::vector<PolicyPureVector*>& GetIndividualPolicies()
        {return this->JPolComponent_VectorImplementation::GetIndividualPolicies();}

        /// Initialize the joint policy to the first joint policy.
        /** This is the joint policy that specifies action 0 --the
         *  first action-- for all observation histories.*/
        virtual void ZeroInitialization()
        { JPolComponent_VectorImplementation::ZeroInitialization();}
        /// Initialize the policy of agentI to the first policy.
        /** This is the policy that specifies action 0 --the first
         *  action-- for all observation histories.*/
        virtual void ZeroInitialization(Index i)
        { JPolComponent_VectorImplementation::ZeroInitialization(i);}
        ///Randomly initialize the joint policy.
        virtual void RandomInitialization()
        { JPolComponent_VectorImplementation::RandomInitialization();}
        ///Randomly initialize the policy for agentI.
        virtual void RandomInitialization(Index i)
        { JPolComponent_VectorImplementation::RandomInitialization(i);}
        virtual void SetAction(Index agentI, Index domainI, Index aI)
        { JPolComponent_VectorImplementation::SetAction(agentI, domainI, aI);}

        /// Returns a pointer to a copy of this class.
        virtual JointPolicyPureVector* Clone() const
        { return new JointPolicyPureVector(*this); }


      
};


#endif /* !_JOINTPOLICYPUREVECTOR_H_ */


// Local Variables: ***
// mode:c++ ***
;// End: ***
