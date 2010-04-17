/**\file DICEPSPlanner.cpp
 *
 * Authors:
 * Frans Oliehoek <faolieho@science.uva.nl>
 * Matthijs Spaan <mtjspaan@isr.ist.utl.pt>
 * Julian Kooij <jkooij@science.uva.nl>
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
 * $Id: DICEPS.cpp 3637 2009-08-31 12:47:58Z mtjspaan $
 */

#include <time.h>
#include <sys/times.h>
#include <iostream>
#include <fstream>
#include <float.h>
#include "DICEPSPlanner.h"
#include "Timing.h"

#include "argumentHandlers.h"
#include "argumentUtils.h"

using namespace std;
using namespace ArgumentUtils;

#pragma comment(lib,"libMADPplanning.lib") 

const char *argp_program_version = "DICEPSPlanner";

// Program documentation
static char doc[] =
"DICEPSPlanner - runs the DICEPSPlanner \
\v";

//NOTE: make sure that the below value (nrChildParsers) is correct!
const int nrChildParsers = 5;
const struct argp_child childVector[] = {
    ArgumentHandlers::problemFile_child,
    ArgumentHandlers::globalOptions_child,
    ArgumentHandlers::CE_child,
    ArgumentHandlers::modelOptions_child,
    ArgumentHandlers::solutionMethodOptions_child,
    { 0 }
};

#include "argumentHandlersPostChild.h"

int main(int argc, char **argv)
{
    // parse the command line arguments
    ArgumentHandlers::Arguments args;
    argp_parse (&ArgumentHandlers::theArgpStruc, argc, argv, 0, 0, &args);
    int restarts = args.nrCERestarts;

    if(args.verbose >= 0)
        cout << "DICE: direct CE Policy Search"<<endl;

    srand(time(0));

    int horizon = args.horizon;
    if(args.verbose >= 1)
        cout << "Horizon = " << horizon << endl;

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
    params.SetComputeJointActionHistories(false);
    params.SetComputeIndividualActionObservationHistories(false);
    params.SetComputeIndividualActionHistories(false);
    //params.SetComputeIndividualObservationHistories(false);
    // joint observations histories are needed for
    // efficient computation of joint actions
    params.SetComputeJointObservationHistories(true);
    params.SetComputeJointBeliefs(false);
    if(args.sparse)
        params.SetUseSparseJointBeliefs(true);
    else
        params.SetUseSparseJointBeliefs(false);
    DICEPSPlanner* planner;
    planner = new DICEPSPlanner (params, &decpomdp,
        horizon,
        //CE params
        args.nrCERestarts,
        args.nrCEIterations,
        args.nrCESamples,
        args.nrCESamplesForUpdate, 
        args.CE_use_hard_threshold, //(gamma in CE papers)
        args.CE_alpha, //the learning rate
        args.nrCEEvalutionRuns //the number of evaluation runs
        , args.verbose
    );
    Time.Stop("PlanningUnit");
    if(args.verbose >= 0)
        cout << "DICEPSPlanner initialized" << endl;

    for(int restartI = 0; restartI < restarts; restartI++)
    {
        Time.Start("Plan");
        planner->Plan();
        Time.Stop("Plan");

        double V = planner->GetExpectedReward();
        cout << "value="<< V << endl;
        if(args.verbose >= 1)
        {
            planner->GetJointPolicyPureVector()->Print();
            cout <<  endl;
        }
    }
    /* clean up */

    Time.Stop("Overall");

    if(args.verbose >= 0)
    {
        Time.PrintSummary();
        planner->PrintTimersSummary();
    }

    delete planner;
    }
    catch(E& e){ e.Print(); }
}
