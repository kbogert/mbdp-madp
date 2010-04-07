/**\file TransitionObservationIndependentMADPDiscrete.cpp
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
 * $Id: TransitionObservationIndependentMADPDiscrete.cpp 3611 2009-08-25 15:02:24Z mtjspaan $
 */

#include "TransitionObservationIndependentMADPDiscrete.h"    
#include "TransitionModelMappingSparse.h"
#include "TransitionModelMapping.h"
#include "ObservationModelMappingSparse.h"
#include "ObservationModelMapping.h"
#include "TGet.h"
#include "OGet.h"

#include "VectorTools.h"

using namespace std;

#define DEBUG_TOIMADPD 0
#define DEBUG_CJA 0
#define DEBUG_CJO 0

TransitionObservationIndependentMADPDiscrete::
TransitionObservationIndependentMADPDiscrete(
        string name, string descr, string pf) :
    MultiAgentDecisionProcess(name, descr, pf)
{
    _m_initialized = false;
    _m_sparse = false;
    _m_noJointModels = false;
    _m_nrJointActions=0;
    _m_nrJointStates=0;
    _m_nrJointObservations=0;
    _m_p_tModel = 0;
    _m_p_oModel = 0;
    // these are pointers to get around the const-ness of their Get functions
    _m_jointStatesMap=new map<vector<Index>, State*>;
    _m_indivStateIndicesMap = new map< Index, vector<Index> >;
    _m_jointActionMap=new map<Index, JointActionDiscrete*>;
    _m_jointObsMap=new map<Index, JointObservationDiscrete*>;
    _m_initialStateDistribution=0;
}

TransitionObservationIndependentMADPDiscrete::
TransitionObservationIndependentMADPDiscrete(
    const TransitionObservationIndependentMADPDiscrete&)
{
    throw(E("TransitionObservationIndependentMADPDiscrete: copy ctor not implemented"));
}

TransitionObservationIndependentMADPDiscrete::
~TransitionObservationIndependentMADPDiscrete()
{
    // this destructor leaks memory

    vector<MultiAgentDecisionProcessDiscrete*>::iterator it = 
        _m_individualMADPDs.begin();
    vector<MultiAgentDecisionProcessDiscrete*>::iterator last = 
        _m_individualMADPDs.end();
    while(it != last)
    {
        delete *it;//pointer to MultiAgentDecisionProcessDiscrete
        it++;
    }
    _m_individualMADPDs.clear();
    
    vector<JointActionDiscrete*>::iterator it2 = 
        _m_jointActionVec.begin();
    vector<JointActionDiscrete*>::iterator last2 = 
        _m_jointActionVec.end();
    while(it2 != last2)
    {
        delete *it2; //pointer to MultiAgentDecisionProcessDiscrete
        it2++;
    }
    _m_jointActionVec.clear();
}


void TransitionObservationIndependentMADPDiscrete::SetNrAgents(size_t n)
{
    MultiAgentDecisionProcess::SetNrAgents(n);
    vector<MultiAgentDecisionProcessDiscrete*>::iterator it =  
        _m_individualMADPDs.begin();
    vector<MultiAgentDecisionProcessDiscrete*>::iterator last =  
        _m_individualMADPDs.end();
    while(it != last)
    {
        delete (*it);
        it++;
    }

    _m_individualMADPDs.clear();
    for(Index i=0; i < n; i++)
    {
        stringstream name, descr, pf;
        name << "Indiv.MADPDiscr.Agent"<<i;
        descr << "The individual MADPDiscrete used to model the transition \
and observation dynamics for agent "<<i;
        pf << GetProblemFile() << ".agent" << i;

        MultiAgentDecisionProcessDiscrete* m = new 
            MultiAgentDecisionProcessDiscrete(1, 0, name.str(), descr.str(),
                   pf.str() );
        m->SetSparse(_m_sparse);
        _m_individualMADPDs.push_back( m );
    }

    SetInitialized(false);
}

void TransitionObservationIndependentMADPDiscrete::AddAgent(string namestring)
{
    Index i = GetNrAgents();//the old number of agents
    MultiAgentDecisionProcess::AddAgent(namestring);

    stringstream name, descr, pf;
    name << "Indiv.MADPDiscr.Agent"<<i;
    descr << "The individual MADPDiscrete used to model the transition \
and observation dynamics for agent "<<namestring <<"(agent "<<i<<")";
    pf << GetProblemFile() << ".agent" << i;

    MultiAgentDecisionProcessDiscrete* m = new 
        MultiAgentDecisionProcessDiscrete(1, 0, name.str(), descr.str(),
               pf.str() );
    m->SetSparse(_m_sparse);
    _m_individualMADPDs.push_back( m );

    SetInitialized(false);
}

void TransitionObservationIndependentMADPDiscrete::SetNrStates(Index agentI, size_t nr)
{
    if(agentI >= _m_individualMADPDs.size())
        throw EInvalidIndex("TransitionObservationIndependentMADPDiscrete::SetNrStates - agentI out of bounds...");
    _m_individualMADPDs[agentI]->SetNrStates(nr);    
}
void TransitionObservationIndependentMADPDiscrete::AddState(Index agentI, string name)
{
    if(agentI >= _m_individualMADPDs.size())
        throw EInvalidIndex("TransitionObservationIndependentMADPDiscrete::AddState - agentI out of bounds...");
    _m_individualMADPDs[agentI]->AddState(name);    
}

