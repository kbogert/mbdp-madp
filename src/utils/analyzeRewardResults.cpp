/**\file analyzeRewardResults.cpp
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
 * $Id: analyzeRewardResults.cpp 2117 2008-01-16 23:14:36Z mtjspaan $
 */

#include <iostream>
#include "SimulationResult.h"

using namespace std;

int main(int argc, char **argv)
{
    if(argc!=2)
    {
        cout << "Use as follows: analyzeRewardResults "
             << "<resultsFile>" << endl;
        return(1);
    }

    string rewardsFile=string(argv[1]);

    try {
        SimulationResult result;
        result.Load(rewardsFile);
        result.PrintSummary();
    }
    catch(E& e){ e.Print(); }
}
