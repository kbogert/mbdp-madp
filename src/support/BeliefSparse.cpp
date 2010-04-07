/**\file BeliefSparse.cpp
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
 * $Id: BeliefSparse.cpp 3611 2009-08-25 15:02:24Z mtjspaan $
 */

#include "BeliefSparse.h"
#include "BeliefIteratorSparse.h"
#include "BeliefIteratorGeneric.h"
#include <float.h>
#include "StateDistributionVector.h"

#define BeliefSparse_CheckAndAbort 0

using namespace std;

BeliefSparse::BeliefSparse()
{
}

BeliefSparse::BeliefSparse(size_t size)
{
    _m_b.resize(size,false);
}

BeliefSparse::BeliefSparse(const vector<double> &belief)
{
    _m_b.resize(belief.size(),false);

    unsigned int i=0;
    for(vector<double>::const_iterator it=belief.begin();
        it!=belief.end(); ++it)
    {
        if(*it>0)
            _m_b[i]=*it;
        ++i;
    }
#if BeliefSparse_CheckAndAbort
    if(!SanityCheck())
        abort();
#endif
}


BeliefSparse::BeliefSparse(const BeliefInterface &belief)
{
    Set(belief);
}
BeliefSparse::BeliefSparse(const StateDistribution& belief)
{
    this->Set(belief);
}


//Destructor
BeliefSparse::~BeliefSparse()
{
}

BeliefSparse& 
BeliefSparse::operator= (const BeliefSparse& o)
{
    if (this == &o) return *this;   // Gracefully handle self assignment
    // Put the normal assignment duties here...
    _m_b = o._m_b;
    return *this;
}

BeliefInterface& 
BeliefSparse::operator= (const BeliefInterface& o)
{
    if (this == &o) return *this;   // Gracefully handle self assignment
    const BeliefSparse& casted_o = 
        dynamic_cast<const BeliefSparse&>(o);
    return(operator=(casted_o));// call the operator= for BeliefSparse
}

void BeliefSparse::Set(const BS &belief)
{
    _m_b=belief;
#if BeliefSparse_CheckAndAbort
    if(!SanityCheck())
        abort();
#endif
}

void BeliefSparse::Set(const vector<double> &belief)
{
    _m_b.resize(belief.size(),false);
    _m_b.clear();

    unsigned int i=0;
    for(vector<double>::const_iterator it=belief.begin();
        it!=belief.end(); ++it)
    {
        if(*it>0)
            _m_b[i]=*it;
        ++i;
    }
#if BeliefSparse_CheckAndAbort
    if(!SanityCheck())
        abort();
#endif
}

void BeliefSparse::Set(const StateDistribution& belief)
{
    try{
        const StateDistributionVector& b = 
            dynamic_cast<const StateDistributionVector&>( belief );
        this->Set( (vector<double>) b );
        return;
    }
    catch(exception e)
    {
        //TODO loop over all states and set probability
        throw E("BeliefSparse::Set(const StateDistribution& belief) - inumplemented case.");
    }
}


void BeliefSparse::Set(const BeliefInterface &belief)
{
    _m_b.resize(belief.Size(),false);
    _m_b.clear();

    for(unsigned int i=0; i!=belief.Size(); ++i)
    {
        if(belief.Get(i)>0)
            _m_b[i]=belief.Get(i);
    }
#if BeliefSparse_CheckAndAbort
    if(!SanityCheck())
        abort();
#endif
}

void BeliefSparse::Clear()
{
    _m_b.clear();
}

string BeliefSparse::SoftPrint() const
{
#if BeliefSparse_CheckAndAbort
    if(!SanityCheck())
        abort();
#endif
    stringstream ss;
    ss << "[" << _m_b.size() << "]< ";
    for(BScit it=_m_b.begin();
        it!=_m_b.end(); ++it)
        ss << it.index() << ":" << *it << " ";
    ss << ">";
    return(ss.str());
}

bool BeliefSparse::SanityCheck() const
{
    // check for negative and entries>1
    double sum=0;
    for(BScit it=_m_b.begin();
        it!=_m_b.end(); ++it)
    {
        if(*it<0)
            return(false);
        if(*it>1)
            return(false);
		if(_isnan(*it))
            return(false);
        sum+=*it;
    }

    // check if sums to 1
    if(abs(sum-1)>PROB_PRECISION)
        return(false);

    // check whether the size is not zero
    if(_m_b.size()==0)
        return(false);

    // if we haven't returned yet, the belief is fine
    return(true);
}

double BeliefSparse::InnerProduct(const vector<double> &values) const
{
#if BeliefSparse_CheckAndAbort
    if(!SanityCheck())
        abort();
#endif
    double x=0;
    for(BScit it=_m_b.begin(); it!=_m_b.end(); ++it)
        x+=(*it)*values[it.index()];

    return(x);
}

vector<double> BeliefSparse::InnerProduct(const VectorSet &v) const
{
    vector<double> values(v.size1());

    double x;
    for(unsigned int k=0;k!=v.size1();++k)
    {
        x=0;
        for(BScit it=_m_b.begin(); it!=_m_b.end(); ++it)
            x+=(*it)*v(k,it.index());
        values[k]=x;
    }

    return(values);
}

vector<double> BeliefSparse::InnerProduct(const VectorSet &v,
                                          const vector<bool> &mask) const
{
    vector<double> values(v.size1(),-DBL_MAX);

    double x;
    for(unsigned int k=0;k!=v.size1();++k)
    {
        if(mask[k])
        {
            x=0;
            for(BScit it=_m_b.begin(); it!=_m_b.end(); ++it)
                x+=(*it)*v(k,it.index());
            values[k]=x;
        }
    }

    return(values);
}

BeliefIteratorGeneric BeliefSparse::GetIterator() const
{
    return(BeliefIteratorGeneric(new BeliefIteratorSparse(this))); 
}
