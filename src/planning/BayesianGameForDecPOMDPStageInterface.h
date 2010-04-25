/**\file BayesianGameForDecPOMDPStageInterface.h
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
 * $Id: BayesianGameForDecPOMDPStageInterface.h 3604 2009-08-25 10:52:24Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _BAYESIANGAMEFORDECPOMDPSTAGEINTERFACE_H_
#define _BAYESIANGAMEFORDECPOMDPSTAGEINTERFACE_H_ 1

/* the include directives */
#include "Globals.h"
class PartialJointPolicyDiscretePure;
class JointPolicyDiscretePure;

/** \brief BayesianGameForDecPOMDPStageInterface is a class that represents 
 * TODO: fill out...  */
class BayesianGameForDecPOMDPStageInterface 
{
    private:    
    
    protected:
        ///The stage (time step) that this BG represents
        Index _m_t;
        ///Stores pointer to the past policy - perhaps not needed?
        const PartialJointPolicyDiscretePure* _m_pJPol;
    
    public:
        // Constructor, destructor and copy assignment.
        /// (default) Constructor
        BayesianGameForDecPOMDPStageInterface(const PartialJointPolicyDiscretePure* pastJPol);
        BayesianGameForDecPOMDPStageInterface(Index t);
        /// Destructor.
        virtual ~BayesianGameForDecPOMDPStageInterface(){};
/*        
        /// Copy constructor.
        BayesianGameForDecPOMDPStageInterface(const BayesianGameForDecPOMDPStageInterface& a);
        /// Copy assignment operator
        BayesianGameForDecPOMDPStageInterface& operator= (const BayesianGameForDecPOMDPStageInterface& o);
*/

        Index GetStage() const
        {return _m_t;}
        const PartialJointPolicyDiscretePure* GetPastJointPolicy() const
        { return _m_pJPol;};
        
        /**Returns the (expected) immediate reward for jtI, jaI
         */
        virtual double GetImmediateReward(Index jtI, Index jaI) const=0;
        /**When performing a lot of GetImmediateReward calls we can first 
         * compute a cache of immediate rewards, to speed things up.
         */
        virtual void ComputeAllImmediateRewards() = 0;
        /**We can also clear this cache.
         */
        virtual void ClearAllImmediateRewards() = 0;
        /**\brief Compute the discounted expected imm reward for jpolBG.
         */
        virtual double ComputeDiscountedImmediateRewardForJPol(
                JointPolicyDiscretePure* jpolBG) const = 0;
};


#endif /* !_BAYESIANGAMEFORDECPOMDPSTAGEINTERFACE_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
