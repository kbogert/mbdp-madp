/**\file TimeTools.h
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
 * $Id: TimeTools.h 3604 2009-08-25 10:52:24Z mtjspaan $
 */


#ifndef  TIMETOOLS_INC
#define  TIMETOOLS_INC

#include <sys/time.h>
#include <time.h>

namespace TimeTools{
    ///Returns the difference between start time and current time
    /**Returns a double, time is in microseconds
     */
    double GetDeltaTimeDouble(timeval start_time, timeval cur_time);

}

#endif   /* ----- #ifndef TIMETOOLS_INC  ----- */

