/**\file AlphaVectorPlanning.h
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
 * $Id: AlphaVectorPlanning.h 3633 2009-08-27 12:32:02Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _ALPHAVECTORPLANNING_H_
#define _ALPHAVECTORPLANNING_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"

#include <boost/multi_array.hpp>

#include "VectorSet.h"
#include "BeliefSet.h"
#include "TimedAlgorithm.h"
#include "ValueFunctionPOMDPDiscrete.h"

// for their matrix classes
#include "TransitionModelMapping.h"
#include "TransitionModelMappingSparse.h"
#include "ObservationModelMapping.h"
#include "ObservationModelMappingSparse.h"

class PlanningUnitDecPOMDPDiscrete;
class AlphaVector;
namespace ArgumentHandlers {
    class Arguments;
};

/// Represents back-projected copies of alpha vectors.
typedef boost::multi_array<VectorSet*,2> GaoVectorSet;
/// An index for a GaoVectorSet.
typedef GaoVectorSet::index GaoVectorSetIndex;

/**AlphaVectorPlanning provides base functionality for alpha-vector based
 * POMDP or BG techniques.  */
class AlphaVectorPlanning : public TimedAlgorithm
{
private:

    /**A pointer to the PlanningUnit (which can only be a 
     * #PlanningUnitDecPOMDPDiscrete or derived type).*/
    const PlanningUnitDecPOMDPDiscrete* _m_pu;

    std::vector<const TransitionModelMapping::Matrix* > _m_T;
    std::vector<const ObservationModelMapping::Matrix* > _m_O;

    std::vector<const TransitionModelMappingSparse::SparseMatrix* > _m_Ts;
    std::vector<const ObservationModelMappingSparse::SparseMatrix* > _m_Os;

    typedef boost::numeric::ublas::compressed_vector<double> SparseVector;
    std::vector<std::vector<SparseVector* > > _m_TsForBackup;
    std::vector<std::vector<SparseVector* > > _m_OsForBackup;
    std::vector<std::vector<std::vector<SparseVector* > > > _m_TsOsForBackup;

    bool _m_useSparse;

    GaoVectorSet BackProjectFull(const VectorSet &v) const;
    GaoVectorSet BackProjectSparse(const VectorSet &v) const;

    bool _m_initialized;

    void DeInitialize();

protected:
    
public:
    // Constructor, destructor and copy assignment.
    /// (default) Constructor
    AlphaVectorPlanning(const PlanningUnitDecPOMDPDiscrete& pu);
    /// Destructor.
    virtual ~AlphaVectorPlanning();

    void Initialize();

    /**Returns a ref to the PlanningUnit.*/
    const PlanningUnitDecPOMDPDiscrete* GetPU() const
        { return(_m_pu); }
    
    /// Back projects a value function.
    GaoVectorSet BackProject(const ValueFunctionPOMDPDiscrete &v) const;

    /// Back projects a value function, represented as a VectorSet.
    GaoVectorSet BackProject(const VectorSet &v) const;

    /** Sample a belief set according to the arguments. */
    BeliefSet SampleBeliefs(
        ArgumentHandlers::Arguments args) const;

    /// Compute the cross-sum of two vector sets.
    VectorSet CrossSum(const VectorSet &A, const VectorSet &B) const;

    void MonahanCrossSum(const GaoVectorSet &G,
                         ValueFunctionPOMDPDiscrete &V,
                         Index a,
                         bool doIncPrune) const;

    GaoVectorSet 
    BackProjectMonahan(const QFunctionsDiscrete &Qs) const;

    GaoVectorSet BackProjectMonahan(const ValueFunctionPOMDPDiscrete &V) const;

    /// Prune a valuefunction.
    ValueFunctionPOMDPDiscrete 
    Prune(const ValueFunctionPOMDPDiscrete &V) const;

    /// Prune a VectorSet.
    VectorSet Prune(const VectorSet &V) const;

    /// Exports a value function \a V to file named \a filename.
    static void ExportValueFunction(const std::string & filename,
                                    const ValueFunctionPOMDPDiscrete &V);

    /// Exports a Q functions \a Q to file named \a filename.
    static void ExportValueFunction(const std::string & filename,
                                    const QFunctionsDiscrete &Q);

    /// Exports a Q functions \a Q to file named \a filename.
    static void ExportValueFunction(const std::string & filename,
                                    const QFunctionsDiscreteNonStationary &Q);

    /// Imports a value function from a file named \a filename.
    static ValueFunctionPOMDPDiscrete 
    ImportValueFunction(const std::string & filename);

    static QFunctionsDiscreteNonStationary
    ImportValueFunction(const std::string & filename, size_t nr,
                        size_t nrA, size_t nrS);

    /// Returns the value function induced by the reward model.
    ValueFunctionPOMDPDiscrete GetImmediateRewardValueFunction() const; 

    /// Returns the value function induced by the reward model of \a pu.
    static ValueFunctionPOMDPDiscrete
    GetImmediateRewardValueFunction(const PlanningUnitDecPOMDPDiscrete *pu);

    static ValueFunctionPOMDPDiscrete
    QFunctionsToValueFunction(const QFunctionsDiscrete &Q);

    /// Exports the POMDP represented by \a pu to file named \a filename.
    static void ExportPOMDPFile(const std::string & filename,
                                const PlanningUnitDecPOMDPDiscrete *pu);

    /// Exports the POMDP to file named \a filename.
    void ExportPOMDPFile(const std::string & filename) const;

    /// Exports a belief set to a file.
    static void ExportBeliefSet(const BeliefSet &B,
                                const std::string & filename);

    QFunctionsDiscrete
    ValueFunctionToQ(const ValueFunctionPOMDPDiscrete &V) const;

    static QFunctionsDiscrete 
    ValueFunctionToQ(const ValueFunctionPOMDPDiscrete &V,
                     size_t nrA, size_t nrS);

    static std::vector<int> GetDuplicateIndices(const VectorSet &V);

    static bool VectorIsInValueFunction(const AlphaVector &alpha,
                                        const ValueFunctionPOMDPDiscrete &V);
};

#endif /* !_ALPHAVECTORPLANNING_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
