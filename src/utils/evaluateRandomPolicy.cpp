/**\file evaluateRandomPolicy.cpp
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
 * $Id: evaluateRandomPolicy.cpp 3598 2009-08-20 12:29:54Z mtjspaan $
 */


#include <iostream>
#include "DecPOMDPDiscrete.h"
#include "TOICompactRewardDecPOMDPDiscrete.h"
#include "MADPParser.h"
#include "directories.h"
#include "SimulationDecPOMDPDiscrete.h"
#include "NullPlanner.h"
#include "AgentRandom.h"
#include "argumentUtils.h"

using namespace std;
using namespace ArgumentUtils;

const char *argp_program_version = "evaluateRandomPolicy";

// Program documentation
static char doc[] =
"evaluateRandomPolicy - Evaluates a random policy  \
\v";

//NOTE: make sure that the below value (nrChildParsers) is correct!
const int nrChildParsers = 5;
const struct argp_child childVector[] = {
    ArgumentHandlers::problemFile_child,
    ArgumentHandlers::solutionMethodOptions_child,
    ArgumentHandlers::globalOptions_child,
    ArgumentHandlers::simulation_child,
    ArgumentHandlers::modelOptions_child,
    { 0 }
};

#include "argumentHandlersPostChild.h"

int main(int argc, char **argv)
{
    ArgumentHandlers::Arguments args;
    argp_parse (&ArgumentHandlers::theArgpStruc, argc, argv, 0, 0, &args);

    string dpomdpFile=directories::MADPGetProblemFilename(args);

    try {
    
    cout << "Initializing problem..."<<endl;
        
    TOICompactRewardDecPOMDPDiscrete *toi=0;
    DecPOMDPDiscreteInterface *dpomdp=0;
    PlanningUnitDecPOMDPDiscrete *np=0;
    if(args.isTOI)
    {
        toi=new TOICompactRewardDecPOMDPDiscrete("","",dpomdpFile);
        MADPParser parser(toi);
        dpomdp=toi;
        np=new NullPlanner(args.horizon,toi);
    }
    else
    {
        dpomdp = GetDecPOMDPDiscreteInterfaceFromArgs(args);
        cout << "DecPOMDP initialized" << endl;

        np=new NullPlanner(args.horizon,dpomdp);
        cout << "NullPlanner initialized" << endl;
    }

    SimulationResult result;
    SimulationDecPOMDPDiscrete sim(*np,args);
    vector<AgentFullyObservable*> agents;
    for(unsigned int i=0;i!=np->GetNrAgents();++i)
    {
        AgentFullyObservable *agent1;
        AgentRandom agent(*np,0);
        agent1=new AgentRandom(agent);
        agent1->SetIndex(i);
        agents.push_back(agent1);
    }
    result=sim.RunSimulations(agents);

    cout << "evaluateRandomPolicy sampled value: "
         << result.GetAvgReward() << endl;

    }
    catch(E& e){ e.Print(); }

    return(0);
}