void TransitionObservationIndependentMADPDiscrete::SetNrActions(Index agentI, size_t nr)
{
    if(agentI >= _m_individualMADPDs.size())
        throw EInvalidIndex("TransitionObservationIndependentMADPDiscrete::SetNrActions - agentI out of bounds...");
    _m_individualMADPDs[agentI]->SetNrActions(0, nr);    
}

void TransitionObservationIndependentMADPDiscrete::AddAction(Index agentI, string name)
{
    if(agentI >= _m_individualMADPDs.size())
        throw EInvalidIndex("TransitionObservationIndependentMADPDiscrete::AddAction - agentI out of bounds...");
    _m_individualMADPDs[agentI]->AddAction(0, name);    
}

void TransitionObservationIndependentMADPDiscrete::SetNrObservations(Index agentI, size_t nr)
{
    if(agentI >= _m_individualMADPDs.size())
        throw EInvalidIndex("TransitionObservationIndependentMADPDiscrete::SetNrObservations - agentI out of bounds...");
    _m_individualMADPDs[agentI]->SetNrObservations(0, nr);    
}

void TransitionObservationIndependentMADPDiscrete::AddObservation(Index agentI, string name)
{
    if(agentI >= _m_individualMADPDs.size())
        throw EInvalidIndex("TransitionObservationIndependentMADPDiscrete::AddObservation - agentI out of bounds...");
    _m_individualMADPDs[agentI]->AddObservation(0, name);    
}

#if 0 // will be computed from individual ISDs
void TransitionObservationIndependentMADPDiscrete::SetUniformISD()
{
    size_t nrJS =  GetNrJointStates();
    if(_m_initialStateDistribution->size() != nrJS)
        _m_initialStateDistribution->resize(nrJS);
    double uprob = 1.0 / nrJS;
    vector<double>::iterator it = _m_initialStateDistribution->begin();
    vector<double>::iterator last = _m_initialStateDistribution->end();
    while(it!=last)
    {
        *it = uprob;
        it++;
    }
}
#endif

void  TransitionObservationIndependentMADPDiscrete::SetISD(const vector<double> &v)
{
    if(_m_nrJointStates==0)
        throw(E("TransitionObservationIndependentMADPDiscrete::CreateISD() joint states should have been created already"));
    
    if(v.size() != _m_nrJointStates)
        throw E("TransitionObservationIndependentMADPDiscrete::SetISD - ERROR: nrStates don't match!");

    delete _m_initialStateDistribution;
    _m_initialStateDistribution = new StateDistributionVector(v);
}

void TransitionObservationIndependentMADPDiscrete::CreateJointActions()
{
    _m_jointActionVec.clear();
    if(_m_noJointModels)
    {
        _m_nrJointActions=1;
        for(Index agI = 0; agI < GetNrAgents(); agI++)
            _m_nrJointActions*=(GetIndividualMADPD(agI)->GetNrActions(0));
    }
    else
    {
        JointActionDiscrete* ja = new JointActionDiscrete();
        _m_nrJointActions = CreateJointActionsRecursively(0, *ja, 0);

        if(_m_nrJointActions!=_m_jointActionVec.size())
            throw(E("TransitionObservationIndependentMADPDiscrete::CreateJointActions() sizes do not match"));
    }

    _m_nrIndivActions.clear();
    for(Index agI = 0; agI < GetNrAgents(); agI++)
        _m_nrIndivActions.push_back(GetIndividualMADPD(agI)->GetNrActions(0));

    for(Index ja=0;ja!=_m_nrJointActions;++ja)
        _m_jointToIndActionCache.push_back(
            JointToIndividualActionIndicesNoCache(ja));
}

