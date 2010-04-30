/**\file MBDP.cpp
 *
 * Authors:
 * Christopher Jackson <christopher.jackson@gmail.com>
 *
 * Copyright 2010 Institute for Artificial Intelligence, The University of Georgia
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
 * $Id: $
 */

#define CHECK_RESULT 0

#include <time.h>
#include <sys/times.h>
#include <iostream>
#include <fstream>
#include <float.h>
#include "MBDPPlanner.h"
#include "Timing.h"
#include "SimulationDecPOMDPDiscrete.h"
#include "SimulationResult.h"

#include "argumentHandlers.h"
#include "argumentUtils.h"

using namespace std;
using namespace ArgumentUtils;


const char *argp_program_version = "MBDP";

// Program documentation
static char doc[] =
"MBDP - runs the MBDP planner\
\v";

//NOTE: make sure that the below value (nrChildParsers) is correct!
const int nrChildParsers = 5;
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

    srand(time(0));

    int horizon=args.horizon;

    try {
    //start timers
    Timing Time;    
    Time.Start("Overall");

    DecPOMDPDiscreteInterface & decpomdp = * GetDecPOMDPDiscreteInterfaceFromArgs(args);
    
    //Initialization of the planner with typical options for MBDP
    Time.Start("PlanningUnit");
    PlanningUnitMADPDiscreteParameters params;
    params.SetComputeAll(true);
    PlanningUnitDecPOMDPDiscrete* mbdp = 0;
    mbdp = new MBDPPlanner (params, horizon, &decpomdp, 3, 3.0);
    Time.Stop("PlanningUnit");
    
    if(args.verbose >= 0)
        cout << "MBDP Planner initialized" << endl;

    int restarts = 5;
    for(int restartI = 0; restartI < restarts; restartI++)
    {
        //start all timers:
        Time.Start("Plan");

        mbdp->Plan();
        double V = mbdp->GetExpectedReward();
        cout << "value="<< V << endl;
        if(args.verbose >= 1) 
        {
            mbdp->GetJointPolicyPureVector()->Print();
            cout <<  endl;
        }

        Time.Stop("Plan");

#if CHECK_RESULT
        ValueFunctionDecPOMDPDiscrete vf(mbdp, mbdp->GetJointPolicyPureVector());
        double v = vf.CalculateV(true);
        cout << "Validated value (exact/approx):="<<v;
        SimulationDecPOMDPDiscrete sim(*mbdp, 1000);
        SimulationResult simres = 
            sim.RunSimulations( mbdp->GetJointPolicyPureVector() );
        v = simres.GetAvgReward();
        cout << " / "<<v <<endl;
#endif

    }

    delete mbdp;
    
    Time.Stop("Overall");

    if(args.verbose >= 0)
    {
        Time.PrintSummary();
    }

    }
    catch(E& e){ e.Print(); }
}
