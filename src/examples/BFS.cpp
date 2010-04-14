/**\file BFS.cpp
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
 * $Id: BFS.cpp 3637 2009-08-31 12:47:58Z mtjspaan $
 */

#include <time.h>
#include <sys/times.h>
#include <iostream>
#include <fstream>
#include <float.h>

#include "BruteForceSearchPlanner.h"

#include "argumentHandlers.h"
#include "argumentUtils.h"

using namespace std;
using namespace ArgumentUtils;

#pragma comment(lib,"MADP_dll.lib") 

const char *argp_program_version = "BFS";

// Program documentation
static char doc[] =
"BFS - runs the BruteForceSearchPlanner \
\v";

//NOTE: make sure that the below value (nrChildParsers) is correct!
const int nrChildParsers = 4;
const struct argp_child childVector[] = {
    ArgumentHandlers::problemFile_child,
    ArgumentHandlers::globalOptions_child,
    ArgumentHandlers::modelOptions_child,
    ArgumentHandlers::solutionMethodOptions_child,
    { 0 }
};

#include "argumentHandlersPostChild.h"

int main(int argc, char **argv)
{
    ArgumentHandlers::Arguments args;
    argp_parse (&ArgumentHandlers::theArgpStruc, argc, argv, 0, 0, &args);

    int horizon=args.horizon;

    try {

    DecPOMDPDiscreteInterface & decpomdp = * GetDecPOMDPDiscreteInterfaceFromArgs(args);

    PlanningUnitMADPDiscreteParameters params;
    params.SetComputeAll(true);
    if(args.sparse)
        params.SetUseSparseJointBeliefs(true);
    else
        params.SetUseSparseJointBeliefs(false);

    BruteForceSearchPlanner bfs(params,horizon,&decpomdp);

    if(args.verbose >= 0)
        cout << "BruteForceSearchPlanner initialized" << endl;

    bfs.Plan();
    double V = bfs.GetExpectedReward();
    cout << "\nvalue="<< V << endl;
    if(args.verbose >= 1)
        bfs.GetJointPolicyPureVector()->Print();

    }
    catch(E& e){ e.Print(); }
}
