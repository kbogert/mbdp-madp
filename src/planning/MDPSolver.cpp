/**\file MDPSolver.cpp
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
 * $Id: MDPSolver.cpp 2962 2008-11-02 15:04:43Z mtjspaan $
 */

#include "MDPSolver.h"
#include <float.h>
#include <fstream>
#include <limits.h>
#include "PlanningUnitDecPOMDPDiscrete.h"
#include "JointBeliefInterface.h"
#include "JointAction.h"
#include "State.h"
#include "BeliefIteratorGeneric.h"

using namespace std;

//Destructor
MDPSolver::~MDPSolver()
{
}

double MDPSolver::GetQ(Index time_step, const JointBeliefInterface& jb,
                       Index jaI) const
{
    double Q = 0.0;
#if USE_BeliefIteratorGeneric
    BeliefIteratorGeneric it=jb.GetIterator();
    do Q+=it.GetProbability() * GetQ(time_step,it.GetStateIndex(),jaI);
    while(it.Next());
#else
    for(Index sI=0; sI < jb.Size(); sI++)
        Q += jb.Get(sI) * GetQ(time_step,sI,jaI);
#endif
    return(Q);
}

double MDPSolver::GetQ(const JointBeliefInterface& jb,
                       Index jaI) const
{
    double Q = 0.0;
#if USE_BeliefIteratorGeneric
    BeliefIteratorGeneric it=jb.GetIterator();
    do Q+=it.GetProbability() * GetQ(it.GetStateIndex(),jaI);
    while(it.Next());
#else
    for(Index sI=0; sI < jb.Size(); sI++)
        Q += jb.Get(sI) * GetQ(sI,jaI);
#endif

    return(Q);
}

void MDPSolver::Print() const
{
    size_t horizon = GetPU()->GetHorizon();
    size_t nrS = GetPU()->GetNrStates();
    size_t nrJA =  GetPU()->GetNrJointActions();

    cout << "States: ";
    for(Index sI = 0; sI < nrS; sI++)
        cout << _m_pu->GetState(sI)->SoftPrintBrief() << " ";
    cout << endl;
        
    if(horizon!=MAXHORIZON)
    {
        for(size_t t = 0; t!=horizon; t++)
            for(Index jaI = 0; jaI < nrJA; jaI++)
            {            
                cout << "Q(t=" << t << ",:," << jaI << ") =\t";
                for(Index sI = 0; sI < nrS; sI++)
                    cout << " " << GetQ(t,sI,jaI);
                cout << " " << _m_pu->GetJointAction(jaI)->SoftPrintBrief();
                cout << endl;
            }
    }
    else
    {
        for(Index jaI = 0; jaI < nrJA; jaI++)
        {            
            cout << "Q(:," << jaI << ") =\t";
            for(Index sI = 0; sI < nrS; sI++)
                cout << " " << GetQ(sI,jaI);
            cout << " " << _m_pu->GetJointAction(jaI)->SoftPrintBrief();
            cout << endl;
        }
        
        cout << "Policy: ";
        for(Index sI = 0; sI < nrS; sI++)
        {
            cout << _m_pu->GetState(sI)->SoftPrintBrief() << "->";
            double q,v=-DBL_MAX;
            Index aMax=INT_MAX;

            for(Index jaI = 0; jaI < nrJA; jaI++)
            {
                q=GetQ(sI,jaI);
                if(q>v)
                {
                    v=q;
                    aMax=jaI;
                }
            }
            cout << _m_pu->GetJointAction(aMax)->SoftPrintBrief() << " ";
        }
        cout << endl;
    }
}

Index MDPSolver::GetMaximizingAction(Index time_step, Index sI)
{
    double q,v=-DBL_MAX;
    Index aMax=INT_MAX;

    for(size_t a=0;a!=GetPU()->GetNrJointActions();++a)
    {
        q=GetQ(time_step,sI,a);
        if(q>v)
        {
            v=q;
            aMax=a;
        }
    }

    return(aMax);
}

