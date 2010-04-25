/**\file TransitionObservationIndependentMADPDiscrete.h
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
 * $Id: TransitionObservationIndependentMADPDiscrete.h 3611 2009-08-25 15:02:24Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _TRANSITIONOBSERVATIONINDEPENDENTMADPDISCRETE_H_
#define _TRANSITIONOBSERVATIONINDEPENDENTMADPDISCRETE_H_ 1

/* the include directives */
#include "Globals.h"
#include "MultiAgentDecisionProcess.h"
#include "MultiAgentDecisionProcessDiscreteInterface.h"
#include "TransitionModelDiscrete.h"
#include "ObservationModelDiscrete.h"
#include "MultiAgentDecisionProcessDiscrete.h"
#include <map>
#include "StateDistributionVector.h"

/** 
 * \brief TransitionObservationIndependentMADPDiscrete is an base class that 
 * defines the primary properties of a Transition and Observation independent
 * decision process. 
 *
 * It implements the transition and observation model by assigning a regular
 * (1-agent) MultiAgentDecisionProcessDiscrete for each agent: the agents
 * local model.
 * This class is responsible for constructing the joint actions and
 * observations (upon which rewards will typically be based).
 *
 *
 * */
class TransitionObservationIndependentMADPDiscrete : 
    public MultiAgentDecisionProcess,
    virtual public MultiAgentDecisionProcessDiscreteInterface
{
private:    
    /// Boolean to indicate whether this MADPDiscrete has been initialized.
    bool _m_initialized;
    /// Boolean that indicates whether models should be stored sparsely.
    bool _m_sparse;

    /// Boolean indicating whether joint models should be generated.
    bool _m_noJointModels;

    //cache this here (set by SetInitialized)
    size_t _m_nr_agents;

    /**In a transition-observation independent MADP, each agent has a set
     * of local states and observations together with an individual 
     * transition and observation model. We model this as each agent having
     * its own MultiAgentDecisionProcessDiscrete. This is the vector that 
     * contains a pointer to each agent's MultiAgentDecisionProcessDiscrete.
     */
    std::vector<MultiAgentDecisionProcessDiscrete*> _m_individualMADPDs;

    /**The vector storing the joint actions */    
    std::vector<JointActionDiscrete*> _m_jointActionVec;
    std::map<Index, JointActionDiscrete*> *_m_jointActionMap;
    
    std::vector<std::vector<Index> > _m_jointToIndActionCache;

    /// The stepsize array - used for indiv->joint index calculation.
    size_t * _m_actionStepSize;

    /**Vector that stores the number of individual states. (Created by
     * CreateJointStates() )*/
    std::vector<size_t> _m_nrIndivStates;

    /**The vector storing the individual state indices for each joint
     * index: _m_indivStateIndices[jointStateIndex] = vector<Index> */
    std::vector< std::vector<Index> > _m_indivStateIndices;
    std::map< Index, std::vector<Index> > *_m_indivStateIndicesMap;
    
    std::vector<State*> _m_jointStates;
    std::map<std::vector<Index>, State*> *_m_jointStatesMap;
    
    size_t _m_nrJointStates;

    /**The vector containing the initial state distr over joint states.*/
    //std::vector<double> _m_initialStateDistribution;
    StateDistributionVector* _m_initialStateDistribution;
    /**the number of joint actions.*/
    size_t _m_nrJointActions;
    
    std::vector<size_t> _m_nrIndivActions;
    
    std::vector<size_t> _m_nrIndivObs;
    
    std::vector<std::vector<ObservationDiscrete> > _m_indivObs;
    std::vector<JointObservationDiscrete*> _m_jointObs;
    std::map<Index, JointObservationDiscrete*> *_m_jointObsMap;
    
    size_t _m_nrJointObservations;
    
    std::vector<std::vector<Index> > _m_jointToIndObsCache;

    TransitionModelDiscrete* _m_p_tModel;

    ObservationModelDiscrete* _m_p_oModel;

// initialization functions
        
    /**Recursively constructs all the joint actions.
     * Works by calling
     * CreateJointActionsRecursively on a new (empty) joint action.*/
    void CreateJointActions();
    /* Recursively creates the joint actions (_m_jointActionVec) 
     * using _m_actionVecs (which need to be initialized before calling
     * this function...) */    
    size_t CreateJointActionsRecursively( Index curAgentI, 
                                          JointActionDiscrete& ja, Index jaI);
    
    /**This function generates the joint -> individual state index cache.
     * This function assumes that all the agents and their local states 
     * have been added.*/
    void CreateJointStates();
    
    void CreateJointObservations();

    void CreateISD();

    size_t ConstructJointObservationsRecursively( 
        Index curAgentI, JointObservationDiscrete& jo, Index joI);
    
    std::vector<Index> JointToIndividualActionIndicesNoCache(Index jaI) const;
    
    std::vector<Index> JointToIndividualObservationIndicesNoCache(Index joI) 
        const;
    
protected:    
    //data manipulation (set) functions:
    /** Sets _m_initialized to b. When setting to true, a verification of
     * member elements is performed. (i.e. a check whether all vectors
     * have the correct size and non-zero entries) */
    virtual bool SetInitialized(bool b);

    bool GetSparse() const { return(_m_sparse); }

public:
    //\todo remove - temporary function...
    bool Initialize()
        {return(SetInitialized(true));}
    
    // Constructor, destructor and copy assignment.
    // Default constructor.
    TransitionObservationIndependentMADPDiscrete(
        std::string name="received unspec. by TransitionObservationIndependentMADPDiscrete",
        std::string descr="received unspec.by TransitionObservationIndependentMADPDiscrete",
        std::string pf="received unspec. by TransitionObservationIndependentMADPDiscrete");
    // Copy assignment constructor.
    TransitionObservationIndependentMADPDiscrete(
        const TransitionObservationIndependentMADPDiscrete&);
    
    ///Destructor.
    virtual ~TransitionObservationIndependentMADPDiscrete();
    
// pre-initialization functions, functions that are used to construct the models
// etc.
    /**\brief Sets the number of agents to n.*/
    void SetNrAgents(size_t n);
    /**\brief Adds one agent with an optional name.*/
    void AddAgent(std::string name="unspec.");
    /**\brief Sets the number of states for the specified agent.*/
    void SetNrStates(Index agentI, size_t nr);
    /**\brief Adds a state with a particular name for the specified agent.*/
    void AddState(Index agentI, std::string name);
    /**\brief Sets the number of actions for the specified agent.*/
    void SetNrActions(Index agentI, size_t nr);
    /**\brief Adds an action with a particular name for the specified agent.
         * */
    void AddAction(Index agentI, std::string name);
    /**\brief Sets the number of Observations for the specified agent.*/
    void SetNrObservations(Index agentI, size_t nr);
    /**\brief Adds an Observation with a particular name for the specified 
     * agent.*/
    void AddObservation(Index agentI, std::string name);
#if 0 // will be computed from individual ISDs
    /**Sets the initial state distribution to a uniform one.*/
    void SetUniformISD();
#endif
    /**\brief Sets the initial state distribution to v.*/
    void SetISD(const std::vector<double> &v);

    //get (data) functions:   
    /**Returns a pointer to agentsI's individual model.
     */
    MultiAgentDecisionProcessDiscrete* GetIndividualMADPD(Index agentI)
        const
        {return _m_individualMADPDs[agentI];}
    /**\brief return the number of joint actions.*/
    size_t GetNrJointActions() const;

    /**\brief return a ref to the i-th joint action (a JointActionDiscrete).*/
    const JointActionDiscrete* GetJointActionDiscrete(Index i) const;

    size_t GetNrJointStates() const;
    
//some shortcut functions        

    /**\brief return the number of actions of agent agentI*/    
    size_t GetNrActions(Index agentI) const
        {return GetIndividualMADPD(agentI)->GetNrActions(0);}
    /**\brief Returns the number of local states for agent i.*/
    size_t GetNrStates(Index agI) const
        {return _m_individualMADPDs[agI]->GetNrStates();}
    
    /**\brief return the number of observations of agent agentI*/    
    size_t GetNrObservations(Index agentI) const
        {return GetIndividualMADPD(agentI)->GetNrObservations(0);}
    
//joint <-> individual action conversion

    /**\brief Returns the joint action index that corresponds to the vector 
     * of specified individual action indices.*/
    Index IndividualToJointActionIndices(const std::vector<Index>& 
                                          indivActionIndices) const;
//        /**Returns the joint action index that corresponds to the array of
//         * specified individual action indices.*/
//        Index IndividualToJointActionIndices(Index* IndexArray) const
//            {return IndexTools::IndividualToJointIndicesArray(IndexArray, 
//                    _m_nrActions);}
    /**\brief returns a vector of indices to indiv. action indicies corr.
     * to joint action index jaI.*/
    const std::vector<Index>& JointToIndividualActionIndices(Index jaI) const {
        return(_m_jointToIndActionCache.at(jaI)); }
    Index IndividualToJointActionIndices(const Index* AI_ar) const
        {return IndexTools::IndividualToJointIndicesArrayStepSize(
             AI_ar, _m_actionStepSize, _m_nr_agents);}

    /**\brief returns a vector of individual (local) state indices
     * corresponding to joint state index jointSI.*/
    const std::vector<Index>& JointToIndividualStateIndices(Index jointSI) const;

    /**\brief returns the joint index for indivStateIndices*/
    Index IndividualToJointStateIndices(const std::vector<Index>&
                                        indivStateIndices) const;       
    
    /**\brief returns the joint index for indivObsIndices*/
    Index IndividualToJointObservationIndices(const std::vector<Index>& 
                                               indivObsIndices) const;
    /**\brief returns the individual indices for joint observation joI.*/
    const std::vector<Index>& JointToIndividualObservationIndices(Index joI) 
        const
        { return(_m_jointToIndObsCache.at(joI)); }

    /**\brief SoftPrints the action set for each agent.*/ 
    std::string SoftPrintActionSets() const;
    /**\brief Prints the action set for each agent.*/ 
    void PrintActionSets() const
        {std::cout << SoftPrintActionSets();}
    /**\brief SoftPrints the set of joint actions.*/
    std::string SoftPrintJointActionSet() const;
    /**\brief Prints the set of joint actions.*/
    void PrintJointActionSet() const
        {std::cout << SoftPrintJointActionSet();}
    /**\brief SoftPrints information regarding this 
     * TransitionObservationIndependentMADPDiscrete.*/
    std::string SoftPrint() const;
    /**\brief Prints information regarding this 
     * TransitionObservationIndependentMADPDiscrete.*/
    void Print() const
        {std::cout << SoftPrint();}
    std::string SoftPrintState(Index sI) const;

    void SetSparse(bool sparse);

    // stuff to implement MultiAgentDecisionProcessDiscreteInterface
    
    /**\brief returns probability of joint transition (the product of
     * the probabilities of the individual transitions)
     */
    double GetTransitionProbability(Index sI, Index jaI, Index 
                                    sucSI) const;
    double GetTransitionProbability(const std::vector<Index> &sIs,
                                    const std::vector<Index> &aIs,
                                    const std::vector<Index> &sucSIs) const;

    /**\brief Returns the probability of the joint observation joI (the
     * product of the individual observation probabilities, which depend
     * only on local states).
     */
    double GetObservationProbability(Index jaI, Index sucSI, 
                                     Index joI) const;
    double GetObservationProbability(const std::vector<Index> &aIs,
                                     const std::vector<Index> &sucSIs, 
                                     const std::vector<Index> &oIs) const;

    /**\brief returns a successor state index sampled according to the 
     * transition probabilities.
     */
    Index SampleSuccessorState(Index sI, Index jaI) const;
    std::vector<Index> SampleSuccessorState(const std::vector<Index> &sIs,
                                             const std::vector<Index> &aIs)
        const;
                                             
    /**\brief Returns a joint observation, sampled according to the 
     * observation probabilities.*/
    Index SampleJointObservation(Index jaI, Index sucI) const;
    std::vector<Index> SampleJointObservation(const std::vector<Index> &aIs,
                                               const std::vector<Index> &sucIs)
        const;

    /**\brief Samples an initial state.
     */
    Index SampleInitialState(void) const;
    std::vector<Index> SampleInitialStates(void) const;

    /**\brief returns the number of (joint) states.*/
    size_t GetNrStates() const
        { return(GetNrJointStates()); }
    
    /**\brief Returns a pointer to state i.*/
    const State* GetState(Index i) const;
    const State* GetState(const std::vector<Index> &sIs) const;
    
    /**\brief returns the prob. of state sI according to the initial state
     * distribution. */
    double GetInitialStateProbability(Index sI) const
        { return(_m_initialStateDistribution->at(sI)); }

    /**\brief returns the initial state distribution.*/
    //std::vector<double> GetISD() const;
    virtual const StateDistributionVector* GetISD() const;
    
    /**\brief returns a vector with the number of actions for each agent.*/
    const std::vector<size_t>& GetNrActions() const
        { return(_m_nrIndivActions); }
    
    /**\brief Get a pointer to action a of agentI.*/
    const Action* GetAction(Index agentI, Index a) const
        { return(GetIndividualMADPD(agentI)->GetAction(0,a)); }
    
    /**\brief Returns a pointer to joint action i.*/
    const JointAction* GetJointAction(Index i) const
        { return(GetJointActionDiscrete(i)); }
    
    /**\brief converts individual to joint actions.*/
    Index IndividualToJointActionIndices(Index* IndexArray) const;
    
    /**\brief Returns a vector with the number of observations for each
     * agent.*/
    const std::vector<size_t>& GetNrObservations() const
        { return(_m_nrIndivObs); }
    
    /**\brief Get the number of joint observations*/
    size_t GetNrJointObservations() const;
    
    /**\brief Get a pointer to observation o of agentI.*/
    const Observation* GetObservation(Index agentI, Index o) const
        { return(GetIndividualMADPD(agentI)->GetObservation(0,o)); }
    
    /**\brief Get a pointer to the i-th joint observation.*/
    const JointObservation* GetJointObservation(Index i) const;

    TGet* GetTGet() const;
    OGet* GetOGet() const;

    TransitionModelDiscrete* GetTransitionModelDiscretePtr() const
        { return(_m_p_tModel); }
    
    ObservationModelDiscrete* GetObservationModelDiscretePtr() const
        { return(_m_p_oModel); }
    
    void CreateCentralizedSparseModels();
    void CreateCentralizedFullModels();

};

#endif /* !_TRANSITIONOBSERVATIONINDEPENDENTMADPDISCRETE_H_ */


// Local Variables: ***
// mode:c++ ***
// End: ***
