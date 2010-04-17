/**\file decTigerJESP.cpp
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
 * $Id: decTigerJESP.cpp 3003 2008-11-09 18:38:22Z mtjspaan $
 */

// Very short example program to demonstrate how to solve the DecTiger problem

#include "ProblemDecTiger.h"
#include "JESPDynamicProgrammingPlanner.h"

using namespace std;

//#pragma comment(lib,"MADP_dll.lib") 
#pragma comment(lib,"libMADPplanning.lib")

#include <time.h>
int main()
{
	time_t t = time(0);
	cout << "Seed: " << t << endl;
	srand(86);
    // construct problem
    ProblemDecTiger dectiger;
    // initialize planner for horizon 3
    JESPDynamicProgrammingPlanner jesp(3,&dectiger);
    // run the planning algorithm
    jesp.Plan();

    cout << "Value computed for DecTiger horizon 3: "
         << jesp.GetExpectedReward() << endl;
    cout << "Policy computed:" << endl;
    cout << jesp.GetJointPolicy()->SoftPrint() << endl;

    return(0);
}
