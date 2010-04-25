/**\file BeliefSparse.h
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
 * $Id: BeliefSparse.h 4016 2010-03-11 16:56:02Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _BELIEFSPARSE_H_
#define _BELIEFSPARSE_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"
#include "BeliefInterface.h"

#include <boost/numeric/ublas/vector_sparse.hpp>
#include <boost/numeric/ublas/io.hpp>

class BeliefIteratorSparse;
class StateDistribution;

/// BeliefSparse represents a probability distribution over the state space.
/** It is stored as a sparse vector. */
class BeliefSparse : virtual public BeliefInterface
{
private:    

    friend class BeliefIteratorSparse;

protected:

#if BOOST_1_32_OR_LOWER // they renamed sparse_vector to mapped_vector
    typedef boost::numeric::ublas::sparse_vector<double> BS;
#else    
    typedef boost::numeric::ublas::compressed_vector<double> BS;
#endif    

    typedef BS::const_iterator BScit;
    typedef BS::iterator BSit;
    
    /// The sparse vector to store the belief.
    BS _m_b;
    
public:

    /// Default Constructor
    BeliefSparse();

    /// Constructor which sets the \a size of the joint belief.
    BeliefSparse(size_t size);
        
    /// Constructor which copies \a belief in this joint belief.
    BeliefSparse(const std::vector<double> &belief);

    /// Constructor which copies \a belief in this joint belief.
    BeliefSparse(const BeliefInterface &belief);
    BeliefSparse(const StateDistribution& belief);

    /// Destructor.
    ~BeliefSparse();

    // operators:
    BeliefSparse& operator= (const BeliefSparse& o);
    BeliefInterface& operator= (const BeliefInterface& o);

#if BOOST_1_32_OR_LOWER 
    // uses sparse_vector instead of mapped_vector. The former, however, does
    // not define .ref()
    double& operator[] (Index& i) {
        return 
            //_m_b(i); 
            //_m_b.BS::operator[](i);
            *_m_b.find_element(i);
    }

    double& operator[] (int& i) {
        return 
            //_m_b(i); 
            //_m_b.BS::operator()(i);
            *_m_b.find_element(i);
    }
#else    
    double& operator[] (Index& i) {
        return _m_b.ref(i); //_m_b.BS::operator[](i);
    }

    double& operator[] (int& i) {
        return _m_b.ref(i); //_m_b.BS::operator[](i);
    }
#endif

    //data manipulation (set) functions:
    void Set(const BS &belief);

    void Set(const std::vector<double> &belief);

    void Set(Index sI, double prob) { _m_b[sI]=prob; }

    void Set(const BeliefInterface &belief);
    
    virtual void Set(const StateDistribution& belief);

    //get (data) functions:

    double Get(Index sI) const { return(_m_b[sI]); };
    std::vector<double> Get() const 
    { 
        throw E("BeliefSparse::Get() is not yet implemented");
    };

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
    virtual BeliefSparse* Clone() const
        { return new BeliefSparse(*this); }

};


#endif /* !_BELIEFSPARSE_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
