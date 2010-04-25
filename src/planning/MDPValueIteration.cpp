/**\file MDPValueIteration.cpp
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
 * $Id: MDPValueIteration.cpp 3611 2009-08-25 15:02:24Z mtjspaan $
 */

#include "MDPValueIteration.h"
#include <fstream>
#include <boost/numeric/ublas/matrix_sparse.hpp>

using namespace std;

//Default constructor
MDPValueIteration::MDPValueIteration(const PlanningUnitDecPOMDPDiscrete& pu) :
    MDPSolver(pu)
{
    _m_initialized = false;
}

//Destructor
MDPValueIteration::~MDPValueIteration()
{
}

void MDPValueIteration::Initialize()
{
    StartTimer("Initialize");

    size_t horizon = GetPU()->GetHorizon();
    size_t nrS = GetPU()->GetNrStates();
    size_t nrJA =  GetPU()->GetNrJointActions();

    size_t nrQfunctions;
    if(horizon==MAXHORIZON)
    {
        _m_finiteHorizon=false;
        nrQfunctions=1;
    }
    else
    {
        _m_finiteHorizon=true;
        nrQfunctions=horizon;
    }

    QTable tempTable(nrS,nrJA);
    for(unsigned int s=0;s!=nrS;++s)
        for(unsigned int ja=0;ja!=nrJA;++ja)
            tempTable(s,ja)=0;

    for(Index t=0; t < nrQfunctions; t++)
        _m_QValues.push_back(tempTable);

    _m_initialized = true;

    StopTimer("Initialize");
}

QTables MDPValueIteration::GetQTables() const
{
    return(_m_QValues);
}

QTable MDPValueIteration::GetQTable(Index time_step) const
{
    return(_m_QValues.at(time_step));
}

void MDPValueIteration::SetQTables(const QTables &Qs)
{
    _m_QValues=Qs;
}

void MDPValueIteration::SetQTable(const QTable &Q, Index time_step)
{
    _m_QValues[time_step]=Q;
}

/** Duplication of code from the templatized version, but well... */
void MDPValueIteration::PlanSlow()
{
    if(!_m_initialized)
        Initialize();

    StartTimer("Plan");

    size_t horizon = GetPU()->GetHorizon();
    size_t nrS = GetPU()->GetNrStates();
    size_t nrJA =  GetPU()->GetNrJointActions();

    double R_i,R_f,maxQsuc;

    // cache immediate reward for speed
    QTable immReward(nrS,nrJA);
    for(Index sI = 0; sI < nrS; sI++)
        for(Index jaI = 0; jaI < nrJA; jaI++)
            immReward(sI,jaI)=GetPU()->GetReward(sI, jaI);

   
    if(_m_finiteHorizon)
    {
        for(size_t t = horizon - 1; true; t--)
        {
            for(Index sI = 0; sI < nrS; sI++)
            {
                for(Index jaI = 0; jaI < nrJA; jaI++)
                {
                    //calc. expected immediate reward
                    R_i = immReward(sI,jaI);
                    R_f = 0.0;
                    if(t < horizon - 1)
                    {
                        //calc. expected future reward
                        for(Index ssucI = 0; ssucI < nrS; ssucI++)
                        {
                            //find the best action at ssucI
                            maxQsuc = -DBL_MAX;
                            for(Index jasucI = 0; jasucI < nrJA; jasucI++)
                                maxQsuc = max( _m_QValues[t+1](ssucI,jasucI),
                                               maxQsuc);
                            
                            R_f += GetPU()->GetTransitionProbability(sI, jaI,
                                                                     ssucI)
                                * maxQsuc;
                        }//done calc. expected future reward
                    }
                    _m_QValues[t](sI,jaI) = R_i + R_f;
                }//end for jaI
            }//end for sI
            if(t == 0) //escape from (loop t is unsigned!)
                break;
        }
    }
    else // infinite horizon problem
    {
        double maxDelta=DBL_MAX;
        double gamma=GetPU()->GetDiscount();
        QTable oldQtable;

        // in infinite-horizon case, it is typically worth to cache
        // the transition model
        typedef boost::numeric::ublas::compressed_matrix<double> CMatrix;
        vector<CMatrix*> T;
        CMatrix *Ta;
        double p;
        for(unsigned int a=0;a!=nrJA;++a)
        {
#if DEBUG_MDPValueIteration
            PrintTimersSummary();
#endif
            StartTimer("CacheTransitionModel");
            Ta=new CMatrix(nrS,nrS);

            for(unsigned int s=0;s!=nrS;++s)
                for(unsigned int s1=0;s1!=nrS;++s1)
                {
                    p=GetPU()->GetTransitionProbability(s,a,s1);
                    if(p>0)
                        (*Ta)(s,s1)=p;
                }

            T.push_back(Ta);
            StopTimer("CacheTransitionModel");
        }

        Index sI,ssucI;
        while(maxDelta>1e-4)
        {
            StartTimer("Iteration");
            maxDelta=0;
            oldQtable=_m_QValues[0];
            for(Index jaI = 0; jaI < nrJA; jaI++)
            {
                for(CMatrix::const_iterator1 ri=T[jaI]->begin1();
                    ri!=T[jaI]->end1(); ++ri)
                {
                    sI=ri.index1();

                    //calc. expected immediate reward
                    R_i = immReward(sI,jaI);
                    R_f = 0.0;
                    //calc. expected future reward
                    
                    for (CMatrix::const_iterator2 ci = ri.begin();
                         ci != ri.end(); ++ci)
                    {
                        ssucI=ci.index2();

                        //find the best action at ssucI
                        maxQsuc = -DBL_MAX;
                        for(Index jasucI = 0; jasucI < nrJA; jasucI++)
                            maxQsuc = max( oldQtable(ssucI,jasucI),
                                           maxQsuc);
                            
                        R_f += *ci * maxQsuc;
                    }//done calc. expected future reward

                    _m_QValues[0](sI,jaI) = R_i + gamma*R_f;
                    maxDelta=max(maxDelta,abs(oldQtable(sI,jaI)-
                                              _m_QValues[0](sI,jaI)));
                }//end for jaI
            }//end for sI

            StopTimer("Iteration");

#if DEBUG_MDPValueIteration
            cout << "delta " << maxDelta << endl;
            PrintTimersSummary();
#endif
        }

        for(unsigned int a=0;a!=nrJA;++a)
            delete T[a];
    }
    StopTimer("Plan");

#if DEBUG_MDPValueIteration
    PrintTimersSummary();
#endif
}
