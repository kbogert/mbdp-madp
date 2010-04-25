/**\file BayesianGameIdenticalPayoff.cpp
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
 * $Id: BayesianGameIdenticalPayoff.cpp 3598 2009-08-20 12:29:54Z mtjspaan $
 */

#include "BayesianGameIdenticalPayoff.h"
#include <fstream>

using namespace std;

//Default constructor
BayesianGameIdenticalPayoff::BayesianGameIdenticalPayoff()
{
    _m_initialized=false;
}

//TODO: make refs of these vectors?!
BayesianGameIdenticalPayoff::BayesianGameIdenticalPayoff(size_t nrAgents, 
        const vector<size_t>& nrActions, 
        const vector<size_t>& nrTypes) :
    BayesianGameIdenticalPayoffInterface(nrAgents, nrActions, nrTypes),
    _m_utilFunction(_m_nrJTypes, _m_nrJA, "type", "ja")
{
    _m_initialized=false;
}

bool BayesianGameIdenticalPayoff::SetInitialized(bool b)
{
    //TODO implement checks
    _m_initialized = b;
    return(true);
}

string BayesianGameIdenticalPayoff::SoftPrintUtilForJointType(Index jtype) const
{
    stringstream ss;
    ss << "Utility function for jtype "<<jtype << 
        "with prob.="<< GetProbability(jtype) << endl;
    ss << "jtype\tja\tu(jtype,ja)"<<endl;
    for(Index jaI=0; jaI < _m_nrJA; jaI++)
        ss << jtype << "\t" << jaI << "\t" << GetUtility(jtype, jaI)<<endl;
    return(ss.str());
}

string BayesianGameIdenticalPayoff::SoftPrint() const
{
    stringstream ss;
    ss << BayesianGameBase::SoftPrint();    
    ss << "Utility function:"<<endl;
    for(Index jtype=0; jtype < _m_nrJTypes; jtype++)
    {
        for(Index jaI=0; jaI < _m_nrJA; jaI++)
            ss << GetUtility(jtype,jaI) << " ";
        ss << endl;
    }
//    ss << _m_utilFunction.SoftPrint();
    return(ss.str());
}

void BayesianGameIdenticalPayoff::Save(const BayesianGameIdenticalPayoff &bg,
                                       string filename)
{
    throw(E("Not implemented"));
}

BayesianGameIdenticalPayoff BayesianGameIdenticalPayoff::Load(string filename)
{
    throw(E("Not implemented"));
    BayesianGameIdenticalPayoff bogus; // keep compiler happy
    return(bogus);
}

BayesianGameIdenticalPayoff 
BayesianGameIdenticalPayoff::GenerateRandomBG(
            size_t nrAgents,
            std::vector<size_t> acs,
            std::vector<size_t> obs
        )
{
    BayesianGameIdenticalPayoff bgip(nrAgents, acs, obs);
    for(Index jtype = 0; jtype < bgip.GetNrJointTypes(); jtype++)
        for(Index ja = 0; ja < bgip.GetNrJointActions(); ja++)
        {
            double rn = (rand() - (0.5 * RAND_MAX)) / (RAND_MAX / 20.0);
            bgip.SetUtility(jtype, ja, rn );
        }

    //create random, normalized prob distr.
    vector<double> typeProbs;
    double sum = 0.0;
    for(Index jtype = 0; jtype < bgip.GetNrJointTypes(); jtype++)
    {
        double r = ((double)rand()) / RAND_MAX;
        typeProbs.push_back(r);
    }
    for(Index jtype = 0; jtype < bgip.GetNrJointTypes(); jtype++)
        sum += typeProbs[jtype];
    for(Index jtype = 0; jtype < bgip.GetNrJointTypes(); jtype++)
        bgip.SetProbability(jtype, typeProbs[jtype] / sum );

    //bgip.Print();
    return(bgip);
}
