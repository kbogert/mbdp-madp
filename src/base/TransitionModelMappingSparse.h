/**\file TransitionModelMappingSparse.h
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
 * $Id: TransitionModelMappingSparse.h 4016 2010-03-11 16:56:02Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _TRANSITIONMODELMAPPINGSPARSE_H_
#define _TRANSITIONMODELMAPPINGSPARSE_H_ 1

/* the include directives */
#include "Globals.h"
#include "TransitionModelDiscrete.h"
#include <boost/numeric/ublas/matrix_sparse.hpp>
//#include "TGet.h"
class TGet;
class TGet_TransitionModelMappingSparse;

/// TransitionModelMappingSparse implements a TransitionModelDiscrete.
/** Uses sparse matrices. */
class TransitionModelMappingSparse : public TransitionModelDiscrete
{
public:

#if BOOST_1_32_OR_LOWER // they renamed sparse_vector to mapped_vector
    typedef boost::numeric::ublas::sparse_matrix<double> SparseMatrix;
#else    
    typedef boost::numeric::ublas::compressed_matrix<double> SparseMatrix;
#endif    

private:
    
    std::vector<SparseMatrix* > _m_T;

protected:
    
public:
    // Constructor, destructor and copy assignment.
    /// default Constructor
    TransitionModelMappingSparse(int nrS = 1, int nrJA = 1);

    /// Copy constructor.
    TransitionModelMappingSparse(const TransitionModelMappingSparse& TM);

    /// Destructor.
    ~TransitionModelMappingSparse();    
        
    /// Returns P(s'|s,ja).
    double Get(Index sI, Index jaI, Index sucSI) const
        { return((*_m_T[jaI])(sI,sucSI)); }

    ////data manipulation funtions:
    /// Sets P(s'|s,ja) 
    /** sI, jaI, sucSI, are indices of the state, taken joint action
     * and resulting successor state. prob is the probability. The
     * order of events is s, ja, s', so is the arg. list
     */
    void Set(Index sI, Index jaI, Index sucSI, double prob)
        {
            // make sure probability is not 0
            if(prob > PROB_PRECISION)
                (*_m_T[jaI])(sI,sucSI)=prob;
        }

    /// Get a pointer to a transition matrix for a particular action.
    const SparseMatrix* GetMatrixPtr(Index a) const
        { return(_m_T.at(a)); }

    /// Returns a pointer to a copy of this class.
    virtual TransitionModelMappingSparse* Clone() const
        { return new TransitionModelMappingSparse(*this); }

    friend class TGet_TransitionModelMappingSparse;

};

#endif /* !_TRANSITIONMODELMAPPINGSPARSE_H_ */


// Local Variables: ***
// mode:c++ ***
// End: ***
