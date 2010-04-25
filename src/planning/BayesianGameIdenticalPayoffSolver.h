/**\file BayesianGameIdenticalPayoffSolver.h
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
 * $Id: BayesianGameIdenticalPayoffSolver.h 3603 2009-08-25 10:38:25Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _BAYESIANGAMEIDENTICALPAYOFFSOLVER_H_
#define _BAYESIANGAMEIDENTICALPAYOFFSOLVER_H_ 1

/* the include directives */
#include <iostream>
#include <fstream>
#include "Globals.h"

#include "Referrer.h"
#include "BayesianGameIdenticalPayoff.h"
#include "JointPolicy.h"
#include "JointPolicyPureVector.h"
#include "BGIPSolution.h"

//needed for timing results
#include <sys/time.h>
#include <time.h>


/**\brief BayesianGameIdenticalPayoffSolver is an interface for
 * solvers for Bayesian games with identical payoff.
 *
 * The template argument JP represents the joint policy class the
 * solver should return.
 */
template<class JP>
class BayesianGameIdenticalPayoffSolver : 
    public Referrer<BayesianGameIdenticalPayoffInterface>
{
private:    
    
protected:
    ///Stores the solution found by the solver
    BGIPSolution _m_solution;
    ///This variable gives the number of solutions to return (k).

    ///boolean that indicates whether anytime results should be written
    bool _m_writeAnyTimeResults;

    ///the file to which writes the results are written
    std::ofstream* _m_results_f;
    ///the file to which writes the timings of the results are written
    std::ofstream* _m_timings_f;

    
public:
    // Constructor, destructor and copy assignment.
    /// (default) Constructor 
    /**takes a reference to the BG to be solved. nrSolutions is the number
     * of solutions that the solver should return. I.e., if set higher than
     * 1, it returns the k best found joint policies.
     */
    BayesianGameIdenticalPayoffSolver<JP>(
            const BayesianGameIdenticalPayoffInterface& bg,
            size_t nrSolutions=1) :
        Referrer<BayesianGameIdenticalPayoffInterface>::Referrer(
            const_cast<BayesianGameIdenticalPayoffInterface&>(bg)),
        _m_solution(bg, nrSolutions),
        _m_writeAnyTimeResults(false)
        {
        }

    /// Destructor.
    virtual ~BayesianGameIdenticalPayoffSolver(){};
    
    /**\brief The methods that performs the planning. Returns the
     * expected reward.*/
    virtual double Solve() = 0;
        
    const JointPolicy* GetJointPolicy() const 
        { return(_m_solution.GetJointPolicy()); }
    const JointPolicyPureVector& GetJointPolicyPureVector() const 
        { return(_m_solution.GetJointPolicyPureVector()); }
    double GetExpectedReward() const 
        { return(_m_solution.GetPayoff()); }
    const BGIPSolution & GetSolution() const 
        { return(_m_solution); }
    BGIPSolution & GetSolution()
        { return(_m_solution); }

    ///Turns Anytime results on and of 
    /**When turning on, valid ofstream pointers must be provided for the 
     * results and timings file.
     */
    void SetAnyTimeResults(bool turn_on, std::ofstream* results, 
            std::ofstream* timings)
        {
            _m_writeAnyTimeResults = turn_on;
            if(turn_on)
            {
                _m_results_f = results;
                _m_timings_f = timings;         
            }
            else
            {
                _m_results_f = NULL;
                _m_timings_f = NULL;
            }
        }
    
    double Evaluate(const JP & jpolBG) const
        {
            BayesianGameIdenticalPayoffInterface *bgip=GetReferred();
            double v = 0.0;
            for(Index jt = 0; jt < bgip->GetNrJointTypes(); jt++)
            {
                Index jaI = jpolBG.GetJointActionIndex(jt);  
                double p = bgip->GetProbability(jt);
                double u = bgip->GetUtility(jt, jaI);
                v += p * u;    
            }
            return v;
        }

    JP *GetNewJpol() const
        {
            JP* jpol=new JP(*GetReferred());
            return(jpol);
        }

    ///Gets the desired number of solutions to be returned
    size_t GetNrDesiredSolutions() const 
    {return _m_solution.GetNrDesiredSolutions();};
    ///Gets the found number of solutions
    size_t GetNrFoundSolutions() const 
    {return _m_solution.GetNrFoundSolutions();};
};


#endif /* !_BAYESIANGAMEIDENTICALPAYOFFSOLVER_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
