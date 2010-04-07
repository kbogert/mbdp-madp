/**\file SimulationResult.cpp
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
 * $Id: SimulationResult.cpp 2125 2008-01-18 12:51:50Z mtjspaan $
 */

#include "SimulationResult.h"
#include <float.h>
#include <fstream>

using namespace std;

//Default constructor
SimulationResult::SimulationResult()
{
    _m_nr_stored=0;
    _m_avg_reward=-1;
}

/** 
 * @param horizon planning horizon
 * @param random_seed seed used for sampling
 * @param nrRuns number of runs simulated
 */
SimulationResult::SimulationResult(int horizon,int random_seed,int nrRuns)
{
    _m_horizon=horizon;
    _m_random_seed=random_seed;
    _m_rewards = vector<double>(nrRuns, 0.0);
    _m_nr_stored=0;
    _m_avg_reward=-1;
}

//Destructor
SimulationResult::~SimulationResult()
{
}

void SimulationResult::AddReward(double r)
{
    _m_nr_stored++;
    _m_rewards[_m_nr_stored-1]=r;

    UpdateStatistics();
}

vector<double> SimulationResult::GetRewards(void)
{
    vector<double> rewards(_m_nr_stored);

    for(unsigned int i=0;i<_m_nr_stored;i++)
        rewards[i]=_m_rewards[i];
    
    return(rewards);
}

void SimulationResult::UpdateStatistics()
{ 
    // update the average reward
    double sum=0;
    for(unsigned int i=0;i<_m_nr_stored;i++)
        sum+=_m_rewards[i];

    if(_m_nr_stored>0)
        _m_avg_reward=sum/_m_nr_stored;
    else
        _m_avg_reward=DBL_MAX;
}

void SimulationResult::Print(void)
{
    if(_m_nr_stored>_m_rewards.size())
        cerr << "SimulationResult::Print error _m_nr_stored " << _m_nr_stored  
             << " > " << " _m_rewards.size() " << _m_rewards.size() << endl;

    cout << "SimulationResult::Print horizon " << _m_horizon << " seed "
         << _m_random_seed << " entries " << _m_nr_stored << endl;
    cout << "SimulationResult::Print Rewards: ";
    for(unsigned int i=0;i<_m_nr_stored;i++)
        cout << _m_rewards[i] << " ";
    cout << endl;
    cout << "SimulationResult::Print Average reward " << _m_avg_reward << endl;
}

void SimulationResult::PrintSummary(void)
{
    cout << "Average reward: " << _m_avg_reward << " ("
         << _m_nr_stored << " samples)" << endl;
}

void SimulationResult::Save(string filename)
{
    ofstream fp(filename.c_str());
    if(!fp)
    {
        stringstream ss;
        ss << "SimulationResult::Save failed to open file " << filename << endl;
        throw E(ss);
    }
   
    vector<double> rewards=GetRewards();

    for(unsigned i=0;i<rewards.size();i++)
        fp << rewards[i] << endl;
}

void SimulationResult::Load(string filename)
{
    const int bufsize=65536;
    char buffer[bufsize];

    double r;

    ifstream fp(filename.c_str());
    if(!fp)
    {
        stringstream ss;
        ss << "SimulationResult::Load: failed to "
           << "open file " << filename;
        throw E(ss);
    }

    _m_rewards.clear();

    while(!fp.getline(buffer,bufsize).eof())
    {
        istringstream is(buffer);
        is >> r;
        _m_rewards.push_back(r);
    }

    _m_nr_stored=_m_rewards.size();
    UpdateStatistics();
}
