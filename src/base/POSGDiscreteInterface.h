/**\file POSGDiscreteInterface.h
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
 * $Id: POSGDiscreteInterface.h 4016 2010-03-11 16:56:02Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _POSGDISCRETEINTERFACE_H_
#define _POSGDISCRETEINTERFACE_H_ 1

/* the include directives */
#include <vector>
#include <string>
#include "Globals.h"
#include "MultiAgentDecisionProcessDiscreteInterface.h"
#include "POSGInterface.h"

/**\brief POSGDiscreteInterface is the interface for
 * a discrete POSG model: it defines the set/get reward functions.
 *
 * POSGDiscreteInterface is an interface (i.e. pure abstract class) for
 * a discrete POSG model. This means that there is a single reward function
 * and that states, actions and observations are discrete.
 *
 * Classes that implement this interface are, for instance, POSGDiscrete
 * and TransitionObservationIndependentPOSGDiscrete.
 **/
class POSGDiscreteInterface :
    virtual public MultiAgentDecisionProcessDiscreteInterface, 
    virtual public POSGInterface
{
    private:        

    protected:        
        
    public:
        /// Destructor.Can't make a virt.destr. pure abstract!
        virtual ~POSGDiscreteInterface() {};
        
        /// Creates a new reward model mapping.
        virtual void CreateNewRewardModelForAgent(
                Index agentI) = 0;
        /// Set the reward for state, joint action indices 
        virtual void SetRewardForAgent(Index agentI, Index sI, Index jaI, 
                                       double r) = 0;

        /// Set the reward for state, joint action , suc. state indices 
        virtual void SetRewardForAgent(Index agentI, Index sI, Index jaI,
                                       Index sucSI, double r) = 0;

        /// Set the reward for state, joint action, suc.state, joint obs indices
        virtual void SetRewardForAgent(Index agentI, Index sI, Index jaI, 
                Index sucSI, Index joI, double r) = 0;

        // 'get' functions:         
        /// Return the reward for state, joint action indices 
        virtual double GetRewardForAgent(Index agentI, Index sI, Index jaI) 
                const = 0;
        /// Returns a copy of this class.
        virtual POSGDiscreteInterface* Clone() const = 0;
        
};

#endif /* !_POSGDISCRETEINTERFACE_H_ */


// Local Variables: ***
// mode:c++ ***
// End: ***