size_t TransitionObservationIndependentMADPDiscrete::
CreateJointActionsRecursively(Index curAgentI, JointActionDiscrete& ja, 
        Index jaI)
{
if(DEBUG_CJA)    cerr << "TransitionObservationIndependentMADPDiscrete::CreateJointActions(Index "<<curAgentI<<", JointActionDiscrete& ja, Index "<< jaI<<") called"<<endl;

    bool lastAgent=false;
    if(curAgentI == _m_nrAgents-1)
    {
        lastAgent = true;    
        if(DEBUG_CJA)     cerr << "\nlast agent\n";
    }

    //we are going to walk through this agents action vector
    size_t nrA = GetNrActions(curAgentI);
    
    //first action extends the received ja 
    JointActionDiscrete* p_jaReceivedArgCopy = new JointActionDiscrete(ja);
    JointActionDiscrete* p_ja;
    
    for(Index a=0; a < nrA; a++)
    {
        const ActionDiscrete * adp = GetIndividualMADPD(curAgentI)->
            GetActionDiscrete(0, a);
        if(DEBUG_CJA) cerr << "\nnext action";
//        if(it == first) //
        if(a == 0)      
        {
            if(DEBUG_CJA) cerr << "(first action - not making copy)\n";
            p_ja = &ja;
        }
        else if ( a == nrA-1 )//it == beforelast)
            //this is the last last action   
        {
            if(DEBUG_CJA) cerr << "(last action - not making copy)\n";
            p_ja = p_jaReceivedArgCopy; //don't make a new copy
        }
        else //make a new copy
        {        
            if(DEBUG_CJA) cerr << "(intermed. action - making copy)\n";
            p_ja = new JointActionDiscrete(*p_jaReceivedArgCopy);    
        }    
        if(lastAgent)
        {
            p_ja->SetIndex(jaI);
            if(DEBUG_CJA)cerr << "setting index of this joint action to: "<< 
                jaI <<endl;
        }
//        ActionDiscrete* adp = /*(ActionDiscrete*)*/ &(*it);
        if(DEBUG_CJA)
            cerr <<"Adding agent's indiv. action to joint action..."<<endl;
        p_ja->AddIndividualAction(adp, curAgentI);        
        if(lastAgent) //jointAction is now completed: add it to jointAction set.
        {
            if(DEBUG_CJA){cerr << "INSERTING the joint action:"; 
                p_ja->Print();cerr<<endl;}
            _m_jointActionVec.push_back(p_ja);
            if(DEBUG_CJA){cerr << "\nINSERTED the joint action."<<endl;
                cerr << "_m_jointActionVec now containts "<< 
                _m_jointActionVec.size() << " joint actions." << endl;}
            jaI++;
        }
        else
            jaI = CreateJointActionsRecursively(curAgentI+1,*p_ja, jaI);
        
//        it++;
    }
    if(DEBUG_CJA)    cerr << ">>ProblemDecTiger::CreateJointActionsRecursively(Index "<<curAgentI<<", JointActionDiscrete& ja, Index "<< jaI<<") FINISHED"<<endl;
    return jaI;
}


void TransitionObservationIndependentMADPDiscrete::CreateJointStates()
{
    _m_jointStates.clear();
    size_t nrAg = GetNrAgents();
    _m_nrIndivStates.clear();
    _m_nrJointStates=1;
    for(Index agI = 0; agI < nrAg; agI++)
    {
        size_t nrS = GetIndividualMADPD(agI)->GetNrStates();
        _m_nrIndivStates.push_back(nrS);
        _m_nrJointStates*=nrS;
    }
    if(!_m_noJointModels)
    {
        vector<Index> ind_sI(nrAg, 0);
        size_t i=0;
        do
        {
            _m_indivStateIndices.push_back(ind_sI);
            State *state=new StateDiscrete(i);
            string name="";
            for(Index agI = 0; agI < nrAg; agI++)
            {
                if(agI>0)
                    name+="_";
                name+=GetIndividualMADPD(agI)->GetState(ind_sI[agI])->GetName();
            }
            state->SetName(name);
            state->SetDescription("");
            _m_jointStates.push_back(state);
            i++;
        } while(! IndexTools::Increment(ind_sI, _m_nrIndivStates) );
        
        if(_m_nrJointStates!=_m_jointStates.size())
            throw(E("TransitionObservationIndependentMADPDiscrete::CreateJointStates() sizes do not match"));
    }
}

const State* 
TransitionObservationIndependentMADPDiscrete::GetState(Index i) const
{
    if(!_m_noJointModels) // we cached all joint states
        return(_m_jointStates.at(i));
    else
        return(GetState(JointToIndividualStateIndices(i)));
}

const State* TransitionObservationIndependentMADPDiscrete::GetState(
    const std::vector<Index> &sIs) const
{
    // we cached the ones already asked for
    if(_m_jointStatesMap->find(sIs)!=_m_jointStatesMap->end())
        return(_m_jointStatesMap->find(sIs)->second);
    else // create new joint state and add it to cache
    {
        State *state=new State; // not a StateDiscrete, since the
                                // index might overflow
        string name="";
        for(Index agI = 0; agI < GetNrAgents(); agI++)
        {
            if(agI>0)
                name+="_";
            name+=GetIndividualMADPD(agI)->GetState(sIs[agI])->GetName();
        }
        state->SetName(name);
        state->SetDescription("");
        _m_jointStatesMap->insert(make_pair(sIs,state));
        return(state);
    }

}

const JointActionDiscrete* 
TransitionObservationIndependentMADPDiscrete::GetJointActionDiscrete(Index i) const
{
    if(!_m_noJointModels) // we cached all joint actions
        return(_m_jointActionVec.at(i));
    // we cached the ones already asked for
    else if(_m_jointActionMap->find(i)!=_m_jointActionMap->end())
        return(_m_jointActionMap->find(i)->second);
    else // create new joint action and add it to cache
    {
        JointActionDiscrete *action=new JointActionDiscrete(i);
        vector<Index> ind_sI=
            IndexTools::JointToIndividualIndices(i,_m_nrIndivActions);
        for(Index agI = 0; agI < GetNrAgents(); agI++)
            action->AddIndividualAction(
                GetIndividualMADPD(agI)->GetActionDiscrete(0,ind_sI[agI]),
                agI);
        
        _m_jointActionMap->insert(make_pair(i,action));
        return(action);
    }
}

