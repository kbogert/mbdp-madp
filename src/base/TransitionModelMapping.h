/**\file TransitionModelMapping.h
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
 * $Id: TransitionModelMapping.h 4016 2010-03-11 16:56:02Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _TRANSITIONMODELMAPPING_H_
#define _TRANSITIONMODELMAPPING_H_ 1

/* the include directives */
#include <boost/numeric/ublas/matrix.hpp>
#include "Globals.h"
#include "TransitionModelDiscrete.h"
//#include "TGet.h"
class TGet;
class TGet_TransitionModelMapping;

/// TransitionModelMapping implements a TransitionModelDiscrete.
/** Uses full matrices. */
class TransitionModelMapping : public TransitionModelDiscrete
{
public:

    typedef boost::numeric::ublas::matrix<double> Matrix;

private:

    std::vector<Matrix* > _m_T;

protected:
    
public:
    // Constructor, destructor and copy assignment.
    /// default Constructor
    TransitionModelMapping(int nrS = 1, int nrJA = 1);

    /// Copy constructor.
    TransitionModelMapping(const TransitionModelMapping& TM);

    /// Destructor.
    ~TransitionModelMapping();    
        
    /// Returns P(s'|s,ja)
    double Get(Index sI, Index jaI, Index sucSI) const
        { return((*_m_T[jaI])(sI,sucSI)); }

    //data manipulation funtions:
    ///Sets P(s'|s,ja)
    /**sI, jaI, sucSI, are indices of the state,
     * taken joint action and resulting successor state. prob is 
     * the probability. The order of events is s, ja, s', so is the arg. list
     */
    void Set(Index sI, Index jaI, Index sucSI, double prob)
        { (*_m_T[jaI])(sI,sucSI)=prob; }

    /// Get a pointer to a transition matrix for a particular action.
    const Matrix* GetMatrixPtr(Index a) const
        { return(_m_T.at(a)); }

    /// Returns a pointer to a copy of this class.
    virtual TransitionModelMapping* Clone() const
        { return new TransitionModelMapping(*this); }

    friend class TGet_TransitionModelMapping;
};

#endif /* !_TRANSITIONMODELMAPPING_H_ */


// Local Variables: ***
// mode:c++ ***
// End: ***
