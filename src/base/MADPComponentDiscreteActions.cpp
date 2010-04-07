/**\file MADPComponentDiscreteActions.cpp
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
 * $Id: MADPComponentDiscreteActions.cpp 3598 2009-08-20 12:29:54Z mtjspaan $
 */

#include "MADPComponentDiscreteActions.h"
#include "VectorTools.h"

using namespace std;

#define DEBUG_GETJA_COPYVEC 0
#define DEBUG_CJA 0
#define DEBUG_ADD_DA 0
#define DEBUG_MADP_DA 0

//the following variable enables some runtime checks - enable it for debugging
#define RUNTIME_CHECKS 0



//Default constructor
MADPComponentDiscreteActions::MADPComponentDiscreteActions() 
{
    _m_initialized = false;
    _m_cachedAllJointActions = false;
    _m_actionStepSize = 0;
    _m_jointActionIndices=0;
    _m_jointIndicesValid=true;
}

//Destructor
MADPComponentDiscreteActions::~MADPComponentDiscreteActions()
{
    _m_nrActions.clear();
    vector<vector<ActionDiscrete> >::iterator it = _m_actionVecs.begin();
    vector<vector<ActionDiscrete> >::iterator last = _m_actionVecs.end();
    while(it != last)
    {
        // (*it) isa vector<ActionDiscrete>
        (*it).clear();
        it++;
    }
    _m_actionVecs.clear();
    vector<JointActionDiscrete*>::iterator it2 = _m_jointActionVec.begin();
    vector<JointActionDiscrete*>::iterator last2 = _m_jointActionVec.end();
    while(it2 != last2)
    {
        delete *it2; //removes the joint action pointed to...
        it2++;
    }
    _m_jointActionVec.clear();
    if(_m_jointActionIndices)
    {
        while(!_m_jointActionIndices->empty())
        {
            delete (*_m_jointActionIndices->begin()).second;
            _m_jointActionIndices->erase( _m_jointActionIndices->begin() );
        }
        delete _m_jointActionIndices;
    }
//     if(_m_jointActionIndices)
//     {
//         vector<vector<Index>*>::iterator it3 = _m_jointActionIndices->begin();
//         vector<vector<Index>*>::iterator last3 = _m_jointActionIndices->end();
//         while(it3 != last3)
//         {
//             delete *it3;
//             it3++;
//         }
//     }

    delete[] _m_actionStepSize;
}

//data manipulation (set) functions:

/** This creates nrA unnamed actions.*/
void MADPComponentDiscreteActions::SetNrActions(Index AI, size_t nrA)
{
    if(_m_nrActions.size() != AI)
    {
        stringstream ss;
        ss << "MADPComponentDiscreteActions::SetNrAction("<<AI<<","<<
            nrA<<
            ") - error, actions of agents should be specified in order!"<<
            " (the vector _m_nrActions should contain entries for all "<<
            "preceeding agents.)";
        throw(E(ss));
    }
    else
    {
        _m_nrActions.push_back(nrA);
        //create nameless actions for this agent...    
        vector<ActionDiscrete> thisAgentsActions;
        for(Index i=0;i<nrA;i++)
        {
            stringstream ss;
            ss //<< "ag"<<AI
                <<"a"<<i;
            thisAgentsActions.push_back(ActionDiscrete(i, ss.str() ));
        }
        _m_actionVecs.push_back(thisAgentsActions);
    }
}

void MADPComponentDiscreteActions::AddAction(Index AI, string name)
{
    if(DEBUG_ADD_DA)
        cerr <<  "MADPComponentDiscreteActions::AddAction("<<AI<<","<<name<<")"<<endl;

    if(_m_nrActions.size() != AI && _m_nrActions.size() != AI+1)
    {
        stringstream ss;
        ss << "MADPComponentDiscreteActions::AddAction("<<AI<<","<<name<<
            ") - error, actions of agents should be specified in order!"<<
            " first all actions of agent 1, then all of agent 2,...etc..."<<
            " _m_nrActions.size now is: "<< _m_nrActions.size() <<
            "\n(the vector _m_nrActions should contain entries for all "<<
            "preceeding agents.)";
        throw(E(ss));
    }
    if(_m_nrActions.size() == AI )
    {
        //this is the first action we add for this agent
        _m_nrActions.push_back(1);

        vector<ActionDiscrete> thisAgentsActions;
        ActionDiscrete ad(0, name);
        thisAgentsActions.push_back(ad);
        _m_actionVecs.push_back(thisAgentsActions);
    }
    else
    {
        //we add an action for this agent - increment his nr_actions
        Index newActionIndex = _m_nrActions[AI]++;
        ActionDiscrete ad(newActionIndex, name);
        _m_actionVecs[AI].push_back(ad);
    }
}

