/**\file AlphaVectorPlanning.cpp
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
 * $Id: AlphaVectorPlanning.cpp 3633 2009-08-27 12:32:02Z mtjspaan $
 */

#include "AlphaVectorPlanning.h"
#include <float.h>
#include <fstream>
#include <sys/times.h>

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/io.hpp>

#include "AlphaVector.h"
#include "PlanningUnitDecPOMDPDiscrete.h"
#include "ValueFunctionPOMDPDiscrete.h"
#include "JointBeliefSparse.h"
#include "JointObservation.h"
#include "JointAction.h"
#include "State.h"
#include "argumentHandlers.h"
#include "QMDP.h"

#define DEBUG_AlphaVectorPlanning_BeliefSampling 0
#define DEBUG_AlphaVectorPlanning_BackProject 0
#define DEBUG_AlphaVectorPlanning_BackProjectFullPrintout 0
#define DEBUG_AlphaVectorPlanning_BackProjectFullSanityCheck 0
#define DEBUG_AlphaVectorPlanning_Prune 0
#define DEBUG_AlphaVectorPlanning_CrossSum 0
#define DEBUG_AlphaVectorPlanning_ValueFunctionToQ 0
#define DEBUG_AlphaVectorPlanning_ImportValueFunction 0

#define AlphaVectorPlanning_CheckForDuplicates 1
#define AlphaVectorPlanning_UseUBLASinBackProject 1
#define AlphaVectorPlanning_VerifyUBLASinBackProject 0
#define AlphaVectorPlanning_UseFastSparseBackup 1

using namespace std;

AlphaVectorPlanning::AlphaVectorPlanning(const 
                                         PlanningUnitDecPOMDPDiscrete& pu) :
    _m_pu(&pu),
    _m_TsForBackup(0),
    _m_OsForBackup(0),
    _m_TsOsForBackup(0)
{
    const TransitionModelMappingSparse *tms;
    const TransitionModelMapping *tm;
    const TransitionModelDiscrete *td=GetPU()->GetTransitionModelDiscretePtr();

    if((tms=dynamic_cast<const TransitionModelMappingSparse *>(td)))
        _m_useSparse=true;
    else if((tm=dynamic_cast<const TransitionModelMapping *>(td)))
        _m_useSparse=false;
    else 
        throw(E("AlphaVectorPlanning::Ctor() TransitionModelDiscretePtr not handled"));

    _m_initialized=false;
}

AlphaVectorPlanning::~AlphaVectorPlanning()
{
    DeInitialize();
}


void AlphaVectorPlanning::Initialize()
{
    if(_m_initialized)
        DeInitialize();

    const TransitionModelDiscrete *td=GetPU()->GetTransitionModelDiscretePtr();
    const ObservationModelDiscrete *od=GetPU()->GetObservationModelDiscretePtr();

    if(_m_useSparse)
    {
        const TransitionModelMappingSparse *tms;
        tms=dynamic_cast<const TransitionModelMappingSparse *>(td);
        const ObservationModelMappingSparse *oms;
        oms=dynamic_cast<const ObservationModelMappingSparse *>(od);

#if AlphaVectorPlanning_UseFastSparseBackup
        for(unsigned int a=0;a!=GetPU()->GetNrJointActions();++a)
        {
            _m_Ts.push_back(tms->GetMatrixPtr(a));
            _m_Os.push_back(oms->GetMatrixPtr(a));

            _m_TsForBackup.push_back(vector<SparseVector *>());
            for(unsigned int s=0;s!=GetPU()->GetNrStates();s++)
            {
                SparseVector *temp=new SparseVector(GetPU()->GetNrStates());
                for(unsigned int s1=0;s1!=GetPU()->GetNrStates();s1++)
                {
                    if((*_m_Ts[a])(s,s1)!=0)
                        (*temp)(s1)=(*_m_Ts[a])(s,s1);
                }
                _m_TsForBackup.at(a).push_back(temp);
            }

            _m_OsForBackup.push_back(vector<SparseVector *>());
            for(unsigned o=0;o!=GetPU()->GetNrJointObservations();++o)
            {
                SparseVector *temp=new SparseVector(GetPU()->GetNrStates());
                for(unsigned int s1=0;s1!=GetPU()->GetNrStates();s1++)
                {
                    if((*_m_Os[a])(s1,o)!=0)
                        (*temp)(s1)=(*_m_Os[a])(s1,o);
                }
                _m_OsForBackup.at(a).push_back(temp);
            }

            _m_TsOsForBackup.push_back(vector< vector<SparseVector *> >());
            for(unsigned int s=0;s!=GetPU()->GetNrStates();s++)
            {
                _m_TsOsForBackup.at(a).push_back(vector<SparseVector *>());
                for(unsigned o=0;o!=GetPU()->GetNrJointObservations();++o)
                {
                    SparseVector *temp=
                        new SparseVector(element_prod(*_m_TsForBackup[a][s],
                                                      *_m_OsForBackup[a][o]));
                    _m_TsOsForBackup.at(a).at(s).push_back(temp);
                }
            }
        }
#endif
    }
    else
    {
        const TransitionModelMapping *tm;
        tm=dynamic_cast<const TransitionModelMapping *>(td);
        const ObservationModelMapping *om;
        om=dynamic_cast<const ObservationModelMapping *>(od);

        for(unsigned int a=0;a!=GetPU()->GetNrJointActions();++a)
        {
            _m_T.push_back(tm->GetMatrixPtr(a));
            _m_O.push_back(om->GetMatrixPtr(a));
        }
    }
    _m_initialized=true;
}

