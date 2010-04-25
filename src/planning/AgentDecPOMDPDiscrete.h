/**\file AgentDecPOMDPDiscrete.h
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
 * $Id: AgentDecPOMDPDiscrete.h 2979 2008-11-03 20:00:13Z faolieho $
 */

/* Only include this header file once. */
#ifndef _AGENTDECPOMDPDISCRETE_H_
#define _AGENTDECPOMDPDISCRETE_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"

#include "SimulationAgent.h"

class PlanningUnitDecPOMDPDiscrete;

/** \brief AgentDecPOMDPDiscrete represents an agent in a discrete
 * DecPOMDP setting. */
class AgentDecPOMDPDiscrete : public SimulationAgent
{
private:    

    const PlanningUnitDecPOMDPDiscrete *_m_pu;
    
protected:
    
public:
    // Constructor, destructor and copy assignment.
    /// (default) Constructor
    AgentDecPOMDPDiscrete() : SimulationAgent(-1) 
    {
        throw E("AgentDecPOMDPDiscrete()  is not the right constructor to call");
    }
    AgentDecPOMDPDiscrete(const PlanningUnitDecPOMDPDiscrete &pu, Index id) :
        SimulationAgent(id), _m_pu(&pu) {};

    /// Copy constructor.
    AgentDecPOMDPDiscrete(const AgentDecPOMDPDiscrete& a) :
        SimulationAgent(a),
        _m_pu(a._m_pu){};

    const PlanningUnitDecPOMDPDiscrete* GetPU() const
        { return(_m_pu); }

};


#endif /* !_AGENTDECPOMDPDISCRETE_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
