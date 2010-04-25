/**\file ParserTOIDecPOMDPDiscrete.cpp
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
 * $Id: ParserTOIDecPOMDPDiscrete.cpp 2962 2008-11-02 15:04:43Z mtjspaan $
 */

#include "ParserTOIDecPOMDPDiscrete.h"
#include "ParserDecPOMDPDiscrete.h"
#include <fstream>

using namespace std;

ParserTOIDecPOMDPDiscrete::
ParserTOIDecPOMDPDiscrete(TOIDecPOMDPDiscrete
                          *problem) :
    _m_problem(problem)
{
}

void ParserTOIDecPOMDPDiscrete::Parse()
{
    ParseBase();

    for(Index i=0;i!=_m_problem->GetNrAgents();++i)
        ParseAgent(i);

    ParseRewards();

    _m_problem->SetInitialized(true);
}


void ParserTOIDecPOMDPDiscrete::ParseRewards()
{
    vector<size_t> nrStates(_m_problem->GetNrAgents(),0),
        nrActions(_m_problem->GetNrAgents(),0);
    for(Index i=0;i!=_m_problem->GetNrAgents();++i)
    {
        nrStates[i]=_m_problem->GetIndividualMADPD(i)->GetNrStates();
        nrActions[i]=_m_problem->GetIndividualMADPD(i)->GetNrJointActions();
    }
    ParseRewards(_m_problem->GetNrAgents(),nrStates,nrActions);
}

void ParserTOIDecPOMDPDiscrete::ParseBase()
{
    const int bufsize=65536;
    char buffer[bufsize];

    unsigned int nrAgents;
    double gamma;

    string filename=_m_problem->GetProblemFile() + ".base";
    ifstream fp(filename.c_str());
    if(!fp)
    {
        cerr << "ParserTOIDecPOMDPDiscrete::ParseBase: failed to "
             << "open file " << filename << endl;            
        abort();
    }

    int line=0;
    while(!fp.getline(buffer,bufsize).eof())
    {
        istringstream is(buffer);
        switch(line)
        {
        case 0:
            is >> nrAgents;
            break;
        case 1:
            is >> gamma;
            break;
        }
        line++;
    }

    _m_problem->SetNrAgents(nrAgents);
    _m_problem->SetDiscount(gamma);
}

void ParserTOIDecPOMDPDiscrete::ParseAgent(Index id)
{
    MultiAgentDecisionProcessDiscrete* madp = 
        _m_problem->GetIndividualMADPD(id);

    DecPOMDPDiscrete *decpomdp;
    decpomdp=new DecPOMDPDiscrete("", "", madp->GetProblemFile());
    decpomdp->SetSparse(madp->GetSparse());

    ParserDecPOMDPDiscrete parser(decpomdp);
    parser.Parse();

    if(decpomdp->GetNrAgents()!=1)
        throw(E("ParserTOIDecPOMDPDiscrete::ParseAgent individual models can only be defined for a single agent"));

    StoreDecPOMDP(decpomdp,id);
}

void ParserTOIDecPOMDPDiscrete::StoreDecPOMDP(DecPOMDPDiscrete *decpomdp,
                                              Index id)
{
    MultiAgentDecisionProcessDiscrete* madp = 
        _m_problem->GetIndividualMADPD(id);
    decpomdp->ExtractMADPDiscrete(madp);
    _m_problem->SetIndividualDecPOMDPD(decpomdp,id);
}

/** Format for .rewards file is a set of lines:
 * <s_0 ... s_n> <a_0 ... a_n> <reward>
 */
void ParserTOIDecPOMDPDiscrete::ParseRewards(size_t nrAgents,
                                             const vector<size_t> &nrStates,
                                             const vector<size_t> &nrActions)
{
    const int bufsize=65536;
    char buffer[bufsize];

    vector<unsigned int> states, actions;
    unsigned int state,action;
    double reward;
    
    string filename=_m_problem->GetProblemFile() + ".rewards";
    ifstream fp(filename.c_str());
    if(!fp)
    {
        cerr << "ParserTOIDecPOMDPDiscrete::ParseRewards: failed to "
             << "open file " << filename << endl;            
    }

    _m_problem->CreateNewRewardModel();

    while(!fp.getline(buffer,bufsize).eof())
    {
        istringstream is(buffer);
        states.clear();
        actions.clear();
        for(unsigned int i=0;i!=nrAgents;++i)
        {
            is >> state;
            states.push_back(state);
        }
        for(unsigned int i=0;i!=nrAgents;++i)
        {
            is >> action;
            actions.push_back(action);
        }
        is >> reward;

        _m_problem->
            SetReward(states, actions, reward);
    }
}
