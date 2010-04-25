/**\file ObservationHistoryTree.h
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
 * $Id: ObservationHistoryTree.h 2945 2008-10-25 11:14:45Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _OBSERVATIONHISTORYTREE_H_
#define _OBSERVATIONHISTORYTREE_H_ 1

/* the include directives */
#include "ObservationHistory.h"
#include "TreeNode.h"

/// ObservationHistoryTree is a wrapper for the ObservationHistory class.
/**
 * An ObservationHistoryTree actually represents a node in the tree of
 * observation histories. But each node also specifies a (sub-)tree so
 * there is no actual difference between a tree and a node. This
 * implementation assumes that ObservationHistories are always
 * contained in exactly 1 ObservationHistoryTree: i.e., deleting an
 * object of ObservationHistoryTree will free the memory of the node
 * and the subtree represented by it as well as the memory of all the
 * contained ObservationHistories. */
class ObservationHistoryTree : public TreeNode <ObservationHistory>
{
    private:
    
    protected:
    
    public:
        // Constructor, destructor and copy assignment.
        /// Create a joint observation history tree for joh
        ObservationHistoryTree(ObservationHistory *const oh) :
            TreeNode<ObservationHistory> (oh)
        {}
        /// Copy constructor.
        ObservationHistoryTree(const ObservationHistoryTree& a):
            TreeNode<ObservationHistory> (a)
        {}

        //operators:

        //data manipulation (set) functions:
 
        //get (data) functions:
        /// Returns the length of the contained ObservationHistory.
        size_t GetLength() const  
        {
            return( 
                (GetContainedElement()!=0)?
                GetContainedElement()->GetLength() :
                throw E("_m_jObsHist undefined!")
            );
        };
        ObservationHistory* GetObservationHistory() const
        {return GetContainedElement();}

        ObservationHistoryTree* GetPredecessor() const
        {return (ObservationHistoryTree*) //we know we only put pointers
            //to ObservationHistoryTree's in here.
            TreeNode<ObservationHistory>::GetPredecessor();}

        ObservationHistoryTree* GetSuccessor(Index jObsI)
        {return (ObservationHistoryTree*) //we know we only put pointers
            //to ObservationHistoryTree's in here.
            TreeNode<ObservationHistory>::GetSuccessor(jObsI);}

};


#endif /* !_OBSERVATIONHISTORYTREE_H_ */


// Local Variables: ***
// mode:c++ ***
// End: ***
