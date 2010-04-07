/**\file MultiAgentDecisionProcessInterface.h
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
 * $Id: MultiAgentDecisionProcessInterface.h 4016 2010-03-11 16:56:02Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _MULTIAGENTDECISIONPROCESSINTERFACE_H_
#define _MULTIAGENTDECISIONPROCESSINTERFACE_H_ 1

/* the include directives */
#include <string>
#include <vector>

#include "Globals.h"

/**\brief MultiAgentDecisionProcessInterface is an abstract base class that
 * declares the primary properties of a multiagent decision process.
 *
 * These primary properties are:
 * \li the number of agents
 * \li possibly, a vector of (named) agents
 * \li the filename to be parsed, if applicable.
 * 
 * It is implemented by MultiAgentDecisionProcess
 * */
class MultiAgentDecisionProcessInterface 
{
    private:    

    protected:

    public:

        ///Destructor. 
        //(Can't make a virt.destr. pure abstract!)
        virtual ~MultiAgentDecisionProcessInterface() {}

        ///Return the number of agents
        virtual size_t GetNrAgents() const = 0;

        /// Returns the base part of the problem filename.
        virtual std::string GetUnixName() const = 0;
        /// Returns a copy of this class.
        virtual MultiAgentDecisionProcessInterface* Clone() const = 0;

};

#endif /* !_MULTIAGENTDECISIONPROCESSINTERFACE_H_ */


// Local Variables: ***
// mode:c++ ***
// End: ***