void AlphaVectorPlanning::DeInitialize()
{
    _m_T.clear();
    _m_O.clear();

    _m_Ts.clear();
    _m_Os.clear();

    if(_m_TsForBackup.size())
    {
        for(unsigned i=0;i!=_m_TsForBackup.size();++i)
            for(unsigned j=0;j!=_m_TsForBackup[i].size();++j)
                delete _m_TsForBackup[i][j];
    }
    _m_TsForBackup.clear();

    if(_m_OsForBackup.size())
    {
        for(unsigned i=0;i!=_m_OsForBackup.size();++i)
            for(unsigned j=0;j!=_m_OsForBackup[i].size();++j)
                delete _m_OsForBackup[i][j];
    }
    _m_OsForBackup.clear();

    if(_m_TsOsForBackup.size())
    {
        for(unsigned i=0;i!=_m_TsOsForBackup.size();++i)
            for(unsigned j=0;j!=_m_TsOsForBackup[i].size();++j)
                for(unsigned k=0;k!=_m_TsOsForBackup[i][j].size();++k)
                    delete _m_TsOsForBackup[i][j][k];
    }
    _m_TsOsForBackup.clear();
}

GaoVectorSet
AlphaVectorPlanning::BackProject(const ValueFunctionPOMDPDiscrete &v) const
{
    // convert the valuefunction (a set of AlphaVectors) to a
    // VectorSet, basically removing the action information
    int nrInV=v.size();
    if(nrInV>0)
    {
        int nrS=(v[0].GetValues()).size();
        VectorSet v1(nrInV,nrS);
        for(int k=0;k!=nrInV;k++)
            for(int s=0;s!=nrS;s++)
                v1(k,s)=v[k].GetValue(s);

        if(_m_useSparse)
            return(BackProjectSparse(v1));
        else
            return(BackProjectFull(v1));
    }
    else
    {
        // v is empty, so return empty G
        GaoVectorSet G;
        return(G);
    }
}

/**
 * Implements equation (3.11) of PhD thesis Matthijs.
 */
GaoVectorSet AlphaVectorPlanning::BackProject(const VectorSet &v) const
{
    if(_m_useSparse)
        return(BackProjectSparse(v));
    else
        return(BackProjectFull(v));
}

/**
 * Implements equation (3.11) of PhD thesis Matthijs.
 */