const JointObservation* 
TransitionObservationIndependentMADPDiscrete::GetJointObservation(Index i) const
{
    if(!_m_noJointModels) // we cached all joint obs
        return(_m_jointObs.at(i));
    // we cached the ones already asked for
    else if(_m_jointObsMap->find(i)!=_m_jointObsMap->end())
        return(_m_jointObsMap->find(i)->second);
    else // create new joint obs and add it to cache
    {
        JointObservationDiscrete *observation=new JointObservationDiscrete(i);
        vector<Index> ind_sI=
            IndexTools::JointToIndividualIndices(i,_m_nrIndivObs);
        for(Index agI = 0; agI < GetNrAgents(); agI++)
            observation->AddIndividualObservation(
                GetIndividualMADPD(agI)->GetObservationDiscrete(0,ind_sI[agI]),
                agI);
        
        _m_jointObsMap->insert(make_pair(i,observation));
        return(observation);
    }
}

const std::vector<Index>&
TransitionObservationIndependentMADPDiscrete::
JointToIndividualStateIndices(Index jointSI) const
{
    if(!_m_noJointModels)
        return _m_indivStateIndices[jointSI];
    else if (_m_indivStateIndicesMap->find(jointSI)!=
             _m_indivStateIndicesMap->end())
        return(_m_indivStateIndicesMap->find(jointSI)->second);
    else
    {
        vector<Index> ind_sI=
            IndexTools::JointToIndividualIndices(jointSI,_m_nrIndivStates);
        _m_indivStateIndicesMap->insert(make_pair(jointSI,ind_sI));
        return(_m_indivStateIndicesMap->find(jointSI)->second);
    }
}

void TransitionObservationIndependentMADPDiscrete::CreateJointObservations()
{
    _m_jointObs.clear();
    size_t nrAg = GetNrAgents();
    _m_nrIndivObs.clear();
    for(Index agI = 0; agI < nrAg; agI++)
    {
        size_t nrO = GetIndividualMADPD(agI)->GetNrObservations(0);
        _m_nrIndivObs.push_back(nrO);
    }

    for(Index agI = 0; agI < nrAg; agI++)
    {
        vector<ObservationDiscrete> indObs;
        for(Index o=0; o!=GetIndividualMADPD(agI)->GetNrObservations(0); ++o)
            indObs.push_back(*GetIndividualMADPD(agI)->
                             GetObservationDiscrete(0,o));
        _m_indivObs.push_back(indObs);
    }

    if(_m_noJointModels)
    {
        _m_nrJointObservations=1;
        for(Index agI = 0; agI < nrAg; agI++)
            _m_nrJointObservations*=GetIndividualMADPD(agI)->
                GetNrObservations(0);
    }
    else
    {
        JointObservationDiscrete* jo = new JointObservationDiscrete();
        _m_nrJointObservations=ConstructJointObservationsRecursively(0, *jo, 0);
        if(_m_nrJointObservations!=_m_jointObs.size())
            throw(E("TransitionObservationIndependentMADPDiscrete::CreateJointObservations() sizes do not match"));

    for(Index jo=0;jo!=_m_nrJointObservations;++jo)
        _m_jointToIndObsCache.push_back(
            JointToIndividualObservationIndicesNoCache(jo));
    }
}

size_t TransitionObservationIndependentMADPDiscrete::
ConstructJointObservationsRecursively( 
    Index curAgentI, JointObservationDiscrete& jo, Index joI)
{
    bool lastAgent=false;
    if(curAgentI == GetNrAgents()-1)
    {
        lastAgent = true;    
    }    
    if(curAgentI >= _m_indivObs.size())
    {
        stringstream ss;
        ss << "ConstructJointObservationsRecursively - current Agent index ("<<
            curAgentI<<") out of bounds! (_m_indivObs contains "<<
            "observations for "<<_m_indivObs.size() << " agents...)\n";
        throw E(ss.str().c_str());
    }
    ObservationDVec::iterator first = _m_indivObs[curAgentI].begin();
    ObservationDVec::iterator it = _m_indivObs[curAgentI].begin();
    ObservationDVec::iterator last = _m_indivObs[curAgentI].end();
    ObservationDVec::iterator beforelast = _m_indivObs[curAgentI].end();
    beforelast--;

    if(it == last)
    {
        stringstream ss;
            ss << " empty observation set for agent " << curAgentI;
        throw E(ss);
    }
    //first observation extends the received jo 
    JointObservationDiscrete* p_joReceivedArgCopy =
        new JointObservationDiscrete(jo);
    JointObservationDiscrete* p_jo;
        
    while( it != last) // other observations extend duplicates of jo
    {
        if(it == first) //
        {
            p_jo = &jo;
        }
        else if (it == beforelast)//this is the last valid it -> last observation   
        {
            p_jo = p_joReceivedArgCopy; //don't make a new copy
        }
        else //make a new copy
        {        
            p_jo = new JointObservationDiscrete(*p_joReceivedArgCopy);    
        }    
        if(lastAgent)
        {
            p_jo->SetIndex(joI);
            if(DEBUG_CJO)    
                cerr << "setting index of this observation to: "<< joI <<endl;
        }
        ObservationDiscrete* ai = /*(ObservationDiscrete*)*/ &(*it);
        if(DEBUG_CJO)    
            cerr << "Adding agent's indiv. observation to joint observation..."<<endl;
        p_jo->AddIndividualObservation(ai, curAgentI);
        
        if(lastAgent)//jointObservation is now completed:add it to the jointObservation set.
        {
            if(DEBUG_CJO)
            {cerr<<"INSERTING the joint observation:"; p_jo->Print();cerr<<endl;}
            _m_jointObs.push_back(p_jo);
            if(DEBUG_CJO){cerr << "\nINSERTED the joint observation"<<endl<< "_m_jointObservationVec now containts "<< _m_jointObs.size() << " joint actions." << endl;}
            joI++;
        }
        else
            joI = ConstructJointObservationsRecursively(curAgentI+1,*p_jo, joI);
        it++;
    }
    if(DEBUG_CJO)    cerr << ">> TransitionObservationIndependentMADPDiscrete::ConstructJointObservationsRecursively(Index "<<curAgentI<<", JointObservationDiscrete& jo, Index "<< joI<<") FINISHED"<<endl;
    return joI;
    
}

