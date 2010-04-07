/**\file BGIP_SolverAlternatingMaximization.h
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
 * $Id: BGIP_SolverAlternatingMaximization.h 3603 2009-08-25 10:38:25Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _BGIP_SOLVERALTERNATINGMAXIMIZATION_H_
#define _BGIP_SOLVERALTERNATINGMAXIMIZATION_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"
#include "TimeTools.h"
#include <float.h>
#include "Referrer.h"

#include "BayesianGameIdenticalPayoffSolver.h"
class JointPolicyPureVector;


#define DEBUG_BGIP_SOLVER_AM_SOLVE 0
#define DEBUG_BGIP_SOLVER_AM_SOLVE_EXTRAVERBOSE 0
#define CHECK_NEW_BR 0

/**\brief BGIP_SolverAlternatingMaximization implements an approximate
 * solver for identical payoff Bayesian games, based on alternating
 * maximization. 
 * 
 * The template argument JP represents the joint policy class the
 * solver should return.
 */
template<class JP>
class BGIP_SolverAlternatingMaximization
    : public BayesianGameIdenticalPayoffSolver<JP>
{
private:    
    
    unsigned int _m_nrRestarts;
    int _m_verbose;
#define DEBUG_CBR 0
    double ComputeBestResponse(JP & jpolBG, 
            Index optimizingAgentI)
        {
            if(DEBUG_CBR)
            {
                std::cout << "ComputeBestResponse called - current jpolBG:"<<std::endl;
                jpolBG.Print();
                std::cout << "value="<<Evaluate(jpolBG)<<std::endl;
            }
            BayesianGameIdenticalPayoffInterface *bgip=BayesianGameIdenticalPayoffSolver<JP>::GetReferred();
            Index agI = optimizingAgentI;
            std::vector< std::vector<double> > v (bgip->GetNrTypes(agI), std::vector<double>(
                                            bgip->GetNrActions(agI), 0.0) );
    
            //compute all type-action values for agent agI
            for(Index jt = 0; jt < bgip->GetNrJointTypes(); jt++)
            {
                std::vector<Index> types = bgip->JointToIndividualTypeIndices(jt);
                Index type = types.at(agI);
                double jtProb = bgip->GetProbability(jt);
                Index jaI = jpolBG.GetJointActionIndex(jt);
                std::vector<Index> avec = bgip->JointToIndividualActionIndices(jaI);
                for(Index acI =0 ; acI < bgip->GetNrActions(agI); acI++)
                {
                    avec.at(agI) = acI;
                    Index jaInew = bgip->IndividualToJointActionIndices(avec);
                    v[type][acI] +=  jtProb * bgip->GetUtility(jt, jaInew);
                }
            }
            //compute the best response and value
            double v_best = 0.0;
            for(Index type = 0; type < bgip->GetNrTypes(agI); type++)
            {
                double v_t = -DBL_MAX;
                Index best_a = 0;
                for(Index acI = 0; acI < bgip->GetNrActions(agI); acI++)
                {
                    double v_t_a = v[type][acI];
                    if(v_t_a > v_t)
                    {
                        best_a = acI;
                        v_t = v_t_a;
                    }
                }
                v_best += v_t;
                jpolBG.SetAction(agI, type, best_a);
            }
            return v_best;
        }

protected:
    
public:
    // Constructor, destructor and copy assignment.
    /// (default) Constructor
    BGIP_SolverAlternatingMaximization(
            const BayesianGameIdenticalPayoffInterface& bg,
            unsigned int nrRestarts=10, 
            int verbose=0,
            size_t nrSolutions=1) :
        BayesianGameIdenticalPayoffSolver<JP>(bg, nrSolutions),
        _m_nrRestarts(nrRestarts),
        _m_verbose(verbose)
        {
        }

    /// Destructor.
    ~BGIP_SolverAlternatingMaximization(){};
    double Solve()
        {
            if(_m_verbose >= 1)
                std::cout << "BGIP_SolverAlternatingMaximization::Solve() started"<<std::endl;
            BayesianGameIdenticalPayoffInterface *bgip=BayesianGameIdenticalPayoffSolver<JP>::GetReferred();
    
            struct timeval start_time, cur_time;
            if(gettimeofday(&start_time, NULL) != 0)
                throw "Error with gettimeofday";

            JP *temp=BayesianGameIdenticalPayoffSolver<JP>::GetNewJpol();
            JP jpolBG(*temp);
            JP best=jpolBG;
            delete temp;
            double vmax = -DBL_MAX;
            
            for(Index r=0; r < _m_nrRestarts; ++r)
            {
                if(_m_verbose >= 1)
                    std::cout << "AM: new restart"<<std::endl;
                double v_thisAMrun = -DBL_MAX;
                jpolBG.RandomInitialization();

                //eval the expected payoff of this jpolBG
                double v = Evaluate(jpolBG);
                
                v_thisAMrun = v;
                Index optimizingAgentI = 0;
#if DEBUG_BGIP_SOLVER_AM_SOLVE
                {
                    std::std::cout<<"\n>new AM restart - initialized with v="<<
                        v_thisAMrun;
#if DEBUG_BGIP_SOLVER_AM_SOLVE_EXTRAVERBOSE
                    std::std::cout << " - pol:"<<std::std::endl;
                    jpolBG.Print();
#endif
                    std::std::cout << std::std::endl;
                }
#endif
                
                bool improving = true;
                size_t nr_non_improving_agents = 0;

//TODO: this fails if (in the 2 agent case) the agent that cannot make 
// improvement is the first to try
//      while(nr_non_improving_agents <  (bgip->GetNrAgents() - 1) ) 
                while(nr_non_improving_agents <  bgip->GetNrAgents() ) 
                {
                    if(_m_verbose >= 2 )
                        std::cout << "AM: computing new best response...";
                    improving = false;//unless improvement is found
                    //find best response
                    v = ComputeBestResponse(jpolBG, optimizingAgentI);
                    if(_m_verbose >= 2)
                        std::cout << "v="<<v<<std::endl;
#if CHECK_NEW_BR            
                    JP checkjpolBG = jpolBG;
                    double vcheck = 
                        ComputeBestResponseOld(checkjpolBG, optimizingAgentI);
                    if(jpolBG.GetIndex() != checkjpolBG.GetIndex())
                    {
                        std::cout << "Error best response computation failed!!!"<<std::endl;
                        std::cout << "v="<<v<<", vcheck="<<vcheck<<std::endl;
                        std::cout << "jpolBG="<< jpolBG.SoftPrint();
                        std::cout << "checkjpolBG="<< jpolBG.SoftPrint();
                    }
#endif            
#if DEBUG_BGIP_SOLVER_AM_SOLVE            
                    {
                        std::std::cout<<"best response achieves v="<< v ;
#if DEBUG_BGIP_SOLVER_AM_SOLVE_EXTRAVERBOSE
                        std::std::cout << " - pol:"<<std::std::endl;
                        jpolBG.Print();
#endif
                        std::std::cout << std::std::endl;
                    }
#endif

                    if(v > v_thisAMrun  + 1e-9)
                    {
#if DEBUG_BGIP_SOLVER_AM_SOLVE            
                        std::std::cout << "(improving)" <<std::std::endl;
#endif
                        v_thisAMrun = v;
                        improving = true;                
                    }

                    //next agent
                    if(improving)
                        nr_non_improving_agents = 0;
                    else
                        nr_non_improving_agents++;

                    optimizingAgentI = (optimizingAgentI+1) % bgip->GetNrAgents();
                } // end of this alternating maximization run        
                if(DEBUG_BGIP_SOLVER_AM_SOLVE)
                    std::cout << "AM run ended" <<std::endl;

                size_t oldNrSolutionsFound=
                    BayesianGameIdenticalPayoffSolver<JP>::_m_solution.GetNrFoundSolutions();

                //store the solution
                BayesianGameIdenticalPayoffSolver<JP>::_m_solution.AddSolution( *(new JP(jpolBG)), // make a copy! (jpolBG is local)
                                         v_thisAMrun );
                if(_m_verbose >= 1)
                    if(BayesianGameIdenticalPayoffSolver<JP>::_m_solution.GetNrFoundSolutions()
                       != (oldNrSolutionsFound+1))
                        std::cout << "AM: computed policy not added to BGIPSolution, probably a duplicate" << std::endl;
                
                if(v_thisAMrun > vmax)
                {
                    vmax = v_thisAMrun;
                    best = jpolBG;
                    if(DEBUG_BGIP_SOLVER_AM_SOLVE)
                        std::cout << "(best solution)" <<std::endl;
                    
                    if(BayesianGameIdenticalPayoffSolver<JP>::_m_writeAnyTimeResults){
                        double delta  = TimeTools::GetDeltaTimeDouble(start_time, cur_time);
                        (*BayesianGameIdenticalPayoffSolver<JP>::_m_results_f) << vmax << "\t";
                        (*BayesianGameIdenticalPayoffSolver<JP>::_m_timings_f) << delta << "\t";
                    }
                }
            }
            //end the line in the results file
            if(BayesianGameIdenticalPayoffSolver<JP>::_m_writeAnyTimeResults){
                (*BayesianGameIdenticalPayoffSolver<JP>::_m_results_f) << std::endl;
                (*BayesianGameIdenticalPayoffSolver<JP>::_m_timings_f) << std::endl;
            } 
            
            BayesianGameIdenticalPayoffSolver<JP>::_m_solution.SetPolicy(best);//best.Print();
            BayesianGameIdenticalPayoffSolver<JP>::_m_solution.SetPayoff(vmax);

#if 0
            //check the solution
            std::cout << "BGIP_SolverAlternatingMaximization finished, first solution: " << 
                _m_solution.GetNextSolution()->SoftPrint() << std::endl;
#endif
            return(vmax);
        }

};


#endif /* !_BGIP_SOLVERALTERNATINGMAXIMIZATION_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
