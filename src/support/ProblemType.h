/**\file ProblemType.h
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
 * $Id: ProblemType.h 3604 2009-08-25 10:52:24Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _PROBLEMTYPE_H_
#define _PROBLEMTYPE_H_ 1

/* the include directives */
#include "Globals.h"

/** \brief ProblemType is a class that represents 
 * TODO: fill out...  */
namespace ProblemType 
{
    ///These are the standard problem types
    /**Note: to be able to specify them as an argument on the command 
     * line, you also need to add them to the argumentHandler (in
     * argumentHandler.cpp).
     */
    enum Problem_t {PARSE, DT, FF};

    std::string SoftPrint(Problem_t t);
};


#endif /* !_PROBLEMTYPE_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
