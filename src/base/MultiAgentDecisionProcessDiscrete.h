/**\file MultiAgentDecisionProcessDiscrete.h
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
 * $Id: MultiAgentDecisionProcessDiscrete.h 4016 2010-03-11 16:56:02Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _MULTIAGENTDECISIONPROCESSDISCRETE_H_
#define _MULTIAGENTDECISIONPROCESSDISCRETE_H_ 1

/* the include directives */
#include <vector>
#include <string>

#include "MultiAgentDecisionProcess.h"
#include "MultiAgentDecisionProcessDiscreteInterface.h"
#include "MADPComponentDiscreteActions.h"
#include "MADPComponentDiscreteObservations.h"
#include "MADPComponentDiscreteStates.h"

class TGet;

/**\brief MultiAgentDecisionProcessDiscrete is defines the primary properties
 * of a discrete decision process.
 *
 * MultiAgentDecisionProcessDiscrete is defines the primary properties
 * of a discrete decision process.
 * 
 * It extends MultiAgentDecisionProcess, MADPComponentDiscreteActions and 
 * MADPComponentDiscreteObservations,
 * such that, for each of the MultiAgentDecisionProcess::GetNrAgents() it stores
 * -the discrete action sets 
 * -the discrete observation sets
 *
 * It also extends MADPComponentDiscreteStates such that a discrete state space 
 * is implemented. 
 * 
 * Finally, this class itself stores (pointers to)
 * -the transition model
 * -the observation model */
class MultiAgentDecisionProcessDiscrete : 
    virtual public MultiAgentDecisionProcessDiscreteInterface,
    public MultiAgentDecisionProcess,
    public MADPComponentDiscreteStates,
    public MADPComponentDiscreteActions,
    public MADPComponentDiscreteObservations

