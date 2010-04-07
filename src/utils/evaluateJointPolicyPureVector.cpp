/**\file evaluateJointPolicyPureVector.cpp
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
 * $Id: evaluateJointPolicyPureVector.cpp 3598 2009-08-20 12:29:54Z mtjspaan $
 */


#include <iostream>
#include "DecPOMDPDiscreteInterface.h"
#include "MADPParser.h"
#include "directories.h"
#include "SimulationDecPOMDPDiscrete.h"
#include "JointPolicyPureVector.h"
#include "NullPlanner.h"


#include "argumentHandlers.h"
#include "argumentUtils.h"

using namespace std;
using namespace ArgumentUtils;

const char *argp_program_version = "evaluateJointPolicyPureVector";

// Program documentation
static char doc[] =
"evaluateJointPolicyPureVector - Evaluates a JointPolicyPureVector  \
\v";

//NOTE: make sure that the below value (nrChildParsers) is correct!
const int nrChildParsers = 6;
const struct argp_child childVector[] = {
    ArgumentHandlers::problemFile_child,
    ArgumentHandlers::solutionMethodOptions_child,
    ArgumentHandlers::jpolIndex_child,
    ArgumentHandlers::globalOptions_child,
    ArgumentHandlers::modelOptions_child,
    ArgumentHandlers::simulation_child,
    { 0 }
};

#include "argumentHandlersPostChild.h"

int main(int argc, char **argv)
{
    ArgumentHandlers::Arguments args;
    argp_parse (&ArgumentHandlers::theArgpStruc, argc, argv, 0, 0, &args);

    int h=args.horizon;
    LIndex index=args.jpolIndex;

    try {

    DecPOMDPDiscreteInterface* decpomdp = GetDecPOMDPDiscreteInterfaceFromArgs(args);
    if(args.discount!=-1)
        decpomdp->SetDiscount(args.discount);
    PlanningUnitMADPDiscreteParameters params;
    params.SetComputeAll(false);
    NullPlanner np(params,h,decpomdp);
    JointPolicyPureVector jp(np);
    jp.SetIndex(index);

    SimulationDecPOMDPDiscrete sim(np,args);
    SimulationResult result;

    result=sim.RunSimulations(&jp);

    cout << "Reward h " << h << " reward: " << result.GetAvgReward() << endl;

    }
    catch(E& e){ e.Print(); }

    return(0);
}
