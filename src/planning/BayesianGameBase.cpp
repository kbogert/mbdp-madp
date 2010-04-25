/**\file BayesianGameBase.cpp
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
 * $Id: BayesianGameBase.cpp 3598 2009-08-20 12:29:54Z mtjspaan $
 */

#include "BayesianGameBase.h"
#include "E.h"

using namespace std;

//Default constructor
BayesianGameBase::BayesianGameBase()
    : _m_verboseness(0)
{
    cerr << "Warning BayesianGameBase called without arguments"<< endl;
    _m_initialized=false;
    _m_nrAgents = 0;
    _m_nrActions.clear();
    _m_nrTypes.clear();
    _m_nrJTypes = 0;
    _m_nrJA = 0;
    _m_jTypeProbs.clear();
    _m_stepSizeActions = 0;
    _m_stepSizeTypes = 0;
    _m_jointToIndTypes = 0;
}

BayesianGameBase::BayesianGameBase(
        const size_t nrAgents, 
        const vector<size_t> & nrActions,  
        const vector<size_t> & nrTypes,
        int verb)
    : _m_verboseness(verb)
{
    if( nrActions.size() != nrAgents || nrTypes.size() != nrAgents)
        throw E("Dimension mismatches in creating a Bayesian game");

    _m_nrAgents = nrAgents;
    _m_nrActions = nrActions;
    _m_nrTypes = nrTypes;
    _m_stepSizeTypes = IndexTools::CalculateStepSize(nrTypes);
    _m_stepSizeActions = IndexTools::CalculateStepSize(nrActions);

    //calculate # joint types and actions
    _m_nrJTypes = 1;
    _m_nrJA = 1;
    for(Index i = 0; i < nrAgents; i++)
    {
        _m_nrJTypes *= _m_nrTypes[i];
        _m_nrJA *= _m_nrActions[i];
    }

    if(_m_nrJTypes>1e6)
    {
        cout << "BayesianGameBase: using sparse models" << endl;
        _m_useSparse=true;
    }
    else
    {
        _m_useSparse=false;
        try {
            _m_jTypeProbs = vector<double>(_m_nrJTypes, 0.0);
            _m_jointToIndTypes = new vector<vector<Index> >(_m_nrJTypes);
        } catch(std::bad_alloc)
        {
            cout << "BayesianGameBase: too many joint types ("
                 << _m_nrJTypes
                 << ") to have a full vector in memory, switching to sparse models..." << endl;
            _m_useSparse=true;
        }
    }

    //initialize the probability distribution over joint types:
    if(_m_useSparse)
    {
        _m_jTypeProbsSparse.resize(_m_nrJTypes);
        _m_jTypeProbsSparse.clear();
        _m_jointToIndTypesMap = new map<Index, vector<Index> >();
        _m_jointToIndTypes=0;
    }
    else
    {
        _m_jointToIndTypesMap=0;
    }

    _m_initialized=true;
}

//Copy assignment constructor.    
BayesianGameBase::BayesianGameBase(const BayesianGameBase& o) 
{
    throw E("trying to copy construct a BayesianGameBase - not implemented. (is this necessary?)");
}

//Destructor
BayesianGameBase::~BayesianGameBase()
{
    delete [] _m_stepSizeTypes;
    delete [] _m_stepSizeActions;
}

bool BayesianGameBase::SetInitialized(bool b)
{
    //TODO implement checks
    _m_initialized = b;
    return(true);
}

string BayesianGameBase::SoftPrint() const
{
    stringstream ss;
    ss << "Bayesian game with "<<_m_nrAgents<<" agents"<<endl;
    ss << "Number of actions ";
    ss << SoftPrintVector(_m_nrActions);
    ss << " ("<< _m_nrJA <<" joint actions)";
    ss << "\nNumber of types ";
    ss << SoftPrintVector(_m_nrTypes);
    ss << " ("<< _m_nrJTypes <<" joint types)"<<endl;
    ss << "joint type probs: ";
    ss << SoftPrintVector(_m_jTypeProbs);
    ss << endl;
    return(ss.str());
}

string BayesianGameBase::SoftPrintPolicyDomainElement(Index agentI, 
        Index typeIndex,
        PolicyGlobals::IndexDomainCategory cat) const
{
    if(cat != PolicyGlobals::TYPE_INDEX)
        throw E("BGs only work with types as the policy domain");
    stringstream ss;
    ss << "BGType"<<typeIndex;
    return(ss.str());
}
string BayesianGameBase::SoftPrintAction(Index agentI, Index actionI) const
{
    stringstream ss;
    ss << "BGAction"<<actionI;
    return(ss.str());
}
void BayesianGameBase::PrintPolicyDomain(Index agentI, Index typeIndex) const
{
    throw E("BayesianGameBase::PrintPolicyDomainNot (yet? deprecate?) implemented");
}
void BayesianGameBase::PrintAction(Index agentI, Index actionI) const
{
    throw E("BayesianGameBase::PrintAction(Not (yet? deprecate?) implemented");
}

bool BayesianGameBase::AreCachedJointToIndivIndices(
    const PolicyGlobals::IndexDomainCategory pdc) const 
{
    switch ( pdc )
    {
    case PolicyGlobals::OHIST_INDEX :
        return CacheJointToIndivOH_Indices();
        break;
    case PolicyGlobals::AOHIST_INDEX :
        return CacheJointToIndivAOH_Indices();
        break;
    case PolicyGlobals::TYPE_INDEX : 
        return CacheJointToIndivType_Indices();
        break;
    default:
        throw(E("Used a JointPolicyDiscrete::PolicyGlobals::IndexDomainCategory unknown to BayesianGameBase!"));
        break;
    }				/* -----  end switch  ----- */
};

PolicyGlobals::IndexDomainCategory BayesianGameBase::GetDefaultIndexDomCat()
    const
{
    return PolicyGlobals::TYPE_INDEX;
}

size_t BayesianGameBase::GetNrPolicyDomainElements(
    Index agentI, 
    PolicyGlobals::IndexDomainCategory cat,
    size_t depth) const
{
#if 0
    if(depth!=MAXHORIZON)
        throw(E("BayesianGameBase::GetNrPolicyDomainElements depth argument not supported for BGs"));
#endif
    return _m_nrTypes[agentI];
}

bool
BayesianGameBase::SanityCheck() const 
{
    double p=0.0;
    for(Index jtI=0; jtI < _m_nrJTypes; jtI++)
        p += GetProbability(jtI);
    if(! Globals::EqualProbability(p, 1.0) )
    {
        stringstream ss;
        ss << "Warning, total probability of joint types does not sum to 1.0, "
            << "but to "<<p<<"!";
        throw(E(ss));
    }
    return true;
}

void BayesianGameBase::SanityCheckBGBase()
{ 
    double psum = 0.0;
    for(Index jtI=0; jtI < _m_jTypeProbs.size(); jtI++)
        psum += GetProbability(jtI);

    if(!Globals::EqualProbability(psum, 1.0))
        cout << "Warning! - BayesianGameBase::SanityCheck does not sum to 1.0" << endl;
    if(  abs(psum - 1.0) > 1e-12  )
        cout << "Warning -  - BayesianGameBase::SanityCheck could perhaps use renormalization?"<<endl;

}
