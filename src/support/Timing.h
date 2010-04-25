/**\file Timing.h
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
 * $Id: Timing.h 4016 2010-03-11 16:56:02Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _TIMING_H_
#define _TIMING_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"

#include <time.h>
#include <string>
#include <map>
#include <vector>



/** \brief Timing provides a simple way of timing code. */
class Timing 
{
private:

    /// Stores the start and end of a timespan, in clock cycles.
    struct Times {
        clock_t start, end;
        bool hasEnded;
    };

    /// Keeps track of timing info.
    std::map <std::string, std::vector<Times> > _m_timesMap;
    
    /// The clock cycle at which the class is initialized.
    clock_t _m_timeAtInitialization;

    clock_t GetCpuTime() const;

    double ClockToSeconds(clock_t clockTicks) const;

    void Stop(const std::string & id, clock_t duration);

protected:
    
public:
    // Constructor, destructor and copy assignment.
    /// (default) Constructor
    Timing();
    /// Destructor.
    ~Timing();

    /// Start to time an event identified by \a id.
    void Start(const std::string & id);

    /// Stop to time an event identified by \a id.
    void Stop(const std::string & id);

    /// Print stored timing info.
    void Print() const;

    /// Sums data and prints out a summary.
    void PrintSummary() const;

    /// Save collected timing info to file \a filename.
    void Save(const std::string & filename) const;

    /// Save collected timing info to ofstream \a of.
    void Save(std::ofstream &of) const;

    /// Load timing info from file \a filename.
    void Load(const std::string & filename);

    /// Adds event of certain duration, e.g., an external program call.
    void AddEvent(const std::string & id, clock_t duration);

    /// Returns all stored durations (in s) for a particular event.
    std::vector<double> GetEventDurations(const std::string & id);
};


#endif /* !_TIMING_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
