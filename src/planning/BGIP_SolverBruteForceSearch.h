/**\file BGIP_SolverBruteForceSearch.h
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
 * $Id: BGIP_SolverBruteForceSearch.h 3611 2009-08-25 15:02:24Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _BGIP_SOLVERBRUTEFORCESEARCH_H_
#define _BGIP_SOLVERBRUTEFORCESEARCH_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"
#include "JointPolicyPureVector.h"
#include "BayesianGameIdenticalPayoffSolver.h"
#include <float.h>
#include "TimeTools.h"
#include "Referrer.h"

#define DEBUG_BGIP_SOLVER_BFS 0
#define DEBUG_BGIP_SOLVER_BFS_PRINTOUTPROGRESS 0


/**\brief BGIP_SolverBruteForceSearch is a class that performs Brute
 * force search for identical payoff Bayesian Games.
 *
 * The template argument JP represents the joint policy class the
 * solver should return.
 */
template<class JP>
class BGIP_SolverBruteForceSearch : public BayesianGameIdenticalPayoffSolver<JP>
{
private:    
    ///stores the MaxPlus parameter for the verbosity level
    size_t _m_verbosity;
    ///stores the (desired) number of solutions
    size_t _m_nrSolutions;

protected:
    
public:
    // Constructor, destructor and copy assignment.
    // (default) Constructor
    //BGIP_SolverBruteForceSearch();
    /**Constructor. Directly Associates a problem with the planner
     * Information regarding the problem is used to construct a joint policy
     * of the proper shape.*/
    BGIP_SolverBruteForceSearch(const BayesianGameIdenticalPayoffInterface& bg,
                                size_t verbose=0, size_t nrSolutions=1) :
        BayesianGameIdenticalPayoffSolver<JP>(bg),
        _m_verbosity(verbose),
        _m_nrSolutions(nrSolutions)
        {}

    double Solve()
        {    
            struct timeval start_time, cur_time;
            if(gettimeofday(&start_time, NULL) != 0)
                throw "Error with gettimeofday";

            bool round = false;
            JP* jpol = BayesianGameIdenticalPayoffSolver<JP>::GetNewJpol();//new JP(*BayesianGameIdenticalPayoffSolver<JP>::GetReferred());
            JP best(*jpol);
            double v_best = -DBL_MAX;
            double v = 0.0;

            int i = 0;
            if(DEBUG_BGIP_SOLVER_BFS)
                std::cout<<"Starting Bruteforce search - v_best is init to "<<v_best<<std::endl;
#if DEBUG_BGIP_SOLVER_BFS_PRINTOUTPROGRESS
            LIndex nrJPols = GetReferred()->GetNrJointPolicies();
#endif
            
            while(!round)
            {
                if(DEBUG_BGIP_SOLVER_BFS){std::cout << "Jpol#"<< i << " - ";}
#if DEBUG_BGIP_SOLVER_BFS_PRINTOUTPROGRESS
                if(i % 1000 == 0&& i > 1000)
                {
                    std::cout << "Jpol #"<< i << " of " << nrJPols<< " - ";
                    printf("%.4f", ((double)i / nrJPols) * 100 );
                    std::cout << "%" << std::endl;
                }
#endif
                i++;
                //v = jpol->CalculateV();
                /*ValueFunctionDecPOMDPDiscrete vf(this, jpol);
                  v = vf.CalculateV0Recursively(true);//set caching to true!*/
        
                  size_t nrJT = BayesianGameIdenticalPayoffSolver<JP>::GetReferred()->GetNrJointTypes();
                  //size_t nrJA = GetNrJointActions() const {return _m_nrJA;}
                  v = 0.0;
        
                  for(Index jt = 0; jt < nrJT; jt++)
                  {
                      double P_jt = BayesianGameIdenticalPayoffSolver<JP>::GetReferred()->GetProbability(jt);
                      Index ja = jpol->GetJointActionIndex(jt);  
                      v += P_jt * BayesianGameIdenticalPayoffSolver<JP>::GetReferred()->GetUtility(jt, ja);
                  }

                  if(DEBUG_BGIP_SOLVER_BFS) std::cout << "Expected value = "<< v;
                  if(v > v_best)
                  {
                      if(DEBUG_BGIP_SOLVER_BFS) std::cout << " -> new best policy!!!";
                      v_best = v;
                      best = *jpol; 
                      if(BayesianGameIdenticalPayoffSolver<JP>::_m_writeAnyTimeResults){
                          double delta  = TimeTools::GetDeltaTimeDouble(start_time, cur_time);
                          (*BayesianGameIdenticalPayoffSolver<JP>::_m_results_f) << v_best << "\t";
                          (*BayesianGameIdenticalPayoffSolver<JP>::_m_timings_f) << delta << "\t";
                      }
                  }

                  // if we want more than just the single best solution, try to add all to the solution
                  if(_m_nrSolutions>1)
                      BayesianGameIdenticalPayoffSolver<JP>::_m_solution.AddSolution(*(new JP(*jpol)), v );
                      
                  if(DEBUG_BGIP_SOLVER_BFS) {    
                      std::cout <<  std::endl << "Incrementing joint policy..."<<std::endl; 
                      //std::cout << "jpol: "<<std::endl;
                      //jpol->Print();
                      //std::cout << "best: "<<std::endl; 
                      //best.Print(); //use this to see if best remains
                      //unaffected...
                  }    
                  round = ++(*jpol); //also seems not to be the leak ?
            }
            //end the line in the results file
            if(BayesianGameIdenticalPayoffSolver<JP>::_m_writeAnyTimeResults){
                (*BayesianGameIdenticalPayoffSolver<JP>::_m_results_f) << std::endl;
                (*BayesianGameIdenticalPayoffSolver<JP>::_m_timings_f) << std::endl;
            } 
            delete jpol;
            BayesianGameIdenticalPayoffSolver<JP>::_m_solution.SetPolicy(best);//best.Print();
            BayesianGameIdenticalPayoffSolver<JP>::_m_solution.SetPayoff(v_best);
    
            // also store the solution in the priority queue
            BayesianGameIdenticalPayoffSolver<JP>::_m_solution.AddSolution(*(new JP(best)), v_best );
            
            return(v_best);
        }
        
};


#endif /* !_BGIP_SOLVERBRUTEFORCESEARCH_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