GaoVectorSet AlphaVectorPlanning::BackProjectFull(const VectorSet &v) const
{
    unsigned int nrA=GetPU()->GetNrJointActions(),
        nrO=GetPU()->GetNrJointObservations(),
        nrS=GetPU()->GetNrStates(),
        nrInV=v.size1();

    if(nrInV==0)
        throw(E("AlphaVectorPlanning::BackProjectFull attempting to backproject empty value function"));

#if DEBUG_AlphaVectorPlanning_BackProject
    tms timeStruct;
    clock_t ticks_before, ticks_after;
    ticks_before = times(&timeStruct);
#endif

    StartTimer("BackProjectFull");
    
    GaoVectorSet G(boost::extents[nrA][nrO]);
    VectorSet v1(nrInV,nrS);
#if AlphaVectorPlanning_UseUBLASinBackProject
    VectorSet vv=v;
#endif
    double x;

#if AlphaVectorPlanning_CheckForDuplicates
    vector<int> duplicates=GetDuplicateIndices(v);
#else
    vector<int> duplicates(nrInV,-1);
#endif
    int dup;

    using namespace boost::numeric::ublas;

    for(unsigned int a=0;a!=nrA;a++)
        for(unsigned int o=0;o!=nrO;o++)
        {
#if AlphaVectorPlanning_UseUBLASinBackProject
            matrix_column<const ObservationModelMapping::Matrix> mO(*_m_O[a],o);
#endif
            for(unsigned int k=0;k!=nrInV;k++)
            {
                if(duplicates[k]==-1)
                {
#if AlphaVectorPlanning_UseUBLASinBackProject
                    const matrix_row<VectorSet> mV(vv,k);
#endif
                    for(unsigned int s=0;s!=nrS;s++)
                    {
#if AlphaVectorPlanning_UseUBLASinBackProject
                        matrix_row<const TransitionModelMapping::Matrix>
                            mT(*_m_T[a],s);
                        x=inner_prod(element_prod(mT,mO),mV);
#if AlphaVectorPlanning_VerifyUBLASinBackProject
                        double x1=0;
                        for(unsigned int s1=0;s1!=nrS;s1++)
                            x1+=(*_m_O[a])(s1,o)*(*_m_T[a])(s,s1)*v(k,s1);
                        if(abs(x-x1)>1e-14)
                        {
                            cerr << x << " " << x1 << " " << x-x1 << endl;
                            abort();
                        }
#endif
#else // AlphaVectorPlanning_UseUBLASinBackProject
                        x=0;
                        for(unsigned int s1=0;s1!=nrS;s1++)
                            x+=(*_m_O[a])(s1,o)*(*_m_T[a])(s,s1)*v(k,s1);
#endif
                        v1(k,s)=x;
                    }
                }
                else
                {
                    dup=duplicates[k];
                    for(unsigned int s=0;s!=nrS;s++)
                        v1(k,s)=v1(dup,s);
                }
            }
            G[a][o]=new VectorSet(v1);
        }

    StopTimer("BackProjectFull");

#if DEBUG_AlphaVectorPlanning_BackProjectFullPrintout
    cout << "BackProjectFull of:" << endl;
    for(unsigned int k=0;k!=nrInV;k++)
    {
        for(unsigned int s=0;s!=nrS;s++)
            cout << v(k,s) << " ";
        cout << endl;
    }

    VectorSet *VS;
    for(unsigned int a=0;a!=nrA;a++)
        for(unsigned int o=0;o!=nrO;o++)
        {
            cout << "Gao a " << a << " o " << o << endl;

            VS=G[a][o];
            for(unsigned int k=0;k!=VS->size1();k++)
            {
                for(unsigned int s=0;s!=VS->size2();s++)
                    cout << (*VS)(k,s) << " ";
                cout << endl;
            }
        }
#endif

#if DEBUG_AlphaVectorPlanning_BackProjectFullSanityCheck
    double maxInV=-DBL_MAX;
    for(unsigned int k=0;k!=nrInV;k++)
        for(unsigned int s=0;s!=nrS;s++)
            maxInV=max(maxInV,v(k,s));

    double maxInGao=-DBL_MAX;
    for(unsigned int a=0;a!=nrA;a++)
        for(unsigned int o=0;o!=nrO;o++)
            for(unsigned int k=0;k!=nrInV;k++)
                for(unsigned int s=0;s!=nrS;s++)
                    maxInGao=max(maxInGao,(*G[a][o])(k,s));

    if(maxInGao>maxInV)
    {
        cout << "Max value in V is " << maxInV << ", max in Gao is "
             << maxInGao << endl;
        abort();
    }
#endif

#if DEBUG_AlphaVectorPlanning_BackProject
    ticks_after = times(&timeStruct);
    cout << "AlphaVectorPlanning::BackProject done in " 
         << ticks_after - ticks_before << " clock ticks, "
         << static_cast<double>((ticks_after - ticks_before))
        / sysconf(_SC_CLK_TCK) 
         << "s" << endl;
    // test results on 22-12-2006
    // using dense Matrix is about 2 faster than calling the Get*Prob()
    // using sparse Matrix is almost 3 times slower then dense Matrix
#endif
    return(G);
}

/**
 * Implements equation (3.11) of PhD thesis Matthijs.
 */
GaoVectorSet AlphaVectorPlanning::BackProjectSparse(const VectorSet &v) const
{
    unsigned int nrA=GetPU()->GetNrJointActions(),
        nrO=GetPU()->GetNrJointObservations(),
        nrS=GetPU()->GetNrStates(),
        nrInV=v.size1();

    if(nrInV==0)
        throw(E("AlphaVectorPlanning::BackProjectSparse attempting to backproject empty value function"));

    StartTimer("BackProjectSparse");
    
    GaoVectorSet G(boost::extents[nrA][nrO]);
    VectorSet v1(nrInV,nrS);
    VectorSet vv=v;
    double x;

#if AlphaVectorPlanning_CheckForDuplicates
    vector<int> duplicates=GetDuplicateIndices(v);
#else
    vector<int> duplicates(nrInV,-1);
#endif
    int dup;

    using namespace boost::numeric::ublas;

    for(unsigned int a=0;a!=nrA;a++)
        for(unsigned int o=0;o!=nrO;o++)
        {
#if !AlphaVectorPlanning_UseFastSparseBackup
            matrix_column<const ObservationModelMappingSparse::SparseMatrix>
                mO(*_m_Os[a],o);
#endif
            for(unsigned int k=0;k!=nrInV;k++)
            {
                if(duplicates[k]==-1)
                {
                    const matrix_row<VectorSet> mV(vv,k);

                    for(unsigned int s=0;s!=nrS;s++)
                    {
#if AlphaVectorPlanning_UseFastSparseBackup
                        x=inner_prod(*_m_TsOsForBackup[a][s][o],mV);
#else
                        matrix_row<const TransitionModelMappingSparse::
                            SparseMatrix> mT(*_m_Ts[a],s);
                        x=inner_prod(element_prod(mT,mO),mV);
#endif
                        v1(k,s)=x;
                    }
                }
                else
                {
                    dup=duplicates[k];
                    for(unsigned int s=0;s!=nrS;s++)
                        v1(k,s)=v1(dup,s);
                }
            }
            G[a][o]=new VectorSet(v1);
        }

    StopTimer("BackProjectSparse");

    return(G);
}

