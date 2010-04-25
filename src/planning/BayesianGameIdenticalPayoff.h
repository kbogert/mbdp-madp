/**\file BayesianGameIdenticalPayoff.h
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
 * $Id: BayesianGameIdenticalPayoff.h 3598 2009-08-20 12:29:54Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _BAYESIANGAMEIDENTICALPAYOFF_H_
#define _BAYESIANGAMEIDENTICALPAYOFF_H_ 1

/* the include directives */
#include <iostream>
#include <vector>
#include "Globals.h"
#include "RewardModelMapping.h"
#include "BayesianGameBase.h"
#include "BayesianGameIdenticalPayoffInterface.h"

/**\brief BayesianGameIdenticalPayoff is a class that represents a
 * Bayesian game with identical payoffs. (there is just 1 util
 * function)
 *
 * This is a self contained class:
 * meaning that it does not depend on any Multi-agent decision problem or 
 * Planning unit. This implies that, in order to convert a time-step of a MADP 
 * Planning Unit to a Bayesian game, indices of observation(-action) histories 
 * have to be converted. This class uses its own indices.
 */
class BayesianGameIdenticalPayoff : 
    //virtual 
    //public BayesianGameBase,
    //virtual 
    public BayesianGameIdenticalPayoffInterface
{
    private:

        /**private bool to indicate whether this BG is initialized.
         * To access the BayesianGameBase initialized bool use:
         * BayesianGameBase::_m_initialized
         */
        bool _m_initialized;

        /**Util function - in identical payoff case we need only 1 util function
         * We use RewardModelMapping substituting joint type indices for state
         * indices. */
        RewardModelMapping _m_utilFunction;
            
    protected:
    
    public:
        // Constructor, destructor and copy assignment.
        // (default) Constructor
        BayesianGameIdenticalPayoff();
        BayesianGameIdenticalPayoff(size_t nrAgents, 
                    const std::vector<size_t>& nrActions,  
                    const std::vector<size_t>& nrTypes);
        /// Destructor.
        //~BayesianGameIdenticalPayoff();
        //operators:

        //data manipulation (set) functions:
        
        /**Sets the initialized status to b. When setting to true - checks are
         * performed to see if this is a consistent Bayesian Game.*/
        bool SetInitialized(bool b);
        /**Sets the utility for (for all agents) jtype, ja to u*/
        void SetUtility(const Index jtype, const Index ja, const double u )
        {_m_utilFunction.Set(jtype,ja,u);}
        /**Sets the utility for (for all agents) joint type corresponding to 
         * the individual type indices (indTypeIndices) and joint action
         * corresponding to individual action indices (indActionIndices).*/
        void SetUtility(const std::vector<Index>& indTypeIndices, 
                const std::vector<Index>& indActionIndices,const double u )
        {_m_utilFunction.Set(
                IndividualToJointTypeIndices(indTypeIndices),
                IndividualToJointActionIndices(indActionIndices),
                u);}
        
        //get (data) functions:
        /**Gets the utility for (for all agents) jtype, ja.*/
        double GetUtility(const Index jtype, const Index ja) const
            {return(_m_utilFunction.Get(jtype,ja));}
        /**Gets the utility for (for all agents) joint type corresponding to 
         * the individual type indices (indTypeIndices) and joint action
         * corresponding to individual action indices (indActionIndices).*/
        double GetUtility(const std::vector<Index>& indTypeIndices, 
                const std::vector<Index>& indActionIndices ) const
        {return(_m_utilFunction.Get(
                IndividualToJointTypeIndices(indTypeIndices),
                IndividualToJointActionIndices(indActionIndices) ));}
        /** Prints a description of this  entire BayesianGameIdenticalPayoff 
         * to a string.*/
        std::string SoftPrint() const; 
        /**Print this BayesianGameIdenticalPayoff to cout.*/
        void Print() const
        { std::cout << SoftPrint();}
        /**Prints the utilities for jtype*/
        std::string SoftPrintUtilForJointType(Index jtype) const;
        /**\todo TODO: check if this can be deprecated \deprecated
         * Prints the utilities for jtype*/
        void PrintUtilForJointType(Index jtype) const
        {std::cout << SoftPrintUtilForJointType(jtype);}

        static void Save(const BayesianGameIdenticalPayoff &bg,
                         std::string filename);

        ///Loads a BG from file
        /**Note that it returns the BG by value, so the copy assignment
         * operator should be working. Also, this may be less suitable
         * for large BGs.
         */
        static BayesianGameIdenticalPayoff Load(std::string filename);
        ///Generates a random BG with identical payoffs.
        /**Note that it returns the BG by value, so the copy assignment
         * operator should be working. Also, this may be less suitable
         * for large BGs.
         */
        static BayesianGameIdenticalPayoff GenerateRandomBG(
            size_t nrAgents,
            std::vector<size_t> acs,
            std::vector<size_t> obs
            );
};


#endif /* !_BAYESIANGAMEIDENTICALPAYOFF_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
