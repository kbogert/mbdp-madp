/**\file MultiAgentDecisionProcess.cpp
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
 * $Id: MultiAgentDecisionProcess.cpp 3598 2009-08-20 12:29:54Z mtjspaan $
 */

#include "MultiAgentDecisionProcess.h"    

using namespace std;

#define DEBUG_MADP 0

MultiAgentDecisionProcess::MultiAgentDecisionProcess(size_t nrAgents, 
    string name, string description, string pf) :
    NamedDescribedEntity(name, description),
    _m_nrAgents(nrAgents),
    _m_problemFile(pf)
{
    InitializeUnixName();
}

MultiAgentDecisionProcess::MultiAgentDecisionProcess(
    string name, string description, string pf) :
    NamedDescribedEntity(name, description),
    _m_nrAgents(0),
    _m_problemFile(pf)
{
    InitializeUnixName();
}

void MultiAgentDecisionProcess::InitializeUnixName()
{
    // strip everything before and including the last /
    string unixName=_m_problemFile.substr(_m_problemFile.find_last_of('/') + 1);

    // and after the last .
    _m_unixName=unixName.substr(0,unixName.find_last_of('.'));
}

MultiAgentDecisionProcess::~MultiAgentDecisionProcess()
{
    _m_problemFile.clear();
}

size_t MultiAgentDecisionProcess::GetNrAgents() const 
{
    return(_m_nrAgents);
}

void MultiAgentDecisionProcess::SetNrAgents(size_t nrAgents) 
{
    _m_nrAgents = nrAgents;
    _m_agents.clear();
    for(Index i = 0; i < nrAgents; i++)
        _m_agents.push_back(Agent(i));
}

void MultiAgentDecisionProcess::AddAgent(string name)
{
    _m_agents.push_back( Agent(_m_nrAgents++, name) );
}


string MultiAgentDecisionProcess::GetProblemFile() const 
{
    return(_m_problemFile);
}

string MultiAgentDecisionProcess::SoftPrint() const
{
    stringstream ss;
    ss << "Problem:"<< GetName()<< endl;
    ss << "descr.:"<< GetDescription() << endl;
    ss << "nrAgents=" << _m_nrAgents << endl;
    ss << "problem file=" << _m_problemFile << endl;
    return(ss.str());
}
