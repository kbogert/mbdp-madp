/**\file JointPolicyDiscrete.cpp
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
 * $Id: JointPolicyDiscrete.cpp 4016 2010-03-11 16:56:02Z mtjspaan $
 */

#include "JointPolicyDiscrete.h"
#include "PolicyDiscrete.h"
using namespace std;

//Default constructor
JointPolicyDiscrete::JointPolicyDiscrete(const 
        Interface_ProblemToPolicyDiscrete& iptpd,
        PolicyGlobals::IndexDomainCategory idc )
    :
    JointPolicy(iptpd.GetNrAgents())
    ,_m_indexDomCat( idc )
    ,_m_PTPD(&iptpd)
{
    _m_nrAgents = _m_PTPD->GetNrAgents();
}
//Copy  constructor.    
JointPolicyDiscrete::JointPolicyDiscrete(const JointPolicyDiscrete& o) 
    :
    JointPolicy(o)
    ,_m_indexDomCat(o._m_indexDomCat)
    ,_m_PTPD(o._m_PTPD)
{
}

JointPolicyDiscrete&
JointPolicyDiscrete::operator= (const JointPolicyDiscrete& o)
{
    if (this == &o) return *this;   // Gracefully handle self assignment
    JointPolicy::operator= ( o );   //call parent
    _m_indexDomCat = o._m_indexDomCat;
    _m_PTPD = o._m_PTPD;
    return *this;
}

void
JointPolicyDiscrete::SampleJointActionVector( 
        const vector<Index>& indivDomIndices , 
        vector<Index>& sampled_aIs  ) const
{
    sampled_aIs.resize(_m_nrAgents);
    for(Index agI=0; agI < _m_nrAgents; agI++)
    {
        PolicyDiscrete* p = GetIndividualPolicyDiscrete(agI);
        Index agI_domI = indivDomIndices.at(agI);
        sampled_aIs.at(agI) = p->SampleAction(agI_domI);
    }
    return;
}

Index JointPolicyDiscrete::SampleJointAction( 
        const vector<Index>& indivDomIndices  ) const
{
    vector<Index> sampled_aIs;
    SampleJointActionVector(indivDomIndices, sampled_aIs);
    Index ja = _m_PTPD->IndividualToJointActionIndices(sampled_aIs);
    return ja;

}
void
JointPolicyDiscrete::SampleJointActionVector( Index i, 
       vector<Index>& sampled_aIs ) const
{

    if( _m_PTPD->AreCachedJointToIndivIndices(_m_indexDomCat) )
    {
        const vector<Index>& indivDomIndices = _m_PTPD->
            JointToIndividualPolicyDomainIndicesRef (i, _m_indexDomCat);
        return( SampleJointActionVector( indivDomIndices, sampled_aIs) );
    }
    else
    {
        vector<Index> indivDomIndices = _m_PTPD->    
            JointToIndividualPolicyDomainIndices(i, _m_indexDomCat);
        return( SampleJointActionVector( indivDomIndices, sampled_aIs) );
    }
            
}
Index JointPolicyDiscrete::SampleJointAction( Index i ) const
{
    if( _m_PTPD->AreCachedJointToIndivIndices(_m_indexDomCat) )
    {
        const vector<Index>& indivDomIndices = _m_PTPD->
            JointToIndividualPolicyDomainIndicesRef (i, _m_indexDomCat);
        return( SampleJointAction( indivDomIndices) );
    }
    else
    {
        vector<Index> indivDomIndices = _m_PTPD->    
            JointToIndividualPolicyDomainIndices(i, _m_indexDomCat);
        return( SampleJointAction( indivDomIndices) );
    }
            
}
