/**\file ActionObservationHistoryTree.h
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
 * $Id: ActionObservationHistoryTree.h 2116 2008-01-16 23:11:49Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _ACTIONOBSERVATIONHISTORYTREE_H_
#define _ACTIONOBSERVATIONHISTORYTREE_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"
#include "TreeNode.h"
#include "ActionObservationHistory.h"


/// ActionObservationHistoryTree is a wrapper for ActionObservationHistory.
/**
 * A class derived from #TreeNode, and similar to #ObservationHistoryTree:
 *
 * ActionObservationHistoryTree is a class that represents a wrapper for the 
 * ActionObservationHistory class. An ActionObservationHistoryTree actually 
 * represents  a node in the tree of observation histories. But each node also 
 * specifies a (sub-)tree so there is no actual difference between a tree and 
 * a node. 
 * This implementation assumes that ActionObservationHistories are always 
 * contained in exactly 1 ActionObservationHistoryTree: i.e., deleting an 
 * object of ActionObservationHistoryTree will free the memory of the node and 
 * the subtree represented by it as well as the memory of all the contained 
 * ActionObservationHistories.
 *
 * A difference with #ObservationHistoryTree is that here a successor is 
 * specified by 2 indices. One option would be to combine these into a joint
 * index, but this would add calculation every time we're traversing the tree.
 * Instead this class defines 2 types of nodes: ones that specify the 
 * action successor (A_SUC) and ones that specify the observation successor
 * (O_SUC).
 * Only the A_SUC nodes contain actual ActionObservationHistories, O_SUC nodes
 * are 'intermediate nodes' and no operations should be performed on them.
 * */
class ActionObservationHistoryTree :  public TreeNode <ActionObservationHistory>
{
    private:
        enum aoh_t {A_SUC, O_SUC};

        aoh_t _m_nodeType;
    
    protected:
    
    public:
        // Constructor, destructor and copy assignment.
        /// (default) Constructor
        ActionObservationHistoryTree(aoh_t nt = A_SUC) :
            TreeNode<ActionObservationHistory>(),
            _m_nodeType(nt){};

        /// Create a joint observation history tree for joh
        ActionObservationHistoryTree(ActionObservationHistory *const aoh, 
                aoh_t nt = A_SUC);

        /// Copy constructor.
        ActionObservationHistoryTree(const ActionObservationHistoryTree& a);
        //operators:

        //data manipulation (set) functions:
        /// Sets the index to i.
        void SetIndex(Index i);
        /// Sets the sucI'th successor of this TreeNode to suc.
        /** (e.g. the successor for observation number sucI). */
        void SetSuccessor(Index aI, Index oI,ActionObservationHistoryTree* suc);

        
        //get (data) functions:
        /// Get the successor node.
        ActionObservationHistoryTree* GetSuccessor(Index aI, Index oI);
        /// Get the history stored in this node.
        ActionObservationHistory* GetActionObservationHistory() const;

        void Print() const;
};


#endif /* !_ACTIONOBSERVATIONHISTORYTREE_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
