/**\file AlphaVector.cpp
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
 * $Id: AlphaVector.cpp 2320 2008-02-25 17:01:34Z mtjspaan $
 */

#include "AlphaVector.h"

using namespace std;

/// Default constructor
AlphaVector::AlphaVector()
{
    _m_values.assign(0,0);
    _m_betaI=-1;
}

AlphaVector::AlphaVector(size_t nrS)
{
    _m_values.assign(nrS,0);
    _m_betaI=-1;
}

AlphaVector::AlphaVector(size_t nrS, double val)
{
    _m_values.assign(nrS,val);
    _m_betaI=-1;
}

//Destructor
AlphaVector::~AlphaVector()
{
}
//Copy assignment operator
AlphaVector& AlphaVector::operator= (const AlphaVector& o)
{
    if (this == &o) return *this;   // Gracefully handle self assignment
    // Put the normal assignment duties here...

    this->_m_action=o._m_action;
    this->_m_values=o._m_values;
    this->_m_betaI=o._m_betaI;

    return *this;
}

string AlphaVector::SoftPrint() const
{
    stringstream ss;
    ss << "a " << _m_action << " bI " << _m_betaI
       << " : values";
    vector<double>::const_iterator it=_m_values.begin();
    while(it!=_m_values.end())
    {
        ss << " " << *it;
        it++;
    }
    return(ss.str());
}

void AlphaVector::SetValues(const vector<double> &vs)
{
    if(vs.size()!=_m_values.size())
        throw(E("AlphaVector::SetValues vector sizes do not match"));
    else
        _m_values=vs;
}
    
bool AlphaVector::Equal(const AlphaVector &alpha) const
{
    if(this->GetNrValues()!=alpha.GetNrValues())
        return(false);

    if(this->GetAction()!=alpha.GetAction())
        return(false);

    if(this->GetBetaI()!=alpha.GetBetaI())
        return(false);

    vector<double> values=alpha.GetValues();

    if(_m_values!=values)
        return(false);

    // else
    return(true);
}