void TransitionObservationIndependentMADPDiscrete::CreateISD()
{
    size_t nrJS = _m_nrJointStates;
    if(nrJS==0)
        throw(E("TransitionObservationIndependentMADPDiscrete::CreateISD() joint states should have been created already"));

    //vector<vector<double> > isdIs;
    //vector< const StateDistributionVector* > isdIs;
    vector< const StateDistribution* > isdIs;

    for(Index i=0;i!=GetNrAgents();++i)
        isdIs.push_back(GetIndividualMADPD(i)->GetISD());

    if(!_m_noJointModels)
    {
        vector<double> ISD(nrJS,1);
        for(Index s=0;s!=nrJS;++s)
            for(Index i=0;i!=GetNrAgents();++i)
                ISD[s]*=  isdIs[i]->GetProbability(_m_indivStateIndices[s][i] );

        SetISD(ISD);
    }
}

bool TransitionObservationIndependentMADPDiscrete::SetInitialized(bool b)
{
    if(b == false)
    {
        if(_m_initialized == true)
            delete [] _m_actionStepSize;
        _m_initialized = false;
        return(true);
    }
    if(_m_initialized == true && b == true)
    {
        //first free mem before re-initialize:
        delete [] _m_actionStepSize;
    }

    if(DEBUG_TOIMADPD)
        cerr << "TransitionObservationIndependentMADPDiscrete::SetInitialized"<<
        " called - GetNrAgents()="<< GetNrAgents()<<endl;
    
    if(GetNrAgents() < 1 )
        throw E("TransitionObservationIndependentMADPDiscrete::SetInitialized(bool b) called, but the number of agents has not been set yet.. (is 0 at the moment...)");

    if(b == true)
    {
        //first initialize the individual models... 
        vector<MultiAgentDecisionProcessDiscrete*>::iterator it = 
            _m_individualMADPDs.begin();
        vector<MultiAgentDecisionProcessDiscrete*>::iterator last = 
            _m_individualMADPDs.end();
        while(it != last)
        {
            (*it)->Initialize();
            it++;
        }

        // most likely we will not have the memory space to store all this...
        if(GetNrAgents()>2)
            _m_noJointModels=true;
        
        //now perform the necessary actions for this class...
        CreateJointActions();
        CreateJointStates();
        CreateJointObservations();
        
        CreateISD();

        _m_nr_agents=GetNrAgents();
        _m_actionStepSize=IndexTools::CalculateStepSize(_m_nrIndivActions);
        
        _m_initialized = b;
    }
    return(true);
}

Index TransitionObservationIndependentMADPDiscrete::
IndividualToJointActionIndices(Index* IndexArray) const
{
    Index a=IndexTools::IndividualToJointIndicesArray(IndexArray,
                                                       _m_nrIndivActions);
    return(a);
}

Index TransitionObservationIndependentMADPDiscrete::
IndividualToJointActionIndices(const vector<Index>& indivActionIndices) const
{
    if(!_m_initialized)
    {
        stringstream ss;
            ss << "TransitionObservationIndependentMADPDiscrete::"<<
                "IndividualToJointActionIndices(vector<Index>&)"<<
                " - Error: not initialized. "<<endl;
        throw E(ss);
    }

    Index i = IndexTools::IndividualToJointIndices(indivActionIndices,
                                                   _m_nrIndivActions);
    return(i);
}

vector<Index> TransitionObservationIndependentMADPDiscrete::
JointToIndividualActionIndicesNoCache(Index jaI) const
{
#if 0
    if(!_m_initialized)
    {
    stringstream ss;
        ss << "TransitionObservationIndependentMADPDiscrete::"<<
            "JointToIndividualActionIndices("<< jaI<<
            ") - Error: not initialized. "<<endl;
    throw E(ss);
    }
#endif
#if 0
    const JointActionDiscrete* jai = GetJointActionDiscrete(jaI);
    vector<Index> vai = jai->GetIndividualActionDiscretesIndices();
#endif
    vector<Index> vai=IndexTools::JointToIndividualIndices(jaI,
                                                           _m_nrIndivActions);

    if(DEBUG_TOIMADPD)
    {    
        cerr << "TransitionObservationIndependentMADPDiscrete::"<<
            "JointToIndividualActionIndices"<< "(Index "<<jaI<<")" << endl <<
            "vai.size() = " <<vai.size() << " - elements: "<<endl;
        vector<Index>::iterator vai_it = vai.begin();
        vector<Index>::iterator vai_last = vai.end();
        while(vai_it != vai_last)
        {
            cerr << ", " << *vai_it;
            vai_it++;
        }
        cerr << endl;
    }
    return(vai);
}

