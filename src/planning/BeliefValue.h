/**\file BeliefValue.h
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
 * $Id: BeliefValue.h 2310 2008-02-21 18:57:12Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _BELIEFVALUE_H_
#define _BELIEFVALUE_H_ 1

/* the include directives */
#include "BeliefSet.h"
#include "VectorSet.h"
#include "ValueFunctionPOMDPDiscrete.h"

class AlphaVector;
class JointBeliefInterface;

/**BeliefValue is a namespace for functions that compute the value of
 * a particular belief.*/
namespace BeliefValue 
{
    /// Get the values of the \a Beliefs for value function \a V.
    std::vector<double> GetValues(const BeliefSet &Beliefs,
                                  const ValueFunctionPOMDPDiscrete &V);
    /// Get the values of the \a Beliefs for alpha vector \a alpha.
    std::vector<double> GetValues(const BeliefSet &Beliefs,
                                  const AlphaVector &alpha);

    /// Get the values of the \a Beliefs for q functions \a Q.
    std::vector<double> GetValues(const BeliefSet &Beliefs,
                                  const QFunctionsDiscrete &Q);

    /// Get the value of a single \a Belief for alpha vecotr \a alpha.
    double GetValue(const JointBeliefInterface &Belief,
                    const AlphaVector &alpha);

    /// Get the value of a single \a Belief for value function \a V.
    double GetValue(const JointBeliefInterface &Belief,
                    const ValueFunctionPOMDPDiscrete &V);

    /// Get the value of a single \a Belief for q functions \a Q.
    double GetValue(const JointBeliefInterface &Belief,
                    const QFunctionsDiscrete &Q);

    /// Get the value of a single \a Belief for non-stationary q functions \a Q.
    double GetValue(const JointBeliefInterface &Belief,
                    const QFunctionsDiscreteNonStationary &Q,
                    Index t);

    /// Get the value of a single \a Belief for \a V given the \a mask.
    double GetValue(const JointBeliefInterface &Belief,
                    const ValueFunctionPOMDPDiscrete &V,
                           const std::vector<bool> mask);

    /// Get the value of a \a Belief for \a v given the \a mask.
    double GetValue(const JointBeliefInterface &Belief,
                    const VectorSet &v,
                    const std::vector<bool> mask);

    /** Returns the index of the vector in \a v that maximizes the
     *  value of \a b. */
    int GetMaximizingVectorIndex(const JointBeliefInterface &b, 
                                 const VectorSet &v);

    int GetMaximizingVectorIndex(const JointBeliefInterface &b, 
                                 const ValueFunctionPOMDPDiscrete &V);

    /** Returns the index of the vector in \a v that maximizes the
     * value of \a b. Only vectors whose \a mask is true will be
     * considered. */
    int GetMaximizingVectorIndex(const JointBeliefInterface &b, 
                                 const VectorSet &v,
                                 const std::vector<bool> &mask);
    
    int GetMaximizingVectorIndexAndValue(const JointBeliefInterface &b, 
                                         const VectorSet &v,
                                         const std::vector<bool> &mask,
                                         double &value);
    
    /** Returns the alpha vector from \a V that maximizes the value of
     *  the \a k 'th belief in set \a S. */
    AlphaVector GetMaximizingVector(const BeliefSet &S,
                                    int k,
                                    const ValueFunctionPOMDPDiscrete &V);
}

#endif /* !_BELIEFVALUE_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
