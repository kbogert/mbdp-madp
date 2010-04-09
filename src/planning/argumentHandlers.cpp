/**\file argumentHandlers.cpp
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
 * $Id: argumentHandlers.cpp 4012 2010-03-11 15:29:07Z mtjspaan $
 */

#include "argumentHandlers.h"
#include <string.h>

using namespace ArgumentHandlers;

namespace ArgumentHandlers {

const char *argp_program_bug_address = 
"<faolieho@science.uva.nl>, <mtjspaan@isr.ist.utl.pt>";

// a group for input arguments
static const int GID_INPUTARG=1;


//Dec-POMDP File options (problemFile)
static const int GID_PROBLEMFILE=GID_INPUTARG;
const char *problemFile_argp_version = ".dpomdp file argument parser 0.1";
static const char *problemFile_args_doc = "PROBLEM";
static const char *problemFile_doc = 
"This is the documentation for the .dpomdp file argument parser\
This parser should be included as a child argp parser in the \
main argp parser of your application.(and this message will\
not be shown)\
\vPROBLEM is either \n\
a) one of the following standard problems: DT, FF\n\
or \n\
b) a Dec-POMDP problem filename (.dpomdp or .toi-dpomdp). \
If it includes an extension, PROBLEM will be attempted to be loaded as is, \
otherwise the <PROBLEMSDIR> will be searched. \
I.e., ~/.madp/problems/PROBLEM.{toi-}dpomdp will be loaded.\n\
Some of the standard problems take options.";

static const int OPT_NRAGENTS=1; //#agents
static const int OPT_NRHOUSES=2; //#houses
static const int OPT_NRFLS=3;    //#FLs
static struct argp_option problemFile_options[] = {
{"agents",      OPT_NRAGENTS,   "NRAGENTS",  0, "FireFighting: the number of agents (2)" },
{"houses",      OPT_NRHOUSES,   "NRHOUSES",  0, "FireFighting: the number of houses (3)" },
{"firelevels",  OPT_NRFLS,      "NRFLS",  0, "FireFighting: the number of firelevels (3)"},
{ 0 }
};
error_t
problemFile_parse_argument (int key, char *arg, struct argp_state *state)
{
    static bool got_problemFile = 0;
    //if we already got the dec-pomdp file return
    if(got_problemFile)
        return ARGP_ERR_UNKNOWN;
    /* Get the input argument from argp_parse, which we
      know is a pointer to our arguments structure. */
    struct Arguments *theArgumentsStruc = (struct Arguments*) state->input;

    switch (key)
    {
        case OPT_NRAGENTS:
            theArgumentsStruc->nrAgents = atoi(arg);
            break;
        case OPT_NRHOUSES:
            theArgumentsStruc->nrHouses = atoi(arg);
            break;
        case OPT_NRFLS:
            theArgumentsStruc->nrFLs = atoi(arg);
            break;
        case ARGP_KEY_NO_ARGS:
            argp_usage (state);
            break;
        case ARGP_KEY_ARG:
        {
            theArgumentsStruc->dpf = std::string("").c_str(); 
            if(strcmp(arg, "DT") == 0)
                theArgumentsStruc->problem_type = ProblemType::DT;
            else if(strcmp(arg, "FF") == 0)
                theArgumentsStruc->problem_type = ProblemType::FF;
            else
                theArgumentsStruc->dpf = arg; 
                got_problemFile = 1; 
            break;
        }
        default:
            return ARGP_ERR_UNKNOWN;
     }
    return 0;
}
static struct argp problemFile_argp = { problemFile_options, problemFile_parse_argument, problemFile_args_doc, problemFile_doc };
extern const struct argp_child problemFile_child = {&problemFile_argp, 0, "Problem specification options", GID_PROBLEMFILE};



//global options (globalOptions)
static const int GID_GLOBALOPTIONS=8;
const char *globalOptions_argp_version = "global options parser 0.1";
static const char *globalOptions_args_doc = 0;
static const char *globalOptions_doc = 
"This is the documentation for the global options parser\
This parser should be included as a child argp parser in the \
main argp parser of your application. (and this message will\
not be shown)"; 
//\v";
static struct argp_option globalOptions_options[] = {
{"verbose",  'v', 0,       0, "Produce verbose output. Specifying this option multiple times increases verbosity." },
{"quiet",    'q', 0,       0, "Don't produce any output" },
{"silent",   's', 0,       OPTION_ALIAS },
{ 0 }
};
error_t
globalOptions_parse_argument (int key, char *arg, struct argp_state *state)
{
    /* Get the input argument from argp_parse, which we
      know is a pointer to our arguments structure. */
    struct Arguments *theArgumentsStruc = (struct Arguments*) state->input;

    switch (key)
    {
        case 'q': case 's':
            theArgumentsStruc->verbose--;
            break;
        case 'v':
            theArgumentsStruc->verbose++;
            break;
        default:
            return ARGP_ERR_UNKNOWN;
     }
    return 0;
}
static struct argp globalOptions_argp = { globalOptions_options, globalOptions_parse_argument, globalOptions_args_doc, globalOptions_doc };
const struct argp_child globalOptions_child = {&globalOptions_argp, 0, "General options", GID_GLOBALOPTIONS};



//model options modelOptions
static const int GID_MODELOPTIONS=3;
const char *modelOptions_argp_version = "Model options parser 0.1";
static const char *modelOptions_args_doc = 0;
static const char *modelOptions_doc = 
"This is the documentation for the model options parser\
This parser should be included as a child argp parser in the \
main argp parser of your application. (and this message will\
not be shown)\
\v";

static const int OPT_TOI=1;
static struct argp_option modelOptions_options[] = {
{"sparse",              's',0,  0, "Use sparse transition and observation models" },
{"toi",         OPT_TOI,    0,  0, "Indicate that PROBLEM is a transition observation independent Dec-POMDP" },
{"discount",  'g', "GAMMA",     0, "Set the problem's discount parameter (overriding its default)" },
{ 0 }
};
error_t
modelOptions_parse_argument (int key, char *arg, struct argp_state *state)
{
    /* Get the input argument from argp_parse, which we
      know is a pointer to our arguments structure. */
    struct Arguments *theArgumentsStruc = (struct Arguments*) state->input;

    switch (key)
    {
        case 's': 
            theArgumentsStruc->sparse = 1;
            break;
        case OPT_TOI:
            theArgumentsStruc->isTOI=1;
            break;
        case 'g':
            theArgumentsStruc->discount = strtod(arg,0);
            break;
        default:
            return ARGP_ERR_UNKNOWN;
     }
    return 0;
}
static struct argp modelOptions_argp = { modelOptions_options, modelOptions_parse_argument, modelOptions_args_doc, modelOptions_doc };
const struct argp_child modelOptions_child = {&modelOptions_argp, 0, "Model options", GID_MODELOPTIONS};


//Solution method options (solutionMethodOptions)
const char *solutionMethodOptions_argp_version = "Solution method options parser 0.1";
static const char *solutionMethodOptions_args_doc = 0;
static const char *solutionMethodOptions_doc = 
"This is the documentation for the solution method options parser\
This parser should be included as a child argp parser in the \
main argp parser of your application. (and this message will\
not be shown)"; 
//\v";

//we define a special solution method group ID, so it is easier to group other
//parsers with this one
static const int GID_SM=2;
static const int OPT_INF=1;
static struct argp_option solutionMethodOptions_options[] = {
{"horizon",'h',"HOR", 0, "Specifies the horizon to be considered" },
{"inf", OPT_INF , 0,       0, "Indicate that horizon is infinite" },
{ 0 }
};
error_t
solutionMethodOptions_parse_argument (int key, char *arg, struct argp_state *state)
{
    /* Get the input argument from argp_parse, which we
      know is a pointer to our arguments structure. */
    struct Arguments *theArgumentsStruc = (struct Arguments*) state->input;

    switch (key)
    {
        case 'h': 
            theArgumentsStruc->horizon = atoi(arg);
            break;
        case OPT_INF:
            theArgumentsStruc->infiniteHorizon=1;
            break;
        default:
            return ARGP_ERR_UNKNOWN;
     }
    return 0;
}
static struct argp solutionMethodOptions_argp = { solutionMethodOptions_options, solutionMethodOptions_parse_argument, solutionMethodOptions_args_doc, solutionMethodOptions_doc };
const struct argp_child solutionMethodOptions_child = {&solutionMethodOptions_argp, 0, "Solution method options", GID_SM };


/* stolen from dietlibc - http://www.fefe.de/dietlibc/ , thanks for nothing microsoft. what year is it now? How long ago was C99? stupid fucks */

#include <ctype.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

unsigned long long int strtoull(const char *ptr, char **endptr, int base)
{
  int neg = 0, overflow = 0;
  long long int v=0;
  const char* orig;
  const char* nptr=ptr;

  while(isspace(*nptr)) ++nptr;

  if (*nptr == '-') { neg=1; nptr++; }
  else if (*nptr == '+') ++nptr;
  orig=nptr;
  if (base==16 && nptr[0]=='0') goto skip0x;
  if (base) {
    register unsigned int b=base-2;
    if (b>34) { errno=EINVAL; return 0; }
  } else {
    if (*nptr=='0') {
      base=8;
skip0x:
      if (((*(nptr+1)=='x')||(*(nptr+1)=='X')) && isxdigit(nptr[2])) {
	nptr+=2;
	base=16;
      }
    } else
      base=10;
  }
  while(*nptr) {
    register unsigned char c=*nptr;
    c=(c>='a'?c-'a'+10:c>='A'?c-'A'+10:c<='9'?c-'0':0xff);
    if (c>=base) break;	/* out of base */
    {
      register unsigned long x=(v&0xff)*base+c;
      register unsigned long long w=(v>>8)*base+(x>>8);
      if (w>(ULLONG_MAX>>8)) overflow=1;
      v=(w<<8)+(x&0xff);
    }
    ++nptr;
  }
  if (nptr==orig) {		/* no conversion done */
    nptr=ptr;
    errno=EINVAL;
    v=0;
  }
  if (endptr) *endptr=(char *)nptr;
  if (overflow) {
    errno=ERANGE;
    return ULLONG_MAX;
  }
  return (neg?-v:v);
}


//joint policy argument parser (jpolIndex)
static const int GID_JPOLINDEX=GID_INPUTARG;
const char *jpolIndex_argp_version = "joint policy index argument parser 0.1";
static const char *jpolIndex_args_doc = "JPOL-INDEX";
static const char *jpolIndex_doc = 
"This is the documentation for the joint policy index argument parser\
This parser should be included as a child argp parser in the \
main argp parser of your application.(and this message will\
not be shown)\
\vJPOL-INDEX is a (long long) integer that is the index of the joint \
policy to be considered.";
static struct argp_option jpolIndex_options[] = {
//{"none",  'v', 0,       0, "no options" },
{ 0 }
};
error_t
jpolIndex_parse_argument (int key, char *arg, struct argp_state *state)
{
    static bool got_jpolIndex = 0;
    //if we already got the dec-pomdp file return
    if(got_jpolIndex)
        return ARGP_ERR_UNKNOWN;
    /* Get the input argument from argp_parse, which we
      know is a pointer to our arguments structure. */
    struct Arguments *theArgumentsStruc = (struct Arguments*) state->input;

    switch (key)
    {
        case ARGP_KEY_NO_ARGS:
            argp_usage (state);
            break;
        case ARGP_KEY_ARG:
        {
            char *left;
            theArgumentsStruc->jpolIndex = strtoull(arg,&left,10);
            if(*left != '\0')
            {
                std::stringstream ss;
                ss << "Could not entirely parse the JPOL-INDEX: arg='"
                   << arg <<"', left='" << left
                   << "', found jpol index='"<< theArgumentsStruc->jpolIndex
                   << "'";
                throw(E(ss));
            }
            got_jpolIndex = 1;
            break;
        }
        default:
            return ARGP_ERR_UNKNOWN;
     }
    return 0;
}
static struct argp jpolIndex_argp = { jpolIndex_options, jpolIndex_parse_argument, jpolIndex_args_doc, jpolIndex_doc };
const struct argp_child jpolIndex_child = {&jpolIndex_argp, 0, 0, GID_PROBLEMFILE};


//GMAA options (gmaa)
static const int GID_GMAA=GID_SM;
const char *gmaa_argp_version = "GMAA options parser 0.1";
static const char *gmaa_args_doc = 0;
static const char *gmaa_doc = 
"This is the documentation for the options options parser\
This parser should be included as a child argp parser in the \
main argp parser of your application. (and this message will\
not be shown)\
\v\
GMAA parameter:\n\
0 or MAAstar -> use GMAA_MAAstar\n\
1 or kGMAA   -> use GMAA_kGMAA (uses K)\n\
2 or FSPC    -> use Forward Sweep Policy Computation (kGMAA with k=1)\n\
\n\
BGIP_SOLVERTYPE parameter:\n\
0 or BFS\t-\tbrute force search\n\
1 or AM \t-\tAlternating Maximization\n";

static const int AM_RESTARTS=1;
static struct argp_option gmaa_options[] = {
{"GMAA",    'G', "GMAA", 0, "Select which GMAA variation to use" },
{"BGIP_Solver", 'B', "BGIP_SOLVERTYPE", 0, "Select which Bayesian game solver to use"},
{"k",   'k', "K", 0, "Set k in k-GMAA" },
{"restarts", 'r', "RESTARTS", 0, "Set the number of restarts"},
{"AM-restarts", AM_RESTARTS, "AM_RESTARTS", 0, "nr restarts for solving BGs withFSPC_AM"},
{ 0 }
};
error_t
gmaa_parse_argument (int key, char *arg, struct argp_state *state)
{
    /* Get the input argument from argp_parse, which we
      know is a pointer to our arguments structure. */
    struct Arguments *theArgumentsStruc = (struct Arguments*) state->input;

    switch (key)
    {

    case 'G':
        if(strlen(arg)==1)
            theArgumentsStruc->gmaa=static_cast<GMAA_t>(atoi(arg));
        else if(strcmp(arg,"MAAstar")==0)
            theArgumentsStruc->gmaa=MAAstar;
        else if(strcmp(arg,"FSPC")==0)
            theArgumentsStruc->gmaa=FSPC;
        else if(strcmp(arg,"kGMAA")==0)
            theArgumentsStruc->gmaa=kGMAA;
        else
            return ARGP_ERR_UNKNOWN;
        break;
    case 'B':
        if(strlen(arg)==1){
            int methodI=atoi(arg);
            if (methodI < 0 || methodI > (int)NUMBER_OF_BGIP_SOLVER_TYPES)
                throw E("Wrong BGIP_SolverType number!");
            theArgumentsStruc->bgsolver =
                static_cast<BGIP_SolverType::BGIP_Solver_t>(methodI);
        }
        else if(strcmp(arg,"BFS")==0)
            theArgumentsStruc->bgsolver = BGIP_SolverType::BFS;
        else if(strcmp(arg,"AM")==0)
            theArgumentsStruc->bgsolver = BGIP_SolverType::AM;
        else
            return ARGP_ERR_UNKNOWN;
        break;
        
    case 'k':
        theArgumentsStruc->k = atoi(arg);
        break;
    case 'r':
        theArgumentsStruc->nrRestarts = atoi(arg);
        break;
    case AM_RESTARTS:
        theArgumentsStruc->nrAMRestarts = atoi(arg);
        break;
    default:
        return ARGP_ERR_UNKNOWN;
    }
    return 0;
}
static struct argp gmaa_argp = { gmaa_options, gmaa_parse_argument,
                                 gmaa_args_doc, gmaa_doc
};
const struct argp_child gmaa_child = {&gmaa_argp, 0, "GMAA options", GID_GMAA};


//Perseus options (perseus)
static const int GID_PERSEUS=GID_SM;
const char *perseus_argp_version = "Perseus options parser 0.1";
static const char *perseus_args_doc = 0;
static const char *perseus_doc = 
"This is the documentation for the options options parser\
This parser should be included as a child argp parser in the \
main argp parser of your application. (and this message will\
not be shown)";

static struct argp_option perseus_options[] = {
{"savePOMDP",  'P', 0, 0, "Save the POMDP to disk" },
{"saveIntermediateV",  'V', 0, 0, "Save intermediate value functions to disk" },
{"saveTimings", 't', 0, 0, "Save timing results to disk"},
{"minNrIterations",   'i', "ITERS", 0, "Make Perseus run at least ITERS iterations" },
{"initReward",  'I', 0, 0, "Initialize the value function with the immediate reward."},
{"initZero",  'z', 0, 0, "Initialize the value function with 0."},
{ 0 }
};
error_t
perseus_parse_argument (int key, char *arg, struct argp_state *state)
{
    /* Get the input argument from argp_parse, which we
      know is a pointer to our arguments structure. */
    struct Arguments *theArgumentsStruc = (struct Arguments*) state->input;

    switch (key)
    {
    case 'n':
        theArgumentsStruc->nrBeliefs = atoi(arg);
        break;
    case 'P':
        theArgumentsStruc->savePOMDP=1;
        break;
    case 'V':
        theArgumentsStruc->saveIntermediateV=1;
        break;
    case 't':
        theArgumentsStruc->saveTimings = 1;
        break;
    case 'i':
        theArgumentsStruc->minimumNrIterations = atoi(arg);
        break;
    case 'I':
        theArgumentsStruc->initializeWithImmediateReward=1;
        break;
    case 'z':
        theArgumentsStruc->initializeWithZero=1;
        break;
    default:
        return ARGP_ERR_UNKNOWN;
    }
    return 0;
}
static struct argp perseus_argp = { perseus_options, perseus_parse_argument,
                                    perseus_args_doc, perseus_doc };
const struct argp_child perseus_child = {&perseus_argp, 0,
                                         "Perseus general options", GID_PERSEUS};

//Perseus belief set sampling options (perseusbelief)
static const int GID_PERSEUSBELIEF=GID_SM;
const char *perseusbelief_argp_version = "Perseus Belief options parser 0.1";
static const char *perseusbelief_args_doc = 0;
static const char *perseusbelief_doc = 
"This is the documentation for the options options parser\
This parser should be included as a child argp parser in the \
main argp parser of your application. (and this message will\
not be shown)";

static struct argp_option perseusbelief_options[] = {
{"beliefs",'n', "BELIEFS", 0, "Set the belief set size" },
{"saveBeliefs",  'B', 0, 0, "Save beliefs to disk" },
{"beliefSamplingHorizon",   'H', "HORIZON", 0, "Introduce an artificial horizon when sampling the beliefs (useful in infinite-horizon case)" },
{"uniqueBeliefs",  'u', 0, 0, "Sample unique beliefs (no duplicates)" },
{"useQMDP",  'Q', 0, 0, "Follow the QMDP policy while sampling beliefs instead of acting uniformly at random."},
{"QMDPexploreProb",  'x', "PROB", 0, "Probability with which to take a random action when using QMDP for belief sampling."},
{ 0 }
};
error_t
perseusbelief_parse_argument (int key, char *arg, struct argp_state *state)
{
    /* Get the input argument from argp_parse, which we
      know is a pointer to our arguments structure. */
    struct Arguments *theArgumentsStruc = (struct Arguments*) state->input;

    switch (key)
    {
    case 'n':
        theArgumentsStruc->nrBeliefs = atoi(arg);
        break;
    case 'B':
        theArgumentsStruc->saveBeliefs=1;
        break;
    case 'H':
        theArgumentsStruc->resetAfter = atoi(arg);
        break;
    case 'u':
        theArgumentsStruc->uniqueBeliefs=1;
        break;
    case 'Q':
        theArgumentsStruc->useQMDPforSamplingBeliefs=1;
        break;
    case 'x':
        theArgumentsStruc->QMDPexploreProb = strtod(arg,0);
        break;
    default:
        return ARGP_ERR_UNKNOWN;
    }
    return 0;
}
static struct argp perseusbelief_argp = { perseusbelief_options, perseusbelief_parse_argument,
                                    perseusbelief_args_doc, perseusbelief_doc };
const struct argp_child perseusbelief_child = {&perseusbelief_argp, 0,
                                         "Perseus belief set sampling options", GID_PERSEUSBELIEF};

//Perseus Backup options (perseusbackup)
static const int GID_PERSEUSBACKUP=GID_SM;
const char *perseusbackup_argp_version = "Perseus Backup options parser 0.1";
static const char *perseusbackup_args_doc = 0;
static const char *perseusbackup_doc = 
"This is the documentation for the options options parser\
This parser should be included as a child argp parser in the \
main argp parser of your application. (and this message will\
not be shown)\
\vBACKUP parameter:\n\
0  or POMDP   -> use PerseusPOMDP (default)\n\
1  or BG      -> use PerseusBG (BG solver can be specified by BGBACKUP)\n\
\n\
BGBACKUP parameter (details in AlphaVectorBG.{h,cpp}):\n\
0 or EXH_MAX       -> use EXHAUSTIVE_ONLYKEEPMAX backup in PerseusBG\n\
1 or EXH_ALL       -> use EXHAUSTIVE_STOREALL backup in PerseusBG\n\
2 or BGS_EXH       -> use BGIP_SOLVER_EXHAUSTIVE backup in PerseusBG (default)\n\
3 or BGS_ALTMAX    -> use BGIP_SOLVER_ALTERNATINGMAXIMIZATION backup in PerseusBG\n\
4 or BGS_ALTMAX100 -> use BGIP_SOLVER_ALTERNATINGMAXIMIZATION_100STARTS backup\n\
";

static struct argp_option perseusbackup_options[] = {
{"backup",  'b', "BACKUP", 0, "Select which backup to use, see below" },
{"vectorEachBelief",   'e', 0, 0, "If specified, don't sample from belief set, but compute vector for each belief" },
{"BGbackup",  'y', "BGBACKUP", 0, "Select which BG backup to use for PerseusBG" },
{"waitPenalty",   'w', "PENALTY", 0, "Set the wait penalty for PerseusImplicitWaiting" },
{"weight",   'W', "WEIGHT", 0, "Set the weight for PerseusWeighted{NS}" },
{"commModel",   'c', "COMM", 0, "Select the communication model for PerseusWeighted" },
{ 0 }
};
error_t
perseusbackup_parse_argument (int key, char *arg, struct argp_state *state)
{
    /* Get the input argument from argp_parse, which we
      know is a pointer to our arguments structure. */
    struct Arguments *theArgumentsStruc = (struct Arguments*) state->input;

    switch (key)
    {
    case 'y':
        if(strlen(arg)==1)
            theArgumentsStruc->bgBackup=static_cast<BGBackupType>(atoi(arg));
        else if(strcmp(arg,"EXH_MAX")==0)
            theArgumentsStruc->bgBackup=EXHAUSTIVE_ONLYKEEPMAX;
        else if(strcmp(arg,"EXH_ALL")==0)
            theArgumentsStruc->bgBackup=EXHAUSTIVE_STOREALL;
        else if(strcmp(arg,"BGS_EXH")==0)
            theArgumentsStruc->bgBackup=BGIP_SOLVER_EXHAUSTIVE;
        else if(strcmp(arg,"BGS_ALTMAX")==0)
            theArgumentsStruc->bgBackup=BGIP_SOLVER_ALTERNATINGMAXIMIZATION;
        else if(strcmp(arg,"BGS_ALTMAX100")==0)
            theArgumentsStruc->bgBackup=BGIP_SOLVER_ALTERNATINGMAXIMIZATION_100STARTS;
        else
            return ARGP_ERR_UNKNOWN;
        break;
    case 'b':
        if(strlen(arg)==1)
            theArgumentsStruc->backup=static_cast<PerseusBackupType>(atoi(arg));
        else if(strcmp(arg,"POMDP")==0)
            theArgumentsStruc->backup=POMDP;
        else if(strcmp(arg,"BG")==0)
            theArgumentsStruc->backup=BG;
        else
            return ARGP_ERR_UNKNOWN;
        break;
    case 'w':
        theArgumentsStruc->waitPenalty = strtod(arg,0);
        break;
    case 'W':
        theArgumentsStruc->weight = strtod(arg,0);
        break;
    case 'c':
        theArgumentsStruc->commModel = atoi(arg);
        break;
    case 'e':
        theArgumentsStruc->computeVectorForEachBelief = 1;
        break;
    default:
        return ARGP_ERR_UNKNOWN;
    }
    return 0;
}
static struct argp perseusbackup_argp = { perseusbackup_options,
                                          perseusbackup_parse_argument,
                                          perseusbackup_args_doc,
                                          perseusbackup_doc };
const struct argp_child perseusbackup_child = {&perseusbackup_argp, 0,
                                               "Perseus backup options",
                                               GID_PERSEUSBACKUP};

//Qheur options (qheur)
static const int GID_QHEUR=GID_SM;
const char *qheur_argp_version = "QHEUR options parser 0.1";
static const char *qheur_args_doc = 0;
static const char *qheur_doc = 
"This is the documentation for the options options parser\
This parser should be included as a child argp parser in the \
main argp parser of your application. (and this message will\
not be shown)\vQHEUR parameter:\n\
0 or QMDP (defined on joint beliefs)\n\
1 or QPOMDP\n\
2 or QBG\n\
3 or QMDPc (cached for each joint AO history)";

static struct argp_option qheur_options[] = {
{"Qheuristic",  'Q', "QHEUR", 0, "Select which Q-heuristic to use" },
{ 0 }
};
error_t
qheur_parse_argument (int key, char *arg, struct argp_state *state)
{
    /* Get the input argument from argp_parse, which we
      know is a pointer to our arguments structure. */
    struct Arguments* theArgumentsStruc = (struct Arguments*) state->input;

    switch (key)
    {
    case 'Q':
        if(strlen(arg)==1)
            theArgumentsStruc->qheur=static_cast<Qheur_t>(atoi(arg));
        else if(strcmp(arg,"QMDP")==0)
            theArgumentsStruc->qheur=eQMDP;
        else if(strcmp(arg,"QPOMDP")==0)
            theArgumentsStruc->qheur=eQPOMDP;
        else if(strcmp(arg,"QBG")==0)
            theArgumentsStruc->qheur=eQBG;
        else if(strcmp(arg,"QMDPc")==0)
            theArgumentsStruc->qheur=eQMDPc;
        else
            return ARGP_ERR_UNKNOWN;
        break;
    default:
        return ARGP_ERR_UNKNOWN;
    }
    return 0;
}
static struct argp qheur_argp = { qheur_options, qheur_parse_argument,
                                  qheur_args_doc, qheur_doc };
const struct argp_child qheur_child = {&qheur_argp, 0, "Q-heuristic options", 
                                       GID_QHEUR};


//Simulation options (simulation)
static const int GID_SIMULATION=7;
const char *simulation_argp_version = "Simulation options parser 0.1";
static const char *simulation_args_doc = 0;
static const char *simulation_doc = 
"This is the documentation for the options options parser\
This parser should be included as a child argp parser in the \
main argp parser of your application. (and this message will\
not be shown)"; 
//\v";
static struct argp_option simulation_options[] = {
{"runs",  'r', "RUNS", 0, "Set the number of episodes to simulate" },
{"seed",  'S', "SEED", 0, "Set the random seed" },
{ 0 }
};
error_t
simulation_parse_argument (int key, char *arg, struct argp_state *state)
{
    /* Get the input argument from argp_parse, which we
      know is a pointer to our arguments structure. */
    struct Arguments *theArgumentsStruc = (struct Arguments*) state->input;

    switch (key)
    {
    case 'r':
        theArgumentsStruc->nrRuns=atoi(arg);
        break;
    case 'S':
        theArgumentsStruc->randomSeed=atoi(arg);
        break;
    default:
        return ARGP_ERR_UNKNOWN;
    }
    return 0;
}
static struct argp simulation_argp = { simulation_options,
                                       simulation_parse_argument,
                                       simulation_args_doc, simulation_doc };
const struct argp_child simulation_child = {&simulation_argp, 0,
                                            "Simulation options", 
                                            GID_SIMULATION};

//CE options (CE)
static const int GID_CE=GID_SM;
const char *CE_argp_version = "CE options parser 0.1";
static const char *CE_args_doc = 0;
static const char *CE_doc = 
"This is the documentation for the CE (cross entropy) options parser\
This parser should be included as a child argp parser in the \
main argp parser of your application. (and this message will\
not be shown)\
\v\
Options for using CE (the cross-entropy method) for optimization include \
the number of restarts (runs), the number of iteration for each runs, \
how much samples are drawn each iteration, and how much of those are \
used to update the probability distribution.";

static const int CE_RESTARTS = 1;
static const int CE_EVALUATION_RUNS = 2;
static struct argp_option CE_options[] = {
{"CE-restarts", CE_RESTARTS, "CERESTARTS", 0, "Set the number of CE restarts (runs)"},
{"CE-eval-runs", CE_EVALUATION_RUNS, "CEEVALRUNS", 0, "Set the number of policy evaluation runs. More runs will result in more accurate evaluation. (set 0 for exact evaluation)."},
{"iterations", 'i', "ITERATIONS", 0, "Set the number of iterations per run"},
{"samples", 'n', "SAMPLES", 0, "Set the number of samples per iteration"},
{"updateSamples", 'u', "UPDATESAMPPLES", 0, "Set the number of samples used to update the prob. distribution."},
{"not_strictly_improving", 'N', 0, 0, "Do not use a hard threshold: do not require that newly sampled policies are strictly better then before. (this corresponds to the gamma in the CE papers)"},
{"alpha", 'a', "ALPHA", 0, "The learning rate"},
{ 0 }
};
error_t
CE_parse_argument (int key, char *arg, struct argp_state *state)
{
    /* Get the input argument from argp_parse, which we
      know is a pointer to our arguments structure. */
    struct Arguments *theArgumentsStruc = (struct Arguments*) state->input;

    switch (key)
    {
    case CE_EVALUATION_RUNS:
        theArgumentsStruc->nrCEEvalutionRuns = atoi(arg);
        break;
    case CE_RESTARTS:
        theArgumentsStruc->nrCERestarts = atoi(arg);
        break;
    case 'i':
        theArgumentsStruc->nrCEIterations =  atoi(arg);
        break;
    case 'n':
        theArgumentsStruc->nrCESamples =  atoi(arg);
        break;
    case 'u':
        theArgumentsStruc->nrCESamplesForUpdate =  atoi(arg);
        break;
    case 'N':
        theArgumentsStruc->CE_use_hard_threshold = 0;
        break;
    case 'a':
        theArgumentsStruc->CE_alpha =  atof(arg);
        break;
    default:
        return ARGP_ERR_UNKNOWN;
    }
    return 0;
}
static struct argp CE_argp = { CE_options, CE_parse_argument,
                                 CE_args_doc, CE_doc };
const struct argp_child CE_child = {&CE_argp, 0, "CE options", GID_CE};


//JESP options (JESP)
static const int GID_JESP=GID_SM;
const char *JESP_argp_version = "JESP options parser 0.1";
static const char *JESP_args_doc = 0;
static const char *JESP_doc = 
"This is the documentation for the JESP (Joint Equilibrium-based \
Search for Policies) options parser.\
This parser should be included as a child argp parser in the \
main argp parser of your application. (and this message will\
not be shown)\
\v\
Options for using  JESP (Joint Equilibrium-based \
Search for Policies) include: \
the type of JESP (exhaustive or Dynamic Programming), which can be:\n\
0 or Exh - exhaustive JESP\n\
1 or DP  - Dynamic programming\n\n\
and the number of restarts (runs).";

static const int JESP_RESTARTS = 1;
static const int JESP_TYPE = 2;
static struct argp_option JESP_options[] = {
{"JESP-restarts", JESP_RESTARTS, "JESPRESTARTS", 0, "Set the number of JESP restarts (runs)"},
{"JESP-type", JESP_TYPE, "JESPTYPE", 0, "Set the type of JESP (Exh or [DP])"},
{ 0 }
};
error_t
JESP_parse_argument (int key, char *arg, struct argp_state *state)
{
    /* Get the input argument from argp_parse, which we
      know is a pointer to our arguments structure. */
    struct Arguments *theArgumentsStruc = (struct Arguments*) state->input;

    switch (key)
    {
    case JESP_RESTARTS:
        theArgumentsStruc->JESPnrRestarts = atoi(arg);
        break;
    case JESP_TYPE:
        if(strlen(arg)==1)
            theArgumentsStruc->jesp=static_cast<JESP_t>(atoi(arg));
        else if(strcmp(arg,"Exh")==0)
            theArgumentsStruc->jesp = JESPExhaustive;
        else if(strcmp(arg,"DP")==0)
            theArgumentsStruc->jesp = JESPDP;
        else
            return ARGP_ERR_UNKNOWN;
        break;
    default:
        return ARGP_ERR_UNKNOWN;
    }
    return 0;
}
static struct argp JESP_argp = { JESP_options, JESP_parse_argument,
                                 JESP_args_doc, JESP_doc };
const struct argp_child JESP_child = {&JESP_argp, 0, "JESP options", GID_JESP};



} // end namespace
