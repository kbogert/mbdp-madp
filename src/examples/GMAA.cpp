/**\file GMAA.cpp
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
 * $Id: GMAA.cpp 3629 2009-08-26 12:16:19Z mtjspaan $
 */

#include <sys/times.h>
#include <iostream>
#include <fstream>
#include <float.h>

#include "GeneralizedMAAStarPlannerForDecPOMDPDiscrete.h"
#include "GMAA_MAAstar.h"
#include "GMAA_kGMAA.h"
#include "QBG.h"
#include "QPOMDP.h"
#include "QMDP.h"
#include "Timing.h"
#include "qheur.h"
#include "gmaatype.h"
#include "BGIP_SolverType.h"
#include "BGIP_SolverCreator_AM.h"
#include "BGIP_SolverCreator_BFS.h" 
#include "argumentHandlers.h"
#include "argumentUtils.h"

using namespace qheur;
using namespace GMAAtype;
using namespace BGIP_SolverType;
using namespace std;
using namespace ArgumentUtils;

#pragma comment(lib,"MADP_dll.lib") 

QFunctionJAOH* getQheuristic(GeneralizedMAAStarPlannerForDecPOMDPDiscrete *gmaa,
                             Qheur_t Qheur)
{
    QFunctionJAOH* q = 0;
    switch(Qheur)
    {
    case(eQMDP):
        q = new QMDP(*gmaa,false);
        break;
    case(eQPOMDP):
        q = new QPOMDP(*gmaa);
        break;
    case(eQBG):
        q = new QBG(*gmaa);
        break;
    case(eQMDPc):
        q = new QMDP(*gmaa,true);
        break;
    }

    return(q);
}

const char *argp_program_version = "GMAA";

// Program documentation
static char doc[] =
"GMAA - runs Generalized MAAStar planners \
\vFor more information please consult the MADP documentation.";

//NOTE: make sure that the below value (nrChildParsers) is correct!
const int nrChildParsers = 6;
const struct argp_child childVector[] = {
    ArgumentHandlers::problemFile_child,
    ArgumentHandlers::globalOptions_child,
    ArgumentHandlers::modelOptions_child,
    ArgumentHandlers::solutionMethodOptions_child,
    ArgumentHandlers::gmaa_child,
    ArgumentHandlers::qheur_child,
    { 0 }
};


#include "argumentHandlersPostChild.h"

int main(int argc, char **argv)
{
    ArgumentHandlers::Arguments args;
    argp_parse (&ArgumentHandlers::theArgpStruc, argc, argv, 0, 0, &args);

    GMAA_t GMAAtype=args.gmaa;
    BGIP_Solver_t bgst = args.bgsolver;
    Qheur_t Qheur=args.qheur;
    int horizon=args.horizon;
    int k=args.k;
    //int restarts=args.nrRestarts;
   
try 
{

    Timing Time;    
    Time.Start("Overall");
    Time.Start("PlanningUnit");

    srand(time(0));

    if(args.verbose >= 1)
        cout << "Instantiating the problem..."<<endl;
    DecPOMDPDiscreteInterface* decpomdp = GetDecPOMDPDiscreteInterfaceFromArgs(args);
    if(args.verbose >= 1)
        cout << "...done."<<endl;

    GeneralizedMAAStarPlannerForDecPOMDPDiscrete *gmaa=0;
    QFunctionJAOH *q;

    string filename="",timingsFilename="", jpolFilename="";
    ofstream of;
    ofstream of_jpol;

    PlanningUnitMADPDiscreteParameters params;
    params.SetComputeAll(true);
    params.SetComputeJointActionObservationHistories(false);
    params.SetComputeJointObservationHistories(false);
    params.SetComputeJointActionHistories(false);
    params.SetComputeJointBeliefs(false);
    if(args.sparse)
        params.SetUseSparseJointBeliefs(true);
    params.SetComputeIndividualActionObservationHistories(false);
    params.SetComputeIndividualActionHistories(false);
    params.SetComputeIndividualObservationHistories(false);


    if(args.verbose >= 1)
        cout << "Instantiating the planning unit..."<<endl;
    double V=-DBL_MAX;
    Time.Start("PlanningUnit");
    BGIP_SolverCreatorInterface<JointPolicyPureVector> * bgsc_p = NULL;

    switch(GMAAtype)
    {
    case MAAstar:
        // for MAAstar we don't use BGIP_SolverCreator:
        // we need to return *all* found policies
        break;
    case kGMAA:
    case FSPC:
        switch(bgst)
        {
        case BFS:
            bgsc_p = new BGIP_SolverCreator_BFS<JointPolicyPureVector>(args.verbose);
            break;
        case AM:
            bgsc_p = new BGIP_SolverCreator_AM<JointPolicyPureVector>(
                args.nrAMRestarts, args.verbose, k);
            break;
        default:
            throw E("BGIP_Solver is not handled");
            break;
        }
    }

    int verboseness = args.verbose;
    switch(GMAAtype)
    {
    case MAAstar:
        gmaa=new GMAA_MAAstar(params, horizon, decpomdp, verboseness );
        break;
    case kGMAA:
        gmaa=new GMAA_kGMAA(params, bgsc_p, horizon, decpomdp, k);
        break;
    case FSPC:
        gmaa=new GMAA_kGMAA(params, bgsc_p, horizon, decpomdp, 1);
        break;
    default:
        throw E("unrecognized GMAA type?!");
    }

    gmaa->SetVerbose(args.verbose);

    Time.Stop("PlanningUnit");

    if(args.verbose >= 0)
        cout << "GMAA Planner initialized" << endl;

    if(args.verbose >= 1)
        cout << "Computing the Q heuristic ("<<Qheur<<")..."<<endl;
    q=getQheuristic(gmaa,Qheur);
    Time.Start("ComputeQ");
    
    q->Compute();
    
    Time.Stop("ComputeQ");

    if(args.verbose >= 0)
        cout << "Q heuristic computed" << endl;

    gmaa->SetQHeuristic(q);
    for(int restartI = 0; restartI < args.nrRestarts; restartI++)
    {
        Time.Start("Plan");
        gmaa->Plan();
        V = gmaa->GetExpectedReward();
        Time.Stop("Plan");
        cout << "\nvalue="<< V << endl;
        JointPolicyDiscretePure* found_jpol =  gmaa->GetJointPolicyDiscretePure();
        if(args.verbose >= 1)
            cout << found_jpol->SoftPrint();
    }

    Time.Stop("Overall");

    if(args.verbose >= 0)
    {
        Time.PrintSummary();
        gmaa->PrintTimersSummary();
    }
    
    delete q;
    delete gmaa;
    delete decpomdp;
}
catch(E& e){ 
    e.Print(); 
    exit(-1); 
}
}
