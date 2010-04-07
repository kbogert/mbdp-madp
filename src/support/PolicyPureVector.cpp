/**\file PolicyPureVector.cpp
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
 * $Id: PolicyPureVector.cpp 3598 2009-08-20 12:29:54Z mtjspaan $
 */

#include "PolicyPureVector.h"
#include "IndexTools.h"
#include <stdlib.h>

using namespace std;

#define DEBUG_PPV 0

using std::stringstream;

PolicyPureVector::PolicyPureVector(
    const Interface_ProblemToPolicyDiscretePure& pu,
    Index agentI,
    PolicyGlobals::IndexDomainCategory idc,
    size_t depth
        ) :
     PolicyDiscretePure(pu,idc, agentI)
{
    Index nrDE = GetInterfacePTPDiscretePure()->
        GetNrPolicyDomainElements(agentI, GetIndexDomainCategory(), depth);
    if(DEBUG_PPV)
        cout << "PolicyPureVector(): creating policy for agent "<<agentI
             << ", depth " << depth << " (nr domain elements "
             << nrDE << ")" << endl;

    _m_agentI = agentI;
    _m_domainToActionIndices = vector<Index>::vector(nrDE, 0);
}

//Copy assignment constructor.    
PolicyPureVector::PolicyPureVector(const PolicyPureVector& o) :
    PolicyDiscretePure(o)
{
    if(DEBUG_PPV)    cout << " clone PolicyPureVector ";
    _m_agentI = o._m_agentI;
    _m_domainToActionIndices =vector<Index>::vector(o._m_domainToActionIndices);
}

//Destructor
PolicyPureVector::~PolicyPureVector()
{
    _m_domainToActionIndices.clear();
}

PolicyPureVector& PolicyPureVector::operator= (const PolicyPureVector& o)
{
    if (this == &o) return *this;   // Gracefully handle self assignment
    // Put the normal assignment duties here...
    PolicyDiscretePure::operator= ( o );
    _m_agentI = o._m_agentI;
    _m_domainToActionIndices = o._m_domainToActionIndices;

    return *this;
}
void PolicyPureVector::ZeroInitialization()
{
if(DEBUG_PPV)cout << ">>>PolicyPureVector::ZeroInitialization(): for agent " 
                              << _m_agentI << endl;
    vector<Index>::iterator it = _m_domainToActionIndices.begin();
    vector<Index>::iterator last = _m_domainToActionIndices.end();

    while(it != last)
    {
        *it = 0;
        it++;
    }
}

void PolicyPureVector::RandomInitialization()
{
    if(DEBUG_PPV)
        cout << ">>>PolicyPureVector::RandomInitialization(): for agent " 
            << _m_agentI << endl;

    Index nrA = GetInterfacePTPDiscretePure()->GetNrActions(_m_agentI);   
    vector<Index>::iterator it = _m_domainToActionIndices.begin();
    vector<Index>::iterator last = _m_domainToActionIndices.end();

    while(it != last)
    {
        int r = rand();
        if(DEBUG_PPV)
            cout << "rand() = " <<r<<endl;
        *it =  r% nrA;
        it++;
    }
}

bool PolicyPureVector::Increment()
{
    bool carry_over = true;
    size_t nrA = GetInterfacePTPDiscretePure()->GetNrActions(_m_agentI);
    size_t nrOH = GetInterfacePTPDiscretePure()->
        GetNrPolicyDomainElements(_m_agentI, GetIndexDomainCategory(),
                                  GetDepth());

    //i is an integer index counting from nrObservationHistories-1 (=the last
    // observation history) to 0
    //(corresponding to the first (empty) observation sequence.
    Index i = nrOH - 1;
    while(carry_over)
    {
        _m_domainToActionIndices[i] = (_m_domainToActionIndices[i] + 1) % nrA;
        carry_over = (_m_domainToActionIndices[i] == 0);
        if(i > 0)
            i--;
        else
            break;
    }
    return(carry_over);
}

LIndex PolicyPureVector::GetIndex() const
{
    int nrO=GetInterfacePTPDiscretePure()->
        GetNrPolicyDomainElements(_m_agentI,
                                  GetIndexDomainCategory(),
                                  GetDepth() ),
        nrA=GetInterfacePTPDiscretePure()->GetNrActions(_m_agentI);
    LIndex i=0;

    vector<LIndex> nrElems(2);
    nrElems[0]=1;
    nrElems[1]=nrA;

    vector<LIndex> indexVec(2);

    for(int o=0;o!=nrO;++o)
    {
        nrElems[0]*=nrO;
        indexVec[0]=i;
        indexVec[1]=_m_domainToActionIndices[o];
        i=IndexTools::IndividualToJointIndices(indexVec,nrElems);
    }
    return(i);
}

void PolicyPureVector::SetIndex(LIndex i)
{
    int nrO=GetInterfacePTPDiscretePure()->
        GetNrPolicyDomainElements(_m_agentI, 
                                  GetIndexDomainCategory(),
                                  GetDepth()),
        nrA=GetInterfacePTPDiscretePure()->GetNrActions(_m_agentI);
    
    vector<LIndex> nrElems(2);
    nrElems[0]=static_cast<LIndex>(pow(static_cast<double>(nrA),nrO));
    nrElems[1]=nrA;
    vector<LIndex> indexVec(2);

    for(int o=nrO-1;o>=0;--o)
    {
        nrElems[0]/=nrO;
        indexVec=IndexTools::JointToIndividualIndices(i,nrElems);
        SetAction(o,indexVec[1]);
        i=indexVec[0];
    }
}

void PolicyPureVector::SetDepth(size_t d)
{
    Policy::SetDepth(d);
    _m_domainToActionIndices.resize(
        GetInterfacePTPDiscretePure()->GetNrPolicyDomainElements(
            _m_agentI,
            GetIndexDomainCategory(),
            d));
}

string PolicyPureVector::SoftPrint() const
{
    vector<Index>::const_iterator it = _m_domainToActionIndices.begin();
    vector<Index>::const_iterator last = _m_domainToActionIndices.end();
   
    //const ObservationHistoryTree* oht;
    Index dIndex = 0;

    stringstream ss;

    while(it != last)
    {
        ss << GetInterfacePTPDiscretePure()->SoftPrintPolicyDomainElement
            (_m_agentI, dIndex, GetIndexDomainCategory() );
        ss << " --> ";
        ss << GetInterfacePTPDiscretePure()->SoftPrintAction(_m_agentI, *it);
        ss << endl;
                
        it++;
        dIndex++;
    }
    return(ss.str());
}

