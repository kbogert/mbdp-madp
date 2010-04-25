/**\file JointObservationDiscrete.cpp
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
 * $Id: JointObservationDiscrete.cpp 2945 2008-10-25 11:14:45Z mtjspaan $
 */

#include "JointObservationDiscrete.h"
#include "ObservationDiscrete.h"

using namespace std;

#define DEBUG_JOD 0

//Default constructor
JointObservationDiscrete::JointObservationDiscrete(Index index) :
    DiscreteEntity(index)
{
}

JointObservationDiscrete::JointObservationDiscrete(Index index,
                                                   vector<const ObservationDiscrete*> a) :
    DiscreteEntity(index),
    _m_opVector(a)
    
{
    _m_oIndexVector = ConstructIndividualObservationDiscretesIndices();
}

//Copy assignment constructor.    
JointObservationDiscrete::JointObservationDiscrete(const 
                                                   JointObservationDiscrete& o) :
    DiscreteEntity(o)
{    
if(DEBUG_JOD)    cout << " cloning JointObservationDiscrete ";
    vector<const ObservationDiscrete*>::const_iterator itp = o._m_opVector.begin();
    vector<const ObservationDiscrete*>::const_iterator lastp = o._m_opVector.end();
    while(itp != lastp)
    {
        const ObservationDiscrete* t = *itp;
        _m_opVector.push_back(t);
        itp++;
    }
    _m_oIndexVector = o._m_oIndexVector;
}

//Destructor
JointObservationDiscrete::~JointObservationDiscrete()
{
if(DEBUG_JOD)    cout << "deleting JointObservationDiscrete";
/*  Do not delete the individual observations - only one copy of these, so 
 *  would lead to segfaults.
    for(Index i=0; i<_m_opVector.size(); i++)
    delete _m_opVector[i];*/
    _m_opVector.clear();
}

void JointObservationDiscrete::AddIndividualObservation(const ObservationDiscrete* a,  Index agentI)
{
    if (agentI != _m_opVector.size() )
    cout << "WARNING! AddIndividualAction: size of _m_opVector does not match index of agent!\n _m_opVector.size()="<< _m_opVector.size()<<" - agentI="<<agentI<<endl;    
    _m_opVector.push_back(a);
    _m_oIndexVector.push_back(a->GetIndex());
}

string JointObservationDiscrete::SoftPrint() const
{
    stringstream ss;
    vector<const ObservationDiscrete*>::const_iterator it =  _m_opVector.begin();
    vector<const ObservationDiscrete*>::const_iterator last =  _m_opVector.end();

    ss << "JO" << GetIndex();

    while(it != last)
    {
        if(*it != 0)
            ss << "_" << (*it)->SoftPrintBrief(); 
        it++;
    }
    //ss << "(vector="<< PrintTools::SoftPrintVector(_m_oIndexVector) <<", size="
        //<<_m_oIndexVector.size()<<")";
    return(ss.str());
}    

string JointObservationDiscrete::SoftPrintBrief() const
{
    stringstream ss;
    vector<const ObservationDiscrete*>::const_iterator it =  _m_opVector.begin();
    vector<const ObservationDiscrete*>::const_iterator last =  _m_opVector.end();

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


vector<Index> JointObservationDiscrete::ConstructIndividualObservationDiscretesIndices() const
{
    vector<Index> iv;
    vector<const ObservationDiscrete*>::const_iterator it = _m_opVector.begin();
    vector<const ObservationDiscrete*>::const_iterator last = _m_opVector.end();
if(DEBUG_JOD){ cout << " JointObservationDiscrete::" <<
    "GetIndividualObservationDiscretesIndices() _m_opVector size =" 
    << _m_opVector.size() << endl;
}
    while(it != last)
    {
    
        Index index = (*it)->GetIndex();
        iv.push_back( index );
        it++;
    }
    return(iv);
}
