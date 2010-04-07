/**\file ObservationModelMappingSparse.cpp
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
 * $Id: ObservationModelMappingSparse.cpp 2151 2008-01-21 16:32:52Z mtjspaan $
 */

#include "ObservationModelMappingSparse.h"

using namespace std;

ObservationModelMappingSparse::ObservationModelMappingSparse(int nrS,
                                                             int nrJA,
                                                             int nrJO) :
    ObservationModelDiscrete(nrS, nrJA, nrJO)
{
    SparseMatrix *O;
    for(int a=0;a!=nrJA;++a)
    {
        O=new SparseMatrix(nrS,nrJO);
        _m_O.push_back(O);
    }
}

ObservationModelMappingSparse::
ObservationModelMappingSparse(const ObservationModelMappingSparse& OM) :
    ObservationModelDiscrete(OM)
{
    SparseMatrix *O;
    for(unsigned int a=0;a!=OM._m_O.size();++a)
    {
        O=new SparseMatrix(*OM._m_O[a]);
        _m_O.push_back(O);
    }
}

ObservationModelMappingSparse::~ObservationModelMappingSparse()
{    
    for(vector<SparseMatrix*>::iterator it=_m_O.begin();
        it!=_m_O.end(); ++it)
        delete(*it);
    _m_O.clear();
}
