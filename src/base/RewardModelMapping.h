/**\file RewardModelMapping.h
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
 * $Id: RewardModelMapping.h 4016 2010-03-11 16:56:02Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _REWARDMODELMAPPING_H_
#define _REWARDMODELMAPPING_H_ 1

/* the include directives */
#include <boost/numeric/ublas/matrix.hpp>
#include "Globals.h"
#include "RewardModel.h"

/// RewardModelMapping represents a discrete reward model.
class RewardModelMapping : public RewardModel
{
private:

    std::string _m_s_str;
    std::string _m_ja_str;
    
    typedef boost::numeric::ublas::matrix<double> Matrix;

    Matrix _m_R;

protected:
    
public:
    // Constructor, destructor and copy assignment.
    /** default Constructor
     *  nrS - number of states
     *  nrJA - number of joint actions
     *  s_str - how to call a state (For example you can use this class to 
     *          create a mapping from observation histories and ja's to 
     *          reals. Then this argument could be "joh")
     *  ja_str - idem for the joint actions
     */
    RewardModelMapping(size_t nrS = 1, size_t nrJA = 1, std::string s_str="s",
                       std::string ja_str="ja");
    /// Copy constructor.
    //RewardModelMapping(const RewardModelMapping&);
    /// Destructor.
    ~RewardModelMapping();
        
    /// Returns R(s,ja)
    double Get(Index s_i, Index ja_i) const
        { return(_m_R(s_i,ja_i)); }

    //data manipulation funtions:
    /// Sets R(s_i,ja_i)
    /** Index ja_i, Index s_i, are indices of the state and taken
     * joint action. r is the reward. The order of events is s, ja, so
     * is the arg. list. */
    void Set(Index s_i, Index ja_i, double rew)
        { _m_R(s_i,ja_i)=rew; }

    /// Returns a pointer to a copy of this class.
    virtual RewardModelMapping* Clone() const
        { return new RewardModelMapping(*this); }

    /// Prints a description of *this* to a string.
    std::string SoftPrint() const; 
    ///Print *this* to cout.
    void Print() const
        { std::cout << SoftPrint();}

    friend class RGet_RewardModelMapping;
};

#endif /* !_REWARDMODELMAPPING_H_*/

// Local Variables: ***
// mode:c++ ***
// End: ***

