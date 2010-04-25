/**\file IndexTools.h
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
 * $Id: IndexTools.h 3598 2009-08-20 12:29:54Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _INDEXTOOLS_H_
#define _INDEXTOOLS_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"

/// IndexTools contains functionality for manipulating indices.
/** A detailed description of how joint indices etc are constructed,
 * see doc/manually_maintained/MADPToolbox-Histories+indices.ps.gz .
 */
namespace IndexTools {
    /// Increments index which ranges over nrElems
    bool Increment(Index& index, size_t nrElems);

    /// Increments vector of indices that range over nrElems
    bool Increment(std::vector<Index>& indexVec, const std::vector<size_t>& nrElems );

    /// Convert individual to joint indices.
    Index IndividualToJointIndices(const std::vector<Index>& indices, 
            const std::vector<size_t>& nrElems);
    /// Convert individual to joint indices. Only uses first n entries of vecs.
    Index IndividualToJointIndices(const std::vector<Index>& indices, 
            const std::vector<size_t>& nrElems, size_t n);
    /// A variant that takes an array instead of a vector for extra speed.
    Index IndividualToJointIndicesArray(const Index* indices,
            const std::vector<size_t>& nrElems); 
    ///A variant that takes a cached step_size vector for extra speed.
    Index IndividualToJointIndicesStepSize(const std::vector<Index>& indices, 
            const std::vector<size_t>& step_size);
    ///A variant that takes a cached step_size array for extra speed.
    Index IndividualToJointIndicesStepSize(const std::vector<Index>& indices, 
            const size_t * step_size);
    /** \brief A variant that 1) takes an array instead of a vector 
     * and 2) takes a cached step_size array for extra speed.*/
    Index IndividualToJointIndicesArrayStepSize(const Index* indices,
            const size_t * step_size, size_t vec_size); 

    /// A variant with a step_size vector.
    Index IndividualToJointIndicesArrayStepSize(const Index* indices,
            const std::vector<size_t> &step_size, size_t vec_size); 

    ///The reverse of IndividualToJointIndices. 
    std::vector<Index> JointToIndividualIndices(Index jointI, 
            const std::vector<size_t>& nrElems );
    /** \brief The reverse of IndividualToJointIndices - taking the
     * stepSize array as an argument. */
    std::vector<Index> JointToIndividualIndicesStepSize(Index jointI, 
            const size_t * stepSize, size_t vec_size ) ;
    /** \brief The reverse of IndividualToJointIndices - taking the
     * stepSize array as an argument. */
    std::vector<Index> JointToIndividualIndicesStepSize(
            Index jointI, 
            const std::vector<size_t> &stepSize, 
            size_t  vec_size  
            ) ;

    std::vector<Index> JointToIndividualIndicesStepSize(
            Index jointI, 
            const std::vector<size_t> &stepSize
            );
    /** \brief The reverse of IndividualToJointIndices - taking the
     * stepSize array as an argument and returning a pointer to a
     * array.
     *
     * Note: the returned array is allocate with new, so it must be
     * freed.*/
    const Index * JointToIndividualIndicesArrayStepSize(Index jointI, 
            const size_t * stepSize, size_t vec_size ) ;

    /** \brief Calculates the step size array for nrElems. (so is of
     * the same size as nrElems).
     */
    size_t * CalculateStepSize(const std::vector<size_t>& nrElems);
    /**\brief Calculates the step size array from the first n entries 
     * of nrElems. 
     * (so the array's size is n).
     */
    size_t * CalculateStepSize(const std::vector<size_t>& nrElems, size_t n);

    // LIndex versions of all functions

    /// LIndex equivalent function.
    bool Increment(LIndex& index, LIndex& nrElems );
    /// LIndex equivalent function.
    bool Increment(std::vector<LIndex>& indexVec, std::vector<LIndex>& nrElems );

    /// LIndex equivalent function.
    LIndex IndividualToJointIndices(const std::vector<LIndex>& indices, 
            const std::vector<LIndex>& nrElems) ;
    /// LIndex equivalent function.
    LIndex IndividualToJointIndicesArray(LIndex* indices,
            const std::vector<LIndex>& nrElems); 
    /// LIndex equivalent function.
    LIndex IndividualToJointIndicesStepSize(const std::vector<LIndex>& indices, 
            const std::vector<LIndex>& step_size) ;
    /// LIndex equivalent function.
    LIndex IndividualToJointIndicesStepSize(const std::vector<LIndex>& indices, 
            const LIndex * step_size) ;
    /// LIndex equivalent function.
    LIndex IndividualToJointIndicesArrayStepSize(LIndex* indices,
            const LIndex * step_size, LIndex vec_size); 
    /// LIndex equivalent function.
    LIndex IndividualToJointIndicesArrayStepSize(LIndex* indices,
            const std::vector<LIndex> &step_size, LIndex vec_size);
    /// LIndex equivalent function.
    const LIndex * JointToIndividualIndicesArrayStepSize(
            LIndex jointI, 
            const LIndex * stepSize, LIndex vec_size ) ;
    /// LIndex equivalent function.
    std::vector<LIndex> JointToIndividualIndicesStepSize(LIndex jointI, 
            const LIndex * stepSize, LIndex vec_size ) ;
    /// LIndex equivalent function.
    std::vector<LIndex> JointToIndividualIndicesStepSize(LIndex jointI, 
            const std::vector<LIndex> &stepSize, LIndex vec_size ) ;
    std::vector<LIndex> JointToIndividualIndicesStepSize(LIndex jointI, 
            const std::vector<LIndex> &stepSize);
    /// LIndex equivalent function.
    std::vector<LIndex> JointToIndividualIndices(LIndex jointI, 
            const std::vector<LIndex>& nrElems ) ;
    /// LIndex equivalent function.
    LIndex * CalculateStepSize(const std::vector<LIndex>& nrElems);

    /** \brief Computation of a index for (joint) actionObservations 
     *
     * ActionObservation indices (aoI's) are used as the basis for indexing
     * (Joint)ActionObservationHistories.
     * This function computes them.
     *
     * \sa manually maintained documentation
     */
    Index ActionAndObservation_to_ActionObservationIndex(Index aI, 
            Index oI, size_t nrA, size_t nrO);

    /// Convert (joint)  ActionObservation indices to (joint) Action indices.
    Index ActionObservation_to_ActionIndex(Index aoI, size_t nrA, size_t nrO);

    /** \brief Convert (joint) ActionObservation indices to (joint)
     * Observation indices.
     */
    Index ActionObservation_to_ObservationIndex(Index aoI, size_t nrA,size_t nrO);
    
    /** \brief Calculate the number of sequences of length up to
     * seqLength, for which at every time step o options are
     * available.
     *
     * Calculation includes 1 empty sequence (of length 0). * 
     *
     */
    size_t CalculateNumberOfSequences(size_t o, size_t seqLength);

}

#endif /* !_INDEXTOOLS_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