/** Calls ConstructJointActionsRecursively() on a new (empty) joint
 * action.*/
size_t MADPComponentDiscreteActions::ConstructJointActions()
{
    JointActionDiscrete* ja = new JointActionDiscrete();
    size_t NRJA = ConstructJointActionsRecursively(0, *ja, 0);
    _m_cachedAllJointActions=true;
    return NRJA; 
}

/** Creates (_m_jointActionVec) using _m_actionVecs (which need to be
 * initialized before calling this function...) */    
size_t MADPComponentDiscreteActions::ConstructJointActionsRecursively(
    Index curAgentI, JointActionDiscrete& ja, Index jaI)
{

    bool lastAgent=false;
    if(curAgentI == GetNrAgents()-1)
    {
        lastAgent = true;    
    }
    if(curAgentI >= _m_actionVecs.size())
    {
        stringstream ss;
        ss << "ConstructJointActionsRecursively - current Agent index ("<<
            curAgentI<<") out of bounds! (_m_actionVecs contains actions for "<<
            _m_actionVecs.size() << " agents...)\n";
        throw E(ss);
    }

    ActionDVec::iterator first = _m_actionVecs[curAgentI].begin();
    ActionDVec::iterator it = _m_actionVecs[curAgentI].begin();
    ActionDVec::iterator last = _m_actionVecs[curAgentI].end();
    ActionDVec::iterator beforelast = _m_actionVecs[curAgentI].end();
    beforelast--;

    if(it == last)
    {
        stringstream ss; ss << "ERROR empty action set for agent " << curAgentI;
        throw E(ss);
    }
    //first action extends the received ja 
    JointActionDiscrete* p_jaReceivedArgCopy = new JointActionDiscrete(ja);
    JointActionDiscrete* p_ja;
        
    while( it != last) // other actions extend duplicates of ja
    {
        if(DEBUG_CJA)    cerr << "\nnext action";
            if(it == first) //
            {
                if(DEBUG_CJA)        
                    cerr << "(first action - not making copy)\n";
                p_ja = &ja;
            }
        else if (it == beforelast)//this is the last valid it -> last action   
        {
            if(DEBUG_CJA)        cerr << "(last action - not making copy)\n";
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
            if(DEBUG_CJA)cerr << "setting index of this joint action to: "
                << jaI <<endl;
        }
        ActionDiscrete* ai = /*(ActionDiscrete*)*/ &(*it);
        if(DEBUG_CJA)cerr <<"Adding agent's indiv. action to joint action..."
            <<endl;
        p_ja->AddIndividualAction(ai, curAgentI);
        
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
            jaI = ConstructJointActionsRecursively(curAgentI+1,*p_ja, jaI);
        
        it++;
    }
    if(DEBUG_CJA)    
        cerr << ">>ProblemDecTiger::ConstructJointActionsRecursively(Index "<<
            curAgentI<<", JointActionDiscrete& ja, Index "<< jaI<<") FINISHED"
            <<endl;
    return jaI;
}


/** When setting to true, a verification of member elements is
 * performed. (i.e. a check whether all vectors have the correct size
 * and non-zero entries) */
bool MADPComponentDiscreteActions::SetInitialized(bool b)
{
    if(b == false)
    {
        if(_m_initialized == true)
            delete [] _m_actionStepSize;
        _m_initialized = b;
        return true;
    }
    if(_m_initialized == true && b == true)
    {
        //first free mem before re-initialize:
        delete [] _m_actionStepSize;
    }
    if(b == true)
    {
        if(_m_nrActions.size() != GetNrAgents())
            throw(E("MADPComponentDiscreteActions::SetInitialized size of _m_nrActions vector does not agree with the number of agents"));
        _m_nr_agents=GetNrAgents();
        _m_actionStepSize=IndexTools::CalculateStepSize(_m_nrActions);

        if(!_m_cachedAllJointActions)
        {
            size_t nrJA=1;
            size_t prevNrJA=nrJA;
            for(Index i=0;i!=_m_nrActions.size();++i)
            {
                nrJA*=_m_nrActions[i];
                // detect overflow
                if(nrJA<prevNrJA)
                    _m_jointIndicesValid=false;
                prevNrJA=nrJA;
            }
            _m_nrJointActions=nrJA;
            _m_jointActionIndices=
                new map<Index, vector<Index> *>();
        }
        else
            _m_nrJointActions=_m_jointActionVec.size();
        _m_initialized = b;
    }
    return(true);
}



