/**\file PolicyPureVector.h
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
 * $Id: PolicyPureVector.h 4016 2010-03-11 16:56:02Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _POLICYPUREVECTOR_H_
#define _POLICYPUREVECTOR_H_ 1

/* the include directives */
#include <iostream>
#include <cmath>
#include "PolicyDiscretePure.h"
#include "ObservationHistoryTree.h"
#include "E.h"


/** \brief PolicyPureVector is a class that represents a pure
 * (=deterministic) policy.
 *
 * The implementation of this particular class is based on a vector of
 * length nrObservation-histories, that specifies an action index for
 * each observation history index.  Also a policy PolicyPureVector is
 * a #Referrer to an object that implements the functions defined by
 * the #Interface_ProblemToPolicyDiscretePure (for example a planning
 * unit or Bayesian game).
 *
 * TODO: the class was not designed with partial policies in mind.
 */
class PolicyPureVector : public PolicyDiscretePure 
{
    private:    
    
    protected:
        ///The index of the agent to which this policy belongs.
        Index _m_agentI;
        /** \brief The vector that stores the action indices for each
         * observation history.*/
        std::vector<Index> _m_domainToActionIndices;
    
    public:
        // Constructor, destructor and copy assignment.
        // (default) Constructor
        //PolicyPureVector();
        /**Alternate constructor. Associates a problem and agent with the policy
         * . Information regarding the problem is used to construct a policy
         * of the proper shape.*/
        PolicyPureVector(const Interface_ProblemToPolicyDiscretePure& pu, 
                         Index agentI,
                         PolicyGlobals::IndexDomainCategory idc,
                         size_t depth=MAXHORIZON);
        /// Copy constructor.
        PolicyPureVector(const PolicyPureVector& a);
        /// Destructor.
        virtual ~PolicyPureVector();
        virtual PolicyPureVector& operator= (const PolicyPureVector& o);

        //operators:
        ///Performs increment. See Increment().
        bool operator++ ()   {    return( this->Increment() );     };

        /// Get the index of this policy.
        LIndex GetIndex() const;

        /// Sets the index of this policy. Updates the policy represented.
        void SetIndex(LIndex i);

        //data manipulation (set) functions:
        /// Initialize the policy to the first policy.
        /** This is the policy that specifies action 0 --the first
         *  action-- for all observation histories.*/
        void ZeroInitialization();
        ///Randomly initialize the policy.
        void RandomInitialization();
        ///Randomly initialize the policy for agent agentI.
        void RandomInitialization(Index agentI)
        {
            if(agentI != _m_agentI)
                throw E("Error, agent index doesn't match.");
            RandomInitialization();
        }

        /// Increments the policy, used to iterate over policies.
        /**Policies are enumerable. This function changes a policy to the one 
         * with the next IndexValue. Returns true when increment changes to 
         * policy number from nrPolicies-1 to 0 (carry over signal).*/
        bool Increment();

        /** \brief Sets the number of time steps for which this policy
         * is valid.*/
        void SetDepth(size_t d);

        ///Sets the policy to map ohI->aI.
        void SetAction(Index ohI, Index aI)
            {_m_domainToActionIndices.at(ohI) =  aI;}
        
        //get (data) functions:

        /**Returns the action (index) this policy specifies for a
         * particular domain index. */
        Index GetActionIndex(Index oh) const
            {return( _m_domainToActionIndices[oh] ); }
        
        /// Returns a pointer to a copy of this class.
        virtual PolicyPureVector* Clone() const
        { return new PolicyPureVector(*this); }

        /// Prints a description of this PolicyPureVector to a string.
        std::string SoftPrint() const; 

};


#endif /* !_POLICYPUREVECTOR_H_ */


// Local Variables: ***
// mode:c++ ***
// End: ***