Index TransitionObservationIndependentMADPDiscrete::
IndividualToJointObservationIndices(const vector<Index>& 
                                    indivObsIndices) const
{
    if(!_m_initialized)
    {
        stringstream ss;
        ss << "TransitionObservationIndependentMADPDiscrete::"<<
            "IndividualToJointObservationIndices(const vector<Index>)"<<
            " - Error: not initialized. "<<endl;
        throw E(ss);
    }

    vector<size_t> nrO;
    for(Index agI=0; agI < GetNrAgents(); agI++)
        nrO.push_back(GetNrObservations(agI));

    Index i = IndexTools::IndividualToJointIndices(indivObsIndices,nrO);

    return(i);
}

vector<Index> TransitionObservationIndependentMADPDiscrete::
JointToIndividualObservationIndicesNoCache(Index joI) const
{
#if 0
    if(!_m_initialized)
    {
        stringstream ss;
        ss << "TransitionObservationIndependentMADPDiscrete::"<<
            "JointToIndividualObservationIndices("<< joI<<
            ") - Error: not initialized. "<<endl;
        throw E(ss);
    }
#endif
    vector<size_t> nrO;
    for(Index agI=0; agI < GetNrAgents(); agI++)
        nrO.push_back(GetNrObservations(agI));
    vector<Index> voi =
        IndexTools::JointToIndividualIndices(joI,nrO);
    if(DEBUG_TOIMADPD)
    {    
        cerr << "TransitionObservationIndependentMADPDiscrete::"<<
            "JointToIndividualActionIndices"<< "(Index "<<joI<<")" << endl <<
            "voi.size() = " <<voi.size() << " - elements: "<<endl;
        vector<Index>::iterator voi_it = voi.begin();
        vector<Index>::iterator voi_last = voi.end();
        while(voi_it != voi_last)
        {
            cerr << ", " << *voi_it;
            voi_it++;
        }
        cerr << endl;
    }
    return(voi);
}

Index TransitionObservationIndependentMADPDiscrete::
IndividualToJointStateIndices(const vector<Index>& indivStateIndices) const
{
    return(IndexTools::IndividualToJointIndices(indivStateIndices,
                                                _m_nrIndivStates));
}

string TransitionObservationIndependentMADPDiscrete::SoftPrint() const
{    
    stringstream str;
    str << MultiAgentDecisionProcess::SoftPrint();
    if(!_m_initialized)
    {
        stringstream ss;
            ss << "TransitionObservationIndependentMADPDiscrete::Print("<< 
            ") - Error: not initialized. "<<endl;
        throw E(ss);
    }
    str << "#joint states=" << GetNrJointStates() << endl;
    str << "#joint actions="<<GetNrJointActions()<<endl;
    str << "#joint observations="<<GetNrJointObservations()<<endl;
    str << SoftPrintActionSets();
    str << "Joint Actions:"<<endl;
    str << SoftPrintJointActionSet();
    //print the individual MADPs
    str << "Individual MADPs for each agent:"<<endl;
    for(Index agI=0; agI < GetNrAgents(); agI++)
        str << "Agent "<< agI << ":" <<endl << 
            GetIndividualMADPD(agI)->SoftPrint();
    
    return(str.str());
}

string TransitionObservationIndependentMADPDiscrete::SoftPrintActionSets() const
{
    stringstream str;
    if(!_m_initialized)
    {
        stringstream ss;
            ss << "TransitionObservationIndependentMADPDiscrete::PrintAction"<<
                "Sets() - Error: not initialized. "<<endl;
        throw E(ss);
    }    
    str << "Actions:"<<endl;
    for(Index agentIndex=0; agentIndex < _m_nrAgents; agentIndex++)
    {
        str << "agentI " << agentIndex << " - nrActions " << 
            GetNrActions(agentIndex)<<endl; 
        for(Index actionI=0; actionI < GetNrActions(agentIndex); actionI++)
        {

            const ActionDiscrete * adp = GetIndividualMADPD(agentIndex)->
                GetActionDiscrete(0, actionI);
            str << adp->SoftPrint();
            str << endl;
        }
    }
    return(str.str());
}

string TransitionObservationIndependentMADPDiscrete::SoftPrintJointActionSet() 
    const
{
    stringstream str;
    if(!_m_initialized)
    {
        stringstream ss;
            ss << "TransitionObservationIndependentMADPDiscrete::PrintJoint"<<
                "ActionSets() - Error: not initialized. "<<endl;
        throw E(ss);
    }   
    vector<JointActionDiscrete*>::const_iterator ja_it = 
        _m_jointActionVec.begin();
    vector<JointActionDiscrete*>::const_iterator ja_last = 
        _m_jointActionVec.end();
    while(ja_it != ja_last)
    {
        str << (*ja_it)->SoftPrint();
        str<<endl;
        ja_it++;    
    }
    return(str.str());
}