QTable MDPSolver::LoadQTable(string filename)
{
    return(LoadQTable(filename,
                      GetPU()->GetNrStates(),
                      GetPU()->GetNrJointActions()));
}

QTable MDPSolver::LoadQTable(string filename,
                             unsigned int nrS,
                             unsigned int nrA)
{
    const int bufsize=65536;
    char buffer[bufsize];

    ifstream fp(filename.c_str());
    if(!fp)
    {
        cerr << "MDPSolver::LoadQTable: failed to "
             << "open file " << filename << endl;            
    }

    size_t a,s;
    double q;

    QTable Q(nrS,nrA);

    s=0;
    while(!fp.getline(buffer,bufsize).eof())
    {
        istringstream is(buffer);
        a=0;
        while(is >> q)
            Q(s,a++)=q;

        if(a!=nrA)
            throw(E("MDPSolver::LoadQTable wrong number of actions"));

        s++;
    }
    
    if(s!=nrS)
        throw(E("MDPSolver::LoadQTable wrong number of states"));

    return(Q);
}

QTables MDPSolver::LoadQTables(string filename, int nrTables)
{
    return(LoadQTables(filename,
                       GetPU()->GetNrStates(),
                       GetPU()->GetNrJointActions(),
                       nrTables));
}

QTables MDPSolver::LoadQTables(string filename,
                               unsigned int nrS,
                               unsigned int nrA,
                               unsigned int nrTables)
{
    const int bufsize=65536;
    char buffer[bufsize];

    ifstream fp(filename.c_str());
    if(!fp)
    {
        cerr << "MDPSolver::LoadQTables: failed to "
             << "open file " << filename << endl;            
    }

    size_t a,s,i;
    double q;

    QTable Q(nrS,nrA);
    QTables Qs;
    for(i=0;i!=nrTables;i++)
        Qs.push_back(Q);
    
    s=0;
    i=0;
    while(!fp.getline(buffer,bufsize).eof())
    {
        istringstream is(buffer);
        a=0;
        while(is >> q)
            Qs[i](s,a++)=q;

        if(a!=nrA)
            throw(E("MDPSolver::LoadQTables wrong number of actions"));

        s++;
        if(s==nrS)
        {
            i++;
            s=0;
        }
    }
    
    if(i!=nrTables)
        throw(E("MDPSolver::LoadQTables wrong number of tables"));

    return(Qs);
}

void MDPSolver::SaveQTable(const QTable &Q, string filename)
{
    ofstream fp(filename.c_str());
    if(!fp)
    {
        stringstream ss;
        ss << "MDPSolver::SaveQTable: failed to open file " << filename << endl;
        throw E(ss.str());
    }

    fp.precision(16);

    unsigned int nrS=Q.size1(),
        nrA=Q.size2();
   
    for(unsigned int s=0;s!=nrS;++s)
    {
        for(unsigned int a=0;a!=nrA;++a)
        {
            fp << Q(s,a);
            if(a!=nrA-1)
                fp << " ";
        }
        fp << endl;
    }
}

void MDPSolver::SaveQTables(const QTables &Qs, string filename)
{
    ofstream fp(filename.c_str());
    if(!fp)
    {
        stringstream ss;
        ss << "MDPSolver::SaveQTables: failed to open file " << filename << endl;
        throw E(ss);
    }

    fp.precision(16);

    unsigned int nrS=Qs[0].size1(),
        nrA=Qs[0].size2(),
        h=Qs.size();

    for(unsigned int k=0;k!=h;++k)
        for(unsigned int s=0;s!=nrS;++s)
        {
            for(unsigned int a=0;a!=nrA;++a)
            {
                fp << Qs[k](s,a);
                if(a!=nrA-1)
                    fp << " ";
            }
            fp << endl;
        }
}
