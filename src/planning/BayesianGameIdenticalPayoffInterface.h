/**\file BayesianGameIdenticalPayoffInterface.h
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
 * $Id: BayesianGameIdenticalPayoffInterface.h 3604 2009-08-25 10:52:24Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _BAYESIANGAMEIDENTICALPAYOFFINTERFACE_H_
#define _BAYESIANGAMEIDENTICALPAYOFFINTERFACE_H_ 1

/* the include directives */
#include "Globals.h"
#include "BayesianGameBase.h"

/** \brief BayesianGameIdenticalPayoffInterface provides an interface
 * for Bayesian Games with identical payoffs. */
class BayesianGameIdenticalPayoffInterface 
    : public BayesianGameBase
    
{
    private:    
    
    protected:
    
    public:
        // Constructor, destructor and copy assignment.
        /// (default) Constructor
        BayesianGameIdenticalPayoffInterface()
        {};
        BayesianGameIdenticalPayoffInterface(
                    size_t nrAgents, 
                    const std::vector<size_t>& nrActions,  
                    const std::vector<size_t>& nrTypes)
        :
            BayesianGameBase(nrAgents, nrActions, nrTypes)
        {};
        
        //get (data) functions:
        /**Gets the utility for (for all agents) jtype, ja.*/
        virtual double GetUtility(const Index jtype, const Index ja) const = 0;
        /**Gets the utility for (for all agents) joint type corresponding to 
         * the individual type indices (indTypeIndices) and joint action
         * corresponding to individual action indices (indActionIndices).*/
        virtual double GetUtility(const std::vector<Index>& indTypeIndices, 
                const std::vector<Index>& indActionIndices ) const = 0;
        
        /** Prints a description of this  entire BayesianGameIdenticalPayoff 
         * to a string.*/
        virtual std::string SoftPrint() const = 0; 
        /**Print this BayesianGameIdenticalPayoff to cout.*/
        virtual void Print() const
        { std::cout << SoftPrint();}

};


#endif /* !_BAYESIANGAMEIDENTICALPAYOFFINTERFACE_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
