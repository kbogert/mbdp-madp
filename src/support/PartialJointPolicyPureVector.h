/**\file PartialJointPolicyPureVector.h
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
 * $Id: PartialJointPolicyPureVector.h 4016 2010-03-11 16:56:02Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _PARTIALJOINTPOLICYPUREVECTOR_H_
#define _PARTIALJOINTPOLICYPUREVECTOR_H_ 1

/* the include directives */
#include "Globals.h"
#include "JPolComponent_VectorImplementation.h"
#include "PartialJointPolicyDiscretePure.h"

/** \brief PartialJointPolicyPureVector implements a
 * PartialJointPolicy using a mapping of history indices to
 * actions. */
class PartialJointPolicyPureVector :
//    public JointPolicyPureVector , //<- don't use mutliple inheritance for code reuse..
    public PartialJointPolicyDiscretePure,
    private JPolComponent_VectorImplementation // use private inheritance for composition
{
    private:    
        
    protected:
    
    public:
        // Constructor, destructor and copy assignment.
        PartialJointPolicyPureVector(
                const Interface_ProblemToPolicyDiscretePure& pu,
                PolicyGlobals::IndexDomainCategory idc,
                double pastReward = 0.0,
                size_t depth = MAXHORIZON);

        /// Copy constructor.
        PartialJointPolicyPureVector(const PartialJointPolicyPureVector& a)
            :
            PartialJointPolicyDiscretePure(a)
            , JPolComponent_VectorImplementation(a)
        {};
        PartialJointPolicyPureVector(const PartialJointPolicyDiscretePure& a)
            :
            PartialJointPolicyDiscretePure(a),
            JPolComponent_VectorImplementation( 
                dynamic_cast<const PartialJointPolicyPureVector&>( a ) )
        {};


        /// Destructor.
        virtual ~PartialJointPolicyPureVector() {};
        /// Copy assignment operator
        virtual PartialJointPolicyPureVector& operator= 
            (const PartialJointPolicyPureVector& o);
        virtual PartialJointPolicyPureVector& operator= 
            (const PartialJointPolicyDiscretePure& o);

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
    //
        bool operator++ ()   
        {   return( this->Increment() );     };
        bool Increment(Index agentI)
        { return this->JPolComponent_VectorImplementation::Increment(agentI); }
        bool Increment()
        { return this->JPolComponent_VectorImplementation::Increment(); }

        LIndex GetIndex() const
        {   return this->JPolComponent_VectorImplementation::GetIndex(); }
        void SetIndex(LIndex i)
        {   this->JPolComponent_VectorImplementation::SetIndex(i); }

        virtual Index GetJointActionIndex(Index i) const
        { return JPolComponent_VectorImplementation::GetJointActionIndex(i); }
        virtual Index GetActionIndex(Index agI , Index domainI) const
        { return JPolComponent_VectorImplementation::GetActionIndex(agI , domainI);}

        virtual PolicyDiscrete* GetIndividualPolicyDiscrete(Index i) const
        { return JPolComponent_VectorImplementation::GetIndividualPolicyDiscrete(i) ;}
        /// Returns a reference to the vector of pointers to individual policies
        /** This function should be used to manipulate individual policies.
         */
        std::vector<PolicyPureVector*>& GetIndividualPolicies()
        {return this->JPolComponent_VectorImplementation::GetIndividualPolicies();}
        
        virtual void ZeroInitialization()
        { JPolComponent_VectorImplementation::ZeroInitialization();}
        virtual void ZeroInitialization(Index i)
        { JPolComponent_VectorImplementation::ZeroInitialization(i);}
        virtual void RandomInitialization()
        { JPolComponent_VectorImplementation::RandomInitialization();}
        virtual void RandomInitialization(Index i)
        { JPolComponent_VectorImplementation::RandomInitialization(i);}
        virtual void SetAction(Index agentI, Index domainI, Index aI)
        { JPolComponent_VectorImplementation::SetAction(agentI, domainI, aI);}
        
        /// Returns a pointer to a copy of this class.
        virtual PartialJointPolicyPureVector* Clone() const
        { return new PartialJointPolicyPureVector(*this); }

};


#endif /* !_PARTIALJOINTPOLICYPUREVECTOR_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