size_t MADPComponentDiscreteActions::GetNrActions(Index agentI) const
{    
#if 0
    // this is very inconvenient: we sometimes want to get the #actions
    // before setting to initialised.
    if(!_m_initialized)
    {
        stringstream ss;
            ss << "MADPComponentDiscreteActions::GetNrActions("<< 
            agentI<<") - Error: not initialized. "<<endl;
        throw E(ss);
    }
#endif    
    size_t nrA = GetNrAgents();
    if(nrA != _m_nrActions.size())
    {
        stringstream ss;
            ss << "MADPComponentDiscreteActions::GetNrActions("<< 
            agentI<<") - Error: nrA != _m_nrActions.size() "<<endl;
        throw E(ss);
    }
    if(agentI < nrA)
        return _m_nrActions[agentI];
    else
    {
        stringstream ss;
            ss << "Warning: MADPComponentDiscreteActions::GetNrActions(Index agentI) - index out of bounds"<<endl;
        throw E(ss);
    }
}
size_t MADPComponentDiscreteActions::GetNrJointActions() const
{
    if(!_m_initialized)
    {
        stringstream ss;
            ss << "MADPComponentDiscreteActions::GetNrJointActions("<< 
            ") - Error: not initialized. "<<endl;
        throw E(ss);
    }
    if(!_m_jointIndicesValid)
    {
        throw(E("MADPComponentDiscreteActions::GetNrJointActions() joint indices are not available, overflow detected"));
    }
    return(_m_nrJointActions);
}

/** Throws an exception if there is no action with name s.*/
Index MADPComponentDiscreteActions::GetActionIndexByName(string s,
                                                          Index agentI) const
{
    if(!_m_initialized)
        throw E("MADPComponentDiscreteActions::GetActionIndexByName - not initialized!");

    if(agentI >= _m_actionVecs.size())
    {
        stringstream ss;
        ss << "GetActionIndexByName -  Agent index ("<<
            agentI<<") out of bounds! (_m_actionVecs contains actions for "<<
            _m_actionVecs.size() << " agents...)\n";
        throw E(ss);
    }
    vector<ActionDiscrete>::const_iterator it = _m_actionVecs[agentI].begin();
    vector<ActionDiscrete>::const_iterator last = _m_actionVecs[agentI].end();
    while(it != last)
    {
        string s2 = (*it).GetName();
        if(s == s2)
        //if(strcmp(s,s2) == 0)//match
            return( (*it).GetIndex() );
        it++;
    }
    //not found
    stringstream ss;
    ss << "GetActionIndexByName - action \"" << s << "\" of agent " << agentI <<
    " not found." << endl;
    throw E(ss.str().c_str());

}

