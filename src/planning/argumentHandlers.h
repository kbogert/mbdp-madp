/**\file argumentHandlers.h
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
 * $Id: argumentHandlers.h 3635 2009-08-27 13:33:33Z mtjspaan $
 */

#ifndef  _ARGUMENTHANDLERS_H_
#define  _ARGUMENTHANDLERS_H_ 1

#include <iostream>
#include <stdlib.h>
#include <error.h>
#include <argp.h>
#include <vector>
#include "Globals.h"
#include "qheur.h"
#include "gmaatype.h"
#include "JESPtype.h"
#include "PerseusBackupType.h"
#include "BGBackupType.h"
#include "BGIP_SolverType.h"
#include "ProblemType.h" //problem enum.

/// \brief ArgumentHandlers contains functionality for parsing and
/// handling command-line arguments.
namespace ArgumentHandlers {

using namespace qheur;
using namespace GMAAtype;
using namespace JESPtype;
using namespace BGIP_SolverType;
using namespace ProblemType;

/// Arguments contains all defined parameters to be set on the command line. 
struct Arguments
{
    //General options (globopt)
    int verbose;    // < 0 means quiet, > 0 is verbose
    
    //The dec-pomdp file argument (dpf)
    const char * dpf; //the dpomdp file string
    //do we use a standard (i.e. .cpp) problem rather than parsing:
    Problem_t problem_type;
    size_t nrAgents;
    size_t nrHouses;
    size_t nrFLs;

    //output file options (outputFileOptions)
    int dryrun;
    char * description, * prefix;

    //model options (modelOptions)
    int sparse;
    int isTOI;
    double discount;

    //solution methods options (solutionMethodOptions)
    int horizon;
    int infiniteHorizon;

    //the jpolIndex input argument
    LIndex jpolIndex;

    // GMAA options
    GMAA_t gmaa; //the GMAA type
    BGIP_Solver_t bgsolver; //the BG solver type
    int nrRestarts; //the number of times that the GMAA algorithm is run
    int k;
    
    
    
    
    // JESP options
    JESP_t jesp;
    int JESPnrRestarts;
    // alternating maximization options
    int nrAMRestarts;

    // Perseus options
    int savePOMDP;
    int saveIntermediateV;
    int minimumNrIterations;
    int uniqueBeliefs;
    int initializeWithImmediateReward;
    int initializeWithZero;
	int saveTimings;

    // Perseus belief set sampling options
    int nrBeliefs;
    int saveBeliefs;
    int resetAfter;
    int useQMDPforSamplingBeliefs;
    double QMDPexploreProb;

    // Perseus backup options
    PerseusBackupType backup;
    BGBackupType bgBackup;
    double waitPenalty;
    double weight;
    int commModel;
    int computeVectorForEachBelief;
    
    // Qheur options
    Qheur_t qheur;

    // Simulation options
    int nrRuns;
    int randomSeed;


    
    
    
    
    
    
    // CE (cross-entropy) options 
    size_t nrCERestarts;
    size_t nrCEIterations;
    size_t nrCESamples;
    size_t nrCESamplesForUpdate;
    bool CE_use_hard_threshold; //(gamma in CE papers)
    double CE_alpha; //the learning rate
    size_t nrCEEvalutionRuns; // number of policy evaluation runs

    //default values by constructor:
    Arguments()
    {
        // general
        verbose = 0;
        // problem file
        dpf = 0;
        problem_type = PARSE;
        nrAgents = 2;
        nrHouses = 3;
        nrFLs = 3;
        // output
        dryrun = 0;
        description = NULL;
        prefix = NULL;

        // model
        sparse = 0;
        isTOI = 0;
        discount = -1;

        // solution method
        horizon = 2;
        infiniteHorizon = 0;

        // jpol index
        jpolIndex = 0;

        // GMAA
        gmaa = MAAstar;
        bgsolver = BFS;
        nrRestarts = 1;
        nrAMRestarts = 10;
        k = 1;

        
        
        //JESP options
        jesp = JESPDP;
        JESPnrRestarts = 10;

        // Perseus
        savePOMDP = 0;
        saveIntermediateV = 0;
        minimumNrIterations = 0;
        initializeWithImmediateReward = 0;
        initializeWithZero = 0;
        saveTimings = 0;

        // Perseus belief set sampling options
        nrBeliefs = 10;
        saveBeliefs = 0;
        resetAfter = 0;
        uniqueBeliefs = 0;
        useQMDPforSamplingBeliefs = 0;
        QMDPexploreProb = 0.1;

        // PerseusBackup
        backup = POMDP;
        bgBackup = BGIP_SOLVER_EXHAUSTIVE;
        waitPenalty = -1;
        weight = -1;
        commModel = -1;
        computeVectorForEachBelief = 0;

        // Qheur options
        qheur = eQMDP;
        // Simulation options
        nrRuns = 1000;
        randomSeed = 42;
        // CE (cross-entropy) options 
        nrCERestarts = 10;
        nrCEIterations = 50;
        nrCESamples = 50;
        nrCESamplesForUpdate = 10;
        CE_use_hard_threshold = 1; //(gamma in CE papers)
        CE_alpha = 0.3; //the learning rate
        nrCEEvalutionRuns = 0; // number of policy evaluation runs. 0 = exact evaluation

    }
        
};


extern const char *argp_program_bug_address;

error_t problemFile_parse_argument (int key, char *arg,
                                    struct argp_state *state);
extern const struct argp_child problemFile_child;

error_t globalOptions_parse_argument (int key, char *arg,
                                      struct argp_state *state);
extern const struct argp_child globalOptions_child;

error_t modelOptions_parse_argument (int key, char *arg,
                                     struct argp_state *state);
extern const struct argp_child modelOptions_child;

error_t solutionMethodOptions_parse_argument (int key, char *arg,
                                              struct argp_state *state);
extern const struct argp_child solutionMethodOptions_child;

error_t jpolIndex_parse_argument (int key, char *arg, 
                                  struct argp_state *state);
extern const struct argp_child jpolIndex_child;

error_t gmaa_parse_argument (int key, char *arg, 
                             struct argp_state *state);
extern const struct argp_child gmaa_child;

error_t perseus_parse_argument (int key, char *arg, 
                             struct argp_state *state);
extern const struct argp_child perseus_child;

error_t perseusbackup_parse_argument (int key, char *arg, 
                                      struct argp_state *state);
extern const struct argp_child perseusbackup_child;

error_t perseusbelief_parse_argument (int key, char *arg, 
                                      struct argp_state *state);
extern const struct argp_child perseusbelief_child;

error_t qheur_parse_argument (int key, char *arg, 
                              struct argp_state *state);
extern const struct argp_child qheur_child;


error_t simulation_parse_argument (int key, char *arg, 
                                   struct argp_state *state);
extern const struct argp_child simulation_child;

error_t CE_parse_argument (int key, char *arg, 
                             struct argp_state *state);
extern const struct argp_child CE_child;

error_t JESP_parse_argument (int key, char *arg, 
                             struct argp_state *state);
extern const struct argp_child JESP_child;


} //namespace

#endif /* !_ARGUMENTHANDLERS_H_*/
