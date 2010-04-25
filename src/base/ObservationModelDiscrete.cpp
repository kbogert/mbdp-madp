/**\file ObservationModelDiscrete.cpp
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
 * $Id: ObservationModelDiscrete.cpp 2945 2008-10-25 11:14:45Z mtjspaan $
 */

#include "ObservationModelDiscrete.h"
#include <stdlib.h>

using namespace std;

//Default constructor
ObservationModelDiscrete::ObservationModelDiscrete(int nrS,
                                                   int nrJA,
                                                   int nrJO) :
    _m_nrStates(nrS),
    _m_nrJointActions(nrJA),
    _m_nrJointObservations(nrJO)
{
}

//Destructor
ObservationModelDiscrete::~ObservationModelDiscrete()
{
}

string ObservationModelDiscrete::SoftPrint() const
{
    stringstream ss;
    double p;
    ss << "jo\tja\ts'\tP (tuples with P==0 are not printed)"<<endl;
    for(int jo_i = 0; jo_i < _m_nrJointObservations; jo_i++)
        for(int ja_i = 0; ja_i < _m_nrJointActions; ja_i++)
            for(int s_ip = 0; s_ip < _m_nrStates; s_ip++)
            {
                p=Get(ja_i, s_ip, jo_i);
                if(p>0)
                    ss << jo_i << "\t" << ja_i << "\t" << s_ip << "\t" << p
                         << endl;
            }
    return(ss.str());
}
    
Index ObservationModelDiscrete::SampleJointObservation(Index jaI, Index sucI)
{
    double randNr=rand() / (RAND_MAX + 1.0);
    
    double sum=0;
    Index jo=0;
    int i;
    
    for(i=0;i<_m_nrJointObservations;i++)
    {
        sum+=Get(jaI,sucI,i);
        if(randNr<=sum)
        {
            jo=i;
            break;
        }
    }
    
    return(jo);
}
