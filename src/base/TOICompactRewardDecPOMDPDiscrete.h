/**\file TOICompactRewardDecPOMDPDiscrete.h
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
 * $Id: TOICompactRewardDecPOMDPDiscrete.h 4016 2010-03-11 16:56:02Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _TOICOMPACTREWARDDECPOMDPDISCRETE_H_
#define _TOICOMPACTREWARDDECPOMDPDISCRETE_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"
#include "TOIDecPOMDPDiscrete.h"

/**\brief TOICompactRewardDecPOMDPDiscrete is a class that represents a
 * transition observation independent Dec-POMDP, in which the reward
 * is the sum of each agent's individual reward plus some shared
 * reward. The shared reward is defined for two agents only, and
 * replicated for all combinations. */
class TOICompactRewardDecPOMDPDiscrete :
    public TOIDecPOMDPDiscrete
{
private:    
    /**Boolean that tracks whether this DecPOMDP is initialized.*/
    bool _m_initialized;         

    std::vector<size_t>_m_nrTwoAgentStates, _m_nrTwoAgentActions;

    double GetTwoAgentReward(Index i, Index j,
                             const std::vector<Index> &indSIs,
                             const std::vector<Index> &indAIs) const;

protected:
    std::vector<RewardModel*> _m_p_rModels;    
public:
    // Constructor, destructor and copy assignment.
    /// (default) Constructor
    TOICompactRewardDecPOMDPDiscrete(
        std::string name="received unspec. by TOICompactRewardDecPOMDPDiscrete", 
        std::string descr="received unspec. by TOICompactRewardDecPOMDPDiscrete", 
        std::string pf="received unspec. by TOICompactRewardDecPOMDPDiscrete");

    TOICompactRewardDecPOMDPDiscrete
    (const TOICompactRewardDecPOMDPDiscrete& o);

    virtual ~TOICompactRewardDecPOMDPDiscrete();

    TOICompactRewardDecPOMDPDiscrete& operator=
    (const TOICompactRewardDecPOMDPDiscrete& o);

    /** Sets _m_initialized to b. When setting to true, a verification of
     * member elements is performed. (i.e. a check whether all vectors
     * have the correct size and non-zero entries) */
    virtual bool SetInitialized(bool b);   

    void SetIndividualRewardModel(RewardModel* rewardModel,
                                  Index agentID);

    //get (data) functions:
    ///**return the reward for state, joint action indices */
    double GetReward(Index sI, Index jaI) const;
    double GetReward(const std::vector<Index> &sIs,
                     const std::vector<Index> &aIs) const;

    double GetIndividualReward(Index indSI, Index indAI, Index agentID) const;

    /// Returns a pointer to a copy of this class.
    virtual TOICompactRewardDecPOMDPDiscrete* Clone() const
        { return new TOICompactRewardDecPOMDPDiscrete(*this); }

    /** SoftPrints some information on the DecPOMDPDiscrete.*/        
    std::string SoftPrint() const;
};


#endif /* !_TOICOMPACTREWARDDECPOMDPDISCRETE_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
