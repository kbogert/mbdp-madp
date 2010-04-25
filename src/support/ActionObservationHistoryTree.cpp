/**\file ActionObservationHistoryTree.cpp
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
 * $Id: ActionObservationHistoryTree.cpp 2118 2008-01-17 12:44:40Z mtjspaan $
 */

#include "ActionObservationHistoryTree.h"

#define DEBUG_AOHT 0

using namespace std;

/// Create a joint observation history tree for joh
ActionObservationHistoryTree::ActionObservationHistoryTree(
        ActionObservationHistory * const oh, aoh_t nt) :    
    TreeNode<ActionObservationHistory> (oh)
{
    _m_nodeType = nt; 
}
//Copy constructor.    
ActionObservationHistoryTree::
ActionObservationHistoryTree(const ActionObservationHistoryTree& o) :
    TreeNode<ActionObservationHistory>(o)
{
}

void ActionObservationHistoryTree::SetIndex(Index i)
{
    if (_m_nodeType == O_SUC)
        throw E("Trying ActionObservationHistoryTree::SetIndex on O_SUC node");

    this->TreeNode<ActionObservationHistory>::SetIndex(i);
};

void ActionObservationHistoryTree::SetSuccessor(Index aI, Index oI,
        ActionObservationHistoryTree* suc)
{
    if (_m_nodeType == O_SUC)
        throw E("Trying ActionObservationHistoryTree::SetSuccessor(Index aI, Index oI, ActionObservationHistoryTree* suc)  on O_SUC node");

    //first see if necessary to create a new  intermediate node
    ActionObservationHistoryTree* oNode; 
    if(this->TreeNode<ActionObservationHistory>::ExistsSuccessor(aI))
        oNode = (ActionObservationHistoryTree*)
            this->TreeNode<ActionObservationHistory>::GetSuccessor(aI);
    else //we need to create an intermediate node
    {
        oNode = new ActionObservationHistoryTree(O_SUC);

        //which is the aI'th successor of this node
        this->TreeNode<ActionObservationHistory>::SetSuccessor(aI, oNode);
    }

    //let oNode point to the actual successor.
    //Note: SetSuccessor with 1 index should give no problem for O_SUC nodes
    oNode->TreeNode<ActionObservationHistory>::SetSuccessor(oI, suc);
}

ActionObservationHistoryTree* ActionObservationHistoryTree::GetSuccessor(Index 
        aI, Index oI)
{
    if (_m_nodeType == O_SUC)
        throw E("Trying ActionObservationHistoryTree::SetSuccessor(Index aI, Index oI, ActionObservationHistoryTree* suc)  on O_SUC node");

    ActionObservationHistoryTree* suc;
    try {
        suc = (ActionObservationHistoryTree*)
        //we only put ActionObservationHistoryTree*'s in here so this cast
        //should be allowed.
        this->TreeNode<ActionObservationHistory>::GetSuccessor(aI) //the oNode
        ->TreeNode<ActionObservationHistory>::GetSuccessor(oI);
    } catch(EInvalidIndex& e) {
        // successor does not exist, so we should create it, see
        // JointActionObservationHistoryTree::GetSuccessor for
        // inspiration
        throw(E("ActionObservationHistoryTree::GetSuccessor generation of successors on the fly not yet implemented"));
    }

    return(suc);
}

ActionObservationHistory* ActionObservationHistoryTree::
    GetActionObservationHistory() const
{
    if (_m_nodeType == O_SUC)
        throw E("Trying ActionObservationHistoryTree::GetActionObservationHistory() on O_SUC node");

    return GetContainedElement();
}
    
void ActionObservationHistoryTree::Print() const
{
    if(_m_nodeType == A_SUC)
    {
        if(_m_containedElem == 0)
            return;    

        cout << "index: ";
        if(_m_indexValid)
            cout<< _m_index;
        else
            cout << "INVALID";
        cout << " - ";
        _m_containedElem->Print();
        cout <<endl;
    }
    //else //if (_m_nodeType == O_SUC)
    
    map< Index, TreeNode<ActionObservationHistory>*>::const_iterator
        it = _m_successor.begin();
    while(it != _m_successor.end())
    {        
        pair< Index, TreeNode<ActionObservationHistory>*> p = *it;
        TreeNode<ActionObservationHistory>* suc_tn = p.second;
        //we only put ActionObservationHistoryTree's as successors, so
        //we can do this:
        ActionObservationHistoryTree* suc_aoht =
            static_cast<ActionObservationHistoryTree*>(suc_tn);
        if(suc_aoht != 0)
            suc_aoht->Print();
        else
            throw E("ActionObservationHistoryTree::Print() - encountered"\
"a successor of this ActionObservationHistoryTree that is 0 (NULL) ");

        it++;
    }

}

