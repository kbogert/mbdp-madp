/**\file PolicyPoolInterface.h
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
 * $Id: PolicyPoolInterface.h 3603 2009-08-25 10:38:25Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _POLICYPOOLINTERFACE_H_
#define _POLICYPOOLINTERFACE_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"
#include "PolicyPoolItemInterface.h"
class Interface_ProblemToPolicyDiscretePure;

/**\brief PolicyPoolInterface is an interface for PolicyPools
 * containing fully defined Joint Policies.  */
class PolicyPoolInterface 
{
    private:    
    
    protected:
    
    public:
        // Constructor, destructor and copy assignment.
        /// (default) Constructor
        //PolicyPoolInterface();
        /// Copy constructor.
        //PolicyPoolInterface(const PolicyPoolInterface& a);
        /// Destructor.
        virtual ~PolicyPoolInterface(){};
        /**\brief Copy assignment operator.
         *
         * This must be implemented by the derived class (with this prototype).
         * For an example, see PolicyPoolJPolValPair.
         *
         * For now, this function is purely abstract. Might there be some 
         * members added to this (base) class, then an implementation could
         * be made. This should then be called using
         *          PolicyPoolInterface::operator=(o)
         * from the copy assignment operator of the derived class. See also
         * http://www.icu-project.org/docs/papers/cpp_report/the_assignment_operator_revisited.html.
         */        
        virtual PolicyPoolInterface& operator= (const PolicyPoolInterface& o)=0;

        //operators:

        //data manipulation (set) functions:

        /**\brief Initializes the Policy pool with the empty joint policy
         *
         * A pointer to a Interface_ProblemToPolicyDiscretePure is needed to create the
         * joint policy.
         */
        virtual void Init(const Interface_ProblemToPolicyDiscretePure* pu)=0; 

        /**\brief The 'Select' operator from #refGMAA.
         *
         * This returns a reference to the next PolicyPoolItem (a wrapper for a
         * partial joint policy, together with some properties).
         *
         * The returned PolicyPoolItem is not removed from the PolicyPool.
         */
        virtual PolicyPoolItemInterface* Select()const=0;        
        /**\brief Removes the item returned by 'Select'.
         *
         * This removes the next PolicyPoolItem (a wrapper for a
         * partial joint policy, together with some properties), as would
         * be returned by 'Select'.
         */
        virtual void Pop()=0;
        /**\brief returns the contained item with the highest value.
         *
         * This function returns a pointer to the PolicyPoolItemInterface
         * contained in this Policy pool with the highest (heuristic) value.
         *
         * Heuristic is between brackets, because this function is typically
         * used when we found lower bounds (i.e. full policies) and then select
         * the maximum lowerbound.
         */
        virtual PolicyPoolItemInterface* GetBestRanked() const=0;
        /**\brief remove the GetBestRanked() item
         *
         * Removes the PolicyPoolItemInterface contained
         * in this Policy pool with the highest (heuristic) value.
         * (as is returned by GetBestRanked() )
         */
        virtual void PopBestRanked()=0;

        /**\brief Add a PolicyPoolItem to the Pool.
         *
         * ...
         */
        virtual void Insert(PolicyPoolItemInterface*  ppi)=0;


        /**\brief add all elements of pp to 'this'.
         *
         *...
         */
        virtual void Union(PolicyPoolInterface*  pp)=0;
        /**\brief prune the items in the policy pool with exp.value < v
         *
         *...
         */
        virtual void Prune(double v)=0;       
        //get (data) functions:
        
        /**\brief return teh number of items in the policy pool
         *
         * ...
         */
        virtual size_t Size() const = 0;
        /**\brief return whether the number of items in the policy pool is 0
         *
         * ...
         */
        size_t Empty() const
        {return(Size()==0);};
};


#endif /* !_POLICYPOOLINTERFACE_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
