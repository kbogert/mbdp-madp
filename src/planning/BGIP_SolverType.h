/**\file BGIP_SolverType.h
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
 * $Id: BGIP_SolverType.h 3598 2009-08-20 12:29:54Z mtjspaan $
 */

#ifndef  _BG_SOLVER_TYPE_H_
#define  _BG_SOLVER_TYPE_H_ 1

#include <string>

namespace BGIP_SolverType {

    enum BGIP_Solver_t {
        BFS, AM, 
        Random
    };
    const std::string BGIP_SolverNames[] = {
        "BGIP_Solver-BFS",
        "BGIP_Solver-AM",
        "BGIP_Solver-Random",
    };
    std::string SoftPrint(BGIP_Solver_t type);
    const size_t NUMBER_OF_BGIP_SOLVER_TYPES = 4;

}

#endif /* !_BG_SOLVER_TYPE_H_*/
