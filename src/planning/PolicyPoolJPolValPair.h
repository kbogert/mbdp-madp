/**\file PolicyPoolJPolValPair.h
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
 * $Id: PolicyPoolJPolValPair.h 3603 2009-08-25 10:38:25Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _POLICYPOOLJPOLVALPAIR_H_
#define _POLICYPOOLJPOLVALPAIR_H_ 1

/* the include directives */
#include <iostream>
#include <queue>
#include "Globals.h"
#include "JointPolicyValuePair.h"
#include "PolicyPoolInterface.h"


/**\brief PolicyPoolJPolValPair is a policy pool with joint policy -
 * value pairs. */
class PolicyPoolJPolValPair : public PolicyPoolInterface 
{
    private:   
        ///The pointer to the JointPolicyValuePair queue
        std::priority_queue<JointPolicyValuePair*> * _m_jpvpQueue_p;
    
    protected:
    
    public:
        // Constructor, destructor and copy assignment.
        /// (default) Constructor
        PolicyPoolJPolValPair();
        /// Destructor.
        ~PolicyPoolJPolValPair();
        /// Copy assignment operator
        PolicyPoolJPolValPair& operator= (const PolicyPoolJPolValPair& o);
        PolicyPoolInterface& operator= (const PolicyPoolInterface& o);

        //operators:

        //data manipulation (set) functions:
        /**\brief  initializes the policy pool with the empty joint policy
         * and a heuristic value set to infinuty (i.e., DBL_MAX)
         *
         * A pointer to a Interface_ProblemToPolicyDiscretePure is needed to create the
         * joint policy.
         */
        void Init(const Interface_ProblemToPolicyDiscretePure* pu);
        
        /**\brief The 'Select' operator from #refGMAA.
         *
         * This returns a reference to the next PolicyPoolItem (a wrapper for a
         * partial joint policy, together with some properties).
         *
         * The returned PolicyPoolItem is not removed from the PolicyPool.
         */
        PolicyPoolItemInterface* Select() const;   
        /**\brief Removes the item returned by 'Select'.
         *
         * This removes the next PolicyPoolItem (a wrapper for a
         * partial joint policy, together with some properties), as would
         * be returned by 'Select'.
         */
        void Pop();
        /**\brief returns the contained item with the highest value.
         *
         * This function returns a pointer to the PolicyPoolItemInterface
         * contained in this Policy pool with the highest (heuristic) value.
         *
         * Heuristic is between brackets, because this function is typically
         * used when we found lower bounds (i.e. full policies) and then select
         * the maximum lowerbound.
         *
         * Because this class always 'select's the best ranked policy, this
         * function does the same as 'Select()'.
         */
        PolicyPoolItemInterface* GetBestRanked() const
        {return(Select());};
        /**\brief remove the GetBestRanked() item
         *
         * Removes the PolicyPoolItemInterface contained
         * in this Policy pool with the highest (heuristic) value.
         * (as is returned by GetBestRanked() )
         *
         * Because this class always 'select's the best ranked policy, this
         * function does the same as 'Pop()'.
         */
        void PopBestRanked()
        {Pop();};
        /**\brief Add a PolicyPoolItem to the Pool.
         *
         * ...
         */
        void Insert(PolicyPoolItemInterface*  ppi); 
        
        /**\brief add all elements of pp to 'this'.
         *
         * Note, that the pool pp is emptied in this process.
         */
        void Union(PolicyPoolInterface*  pp);
        void Prune(double v);       
        //get (data) functions:
        
        /**\brief return the number of items in the policy pool
         *
         * ...
         */
        size_t Size() const
        {
            return(_m_jpvpQueue_p->size());
        }
};


#endif /* !_POLICYPOOLJPOLVALPAIR_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