{
    private:    
        ///Boolean to indicate whether this MADPDiscrete has been initialized.
        bool _m_initialized;    

        /**\brief Boolean that controls whether sparse transition and 
         * observation models are used.
         */
        bool _m_sparse;
        
        /**\brief Check whether models appear valid probability
         * distributions.  
         *
         * This is a private function as to avoid
         * doubts as to what is and is not checked. (when called from
         * a derived class, no derived features are checked).*/
        bool SanityCheck(void);

        /// Pointer to transition model
        TransitionModelDiscrete* _m_p_tModel;

        /// Pointer to observation model
        ObservationModelDiscrete* _m_p_oModel;

    protected:    

        //data manipulation (set) functions:
        /**\brief Sets _m_initialized to b. 
         *
         * When setting to true, a verification of
         * member elements is performed. (i.e. a check whether all vectors
         * have the correct size and non-zero entries) */
        bool SetInitialized(bool b);
    public:
        // Constructor, destructor and copy assignment.
        /// Default constructor.
        MultiAgentDecisionProcessDiscrete();

        /**\brief Constructor that  sets the 
         * \li name
         * \li description 
         * \li problem file for the MADP.*/
        MultiAgentDecisionProcessDiscrete(
            std::string name="received unspec. by MultiAgentDecisionProcessDiscrete",
            std::string descr="received unspec.by MultiAgentDecisionProcessDiscrete",
            std::string pf="received unspec. by MultiAgentDecisionProcessDiscrete");
        /**\brief Constructor that  sets the 
         * \li nrAgents
         * \li nrStates
         * \li name
         * \li description 
         * \li problem file for the MADP.*/
        MultiAgentDecisionProcessDiscrete(
            int nrAgents, int nrS, std::string 
            name="received unspec. by MultiAgentDecisionProcessDiscrete",
            std::string descr="received unspec.by MultiAgentDecisionProcessDiscrete",
            std::string pf="received unspec. by MultiAgentDecisionProcessDiscrete");

        ///Destructor.
        ~MultiAgentDecisionProcessDiscrete();

        /**\brief A function that can be called by other classes in order to
         * request a MultiAgentDecisionProcessDiscrete to (try to)
         * initialize.*/
        bool Initialize()
            {return SetInitialized(true);}

        ///Creates a new transition model mapping.
        void CreateNewTransitionModel();
        ///Creates a new observation model mapping.
        void CreateNewObservationModel();

        ///Set the probability of successor state sucSI: P(sucSI|sI,jaI).
        void SetTransitionProbability(Index sI, Index jaI, Index sucSI, 
                double p);

        ///Set the probability of joint observation joI: P(joI|jaI,sucSI).
        void SetObservationProbability(Index jaI, Index sucSI, Index joI, 
                double p);
        
        // 'get' functions:     
        ///Return the probability of successor state sucSI: P(sucSI|sI,jaI).
        double GetTransitionProbability(Index sI, Index jaI, Index sucSI) 
            const;

        TGet* GetTGet() const;
        OGet* GetOGet() const;

        ///Return the probability of joint observation joI: P(joI|jaI,sucSI).
        double GetObservationProbability(Index jaI, Index sucSI, Index joI) 
            const;

        /// Sample a successor state.
        Index SampleSuccessorState(Index sI, Index jaI) const;

        /// Sample an observation.
        Index SampleJointObservation(Index jaI, Index sucI) const;

        ///SoftPrints information on the MultiAgentDecisionProcessDiscrete.
        std::string SoftPrint() const;
        ///Prints some information on the MultiAgentDecisionProcessDiscrete.
        void Print() const
        { std::cout << SoftPrint();}
        
        /**\brief Indicate whether sparse transition and observation models
         * should be used. 
         *
         * Default is to not use sparse models. Only
         * has effect before the class has been initialized. */
        void SetSparse(bool sparse);

        /// Are we using sparse transition and observation models?
        bool GetSparse() const { return(_m_sparse); }

        const TransitionModelDiscrete* GetTransitionModelDiscretePtr() const
        { return(_m_p_tModel); }

        const ObservationModelDiscrete* GetObservationModelDiscretePtr() const
        { return(_m_p_oModel); }

        /// Set the transition model.
        void SetTransitionModelPtr(TransitionModelDiscrete* ptr)
        { _m_p_tModel=ptr; }

        /// Set the obversation model.
        void SetObservationModelPtr(ObservationModelDiscrete* ptr)
        { _m_p_oModel=ptr; }

        /// Returns a pointer to a copy of this class.
        virtual MultiAgentDecisionProcessDiscrete* Clone() const
        { return new MultiAgentDecisionProcessDiscrete(*this); }

};

#include "TransitionModelDiscrete.h"
#include "ObservationModelDiscrete.h"

inline void MultiAgentDecisionProcessDiscrete::SetTransitionProbability(Index
        sI, Index jaI, Index sucSI, double p)
{ _m_p_tModel->Set(sI, jaI, sucSI, p);}
inline void MultiAgentDecisionProcessDiscrete::SetObservationProbability(Index
        jaI, Index sucSI, Index joI, double p)
{ _m_p_oModel->Set(jaI, sucSI, joI,p);}
inline double
MultiAgentDecisionProcessDiscrete::GetTransitionProbability(Index sI, Index
        jaI, Index sucSI) const
{ return(_m_p_tModel->Get(sI, jaI, sucSI));}
inline double
MultiAgentDecisionProcessDiscrete::GetObservationProbability(Index jaI, Index
        sucSI, Index joI) const
{ return(_m_p_oModel->Get(jaI, sucSI, joI));}
inline Index MultiAgentDecisionProcessDiscrete::SampleSuccessorState(Index
        sI, Index jaI) const
{ return(_m_p_tModel->SampleSuccessorState(sI,jaI));}
inline Index MultiAgentDecisionProcessDiscrete::SampleJointObservation(Index
        jaI, Index sucI) const
{ return(_m_p_oModel->SampleJointObservation(jaI,sucI)); }

#endif /* !_MULTIAGENTDECISIONPROCESS_H_ */


// Local Variables: ***
// mode:c++ ***
// End: ***
