/**\file MultiAgentDecisionProcessDiscreteInterface.h
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
 * $Id: MultiAgentDecisionProcessDiscreteInterface.h 4016 2010-03-11 16:56:02Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _MULTIAGENTDECISIONPROCESSDISCRETEINTERFACE_H_
#define _MULTIAGENTDECISIONPROCESSDISCRETEINTERFACE_H_ 1

/* the include directives */
#include <vector>
#include <string>

#include "MultiAgentDecisionProcessInterface.h"

class Action;
class Observation;
class JointObservation;
class State;
class JointAction;
class TransitionModelMapping;
class TransitionModelMappingSparse;
class ObservationModelMapping;
class ObservationModelMappingSparse;

class TransitionModelDiscrete; 
class ObservationModelDiscrete;

class TGet;
class OGet;
class StateDistribution;

/**\brief MultiAgentDecisionProcessDiscreteInterface is an abstract base
 * class that defines publicly accessible member functions that a
 * discrete multiagent decision process must implement.
 *
 * This interface is currently implemented by MultiAgentDecisionProcessDiscrete
 * and MultiAgentDecisionProcessDiscreteFactoredStates. 
 *
 * The functions this interface defines relate to actions, observations,
 * transition and observation probabilities. *
 *
 **/
class MultiAgentDecisionProcessDiscreteInterface : 
    virtual public MultiAgentDecisionProcessInterface
{
    private:    

    protected:    

    public:

        ///Destructor. Can't make a virt.destr. pure abstract!
        virtual ~MultiAgentDecisionProcessDiscreteInterface() {};

        // 'get' functions:     

        ///Return the number of states.
        virtual size_t GetNrStates() const = 0;
        ///Returns a pointer to state i.
        virtual const State* GetState(Index i) const = 0;
        virtual std::string SoftPrintState(Index sI) const = 0;

        /////Return the initial state distribution.
        virtual double GetInitialStateProbability(Index sI) const = 0;
        /// Returns the complete initial state distribution.
        virtual const StateDistribution* GetISD() const = 0;


        
        ///Return the number of actions vector    
        virtual const std::vector<size_t>& GetNrActions() const = 0;
        ///Return the number of actions of agent agentI    
        virtual size_t GetNrActions(Index AgentI) const =0 ;
        ///Return the number of joiny actions.
        virtual size_t GetNrJointActions() const = 0;

        ///Return a ref to the a-th action of agent agentI.
        virtual const Action* GetAction(Index agentI, Index a) const = 0;
        ///Return a ref to the i-th joint action.
        virtual const JointAction* GetJointAction(Index i) const = 0;
        /**\brief Returns the joint action index that corresponds to the array
         * of specified individual action indices.*/
        virtual Index IndividualToJointActionIndices(const Index* AI_ar)
            const = 0;
        /**\brief Returns the joint action index that corresponds to the vector
         * of specified individual action indices.*/
        virtual Index IndividualToJointActionIndices(const std::vector<Index>& 
                indivActionIndices) const = 0;
        /**\brief Returns a vector of indices to indiv. action indicies corr.
         * to joint action index jaI.*/
        virtual const std::vector<Index>& JointToIndividualActionIndices(
                Index jaI) const = 0;
        

        ///Return the number of observations vector.    
        virtual const std::vector<size_t>& GetNrObservations() const = 0;
        ///Return the number of observations of agent agentI    
        virtual size_t GetNrObservations(Index AgentI) const = 0;
        ///Return the number of joiny observations.
        virtual size_t GetNrJointObservations() const = 0; 

        ///Return a ref to the a-th observation of agent agentI.
        virtual const Observation* GetObservation(Index agentI, Index a) 
            const = 0; 
        ///Return a ref to the i-th joint observation.
        virtual const JointObservation* GetJointObservation(Index i) const = 0;

        /**\brief Returns the joint observation index that corresponds to the
         * vector of specified individual observation indices.*/
        virtual Index IndividualToJointObservationIndices(
                const std::vector<Index>& 
                indivObservationIndices) const = 0;
        /**\brief Returns a vector of indices to indiv. observation indicies
         * corr. to joint observation index jaI.*/
        virtual const std::vector<Index>& 
            JointToIndividualObservationIndices(Index joI) const = 0;

        ///Return the probability of successor state sucSI: P(sucSI|sI,jaI).
        virtual double GetTransitionProbability(Index sI, Index jaI, Index 
                sucSI) const = 0;
        virtual TGet* GetTGet() const = 0;

        ///Return the probability of joint observation joI: P(joI|jaI,sucSI).
        virtual double GetObservationProbability(Index jaI, Index sucSI, 
                Index joI) const = 0;
        virtual OGet* GetOGet() const = 0;
        

        /**\brief Returns a pointer to the underlying transition model.
         *
         * If speed is required (for instance when looping through all states)
         * the pointer can be requested by an algorithm. It can than obtain
         * a pointer to the actual implementation type by runtime type 
         * identification. (i.e., using typeid and dynamic_cast).
         */
        virtual const TransitionModelDiscrete* GetTransitionModelDiscretePtr() 
            const = 0;

        /**\brief Returns a pointer to the underlying observation model.
         *
         * If speed is required (for instance when looping through all states)
         * the pointer can be requested by an algorithm. It can than obtain
         * a pointer to the actual implementation type by runtime type 
         * identification. (i.e., using typeid and dynamic_cast).
         */
        virtual const ObservationModelDiscrete* GetObservationModelDiscretePtr()            const = 0;


        //sample functions:

        /// Sample a successor state - needed by simulations.
        virtual Index SampleSuccessorState(Index sI, Index jaI) const = 0;
        /// Sample an observation - needed for simulations.
        virtual Index SampleJointObservation(Index jaI, Index sucI) const =0;
        /// Sample a state according to the initial state PDF.
        virtual Index SampleInitialState(void) const = 0;

        /// Returns a pointer to a copy of this class.
 //       virtual MultiAgentDecisionProcessDiscreteInterface* Clone() const = 0;

        /**\brief Prints some information on the 
         * MultiAgentDecisionProcessDiscreteInterface.
         * */ 
        virtual std::string SoftPrint() const = 0;

};

#endif /* !_MULTIAGENTDECISIONPROCESSINTERFACE_H_ */


// Local Variables: ***
// mode:c++ ***
// End: ***
