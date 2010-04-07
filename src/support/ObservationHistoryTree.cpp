/**\file ObservationHistoryTree.cpp
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
 * $Id: ObservationHistoryTree.cpp 2116 2008-01-16 23:11:49Z mtjspaan $
 */


#define DEBUG_OHT 0

/*
//Default constructor
ObservationHistoryTree::ObservationHistoryTree()
{
    _m_index = 0;
    _m_indexValid = false;
    _m_obsHist = 0;
}
ObservationHistoryTree::ObservationHistoryTree(ObservationHistory *const oh)
{
    _m_index = 0;
    _m_indexValid = false;
    _m_obsHist = oh;
}
//Copy assignment constructor.    
ObservationHistoryTree::ObservationHistoryTree(const ObservationHistoryTree& o) 
{
if(DEBUG_OHT){     cout << "Cloning ObservationHistoryTree. This node ";
    PrintThisNode();cout << endl;}
}

//Destructor -- deletes this node, the contained ObservationHistory and all
//successors
ObservationHistoryTree::~ObservationHistoryTree()
{
if(DEBUG_OHT){    cout << "Deleting ObservationHistoryTree. This node ";
    PrintThisNode();cout << endl;}
    
    delete(_m_obsHist);
    vector<ObservationHistoryTree*>::iterator it = _m_successor.begin();
    vector<ObservationHistoryTree*>::iterator last = _m_successor.end();
    
    while(it != last)
    {
        delete(*it);
        it++;
    }
    _m_successor.clear();
}
void ObservationHistoryTree::SetSuccessor(Index observationI, 
    ObservationHistoryTree* suc)
{
    size_t cursize = _m_successor.size();
    if(observationI == cursize)
        _m_successor.push_back(suc);
    else if(observationI < 0 || observationI > _m_successor.size() )
        cout << "ObservationHistoryTree::SetSuccessor ERROR index out of"
        << " bounds! (perhaps setting _m_successor["
        << observationI<< "] before _m_successor[" 
        << observationI-1 << "] ?? )";
    else
    {
        cout << "_m_successor["<< observationI<< "] already set: overwriting!";
        _m_successor[observationI] = suc;
    }
}
ObservationHistoryTree* ObservationHistoryTree::GetSuccessor(Index observationI) const
{
    if(observationI < 0 || observationI >= _m_successor.size() )
        throw E("ObservationHistoryTree::GetSuccessor index out of bounds!");
    else
        return(_m_successor[observationI]);
}
void ObservationHistoryTree::PrintThisNode() const
{
    if(_m_obsHist != 0)
    {
        cout << "index: "<<_m_index<<" - ";
        _m_obsHist->Print();
    }
}
void ObservationHistoryTree::Print() const
{
    if(_m_obsHist != 0)
    {
        cout << "index: "<<_m_index<<" - ";
        _m_obsHist->Print();
        cout <<endl;
        vector<ObservationHistoryTree*>::const_iterator it = _m_successor.begin();
        vector<ObservationHistoryTree*>::const_iterator last = _m_successor.end();
        while(it != last)
        {
            if(*it != 0) (*it)->Print();
            it++;
        }
    }
}
*/