const Action* MADPComponentDiscreteActions::GetAction(Index agentI, Index a) const
{
    return ((Action*) GetActionDiscrete( agentI,  a) );
}
const ActionDiscrete* MADPComponentDiscreteActions::GetActionDiscrete(Index agentI, Index a) const
{
    if(!_m_initialized)
    {
        stringstream ss;
            ss << "MADPComponentDiscreteActions::GetAction("<< 
            agentI<<") - Error: not initialized. "<<endl;
        throw E(ss);
    }
    if(agentI < GetNrAgents() )
    {
        if(a < GetNrActions(agentI) )
        {
            return (&_m_actionVecs[agentI][a]);
        }
        //else
        stringstream ss;
            ss << "WARNING MADPComponentDiscreteActions::GetAction(Index agentI, Index a) index a out of bounds"<<endl;
        throw E(ss);
    }
    //else
    stringstream ss;
    ss << "WARNING MADPComponentDiscreteActions::GetAction(Index agentI, Index a) index agentI out of bounds"<<endl;   
    throw E(ss);
}
/*return a ref to the i-th joint action.*/
const JointActionDiscrete* MADPComponentDiscreteActions::GetJointActionDiscrete(Index i) const
{
    if(!_m_initialized)
    {
        stringstream ss;
            ss << "MADPComponentDiscreteActions::GetJointActionDiscrete("<< 
            i<<") - Error: not initialized. "<<endl;
        throw E(ss);
    }
    if(!_m_cachedAllJointActions)
    {
        throw E("MADPComponentDiscreteActions::GetJointActionDiscrete: joint actions have not been created");
    }
    if(i < _m_jointActionVec.size() )
    {
        const JointActionDiscrete* j = _m_jointActionVec[i];
        return( j );
    }
    //else        
    stringstream ss;
    ss << "WARNING MADPComponentDiscreteActions::GetJointActionDiscrete(Index i) index a out of bounds"<<endl;
    throw E(ss);
}
/*return a ref to the i-th joint action.*/
const JointAction* MADPComponentDiscreteActions::GetJointAction(Index i) const
{
    if(!_m_initialized)
    {
        stringstream ss;
            ss << "MADPComponentDiscreteActions::GetJointAction("<< 
            i<<") - Error: not initialized. "<<endl;
            throw E(ss);
    }
    if(!_m_cachedAllJointActions)
    {
        throw E("MADPComponentDiscreteActions::GetJointActionDiscrete: joint actions have not been created");
    }
    if(i < _m_jointActionVec.size() )
        return( (const JointAction*) _m_jointActionVec[i] );
    //else        
    stringstream ss;
    ss << "WARNING MADPComponentDiscreteActions::GetJointAction(Index i) index a out of bounds"<<endl;
    throw E(ss);
}

Index MADPComponentDiscreteActions::IndividualToJointActionIndices(
        const vector<Index>& indivActionIndices)const
{
#if RUNTIME_CHECKS
    if(!_m_initialized)
    {
        stringstream ss;
            ss << "MADPComponentDiscreteActions::GetJointActionIndex("<< 
            "vector<Index>& indivActionIndices) -Error: not initialized."<<endl;
        throw E(ss);
    }
#endif                 
    Index i = IndexTools::IndividualToJointIndicesStepSize(indivActionIndices,
            _m_actionStepSize);

    return(i);
}

string MADPComponentDiscreteActions::SoftPrint() const
{
    stringstream ss;
    if(DEBUG_MADP_DA){ss << "MADPComponentDiscreteActions::Print()" << endl;}
    if(!_m_initialized)
    {
        stringstream ss;
            ss << "MADPComponentDiscreteActions::Print("<< 
            ") - Error: not initialized. "<<endl;
        throw E(ss);
    }    
    ss << "#joint actions="<<GetNrJointActions()<<endl;
    ss << SoftPrintActionSets();
    ss << "Joint Actions:"<<endl;
    ss << SoftPrintJointActionSet();
    return(ss.str());
}

string MADPComponentDiscreteActions::SoftPrintActionSets() const
{
    stringstream ss;
    if(!_m_initialized)
    {
        stringstream ss;
            ss << "MADPComponentDiscreteActions::PrintActionSets("<< 
            ") - Error: not initialized. "<<endl;
        throw E(ss);
    }    
    ss << "Actions:"<<endl;
    for(Index agentIndex=0; agentIndex < GetNrAgents(); agentIndex++)
    {
        ss << "agentI " << agentIndex << " - nrActions " << 
            GetNrActions(agentIndex)<<endl;
        vector<ActionDiscrete>::const_iterator f = 
            _m_actionVecs[agentIndex].begin();
        vector<ActionDiscrete>::const_iterator l = 
            _m_actionVecs[agentIndex].end();
        while(f != l)
        {
            ss << (*f).SoftPrint() << endl;
            // (*f).GetName() << " - " << (*f).GetDescription()<<endl;
            f++;
        }
    }
    return(ss.str());
}

string MADPComponentDiscreteActions::SoftPrintJointActionSet() const
{
    stringstream ss;
    if(!_m_initialized)
    {
        stringstream ss;
            ss << "MADPComponentDiscreteActions::PrintJointActionSets("<< 
            ") - Error: not initialized. "<<endl;
        throw E(ss);
    }   
    vector<JointActionDiscrete*>::const_iterator ja_it = 
    _m_jointActionVec.begin();
    vector<JointActionDiscrete*>::const_iterator ja_last = 
    _m_jointActionVec.end();
    while(ja_it != ja_last)
    {
        ss << (*ja_it)->SoftPrint()<<endl;
        ja_it++;    
    }
    return(ss.str());
}
