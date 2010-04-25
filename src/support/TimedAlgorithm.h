/**\file TimedAlgorithm.h
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
 * $Id: TimedAlgorithm.h 4016 2010-03-11 16:56:02Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _TIMEDALGORITHM_H_
#define _TIMEDALGORITHM_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"

#include "Timing.h"

/**\brief TimedAlgorithm allows for easy timekeeping of parts of an
 * algorithm.*/
class TimedAlgorithm 
{
private:    
    
    /// Stores the timing info.
    // This is a pointer, so that timing information can be stored in
    // const functions.
    Timing *_m_timer;

protected:
    
public:
    // Constructor, destructor and copy assignment.
    /// (default) Constructor
    TimedAlgorithm();
    /// Destructor.
    virtual ~TimedAlgorithm();

    /// Start to time an event identified by \a id.
    void StartTimer(const std::string & id) const;

    /// Stop to time an event identified by \a id.
    void StopTimer(const std::string & id) const;

    /// Print stored timing info.
    void PrintTimers() const;

    /// Sums data and prints out a summary.
    void PrintTimersSummary() const;

    /// Save collected timing info to file \a filename.
    void SaveTimers(const std::string & filename) const;

    /// Save collected timing info to ofstream \a of.
    void SaveTimers(std::ofstream &of) const;

    /// Load timing info from file \a filename.
    void LoadTimers(const std::string & filename);

    /// Adds event of certain duration, e.g., an external program call.
    void AddTimedEvent(const std::string & id, clock_t duration);

    /// Returns all stored durations (in s) for a particular event.
    std::vector<double> GetTimedEventDurations(const std::string & id);

};


#endif /* !_TIMEDALGORITHM_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
