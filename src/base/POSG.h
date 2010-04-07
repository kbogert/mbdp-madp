/**\file POSG.h
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
 * $Id: POSG.h 2151 2008-01-21 16:32:52Z mtjspaan $
 */

#ifndef _POSG_H_
#define _POSG_H_ 1

/* the include directives */

#include <iostream>
#include "Globals.h"
#include "POSGInterface.h"


/**\brief POSG is a simple implementation of POSGInterface.
 *
 *  It defines a couple of functions that relate to the (types of)
 *  rewards and discount factors for each agent.
 *
 * Conceptually an MultiAgentDecisionProcess that implements this interface, is
 * a POSG: each agent his its own reward function.
  */
class POSG : 
    virtual public POSGInterface
{
    private:
        /// is this initialized?
        bool _m_initialized;
        /// the number of agents
        size_t _m_nrAgents;

        /// The discount parameter.
        /** When agents have different interests (the POSG setting),
         * they may also have different discount factors.
         * For a
         * POSG, however, we have one global discount factor
         * (which typically is 1.0 in the finite horizon case).
         **/
        std::vector<double> _m_discount;
        ///  Do the agents get rewards or costs?
        std::vector<reward_t> _m_rewardType;
    protected:

    public:

        // constructors etc.
        // Default constructor. sets initialized to false
        POSG();

        ///changed initialized status
        bool SetInitialized(bool b);

        ///Sets the number of agents
        void SetNrAgents (size_t nrAgents);

        /// Sets the discount parameter of \a agentI to \a d.
        void SetDiscount(Index agentI, double d);
        /// Returns the discount parameter for agent \a agentI.
        double GetDiscount(Index agentI) const {return _m_discount.at(agentI);}
        /// Sets the reward type to reward_t r.
        /** At the moment only REWARD is supported. */
        void SetRewardType(Index agentI, reward_t r);
        /// Returns the reward type.
        reward_t GetRewardType(Index agentI) const 
        {return _m_rewardType.at(agentI);}
        
        /// SoftPrints some information on the POSG.        
        std::string SoftPrint() const;

};

#endif //! _POSG_H_

// Local Variables: ***
// mode:c++ ***
// End: ***
