/**\file TransitionModelMappingSparse.cpp
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
 * $Id: TransitionModelMappingSparse.cpp 2151 2008-01-21 16:32:52Z mtjspaan $
 */

#include "TransitionModelMappingSparse.h"

using namespace std;

TransitionModelMappingSparse::TransitionModelMappingSparse(int nrS, int nrJA) :
    TransitionModelDiscrete(nrS, nrJA)
{    
    SparseMatrix *T;
    for(int a=0;a!=nrJA;++a)
    {
        T=new SparseMatrix(nrS,nrS);
        _m_T.push_back(T);
    }
}

TransitionModelMappingSparse::
TransitionModelMappingSparse(const TransitionModelMappingSparse& TM) :
    TransitionModelDiscrete(TM)
{
    SparseMatrix *T;
    for(unsigned int a=0;a!=TM._m_T.size();++a)
    {
        T=new SparseMatrix(*TM._m_T[a]);
        _m_T.push_back(T);
    }
}

TransitionModelMappingSparse::~TransitionModelMappingSparse()
{    
    for(vector<SparseMatrix*>::iterator it=_m_T.begin();
        it!=_m_T.end(); ++it)
        delete(*it);
    _m_T.clear();
}
