/**\file DecPOMDP.cpp
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
 * $Id: DecPOMDP.cpp 2151 2008-01-21 16:32:52Z mtjspaan $
 */

#include "DecPOMDP.h"

using namespace std;

DecPOMDP::DecPOMDP() 
{
    _m_rewardType = REWARD;
    _m_discount = 1.0;
}

void DecPOMDP::SetDiscount(double d)
{
    if(d>=0 && d<=1)
        _m_discount=d;
    else
        throw(E("DecPOMDP::SetDiscount() discount not valid, should be >=0 and <=1"));
}

string DecPOMDP::SoftPrint() const
{
    stringstream ss;
    ss << "Discount factor: " << _m_discount << endl;
    ss << "Reward type: " << _m_rewardType << endl;
    return ss.str();
}

void DecPOMDP::SetRewardType(reward_t r)
{
    if(r!=REWARD)
        throw(E("DecPOMDP::SetRewardType only reward type REWARD is supported"));
    _m_rewardType = r;
}
