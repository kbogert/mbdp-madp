/**\file BayesianGame.cpp
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
 * $Id: BayesianGame.cpp 3598 2009-08-20 12:29:54Z mtjspaan $
 */

#include "BayesianGame.h"
#include "E.h"

using namespace std;

BayesianGame::BayesianGame(size_t nrAgents, const vector<size_t> &nrActions,  
                           const vector<size_t> &nrTypes) :
    BayesianGameBase(nrAgents, nrActions, nrTypes)
{
    //initialize the utility functions
    RewardModelMapping r(_m_nrJTypes, _m_nrJA, "type", "ja");
    for(Index i = 0; i < _m_nrAgents; i++)
        _m_utilFuncs.push_back(r); //r is copied by value so we get independent
        //copies in _m_utilFuncs.

}
//Copy assignment constructor.    
BayesianGame::BayesianGame(const BayesianGame& o)  :
     BayesianGameBase(o)
{
    throw E("trying to copy construct a BayesianGame - not implemented. (is this necessary?)");
}
//Destructor

bool BayesianGame::SetInitialized(bool b)
{
    //TODO implement checks
    _m_initialized = b;
    return(true);
}

void BayesianGame::Print() const
{
    BayesianGameBase::Print();
    
    cout << "Utility functions:"<<endl;
    for(Index aI = 0; aI < _m_nrAgents; aI++)
    {
        cout << "Agent "<<aI<<":"<<endl;
        _m_utilFuncs[aI].Print();
    }
}

