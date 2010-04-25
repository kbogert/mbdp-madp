/**\file TimeTools.cpp
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
 * $Id: TimeTools.cpp 3604 2009-08-25 10:52:24Z mtjspaan $
 */

#include "TimeTools.h"

#include <sys/types.h>

namespace TimeTools{

double GetDeltaTimeDouble(timeval start_time, timeval cur_time)
{
    if(gettimeofday(&cur_time, NULL) != 0)
        throw "Error with gettimeofday";

    time_t delta_sec = cur_time.tv_sec - start_time.tv_sec;
    suseconds_t delta_usec = cur_time.tv_usec - start_time.tv_usec;
    double delta = 1000000.0 * delta_sec + delta_usec; //in microsecond
    return delta;
}

}