BeliefSet AlphaVectorPlanning::SampleBeliefs(
    ArgumentHandlers::Arguments args) const
{
    StartTimer("SampleBeliefs");
    
    int h=_m_pu->GetHorizon(),
        nrS=_m_pu->GetNrStates(),
        nrA=_m_pu->GetNrJointActions(),
        i,d=0,s;
    Index a;
    Index o;
    Index s0=0,s1;
    JointBeliefInterface *b0p, *b1p;
    b0p = _m_pu->GetNewJointBeliefInterface(nrS);
    b1p = _m_pu->GetNewJointBeliefInterface(nrS);
    JointBeliefInterface& b0 = *b0p;
    JointBeliefInterface& b1 = *b1p;
    BeliefSet S(args.nrBeliefs);
    bool foundEqualBelief,equal,addBelief;
    int nrEqualFound=0;

    // we don't want to artificially reset the problem
    if(args.resetAfter==0)
    {
        if(h==static_cast<int>(MAXHORIZON))
            cout << "Warning: sampling beliefs for an infinite horizon "
                 << "without reset." << endl;
        args.resetAfter=h;
    }

    QMDP *qmdp=0;
    if(args.useQMDPforSamplingBeliefs)
    {
        qmdp=new QMDP(*GetPU());
        qmdp->Compute();
    }

    i=0;
    // make sure we don't try to keep on sampling beliefs if there are
    // not enough unique beliefs (<args.nrBeliefs)
    while(i<args.nrBeliefs && nrEqualFound<(args.nrBeliefs*2))
    {
        // reset the problem if either we exceeded the horizon, or the
        // user-supplied parameter (used in the infinite-horizon case)
        if(d>h || d>args.resetAfter)
            d=0;

        if(d==0)
        {
            s1=_m_pu->GetReferred()->SampleInitialState();
            b1.Set(* _m_pu->GetProblem()->GetISD());
        }
        else
        {
            if(args.useQMDPforSamplingBeliefs &&
               (rand() / (RAND_MAX + 1.0)) > args.QMDPexploreProb)
            {
                double valMax=-DBL_MAX;
                a=INT_MAX;
                for(int aQMDP=0;aQMDP!=nrA;++aQMDP)
                {
                    double qQMDP=qmdp->GetQ(b0,aQMDP);
                    if(qQMDP>valMax)
                    {
                        valMax=qQMDP;
                        a=aQMDP;
                    }
                }
            }
            else
            {
                // sample an action uniformly at random
                a=static_cast<int>(nrA*(rand() / (RAND_MAX + 1.0)));
            }

            s1=_m_pu->GetReferred()->SampleSuccessorState(s0,a);
            o=_m_pu->GetReferred()->SampleJointObservation(a,s1);

            b1=b0;
            b1.Update(*_m_pu->GetReferred(),a,o);
        }

        if(args.uniqueBeliefs)
        {
            foundEqualBelief=false;
            // loop over all beliefs already in S
            for(int j=0;j!=i;j++)
            {
                equal=true;
                for(s=0;s!=nrS;s++)
                {
                    // if one number differs we can move on to the next j
                    if(S[j]->Get(s)!=b1.Get(s))
                    {
                        equal=false;
                        break;
                    }
                }
                // if we found an equal belief we can stop
                if(equal)
                {
                    foundEqualBelief=true;
                    break;
                }
            }
            if(foundEqualBelief)
            {
                nrEqualFound++;
                addBelief=false;
            }
            else
                addBelief=true;
        }
        else
            addBelief=true;
        
        if(addBelief)
        {
            if(!b1.SanityCheck())
                throw(E("AlphaVectorPlanning::BeliefSampling belief fails sanity check"));

            S[i]=new JointBeliefSparse(b1); // HMMM, always sparse?
            i++;

            if(DEBUG_AlphaVectorPlanning_BeliefSampling)
            {
                cout << "AlphaVectorPlanning::SampleBeliefs sampled belief nr "
                     << i << "/" << args.nrBeliefs << " (nrEqualFound " 
                     << nrEqualFound << ")" << endl;
            }
        }
        
        d++;
        s0=s1;
        b0=b1;
    }

    delete b0p;
    delete b1p;
    delete qmdp;

    StopTimer("SampleBeliefs");

    // we did not manage to sample args.nrBeliefs unique beliefs
    if(i<args.nrBeliefs)
    {
        cout << "AlphaVectorPlanning::SampleBeliefs: warning, only " 
             << "managed to sample " << i << " unique beliefs instead of " 
             << args.nrBeliefs << endl;
        BeliefSet S1(i);
        for(int j=0;j!=i;j++)
            S1[j]=S[j];
        return(S1);
    }
    else
        return(S);
}