string
TransitionObservationIndependentMADPDiscrete::SoftPrintState(Index sI) const
{
    vector<Index> sIs=JointToIndividualStateIndices(sI);
    stringstream ss;
    for(Index agI = 0; agI < sIs.size(); agI++)
        ss << GetIndividualMADPD(agI)->SoftPrintState(sIs[agI]);
    return(ss.str());
}


double TransitionObservationIndependentMADPDiscrete::
GetTransitionProbability(Index sI,
                         Index jaI,
                         Index sucSI) const
{
    double p=1;
    if(_m_noJointModels)
    {
        vector<Index> sIs=JointToIndividualStateIndices(sI),
            sucSIs=JointToIndividualStateIndices(sucSI);
        vector<Index> aIs=JointToIndividualActionIndices(jaI);
        for(Index agI = 0; agI < GetNrAgents(); agI++)
        {
            p*=GetIndividualMADPD(agI)->GetTransitionProbability(
                sIs[agI],
                aIs[agI],
                sucSIs[agI]);
            if(p==0)
                break;
        }
    }
    else
    {
        for(Index agI = 0; agI < GetNrAgents(); agI++)
        {
            p*=GetIndividualMADPD(agI)->GetTransitionProbability(
                _m_indivStateIndices[sI][agI],
                _m_jointToIndActionCache[jaI][agI],
                _m_indivStateIndices[sucSI][agI]);
            if(p==0)
                break;
        }
    }
    return(p);
}

double TransitionObservationIndependentMADPDiscrete::
GetTransitionProbability(const vector<Index> &sIs,
                         const vector<Index> &aIs,
                         const vector<Index> &sucSIs) const
{
    double p=1;
    for(Index agI = 0; agI < GetNrAgents(); agI++)
    {
        p*=GetIndividualMADPD(agI)->GetTransitionProbability(
            sIs[agI],
            aIs[agI],
            sucSIs[agI]);
        if(p==0)
                break;
    }
    return(p);
}

double TransitionObservationIndependentMADPDiscrete::
GetObservationProbability(Index jaI,
                          Index sucSI, 
                          Index joI) const
{
    double p=1;
    if(_m_noJointModels)
    {
        vector<Index> sucSIs=JointToIndividualStateIndices(sucSI);
        vector<Index> aIs=JointToIndividualActionIndices(jaI);
        vector<Index> oIs=JointToIndividualObservationIndices(joI);
        for(Index agI = 0; agI < GetNrAgents(); agI++)
        {
            p*=GetIndividualMADPD(agI)->GetObservationProbability(
                aIs[agI],
                sucSIs[agI],
                oIs[agI]);
            if(p==0)
                break;
        }
    }
    else
    {
        for(Index agI = 0; agI < GetNrAgents(); agI++)
        {
            p*=GetIndividualMADPD(agI)->GetObservationProbability(
                _m_jointToIndActionCache[jaI][agI],
                _m_indivStateIndices[sucSI][agI],
                _m_jointToIndObsCache[joI][agI]);
            if(p==0)
                break;
        }
    }
    return(p);
}

double TransitionObservationIndependentMADPDiscrete::
GetObservationProbability(const vector<Index> &aIs,
                          const vector<Index> &sucSIs, 
                          const vector<Index> &oIs) const
{
    double p=1;
    for(Index agI = 0; agI < GetNrAgents(); agI++)
    {
        p*=GetIndividualMADPD(agI)->GetObservationProbability(
            aIs[agI],
            sucSIs[agI],
            oIs[agI]);
        if(p==0)
            break;
    }
    return(p);
}

Index TransitionObservationIndependentMADPDiscrete::
SampleSuccessorState(Index sI, Index jaI) const
{
    vector<Index> sIs=JointToIndividualStateIndices(sI);
    vector<Index> aIs=JointToIndividualActionIndices(jaI);
    return(IndividualToJointStateIndices(SampleSuccessorState(sIs,aIs)));
}

vector<Index> 
TransitionObservationIndependentMADPDiscrete::SampleSuccessorState(
    const vector<Index> &sIs,
    const vector<Index> &aIs) const
{
    vector<Index> sucSIs(GetNrAgents());
    for(Index agI = 0; agI < GetNrAgents(); agI++)
        sucSIs[agI]=GetIndividualMADPD(agI)->SampleSuccessorState(sIs[agI],
                                                                  aIs[agI]);
    return(sucSIs);
}

Index TransitionObservationIndependentMADPDiscrete::
SampleJointObservation(Index jaI,
                       Index sucI) const
{
    vector<Index> sucIs=JointToIndividualStateIndices(sucI);
    vector<Index> aIs=JointToIndividualActionIndices(jaI);

    return(IndividualToJointObservationIndices(SampleJointObservation(aIs,
                                                                      sucIs)));
}

vector<Index> 
TransitionObservationIndependentMADPDiscrete::SampleJointObservation(
    const vector<Index> &aIs,
    const vector<Index> &sucIs)
    const
{
    vector<Index> oIs(GetNrAgents());

    for(Index agI = 0; agI < GetNrAgents(); agI++)
        oIs[agI]=GetIndividualMADPD(agI)->SampleJointObservation(aIs[agI],
                                                                 sucIs[agI]);
    return(oIs);
}


Index TransitionObservationIndependentMADPDiscrete::
SampleInitialState(void) const
{
    return(IndividualToJointStateIndices(SampleInitialStates()));
}

