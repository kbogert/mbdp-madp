/**\file PolicyDiscrete.h
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
 * $Id: PolicyDiscrete.h 4016 2010-03-11 16:56:02Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _POLICYDISCRETE_H_
#define _POLICYDISCRETE_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"
#include "Policy.h"
#include "Interface_ProblemToPolicyDiscrete.h"
#include "Referrer.h"

using namespace PolicyGlobals;

/**\brief PolicyDiscrete is a class that represents a discrete 
 * policy.
 *
 * A `discrete joint policy' is a policy for a discrete problem. I.e., the 
 * problem specifies, for each agent, a discrete domain for the policy and 
 * discrete actions.
 *
 * A PolicyDiscrete from discrete indices over the domain (typically 
 * action-observation histories or types) to (degenerate) probability 
 * distributions over indices over (joint) actions.
 *
 * This means that this class includes both pure and stochastic pure policies.
 *
 * */
class PolicyDiscrete : 
//    public Referrer<Interface_ProblemToPolicyDiscrete>,
    public Policy
{
    private:    
        const Interface_ProblemToPolicyDiscrete* _m_I_PTPD;
        /// Maintains the IndexDomainCategory.
        PolicyGlobals::IndexDomainCategory _m_indexDomCat;
    
    protected:
    
    public:
        // Constructor, destructor and copy assignment.
        /// (default) Constructor
        PolicyDiscrete( const Interface_ProblemToPolicyDiscrete& iptpd,
                        PolicyGlobals::IndexDomainCategory idc,
                        Index agentI ) :
            Policy(agentI),
            _m_I_PTPD(&iptpd),
            _m_indexDomCat(idc){};
            
        /// Copy constructor.
        PolicyDiscrete(const PolicyDiscrete& a) :
            Policy(a),
            _m_I_PTPD(a._m_I_PTPD),
            _m_indexDomCat(a._m_indexDomCat)
        {};

        /// Destructor.
        virtual ~PolicyDiscrete()
        {};

        //operators:

        //data manipulation (set) functions:
        /**\brief Sets the category of the domain over which the indices of
         * this policy are specified.
         */
        void SetIndexDomainCategory(IndexDomainCategory idc)
        {_m_indexDomCat = idc;};
        
        //get (data) functions:
        /**\brief Returns the Category of the domain over which the indices of
         * this policy are specified.
         */
        IndexDomainCategory GetIndexDomainCategory() const
        {return (_m_indexDomCat);};

        /**\brief Returns the probability that the policy specifies action
         * for domain index i.
         *
         * Implementations for pure policies clearly should return 0 or 1.
         */
        virtual double GetActionProb( Index i, Index ja ) const = 0;
        
        /**\brief samples an action for domain index i.
         */
        Index SampleAction( Index i ) const;

        /**\brief return a pointer to the referred 
         * Interface_ProblemToPolicyDiscrete.
         */
        const Interface_ProblemToPolicyDiscrete* GetInterfacePTPDiscrete() const
        {return _m_I_PTPD;}

        /// Returns a pointer to a copy of this class.
        virtual PolicyDiscrete* Clone() const = 0;

};


#endif /* !_POLICYDISCRETE_H_ */


// Local Variables: ***
// mode:c++ ***
// End: ***
