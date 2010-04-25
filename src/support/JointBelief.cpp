/**\file JointBelief.cpp
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
 * $Id: JointBelief.cpp 4016 2010-03-11 16:56:02Z mtjspaan $
 */

#include "JointBelief.h"
#include <float.h>
//Necessary as header file contains a forward declaration:
#include "MultiAgentDecisionProcessDiscreteInterface.h" 
#include <typeinfo>

#include "TGet.h"

using namespace std;

#define JointBelief_doSanityCheckAfterEveryUpdate 0

JointBelief::JointBelief(size_t size) :
    Belief(size)
{
}

JointBelief::JointBelief(const vector<double> &belief) :
    Belief(belief)
{
}

JointBelief::JointBelief(const JointBeliefInterface &belief) :
    Belief(belief)
{
}
JointBelief::JointBelief(const StateDistribution& belief):
    Belief(belief)
{}

//Destructor
JointBelief::~JointBelief()
{
}

JointBelief& 
JointBelief::operator= (const JointBelief& o)
{
    if (this == &o) return *this;   // Gracefully handle self assignment

    Belief::operator=(o);

    return(*this);
}

JointBeliefInterface& 
JointBelief::operator= (const JointBeliefInterface& o)
{
    //this code is called when we perform 
    // jb1 = jb2
    // and jb1 is a JointBelief (I.e., this is the operator= function of jb1
    // and *this* is a JointBelief, since we got here)
    //
    // Therefore this code assumes that jb2 (I.e., 'o') is also a JointBelief 
    // (and not a JointBeliefSparse or something like that).
    //
    // If it is something else, we get in trouble here!
    if (this == &o) return *this;   // Gracefully handle self assignment
    try{
        const JointBelief& casted_o = dynamic_cast<const JointBelief&>(o);
        return(operator=(casted_o));// call the operator= for JointBelief
    }catch(std::bad_cast bc){
        throw E("JointBelief::operator= bad_cast exception. Are you trying to assign me (a JointBelief) with some other JointBeliefInterface (e.g. JointBeliefSparse) ??");
    }

}

double JointBelief::Update(const MultiAgentDecisionProcessDiscreteInterface &pu,
                           Index lastJAI, Index newJOI)
{
    double Po_ba = 0.0; // P(o|b,a) with o=newJO
    vector<double> newJB_unnorm;
    size_t nrS = pu.GetNrStates();
    
    TGet* T = 0;
    T = pu.GetTGet();
    if(T != 0)
    {
        for(Index sI=0; sI < nrS; sI++)
        {
            //P(newJOI | lastJAI, sI) :
            double Po_as = pu.GetObservationProbability(lastJAI, sI, newJOI);
            //P(sI | b, a) = sum_(prec_s) P(sI | prec_s, a)*JB(prec_s)
            double Ps_ba = 0.0;
            //for(BScit it=_m_b.begin(); it!=_m_b.end(); ++it)
                //Ps_ba += T->Get(it.index(), lastJAI, sI) * *it;
            for(Index prec_sI=0; prec_sI < nrS; prec_sI++)
                Ps_ba += T->Get(prec_sI, lastJAI, sI) * _m_b[prec_sI];
                //Ps_ba += pu.GetTransitionProbability(prec_sI, lastJAI, sI) * 
                    //_m_b[prec_sI];

            //the new (unormalized) belief P(s,o|b,a)
            double Pso_ba = Po_as * Ps_ba;

            newJB_unnorm.push_back(Pso_ba); //unormalized new belief
            Po_ba += Pso_ba; //running sum of P(o|b,a)
        }
    }
    else 
    {
        for(Index sI=0; sI < nrS; sI++)
        {
           //P(newJOI | lastJAI, sI) :
            double Po_as = pu.GetObservationProbability(lastJAI, sI, newJOI);
            //P(sI | b, a) = sum_(prec_s) P(sI | prec_s, a)*JB(prec_s)
            double Ps_ba = 0.0;
            //for(BScit it=_m_b.begin(); it!=_m_b.end(); ++it)
                //Ps_ba += T->Get(it.index(), lastJAI, sI) * *it;
            for(Index prec_sI=0; prec_sI < nrS; prec_sI++)
                Ps_ba += pu.GetTransitionProbability(prec_sI, lastJAI, sI) * 
                    _m_b[prec_sI];

            //the new (unormalized) belief P(s,o|b,a)
            double Pso_ba = Po_as * Ps_ba;

            newJB_unnorm.push_back(Pso_ba); //unormalized new belief
            Po_ba += Pso_ba; //running sum of P(o|b,a)
        }
        //throw E("JointBelief::Update tried to obtain a TGet, but apparently the transition model is not cached? (it should be, since this belief update loops over all states it should be possible to cache the transition model)");
    }
   
    //normalize:
    if(Po_ba>0)
        for(Index sI=0; sI < nrS; sI++)
            _m_b[sI]=newJB_unnorm[sI]/Po_ba;

    delete T;

#if JointBelief_doSanityCheckAfterEveryUpdate
    if(!SanityCheck())
        throw(E("JointBelief::Update SanityCheck failed"));
#endif

    return(Po_ba);
}
