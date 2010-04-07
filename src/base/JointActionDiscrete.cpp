/**\file JointActionDiscrete.cpp
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
 * $Id: JointActionDiscrete.cpp 2945 2008-10-25 11:14:45Z mtjspaan $
 */

#include "JointActionDiscrete.h"
#include "ActionDiscrete.h"

using namespace std;

#define DEBUG_JAD 0

//Default constructor
JointActionDiscrete::JointActionDiscrete(Index index) :
    DiscreteEntity(index)
{
}

JointActionDiscrete::JointActionDiscrete(Index index,
                                         vector<const ActionDiscrete*> a) : 
    DiscreteEntity(index),
    _m_apVector(a)
{
    _m_aIndexVector = ConstructIndividualActionDiscretesIndices();
}

//Copy assignment constructor.        
JointActionDiscrete::JointActionDiscrete(const JointActionDiscrete& o) :
    DiscreteEntity(o)
{    
if(DEBUG_JAD)   cout << " cloning joint action ";

    vector<const ActionDiscrete*>::const_iterator itp = o._m_apVector.begin();
    vector<const ActionDiscrete*>::const_iterator lastp = o._m_apVector.end();
    while(itp != lastp)
    {
        const ActionDiscrete* t = *itp;
        _m_apVector.push_back(t);
        itp++;
    }
    _m_aIndexVector = o._m_aIndexVector;
}

//Destructor
JointActionDiscrete::~JointActionDiscrete()
{
if(DEBUG_JAD) cout << "deleting joint action";

/*  Do not delete the individual actions that are pointed to (there is only
 *  one copy of those, so that will lead to segfaults)
    for(Index i=0; i<_m_apVector.size(); i++) 
        delete _m_apVector[i];*/

    _m_apVector.clear();
}

void JointActionDiscrete::DeleteIndividualActions()
{
    for(vector<const ActionDiscrete*>::size_type i=0; i<_m_apVector.size(); i++) 
        delete _m_apVector[i];
}

void JointActionDiscrete::AddIndividualAction(const ActionDiscrete* a, 
        Index agentI)
{
    if( static_cast< vector<const ActionDiscrete*>::size_type >(agentI) != 
        _m_apVector.size() )
    {
        stringstream ss;
        ss << "WARNING! AddIndividualAction: size of _m_apVector does not match index of agent!\n _m_apVector.size()="
           << _m_apVector.size()<<" - agentI="<<agentI;
        throw(E(ss));
    }
    _m_apVector.push_back(a);
    _m_aIndexVector.push_back(a->GetIndex());
}

string JointActionDiscrete::SoftPrint() const
{
    stringstream ss;
    vector<const ActionDiscrete*>::const_iterator it =  _m_apVector.begin();
    vector<const ActionDiscrete*>::const_iterator last =  _m_apVector.end();

    ss << "JA" << GetIndex();
    
    while(it != last)
    {
        if(*it != 0)
            ss << "_" << (*it)->SoftPrintBrief(); 
        it++;
    }
    return(ss.str());
}

string JointActionDiscrete::SoftPrintBrief() const
{
    stringstream ss;
    vector<const ActionDiscrete*>::const_iterator it =  _m_apVector.begin();
    vector<const ActionDiscrete*>::const_iterator last =  _m_apVector.end();
    
    while(it != last)
    {
        if(*it != 0)
            ss << (*it)->SoftPrintBrief();
        if(it != last-1)
            ss << "_";
        it++;
    }
    return(ss.str());
}

vector<Index> JointActionDiscrete::ConstructIndividualActionDiscretesIndices() const
{
    vector<Index> iv;
    vector<const ActionDiscrete*>::const_iterator it = _m_apVector.begin();
    vector<const ActionDiscrete*>::const_iterator last = _m_apVector.end();
    while(it != last)
    {
        
        Index index = (*it)->GetIndex();
        iv.push_back( index );
        it++;
    }
    return(iv);
}
