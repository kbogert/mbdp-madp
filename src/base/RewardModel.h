/**\file RewardModel.h
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
 * $Id: RewardModel.h 4016 2010-03-11 16:56:02Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _REWARDMODEL_H_
#define _REWARDMODEL_H_ 1

/* the include directives */
#include "Globals.h"
#include "QTableInterface.h"

/// RewardModel represents the reward model in a decision process.
class RewardModel 
    : public QTableInterface
{
    private:
   
    protected:
    /// The number of states.
    size_t _m_nrStates;
    /// The number of joint actions.
    size_t _m_nrJointActions;    
    
    public:
    // Constructor, destructor and copy assignment.
    /// default Constructor
    RewardModel(size_t nrS=1, size_t nrJA=1) :
        _m_nrStates(nrS),
        _m_nrJointActions(nrJA){};

    /// Destructor.
    virtual ~RewardModel(){};

    /// Returns R(s,ja)
    virtual double Get(Index s_i, Index ja_i) const = 0;

    //data manipulation funtions:
    /// Sets R(s_i,ja_i)
    /** Index ja_i, Index s_i, are indices of the state and taken
     * joint action. r is the reward. The order of events is s, ja, so
     * is the arg. list. */
    virtual void Set(Index s_i, Index ja_i, double rew) = 0;

    /// Returns a pointer to a copy of this class.
    virtual RewardModel* Clone() const = 0;

    /// Prints a description of *this* to a string.
    virtual std::string SoftPrint() const = 0;
    ///Print *this* to cout.
    void Print() const
        { std::cout << SoftPrint();}

};

#endif /* !_REWARDMODEL_H_ */


// Local Variables: ***
// mode:c++ ***
// End: ***

