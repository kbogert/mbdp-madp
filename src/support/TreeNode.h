/**\file TreeNode.h
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
 * $Id: TreeNode.h 2151 2008-01-21 16:32:52Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _TREENODE_H_
#define _TREENODE_H_ 1

/* the include directives */
#include <iostream>
#include <map>
#include "Globals.h"
#include "E.h"



#define DEBUG_TREENODE 0

/** \brief TreeNode represents a node in a tree of histories, for
 * instance observation histories.
 *
 * TreeNode is a class that represents a wrapper for the Tcontained
 * class.  Each node also specifies a (sub-)tree so there is no actual
 * difference between a tree and a node.  This implementation assumes
 * that ObservationHistories are always contained in exactly 1
 * TreeNode: i.e., deleting an object of TreeNode will free the memory
 * of the node and the subtree represented by it as well as the memory
 * of all the contained ObservationHistories. */
template <class Tcontained >
class TreeNode 
{
    private:
    protected:
        /**The map that stores the pointers to the successor
         * TreeNodes*/
        std::map< Index, TreeNode<Tcontained>* > _m_successor; 
        ///A Pointer to the predecessor.
        TreeNode<Tcontained>* _m_pred;
        /**The index of this TreeNode (and thus of the contained
         * Tcontained - typically an observation history).*/
        Index _m_index;
        ///Whether the index is valid.
        bool _m_indexValid;
        ///The contained element 
        Tcontained* _m_containedElem;
    

    
    public:
        // Constructor, destructor and copy assignment.
        /// (default) Constructor
        TreeNode()
        {    
            _m_index = 42; // weird number to help track it down in gdb etc
            _m_indexValid = false;
            _m_containedElem = 0;
            _m_pred = 0;
        }

        TreeNode(Tcontained *const oh)
        {
            _m_index = 0;
            _m_indexValid = false;
            _m_containedElem = oh;
            _m_pred = 0;
        }
        /// Copy constructor.
        TreeNode(const TreeNode& a)
        {
            _m_successor=a._m_successor;
            _m_pred=a._m_pred;
            _m_index=a._m_index;
            _m_indexValid=a._m_indexValid;
            _m_containedElem=new Tcontained(*a._m_containedElem);

#if DEBUG_TREENODE
            cerr << "Cloning TreeNode. This node ";
            PrintThisNode();
            cerr << endl;
#endif        
        }

        /// Destructor.
        virtual ~TreeNode()
        {
#if DEBUG_TREENODE
            cerr << "Deleting TreeNode. This node ";
            PrintThisNode();cerr << endl;
#endif
            delete(_m_containedElem);

            while(!_m_successor.empty())
            {
                delete _m_successor.begin()->second; // recursively
                                                     // delete the
                                                     // rest of the
                                                     // tree
                _m_successor.erase(_m_successor.begin());
            }
        }

        //operators:

        //data manipulation (set) functions:
        ///Sets the index to i
        void SetIndex(Index i){_m_index = i; _m_indexValid = true; };
        /** \brief Sets the sucI'th successor of this TreeNode to suc.
         *
         * For example, the successor for observation number
         * sucI. Also sets the predecessor of suc to this.*/
        void SetSuccessor(Index sucI, TreeNode<Tcontained>* suc);
        /** \brief Sets the predecessor of this node to be pred.
         *
         * This function is typically called by SetSuccessor (not
         * manually).*/
        void SetPredeccessor(TreeNode<Tcontained>* pred)
            {_m_pred = pred;}

        //get (data) functions:
        
        ///Get the succesor TreeNode* for the sucI'th successor
        TreeNode* GetSuccessor(Index sucI);
        ///Get the predecessor TreeNode*. 
        TreeNode* GetPredecessor() const
            {return(_m_pred);}
            
        /**\brief Returns the index of this TreeNode (and thus
         * corresponding to the contained element).*/
        Index GetIndex() const 
        {
            if(_m_indexValid) 
                return(_m_index);
            else
                throw E("This TreeNode's index is invalid (not yet set)");
        }
        ///Returns a pointer to the contained element (Tcontained) 
        Tcontained* GetContainedElement() const {return(_m_containedElem);};

        /// Check whether a particular successor sucI exists.
        bool ExistsSuccessor(Index sucI);

        /** \brief Prints the tree starting from this node of the
         * history tree (including the successors).*/
        void Print() const;
        /** \brief Prints only this node of the history tree (not the
         * successors).*/
        void PrintThisNode() const;
    
};

template <class Tcontained>
void TreeNode<Tcontained>::SetSuccessor(Index sucI, 
    TreeNode<Tcontained>* suc)
{
    if( ExistsSuccessor(sucI) )
    {
#if DEBUG_TREENODE
        cout << "_m_successor["<< sucI<< "] already set: overwriting!\n";
#endif
        _m_successor[sucI] = suc;
    }
    else
    {    
        std::pair< Index, TreeNode<Tcontained>* > arg_pair = 
            make_pair(sucI, suc);
        std::pair< typename std::map<  Index, TreeNode<Tcontained>* >::iterator, bool> 
            result_pair;
        result_pair = _m_successor.insert(arg_pair);
        if(result_pair.second == false)
        {
            std::stringstream ss;
            ss << "TreeNode<Tcontained>::SetSuccessor insertion failed, "
               << "but _m_successor["<< sucI<< "] wasn't already set ?!?";
            throw(E(ss));
        }
    }

    suc->SetPredeccessor(this);
}

template <class Tcontained>
TreeNode<Tcontained>* TreeNode<Tcontained>::GetSuccessor(Index sucI)
{
    if(_m_successor.find(sucI)==_m_successor.end())
        throw EInvalidIndex("TreeNode::GetSuccessor successor not found");
    else
        return(_m_successor[sucI]);
}

template <class Tcontained>
bool TreeNode<Tcontained>::ExistsSuccessor(Index sucI)
{
    if(_m_successor.find(sucI)==_m_successor.end())
        return(false);
    else
        return(true);
}


template <class Tcontained>
void TreeNode<Tcontained>::PrintThisNode() const
{
    if(_m_containedElem != 0)
    {
        std::cout << "index: "<<_m_index<<" - ";
        _m_containedElem->Print();
    }
}

template <class Tcontained>
void TreeNode<Tcontained>::Print() const
{
    if(_m_containedElem != 0)
    {

        std::cout << "index: ";
        if(_m_indexValid)
            std::cout<< _m_index;
        else
            std::cout << "INVALID";
        std::cout << " - ";
        _m_containedElem->Print();
        std::cout << std::endl;
        //typname dependent on template should be called using typename
        typename std::map< Index, TreeNode<Tcontained>*>::const_iterator it = 
            _m_successor.begin();
        while(it != _m_successor.end())
        {
            if(it->second != 0) it->second->Print();
            it++;
        }
    }
}

#endif /* !_TREENODE_H_ */


// Local Variables: ***
// mode:c++ ***
// End: ***
