/**\file Belief.h
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
 * $Id: Belief.h 4016 2010-03-11 16:56:02Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _BELIEF_H_
#define _BELIEF_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"
#include "BeliefInterface.h"
#include "StateDistributionVector.h"

class BeliefIterator;

/// Belief represents a probability distribution over the state space.
/** It is stored as a full vector. */
class Belief : virtual public BeliefInterface
{
private:    
    
    friend class BeliefIterator;

protected:
    
    /// The vector of probability values.
    //std::vector<double> _m_b;
    StateDistributionVector _m_b;

public:

    /// Constructor which sets the \a size of the belief.
    Belief(size_t size);

    /// Constructor which copies \a belief in this belief.
    Belief(const std::vector<double> &belief);

    /// Constructor which copies \a belief in this belief.
    Belief(const BeliefInterface &belief);

    Belief(const StateDistribution& belief);
    /// Destructor.
    ~Belief();

    Belief& operator= (const Belief& o);
    BeliefInterface& operator= (const BeliefInterface& o);

    // operators:
    double& operator[] (Index& i) {
        return(_m_b[i]);
    }

    double& operator[] (int& i) {
        return(_m_b[i]);
    }

    //data manipulation (set) functions:

    virtual void Set(const std::vector<double> &belief);

    virtual void Set(Index sI, double prob) { _m_b[sI]=prob; }

    virtual void Set(const BeliefInterface &belief);
    
    virtual void Set(const StateDistribution& belief);

    //get (data) functions:

    double Get(Index sI) const { return(_m_b.at(sI)); };

    std::vector<double> Get() const { return(_m_b); };

    void Clear();

    std::string SoftPrint() const;

    void Print() const { std::cout << SoftPrint(); }

    unsigned int Size() const { return(_m_b.size()); }

    bool SanityCheck() const;

    double InnerProduct(const std::vector<double> &values) const;

    std::vector<double> InnerProduct(const VectorSet &v) const;

    std::vector<double> InnerProduct(const VectorSet &v,
                                const std::vector<bool> &mask) const;

    BeliefIteratorGeneric GetIterator() const;

    /// Returns a pointer to a copy of this class.
    virtual Belief* Clone() const
        { return new Belief(*this); }

};


#endif /* !_BELIEF_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
