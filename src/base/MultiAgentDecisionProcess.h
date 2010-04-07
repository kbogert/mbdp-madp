/**\file MultiAgentDecisionProcess.h
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
 * $Id: MultiAgentDecisionProcess.h 3598 2009-08-20 12:29:54Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _MULTIAGENTDECISIONPROCESS_H_
#define _MULTIAGENTDECISIONPROCESS_H_ 1

/* the include directives */
#include <string>
#include <vector>

#include "NamedDescribedEntity.h"
#include "MultiAgentDecisionProcessInterface.h"
#include "Agent.h"
#include "Globals.h"

/**\brief MultiAgentDecisionProcess is an class that defines the primary
 * properties of a decision process. 
 *
 * These primary properties are:
 * -the number of agents
 * -possibly, a vector of (named) agents
 * -the filename to be parsed, if applicable.
 * 
 * It is the only current implementation of MultiAgentDecisionProcessInterface
 * */
class MultiAgentDecisionProcess : 
    virtual public MultiAgentDecisionProcessInterface, 
    public NamedDescribedEntity
{
    private:
    
        void InitializeUnixName();

    protected:
        /**The number of agents participating in the MADP.*/
        size_t _m_nrAgents;
        /**Vector containing Agent objects, which are indexed named entities.*/
        std::vector<Agent> _m_agents;
        
        /**String holding the filename of the problem file to be parsed - if 
         * applicable.*/
        std::string _m_problemFile;
        /**String for the unix name of the MADP.*/
        std::string _m_unixName;

    public:
        // Constructor, destructor and copy assignment.
        /// Constructor.
        MultiAgentDecisionProcess(
            size_t nrAgents, 
            std::string name="received unspec. by MultiAgentDecisionProcess", 
            std::string description="received unspec. by MultiAgentDecisionProcess", 
            std::string pf="received unspec. by MultiAgentDecisionProcess");
        
        /// Default Constructor without specifying the number of agents.
        MultiAgentDecisionProcess(
            std::string name="received unspec. by MultiAgentDecisionProcess", 
            std::string description="received unspec. by MultiAgentDecisionProcess", 
            std::string pf="received unspec. by MultiAgentDecisionProcess");

        ///Destructor.    
        virtual ~MultiAgentDecisionProcess();

        /**Sets the number of agents. this creates nrAgents unnamed agents.*/
        void SetNrAgents(size_t nrAgents);
        /**Add a new agent with name "name" to the MADP. 
         * NOTE: This increments the number of agents as well!*/
        void AddAgent(std::string name);

        /**Returns the number of agents in this MultiAgentDecisionProcess. */
        size_t GetNrAgents() const;
        /**Returns the name of the problem file. */
        std::string GetProblemFile() const;

        /// \brief Returns a name which can be in unix path, by
        /// default the base part of the problem filename.
        std::string GetUnixName() const { return(_m_unixName); }

        /// Sets the name which can be used inin unix paths.
        void SetUnixName(std::string unixName) { _m_unixName=unixName; }

        /** Prints some information on the MultiAgentDecisionProcess.*/    
        std::string SoftPrint() const;
        void Print() const
        {std::cout << SoftPrint();}
};

#endif /* !_MULTIAGENTDECISIONPROCESS_H_ */


// Local Variables: ***
// mode:c++ ***
// End: ***
