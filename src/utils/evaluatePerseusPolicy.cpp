/**\file evaluatePerseusPolicy.cpp
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
 * $Id: evaluatePerseusPolicy.cpp 3258 2009-04-27 21:34:43Z faolieho $
 */


#include <iostream>
#include "TOIDecPOMDPDiscrete.h"
#include "directories.h"
#include "SimulationDecPOMDPDiscrete.h"
#include "NullPlanner.h"
#include "AgentPOMDP.h"
#include "AgentBG.h"
#include "PerseusBackupType.h"
#include "AlphaVectorBG.h"
#include "Perseus.h"
#include "PerseusBGPlanner.h"
#include "BeliefValue.h"
#include "AlphaVectorPlanning.h"
#include "JointBelief.h"
#include <float.h>
#include "argumentHandlers.h"
#include "argumentUtils.h"

using namespace std;
using namespace ArgumentUtils;

using namespace std;

const char *argp_program_version = "evaluatePerseusPolicy";

// Program documentation
static char doc[] =
"evaluatePerseusPolicy - simulate Perseus value functions \
\v";

//NOTE: make sure that the below value (nrChildParsers) is correct!
const int nrChildParsers = 6;
const struct argp_child childVector[] = {
    ArgumentHandlers::problemFile_child,
    ArgumentHandlers::globalOptions_child,
    ArgumentHandlers::modelOptions_child,
    ArgumentHandlers::solutionMethodOptions_child,
    ArgumentHandlers::perseusbackup_child,
    ArgumentHandlers::simulation_child,
    { 0 }
};

#include "argumentHandlersPostChild.h"

int main(int argc, char **argv)
{
    try {

    ArgumentHandlers::Arguments args;
    argp_parse (&ArgumentHandlers::theArgpStruc, argc, argv, 0, 0, &args);

    QAVParameters qavParams=Perseus::ProcessArguments(args);

    DecPOMDPDiscreteInterface* decpomdp;
    decpomdp = GetDecPOMDPDiscreteInterfaceFromArgs(args);

    stringstream valueFunction;
    valueFunction << directories::MADPGetResultsFilename("POMDP",*decpomdp,args)
                  << "Perseus"
                  << Perseus::BackupTypeToString(qavParams) 
                  << "ValueFunction_h";
    if(args.infiniteHorizon)
        valueFunction << MAXHORIZON;
    else
        valueFunction << args.horizon;

    if(args.isTOI)
    {
        if(args.sparse)
            dynamic_cast<TOIDecPOMDPDiscrete*>(decpomdp)->CreateCentralizedSparseModels();
        else
            dynamic_cast<TOIDecPOMDPDiscrete*>(decpomdp)->CreateCentralizedFullModels();
    }

    size_t horizon;
    if(!args.infiniteHorizon)
        horizon=args.horizon;
    else
        horizon=MAXHORIZON;
   
    PlanningUnitMADPDiscreteParameters params;
    params.SetComputeAll(false);
    if(args.sparse)
        params.SetUseSparseJointBeliefs(true);
    else
        params.SetUseSparseJointBeliefs(false);
    PlanningUnitDecPOMDPDiscrete *np=new NullPlanner(params,horizon,
                                                     decpomdp);

    SimulationDecPOMDPDiscrete sim(*np,args);
    SimulationResult result;

    switch(args.backup)
    {
    case POMDP:
    {
        vector<AgentSharedObservations*> agents;
        AgentSharedObservations *agent1;
        QAV<PerseusPOMDPPlanner> *Qpomdp=
            new QAV<PerseusPOMDPPlanner>(*np,valueFunction.str());
        for(unsigned int i=0;i!=decpomdp->GetNrAgents();++i)
        {
            agent1=new AgentPOMDP(*np,0,Qpomdp);
            agent1->SetIndex(i);
            agents.push_back(agent1);
        }
        result=sim.RunSimulations(agents);
        break;
    }
    case BG:
    {
        vector<AgentDelayedSharedObservations*> agents;
        QAV<PerseusBGPlanner> *Qbg=
            new QAV<PerseusBGPlanner>(*np,valueFunction.str());
        AgentDelayedSharedObservations *agent1;
        for(unsigned int i=0;i!=decpomdp->GetNrAgents();++i)
        {
            agent1=new AgentBG(*np,0,Qbg);
            agent1->SetIndex(i);
            agents.push_back(agent1);
        }
        result=sim.RunSimulations(agents);
        break;
    }
    default:
        throw("PerseusBackupType is unknown");
    }

    double Vjb0;
    Vjb0=
        BeliefValue::GetValue(JointBelief(*decpomdp->GetISD()),
                              AlphaVectorPlanning::
                              ImportValueFunction(valueFunction.str()));

    if(args.verbose < 0)
        cout << result.GetAvgReward() << " " << Vjb0 << endl;
    else
    {
        cout << "Empirical control quality (h " << horizon << " backup "
             << Perseus::BackupTypeToString(qavParams)
             << " V(jb0) " << Vjb0 << ") = " << result.GetAvgReward() << endl;
    }

    }
    catch(E& e){ e.Print(); }

    return(0);
}
