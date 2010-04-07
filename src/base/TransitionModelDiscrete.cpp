/**\file TransitionModelDiscrete.cpp
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
 * $Id: TransitionModelDiscrete.cpp 2151 2008-01-21 16:32:52Z mtjspaan $
 */

#include "TransitionModelDiscrete.h"

using namespace std;

TransitionModelDiscrete::TransitionModelDiscrete(int nrS, int nrJA) :
    _m_nrStates(nrS),
    _m_nrJointActions(nrJA)
{
}

TransitionModelDiscrete::~TransitionModelDiscrete()
{    
}

string TransitionModelDiscrete::SoftPrint() const 
{
    stringstream ss;
    double p = 0.0;
    ss << "s\tja\ts'\tP (tuples with P==0 are not printed)"<<endl;
    for(int sI = 0; sI < _m_nrStates; sI++)
        for(int jaI = 0; jaI < _m_nrJointActions; jaI++)
            for(int sIp = 0; sIp < _m_nrStates; sIp++)
            {
                p = Get(sI, jaI, sIp);
                if(p>0)
                    ss << sI << "\t" << jaI << "\t" << sIp << "\t" << p << endl;
            }
    return(ss.str());
}

Index TransitionModelDiscrete::SampleSuccessorState(Index state, Index action)
{
    double randNr=rand() / (RAND_MAX + 1.0);

    double sum=0;
    Index sucState=0;
    int i;

    for(i=0;i<_m_nrStates;i++)
    {
        sum+=Get(state,action,i);
        if(randNr<=sum)
        {
            sucState=i;
            break;
        }
    }
    return(sucState);
}
