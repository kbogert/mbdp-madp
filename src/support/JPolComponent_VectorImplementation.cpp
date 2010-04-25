/**\file JPolComponent_VectorImplementation.cpp
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
 * $Id: JPolComponent_VectorImplementation.cpp 3604 2009-08-25 10:52:24Z mtjspaan $
 */

#include "JPolComponent_VectorImplementation.h"
#include "IndexTools.h"
using namespace std;


void JPolComponent_VectorImplementation::Construct(        
        const Interface_ProblemToPolicyDiscretePure& pu,
        PolicyGlobals::IndexDomainCategory idc,
        size_t depth
    )
{
    _m_idc = idc;
    for(Index agI = 0; agI < pu.GetNrAgents(); agI++)
    {
        PolicyPureVector* pol =
            new PolicyPureVector(pu, agI, idc,
                                 depth);
        _m_indivPols_PolicyPureVector.at(agI) = pol;
    }
    //allocate a new array for temporarily storing indiv. actions
    _m_indivActionIndices = new Index[pu.GetNrAgents()];    
}

JPolComponent_VectorImplementation::JPolComponent_VectorImplementation(
    const Interface_ProblemToPolicyDiscretePure& pu,
    size_t depth)
    : 
    _m_PTPDP(&pu)
    , _m_indivPols_PolicyPureVector(pu.GetNrAgents())
{
    Construct( pu, pu.GetDefaultIndexDomCat(), depth);
}

JPolComponent_VectorImplementation::JPolComponent_VectorImplementation(
        const Interface_ProblemToPolicyDiscretePure& pu,
        PolicyGlobals::IndexDomainCategory idc,
        size_t depth
        )
    :
    _m_PTPDP(&pu)
    , _m_indivPols_PolicyPureVector(pu.GetNrAgents())
{
    Construct( pu, idc, depth);
}

//Copy constructor.    
JPolComponent_VectorImplementation::JPolComponent_VectorImplementation(const JPolComponent_VectorImplementation& o) 
{
    
    // we want to create an actual clone of this joint policy and thus
    // of the member (individual policies)
    this->PrivClone(o);
}

void JPolComponent_VectorImplementation::PrivClone(const JPolComponent_VectorImplementation& o)
{
    _m_idc = o._m_idc;
    _m_PTPDP = o._m_PTPDP;
    _m_indivPols_PolicyPureVector.resize(
            o._m_indivPols_PolicyPureVector.size() );

    vector<PolicyPureVector*>::const_iterator it = 
    o._m_indivPols_PolicyPureVector.begin();
    vector<PolicyPureVector*>::const_iterator last = 
    o._m_indivPols_PolicyPureVector.end();

    Index i=0;
    while(it != last)
    {
        //make a copy of the individual policy
        PolicyPureVector* ind_pol = new PolicyPureVector(**it);
        //store the reference to the new copy 
        _m_indivPols_PolicyPureVector[i] = (ind_pol);
        it++; 
        i++;
    }
    //allocate a new array for temporarily storing indiv. actions
    _m_indivActionIndices = new Index[ _m_PTPDP->GetNrAgents() ];
       
}
//Destructor
JPolComponent_VectorImplementation::~JPolComponent_VectorImplementation()
{
    //prevent memory leakage... should delete the individual policies referred 
    //to...
    ClearIndividualPolicies();
    delete [] _m_indivActionIndices;
}

void JPolComponent_VectorImplementation::ClearIndividualPolicies()
{
    //NOTE: this means that when adding a ind. policy p to the joint policy (or 
    //replacing one) we should make a copy of p and insert the ref to this copy.
    //Otherwise deleting the joint policy deletes the individual policies, 
    //whose other references become dangling.
    vector<PolicyPureVector*>::iterator it = 
        _m_indivPols_PolicyPureVector.begin();
    vector<PolicyPureVector*>::iterator last = 
        _m_indivPols_PolicyPureVector.end();

    while(it != last)
    {
        delete (*it);
        it++;
    }
    _m_indivPols_PolicyPureVector.clear();    

}



//Copy assignment operator
JPolComponent_VectorImplementation& JPolComponent_VectorImplementation::operator= (const JPolComponent_VectorImplementation& o)
{
    if (this == &o) return *this;   // Gracefully handle self assignment
    // Put the normal assignment duties here...

    //we delete the PolicyPureVectors pointed to: 
    //this means that we should not be able 
    //to add indiv. policies without copying them!!! 
    size_t s = _m_indivPols_PolicyPureVector.size() ;
    if( s != o._m_indivPols_PolicyPureVector.size() )
    {
        ClearIndividualPolicies();
        _m_indivPols_PolicyPureVector.resize( 
                o._m_indivPols_PolicyPureVector.size(), 0);
    }
    
    for(Index i=0; i < _m_indivPols_PolicyPureVector.size() ; i++)
    {
        PolicyPureVector* o_pol = o._m_indivPols_PolicyPureVector[i];
        PolicyPureVector* this_pol =   this->_m_indivPols_PolicyPureVector[i];     
        if(this_pol == 0) // this->_m_indivPols_PolicyPureVector[i] == 0
        {
            //this pol is not a jppv yet, so we need to copy
            PolicyPureVector* copy =  new PolicyPureVector(*o_pol);
            this->_m_indivPols_PolicyPureVector[i] = copy;
        }
        else
        {
            //this_pol is an existing ppv: do assignment.
            (*this_pol) = (*o_pol);
        }
    }
    return *this;
}

