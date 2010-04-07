/**\file ObservationModelMappingSparse.h
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
 * $Id: ObservationModelMappingSparse.h 4016 2010-03-11 16:56:02Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _OBSERVATIONMODELMAPPINGSPARSE_H_
#define _OBSERVATIONMODELMAPPINGSPARSE_H_ 1

/* the include directives */
#include "Globals.h"
#include "ObservationModelDiscrete.h"
#include <boost/numeric/ublas/matrix_sparse.hpp>
class OGet;
class OGet_ObservationModelMapping;

/// ObservationModelMappingSparse implements an ObservationModelDiscrete.
/** Uses sparse matrices. */
class ObservationModelMappingSparse : 
    public ObservationModelDiscrete
{
public:
#if BOOST_1_32_OR_LOWER // they renamed sparse_vector to mapped_vector
    typedef boost::numeric::ublas::sparse_matrix<double> SparseMatrix;
#else    
    typedef boost::numeric::ublas::compressed_matrix<double> SparseMatrix;
#endif    


private:

    std::vector<SparseMatrix* > _m_O;
    
protected:
    
public:
    // Constructor, destructor and copy assignment.
    /// default Constructor
    ObservationModelMappingSparse(int nrS = 1, int nrJA = 1, int nrJO = 1);

    /// Copy constructor.
    ObservationModelMappingSparse(const ObservationModelMappingSparse& OM);
    /// Destructor.
    ~ObservationModelMappingSparse();
    
    /// Returns P(jo|ja,s')
    double Get(Index ja_i, Index suc_s_i, Index jo_i) const
        { return((*_m_O[ja_i])(suc_s_i,jo_i)); }

    //data manipulation funtions:
    /// Sets P(o|ja,s')
    /** jo_i, Index ja_i, Index suc_s_i, are indices of the joint
     * observation, taken joint action and resulting successor
     * state. prob is the probability. The order of events is ja, s',
     * o, so is the arg. list
     */
    void Set(Index ja_i, Index suc_s_i, Index jo_i, double prob)
        {
            // make sure probability is not 0
            if(prob > PROB_PRECISION)
                (*_m_O[ja_i])(suc_s_i,jo_i)=prob;
        }
        
    /// Get a pointer to a transition matrix for a particular action.
    const SparseMatrix* GetMatrixPtr(Index a) const
        { return(_m_O.at(a)); }

    /// Returns a pointer to a copy of this class.
    virtual ObservationModelMappingSparse* Clone() const
        { return new ObservationModelMappingSparse(*this); }

    friend class OGet_ObservationModelMappingSparse;
};

#endif /* !_OBSERVATIONMODELMAPPINGSPARSE_H_*/

// Local Variables: ***
// mode:c++ ***
// End: ***

