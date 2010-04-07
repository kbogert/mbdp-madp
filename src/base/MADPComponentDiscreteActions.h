/**\file MADPComponentDiscreteActions.h
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
 * $Id: MADPComponentDiscreteActions.h 3598 2009-08-20 12:29:54Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _MADPCOMPONENTDISCRETEACTIONS_H_
#define _MADPCOMPONENTDISCRETEACTIONS_H_ 1


/* the include directives */
#include <iostream>
#include <sstream>
#include "Globals.h"
#include "MultiAgentDecisionProcessDiscreteInterface.h"
#include "ActionDiscrete.h"
#include "JointActionDiscrete.h"
#include "IndexTools.h"

#include <map>


namespace {
    typedef std::vector<ActionDiscrete> ActionDVec;
}

/** \brief MADPComponentDiscreteActions contains functionality for
 * discrete action spaces.
 *
 *  It implements a part of the
 *  MultiAgentDecisionProcessDiscreteInterface. */
class MADPComponentDiscreteActions
    : 
    virtual public MultiAgentDecisionProcessDiscreteInterface //which this implements partly
{
    private:
    
        bool _m_initialized;    
        bool _m_cachedAllJointActions;
        bool _m_jointIndicesValid;
        size_t _m_nrJointActions;

        //cache this here (set by SetInitialized)
        size_t _m_nr_agents;
    
        /// The stepsize array - used for indiv->joint index calculation.
        size_t * _m_actionStepSize;

        ///The vector storing pointers to joint actions.
        /** To use this, ConstructJointActions() should be called */
        std::vector<JointActionDiscrete*> _m_jointActionVec;
    
        /// When not all joint actions have been created, here we cache
        /// the individual indices created by
        /// JointToIndividualActionIndices()
        std::map<Index, std::vector<Index> *> *_m_jointActionIndices;

        /// Recursively creates the joint actions.
        size_t ConstructJointActionsRecursively( Index curAgentI, 
            JointActionDiscrete& ja, Index jaI);

        std::string SoftPrintActionSets() const;
        std::string SoftPrintJointActionSet() const;

    protected:
        /// The number of actions for each agent.
        std::vector<size_t> _m_nrActions;
        /// The vectors of actions (vectors of ActionDiscrete) for each agent.
        std::vector<std::vector<ActionDiscrete> > _m_actionVecs;    

    public:

        /// Default constructor.
        MADPComponentDiscreteActions();

        /// Destructor.
        virtual ~MADPComponentDiscreteActions();

        //data manipulation (set) functions:

        /// Sets _m_initialized to b.
        bool SetInitialized(bool b);

        /// Sets the number of actions for agent AI.
        void SetNrActions(Index AI, size_t nrA);

        /// Add a new action with name "name" to the actions of agent AI.
        void AddAction(Index AI, std::string name);

        /// Recursively constructs all the joint actions.
        size_t ConstructJointActions();

        //get (data) functions:    

        /// Return the number of actions vector.
        const std::vector<size_t>& GetNrActions() const
        {return _m_nrActions;}

        /// Return the number of actions of agent agentI.    
        size_t GetNrActions(Index AgentI) const;

        /// Return the number of joiny actions.
        size_t GetNrJointActions() const;

        /// Returns the action index of the agent I's action s.
        Index GetActionIndexByName(std::string s, Index agentI) const;

        /// Returns the name of a particular action a of agent i.
        std::string GetActionName(Index a, Index i) const {
            return(_m_actionVecs.at(i).at(a).GetName()); }

        /// Returns the name of a particular joint action a.
        std::string GetJointActionName(Index a) const {
            return(_m_jointActionVec.at(a)->SoftPrint()); } 

        /// Return a ref to the a-th action of agent agentI.
        const Action* GetAction(Index agentI, Index a) const;

        /// Return a ref to the a-th action of agent agentI.
        const ActionDiscrete* GetActionDiscrete(Index agentI, Index a) const;

        /// Return a ref to the i-th joint action.
        const JointAction* GetJointAction(Index i) const;

        /// Return a ref to the i-th joint action (a JointActionDiscrete).
        const JointActionDiscrete* GetJointActionDiscrete(Index i) const;

        /** \brief Returns the joint action index that corresponds to
         * the vector of specified individual action indices.*/
        Index IndividualToJointActionIndices(const std::vector<Index>& 
                indivActionIndices) const;

        /** \brief Returns the joint action index that corresponds to
         * the array of specified individual action indices.*/
        Index IndividualToJointActionIndices(const Index* IndexArray) const
            {return IndexTools::IndividualToJointIndicesArrayStepSize(
                    IndexArray, _m_actionStepSize, _m_nr_agents);}

        /** \brief Returns a vector of indices to indiv. action
         * indicies corr. to joint action index jaI.*/
        const std::vector<Index>& JointToIndividualActionIndices(Index jaI)const
        {
            if(!_m_jointIndicesValid)
            {
                throw(E("MADPComponentDiscreteActions::JointToIndividualActionIndices() joint indices are not available, overflow detected"));
            }
            if(_m_cachedAllJointActions)
                return GetJointActionDiscrete(jaI)->
                    GetIndividualActionDiscretesIndices();
            else if(_m_jointActionIndices->find(jaI)!=
                    _m_jointActionIndices->end())
                return(*_m_jointActionIndices->find(jaI)->second);
            else // create new 
            {
                std::vector<Index> *indices=new std::vector<Index>();
                *indices=IndexTools::JointToIndividualIndices(jaI,
                                                              GetNrActions());
                _m_jointActionIndices->insert(make_pair(jaI,indices));
                return(*indices);
            }
        }
        
        std::string SoftPrint() const;
        void Print() const
        {std::cout << MADPComponentDiscreteActions::SoftPrint();}
};


#endif /* !_MADPCOMPONENTDISCRETEACTIONS_H_ */


// Local Variables: ***
// mode:c++ ***
// End: ***
