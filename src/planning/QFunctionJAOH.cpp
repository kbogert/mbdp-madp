/**\file QFunctionJAOH.cpp
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
 * $Id: QFunctionJAOH.cpp 3604 2009-08-25 10:52:24Z mtjspaan $
 */

#include "QFunctionJAOH.h"
#include "MDPSolver.h"
#include "PlanningUnitDecPOMDPDiscrete.h"
#include <fstream>

#define DEBUG_QHEUR_COMP 0

using namespace std;

QFunctionJAOH::QFunctionJAOH(
    const PlanningUnitDecPOMDPDiscrete &pu) :
    QFunctionForDecPOMDP(pu), //virtual base first
    QFunctionJAOHInterface()
{
}

void QFunctionJAOH::ComputeWithCachedQValues(string filenameCache)
{
    bool cached;

    {
        ifstream fp(filenameCache.c_str());
        if(!fp)
            cached=false;
        else
            cached=true;
    }

    // Couldn't open cache file, so compute
    if(!cached)
    {
        Compute();
        MDPSolver::SaveQTable(_m_QValues,filenameCache);

#if DEBUG_QHEUR_COMP
        cout << "QFunctionJAOH::ComputeWithCachedQValues saved Q values to "
             << filenameCache << endl;
#endif
    }
    else // load Q values from file
    {
        _m_QValues=
            MDPSolver::LoadQTable(filenameCache,
                                  GetPU()->
                                  GetNrJointActionObservationHistories(),
                                  GetPU()->GetNrJointActions());
#if DEBUG_QHEUR_COMP
        cout << "QFunctionJAOH::ComputeWithCachedQValues loaded Q values from "
             << filenameCache << endl;
#endif
    }
}
void QFunctionJAOH::ComputeWithCachedQValues()
{
    ComputeWithCachedQValues(GetCacheFilename());
}
