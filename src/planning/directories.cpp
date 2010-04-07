/**\file directories.cpp
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
 * $Id: directories.cpp 3604 2009-08-25 10:52:24Z mtjspaan $
 */

#include "directories.h"
#include <wordexp.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "PlanningUnit.h"
#include "MultiAgentDecisionProcessInterface.h"
#include "argumentHandlers.h"

using namespace std;

string directories::MADPGetResultsDir()
{
    wordexp_t p;
    wordexp("~/.madp/results",&p,0);
    string dir(p.we_wordv[0]);
    wordfree(&p);
    return(dir);
}

string directories::MADPGetResultsDir(const string & method,
                                      const string & problem)
{
    string dir=MADPGetResultsDir() + "/" + method + "/" + problem;
    return(dir);
}

string directories::MADPGetResultsDir(const string & method,
                                      const PlanningUnit &pu)
{
    return(MADPGetResultsDir(method,pu.GetProblem()->GetUnixName()));
}

string
directories::MADPGetResultsDir(const string & method,
                               const MultiAgentDecisionProcessInterface
                               &problem)
{
    return(MADPGetResultsDir(method,problem.GetUnixName()));
}

string directories::MADPGetResultsDir(const string & method,
                                      const PlanningUnit *pu)
{
    return(MADPGetResultsDir(method,pu->GetProblem()->GetUnixName()));
}

string
directories::MADPGetResultsDir(const string & method,
                               const MultiAgentDecisionProcessInterface
                               *problem)
{
    return(MADPGetResultsDir(method,problem->GetUnixName()));
}

void directories::MADPCreateResultsDir(const string & method,
                                       const string & problem)
{
    string dir=MADPGetResultsDir() + "/" + method + "/" + problem;
    
    struct stat statInfo;
    if(stat(dir.c_str(),&statInfo)==0 &&
       S_ISDIR(statInfo.st_mode))
    {
#if 0
        cout << "Results dir " << dir << " already exists" << endl;
#endif
    }
    else
        if(mkdir(dir.c_str(),0777)!=0)
            perror("mkdir error");
}

void directories::MADPCreateResultsDir(const string & method,
                                      const PlanningUnit &pu)
{
    return(MADPCreateResultsDir(method,pu.GetProblem()->GetUnixName()));
}

void
directories::MADPCreateResultsDir(const string & method,
                                  const MultiAgentDecisionProcessInterface
                                  &problem)
{
    return(MADPCreateResultsDir(method,problem.GetUnixName()));
}

void directories::MADPCreateResultsDir(const string & method,
                                      const PlanningUnit *pu)
{
    return(MADPCreateResultsDir(method,pu->GetProblem()->GetUnixName()));
}

void
directories::MADPCreateResultsDir(const string & method,
                                  const MultiAgentDecisionProcessInterface
                                  *problem)
{
    return(MADPCreateResultsDir(method,problem->GetUnixName()));
}

string
directories::MADPGetResultsBaseFilename(const string & method, const string & problem, 
                                        const ArgumentHandlers::Arguments &args)
{
    string descr;
    if(args.description == NULL)
        descr = problem;
    else
        descr = string(args.description);

    string basename = method + "_" + descr + "_";
    if(args.prefix != NULL )
        basename = basename + args.prefix + "_";

    if(args.discount!=-1)
    {
        stringstream ss;
        ss << basename << "g" << args.discount << "_";
        basename=ss.str();
    }
    return(basename);
}

string directories::MADPGetResultsFilename(const string & method,
                                           const string & problem,
                                           const
                                           ArgumentHandlers::Arguments &args)
{
    return(MADPGetResultsDir(method,problem) + "/" +
           MADPGetResultsBaseFilename(method, problem, args));
}

string directories::MADPGetResultsFilename(const string & method,
                                           const PlanningUnit &pu,
                                           const
                                           ArgumentHandlers::Arguments &args)
{
    return(MADPGetResultsDir(method,pu) + "/" +
           MADPGetResultsBaseFilename(method,pu.GetProblem()->GetUnixName(),
                                      args));
}

string
directories::MADPGetResultsFilename(const string & method,
                                    const 
                                    MultiAgentDecisionProcessInterface &problem,
                                    const ArgumentHandlers::Arguments &args)
{
    return(MADPGetResultsDir(method,problem) + "/" +
           MADPGetResultsBaseFilename(method,problem.GetUnixName(),
                                      args));
}

string directories::MADPGetProblemsDir()
{
    wordexp_t p;
    wordexp("~/.madp/problems",&p,0);
    string dir(p.we_wordv[0]);
    wordfree(&p);
    return(dir);
}

string directories::MADPGetProblemFilename(const string & problem, const string & extension)
{
    // check whether the problem string ends in the extension
    if(extension.size() < problem.size() && // otherwise the compare
                                            // cannot be done
       problem.compare(problem.size()-extension.size(),
                       extension.size(),
                       extension)==0)
        return(problem);
    else
        return(MADPGetProblemsDir() + "/" + problem + "." + extension);
}

string directories::MADPGetProblemFilename(const string & problem)
{
    // default extension
    return(MADPGetProblemFilename(problem,"dpomdp"));
}

string directories::MADPGetProblemFilename(const 
                                           ArgumentHandlers::Arguments &args)
{
    if(args.isTOI)
        return(MADPGetProblemFilename(args.dpf,"toi-dpomdp"));
    else
        return(MADPGetProblemFilename(args.dpf,"dpomdp"));
}
