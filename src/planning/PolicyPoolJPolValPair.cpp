/**\file PolicyPoolJPolValPair.cpp
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
 * $Id: PolicyPoolJPolValPair.cpp 3603 2009-08-25 10:38:25Z mtjspaan $
 */
#include <float.h>
#include "PolicyPoolJPolValPair.h"
#include "JPPVValuePair.h"
#include "JointPolicyPureVector.h"
#define DEBUG_PPJPVP_ASSIGN 0

using namespace std;

//Default constructor
PolicyPoolJPolValPair::PolicyPoolJPolValPair()
{   
    _m_jpvpQueue_p = new priority_queue<JointPolicyValuePair*>(); //&JPolValPool;    
}

//Destructor
PolicyPoolJPolValPair::~PolicyPoolJPolValPair()
{
    while(_m_jpvpQueue_p->size() > 0)
    {
        delete _m_jpvpQueue_p->top();
        _m_jpvpQueue_p->pop();
    }
    delete _m_jpvpQueue_p;
}
//Copy assignment operator
PolicyPoolJPolValPair& PolicyPoolJPolValPair::operator= 
    (const PolicyPoolJPolValPair& o)
{
    if(DEBUG_PPJPVP_ASSIGN)
        cout <<"PolicyPoolJPolValPair& PolicyPoolJPolValPair::operator= \
called"<<endl;

    if (this == &o) return *this;   // Gracefully handle self assignment
    // Put the normal assignment duties here...
    //
    // empty own queue 
    while(_m_jpvpQueue_p->size() > 0)
    {
        delete _m_jpvpQueue_p->top();
        _m_jpvpQueue_p->pop();
    }
    *_m_jpvpQueue_p = *(o._m_jpvpQueue_p);

    return *this;
}
PolicyPoolInterface& PolicyPoolJPolValPair::operator= 
    (const PolicyPoolInterface& o)
{
    if(DEBUG_PPJPVP_ASSIGN)
        cout <<"PolicyPoolInterface& PolicyPoolJPolValPair::operator= \
called."<<endl;
    if (this == &o) return *this;   // Gracefully handle self assignment
    const PolicyPoolJPolValPair& casted_o = 
        dynamic_cast<const PolicyPoolJPolValPair&>(o);

    return(operator=(casted_o));

}


void PolicyPoolJPolValPair::Init(const Interface_ProblemToPolicyDiscretePure* pu)
{
    //start with a horizon 0 joint policy - i.e. specifying 0 actions
    JointPolicyPureVector* jpol_empty = 
        new JointPolicyPureVector(*pu, OHIST_INDEX); 
    jpol_empty->SetDepth(0);
    JointPolicyValuePair* jpv_empty = new JPPVValuePair(*jpol_empty, DBL_MAX); 
    _m_jpvpQueue_p->push(jpv_empty);
    //JPolValPool_p->push(jpv_empty);
}

PolicyPoolItemInterface* PolicyPoolJPolValPair::Select() const
{
    if(_m_jpvpQueue_p->size() > 0)
    {
        PolicyPoolItemInterface* ppi = (PolicyPoolItemInterface* ) 
            _m_jpvpQueue_p->top();
        return(ppi);
    }
    else
        throw E("Pool empty!");

}
void PolicyPoolJPolValPair::Pop()
{
    _m_jpvpQueue_p->pop();
}


void PolicyPoolJPolValPair::Insert(PolicyPoolItemInterface*  ppi)
{
    JointPolicyValuePair* jp = dynamic_cast<JointPolicyValuePair*>(ppi);

    if(jp==0)
        throw(E("PolicyPoolJPolValPair::Insert could not cast input to JointPolicyValuePair"));

    _m_jpvpQueue_p->push(jp);
    
}

void PolicyPoolJPolValPair::Union(PolicyPoolInterface*  o_ppi)
{
    PolicyPoolJPolValPair * o = dynamic_cast<PolicyPoolJPolValPair *>(o_ppi);

    if(o==0)
        throw(E("PolicyPoolJPolValPair::Union could not cast input to PolicyPoolJPolValPair"));

    while(o->_m_jpvpQueue_p->size() > 0)
    {
        this->_m_jpvpQueue_p->push(o->_m_jpvpQueue_p->top());
        o->_m_jpvpQueue_p->pop();
    }
}

void PolicyPoolJPolValPair::Prune(double v)
{
     priority_queue<JointPolicyValuePair*> * new_jpvpQueue_p = 
         new priority_queue<JointPolicyValuePair*>;

     while(_m_jpvpQueue_p->size() > 0)
     {
         JointPolicyValuePair* jpvp = _m_jpvpQueue_p->top();
         if(jpvp->GetValue() > v)
         {
             new_jpvpQueue_p->push(jpvp);
         }
         else
             delete jpvp; // no longer necessary
         _m_jpvpQueue_p->pop();    
     }

     delete _m_jpvpQueue_p; //delete old queue
     _m_jpvpQueue_p = new_jpvpQueue_p; //point to new queue


}
