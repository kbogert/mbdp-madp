/**\file BeliefIteratorSparse.h
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
 * $Id: BeliefIteratorSparse.h 4016 2010-03-11 16:56:02Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _BELIEFITERATORSPARSE_H_
#define _BELIEFITERATORSPARSE_H_ 1

/* the include directives */
#include "Globals.h"
#include "BeliefIteratorInterface.h"
#include "BeliefSparse.h"

#define BeliefIteratorSparse_UseCIT 0

/** \brief BeliefIteratorSparse is an iterator for sparse beliefs. */
class BeliefIteratorSparse : public BeliefIteratorInterface
{
private:    

#if BeliefIteratorSparse_UseCIT
    BeliefSparse::BScit _m_it;
#else
    Index _m_i;
#endif
    const BeliefSparse *_m_belief;

protected:
    
public:

    // Constructor, destructor and copy assignment.
    /// (default) Constructor
#if BeliefIteratorSparse_UseCIT
    BeliefIteratorSparse(const BeliefSparse *b) : _m_belief(b)
        {
            _m_it=_m_belief->_m_b.begin();
        }
#else
    BeliefIteratorSparse(const BeliefSparse *b) : _m_i(0), _m_belief(b)
        {
            if(_m_belief->_m_b.nnz()==0)
                throw(E("BeliefIteratorSparse ctor: belief is empty"));
        }
#endif

    /// Destructor.
    virtual ~BeliefIteratorSparse(){}

#if BeliefIteratorSparse_UseCIT
    double GetProbability() const { return(*_m_it); }
    Index GetStateIndex() const { return(_m_it.index()); }
    bool Next()
        {
            _m_it++;
            if(_m_it==_m_belief->_m_b.end())
                return(false);
            else
                return(true);
        }
#else
    double GetProbability() const { return(_m_belief->
                                           _m_b.value_data()[_m_i]); }
    Index GetStateIndex() const { return(_m_belief->
                                         _m_b.index_data()[_m_i]); }
    bool Next()
        {
            if(_m_i>=(_m_belief->_m_b.nnz()-1))
                return(false);
            else
            {
                _m_i++;
                return(true);
            }
        }
#endif
    /// Returns a pointer to a copy of this class.
    virtual BeliefIteratorSparse* Clone() const
        { return new BeliefIteratorSparse(*this); }


};

#endif /* !_BELIEFITERATORSPARSE_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
