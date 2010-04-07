/**\file JESP.cpp
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
 * $Id: JESP.cpp 3637 2009-08-31 12:47:58Z mtjspaan $
 */

#define CHECK_RESULT 0

#include <time.h>
#include <sys/times.h>
#include <iostream>
#include <fstream>
#include <float.h>
#include "JESPExhaustivePlanner.h"
#include "JESPDynamicProgrammingPlanner.h"
#include "Timing.h"
#include "SimulationDecPOMDPDiscrete.h"
#include "SimulationResult.h"

#include "argumentHandlers.h"
#include "argumentUtils.h"

using namespace std;
using namespace ArgumentUtils;


const char *argp_program_version = "JESP";

// Program documentation
static char doc[] =
"JESP - runs the JESP planner\
\v";

//NOTE: make sure that the below value (nrChildParsers) is correct!
const int nrChildParsers = 5;
const struct argp_child childVector[] = {
    ArgumentHandlers::problemFile_child,
    ArgumentHandlers::globalOptions_child,
    ArgumentHandlers::modelOptions_child,
    ArgumentHandlers::solutionMethodOptions_child,
    ArgumentHandlers::JESP_child,
    { 0 }
};

#include "argumentHandlersPostChild.h"

int main(int argc, char **argv)
{
    ArgumentHandlers::Arguments args;
    argp_parse (&ArgumentHandlers::theArgpStruc, argc, argv, 0, 0, &args);
    int restarts = args.JESPnrRestarts;

    srand(time(0));

    int horizon=args.horizon;

    try {
    //start timers
    Timing Time;    
    Time.Start("Overall");

    DecPOMDPDiscreteInterface & decpomdp = * GetDecPOMDPDiscreteInterfaceFromArgs(args);
    
    //Initialization of the planner with typical options for JESP:
    Time.Start("PlanningUnit");
    PlanningUnitMADPDiscreteParameters params;
    params.SetComputeAll(true);
    params.SetComputeJointActionObservationHistories(false);
    params.SetComputeJointObservationHistories(false);
    params.SetComputeJointBeliefs(false);
    if(args.sparse)
        params.SetUseSparseJointBeliefs(true);
    else
        params.SetUseSparseJointBeliefs(false);
    PlanningUnitDecPOMDPDiscrete* jesp = 0;
    if(args.jesp == JESPtype::JESPExhaustive)
    {
        jesp = new JESPExhaustivePlanner (params,horizon,&decpomdp);
        if(args.verbose >= 0)
            cout << "JESPExhaustivePlanner initialized" << endl;
    }
    else if(args.jesp == JESPtype::JESPDP)
    {
        jesp = new JESPDynamicProgrammingPlanner (params,horizon,&decpomdp);
        if(args.verbose >= 0)
            cout << "JESPDynamicProgrammingPlanner initialized" << endl;
    }
    Time.Stop("PlanningUnit");
    if(args.verbose >= 0)
        cout << "JESP Planner initialized" << endl;

    for(int restartI = 0; restartI < restarts; restartI++)
    {
        //start all timers:
        Time.Start("Plan");

        jesp->Plan();
        double V = jesp->GetExpectedReward();
        cout << "value="<< V << endl;
        if(args.verbose >= 1) 
        {
            jesp->GetJointPolicyPureVector()->Print();
            cout <<  endl;
        }

        Time.Stop("Plan");

#if CHECK_RESULT
        ValueFunctionDecPOMDPDiscrete vf(jesp, jesp->GetJointPolicyPureVector());
        double v = vf.CalculateV(true);
        cout << "Validated value (exact/approx):="<<v;
        SimulationDecPOMDPDiscrete sim(*jesp, 1000);
        SimulationResult simres = 
            sim.RunSimulations( jesp->GetJointPolicyPureVector() );
        v = simres.GetAvgReward();
        cout << " / "<<v <<endl;
#endif

    }

    delete jesp;
    
    Time.Stop("Overall");

    if(args.verbose >= 0)
    {
        Time.PrintSummary();
    }

    }
    catch(E& e){ e.Print(); }
}