VectorSet AlphaVectorPlanning::CrossSum(const VectorSet &A,
                                        const VectorSet &B) const
{
    int nrInA=A.size1(),
        nrInB=B.size1(),
        nrS=A.size1();

#if DEBUG_AlphaVectorPlanning_CrossSum
    cout << "AlphaVectorPlanning::CrossSum of " << nrInA 
         << " times " << nrInB << endl;
#endif

    VectorSet C(nrInA*nrInB,nrS);
    
    int k=-1;
    for(int i=0;i!=nrInA;i++)
        for(int j=0;j!=nrInB;j++)
        {
            k++;
            for(int s=0;s!=nrS;s++)
                C(k,s)=A(i,s)+B(j,s);
        }

    return(C);
}

void AlphaVectorPlanning::MonahanCrossSum(const GaoVectorSet &G,
                                          ValueFunctionPOMDPDiscrete &V,
                                          Index a,
                                          bool doIncPrune) const
{
    int nrS=GetPU()->GetNrStates(),
        nrO=GetPU()->GetNrJointObservations();
    AlphaVector alpha(nrS);

#if DEBUG_AlphaVectorPlanning_CrossSum    
    cout << "AlphaVectorPlanning::MonahanCrossSum for action " << a << endl;
#endif

    // Do the cross-sums, creates G_a of (3.25)
    VectorSet Ga=*G[a][0];
    for(GaoVectorSetIndex o=1;o!=nrO;o++)
    {
        if(doIncPrune)
        {
            VectorSet Ga2=CrossSum(Ga,*G[a][o]);
            VectorSet Ga1=Prune(Ga2);
            Ga.resize(Ga1.size1(),Ga1.size2());
            Ga=Ga1;
        }
        else
        {
            VectorSet Ga1=CrossSum(Ga,*G[a][o]);
            Ga.resize(Ga1.size1(),Ga1.size2());
            Ga=Ga1;
        }
    }
        
    // Add the resulting vectors to V (HV_n of (3.25))
    for(unsigned int k=0;k!=Ga.size1();k++)
    {
        alpha.SetAction(a);
        for(int s=0;s!=nrS;s++)
            alpha.SetValue(Ga(k,s),s);
        V.push_back(alpha);
    }
}

GaoVectorSet 
AlphaVectorPlanning::
BackProjectMonahan(const QFunctionsDiscrete &Qs) const
{
    return(BackProjectMonahan(QFunctionsToValueFunction(Qs)));
}


GaoVectorSet 
AlphaVectorPlanning::BackProjectMonahan(const 
                                        ValueFunctionPOMDPDiscrete &V) const
{
    int nrS=GetPU()->GetNrStates(),
        nrA=GetPU()->GetNrJointActions(),
        nrO=GetPU()->GetNrJointObservations(),
        nrInV=V.size();
    double gamma=GetPU()->GetDiscount();

    GaoVectorSet Gao=BackProject(V);

    GaoVectorSet G(boost::extents[nrA][nrO]);
    VectorSet *vGao;
    VectorSet v1(nrInV,nrS);

    // Create G^o_a vectors of (3.25) of PhD Matthijs
    for(GaoVectorSetIndex a=0;a!=nrA;a++)
        for(GaoVectorSetIndex o=0;o!=nrO;o++)
        {
            vGao=Gao[a][o];
            for(int k=0;k!=nrInV;k++)
                for(int s=0;s!=nrS;s++)
                    v1(k,s)=(GetPU()->GetReward(s,a))/nrO+gamma*(*vGao)(k,s);
            G[a][o]=new VectorSet(v1);
        }

    return(G);
}

ValueFunctionPOMDPDiscrete
AlphaVectorPlanning::Prune(const ValueFunctionPOMDPDiscrete &V) const
{
    ValueFunctionPOMDPDiscrete V1;
    int nrS=GetPU()->GetNrStates();
    bool dominated,valuesDominated;
    vector<bool> dominatedVectors(V.size(),false);
    int i;

#if DEBUG_AlphaVectorPlanning_Prune
    cout << "AlphaVectorPlanning::Prune " << V.size() << " vectors" << endl;
#endif

    vector<AlphaVector>::const_iterator it=V.begin();
    vector<AlphaVector>::const_iterator it1;
    i=0;
    while(it!=V.end())
    {
        it1=V.begin();
        dominated=false;
        // check whether "it" is dominated by any it1
        while(!dominatedVectors[i] && it1!=V.end() && !dominated)
        {
            valuesDominated=true;
            for(int s=0;s!=nrS;s++)
                if(it->GetValue(s) > it1->GetValue(s))
                    valuesDominated=false;

            if(valuesDominated && it1->GetAction()==it->GetAction() && it1!=it)
                dominated=true;
            else
                dominated=false;

            it1++;
        }
        if(!dominated)
        {
            V1.push_back(*it);
#if DEBUG_AlphaVectorPlanning_Prune
            cout << "AlphaVectorPlanning::Prune added vector " << i << endl;
#endif
        }
        else
            dominatedVectors[i]=true;

        it++;
        i++;
    }

#if DEBUG_AlphaVectorPlanning_Prune
    cout << "AlphaVectorPlanning::Prune reduced " << V.size() << " to " 
         << V1.size() << endl;
#endif

    return(V1);
}