void JPolComponent_VectorImplementation::RandomInitialization()
{
    for(Index agI = 0; agI < _m_indivPols_PolicyPureVector.size(); agI++)
        RandomInitialization(agI);
}


void JPolComponent_VectorImplementation::RandomInitialization(Index agI)
{
    PolicyPureVector* this_pol = this->_m_indivPols_PolicyPureVector[agI];
    if(this_pol == 0) 
    {
        throw E(" JPolComponent_VectorImplementation::RandomInitialization(agI) this_pol is 0!?");
    }
    this_pol->RandomInitialization();
}


void JPolComponent_VectorImplementation::ZeroInitialization()
{
    for(Index agI = 0; agI < _m_indivPols_PolicyPureVector.size(); agI++)
        ZeroInitialization(agI);
}


void JPolComponent_VectorImplementation::ZeroInitialization(Index agI)
{
    PolicyPureVector* this_pol = this->_m_indivPols_PolicyPureVector[agI];
    if(this_pol == 0) 
    {
        throw E(" JPolComponent_VectorImplementation::ZeroInitialization(agI) this_pol is 0!?");
    }
    this_pol->ZeroInitialization();
}




bool JPolComponent_VectorImplementation::Increment()
{
    bool carry_over = true;
    size_t nrAgents = _m_PTPDP->GetNrAgents();
    Index agentI = nrAgents - 1;
    while(carry_over /*&& agentI >= 0*/)
    {
//    _m_obsHistToActionIndices[i] = (_m_obsHistToActionIndices[i] + 1) % nrA;
    carry_over = ++(*_m_indivPols_PolicyPureVector[agentI]) ;
        //(_m_obsHistToActionIndices[i] == 0);
    if(agentI >=1)
            agentI--;
        else//agentI is 0; -- will get huge unsigned int leading to seg.fault
            //if we don't jump out
            break;
    }
    return(carry_over);
}

LIndex JPolComponent_VectorImplementation::GetIndex() const
{
    int nrAgents=_m_PTPDP->GetNrAgents();

    vector<LIndex> nrElems(2);
    nrElems[0]=1;
    nrElems[1]=1;

    vector<LIndex> indexVec(2);

    vector<LIndex> nrIndPol(nrAgents);
    vector<LIndex> individualIndices(nrAgents);
    for(int k=0;k<nrAgents;++k)
    {
        nrIndPol[k]=_m_PTPDP->GetNrPolicies(k, _m_idc,
                                            _m_indivPols_PolicyPureVector[k]->
                                            GetDepth());
        individualIndices[k]=_m_indivPols_PolicyPureVector[k]->GetIndex();
    }

    LIndex i=individualIndices[0];

    for(int k=1;k<nrAgents;++k)
    {
        
        nrElems[0]*=nrIndPol[k-1];
        nrElems[1]=nrIndPol[k-1];

        indexVec[0]=i;
        indexVec[1]=individualIndices[k];
        i=IndexTools::IndividualToJointIndices(indexVec,nrElems);
#if 0
        cout << SoftPrintVector(nrIndPol) << " "
             << SoftPrintVector(individualIndices)
             << " " << k << " "
             << SoftPrintVector(indexVec) << " "
             << SoftPrintVector(nrElems) << endl;
#endif
    }
    return(i);
}

void JPolComponent_VectorImplementation::SetIndex(LIndex i)
{
    int nrAgents=_m_PTPDP->GetNrAgents();

    vector<LIndex> nrElems(2);
    nrElems[0]=1;
    nrElems[1]=1;

    vector<LIndex> indexVec(2);

    //contains the number of individual policies per agent:
    vector<LIndex> nrIndPol(nrAgents);
    for(int k=0;k<nrAgents;++k)
    {
        nrIndPol[k]=_m_PTPDP->GetNrPolicies(k, _m_idc );
        nrElems[0]*=nrIndPol[k];
    }
    //nrElems[0] now containts the number of joint policies:
    //  1 * nrIndPol[1] * ... * nrIndPol[nrAgents-1] 

    // Matthijs... wtf is happening here?!?
    for(int k=nrAgents-1;k>0;--k)
    {
        nrElems[0]*=nrIndPol[k-1]; 
        nrElems[1]=nrIndPol[k-1];

        indexVec=IndexTools::JointToIndividualIndices(i,nrElems);
        _m_indivPols_PolicyPureVector[k]->SetIndex(indexVec[1]);
        i=indexVec[0]; //this seems to be a remainder?!
#if 0
        cout << SoftPrintVector(nrIndPol)
             << " " << k << " "
             << SoftPrintVector(indexVec) << " "
             << SoftPrintVector(nrElems) << endl;
#endif
    }
    _m_indivPols_PolicyPureVector[0]->SetIndex(indexVec[0]);
}

