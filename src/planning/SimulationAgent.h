/**\file SimulationAgent.h
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
 * $Id: SimulationAgent.h 2945 2008-10-25 11:14:45Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _SIMULATIONAGENT_H_
#define _SIMULATIONAGENT_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"

/// SimulationAgent represents an agent in for class Simulation.
class SimulationAgent 
{
private:    
    
    /// The index of this SimulationAgent, should be unique.
    Index _m_id;

    /// Whether we want the agent to be verbose.
    bool _m_verbose;

protected:
    
public:
    // Constructor, destructor and copy assignment.
    /// (default) Constructor
    SimulationAgent(Index id, bool verbose=false) :
        _m_id(id), _m_verbose(verbose){};

    /// Destructor.
    virtual ~SimulationAgent(){};

    /// Retrieves the index of this agent.
    virtual Index GetIndex() const { return(_m_id); }

    /// Sets the index of this agent.
    virtual void SetIndex(Index id) { _m_id=id; }

    /// Set whether this agent should be verbose.
    virtual void SetVerbose(bool verbose) { _m_verbose=verbose; }
    
    /// If true, the agent will report more.
    virtual bool GetVerbose() const { return(_m_verbose); }

    /// Will be called before an episode, to reinitialize the agent.
    virtual void ResetEpisode() = 0;

    /// Return some information about this agent.
    virtual std::string SoftPrint() const
    {
        std::stringstream ss;
        ss << "SimulationAgent id " << GetIndex();
        return(ss.str());
    }

    /// Print out some information about this agent.
    void Print() const {std::cout << SoftPrint(); }

};


#endif /* !_SIMULATIONAGENT_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
