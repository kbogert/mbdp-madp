/**\file PolicyPoolPartialJPolValPair.cpp
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
 * $Id: PolicyPoolPartialJPolValPair.cpp 3603 2009-08-25 10:38:25Z mtjspaan $
 */
#include <float.h>
#include "PolicyPoolPartialJPolValPair.h"
#include "PartialJointPolicyPureVector.h"
#define DEBUG_PPJPVP_ASSIGN 0

using namespace std;

//Default constructor
PolicyPoolPartialJPolValPair::PolicyPoolPartialJPolValPair()
{   
    _m_jpvpQueue_p = new priority_queue<PartialJPDPValuePair*>(); //&JPolValPool;    
}


//Copy constructor.    
//PolicyPoolPartialJPolValPair::PolicyPoolPartialJPolValPair(const PolicyPoolPartialJPolValPair& o) 
//{
    //throw E("PolicyPoolPartialJPolValPair /Copy constructor. is not (and never will be?) defined.");
//}
//Destructor
PolicyPoolPartialJPolValPair::~PolicyPoolPartialJPolValPair()
{
    while(_m_jpvpQueue_p->size() > 0)
    {
        delete _m_jpvpQueue_p->top();
        _m_jpvpQueue_p->pop();
    }
    delete _m_jpvpQueue_p;
}
//Copy assignment operator
PolicyPoolPartialJPolValPair& PolicyPoolPartialJPolValPair::operator= 
    (const PolicyPoolPartialJPolValPair& o)
{
    if(DEBUG_PPJPVP_ASSIGN)
        cout <<"PolicyPoolPartialJPolValPair& PolicyPoolPartialJPolValPair::operator= \
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
PartialPolicyPoolInterface& PolicyPoolPartialJPolValPair::operator= 
    (const PartialPolicyPoolInterface& o)
{
    if(DEBUG_PPJPVP_ASSIGN)
        cout <<"PartialPolicyPoolInterface& PolicyPoolPartialJPolValPair::operator= \
called."<<endl;
    if (this == &o) return *this;   // Gracefully handle self assignment
    const PolicyPoolPartialJPolValPair& casted_o = 
        dynamic_cast<const PolicyPoolPartialJPolValPair&>(o);

    return(operator=(casted_o));

}


void PolicyPoolPartialJPolValPair::Init(const Interface_ProblemToPolicyDiscretePure* pu)
{
    //start with a horizon 0 joint policy - i.e. specifying 0 actions
#if 0 // old code, now we can specify the depth in the constructors,
      // which prevents us from allocating huge vectors in case of
      // high horizons
    PartialJointPolicyPureVector* jpol_empty = 
        new PartialJointPolicyPureVector(*pu, OHIST_INDEX, 0.0); 
    jpol_empty->SetDepth(0);
#else
    PartialJointPolicyPureVector* jpol_empty = 
        new PartialJointPolicyPureVector(*pu, OHIST_INDEX, 0.0, 0); 
#endif
    PartialJPDPValuePair* jpv_empty = new PartialJPDPValuePair(*jpol_empty, DBL_MAX); 
    _m_jpvpQueue_p->push(jpv_empty);
    //JPolValPool_p->push(jpv_empty);
}

PartialPolicyPoolItemInterface* PolicyPoolPartialJPolValPair::Select() const
{
    if(_m_jpvpQueue_p->size() > 0)
    {
        PartialPolicyPoolItemInterface* ppi = (PartialPolicyPoolItemInterface* ) 
            _m_jpvpQueue_p->top();
        return(ppi);
    }
    else
        throw E("Pool empty!");

}
void PolicyPoolPartialJPolValPair::Pop()
{
    _m_jpvpQueue_p->pop();
}


void PolicyPoolPartialJPolValPair::Insert(PartialPolicyPoolItemInterface*  ppi)
{
    PartialJPDPValuePair* jp = dynamic_cast<PartialJPDPValuePair*>(ppi);

    if(jp==0)
         throw(E("PolicyPoolPartialJPolValPair::Insert could not cast input to PartialJPDPValuePair"));
       
    _m_jpvpQueue_p->push(jp);
    
}

void PolicyPoolPartialJPolValPair::Union(PartialPolicyPoolInterface*  o_ppi)
{
    PolicyPoolPartialJPolValPair * o = dynamic_cast<PolicyPoolPartialJPolValPair *>(o_ppi);

    if(o==0)
        throw(E("PolicyPoolPartialJPolValPair::Union could not cast input to PolicyPoolPartialJPolValPair"));

    while(o->_m_jpvpQueue_p->size() > 0)
    {
        this->_m_jpvpQueue_p->push(o->_m_jpvpQueue_p->top());
        o->_m_jpvpQueue_p->pop();
    }
}

void PolicyPoolPartialJPolValPair::Prune(double v)
{
     priority_queue<PartialJPDPValuePair*> * new_jpvpQueue_p = 
         new priority_queue<PartialJPDPValuePair*>;

     while(_m_jpvpQueue_p->size() > 0)
     {
         PartialJPDPValuePair* jpvp = _m_jpvpQueue_p->top();
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
