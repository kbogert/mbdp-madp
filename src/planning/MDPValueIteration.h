/**\file MDPValueIteration.h
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
 * $Id: MDPValueIteration.h 3611 2009-08-25 15:02:24Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _MDPVALUEITERATION_H_
#define _MDPVALUEITERATION_H_ 1

/* the include directives */
#include <iostream>
#include <float.h>
#include "Globals.h"

#include "PlanningUnitDecPOMDPDiscrete.h"
#include "MDPSolver.h"
#include "TimedAlgorithm.h"
#include "TransitionModelMapping.h"
#include "TransitionModelMappingSparse.h"

#define DEBUG_MDPValueIteration 0

/**\brief MDPValueIteration implements value iteration for MDPs.
  */
class MDPValueIteration : public MDPSolver,
    public TimedAlgorithm
{
private:    
    
    /**_m_QValues represents the non-stationary MDP Q function. 
     * I.e. _m_QValues[t][sI][jaI] gives the expected reward at time-step
     * t (time-to-go = horizon - t). */
    QTables _m_QValues;

    /**Is the MDPValueIteration object initialized?.*/ 
    bool _m_initialized; 
    
    /// Are we solving a finite-horizon problem?
    bool _m_finiteHorizon;

    void Initialize();

    /**Vector<const M*> T is the vector of matrices specifying the transition
       model (one matrix for each joint action). */
    template <class M>
    void Plan(std::vector<const M*> T)
    {

        size_t horizon = GetPU()->GetHorizon();
        size_t nrS = GetPU()->GetNrStates();
        size_t nrJA =  GetPU()->GetNrJointActions();

        Index sI,ssucI;
        double gamma=GetPU()->GetDiscount();
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
                StartTimer("Iteration");
                for(Index jaI = 0; jaI < nrJA; jaI++)
                {
                    for(typename M::const_iterator1 ri=T[jaI]->begin1();
                        ri!=T[jaI]->end1(); ++ri)
                    {
                        sI=ri.index1();
                        
                        //calc. expected immediate reward
                        R_i = immReward(sI,jaI);
                        R_f = 0.0;
                        if(t < horizon - 1)
                        {
                            //calc. expected future reward
                            for (typename M::const_iterator2 ci = ri.begin();
                                 ci != ri.end(); ++ci)
                            {
                                ssucI=ci.index2();
                                //find the best action at ssucI
                                maxQsuc = -DBL_MAX;
                                for(Index jasucI = 0; jasucI < nrJA; jasucI++)
                                    maxQsuc = max( _m_QValues[t+1](ssucI,jasucI),
                                                   maxQsuc);
                            
                                R_f += *ci * maxQsuc;
                            }//done calc. expected future reward
                        }
                        _m_QValues[t](sI,jaI) = R_i + gamma*R_f;
                    }//end for jaI
                }//end for sI
                StopTimer("Iteration");
                if(t == 0) //escape from (loop t is unsigned!)
                    break;
            }
        }
        else // infinite horizon problem
        {
            double maxDelta=DBL_MAX;
            QTable oldQtable;

            while(maxDelta>1e-4)
            {
                StartTimer("Iteration");
                maxDelta=0;
                oldQtable=_m_QValues[0];
                for(Index jaI = 0; jaI < nrJA; jaI++)
                {
                    for(typename M::const_iterator1 ri=T[jaI]->begin1();
                        ri!=T[jaI]->end1(); ++ri)
                    {
                        sI=ri.index1();

                        //calc. expected immediate reward
                        R_i = immReward(sI,jaI);
                        R_f = 0.0;
                        //calc. expected future reward
                    
                        for (typename M::const_iterator2 ci = ri.begin();
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
                        maxDelta=max(maxDelta,
                                          std::abs(oldQtable(sI,jaI)-
                                                   _m_QValues[0](sI,jaI)));
                    }//end for jaI
                }//end for sI

                StopTimer("Iteration");

#if DEBUG_MDPValueIteration
                cout << "delta " << maxDelta << endl;
                PrintTimersSummary();
#endif
            }
        }
    }

    /// Uses the GetTransitionProbability() interface, which is slow.
    void PlanSlow();

protected:
    
public:
    // Constructor, destructor and copy assignment.
    /// (default) Constructor
    MDPValueIteration(){};

    MDPValueIteration(const PlanningUnitDecPOMDPDiscrete& pu);
    /// Destructor.
    ~MDPValueIteration();

    void Plan()
    {
        if(!_m_initialized)
            Initialize();

        StartTimer("Plan");
        
        size_t nrJA =  GetPU()->GetNrJointActions();
        const TransitionModelMappingSparse *tms=0;
        const TransitionModelMapping *tm=0;
        const TransitionModelDiscrete *tmd=
            GetPU()->GetTransitionModelDiscretePtr();

        if(tmd==0)
            PlanSlow(); // just use GetTransitionProbability()
        else if((tms=dynamic_cast<const TransitionModelMappingSparse *>(tmd)))
        {
            std::vector<const TransitionModelMappingSparse::SparseMatrix *> T;
            for(unsigned int a=0;a!=nrJA;++a)
                T.push_back(tms->GetMatrixPtr(a));
            Plan(T);
        }
        else if((tm=dynamic_cast<const TransitionModelMapping *>(tmd)))
        {
            std::vector<const TransitionModelMapping::Matrix *> T;
            for(unsigned int a=0;a!=nrJA;++a)
                T.push_back(tm->GetMatrixPtr(a));
            Plan(T);
        }
        else 
            throw(E("MDPValueIteration::Plan() TransitionModelDiscretePtr not handled"));
            
        StopTimer("Plan");
    }

    double GetQ(Index time_step, Index sI,
                Index jaI) const
        { return(_m_QValues[time_step](sI,jaI)); }

    double GetQ(Index sI, Index jaI) const
        { return(_m_QValues[0](sI,jaI)); }

    QTables GetQTables() const;
    QTable GetQTable(Index time_step) const;

    void SetQTables(const QTables &Qs);
    void SetQTable(const QTable &Q, Index time_step);

};


#endif /* !_MDPVALUEITERATION_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
