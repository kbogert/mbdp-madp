/**\file Simulation.h
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
 * $Id: Simulation.h 3598 2009-08-20 12:29:54Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _SIMULATION_H_
#define _SIMULATION_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"
#include <limits.h>
#include <stdlib.h>

/** \brief Simulation is a class that simulates policies in order to
 * test their control quality. */
class Simulation 
{
private:

    int _m_nrRuns;

    int _m_random_seed;

    bool _m_verbose;

protected:

    static const int illegalRandomSeed=INT_MAX;
    
public:
    // Constructor, destructor and copy assignment.

    /// Constructor that specifies the number of runs and the random seed.
    Simulation(int nrRuns, int seed=illegalRandomSeed) :
        _m_nrRuns(nrRuns),
        _m_random_seed(seed),
        _m_verbose(false)
        {}


    /// Destructor.
    virtual ~Simulation(){};

    void SetVerbose(bool verbose) { _m_verbose=verbose; }

    bool GetVerbose() const { return(_m_verbose); }
    int GetNrRuns() const { return(_m_nrRuns); }
    int GetRandomSeed() const { return(_m_random_seed); }
    void SetRandomSeed( int s) { _m_random_seed = s; srand(s); }

};

#endif /* !_SIMULATION_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