VectorSet
AlphaVectorPlanning::Prune(const VectorSet &V) const
{
    int nrInV=V.size1(),nrS=V.size2();
    bool dominated,valuesDominated;
    vector<bool> dominatedVectors(nrInV,false);
    int it,it1;
    vector<int> vectorsToKeep;

#if DEBUG_AlphaVectorPlanning_Prune
    cout << "AlphaVectorPlanning::Prune " << nrInV << " vectors" << endl;
#endif

    for(it=0;it!=nrInV;it++)
    {
        it1=0;
        dominated=false;
        // check whether "it" is dominated by any it1
        while(!dominatedVectors[it] && it1!=nrInV && !dominated)
        {
            valuesDominated=true;
            for(int s=0;s!=nrS;s++)
                if(V(it,s) > V(it1,s))
                    valuesDominated=false;

            if(valuesDominated && it1!=it)
                dominated=true;
            else
                dominated=false;

            it1++;
        }
        if(!dominated)
        {
            vectorsToKeep.push_back(it);
#if DEBUG_AlphaVectorPlanning_Prune
            cout << "AlphaVectorPlanning::Prune added vector " << it << endl;
#endif
        }
        else
            dominatedVectors[it]=true;

    }

    int newNrInV=vectorsToKeep.size();
    VectorSet V1(newNrInV,nrS);
    for(int i=0;i!=newNrInV;i++)
        for(int s=0;s!=nrS;s++)
            V1(i,s)=V(vectorsToKeep[i],s);

#if DEBUG_AlphaVectorPlanning_Prune
    cout << "AlphaVectorPlanning::Prune reduced " << nrInV << " to " 
         << newNrInV << endl;
#endif

    return(V1);
}


void AlphaVectorPlanning::ExportValueFunction(const string & filename,
                                              const QFunctionsDiscrete &Q)
{
    ExportValueFunction(filename,QFunctionsToValueFunction(Q));
}

void 
AlphaVectorPlanning::
ExportValueFunction(const string & filename,
                    const QFunctionsDiscreteNonStationary &Q)
{
    for(Index t=0;t!=Q.size();++t)
    {
        stringstream filenameT;
        filenameT << filename << "_t" << t;
        ExportValueFunction(filenameT.str(),Q[t]);
    }
}

QFunctionsDiscreteNonStationary
AlphaVectorPlanning::ImportValueFunction(const string & filename, size_t nr,
                                         size_t nrA, size_t nrS)
{
    QFunctionsDiscreteNonStationary Q;
    for(Index t=0;t!=nr;++t)
    {
        stringstream filenameT;
        filenameT << filename << "_t" << t;
        Q.push_back(ValueFunctionToQ(
                        ImportValueFunction(filenameT.str()),nrA,nrS));
    }
    return(Q);
}

/** Export is in a simple text format used by Tony Cassandra for
 * .alpha files. The format is simply:
 *
 * <action>
 * <list of vector components>
 * 
 * <action>
 * <list of vector components>
 */
void
AlphaVectorPlanning::ExportValueFunction(const string & filename,
                                         const ValueFunctionPOMDPDiscrete &V)
{
    vector<double> values;

    ofstream fp(filename.c_str());
    if(!fp)
    {
        cerr << "AlphaVectorPlanning::ExportValueFunction: failed to "
             << "open file " << filename << endl;            
    }

    for(unsigned int i=0;i!=V.size();i++)
    {
        values=V[i].GetValues();
        int nrS=values.size();

        fp << V[i].GetAction() << " " << V[i].GetBetaI() << endl;
        for(int s=0;s!=nrS;s++)
        {
            fp << values[s];
            if(s<(nrS-1))
                fp << " ";
        }
        fp << endl << endl;
    }
}