Index JPolComponent_VectorImplementation::GetJointActionIndex(Index jdI) const
{
    Index ohI, aThisAgent, ja_i;

    // it is possible to cache the joint->individual observ. history mapping
    // If this is done we want to use it by calling 
    //    JointToIndividualObservationHistoryIndicesRef
    // as it is faster.
    // Otherwise we have to use 
    //    JointToIndividualObservationHistoryIndices
    // to avoid a segfault.
    //
    // The mentioned cache is calculated, when generating joint observation
    // histories. This is controlled by the 
    // PlanningUnitMADPDiscreteParameters of the PlanningUnitMADPDiscrete.
    // ( _m_params.GetComputeJointObservationHistories() in particular )

    //if the "Interface_ProblemToPolicyDiscretePure"-implementing object this
    //policy caches joint -> indiv OH indices
    if(_m_PTPDP->AreCachedJointToIndivIndices(_m_idc ) )
    {
        const vector<Index> &individualDomainIndices = _m_PTPDP->
            JointToIndividualPolicyDomainIndicesRef(jdI, _m_idc );

        //vector<Index> individualActionIndices(individualDomainIndices.size());
        for( Index agentI=0; agentI < _m_PTPDP->GetNrAgents() ;  agentI++ )
        {
            ohI=individualDomainIndices[agentI];
            aThisAgent = _m_indivPols_PolicyPureVector[agentI]->
                GetActionIndex(ohI);
            _m_indivActionIndices[agentI]=aThisAgent;
        }
        ja_i = _m_PTPDP->IndividualToJointActionIndices(_m_indivActionIndices);
    } 
    else 
    { 
        vector<Index> individualDomainIndices = _m_PTPDP->
            JointToIndividualPolicyDomainIndices(jdI,_m_idc);

        size_t nrA = _m_PTPDP->GetNrAgents(); 
        if( individualDomainIndices.size() !=
            static_cast<vector<Index>::size_type>(nrA)   ) 
        {
            stringstream ss; 
            ss<<" JPolComponent_VectorImplementation::GetJointActionIndex Dimension "<<
                "mismatch, jdI has " << individualDomainIndices.size() <<
                "individual actions, but there are "<< nrA <<" agents!\n"; 
            throw E(ss); 
        }

        vector<Index> individualActionIndices(individualDomainIndices.size());
        for( Index agentI=0; agentI < individualDomainIndices.size();
             ++agentI )
        {
            ohI=individualDomainIndices[agentI];
            aThisAgent = _m_indivPols_PolicyPureVector[agentI]->GetActionIndex(ohI);
            individualActionIndices[agentI]=aThisAgent;
        }

        ja_i = _m_PTPDP->IndividualToJointActionIndices(
            individualActionIndices);

    }

    return(ja_i);
}

void JPolComponent_VectorImplementation::SetDepthForIndivPols(size_t d)
{
    vector<PolicyPureVector*>::iterator it = 
        _m_indivPols_PolicyPureVector.begin();
    vector<PolicyPureVector*>::iterator last = 
        _m_indivPols_PolicyPureVector.end();

    while(it != last)
    {
        (*it)->SetDepth(d);
        it++;
    }
}

string JPolComponent_VectorImplementation::SoftPrint(void) const
{
    if(_m_PTPDP == 0 )
        throw E("JPolComponent_VectorImplementation:SoftPrintBrief - Error!!! _m_PTPDP==0");
            
    stringstream ss;
    ss << "JPolComponent_VectorImplementation index " << GetIndex()
        //<< " depth " << GetDepth() 
        << endl;
    for(
            Index agentI = 0; 
            agentI <    static_cast< vector<PolicyPureVector*>::size_type> 
                            (_m_PTPDP->GetNrAgents());
            agentI++
        )
    {
        ss << "Policy for agent " << agentI << " (index "
           << _m_indivPols_PolicyPureVector.at(agentI)->GetIndex() << "):" << endl
           << _m_indivPols_PolicyPureVector.at(agentI)->SoftPrint();
    }
    return(ss.str());
} 

string JPolComponent_VectorImplementation::SoftPrintBrief(void) const
{
    if(_m_PTPDP == 0 )
        throw E("JPolComponent_VectorImplementation::SoftPrintBrief - Error!!! _m_PTPDP==0");
            
    stringstream ss;
    ss << GetIndex();

    return(ss.str());
}
        
