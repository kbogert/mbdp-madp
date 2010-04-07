/**\file MADPComponentDiscreteStates.h
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
 * $Id: MADPComponentDiscreteStates.h 3628 2009-08-26 12:08:56Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _MADPCOMPONENTDISCRETESTATES_H_
#define _MADPCOMPONENTDISCRETESTATES_H_ 1

/* the include directives */
#include <iostream>
#include <vector>
#include "Globals.h"

#include "MultiAgentDecisionProcessDiscreteInterface.h"
#include "StateDiscrete.h"

#include "StateDistributionVector.h"

/** 
 * \brief MADPComponentDiscreteStates is a class that represents a discrete
 * state space.
 *
 *  It implements a part of the
 *  MultiAgentDecisionProcessDiscreteInterface. */
class MADPComponentDiscreteStates: 
    virtual public MultiAgentDecisionProcessDiscreteInterface //which this implements partly
{
    private:
        bool _m_initialized;
        size_t _m_nrStates;
    
        ///Returns a string with the states
        std::string SoftPrintStates() const;
        ///Returns a string with the initial state distribution.
        std::string SoftPrintInitialStateDistribution() const;

    protected:
        /// A vector that contains all the states.
        std::vector<StateDiscrete> _m_stateVec;
        /// A StateDistributionVector that represents the initial state distribution. 
        StateDistributionVector* _m_initialStateDistribution;

    public:
        // Constructor, destructor and copy assignment.
        /// (default) Constructor
        MADPComponentDiscreteStates();
        /// Constructor that sets the number of states.
        MADPComponentDiscreteStates(size_t nrS);

        /// Destructor.
        virtual ~MADPComponentDiscreteStates();

        //operators:

        //data manipulation (set) functions:
        /// Sets _m_initialized to b.
        bool SetInitialized(bool b);

        /// Adds a new state.
        void AddState(std::string StateName);

        /// Sets the number of states to nrS.
        void SetNrStates(size_t nrS);

        /// Sets the initial state distribution to a uniform one.
        void SetUniformISD();

        /// Sets the initial state distribution to v.
        void SetISD(StateDistribution* p);
        void SetISD(StateDistributionVector* p)
        { _m_initialStateDistribution = p;}
        void SetISD(std::vector<double> v);
        
        //get (data) functions:        
        /// Return the number of states.
        size_t GetNrStates() const {return _m_nrStates;};

        /// Returns the state index of state s.
        Index GetStateIndex(StateDiscrete s) const;

        /// Returns the state index of state s.
        Index GetStateIndexByName(std::string s) const;
        
        /// Returns a pointer to state i. */
        const State* GetState(Index i) const 
            {return(&_m_stateVec.at(i)); }

        virtual std::string SoftPrintState(Index sI) const
        { return GetStateName(sI);}
        ///  Returns the name of a particular state i. 
        std::string GetStateName(Index i) const {
            return(_m_stateVec.at(i).SoftPrintBrief()); }

        /// Return the initial state distribution.
        double GetInitialStateProbability(Index sI) const;

        /// Returns the complete initial state distribution.
        //std::vector<double> GetISD() const { return(_m_initialStateDistribution); }
        virtual StateDistribution* GetISD() 
        { return(_m_initialStateDistribution); }
        virtual const StateDistribution* GetISD() const 
        { return(_m_initialStateDistribution); }
        
        /// Sample a state according to the initial state PDF.
        Index SampleInitialState() const;
        
        std::string SoftPrint() const;
        void Print() const
        {std::cout << SoftPrint();}
};


#endif /* !_MADPCOMPONENTDISCRETESTATES_H_ */


// Local Variables: ***
// mode:c++ ***
// End: ***