/** Function lacks error checking. */
ValueFunctionPOMDPDiscrete 
AlphaVectorPlanning::ImportValueFunction(const string & filename)
{
    ValueFunctionPOMDPDiscrete V;
    const int bufsize=65536;
    char buffer[bufsize];

    int lineState=0; /* lineState=0 -> read action
                      * lineState=1 -> read values
                      * lineState=2 -> empty line, skip */
    int nrStates=-1;
    bool first=true;
    Index action=0;
    int betaI=-1;
    double value;
    vector<double> values;
    vector<int> actionBetaI;
    long long int actionOrBetaI;

    ifstream fp(filename.c_str());
    if(!fp)
    {
        cerr << "AlphaVectorPlanning::ImportValueFunction: failed to "
             << "open file " << filename << endl;            
    }

    while(!fp.getline(buffer,bufsize).eof())
    {
        switch(lineState)
        {
        case 0:
            // read action
//            action=strtol(buffer,NULL,10);
            actionBetaI.clear();
            {
                istringstream is(buffer);
                while(is >> actionOrBetaI)
                    actionBetaI.push_back(actionOrBetaI);
            }

            switch(actionBetaI.size())
            {
            case 1:
                action=actionBetaI[0];
                betaI=-1;
                break;
            case 2:
                action=actionBetaI[0];
                betaI=actionBetaI[1];
                break;
            default:
                throw(E("AlphaVectorPlanning::ImportValueFunction parse error"));
            }

            lineState++;
            break;
        case 1:
            // read values
            values.clear();

            {
                istringstream is(buffer);
                while(is >> value)
                    values.push_back(value);
            }
            
            if(first)
            {
                nrStates=values.size();
                first=false;
            }
            
            // create new alpha vector and store it
            {
                AlphaVector alpha(nrStates);
                alpha.SetAction(action);
                alpha.SetValues(values);
                alpha.SetBetaI(betaI);

#if DEBUG_AlphaVectorPlanning_ImportValueFunction
                cout << "AlphaVectorPlanning::ImportValueFunction "
                     << "added vector " << V.size() << " for action " 
                     << action << " betaI " << betaI << endl;
#endif

                V.push_back(alpha);
            }

            lineState++;
            break;
        case 2:
            // do nothing, line is empty
            lineState=0;
            break;
        }
    }

    return(V);
}

ValueFunctionPOMDPDiscrete
AlphaVectorPlanning::
GetImmediateRewardValueFunction() const
{
    return(GetImmediateRewardValueFunction(GetPU()));
}

ValueFunctionPOMDPDiscrete
AlphaVectorPlanning::
GetImmediateRewardValueFunction(const PlanningUnitDecPOMDPDiscrete *pu)
{
    size_t nrA=pu->GetNrJointActions(),
        nrS=pu->GetNrStates();
    ValueFunctionPOMDPDiscrete V0;
    AlphaVector alpha(nrS);

    for(Index a=0;a<nrA;a++)
    {
        alpha.SetAction(a);
        for(Index s=0;s<nrS;s++)
            alpha.SetValue(pu->GetReward(s,a),s);
        V0.push_back(alpha);
    }

    return(V0);
}

ValueFunctionPOMDPDiscrete
AlphaVectorPlanning::QFunctionsToValueFunction(const 
                                               QFunctionsDiscrete &Q)
{
    ValueFunctionPOMDPDiscrete V;
    for(QFDcit i=Q.begin();i!=Q.end();++i)
        for(VFPDcit j=i->begin();j!=i->end();++j)
            V.push_back(*j);
    
    return(V);
}

void AlphaVectorPlanning::ExportPOMDPFile(const string & filename) const
{
    ExportPOMDPFile(filename,GetPU());
}

/// Export is in Tony Cassandra's POMDP file format.
void AlphaVectorPlanning::ExportPOMDPFile(const string & filename,
                                          const PlanningUnitDecPOMDPDiscrete 
                                          *pu)
{
    int nrA=pu->GetNrJointActions(),
        nrO=pu->GetNrJointObservations(),
        nrS=pu->GetNrStates();
    ofstream fp(filename.c_str());
    if(!fp)
    {
        cerr << "AlphaVectorPOMDP::ExportPOMDPFile: failed to open file "
             << filename << endl;            
    }

    fp << "discount: " << pu->GetDiscount() << endl;
    switch(pu->GetReferred()->GetRewardType())
    {
    case REWARD:
        fp << "values: reward" << endl;
        break;
    case COST:
        fp << "values: cost" << endl;
    }

    fp << "states:";
    for(int s=0;s<nrS;s++)
        fp << " "  << pu->GetReferred()->GetState(s)->SoftPrintBrief();
    fp << endl;

    fp << "actions:";
    for(int a=0;a<nrA;a++)
        fp << " "  << pu->GetReferred()->GetJointAction(a)->SoftPrintBrief();
    fp << endl;

    fp << "observations:";
    for(int o=0;o<nrO;o++)
        fp << " "  << pu->GetReferred()->GetJointObservation(o)->
            SoftPrintBrief();
    fp << endl;


    JointBeliefInterface*  isd = pu->GetNewJointBeliefFromISD();
    fp << "start: ";
    for(int s0=0;s0<nrS;s0++)
    {
        double bs = isd->Get(s0);
        fp <<  bs << " ";
    }
    fp << endl;

    delete isd;

    double p;
    for(int a=0;a<nrA;a++)
        for(int s0=0;s0<nrS;s0++)
            for(int s1=0;s1<nrS;s1++)
            {
                p=pu->GetTransitionProbability(s0,a,s1);
                if(p!=0)
                    fp << "T: " << a << " : " << s0 << " : " << s1 << " " 
                       << p << endl;
            }

    for(int a=0;a<nrA;a++)
        for(int o=0;o<nrO;o++)
            for(int s1=0;s1<nrS;s1++)
            {
                p=pu->GetObservationProbability(a,s1,o);
                if(p!=0)
                    fp << "O: " << a << " : " << s1 << " : " << o << " " 
                       << p << endl;
            }

    for(int a=0;a<nrA;a++)
        for(int s0=0;s0<nrS;s0++)
        {
            p=pu->GetReward(s0,a);
            if(p!=0)
                fp << "R: " << a << " : " << s0 << " : * : * "
                   << p << endl;
        }

}

