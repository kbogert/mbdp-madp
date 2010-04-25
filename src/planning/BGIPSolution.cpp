/**\file BGIPSolution.cpp
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
 * $Id: BGIPSolution.cpp 3603 2009-08-25 10:38:25Z mtjspaan $
 */

#include "BGIPSolution.h"
#include <fstream>
#include "JPPVValuePair.h"
using namespace std;

//Default constructor
BGIPSolution::BGIPSolution(
        const Interface_ProblemToPolicyDiscretePure& pu,
        size_t nrSolutions
        ) :
    _m_pu(pu),
    _m_policy(0),
    _m_jpolIndex(0),
    _m_payoff(42),
    _m_nrSolutions(nrSolutions),
    _m_q(nrSolutions)
{
}

//Destructor
BGIPSolution::~BGIPSolution()
{
    // delete all the allocated JPPVValuePairs
    while(!_m_q.empty())
    {
        delete _m_q.top();
        _m_q.pop();
    }
    delete _m_policy;
}

void BGIPSolution::SetPolicy(const JointPolicyPureVector &jpol)
{
    _m_policy = new JointPolicyPureVector(jpol);
    //change this to a non-index based solution for now
    //(LIndex are not long enough...)
}

void BGIPSolution::SetPolicy(LIndex jpolIndex)
{
    if(_m_policy==0)
        _m_policy=new JointPolicyPureVector(_m_pu);
    _m_policy->SetIndex(jpolIndex);
    _m_jpolIndex=jpolIndex;
}

void BGIPSolution::Save(string filename) const
{
    ofstream fp(filename.c_str());
    if(!fp)
    {
        stringstream ss;
        ss << "BGIPSolution::Save: failed to open file " << filename << endl;
        throw E(ss);
    }

    fp.precision(16);
    fp << _m_jpolIndex << " " << _m_payoff << endl;
}

void BGIPSolution::Load(string filename)
{
    const int bufsize=65536;
    char buffer[bufsize];

    ifstream fp(filename.c_str());
    if(!fp)
    {
        stringstream ss;
        ss << "BGIPSolution::Load: failed to "
           << "open file " << filename << endl;
        throw E(ss);
    }

    LIndex index;
    double payoff;

    fp.getline(buffer,bufsize);
    istringstream is(buffer);
    is >> index;
    is >> payoff;

    SetPolicy(index);
    SetPayoff(payoff);
}

string BGIPSolution::SoftPrint() const
{
    stringstream ss;
    ss << "JPol" << _m_jpolIndex << "Payoff" << _m_payoff;
    return(ss.str());
}

#define DEBUG_ADD 0
void BGIPSolution::AddSolution(JointPolicyPureVector &jp,
                               double value)
{
    JPPVValuePair * p =  new JPPVValuePair(jp, value );

    Index pI = p->GetJPPV()->GetIndex();
#if DEBUG_ADD
    double v1 = p->GetValue();
    cout << "inserting policy# "<< pI << " with value " << v1 << "...";
#endif        
    if(_m_jpolIndices.find(pI) != _m_jpolIndices.end() )
    {
#if DEBUG_ADD
        cout << " NOT inserting (already in the queue)" << endl;
#endif
        delete p;
        return; //policy is already in the queue
    }
    _m_jpolIndices.insert(pI);
    JPPVValuePair* overflownvp_p = NULL;
    if( _m_q.insert(p, overflownvp_p) )
    {
        Index pI2 =  overflownvp_p->GetJPPV()->GetIndex();
#if DEBUG_ADD
        double v2 = overflownvp_p->GetValue();
        cout << "Removing overflown policy - policy# "<< pI2 << 
            " (with value "<<v2<<") "<< endl;
#endif    
        _m_jpolIndices.erase( pI2 );
//        delete overflown->GetJPol(); //not nec. destructor of JPPVValuePair handles this
        delete overflownvp_p;
    }
    else
    {
#if DEBUG_ADD
        cout << "added without overflow."<< endl;
#endif        
    }
}