vector<Index>
TransitionObservationIndependentMADPDiscrete::SampleInitialStates(void) const
{
    vector<Index> sIs(GetNrAgents());

    for(Index agI = 0; agI < GetNrAgents(); agI++)
        sIs[agI]=GetIndividualMADPD(agI)->SampleInitialState();

    return(sIs);
}

//vector<double> TransitionObservationIndependentMADPDiscrete::GetISD() const
const StateDistributionVector* TransitionObservationIndependentMADPDiscrete::GetISD() const
{
    if(_m_noJointModels)
    {
        throw(E("TransitionObservationIndependentMADPDiscrete::GetISD initial state distribution has not been generated as a double vector."));
    }
    else
        return(_m_initialStateDistribution);
}

void TransitionObservationIndependentMADPDiscrete::SetSparse(bool sparse)
{
    _m_sparse=sparse;

    vector<MultiAgentDecisionProcessDiscrete*>::iterator it =  
        _m_individualMADPDs.begin();
    vector<MultiAgentDecisionProcessDiscrete*>::iterator last =  
        _m_individualMADPDs.end();
    while(it != last)
    {
        (*it)->SetSparse(sparse);
        it++;
    }
}

size_t TransitionObservationIndependentMADPDiscrete::GetNrJointStates() const
{
    if(!_m_initialized)
        throw(E("TransitionObservationIndependentMADPDiscrete::GetNrJointStates() not yet initialized"));
    
    return(_m_nrJointStates);
}

size_t TransitionObservationIndependentMADPDiscrete::GetNrJointActions() const
{
    if(!_m_initialized)
        throw(E("TransitionObservationIndependentMADPDiscrete::GetNrJointActions() not yet initialized"));

    return(_m_nrJointActions);
}

size_t TransitionObservationIndependentMADPDiscrete::GetNrJointObservations() const
{
    if(!_m_initialized)
        throw(E("TransitionObservationIndependentMADPDiscrete::GetNrJointObservations() not yet initialized"));

    return(_m_nrJointObservations);
}

void
TransitionObservationIndependentMADPDiscrete::CreateCentralizedSparseModels()
{
    if(!_m_initialized)
    {
        throw(E("TransitionObservationIndependentMADPDiscrete::CreateCentralizedSparseModels not initialized yet"));
        return;
    }

    _m_p_tModel = new TransitionModelMappingSparse(_m_nrJointStates,
                                                   _m_nrJointActions);
    _m_p_oModel = new ObservationModelMappingSparse(_m_nrJointStates,
                                                    _m_nrJointActions,
                                                    _m_nrJointObservations);
    double p=0;
    for(Index a=0;a!=_m_nrJointActions;++a)
        for(Index s=0;s!=_m_nrJointStates;++s)
        {
            for(Index s1=0;s1!=_m_nrJointStates;++s1)
            {
                p=GetTransitionProbability(s,a,s1);
                if(p>0)
                    _m_p_tModel->Set(s,a,s1,p);
            }

            for(Index o=0;o!=_m_nrJointObservations;++o)
            {
                p=GetObservationProbability(a,s,o);
                if(p>0)
                    _m_p_oModel->Set(a,s,o,p);
            }           
        }
}

void
TransitionObservationIndependentMADPDiscrete::CreateCentralizedFullModels()
{
    // todo: remove the overlap with CreateCentralizedSparseModels()
    if(!_m_initialized)
    {
        throw(E("TransitionObservationIndependentMADPDiscrete::CreateCentralizedFullModels not initialized yet"));
        return;
    }

    _m_p_tModel = new TransitionModelMapping(_m_nrJointStates,
                                             _m_nrJointActions);
    _m_p_oModel = new ObservationModelMapping(_m_nrJointStates,
                                              _m_nrJointActions,
                                              _m_nrJointObservations);
    double p=0;
    for(Index a=0;a!=_m_nrJointActions;++a)
        for(Index s=0;s!=_m_nrJointStates;++s)
        {
            for(Index s1=0;s1!=_m_nrJointStates;++s1)
            {
                p=GetTransitionProbability(s,a,s1);
                if(p>0)
                    _m_p_tModel->Set(s,a,s1,p);
            }

            for(Index o=0;o!=_m_nrJointObservations;++o)
            {
                p=GetObservationProbability(a,s,o);
                if(p>0)
                    _m_p_oModel->Set(a,s,o,p);
            }           
        }
}

TGet* TransitionObservationIndependentMADPDiscrete::
GetTGet() const
{    
    if(_m_noJointModels)
        return 0;

    if(_m_sparse)
        return new TGet_TransitionModelMappingSparse(
                ((TransitionModelMappingSparse*)_m_p_tModel)  ); 
    else
        return new TGet_TransitionModelMapping(
            ((TransitionModelMapping*)_m_p_tModel)  );
}

OGet* TransitionObservationIndependentMADPDiscrete::
GetOGet() const
{    
    if(_m_noJointModels)
        return 0;

    if(_m_sparse)
        return new OGet_ObservationModelMappingSparse(
                ((ObservationModelMappingSparse*)_m_p_oModel)  ); 
    else
        return new OGet_ObservationModelMapping(
            ((ObservationModelMapping*)_m_p_oModel)  );
}