void AlphaVectorPlanning::ExportBeliefSet(const BeliefSet &B,
                                          const string &filename)
{
    ofstream fp(filename.c_str());
    if(!fp)
    {
        cerr << "AlphaVectorPlanning::ExportBeliefSet: failed to open file "
             << filename << endl;            
    }

    int nrB=B.size();
    for(int b=0;b!=nrB;b++)
    {
        for(unsigned int s=0;s!=B[b]->Size();s++)
            fp << B[b]->Get(s) << " ";
        fp << endl;
    }
}

QFunctionsDiscrete
AlphaVectorPlanning::ValueFunctionToQ(const ValueFunctionPOMDPDiscrete &V) const
{
    return(ValueFunctionToQ(V,GetPU()->GetNrJointActions(),
                            GetPU()->GetNrStates()));
}

QFunctionsDiscrete
AlphaVectorPlanning::ValueFunctionToQ(const ValueFunctionPOMDPDiscrete &V,
                                      size_t nrA, size_t nrS)
{
    QFunctionsDiscrete Qs;

    for(Index a=0;a!=nrA;a++)
    {
        ValueFunctionPOMDPDiscrete Q;
        for(Index i=0;i!=V.size();i++)
        {
            if(V[i].GetAction()==a)
                Q.push_back(V[i]);
        }
        // if the action has no vector, it's dominated everywhere, so
        // must never be chosen
        if(Q.size()==0)
        {
            AlphaVector dominatedVector(nrS,-DBL_MAX);
            dominatedVector.SetAction(a);
            Q.push_back(dominatedVector);
#if DEBUG_AlphaVectorPlanning_ValueFunctionToQ
            cout << "AlphaVectorPlanning::GetQFunctionsFromV: action " << a 
                 << " is dominated" << endl;
#endif
        }
        else
        {
#if DEBUG_AlphaVectorPlanning_ValueFunctionToQ
            cout << "AlphaVectorPlanning::GetQFunctionsFromV: action " << a 
                 << " has " << Q.size() 
                 << " vector(s) " << endl;
#endif
        }
        Qs.push_back(Q);
    }
    
    return(Qs);
}

/** Returns a vector<int> which for each vector k in V specifies
 * whether it is unique, in which case vector<int>[k] is set to -1, or
 * whether it is a duplicate of another vector l in V, in which case
 * vector<int>[k] is set to the index of l, where 0 <= l <
 * V.size()). */
vector<int> AlphaVectorPlanning::GetDuplicateIndices(const VectorSet &V)
{
    int nrInV=V.size1(), nrS=V.size2();
    bool equal;

    vector<int> duplicates(nrInV,-1);

    for(int i=1;i!=nrInV;++i) // start at 1, first is never a duplicate
    {
        for(int j=0;j!=i;++j) // loop over all previous vectors
        {
            equal=true;
            for(int s=0;s!=nrS;++s)
            {
                if(abs(V(i,s)-V(j,s))>PROB_PRECISION)
                {
                    equal=false;
                    break; // if 1 number differs, they are not equal
                }
            }
            if(equal)
            {
                duplicates[i]=j;
                break; // we need to find only the first duplicate
            }
        }
    }

#if 0 // reduce verbosity
    PrintVectorCout(duplicates); cout << endl;
#endif
    return(duplicates);
}

bool AlphaVectorPlanning::
VectorIsInValueFunction(const AlphaVector &alpha,
                        const ValueFunctionPOMDPDiscrete &V)
{
    bool equal;

    for(VFPDcit it=V.begin(); it!=V.end(); ++it)
    {
        equal=true;
        // if the actions differ we don't need to check the values
        if(alpha.GetAction()!=it->GetAction())
        {
            equal=false;
            continue;
        }

        for(unsigned i=0; i!=alpha.GetNrValues(); ++i)
            if(abs(alpha.GetValue(i)-it->GetValue(i))>PROB_PRECISION)
            {
                equal=false;
                continue;
            }

        if(equal)
            return(true);
    }

    // if we get here we did not find a match, so alpha is not in V
    return(false);
}
