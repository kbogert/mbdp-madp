/**\file MADPComponentDiscreteObservations.h
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
 * $Id: MADPComponentDiscreteObservations.h 3598 2009-08-20 12:29:54Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _MADPCOMPONENTDISCRETEOBSERVATIONS_H_
#define _MADPCOMPONENTDISCRETEOBSERVATIONS_H_ 1

/* the include directives */
#include <iostream>
#include <sstream>
#include "Globals.h"
#include "MultiAgentDecisionProcessDiscreteInterface.h"
#include "JointObservationDiscrete.h"
#include "ObservationDiscrete.h"
#include "IndexTools.h"
#include <map>

namespace {
    typedef std::vector<ObservationDiscrete> ObservationDVec;
}

/** 
 * \brief MADPComponentDiscreteObservations contains functionality for
 * discrete observation spaces.
 *
 *  It implements a part of the
 *  MultiAgentDecisionProcessDiscreteInterface. */
class MADPComponentDiscreteObservations: 
    virtual public MultiAgentDecisionProcessDiscreteInterface //which this implements partly
{
    private:

        bool _m_initialized;
        bool _m_cachedAllJointObservations;
        bool _m_jointIndicesValid;
        size_t _m_nrJointObservations;
    
        /// The stepsize array - used for indiv->joint index calculation.
        size_t * _m_observationStepSize;

        /// The vector storing the joint observations     
        /** To use this, ConstructJointObservations() should be called */
        std::vector<JointObservationDiscrete*> _m_jointObservationVec;

        /// When not all joint observations have been created, here we cache
        /// the individual indices created by
        /// JointToIndividualObservationIndices()
        std::map<Index, std::vector<Index> *> *_m_jointObservationIndices;

        /// Recursively creates the joint observations.
        size_t ConstructJointObservationsRecursively( Index curAgentI, 
            JointObservationDiscrete& jo, Index joI);

        std::string SoftPrintObservationSets() const;
        std::string SoftPrintJointObservationSet() const;

    protected:
        /// The number of observations for each agent.
        std::vector<size_t> _m_nrObservations;
         /** \brief The vectors of observations (vectors of
         * ObservationDiscrete) for each agent.*/
        std::vector<std::vector<ObservationDiscrete> > _m_observationVecs;    

    public:
        // Constructor, destructor and copy assignment.
        /// (default) Constructor
        MADPComponentDiscreteObservations();
        /// Destructor.
        virtual ~MADPComponentDiscreteObservations();

        //operators:

        //data manipulation (set) functions:
        /// Sets _m_initialized to b.
        bool SetInitialized(bool b);

        /// Sets the number of observations for agent AI.
        void SetNrObservations(Index AI, size_t nrO);

        /// Add a new observation with name "name" to the observ. of agent AI.
        void AddObservation(Index AI, std::string name);

        /// Recursively constructs all the joint observations.
        size_t ConstructJointObservations();

        //get (data) functions:

        /// Return the number of observations vector.    
        const std::vector<size_t>& GetNrObservations() const
            {return _m_nrObservations;}

        /// Return the number of observations of agent agentI    
        size_t GetNrObservations(Index AgentI) const;

        /// Return the number of joiny observations.
        size_t GetNrJointObservations() const; 

        /// Returns the observation index of the agent I's observation s.
        Index GetObservationIndexByName(std::string s, Index agentI) const;

        /// Returns the name of a particular observation o of agent i. 
        std::string GetObservationName(Index o, Index i) const {
            return(_m_observationVecs.at(i).at(o).GetName()); }

        /// Returns the name of a particular joint observation o. 
         std::string GetJointObservationName(Index o) const {
            return(_m_jointObservationVec.at(o)->SoftPrint()); } 

        /// Return a ref to the a-th observation of agent agentI.
        const ObservationDiscrete* GetObservationDiscrete(Index agentI, 
                Index a) const;

        /// Return a ref to the a-th observation of agent agentI.
        const Observation* GetObservation(Index agentI, Index a) const   
        {return( (Observation*) GetObservationDiscrete(agentI,a) );}

        /// Return a ref to the i-th joint observation.
        const JointObservation* GetJointObservation(Index i) const;

        /// Return a ref to the i-th joint observation integer.
        const JointObservationDiscrete* GetJointObservationDiscrete(Index i)
            const;

        /** \brief Returns the joint observation index that
         * corresponds to the vector of specified individual
         * observation indices.*/
        Index IndividualToJointObservationIndices(const std::vector<Index>& 
                indivObservationIndices)const;

        /** \brief Returns a vector of indices to indiv. observation
         * indicies corr. to joint observation index joI.*/
        const std::vector<Index>& 
            JointToIndividualObservationIndices(Index joI) const
        {
            if(!_m_jointIndicesValid)
            {
                throw(E("MADPComponentDiscreteActions::JointToIndividualActionIndices() joint indices are not available, overflow detected"));
            }
            if(_m_cachedAllJointObservations)
                return GetJointObservationDiscrete(joI)->
                    GetIndividualObservationDiscretesIndices();
            else if(_m_jointObservationIndices->find(joI)!=
                    _m_jointObservationIndices->end())
                return(*_m_jointObservationIndices->find(joI)->second);
            else // create new 
            {
                std::vector<Index> *indices=new std::vector<Index>();
                *indices=IndexTools::JointToIndividualIndices(joI,
                                                              GetNrObservations());
                _m_jointObservationIndices->insert(make_pair(joI,indices));
                return(*indices);
            }
        } 
            
        std::string SoftPrint() const;
        void Print() const
        {std::cout << SoftPrint();}
};


#endif /* !_MADPCOMPONENTDISCRETEOBSERVATIONS_H_ */


// Local Variables: ***
// mode:c++ ***
// End: ***
