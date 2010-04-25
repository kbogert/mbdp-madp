/**\file directories.h
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
 * $Id: directories.h 3604 2009-08-25 10:52:24Z mtjspaan $
 */

#ifndef _DIRECTORIES_H_
#define _DIRECTORIES_H_ 1

#include <string>

class PlanningUnit;
class MultiAgentDecisionProcessInterface;
namespace ArgumentHandlers { class Arguments; }

/* This file provides functions to get directory and file names.
 * The code is structered around the following principles.
 *
 * (Input) problem files
 *
 * (Output) result files
 * --------------------
 *  are stored in
 *  MADPGetResultsDir (= ~/.madp/results/METHOD/PROBLEM )
 *  which can be retrieved using MADPGetResultsDir(...)
 *
 *  and have a basename
 *  METHOD_DESCR_PREFIX_ (where DESCR defaults to PROBLEM)
 *  which can be retrieved with MADPGetResultsBaseFilename(...).
 *
 *  The result is that result files are written to
 *  ~/.madp/results/METHOD/PROBLEM/METHOD_DESCR_PREFIX_....
 *
 *  MADPGetResultsFilename(...) gives you the concatenated version directly.
 *
 */

namespace directories {

    std::string MADPGetResultsDir();
    std::string MADPGetResultsDir(const std::string &method,
                                  const std::string &problem);
    std::string MADPGetResultsDir(const std::string &method,
                                  const PlanningUnit &pu);
    std::string MADPGetResultsDir(const std::string &method,
                                  const 
                                  MultiAgentDecisionProcessInterface &problem);
    std::string MADPGetResultsDir(const std::string &method,
                                  const PlanningUnit *pu);
    std::string MADPGetResultsDir(const std::string &method,
                                  const 
                                  MultiAgentDecisionProcessInterface *problem);

    void MADPCreateResultsDir(const std::string &method,
                              const std::string &problem);
    void MADPCreateResultsDir(const std::string &method,
                              const PlanningUnit &pu);
    void MADPCreateResultsDir(const std::string &method,
                              const 
                              MultiAgentDecisionProcessInterface &problem);
    void MADPCreateResultsDir(const std::string &method,
                              const PlanningUnit *pu);
    void MADPCreateResultsDir(const std::string &method,
                              const 
                              MultiAgentDecisionProcessInterface *problem);

    std::string MADPGetResultsBaseFilename(const std::string &method,
                                           const std::string &problem,
                                           const
                                           ArgumentHandlers::Arguments &args);

    std::string MADPGetResultsFilename(const std::string &method,
                                       const std::string &problem,
                                       const ArgumentHandlers::Arguments &args);
    std::string MADPGetResultsFilename(const std::string &method,
                                       const PlanningUnit &pu,
                                       const ArgumentHandlers::Arguments &args);
    std::string MADPGetResultsFilename(const std::string &method,
                                       const
                                       MultiAgentDecisionProcessInterface 
                                       &problem,
                                       const ArgumentHandlers::Arguments &args);

    std::string MADPGetProblemsDir();
    std::string MADPGetProblemFilename(const std::string &problem,
                                       const std::string &extension);
    std::string MADPGetProblemFilename(const std::string &problem);
    std::string MADPGetProblemFilename(const ArgumentHandlers::Arguments &args);

} // namespace directories

#endif /* !_DIRECTORIES_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
