/**\file BGIPSolution.h
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
 * $Id: BGIPSolution.h 3611 2009-08-25 15:02:24Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _BGIPSOLUTION_H_
#define _BGIPSOLUTION_H_ 1

/* the include directives */
#include <iostream>
#include <set>
#include "Globals.h"
#include "JointPolicyPureVector.h"
#include "FixedCapacityPriorityQueue.h"

//forward declarations:
class JPPVValuePair;
class PartialJPDPValPair;

/**\brief BGIPSolution represents a solution for BayesianGameIdenticalPayoff.*/
class BGIPSolution 
{
private:    

    const Interface_ProblemToPolicyDiscretePure& _m_pu;
    JointPolicyPureVector *_m_policy;
    LIndex _m_jpolIndex;
    double _m_payoff;

    ///This variable gives the number of solutions to return (k).
    size_t _m_nrSolutions;

    /**if we want to return the best k solutions, we store them in a priority 
     *queue.
     */
    FixedCapacityPriorityQueue<JPPVValuePair *> _m_q;
    
    //The set of Indicies of the policies added to the queue
    //(to avoid adding duplicates).
    std::set<Index> _m_jpolIndices;

protected:
    
public:
    // Constructor, destructor and copy assignment.
    /// (default) Constructor
    BGIPSolution(const Interface_ProblemToPolicyDiscretePure& pu,
                 size_t nrSolutions=1);
    /// Destructor.
    ~BGIPSolution();

    void SetPayoff(double payoff) { _m_payoff=payoff; }
    double GetPayoff() const { return(_m_payoff); }

    void SetPolicy(const JointPolicyPureVector &jpol);
    void SetPolicy(LIndex jpolIndex);

    const JointPolicy* GetJointPolicy() const { return(_m_policy); }
    const JointPolicyPureVector& GetJointPolicyPureVector() const {
        return(*_m_policy); }
    LIndex GetPolicyIndex() { return(_m_jpolIndex); }

    void Save(std::string filename) const;
    void Load(std::string filename);

    void Print() const { std::cout << SoftPrint() << std::endl; }
    std::string SoftPrint() const;

    size_t GetNrDesiredSolutions() const {return _m_nrSolutions;};
    size_t GetNrFoundSolutions() const {return _m_q.size();};

    /**\brief Adds a JPPVValuePair to the priority queue that maintains the best 
     * _m_nrSolutions solutions.
     *
     * Any old solutions that are no longer needed are automatically deleted.
     */
    void AddSolution(JointPolicyPureVector &jp, double value );

    JPPVValuePair* GetNextSolutionJPPV() {return _m_q.top(); };
    void PopNextSolutionJPPV() { _m_q.pop(); };
    bool IsEmptyJPPV() { return _m_q.empty(); };

};


#endif /* !_BGIPSOLUTION_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
