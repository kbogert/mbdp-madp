/**\file JointObservationHistoryTree.h
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
 * $Id: JointObservationHistoryTree.h 2116 2008-01-16 23:11:49Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _JOINTOBSERVATIONHISTORYTREE_H_
#define _JOINTOBSERVATIONHISTORYTREE_H_ 1

/* the include directives */
#include <iostream>
#include <vector>
#include "Globals.h"
#include "JointObservationHistory.h"
#include "TreeNode.h"
//#include "PlanningUnitMADPDiscrete.h"
class PlanningUnitMADPDiscrete; //forward declaration to avoid including each other



/** 
 * \brief JointObservationHistoryTree is a class that represents a
 * wrapper for the JointObservationHistory class.
 *
 * An JointObservationHistoryTree actually represents a node in the
 * tree of observation histories. But each node also specifies a
 * (sub-)tree so there is no actual difference between a tree and a
 * node.  This implementation assumes that ObservationHistories are
 * always contained in exactly 1 JointObservationHistoryTree: i.e.,
 * deleting an object of JointObservationHistoryTree will free the
 * memory of the node and the subtree represented by it as well as the
 * memory of all the contained ObservationHistories.
 * 
*/
class JointObservationHistoryTree : public TreeNode<JointObservationHistory>
{
    private:
    
    protected:
    
    public:
        // Constructor, destructor and copy assignment.

        /// Create a joint observation history tree for joh
        JointObservationHistoryTree(JointObservationHistory *const joh) :
            TreeNode<JointObservationHistory> (joh)
        {}
        /// Copy constructor.
        JointObservationHistoryTree(const JointObservationHistoryTree& a):
            TreeNode<JointObservationHistory> (a)
        {}
        /// Destructor.
        //~JointObservationHistoryTree();

        //operators:

        //data manipulation (set) functions:
        
        //get (data) functions:
        ///Returns the length of the contained ObservationHistory.
        size_t GetLength() const 
        {
            return( 
                (GetContainedElement()!=0)?
                GetContainedElement()->GetLength() :
                throw E("_m_jObsHist undefined!")
            );
        };
        JointObservationHistory* GetJointObservationHistory() const
        {return GetContainedElement();}
        
        JointObservationHistoryTree* GetPredecessor() const
        {return (JointObservationHistoryTree*) //we know we only put pointers
            //to JointObservationHistoryTree's in here.
            TreeNode<JointObservationHistory>::GetPredecessor();}

        JointObservationHistoryTree* GetSuccessor(Index jObsI)
        {return (JointObservationHistoryTree*) //we know we only put pointers
            //to JointObservationHistoryTree's in here.
            TreeNode<JointObservationHistory>::GetSuccessor(jObsI);}
};


#endif /* !_JOINTOBSERVATIONHISTORYTREE_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
