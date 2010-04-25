/**\file BeliefInterface.h
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
 * $Id: BeliefInterface.h 4016 2010-03-11 16:56:02Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _BELIEFINTERFACE_H_
#define _BELIEFINTERFACE_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"
#include "VectorSet.h"

class BeliefIteratorGeneric;
class StateDistribution;

/** \brief BeliefInterface is an interface for beliefs, i.e.,
 * probability distributions over the state space. */
class BeliefInterface
{
private:
    
protected:
    
public:
    // Constructor, destructor and copy assignment.
    /// (default) Constructor
    BeliefInterface(){};
    
    /// Destructor.
    virtual ~BeliefInterface(){};

    /**\brief Copy assignment operator.
     *
     * This must be implemented by the derived class (with this prototype).
     * For an example, see PolicyPoolJPolValPair.
     *
     * For now, this function is purely abstract. Might there be some 
     * members added to this (base) class, then an implementation could
     * be made. This should then be called using
     *          PolicyPoolInterface::operator=(o)
     * from the copy assignment operator of the derived class. See also
     * http://www.icu-project.org/docs/papers/cpp_report/the_assignment_operator_revisited.html.
     */    
    virtual BeliefInterface& operator= (const BeliefInterface& o)=0;

    // operators:

    /// Gets the probability of the i'th state.
    virtual double& operator[] (Index& i) = 0;

    /// Gets the probability of the i'th state.
    virtual double& operator[] (int& i) = 0;

    //data manipulation (set) functions:

    /// Copy the \a belief into this object.
    virtual void Set(const StateDistribution& belief) = 0;

    /// Copy the \a belief into this object.
    virtual void Set(const std::vector<double> &belief) = 0;

    /// Copy the \a belief into this object.
    virtual void Set(const BeliefInterface &belief) = 0;

    /// Sets probability of the \a sI'th state to \a prob .
    virtual void Set(Index sI, double prob) = 0;

    //get (data) functions:

    /// Gets the probability of the sI'th state.
    virtual double Get(Index sI) const = 0;
    /// Gets a vector of probabilities representing the belief.
    virtual std::vector<double> Get() const=0;

    /// Clears the belief.
    virtual void Clear() = 0;

    /// Prints the belief.
    virtual std::string SoftPrint() const = 0;

    /// Prints the belief.
    virtual void Print() const = 0;

    /// Returns the size of this belief.
    virtual unsigned int Size() const = 0;

    /// Checks whether the belief is a valid probability distribution.
    virtual bool SanityCheck() const = 0;

    /// Computes the inner product of a belief with the vector \a values.
    virtual double InnerProduct(const std::vector<double> &values) const = 0;

    /// Computes the inner product of a belief with the VectorSet \a v.
    /** Returns the inner product with each vector in \a v. */
    virtual std::vector<double> InnerProduct(const VectorSet &v) const = 0;
    
    /// Computes the inner product of a belief with the VectorSet \a v.
    /** Returns the inner product with each vector in \a v, but only
     * for vectors whose \a mask is set to true. */
    virtual std::vector<double> InnerProduct(const VectorSet &v,
                                        const std::vector<bool> &mask) const = 0;

    virtual BeliefIteratorGeneric GetIterator() const = 0;

    /// Returns a pointer to a copy of this class.
    virtual BeliefInterface* Clone() const = 0;

};


#endif /* !_BELIEFINTERFACE_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
