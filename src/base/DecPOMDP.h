/**\file DecPOMDP.h
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
 * $Id: DecPOMDP.h 2151 2008-01-21 16:32:52Z mtjspaan $
 */

#ifndef _DECPOMDP_H_
#define _DECPOMDP_H_ 1

/* the include directives */

#include <iostream>
#include "Globals.h"
#include "DecPOMDPInterface.h"


/**\brief DecPOMDP is a simple implementation of DecPOMDPInterface.
 *
 *  It defines a couple of functions that relate to the (types of)
 *  rewards and discount factor.
 *
 * Conceptually an MultiAgentDecisionProcess that implements this interface, is
 * a Dec-POMDP: the system is cooperative and there is only 1 reward function.
  */
class DecPOMDP : 
    virtual public DecPOMDPInterface
{
    private:

        /// The discount parameter.
        /** When agents have different interests (the POSG setting),
         * they may also have different discount factors. For a
         * Dec-POMDP, however, we have one global discount factor
         * (which typically is 1.0 in the finite horizon case).*/
        double _m_discount;
        ///  Do the agents get rewards or costs?
        reward_t _m_rewardType;
    protected:

    public:

        // constructors etc.
        /// Default constructor. sets RewardType to REWARD and discount to 1.0.
        DecPOMDP();

        /// Sets the discount parameter to d.
        void SetDiscount(double d);
        /// Returns the discount parameter.
        double GetDiscount() const {return _m_discount;}
        /// Sets the reward type to reward_t r.
        /** At the moment only REWARD is supported. */
        void SetRewardType(reward_t r);
        /// Returns the reward type.
        reward_t GetRewardType() const {return _m_rewardType;}
        
        /// SoftPrints some information on the DecPOMDP.        
        std::string SoftPrint() const;

    ///Functions needed for POSGInterface:
        void SetDiscountForAgent(Index agentI, double d)
        {SetDiscount(d);}

        /// Returns the discount parameter.
        double GetDiscountForAgent(Index agentI) const
        {return GetDiscount();}

        /// Sets the reward type to reward_t r.
        void SetRewardTypeForAgent(Index agentI, reward_t r) 
        {SetRewardType(r);}

        /// Returns the reward type.
        reward_t GetRewardTypeForAgent(Index agentI) const 
        {return GetRewardType();}


};

#endif //! _DECPOMDP_H_

// Local Variables: ***
// mode:c++ ***
// End: ***
