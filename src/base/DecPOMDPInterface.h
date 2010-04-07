/**\file DecPOMDPInterface.h
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
 * $Id: DecPOMDPInterface.h 4016 2010-03-11 16:56:02Z mtjspaan $
 */

#ifndef _DECPOMDPINTERFACE_H_
#define _DECPOMDPINTERFACE_H_ 1

/* the include directives */

#include <iostream>
#include "Globals.h"
#include "POSGInterface.h"
class State;
class JointAction;




/**\brief DecPOMDPInterface is an interface for DecPOMDPs. It declares a couple
 * of function that relate to the (types of) rewards and discount factor.
 *
 * Conceptually an MultiAgentDecisionProcess that implements this interface, is
 * a Dec-POMDP: the system is cooperative and there is only 1 reward function.
 */
class DecPOMDPInterface : public virtual POSGInterface
{
    private:

    protected:

    public:
        /*using POSGInterface::SetDiscount;
        using POSGInterface::GetDiscount;
        using POSGInterface::GetRewardType;
        using POSGInterface::SetRewardType;
        using POSGInterface::GetReward;
        using POSGInterface::SetReward;*/

        /// Virtual destructor.
        virtual ~DecPOMDPInterface() {};
        
        /// Sets the discount parameter to 0 < d <= 1.
        virtual void SetDiscount(double d) = 0;

        /// Returns the discount parameter.
        virtual double GetDiscount() const = 0;

        /// Sets the reward type to reward_t r.
        virtual void SetRewardType(reward_t r) = 0;

        /// Returns the reward type.
        virtual reward_t GetRewardType() const  = 0;

        /// Function that returns the reward for a state and joint action.
        /** This should be very generic.*/
        virtual double GetReward(State* s, JointAction* ja) const = 0;
        
        /// Function that sets the reward for a state and joint action.
        /** This should be very generic.*/
        virtual void SetReward(State* s, JointAction* ja, double r) = 0;
        
        /// Returns a pointer to a copy of this class.
        virtual DecPOMDPInterface* Clone() const = 0;
};

#endif //! _DECPOMDPINTERFACE_H_

// Local Variables: ***
// mode:c++ ***
// End: ***
