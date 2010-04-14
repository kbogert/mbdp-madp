/**\file Perseus.cpp
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
 * $Id: Perseus.cpp 4011 2010-03-11 14:52:19Z mtjspaan $
 */

#include <iostream>
#include "PerseusPOMDPPlanner.h"
#include "PerseusBGPlanner.h"
#include "TOIDecPOMDPDiscrete.h"
#include "NullPlanner.h"
#include "directories.h"
#include "float.h"
#include "argumentHandlers.h"
#include "argumentUtils.h"

using namespace std;
using namespace ArgumentUtils;

#pragma comment(lib,"MADP_dll.lib") 

const char *argp_program_version = "Perseus";

// Program documentation
static char doc[] =
"Perseus - runs Perseus planners \
\v";

//NOTE: make sure that the below value (nrChildParsers) is correct!
const int nrChildParsers = 7;
const struct argp_child childVector[] = {
    ArgumentHandlers::problemFile_child,
    ArgumentHandlers::globalOptions_child,
    ArgumentHandlers::modelOptions_child,
    ArgumentHandlers::solutionMethodOptions_child,
    ArgumentHandlers::perseus_child,
    ArgumentHandlers::perseusbelief_child,
    ArgumentHandlers::perseusbackup_child,
    { 0 }
};

#include "argumentHandlersPostChild.h"

int main(int argc, char **argv)
{
    try
    {

    ArgumentHandlers::Arguments args;
    argp_parse (&ArgumentHandlers::theArgpStruc, argc, argv, 0, 0, &args);

    size_t horizon;
    if(args.infiniteHorizon)
        horizon=MAXHORIZON;
    else
        horizon=args.horizon;
    
    QAVParameters qavParams=Perseus::ProcessArguments(args);

    DecPOMDPDiscreteInterface* decpomdp;
    decpomdp = GetDecPOMDPDiscreteInterfaceFromArgs(args);

    string resultsDir=directories::MADPGetResultsDir("POMDP",decpomdp);

    if(args.isTOI)
    {
        // necessary for running Perseus
        if(args.sparse)
        {
            cout << "Creating centralized sparse models"; cout.flush();
            dynamic_cast<TOIDecPOMDPDiscrete*>(decpomdp)->CreateCentralizedSparseModels();
            cout << "." << endl;
        }
        else
        {
            cout << "Creating centralized full models"; cout.flush();
            dynamic_cast<TOIDecPOMDPDiscrete*>(decpomdp)->CreateCentralizedFullModels();
            cout << "." << endl;
        }
    }

    PlanningUnitMADPDiscreteParameters params;
    params.SetComputeAll(false);
    if(args.sparse)
        params.SetUseSparseJointBeliefs(true);
    else
        params.SetUseSparseJointBeliefs(false);
    NullPlanner *np=new NullPlanner(params,horizon,decpomdp);
    
    Perseus *P;
    PerseusStationary *PS=0;
    switch(args.backup)
    {
    case POMDP:
        PS=new PerseusPOMDPPlanner(*np);
        break;
    case BG:
        PS=new PerseusBGPlanner(*np,qavParams);
        break;
    default:
        throw(E("PerseusBackupType is unknown"));
    }
    P=PS;

    P->SetVerbose(args.verbose);
    if(args.minimumNrIterations)
        P->SetMinimumNumberOfIterations(args.minimumNrIterations);
    if(args.initializeWithZero)
        P->SetInitializeWithZero(true);
    if(args.initializeWithImmediateReward)
        P->SetInitializeWithImmediateReward(true);
    P->SetIdentification("Perseus" + Perseus::BackupTypeToString(qavParams));
    P->SetResultsFilename(directories::MADPGetResultsFilename("POMDP",
                                                              *decpomdp,args));
    if(args.verbose >= 0)
        cout << "Sampling " << args.nrBeliefs << " beliefs"; cout.flush();

    BeliefSet B=P->SampleBeliefs(args);

    PS->SetBeliefSet(B);

    if(args.saveBeliefs && !args.dryrun)
    {
        stringstream beliefFilename;
        beliefFilename << resultsDir << "/" << P->GetIdentification()
                       << "Beliefs"
                       << args.nrBeliefs << "_" << horizon << "_"
                       << args.resetAfter;
        if(args.useQMDPforSamplingBeliefs)
            beliefFilename << "_" << "QMDPsamplingPolicy"
                           << args.QMDPexploreProb;
        else
            beliefFilename << "_" << "randomSamplingPolicy";

        AlphaVectorPlanning::ExportBeliefSet(B,beliefFilename.str());
        if(args.verbose >= 0)
            cout << "Saved beliefs to " << beliefFilename.str() << endl;
    }
    if(args.verbose >= 0)
        cout << "." << endl;

    if(args.savePOMDP && !args.dryrun)
    {
        stringstream POMDPfilename;
        POMDPfilename << resultsDir << "/" << decpomdp->GetUnixName();
        if(!args.infiniteHorizon)
            POMDPfilename << "_h" << horizon;
        POMDPfilename << ".POMDP";
        AlphaVectorPlanning::ExportPOMDPFile(POMDPfilename.str(),np);
    }

    if(args.saveIntermediateV && !args.dryrun)
        P->SetSaveIntermediateValueFunctions(true);
    if(args.saveTimings && !args.dryrun)
        P->SetSaveTimings(true);
    if(args.computeVectorForEachBelief)
        P->SetComputeVectorForEachBelief(true);
    if(args.dryrun)
        P->SetDryrun(true);
        
    P->Plan();

    if(args.verbose >= 0)
        P->PrintTimersSummary();
    }
    catch(E& e){ e.Print(); }

    return(0);
}
