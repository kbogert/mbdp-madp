/**\file BGIP_SolverRandom.cpp
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
 * $Id: BGIP_SolverRandom.cpp 3604 2009-08-25 10:52:24Z mtjspaan $
 */

#include "BGIP_SolverRandom.h"
#include "TimeTools.h"
#include <float.h>

using namespace std;

//Default constructor
BGIP_SolverRandom::BGIP_SolverRandom(
        const BayesianGameIdenticalPayoff& bg) :
    BayesianGameIdenticalPayoffSolver<JointPolicyPureVector>(bg)
{}

double BGIP_SolverRandom::Solve()
{    
    JointPolicyPureVector jpol(*GetReferred());
    jpol.RandomInitialization();

    double v = 0.0;
    
    for(Index jt = 0; jt < GetReferred()->GetNrJointTypes(); jt++)
    {
        double P_jt = GetReferred()->GetProbability(jt);
        Index ja = jpol.GetJointActionIndex(jt);  
        v += P_jt * GetReferred()->GetUtility(jt, ja);
    }
    
    _m_solution.SetPolicy(jpol);
    _m_solution.SetPayoff(v);

    return(v);
}
